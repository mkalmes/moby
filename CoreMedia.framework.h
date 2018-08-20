// ==========  CoreMedia.framework/Headers/CMAttachment.h
/*
    File:  CMAttachment.h

	Framework:  CoreMedia
 
    Copyright 2006-2015 Apple Inc. All rights reserved.

*/

#ifndef CMATTACHMENT_H
#define CMATTACHMENT_H

#include <Availability.h>
#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C" {
#endif
    
#pragma pack(push, 4)
	
CF_IMPLICIT_BRIDGING_ENABLED

/* A CMAttachmentBearer is a CF-based object that supports the suite of key/value/mode attachment APIs defined in this header file.  Since plain C has no type subclassing, we use CFType as the basis for the CMAttachmentBearer type.  (Not all CFTypes support CMAttachmentBearer methods; if a CMAttachmentBearer method is called on a CF object that does not support it, it will fail.) */
typedef CM_BRIDGED_TYPE(id) CFTypeRef CMAttachmentBearerRef;

// The attachment modes are the same as those defined in CVBuffer.h.
typedef uint32_t CMAttachmentMode;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMAttachmentMode
#else
enum
#endif
{
	kCMAttachmentMode_ShouldNotPropagate    = 0,
	kCMAttachmentMode_ShouldPropagate       = 1
};

/*!
    @function   CMSetAttachment
    @abstract   Sets or adds a attachment of a CMAttachmentBearer
    @discussion You can attach any CF object to a CMAttachmentBearer object to store additional information. CMSetAttachment stores an attachment identified by a key. If the key doesn't exist, the attachment will be added. If the key does exist, the existing attachment will be replaced. In both cases the retain count of the attachment will be incremented. The value can be any CFType but nil has no defined behavior.  Given a CVBufferRef, CMSetAttachment is equivalent to CVBufferSetAttachment.
    @param      target  Target CMAttachmentBearer.
    @param      key     Key in form of a CFString identifying the desired attachment.
    @param      value	Attachment in form af a CF object.
    @param      attachmentMode	Specifies which attachment mode is desired for this attachment.   A particular attachment key may only exist in
                                a single mode at a time.
*/
CM_EXPORT void	CMSetAttachment(CMAttachmentBearerRef CM_NONNULL target, CFStringRef CM_NONNULL key, CFTypeRef CM_NULLABLE value, CMAttachmentMode attachmentMode) __OSX_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_0 );


/*!
    @function   CMGetAttachment
    @abstract   Returns a specific attachment of a CMAttachmentBearer
    @discussion You can attach any CF object to a CMAttachmentBearer to store additional information. CMGetAttachment retrieves an attachment identified by a key.  Given a CVBufferRef, CMGetAttachment is equivalent to CVBufferGetAttachment.
    @param      target  Target CMAttachmentBearer.
    @param      key	Key in form of a CFString identifying the desired attachment.
    @param      attachmentModeOut.  Returns the mode of the attachment, if desired.  May be NULL.
    @result     If found the attachment object; else NULL.
*/
CM_EXPORT CFTypeRef CM_NULLABLE CMGetAttachment(CMAttachmentBearerRef CM_NONNULL target, CFStringRef CM_NONNULL key, CMAttachmentMode * CM_NULLABLE attachmentModeOut) __OSX_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_0 );

/*!
    @function   CMRemoveAttachment
    @abstract   Removes a specific attachment of a CMAttachmentBearer
    @discussion CMRemoveAttachment removes an attachment identified by a key. If found the attachment is removed and the retain count decremented.  Given a CVBufferRef, CMRemoveAttachment is equivalent to CVBufferRemoveAttachment.
    @param      target  Target CMAttachmentBearer.
    @param      key	Key in form of a CFString identifying the desired attachment.
*/
CM_EXPORT void	CMRemoveAttachment(CMAttachmentBearerRef CM_NONNULL target, CFStringRef CM_NONNULL key) __OSX_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_0 );

/*!
    @function   CMRemoveAllAttachments
    @abstract   Removes all attachments of a CMAttachmentBearer
    @discussion While CMRemoveAttachment removes a specific attachment identified by a key CMRemoveAllAttachments removes all attachments of a buffer and decrements their retain counts.  Given a CVBufferRef, CMRemoveAllAttachments is equivalent to CVBufferRemoveAllAttachments.
    @param      target  Target CMAttachmentBearer.
*/
CM_EXPORT void	CMRemoveAllAttachments(CMAttachmentBearerRef CM_NONNULL target) __OSX_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_0 );

/*!
    @function   CMCopyDictionaryOfAttachments
    @abstract   Returns all attachments of a CMAttachmentBearer
    @discussion CMCopyDictionaryOfAttachments is a convenience call that returns all attachments with their corresponding keys in a new CFDictionary that the caller must dispose by calling CFRelease.  Given a CVBufferRef, CMCopyDictionaryOfAttachments is similar to CVBufferGetAttachments, except that CVBufferGetAttachments returns a CFDictionary that may change if attachments are added later.
    @param      allocator  Allocator for the new dictionary; pass kCFAllocatorDefault or NULL to use the default allocator.
    @param      target  Target CMAttachmentBearer.
    @result     A CFDictionary with all buffer attachments identified by there keys. If no attachment is present, NULL is returned.  Returns NULL
		for invalid attachment mode.
*/
CM_EXPORT CFDictionaryRef CM_NULLABLE CMCopyDictionaryOfAttachments(CFAllocatorRef CM_NULLABLE allocator, CMAttachmentBearerRef CM_NONNULL target, CMAttachmentMode attachmentMode) __OSX_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_0 );

/*!
    @function   CMSetAttachments
    @abstract   Sets a set of attachments for a CMAttachmentBearer
    @discussion CMSetAttachments is a convenience call that in turn calls CMSetAttachment for each key and value in the given dictionary. All key value pairs must be in the root level of the dictionary.  Given a CVBufferRef, CMSetAttachments is equivalent to CVBufferSetAttachments.
    @param      target  Target CMAttachmentBearer.
*/
CM_EXPORT void CMSetAttachments(CMAttachmentBearerRef CM_NONNULL target, CFDictionaryRef CM_NONNULL theAttachments, CMAttachmentMode attachmentMode) __OSX_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_0 );

/*!
    @function   CMPropagateAttachments
    @abstract   Copy all propagatable attachments from one buffer to another.
    @discussion CMPropagateAttachments is a convenience call that copies all attachments with a mode of kCMAttachmentMode_ShouldPropagate from one
                buffer to another.  Given a CVBufferRef, CMPropagateAttachments is equivalent to CVBufferPropagateAttachments.
    @param      source  CMAttachmentBearer to copy attachments from.
    @param      destination  CMAttachmentBearer to copy attachments to.
*/
CM_EXPORT void  CMPropagateAttachments(CMAttachmentBearerRef CM_NONNULL source, CMAttachmentBearerRef CM_NONNULL destination) __OSX_AVAILABLE_STARTING( __MAC_10_7, __IPHONE_4_0 );
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // CMATTACHMENT_H
// ==========  CoreMedia.framework/Headers/CMAudioClock.h
/*
	File:  CMAudioClock.h
 
	Framework:  CoreMedia
 
	Copyright 2006-2015 Apple Inc. All rights reserved.
 
*/

#ifndef __CMAUDIOCLOCK__
#define __CMAUDIOCLOCK__

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMSync.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

/*!
	@function	CMAudioClockCreate
	@abstract	Creates a clock that advances at the same rate as audio output.
	@discussion
		This clock will not drift from audio output, but may drift from CMClockGetHostTimeClock().
		When audio output is completely stopped, the clock continues to advance, tracking CMClockGetHostTimeClock() 
		until audio output starts up again.
		This clock is suitable for use as AVPlayer.masterClock when synchronizing video-only playback 
		with audio played through other APIs or objects.
	@param	allocator
		A CFAllocator to use to allocate the clock.  
		Pass kCFAllocatorDefault or NULL to use the default allocator.
	@param	clockOut
		Points to a CMClockRef to receive the newly created clock.
		The caller is responsible for calling CFRelease to release this clock.
*/
CM_EXPORT OSStatus
CMAudioClockCreate(
		CM_NULLABLE CFAllocatorRef allocator,
		CM_RETURNS_RETAINED_PARAMETER CM_NULLABLE CMClockRef * CM_NONNULL clockOut)
			__OSX_AVAILABLE_STARTING(__MAC_NA, __IPHONE_6_0);

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // __CMAUDIOCLOCK__
// ==========  CoreMedia.framework/Headers/CMTimeRange.h
/*
    File:  CMTimeRange.h
	
	Framework:  CoreMedia
 
    Copyright 2007-2015 Apple Inc. All rights reserved.
 
*/

#ifndef CMTIMERANGE_H
#define CMTIMERANGE_H

/*!
	@header
	@abstract	API for creating and manipulating CMTimeRange structs.
	@discussion	CMTimeRange structs are non-opaque mutable structs that represent time ranges.
	
				A CMTimeRange is represented as two CMTime structs, one that specifies the start time of the
				range and another that specifies the duration of the range. A time range does not include the time
				that is the start time plus the duration. In other words, the following expression
				
					CMTimeRangeContainsTime(range, CMTimeRangeGetEnd(range))
					
				always evaluates to false.
				
				CMTimeRanges can be converted to/from immutable CFDictionaries, via CMTimeRangeCopyAsDictionary and
				CMTimeRangeMakeFromDictionary, for use in annotations and various CF containers.
				
				The epoch in a CMTime that represents a duration should always be 0, and the value must be non-negative. 
				The epoch in a CMTime that	represents a timestamp may be non-zero, but range operations (such as
				CMTimeRangeGetUnion) can only be performed on ranges whose start fields have the same epoch. 
				CMTimeRanges cannot span different epochs.
*/

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTime.h>
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	CMTimeRange
	@abstract	A time range represented as two CMTime structures.
*/
typedef struct
{
	CMTime			start;		/*! @field start The start time of the time range. */
	CMTime			duration;	/*! @field duration The duration of the time range. */
} CMTimeRange;

/*!
	@function	CMTIMERANGE_IS_VALID
    @abstract   Returns whether a CMTimeRange is valid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange is valid, false if it is invalid.
*/
#define CMTIMERANGE_IS_VALID(range) ((Boolean)(CMTIME_IS_VALID(range.start) && CMTIME_IS_VALID(range.duration) && (range.duration.epoch == 0) && (range.duration.value >= 0)))

/*!
	@function	CMTIMERANGE_IS_INVALID
    @abstract   Returns whether a CMTimeRange is invalid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange is invalid, false if it is valid.
*/
#define CMTIMERANGE_IS_INVALID(range) (! CMTIMERANGE_IS_VALID(range))

/*!
	@function	CMTIMERANGE_IS_INDEFINITE
    @abstract   Returns whether a CMTimeRange is indefinite.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange is indefinite, false if it is not.
*/
#define CMTIMERANGE_IS_INDEFINITE(range) ((Boolean)(CMTIMERANGE_IS_VALID(range) && (CMTIME_IS_INDEFINITE(range.start) || CMTIME_IS_INDEFINITE(range.duration))))

/*!
	@function	CMTIMERANGE_IS_EMPTY
    @abstract   Returns whether a CMTimeRange has a duration of 0.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeRange has a duration of 0, false if it is not.
*/
#define CMTIMERANGE_IS_EMPTY(range) ((Boolean)(CMTIMERANGE_IS_VALID(range) && (CMTIME_COMPARE_INLINE(range.duration, ==, kCMTimeZero))))

CM_EXPORT const CMTimeRange kCMTimeRangeZero	/*! @constant kCMTimeRangeZero 
													Use this constant to generate an empty CMTimeRange at 0. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);		

CM_EXPORT const CMTimeRange kCMTimeRangeInvalid /*! @constant kCMTimeRangeInvalid 
													Use this constant to generate an invalid CMTimeRange. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeMake
	@abstract	Make a valid CMTimeRange with start and duration.
	@result		The resulting CMTimeRange.
    @discussion The duration parameter must have an epoch of 0; otherwise an invalid time range will be returned.
*/
CM_EXPORT CMTimeRange CMTimeRangeMake(
				CMTime start,					/*! @param start			Initializes the start field of the resulting CMTimeRange. */
				CMTime duration)				/*! @param duration			Initializes the duration field of the resulting CMTimeRange. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
 
/*!
	@function	CMTimeRangeGetUnion
    @abstract   Returns the union of two CMTimeRanges.
    @discussion	This function returns a CMTimeRange structure that represents the union of the time ranges specified by the <i>range1</i> and <i>range2</i> parameters.
				This is the smallest range that includes all times that are in either range.
	@result     The union of the two CMTimeRanges.
*/
CM_EXPORT CMTimeRange CMTimeRangeGetUnion(
				CMTimeRange range1,				/*! @param range1			A CMTimeRange to be unioned. */
				CMTimeRange range2)				/*! @param range2			Another CMTimeRange to be unioned. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeGetIntersection
    @abstract   Returns the intersection of two CMTimeRanges.
    @discussion	This function returns a CMTimeRange structure that represents the intersection of the time ranges specified by the <i>range1</i> and <i>range2</i> parameters.
				This is the largest range that both ranges include.
	@result     The intersection of the two CMTimeRanges.
*/
CM_EXPORT CMTimeRange CMTimeRangeGetIntersection(
				CMTimeRange range1,				/*! @param range1			A CMTimeRange to be intersected. */
				CMTimeRange range2)				/*! @param range2			Another CMTimeRange to be intersected. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeEqual
    @abstract   Returns a Boolean value that indicates whether two CMTimeRanges are identical.
    @discussion	This function returns a Boolean value that indicates whether the time ranges specified by the <i>range1</i> and <i>range2</i> parameters are identical.
    @result     Returns true if the two time ranges are identical, false if they differ.
*/
CM_EXPORT Boolean CMTimeRangeEqual(
				CMTimeRange range1,				/*! @param range1			A CMTimeRange to be compared for equality. */
				CMTimeRange range2)				/*! @param range2			Another CMTimeRange to be compared for equality. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeContainsTime
	@abstract	Indicates whether a time is contained within a time range.
    @discussion	This function returns a Boolean value that indicates whether the time specified by the <i>time</i> parameter
				is contained within the range specified by the <i>range</i> parameter.
    @result     Returns true if the specified time is contained within the specified time range, false if it is not.
*/
CM_EXPORT Boolean CMTimeRangeContainsTime(
				CMTimeRange range,				/*! @param range			A CMTimeRange to be tested for inclusion. */
				CMTime time)					/*! @param time				A CMTime to be tested for inclusion. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeContainsTimeRange
	@abstract	Indicates whether a time range is contained within a time range.
    @discussion	This function returns a Boolean value that indicates whether the time range specified by the <i>range1</i> parameter
				contains the range specified by the <i>range2</i> parameter.
    @result     Returns true if the second time range is contained within the first time range, false if it is not.
*/
CM_EXPORT Boolean CMTimeRangeContainsTimeRange(
				CMTimeRange range1,				/*! @param range1			A CMTimeRange. */
				CMTimeRange range2)				/*! @param range2			Another CMTimeRange to be tested for inclusion. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeGetEnd
	@abstract	Returns a CMTime structure representing the end of a time range.
    @result		A CMTime structure representing the end of the specified time range.
    @discussion	This function returns a CMTime structure that indicates the end of the time range specified by the <i>range</i> parameter.
    			CMTimeRangeContainsTime(range, CMTimeRangeGetEnd(range)) is always false.
*/
CM_EXPORT CMTime CMTimeRangeGetEnd(
				CMTimeRange range)				/*! @param range			A CMTimeRange. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeMapTimeFromRangeToRange
	@abstract	Translates a time through a mapping from CMTimeRange to CMTimeRange.
	@result		A CMTime structure representing the translated time.
	@discussion	The start and end time of fromRange will be mapped to the start and end time of toRange respectively.
    			Other times will be mapped linearly, using the formula:
    				result = (t-fromRange.start)*(toRange.duration/fromRange.duration)+toRange.start
    			If either CMTimeRange argument is empty, an invalid CMTime will be returned.
    			If t does not have the same epoch as fromRange.start, an invalid CMTime will be returned.
    			If both fromRange and toRange have duration kCMTimePositiveInfinity, 
    			t will be offset relative to the differences between their starts, but not scaled.
*/
CM_EXPORT CMTime CMTimeMapTimeFromRangeToRange( 
				CMTime t, 
				CMTimeRange fromRange, 
				CMTimeRange toRange )
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeClampToRange
	@abstract	For a given CMTime and CMTimeRange, returns the nearest CMTime inside that time range.
	@result		A CMTime structure inside the given time range.
	@discussion	Times inside the given time range will be returned unmodified.
    			Times before the start and after the end time of the time range will return the start and end time of 
    			the range respectively.
    			If the CMTimeRange argument is empty, an invalid CMTime will be returned.
    			If the given CMTime is invalid, the returned CMTime will be invalid, 
*/
CM_EXPORT CMTime CMTimeClampToRange( 
				CMTime time, 
				CMTimeRange range )
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeMapDurationFromRangeToRange
	@abstract	Translates a duration through a mapping from CMTimeRange to CMTimeRange.
	@result		A CMTime structure representing the translated duration.
	@discussion	The duration will be scaled in proportion to the ratio between the ranges' durations:
    				result = dur*(toRange.duration/fromRange.duration)
    			If dur does not have the epoch zero, an invalid CMTime will be returned.
*/
CM_EXPORT CMTime CMTimeMapDurationFromRangeToRange( 
				CMTime dur, 
				CMTimeRange fromRange, 
				CMTimeRange toRange )
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
/*!
	@function	CMTimeRangeFromTimeToTime
	@abstract	Make a valid CMTimeRange with the given starting and ending times.
	@result		The resulting CMTimeRange.
*/
CM_EXPORT CMTimeRange CMTimeRangeFromTimeToTime(
				CMTime start, 
				CMTime end )
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeCopyAsDictionary
    @abstract   Returns a CFDictionary version of a CMTimeRange.
    @discussion This is useful when putting CMTimeRanges in CF container types.
    @result     A CFDictionary version of the CMTimeRange.
*/
CM_EXPORT CFDictionaryRef CM_NULLABLE CMTimeRangeCopyAsDictionary(
				CMTimeRange range,							/*! @param range			The CMTimeRange from which to create a dictionary. */
				CFAllocatorRef CM_NULLABLE  allocator)		/*! @param allocator		CFAllocator with which to create a dictionary. Pass kCFAllocatorDefault to use the default allocator. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeMakeFromDictionary
    @abstract   Reconstitutes a CMTimeRange struct from a CFDictionary previously created by CMTimeRangeCopyAsDictionary.
    @discussion This is useful when getting CMTimeRanges from CF container types.  If the CFDictionary does not
				have the requisite keyed values, an invalid time range is returned.
	@result		The created CMTimeRange.  
*/
CM_EXPORT CMTimeRange CMTimeRangeMakeFromDictionary(
				CFDictionaryRef CM_NONNULL dict)			/*! @param dict				A CFDictionary from which to create a CMTimeRange. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_BEGIN

/*!
	@defined kCMTimeRangeTimeKey
	@discussion CFDictionary key for start field of a CMTimeRange (CMTime)
*/
CM_EXPORT const CFStringRef kCMTimeRangeStartKey
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@defined kCMTimeRangeDurationKey
	@discussion CFDictionary key for timescale field of a CMTimeRange (CMTime)
*/
CM_EXPORT const CFStringRef kCMTimeRangeDurationKey
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_END

/*!
	@function	CMTimeRangeCopyDescription
    @abstract   Creates a CFString with a description of a CMTimeRange (just like CFCopyDescription).
    @discussion This is used from within CFShow on an object that contains CMTimeRange fields. It is
				also useful from other client debugging code.  The caller owns the returned CFString and is responsible for releasing it.
	@result		The created CFString description.  
*/
CM_EXPORT CFStringRef CM_NULLABLE CMTimeRangeCopyDescription(
				CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator		CFAllocator with which to create description. Pass kCFAllocatorDefault to use the default allocator. */
				CMTimeRange range)							/*! @param range			The CMTimeRange to describe. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeRangeShow
    @abstract   Prints a description of the CMTimeRange (just like CFShow).
    @discussion This is most useful from within gdb.
*/
CM_EXPORT void CMTimeRangeShow(
				CMTimeRange range)				/*! @param range			The CMTimeRange to show. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@typedef	CMTimeMapping
	@abstract	A CMTimeMapping specifies the mapping of a segment of one time line (called "source") into another time line (called "target").
	@discussion
		When used for movie edit lists, the source time line is the media and the target time line is the track/movie.
	@field	source
		The time range on the source time line.  
		For an empty edit, source.start is an invalid CMTime, in which case source.duration shall be ignored.
		Otherwise, source.start is the starting time within the source, and source.duration is the duration 
		of the source timeline to be mapped to the target time range.
	@field	target
		The time range on the target time line.
		If target.duration and source.duration are different, then the source segment should
		be played at rate source.duration/target.duration to fit.
*/
typedef struct 
{
	CMTimeRange source; // eg, media.  source.start is kCMTimeInvalid for empty edits.
	CMTimeRange target; // eg, track.
} CMTimeMapping;

/*!
	@function	CMTIMEMAPPING_IS_VALID
    @abstract   Returns whether a CMTimeMapping is valid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeMapping is valid, false if it is invalid.
*/
#define CMTIMEMAPPING_IS_VALID(mapping) (CMTIMERANGE_IS_VALID(mapping.target))

/*!
	@function	CMTIMEMAPPING_IS_INVALID
    @abstract   Returns whether a CMTimeMapping is invalid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeMapping is invalid, false if it is valid.
*/
#define CMTIMEMAPPING_IS_INVALID(mapping) (! CMTIMEMAPPING_IS_VALID(mapping))

/*!
	@function	CMTIMEMAPPING_IS_EMPTY
    @abstract   Returns whether a CMTimeMapping is empty.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTimeMapping is empty, false if it is not empty.
*/
#define CMTIMEMAPPING_IS_EMPTY(mapping) ((Boolean)((! CMTIME_IS_NUMERIC(mapping.source.start)) && CMTIMERANGE_IS_VALID(mapping.target)))

CM_EXPORT const CMTimeMapping kCMTimeMappingInvalid /*! @constant kCMTimeMappingInvalid 
													Use this constant to generate an invalid CMTimeMapping. */
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

/*!
	@function	CMTimeMappingMake
	@abstract	Make a valid CMTimeMapping with source and target.
	@result		The resulting CMTimeMapping.
    @discussion The source and target parameters must have durations whose epoch is 0; otherwise an invalid time mapping will be returned.
*/
CM_EXPORT CMTimeMapping CMTimeMappingMake(
				CMTimeRange source,				/*! @param source			Initializes the source field of the resulting CMTimeMapping. */
				CMTimeRange target)				/*! @param target			Initializes the target field of the resulting CMTimeMapping. */
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
 
/*!
	@function	CMTimeMappingMakeEmpty
	@abstract	Make a valid CMTimeMapping with an empty source.
	@result		The resulting CMTimeMapping.
    @discussion The target parameter must have a duration whose epoch is 0; otherwise an invalid time mapping will be returned.
*/
CM_EXPORT CMTimeMapping CMTimeMappingMakeEmpty(
				CMTimeRange target)				/*! @param target			Initializes the target field of the resulting CMTimeMapping. */
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
 
/*!
	@function	CMTimeMappingCopyAsDictionary
    @abstract   Returns a CFDictionary version of a CMTimeMapping.
    @discussion This is useful when putting CMTimeMappings in CF container types.
    @result     A CFDictionary version of the CMTimeMapping.
*/
CM_EXPORT CFDictionaryRef CM_NULLABLE CMTimeMappingCopyAsDictionary(
				CMTimeMapping mapping,			/*! @param mapping			The CMTimeMapping from which to create a dictionary. */
				CFAllocatorRef CM_NULLABLE allocator)		/*! @param allocator		CFAllocator with which to create a dictionary. Pass kCFAllocatorDefault to use the default allocator. */
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

/*!
	@function	CMTimeMappingMakeFromDictionary
    @abstract   Reconstitutes a CMTimeMapping struct from a CFDictionary previously created by CMTimeMappingCopyAsDictionary.
    @discussion This is useful when getting CMTimeMappings from CF container types.  If the CFDictionary does not
				have the requisite keyed values, an invalid time mapping is returned.
	@result		The created CMTimeMapping.  
*/
CM_EXPORT CMTimeMapping CMTimeMappingMakeFromDictionary(
				CFDictionaryRef CM_NONNULL dict)			/*! @param dict				A CFDictionary from which to create a CMTimeMapping. */
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_ASSUME_NONNULL_BEGIN
/*!
	@defined kCMTimeMappingSourceKey
	@discussion CFDictionary key for source field of a CMTimeMapping (CMTimeRange)
*/
CM_EXPORT const CFStringRef kCMTimeMappingSourceKey
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

/*!
	@defined kCMTimeMappingTargetKey
	@discussion CFDictionary key for target field of a CMTimeMapping (CMTimeRange)
*/
CM_EXPORT const CFStringRef kCMTimeMappingTargetKey
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_ASSUME_NONNULL_END
/*!
	@function	CMTimeMappingCopyDescription
    @abstract   Creates a CFString with a description of a CMTimeMapping (just like CFCopyDescription).
    @discussion This is used from within CFShow on an object that contains CMTimeMapping fields. It is
				also useful from other client debugging code.  The caller owns the returned CFString and is responsible for releasing it.
	@result		The created CFString description.  
*/
CM_EXPORT CFStringRef CM_NULLABLE CMTimeMappingCopyDescription(
				CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator		CFAllocator with which to create description. Pass kCFAllocatorDefault to use the default allocator. */
				CMTimeMapping mapping)			/*! @param mapping			The CMTimeMapping to describe. */
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

/*!
	@function	CMTimeMappingShow
    @abstract   Prints a description of a CMTimeMapping (just like CFShow).
    @discussion This is most useful from within gdb.
*/
CM_EXPORT void CMTimeMappingShow(
				CMTimeMapping mapping)			/*! @param mapping			The CMTimeMapping to show. */
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
	
#endif // CMTIMERANGE_H
// ==========  CoreMedia.framework/Headers/CMSimpleQueue.h
/*
	File:  CMSimpleQueue.h
	
	Framework:  CoreMedia
 
    Copyright 2006-2015 Apple Inc. All rights reserved.
  
*/

#ifndef CMSIMPLEQUEUE_H
#define CMSIMPLEQUEUE_H

/*!
	@header
	@abstract	API for creating and using CMSimpleQueues.
	@discussion	CMSimpleQueues are CF-based objects that implement a simple lockless FIFO queue of (void *)
				elements. The elements are not assumed to be pointers; they could be simple pointer-sized
				numeric values (although NULL or 0-valued elements are not allowed). If the elements are
				in fact pointers to allocated memory buffers, buffer lifetime management must be handled
				externally.
				
				A CMSimpleQueue can safely handle one enqueueing thread and one dequeueing thread.
				
				CMSimpleQueues are lockless. As such, Enqueues and/or Dequeues can occur on the CoreAudio ioProc
				thread, where locking/blocking is forbidden.
				
				The current status of a CMSimpleQueue can be interrogated.  Clients can get the current number
				of elements in the queue (GetCount) as well as the maximum capacity of the queue (GetCapacity).
				There is also a convenience macro (GetFullness) that uses those two APIs to compute a Float32
				between 0.0 and 1.0, representing the fullness of the queue.  For example, 0.0 represents an
				empty queue, 0.5 represents a queue that is half-full, and 1.0 represents a full queue.
				
				CMSimpleQueues can be reset. This returns them to a newly created state, with no elements in the queue
				(but with the maximum capacity unchanged).
*/

#include <CoreMedia/CMBase.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

//=============================================================================
//	Errors
//=============================================================================

/*!
	@enum CMSimpleQueue Errors
	@discussion The OSStatus errors returned from the CMSimpleQueue APIs.
	@constant	kCMSimpleQueueError_AllocationFailed			An allocation failed.
	@constant	kCMSimpleQueueError_RequiredParameterMissing	NULL or 0 was passed for a required parameter.
	@constant	kCMSimpleQueueError_ParameterOutOfRange			An out-of-range value was passed for a parameter with a restricted valid range.
	@constant	kCMSimpleQueueError_QueueIsFull					Operation failed because queue was full.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMSimpleQueueError_AllocationFailed					= -12770,
	kCMSimpleQueueError_RequiredParameterMissing			= -12771,
	kCMSimpleQueueError_ParameterOutOfRange					= -12772,
	kCMSimpleQueueError_QueueIsFull							= -12773,
};

//=============================================================================
//	Types
//=============================================================================

/*!
	@typedef	CMSimpleQueueRef
	@abstract	A reference to a CMSimpleQueue, a CF object that implements a simple lockless queue of (void *) elements.
		
*/
typedef struct CM_BRIDGED_TYPE(id) opaqueCMSimpleQueue *CMSimpleQueueRef;

//=============================================================================

/*!
	@function	CMSimpleQueueGetTypeID
	@abstract	Returns the CFTypeID of CMSimpleQueue objects.
	@discussion	You can check if a CFTypeRef object is actually a CMSimpleQueue by comparing CFGetTypeID(object)
				with CMSimpleQueueGetTypeID().
	@result		CFTypeID of CMSimpleQueue objects.
*/
CM_EXPORT
CFTypeID CMSimpleQueueGetTypeID(void)
			__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@function	CMSimpleQueueCreate
    @abstract	Creates a CMSimpleQueue.
    @discussion On return, the caller owns the returned CMSimpleQueue, and must release it when done with it.
    @result		Returns noErr if the call succeeds.  Returns kCMSimpleQueueError_ParameterOutOfRange if
				capacity is negative.
*/
CM_EXPORT
OSStatus CMSimpleQueueCreate(
	CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
																Allocator used to allocate storage for the queue. */
	int32_t capacity,										/*! @param capacity
																Capacity of the queue (maximum number of elements holdable at any
																given time).  Required (must not be 0).  Must be a positive value. */
	CM_RETURNS_RETAINED_PARAMETER CMSimpleQueueRef CM_NULLABLE * CM_NONNULL queueOut)		/*! @param queueOut Returned newly created queue is written to this address.
																Must not be NULL. */
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@function	CMSimpleQueueEnqueue
    @abstract	Enqueues an element on the queue.
    @discussion	If the queue is full, this operation will fail.
	@result		Returns noErr if the call succeeds, kCMSimpleQueueError_QueueIsFull if the queue is full.
*/
CM_EXPORT
OSStatus CMSimpleQueueEnqueue(
	CMSimpleQueueRef CM_NONNULL queue,		/*! @param queue
												The queue on which to enqueue the element. Must not be NULL. */
	const void * CM_NONNULL element)		/*! @param element
												Element to enqueue. Must not be NULL (NULL is returned from Dequeue
												to indicate an empty queue). */
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@function	CMSimpleQueueDequeue
    @abstract	Dequeues an element from the queue.
    @discussion If the queue is empty, NULL will be returned.
	@result		The dequeued element.  NULL if the queue was empty, or if there was some other error.
*/
CM_EXPORT
const void * CM_NULLABLE CMSimpleQueueDequeue(
	CMSimpleQueueRef CM_NONNULL queue) 	/*! @param queue
											The queue from which to dequeue an element. Must not be NULL. */
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@function	CMSimpleQueueGetHead
    @abstract	Returns the element at the head of the queue.
    @discussion If the queue is empty, NULL will be returned.
	@result		The head element.  NULL if the queue was empty, or if there was some other error.
*/
CM_EXPORT
const void * CM_NULLABLE CMSimpleQueueGetHead(
	CMSimpleQueueRef CM_NONNULL queue) 	/*! @param queue
											The queue from which to get the head element. Must not be NULL. */
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@function	CMSimpleQueueReset
    @abstract	Resets the queue.
    @discussion	This function resets the queue to its empty state;  all values
				in the queue prior to reset are lost.   Note that CMSimpleQueueReset
				is not synchronized in any way, so the reader thread and writer thread
				must be held off by the client during this operation.
	@result		Returns noErr if the call succeeds.
*/
CM_EXPORT
OSStatus CMSimpleQueueReset(
	CMSimpleQueueRef CM_NONNULL queue) 	/*! @param queue
											The queue to reset. Must not be NULL. */
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@function	CMSimpleQueueGetCapacity
    @abstract	Returns the number of elements that can be held in the queue.
	@result		The number of elements that can be held in the queue.  Returns
				0 if there is an error.
*/
CM_EXPORT
int32_t CMSimpleQueueGetCapacity(
	CMSimpleQueueRef CM_NONNULL queue) 	/*! @param queue
											The queue being interrogated. Must not be NULL. */
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@function	CMSimpleQueueGetCount
    @abstract	Returns the number of elements currently on the queue.
	@result		The number of elements currently in the queue. Returns 0 if there is an error.
*/
CM_EXPORT
int32_t CMSimpleQueueGetCount(
	CMSimpleQueueRef CM_NONNULL queue) 	/*! @param queue
											The queue being interrogated. Must not be NULL. */
		__OSX_AVAILABLE_STARTING(__MAC_10_7, __IPHONE_5_0);

/*!
	@define		CMSimpleQueueGetFullness
	A convenience macro that returns GetCount/GetCapacity, computed in floating point.  0.0 is empty, 0.5 is half full, 1.0 is full.
	Returns 0.0 if there is an error (eg. if queue is NULL).
*/
#define CMSimpleQueueGetFullness(queue) ( CMSimpleQueueGetCapacity(queue) ? \
											( ((Float32)CMSimpleQueueGetCount(queue)) / ((Float32)CMSimpleQueueGetCapacity(queue)) ) \
											: 0.0f )

#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif // ! CMSIMPLEQUEUE_H
// ==========  CoreMedia.framework/Headers/CMFormatDescription.h
/*
    File:  CMFormatDescription.h

	Framework:  CoreMedia
 
    Copyright 2005-2015 Apple Inc. All rights reserved.

*/

#ifndef CMFORMATDESCRIPTION_H
#define CMFORMATDESCRIPTION_H

/*!
	@header
	@abstract	API for creating and manipulating CMFormatDescriptions.
	@discussion	CMFormatDescriptions are immutable CF objects that are used to describe media data of various types, including
				audio, video, and muxed media data. There are two types of APIs in this header, media-type-agnostic APIs
				(supported by all CMFormatDescriptions) and media-type-specific APIs.  The media-type-agnostic APIs are
				prefixed with CMFormatDescription, and the media-type-specific APIs are prefixed with CMAudioFormatDescription,
				CMVideoFormatDescription, etc.
*/

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTime.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreAudio/CoreAudioTypes.h>
#include <AudioToolbox/AudioFormat.h>
#include <CoreGraphics/CGBase.h>
#include <CoreGraphics/CGGeometry.h>
#include <CoreVideo/CoreVideo.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

#pragma mark CMFormatDescription

/*!
	@enum CMFormatDescription Errors
	@discussion OSStatus errors returned by CMFormatDescription APIs.
	@constant	kCMFormatDescriptionError_InvalidParameter Invalid parameter.
	@constant	kCMFormatDescriptionError_AllocationFailed Returned when an allocation fails.
	@constant	kCMFormatDescriptionError_ValueNotAvailable Returned when the CMFormatDescription does not carry such a value.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMFormatDescriptionError_InvalidParameter		= -12710,
	kCMFormatDescriptionError_AllocationFailed		= -12711,
	kCMFormatDescriptionError_ValueNotAvailable		= -12718,
};

/*!
	@typedef	CMFormatDescriptionRef
	@abstract	A reference to a CMFormatDescription, a CF object describing media of a particular type (audio, video, muxed, etc).
*/
typedef const struct CM_BRIDGED_TYPE(id) opaqueCMFormatDescription *CMFormatDescriptionRef;

/*!
	@enum CMMediaType
	@abstract The type of media described by a CMFormatDescription.
	@constant kCMMediaType_Video Video media
	@constant kCMMediaType_Audio Audio media
	@constant kCMMediaType_Muxed Muxed media
	@constant kCMMediaType_Text Text media
	@constant kCMMediaType_ClosedCaption Closed-caption media
	@constant kCMMediaType_Subtitle Subtitle media
	@constant kCMMediaType_TimeCode TimeCode media
	@constant kCMMediaType_Metadata Metadata media
*/
typedef FourCharCode CMMediaType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMMediaType
#else
enum
#endif
{
	kCMMediaType_Video				= 'vide',
	kCMMediaType_Audio				= 'soun',
	kCMMediaType_Muxed				= 'muxx',
	kCMMediaType_Text				= 'text',
	kCMMediaType_ClosedCaption		= 'clcp',
	kCMMediaType_Subtitle			= 'sbtl',
	kCMMediaType_TimeCode			= 'tmcd',
	kCMMediaType_Metadata			= 'meta'
};

/*! 
	@functiongroup	Media-type-agnostic functions
*/

/*!
	@function	CMFormatDescriptionCreate
    @abstract   Creates a generic CMFormatDescription object.
    @discussion Use this call to create any CMFormatDescription that is composed solely of extensions, and for which 
				CFEqual() of a the extensions dictionaries is a valid test for Format Description equality.  Note that
				for some media types using this routine may result in creating a format description that is not fully
				specified for the purpose of media processing. Whenever possible, use media-specific format description
				creations routines such as CMVideoFormatDescriptionCreate, CMAudioFormatDescriptionCreate, etc.
    @result     A new CMFormatDescription object.
*/
CM_EXPORT OSStatus 
CMFormatDescriptionCreate(
	CFAllocatorRef CM_NULLABLE allocator,						/*! @param allocator
																	Allocator to use when creating the CMFormatDescription. If NULL, the default
																	allocator will be used. */
	CMMediaType mediaType,										/*! @param mediaType
																	Four character code identifying the type of media associated with the CMFormatDescription. */
	FourCharCode mediaSubtype,									/*! @param mediaSubtype
																	Four character code identifying the sub-type of media. */
	CFDictionaryRef CM_NULLABLE extensions,						/*! @param extensions
																	Dictionary of extensions to be attached to the CMFormatDescription. May be NULL. */
	CM_RETURNS_RETAINED_PARAMETER CMFormatDescriptionRef CM_NULLABLE * CM_NONNULL descOut)	/*! @param descOut
																	Receives the newly-created CMFormatDescription. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMFormatDescriptionGetTypeID
	@abstract	Returns the CFTypeID of CMFormatDescription objects.
	@discussion	You can check if a CFTypeRef object is actually a CMFormatDescription
				by comparing CFGetTypeID(object) with CMFormatDescriptionGetTypeID().
*/
CM_EXPORT
CFTypeID CMFormatDescriptionGetTypeID(void)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMFormatDescriptionEqual
	@abstract	Compares two CMFormatDescription objects for equality.
	@discussion	This calls CFEqual on the provided CMFormatDescription objects.
                In contrast to the CF call it is NULL safe.
*/
CM_EXPORT
Boolean CMFormatDescriptionEqual(
	CMFormatDescriptionRef CM_NULLABLE desc1,	/*! @param desc1
									The first formatDescription. */
	CMFormatDescriptionRef CM_NULLABLE desc2)	/*! @param desc2
									The second formatDescription. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMFormatDescriptionEqualIgnoringExtensionKeys
	@abstract	Compares two CMFormatDescription objects for equality, ignoring differences in specified lists of format description extension keys and sample description extension keys.
	@discussion
		This function is NULL safe.
		If any keys are passed, kCMFormatDescriptionExtension_VerbatimSampleDescription
		and kCMFormatDescriptionExtension_VerbatimISOSampleEntry will also be automatically
		ignored for the purpose of comparison.
	@param formatDescriptionExtensionKeysToIgnore
		Either a single format description extension key (CFString) 
		or a CFArray of such keys.  
	@param sampleDescriptionExtensionAtomKeysToIgnore
		Either a single sample description extension atom key (four-character CFString) 
		or a CFArray of such keys.  
		See kCMFormatDescriptionExtension_SampleDescriptionExtensionAtoms.
*/
CM_EXPORT
Boolean CMFormatDescriptionEqualIgnoringExtensionKeys(
	CMFormatDescriptionRef CM_NULLABLE desc1,
	CMFormatDescriptionRef CM_NULLABLE desc2,
	CFTypeRef CM_NULLABLE formatDescriptionExtensionKeysToIgnore,
	CFTypeRef CM_NULLABLE sampleDescriptionExtensionAtomKeysToIgnore )
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);

/*!
	@function	CMFormatDescriptionGetMediaType
	@abstract	Returns the media type of a CMFormatDescription.
	@discussion	For example, returns kCMMediaType_Audio for a description of an audio stream.
	@result		The media type of the CMFormatDescription.
*/
CM_EXPORT
CMMediaType CMFormatDescriptionGetMediaType(
	CMFormatDescriptionRef CM_NONNULL desc)	/*! @param desc CMFormatDescription being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMFormatDescriptionGetMediaSubType
	@abstract	Returns the media subtype of a CMFormatDescription.
	@discussion	The media subtype is defined in a media-specific way.
				For audio streams, the media subtype is the asbd.mFormatID.
				For video streams, the media subtype is the video codec type. 
				For muxed streams, it is the format of the muxed stream.
				For example, 'aac ' is returned for a description of an AAC audio
				stream, 'avc1' is returned for a description of an H.264 video
				stream, and 'mp2t' is returned for a description of an MPEG-2
				transport (muxed) stream.  If a particular type of media stream
				does not have subtypes, this API may return 0.
	@result		The media subtype of the CMFormatDescription.
*/
CM_EXPORT
FourCharCode CMFormatDescriptionGetMediaSubType(
	CMFormatDescriptionRef CM_NONNULL desc)	/*! @param desc CMFormatDescription being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMFormatDescriptionGetExtensions
	@abstract	Returns an immutable dictionary containing all the extensions of a CMFormatDescription.
	@discussion If there are no extensions, NULL is returned. Extensions dictionaries are valid property list
				objects.  This means that dictionary keys are all CFStrings, and the values are all either
				CFNumber, CFString, CFBoolean, CFArray, CFDictionary, CFDate, or CFData. The returned
				dictionary is not retained by this call, so clients are required to retain it if they
				need to keep it longer.
	@result		An immutable dictionary containing all the extensions of the CMFormatDescription.  May be NULL.
*/
CM_EXPORT
CFDictionaryRef CM_NULLABLE CMFormatDescriptionGetExtensions(
	CMFormatDescriptionRef CM_NONNULL desc)	/*! @param desc CMFormatDescription being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_BEGIN

/*!
	@define 	kCMFormatDescriptionExtension_OriginalCompressionSettings
	@abstract	This extension contains a media-type-specific dictionary of settings used to produce a compressed media buffer.
	@discussion This extension is valid for format descriptions of all media types, but the contents of the dictionary are defined
				in a media-specific way.  The dictionary and its contents are valid property list objects. This means that
				dictionary keys are all CFStrings, and the values are all either CFNumber, CFString, CFBoolean, CFArray,
				CFDictionary, CFDate, or CFData.
*/
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_OriginalCompressionSettings	// CFDictionary
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@define 	kCMFormatDescriptionExtension_SampleDescriptionExtensionAtoms
	@abstract	Sample description extension atoms that were not translated into other entries in the extensions dictionary.
	@discussion	This key is used by sample description bridges to hold sample description
				extension atoms that they do not recognize.
				The extension is a CFDictionary mapping CFStrings of the four-char-code atom types
				to either CFDatas containing the atom payload or (to represent multiple atoms of a
				specific type) to CFArrays of CFData containing those payloads.
*/
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_SampleDescriptionExtensionAtoms	// CFDictionary of CFString (four-char-code, atom type) -> ( CFData (atom payload) or CFArray of CFData (atom payload) )
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@define 	kCMFormatDescriptionExtension_VerbatimSampleDescription
	@abstract	Preserves the original SampleDescription data.
	@discussion This extension is used to ensure that roundtrips from sample descriptions
				to CMFormatDescriptions back to sample descriptions preserve the exact original
				sample descriptions.
				IMPORTANT: If you make a modified clone of a CMFormatDescription, you must 
				delete this extension from the clone, or your modifications could be lost.
*/
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_VerbatimSampleDescription		// CFData
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@define 	kCMFormatDescriptionExtension_VerbatimISOSampleEntry
	@abstract	Preserves the original ISOSampleEntry data.
	@discussion This extension is used to ensure that roundtrips from ISO Sample Entry (ie. AudioSampleEntry or VisualSampleEntry)
				to CMFormatDescriptions back to ISO Sample Entry preserve the exact original
				sample descriptions.
				IMPORTANT: If you make a modified clone of a CMFormatDescription, you must 
				delete this extension from the clone, or your modifications could be lost.
*/
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_VerbatimISOSampleEntry		// CFData
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CM_ASSUME_NONNULL_END

/*!
	@function	CMFormatDescriptionGetExtension
	@abstract	Returns the specified extension of a CMFormatDescription.
	@discussion If the named extension does not exist, NULL is returned. The extension is always a valid
				property list object. This means that it will be either a CFNumber, CFString, CFBoolean,
				CFArray, CFDictionary, CFDate, or CFData. If it is a CFDictionary, the keys will all be
				CFStrings. The returned extension is not retained by this call, so it is only valid as
				long as the CMFormatDescription is valid. Clients are required to retain it if they
				need to keep it longer.
	@result		The specified extension of the CMFormatDescription.  May be NULL.
*/
CM_EXPORT
CFPropertyListRef CM_NULLABLE CMFormatDescriptionGetExtension(
	CMFormatDescriptionRef CM_NONNULL desc,	/*! @param desc				CMFormatDescription being interrogated */
	CFStringRef CM_NONNULL extensionKey)		/*! @param extensionID		Key of extension to be returned. Cannot be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

				
#pragma mark CMAudioFormatDescription

/*! 
	@functiongroup	Audio-specific functions
*/

/*!
	@enum CMAudioCodecType
	@discussion Four-character codes identifying the code type. Certain codec types are also audio formats.
	@constant	kCMAudioCodecType_AAC_LCProtected iTMS protected low-complexity AAC.
	@constant	kCMAudioCodecType_AAC_AudibleProtected Audible's protected AAC.
*/
typedef FourCharCode CMAudioCodecType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMAudioCodecType
#else
enum
#endif
{
    kCMAudioCodecType_AAC_LCProtected      = 'paac',
	kCMAudioCodecType_AAC_AudibleProtected = 'aaac'
};

/*!
	@typedef CMAudioFormatDescriptionRef
	SYnonym type used for manipulating audio CMFormatDescriptions
*/
typedef CMFormatDescriptionRef CMAudioFormatDescriptionRef;

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMAudioFormatDescriptionCreate
	@abstract	Creates a format description for an audio media stream.
	@discussion	The ASBD is required, the channel layout is optional, and the magic cookie is required
				for some compression formats (and must be NULL for all others). The caller owns the
				returned CMFormatDescription, and must release it when done with it.  The ASBD,
				magic cookie, channel layout, and extensions are all copied (the extensions are
				deep-copied).  The caller can deallocate them or re-use them after making this call.
*/
CM_EXPORT
OSStatus CMAudioFormatDescriptionCreate(
	CFAllocatorRef CM_NULLABLE allocator,								/*! @param allocator		CFAllocator to be used. Pass kCFAllocatorDefault or NULL to use the default allocator. */
	const AudioStreamBasicDescription * CM_NONNULL asbd,				/*! @param asbd				Audio format description (see CoreAudioTypes.h). This information is required. */
	size_t layoutSize,													/*! @param layoutSize		Size, in bytes, of audio channel layout. 0 if layout is NULL. */
	const AudioChannelLayout * CM_NULLABLE layout,						/*! @param layout			Audio channel layout (see CoreAudioTypes.h). Can be NULL. */
	size_t magicCookieSize,												/*! @param magicCookieSize	Size, in bytes, of magic cookie. 0 if magicCookie is NULL. */
	const void * CM_NULLABLE magicCookie,								/*! @param magicCookie		Magic cookie. This information is required for some formats, and must be NULL for all others. */
	CFDictionaryRef CM_NULLABLE extensions,								/*! @param extensions		Dictionary of extension key/value pairs.  Keys are always CFStrings.
																			Values are always property list objects (ie. CFData, CFString, CFArray, CFDictionary,
																			CFDate, CFBoolean, or CFNumber). Can be NULL. */
	CM_RETURNS_RETAINED_PARAMETER CMAudioFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)		/*! @param outDesc			Returned newly created audio CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMAudioFormatDescriptionGetStreamBasicDescription
	@abstract	Returns a read-only pointer to the AudioStreamBasicDescription inside an audio CMFormatDescription.
	@discussion	See CoreAudioTypes.h for the definition of AudioStreamBasicDescription.
				This API is specific to audio format descriptions, and will return NULL if
				used with a non-audio format descriptions.
*/
CM_EXPORT
const AudioStreamBasicDescription * CM_NULLABLE CMAudioFormatDescriptionGetStreamBasicDescription(
	CMAudioFormatDescriptionRef CM_NONNULL desc)		/*! @param desc		CMFormatDescription being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMAudioFormatDescriptionGetMagicCookie
	@abstract	Returns a read-only pointer to (and size of) the magic cookie inside an audio CMFormatDescription.
	@discussion	The magic cookie is a completely opaque piece of data, written and read only by
				the codec itself. A magic cookie is only present for codecs that require it;
				this API will return NULL if one does not exist. This API is specific to audio
				format descriptions, and will return NULL if called with a non-audio format
				description.
	@result		A read-only pointer to the magic cookie inside the audio format description.
*/
CM_EXPORT
const void * CM_NULLABLE CMAudioFormatDescriptionGetMagicCookie(
	CMAudioFormatDescriptionRef CM_NONNULL desc,		/*! @param desc				CMFormatDescription being interrogated. */
	size_t * CM_NULLABLE cookieSizeOut)					/*! @param cookieSizeOut	Pointer to variable that will be written with the size of the cookie. Can be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMAudioFormatDescriptionGetChannelLayout
	@abstract	Returns a read-only pointer to (and size of) the AudioChannelLayout inside an audio CMFormatDescription.
	@discussion	See CoreAudioTypes.h for the definition of AudioChannelLayout.
				AudioChannelLayouts are optional; this API will return NULL if
				one does not exist. This API is specific to audio format
				descriptions, and will return NULL if called with a non-audio
				format description.
	@result		A read-only pointer to the AudioChannelLayout inside the audio format description.
*/
CM_EXPORT
const AudioChannelLayout * CM_NULLABLE CMAudioFormatDescriptionGetChannelLayout(
	CMAudioFormatDescriptionRef CM_NONNULL desc,		/*! @param desc			CMFormatDescription being interrogated. */
	size_t * CM_NULLABLE layoutSize)					/*! @param layoutSize	Pointer to variable that will be written with the size of the layout.
																	Can be NULL. */    
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMAudioFormatDescriptionGetFormatList
	@abstract	Returns a read-only pointer to (and size of) the array of AudioFormatListItem structs inside an audio CMFormatDescription.
	@discussion	This property is analogous to kAudioFormatProperty_FormatList (See AudioFormat.h) and follows
                its conventions.  Namely, formats are returned in order from the most to least 'rich', with 
                channel count taking the highest precedence followed by sample rate.
				This API is specific to audio format descriptions, and will return NULL if called with a non-audio
				format description.
	@result		A read-only pointer to the array of AudioFormatListItem structs inside the audio format description.
*/
CM_EXPORT
const AudioFormatListItem * CM_NULLABLE CMAudioFormatDescriptionGetFormatList(
	CMAudioFormatDescriptionRef CM_NONNULL desc,		/*! @param desc             CMFormatDescription being interrogated. */
	size_t * CM_NULLABLE formatListSize)	            /*! @param formatListSize	Pointer to variable that will be written with the size of the formatList.
                                                                        Can be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMAudioFormatDescriptionGetRichestDecodableFormat
	@abstract	Returns a read-only pointer to the appropriate AudioFormatListItem inside an audio CMFormatDescription.
	@discussion	This property performs validation on the formats represented by the audio in the description.  It
                finds the first AudioFormatListItem for which the current system has a valid decoder.
				This API is specific to audio format descriptions, and will return NULL if called with a non-audio
				format description.  It may also return NULL if there is no suitable decoder available on the
                current system for this audio format.
	@result		A read-only pointer to the appropriate AudioFormatListItem inside the audio format description.
*/
CM_EXPORT
const AudioFormatListItem * CM_NULLABLE CMAudioFormatDescriptionGetRichestDecodableFormat(
	CMAudioFormatDescriptionRef CM_NONNULL desc)	     /*! @param desc             CMFormatDescription being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@function	CMAudioFormatDescriptionGetMostCompatibleFormat
	@abstract	Returns a read-only pointer to the appropriate AudioFormatListItem inside an audio CMFormatDescription.
	@discussion	This property returns a pointer to the last AudioFormatListItem in the kAudioFormatProperty_FormatList
                (see AudioFormat.h).  This API is specific to audio format descriptions, and will return NULL if called 
                with a non-audio format description.
	@result		A read-only pointer to the appropriate AudioFormatListItem inside the audio format description.
*/
CM_EXPORT
const AudioFormatListItem * CM_NULLABLE CMAudioFormatDescriptionGetMostCompatibleFormat(
	CMAudioFormatDescriptionRef CM_NONNULL desc)	     /*! @param desc             CMFormatDescription being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMAudioFormatDescriptionCreateSummary
	@abstract	Creates a summary audio format description from an array of audio format descriptions.
	@discussion
		The summary format description will be canonical LPCM and deep enough in 
		sample rate, channel layout and channel count to sensibly contain the result of decoding 
		and mixing the constituent format descriptions.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCreateSummary(
		CFAllocatorRef CM_NULLABLE allocator,
		CFArrayRef CM_NONNULL formatDescriptionArray, // CFArray[CMAudioFormatDescription]
		uint32_t flags, // pass 0
		CM_RETURNS_RETAINED_PARAMETER CMAudioFormatDescriptionRef CM_NULLABLE * CM_NONNULL summaryFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@enum CMAudioFormatDescriptionMask
	@discussion Mask bits passed to (and returned from) CMAudioFormatDescriptionEqual,
				representing various parts of an audio format description.
	@constant	CMAudioFormatDescriptionMask_StreamBasicDescription	Represents the AudioStreamBasicDescription.
	@constant	CMAudioFormatDescriptionMask_MagicCookie				Represents the magic cookie.
	@constant	CMAudioFormatDescriptionMask_ChannelLayout				Represents the AudioChannelLayout.
	@constant	CMAudioFormatDescriptionMask_Extensions					Represents the format description extensions.
	@constant	CMAudioFormatDescriptionMask_All						Represents all the parts of an audio format description.
*/
typedef uint32_t CMAudioFormatDescriptionMask;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMAudioFormatDescriptionMask
#else
enum
#endif
{
	kCMAudioFormatDescriptionMask_StreamBasicDescription	= (1<<0),
	kCMAudioFormatDescriptionMask_MagicCookie				= (1<<1),
	kCMAudioFormatDescriptionMask_ChannelLayout				= (1<<2),
	kCMAudioFormatDescriptionMask_Extensions				= (1<<3),
	kCMAudioFormatDescriptionMask_All						= kCMAudioFormatDescriptionMask_StreamBasicDescription
															| kCMAudioFormatDescriptionMask_MagicCookie
															| kCMAudioFormatDescriptionMask_ChannelLayout
															| kCMAudioFormatDescriptionMask_Extensions
};

/*!
	@function	CMAudioFormatDescriptionEqual
	@abstract	Evaluates equality for the specified parts of two audio format descriptions.
	@discussion	Bits in equalityMask specify the caller's interest in the equality of various parts of the descriptions.
				Bits set and returned in equalityMaskOut represent the subset of those parts that are equal.
				If there is any sort of error that prevents the comparison from occurring, false will be returned, and
				all bits in equalityMaskOut will be cleared. If you pass kCMAudioFormatDescriptionMask_All in equalityMask,
				and NULL for equalityMaskOut, this API is equivalent to CFEqual(desc1, desc2).
	@result		The result of the comparison.  True if all parts in which the caller is interested are equal.
				False if any of the parts in which the caller is interested are not equal.
*/
CM_EXPORT
Boolean CMAudioFormatDescriptionEqual(
	CMAudioFormatDescriptionRef CM_NONNULL desc1,				/*! @param desc1			The CMAudioFormatDescription being compared. */
	CMAudioFormatDescriptionRef CM_NONNULL desc2,				/*! @param desc2			The CMAudioFormatDescription to which it is being compared. */
	CMAudioFormatDescriptionMask equalityMask,					/*! @param equalityMask		Mask specifying which parts of the descriptions to compare. */
	CMAudioFormatDescriptionMask * CM_NULLABLE equalityMaskOut)	/*! @param equalityMaskOut  Pointer to variable that will be written with the results by part.
																				Bits not set in equalityMask will not be set in equalityMaskOut.
																				Can be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#pragma mark CMVideoFormatDescription

/*! 
	@functiongroup	Video-specific functions
*/

/*!
	@typedef CMVideoFormatDescriptionRef
	Synonym type used for manipulating video CMFormatDescriptions
*/
typedef CMFormatDescriptionRef CMVideoFormatDescriptionRef;

/*!
	@enum CMPixelFormatType
	@discussion Four-character codes identifying the pixel format. Only some codec types are pixel formats.
		In general, CoreVideo CVPixelFormatType constants may be used too.
	@constant	kCMPixelFormat_32ARGB 32-bit ARGB
	@constant	kCMPixelFormat_32BGRA 32-bit BGRA
	@constant	kCMPixelFormat_24RGB 24-bit RGB
	@constant	kCMPixelFormat_16BE555 16-bit big-endian 5-5-5
	@constant	kCMPixelFormat_16BE565 16-bit big-endian 5-6-5
	@constant	kCMPixelFormat_16LE555 16-bit little-endian 5-5-5
	@constant	kCMPixelFormat_16LE565 16-bit little-endian 5-6-5
	@constant	kCMPixelFormat_16LE5551 16-bit little-endian 5-5-5-1
	@constant	kCMPixelFormat_422YpCbCr8 Component Y'CbCr 8-bit 4:2:2 ordered Cb Y'0 Cr Y'1
	@constant	kCMPixelFormat_422YpCbCr8_yuvs Component Y'CbCr 8-bit 4:2:2 ordered Y'0 Cb Y'1 Cr
	@constant	kCMPixelFormat_444YpCbCr8 Component Y'CbCr 8-bit 4:4:4
	@constant	kCMPixelFormat_4444YpCbCrA8 Component Y'CbCrA 8-bit 4:4:4:4
	@constant	kCMPixelFormat_422YpCbCr16 Component Y'CbCr 10,12,14,16-bit 4:2:2
	@constant	kCMPixelFormat_422YpCbCr10 Component Y'CbCr 10-bit 4:2:2
	@constant	kCMPixelFormat_444YpCbCr10 Component Y'CbCr 10-bit 4:4:4
	@constant	kCMPixelFormat_8IndexedGray_WhiteIsZero 8 bit indexed gray, white is zero
*/
typedef FourCharCode CMPixelFormatType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMPixelFormatType
#else
enum
#endif
{
	kCMPixelFormat_32ARGB                   = 32,
	kCMPixelFormat_32BGRA                   = 'BGRA',
	kCMPixelFormat_24RGB                    = 24,
	kCMPixelFormat_16BE555                  = 16,
	kCMPixelFormat_16BE565                  = 'B565',
	kCMPixelFormat_16LE555                  = 'L555',
	kCMPixelFormat_16LE565                  = 'L565',
	kCMPixelFormat_16LE5551                 = '5551',
	kCMPixelFormat_422YpCbCr8               = '2vuy',
	kCMPixelFormat_422YpCbCr8_yuvs          = 'yuvs',
	kCMPixelFormat_444YpCbCr8               = 'v308',
	kCMPixelFormat_4444YpCbCrA8             = 'v408',
	kCMPixelFormat_422YpCbCr16              = 'v216',
	kCMPixelFormat_422YpCbCr10              = 'v210',
	kCMPixelFormat_444YpCbCr10              = 'v410',
	kCMPixelFormat_8IndexedGray_WhiteIsZero = 0x00000028,
};

/*!
	@enum CMVideoCodecType
	@discussion Four-character codes identifying the video codec. Certain codec types are also pixel formats.
				  Note: There is no kCMVideoCodecType_Raw -- use the appropriate pixel format type as the codec type.
	@constant	kCMVideoCodecType_422YpCbCr8	Component Y'CbCr 8-bit 4:2:2 ordered Cb Y'0 Cr Y'1
	@constant	kCMVideoCodecType_Animation		Apple Animation format
	@constant	kCMVideoCodecType_Cinepak	Cinepak format
	@constant	kCMVideoCodecType_JPEG	Joint Photographic Experts Group (JPEG) format
	@constant	kCMVideoCodecType_JPEG_OpenDML	JPEG format with Open-DML extensions
	@constant	kCMVideoCodecType_SorensonVideo		Sorenson video format
	@constant	kCMVideoCodecType_SorensonVideo3	Sorenson 3 video format
	@constant	kCMVideoCodecType_H263	ITU-T H.263 format
	@constant	kCMVideoCodecType_H264	ITU-T H.264 format (AKA ISO/IEC 14496-10 - MPEG-4 Part 10, Advanced Video Coding format)
	@constant	kCMVideoCodecType_HEVC	ITU-T HEVC format
	@constant	kCMVideoCodecType_MPEG4Video	ISO/IEC Moving Picture Experts Group (MPEG) MPEG-4 Part 2 video format
	@constant	kCMVideoCodecType_MPEG2Video	MPEG-2 video format
	@constant	kCMVideoCodecType_MPEG1Video	MPEG-1 video format
	@constant	kCMVideoCodecType_DVCNTSC	DV NTSC format
	@constant	kCMVideoCodecType_DVCPAL	DV PAL format
	@constant	kCMVideoCodecType_DVCProPAL		Panasonic DVCPro PAL format
	@constant	kCMVideoCodecType_DVCPro50NTSC	Panasonic DVCPro-50 NTSC format
	@constant	kCMVideoCodecType_DVCPro50PAL	Panasonic DVCPro-50 PAL format
	@constant	kCMVideoCodecType_DVCPROHD720p60	Panasonic DVCPro-HD 720p60 format
	@constant	kCMVideoCodecType_DVCPROHD720p50	Panasonic DVCPro-HD 720p50 format
	@constant	kCMVideoCodecType_DVCPROHD1080i60	Panasonic DVCPro-HD 1080i60 format
	@constant	kCMVideoCodecType_DVCPROHD1080i50	Panasonic DVCPro-HD 1080i50 format
	@constant	kCMVideoCodecType_DVCPROHD1080p30	Panasonic DVCPro-HD 1080p30 format
	@constant	kCMVideoCodecType_DVCPROHD1080p25	Panasonic DVCPro-HD 1080p25 format
	@constant	kCMVideoCodecType_AppleProRes4444	Apple ProRes 4444 format
	@constant	kCMVideoCodecType_AppleProRes422HQ	Apple ProRes 422 HQ format
	@constant	kCMVideoCodecType_AppleProRes422	Apple ProRes 422 format
	@constant	kCMVideoCodecType_AppleProRes422LT	Apple ProRes 422 LT format
	@constant	kCMVideoCodecType_AppleProRes422Proxy	Apple ProRes 422 Proxy format
*/
typedef FourCharCode CMVideoCodecType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMVideoCodecType
#else
enum
#endif
{
	kCMVideoCodecType_422YpCbCr8       = kCMPixelFormat_422YpCbCr8,
	kCMVideoCodecType_Animation        = 'rle ',
	kCMVideoCodecType_Cinepak          = 'cvid',
	kCMVideoCodecType_JPEG             = 'jpeg',
	kCMVideoCodecType_JPEG_OpenDML     = 'dmb1',
	kCMVideoCodecType_SorensonVideo    = 'SVQ1',
	kCMVideoCodecType_SorensonVideo3   = 'SVQ3',
	kCMVideoCodecType_H263             = 'h263',
	kCMVideoCodecType_H264             = 'avc1',
	kCMVideoCodecType_HEVC             = 'hvc1',
	kCMVideoCodecType_MPEG4Video       = 'mp4v',
	kCMVideoCodecType_MPEG2Video       = 'mp2v',
	kCMVideoCodecType_MPEG1Video       = 'mp1v',

	kCMVideoCodecType_DVCNTSC          = 'dvc ',
	kCMVideoCodecType_DVCPAL           = 'dvcp',
	kCMVideoCodecType_DVCProPAL        = 'dvpp',
	kCMVideoCodecType_DVCPro50NTSC     = 'dv5n',
	kCMVideoCodecType_DVCPro50PAL      = 'dv5p',
	kCMVideoCodecType_DVCPROHD720p60   = 'dvhp',
	kCMVideoCodecType_DVCPROHD720p50   = 'dvhq',
	kCMVideoCodecType_DVCPROHD1080i60  = 'dvh6',
	kCMVideoCodecType_DVCPROHD1080i50  = 'dvh5',
	kCMVideoCodecType_DVCPROHD1080p30  = 'dvh3',
	kCMVideoCodecType_DVCPROHD1080p25  = 'dvh2',
	
	kCMVideoCodecType_AppleProRes4444  = 'ap4h',
	kCMVideoCodecType_AppleProRes422HQ = 'apch',
	kCMVideoCodecType_AppleProRes422   = 'apcn',
	kCMVideoCodecType_AppleProRes422LT = 'apcs',
	kCMVideoCodecType_AppleProRes422Proxy = 'apco',
};

/*!
	@typedef CMVideoDimensions
	Type used for video dimensions, units are pixels
*/
typedef struct {
	int32_t width;
	int32_t height;
} CMVideoDimensions;

CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_FormatName	// CFString
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_Depth			// CFNumber with depth value as directed by http://developer.apple.com/qa/qa2001/qa1183.html
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

// Many of the following extension keys and values are the same as the corresponding CVImageBuffer attachment keys and values
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_CleanAperture __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureWidth __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureHeight __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureHorizontalOffset __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureVerticalOffset __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_CleanAperture				kCVImageBufferCleanApertureKey					// CFDictionary containing the following four keys
#define kCMFormatDescriptionKey_CleanApertureWidth				kCVImageBufferCleanApertureWidthKey				// CFNumber
#define kCMFormatDescriptionKey_CleanApertureHeight				kCVImageBufferCleanApertureHeightKey			// CFNumber
#define kCMFormatDescriptionKey_CleanApertureHorizontalOffset	kCVImageBufferCleanApertureHorizontalOffsetKey	// CFNumber
#define kCMFormatDescriptionKey_CleanApertureVerticalOffset		kCVImageBufferCleanApertureVerticalOffsetKey	// CFNumber

// These additional keys are used to record the precise numerator and denominator in cases where the number is not an integer.
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureWidthRational									// CFArray of 2 CFNumbers: numerator, denominator
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureHeightRational									// CFArray of 2 CFNumbers: numerator, denominator
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureHorizontalOffsetRational						// CFArray of 2 CFNumbers: numerator, denominator
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_CleanApertureVerticalOffsetRational							// CFArray of 2 CFNumbers: numerator, denominator
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_FieldCount __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_FieldCount				kCVImageBufferFieldCountKey						// CFNumber, 1 or 2

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_FieldDetail __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionFieldDetail_TemporalTopFirst __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionFieldDetail_TemporalBottomFirst __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionFieldDetail_SpatialFirstLineEarly __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionFieldDetail_SpatialFirstLineLate __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_FieldDetail				kCVImageBufferFieldDetailKey					// CFString with one of the following four values
#define kCMFormatDescriptionFieldDetail_TemporalTopFirst		kCVImageBufferFieldDetailTemporalTopFirst
#define kCMFormatDescriptionFieldDetail_TemporalBottomFirst		kCVImageBufferFieldDetailTemporalBottomFirst
#define kCMFormatDescriptionFieldDetail_SpatialFirstLineEarly	kCVImageBufferFieldDetailSpatialFirstLineEarly
#define kCMFormatDescriptionFieldDetail_SpatialFirstLineLate	kCVImageBufferFieldDetailSpatialFirstLineLate

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_PixelAspectRatio __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_PixelAspectRatioHorizontalSpacing __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionKey_PixelAspectRatioVerticalSpacing __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_PixelAspectRatio			kCVImageBufferPixelAspectRatioKey				// CFDictionary with the following two keys
#define kCMFormatDescriptionKey_PixelAspectRatioHorizontalSpacing	kCVImageBufferPixelAspectRatioHorizontalSpacingKey	// CFNumber
#define kCMFormatDescriptionKey_PixelAspectRatioVerticalSpacing	kCVImageBufferPixelAspectRatioVerticalSpacingKey	// CFNumber

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_ColorPrimaries __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionColorPrimaries_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionColorPrimaries_EBU_3213 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionColorPrimaries_SMPTE_C __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_ColorPrimaries			kCVImageBufferColorPrimariesKey					// CFString describing the color primaries. This key can be one of the following values:
#define kCMFormatDescriptionColorPrimaries_ITU_R_709_2			kCVImageBufferColorPrimaries_ITU_R_709_2		// CFString
#define kCMFormatDescriptionColorPrimaries_EBU_3213				kCVImageBufferColorPrimaries_EBU_3213			// CFString
#define kCMFormatDescriptionColorPrimaries_SMPTE_C				kCVImageBufferColorPrimaries_SMPTE_C			// CFString
CM_EXPORT const CFStringRef kCMFormatDescriptionColorPrimaries_DCI_P3											// same as kCVImageBufferColorPrimaries_DCI_P3
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionColorPrimaries_P3_D65											// same as kCVImageBufferColorPrimaries_P3_D65
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionColorPrimaries_ITU_R_2020										// same as kCVImageBufferColorPrimaries_ITU_R_2020
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionColorPrimaries_P22												// same as kCVImageBufferColorPrimaries_P22
							__OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_6_0);

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_TransferFunction __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionTransferFunction_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionTransferFunction_SMPTE_240M_1995 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionTransferFunction_UseGamma __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_TransferFunction			kCVImageBufferTransferFunctionKey				// CFString describing the transfer function. This key can be one of the following values:
#define kCMFormatDescriptionTransferFunction_ITU_R_709_2		kCVImageBufferTransferFunction_ITU_R_709_2		// CFString
#define kCMFormatDescriptionTransferFunction_SMPTE_240M_1995	kCVImageBufferTransferFunction_SMPTE_240M_1995	// CFString
#define kCMFormatDescriptionTransferFunction_UseGamma			kCVImageBufferTransferFunction_UseGamma			// CFString
CM_EXPORT const CFStringRef kCMFormatDescriptionTransferFunction_ITU_R_2020										// same as kCVImageBufferTransferFunction_ITU_R_2020
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_GammaLevel __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_GammaLevel				kCVImageBufferGammaLevelKey						// CFNumber describing the gamma level, used in absence of (or ignorance of) kCMFormatDescriptionExtension_TransferFunction

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_YCbCrMatrix __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionYCbCrMatrix_ITU_R_709_2 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionYCbCrMatrix_ITU_R_601_4 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionYCbCrMatrix_SMPTE_240M_1995 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_YCbCrMatrix				kCVImageBufferYCbCrMatrixKey					// CFString describing the color matrix for YCbCr->RGB. This key can be one of the following values:
#define kCMFormatDescriptionYCbCrMatrix_ITU_R_709_2				kCVImageBufferYCbCrMatrix_ITU_R_709_2			// CFString
#define kCMFormatDescriptionYCbCrMatrix_ITU_R_601_4				kCVImageBufferYCbCrMatrix_ITU_R_601_4			// CFString
#define kCMFormatDescriptionYCbCrMatrix_SMPTE_240M_1995			kCVImageBufferYCbCrMatrix_SMPTE_240M_1995		// CFString
CM_EXPORT const CFStringRef kCMFormatDescriptionYCbCrMatrix_DCI_P3												// same as kCVImageBufferYCbCrMatrix_DCI_P3
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionYCbCrMatrix_P3_D65												// same as kCVImageBufferYCbCrMatrix_P3_D65
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionYCbCrMatrix_ITU_R_2020											// same as kCVImageBufferYCbCrMatrix_ITU_R_2020
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_FullRangeVideo										// CFBoolean; by default, false for YCbCr-based compressed formats, indicating that pixel values are video-range rather than full-range
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_ICCProfile											// CFData
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_BytesPerRow											// CFNumber describing the bytes per row of raster pixel data (not used for compressed, planar, tiled or downsampled formats)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/* Chroma siting information. For progressive images, only the TopField value is used. */
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_ChromaLocationTopField __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_ChromaLocationBottomField __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionChromaLocation_Left __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionChromaLocation_Center __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionChromaLocation_TopLeft __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionChromaLocation_Top __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionChromaLocation_BottomLeft __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionChromaLocation_Bottom __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionChromaLocation_DV420 __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_ChromaLocationTopField		kCVImageBufferChromaLocationTopFieldKey		// CFString with one of the following CFString values
#define kCMFormatDescriptionExtension_ChromaLocationBottomField 	kCVImageBufferChromaLocationBottomFieldKey	// CFString with one of the following CFString values
#define kCMFormatDescriptionChromaLocation_Left						kCVImageBufferChromaLocation_Left			// Chroma sample is horizontally co-sited with the left column of luma samples, but centered vertically.
#define kCMFormatDescriptionChromaLocation_Center					kCVImageBufferChromaLocation_Center			// Chroma sample is fully centered
#define kCMFormatDescriptionChromaLocation_TopLeft					kCVImageBufferChromaLocation_TopLeft		// Chroma sample is co-sited with the top-left luma sample.
#define kCMFormatDescriptionChromaLocation_Top						kCVImageBufferChromaLocation_Top			// Chroma sample is horizontally centered, but co-sited with the top row of luma samples.
#define kCMFormatDescriptionChromaLocation_BottomLeft				kCVImageBufferChromaLocation_BottomLeft		// Chroma sample is co-sited with the bottom-left luma sample.
#define kCMFormatDescriptionChromaLocation_Bottom					kCVImageBufferChromaLocation_Bottom			// Chroma sample is horizontally centered, but co-sited with the bottom row of luma samples.
#define kCMFormatDescriptionChromaLocation_DV420					kCVImageBufferChromaLocation_DV420			// Cr and Cb samples are alternately co-sited with the left luma samples of the same field.

/* MPEG-2-conformant formats */
CM_EXPORT const CFStringRef kCMFormatDescriptionConformsToMPEG2VideoProfile			// CFNumber specifying a kCMMPEG2VideoProfile_*
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : int32_t
#else
enum
#endif
{
	kCMMPEG2VideoProfile_HDV_720p30 =				'hdv1',
	kCMMPEG2VideoProfile_HDV_1080i60 =				'hdv2',
	kCMMPEG2VideoProfile_HDV_1080i50 =				'hdv3',
	kCMMPEG2VideoProfile_HDV_720p24 =				'hdv4',
	kCMMPEG2VideoProfile_HDV_720p25 =				'hdv5',
	kCMMPEG2VideoProfile_HDV_1080p24 =				'hdv6',
	kCMMPEG2VideoProfile_HDV_1080p25 =				'hdv7',
	kCMMPEG2VideoProfile_HDV_1080p30 =				'hdv8',
	kCMMPEG2VideoProfile_HDV_720p60 =				'hdv9',
	kCMMPEG2VideoProfile_HDV_720p50 =				'hdva',
	kCMMPEG2VideoProfile_XDCAM_HD_1080i60_VBR35 =	'xdv2',
	kCMMPEG2VideoProfile_XDCAM_HD_1080i50_VBR35 =	'xdv3',
	kCMMPEG2VideoProfile_XDCAM_HD_1080p24_VBR35 =	'xdv6',
	kCMMPEG2VideoProfile_XDCAM_HD_1080p25_VBR35 =	'xdv7',
	kCMMPEG2VideoProfile_XDCAM_HD_1080p30_VBR35 =	'xdv8',
	kCMMPEG2VideoProfile_XDCAM_EX_720p24_VBR35 =	'xdv4',
	kCMMPEG2VideoProfile_XDCAM_EX_720p25_VBR35 =	'xdv5',
	kCMMPEG2VideoProfile_XDCAM_EX_720p30_VBR35 =	'xdv1',
	kCMMPEG2VideoProfile_XDCAM_EX_720p50_VBR35 =	'xdva',
	kCMMPEG2VideoProfile_XDCAM_EX_720p60_VBR35 =	'xdv9',
	kCMMPEG2VideoProfile_XDCAM_EX_1080i60_VBR35 =	'xdvb',
	kCMMPEG2VideoProfile_XDCAM_EX_1080i50_VBR35 =	'xdvc',
	kCMMPEG2VideoProfile_XDCAM_EX_1080p24_VBR35 =	'xdvd',
	kCMMPEG2VideoProfile_XDCAM_EX_1080p25_VBR35 =	'xdve',
	kCMMPEG2VideoProfile_XDCAM_EX_1080p30_VBR35 =	'xdvf',
	kCMMPEG2VideoProfile_XDCAM_HD422_720p50_CBR50 =	'xd5a',
	kCMMPEG2VideoProfile_XDCAM_HD422_720p60_CBR50 =	'xd59',
	kCMMPEG2VideoProfile_XDCAM_HD422_1080i60_CBR50 =	'xd5b',
	kCMMPEG2VideoProfile_XDCAM_HD422_1080i50_CBR50 =	'xd5c',
	kCMMPEG2VideoProfile_XDCAM_HD422_1080p24_CBR50 =	'xd5d',
	kCMMPEG2VideoProfile_XDCAM_HD422_1080p25_CBR50 =	'xd5e',
	kCMMPEG2VideoProfile_XDCAM_HD422_1080p30_CBR50 =	'xd5f',
	kCMMPEG2VideoProfile_XDCAM_HD_540p =				'xdhd',
	kCMMPEG2VideoProfile_XDCAM_HD422_540p =			'xdh2',
	kCMMPEG2VideoProfile_XDCAM_HD422_720p24_CBR50 = 'xd54',
	kCMMPEG2VideoProfile_XDCAM_HD422_720p25_CBR50 = 'xd55',
	kCMMPEG2VideoProfile_XDCAM_HD422_720p30_CBR50 = 'xd51',
	kCMMPEG2VideoProfile_XF = 'xfz1',
};

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_TemporalQuality			// CFNumber
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_SpatialQuality			// CFNumber
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_VerbatimImageDescription __OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
#define kCMFormatDescriptionExtension_VerbatimImageDescription	kCMFormatDescriptionExtension_VerbatimSampleDescription

CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_Version					// CFNumber
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_RevisionLevel				// CFNumber
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMFormatDescriptionExtension_Vendor					// CFString of fourCC
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_EXPORT const CFStringRef kCMFormatDescriptionVendor_Apple
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMVideoFormatDescriptionCreate
	@abstract	Creates a format description for a video media stream.
	@discussion	The caller owns the returned CMFormatDescription, and must release it when done with it. All input parameters
				are copied (the extensions are deep-copied).  The caller can deallocate them or re-use them after making this call.
*/
CM_EXPORT
OSStatus CMVideoFormatDescriptionCreate(
	CFAllocatorRef CM_NULLABLE allocator,							/*! @param allocator	CFAllocator to be used. kCFAllocatorDefault used if NULL. */
	CMVideoCodecType codecType,										/*! @param codecType	The type of video compression. */
	int32_t width,													/*! @param width		The width of encoded video. */
	int32_t height,													/*! @param height		The height of encoded video. */
	CFDictionaryRef CM_NULLABLE extensions,							/*! @param extensions	Dictionary of extension key/value pairs. Keys are always CFStrings.
																		Values are always property list objects (ie. CFData, CFString, CFArray,
																		CFDictionary, CFDate, CFBoolean, or CFNumber). Can be NULL. */
	CM_RETURNS_RETAINED_PARAMETER CMVideoFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)	/*! @param outDesc		Returned newly created video CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMVideoFormatDescriptionCreateForImageBuffer
	@abstract	Creates a format description for a video media stream contained in CVImageBuffers of the type provided.
	@discussion	This convenience function is equivalent to:
	
				CMVideoFormatDescriptionCreate( allocator,
												 ( CVPixelBufferGetTypeID() == CFGetTypeID( imageBuffer ) ? CVPixelBufferGetPixelFormatType( imageBuffer ) : 0,
												 width of image,
												 height of image,
												 extensions );
				
				where extensions is a CFDictionary of attachments to image buffer with keys specified by 
				CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers, and also 
				kCMFormatDescriptionExtension_BytesPerRow if applicable.
*/
CM_EXPORT
OSStatus CMVideoFormatDescriptionCreateForImageBuffer(
	CFAllocatorRef CM_NULLABLE allocator,							/*! @param allocator
																		CFAllocator to be used when creating the CMFormatDescription. NULL will cause the default allocator to be used */
	CVImageBufferRef CM_NONNULL imageBuffer,						/*! @param imageBuffer
																		Image buffer for which we are creating the format description. */
	CM_RETURNS_RETAINED_PARAMETER CMVideoFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)	/*! @param outDesc
																		Returned newly-created video CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMVideoFormatDescriptionCreateFromH264ParameterSets
	@abstract	Creates a format description for a video media stream described by H.264 parameter set NAL units.
	@discussion	This function parses the dimensions provided by the parameter sets and creates a format description suitable for a raw H.264 stream.
				The parameter sets' data can come from raw NAL units and must have any emulation prevention bytes needed.
				The supported NAL unit types to be included in the format description are 7 (sequence parameter set), 8 (picture parameter set) and 13 (sequence parameter set extension). At least one sequence parameter set and one picture parameter set must be provided.
*/
CM_EXPORT
OSStatus CMVideoFormatDescriptionCreateFromH264ParameterSets(
	CFAllocatorRef CM_NULLABLE allocator,									/*! @param allocator
																				CFAllocator to be used when creating the CMFormatDescription. Pass NULL to use the default allocator. */
	 size_t parameterSetCount,												/*! @param parameterSetCount
																				The number of parameter sets to include in the format description. This parameter must be at least 2. */
	 const uint8_t * CM_NONNULL const * CM_NONNULL parameterSetPointers,	/*! @param parameterSetPointers
																				Points to a C array containing parameterSetCount pointers to parameter sets. */
	 const size_t * CM_NONNULL parameterSetSizes,							/*! @param parameterSetSizes
																				Points to a C array containing the size, in bytes, of each of the parameter sets. */
	 int NALUnitHeaderLength,												/*! @param NALUnitHeaderLength
																				Size, in bytes, of the NALUnitLength field in an AVC video sample or AVC parameter set sample. Pass 1, 2 or 4. */
	CM_RETURNS_RETAINED_PARAMETER CMFormatDescriptionRef CM_NULLABLE * CM_NONNULL formatDescriptionOut )	/*! @param formatDescriptionOut
																				Returned newly-created video CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_7_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMVideoFormatDescriptionGetH264ParameterSetAtIndex
	@abstract	Returns a parameter set contained in a H.264 format description.
	@discussion	This function parses the AVC decoder configuration record contained in a H.264 video format description and returns the parameter set NAL unit at the given index from it.
				Both parameterSetPointerOut and parameterSetSizeOut may be NULL, parameterSetCountOut will return the total number of parameter set NAL units contained in the AVC decoder configuration record.
				The parameter set NAL units returned will already have any emulation prevention bytes needed.
				The pointer returned in parameterSetPointerOut points to internal memory of videoDesc, and may only be accessed as long as a retain on videoDesc is held.
*/
CM_EXPORT
OSStatus CMVideoFormatDescriptionGetH264ParameterSetAtIndex(
		CMFormatDescriptionRef CM_NONNULL videoDesc,					/*! @param videoDesc
																			FormatDescription being interrogated. */
		size_t parameterSetIndex,										/*! @param parameterSetIndex
																			Index of the parameter set to be returned in parameterSetPointerOut and parameterSetSizeOut. This parameter is ignored if both parameterSetPointerOut and parameterSetSizeOut are NULL. */
		const uint8_t * CM_NULLABLE * CM_NULLABLE parameterSetPointerOut,	/*! @param parameterSetPointerOut
																			Points to a pointer to receive the parameter set. Pass NULL if you do not want this information. */
		size_t * CM_NULLABLE parameterSetSizeOut,						/*! @param parameterSetSizeOut
																			Points to a size_t to receive the size in bytes of the parameter set. Pass NULL if you do not want this information. */
		size_t * CM_NULLABLE parameterSetCountOut,						/*! @param parameterSetCountOut
																			Number of parameter sets in the AVC decoder configuration record contained in videoDesc. Pass NULL if you do not   want this information. */
		int * CM_NULLABLE NALUnitHeaderLengthOut )						/*! @param NALUnitHeaderLengthOut
																			Points to an int to receive the size, in bytes, of the NALUnitLength field in an AVC video sample or AVC parameter set sample. Pass NULL if you do not want this information. */
							__OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_7_0);

#define CMVideoFormatDescriptionGetCodecType(desc)  CMFormatDescriptionGetMediaSubType(desc)

/*!
	@function	CMVideoFormatDescriptionGetDimensions
	@abstract	Returns the dimensions (in encoded pixels)
	@discussion	This does not take into account pixel aspect ratio or clean aperture tags.
*/
CM_EXPORT
CMVideoDimensions CMVideoFormatDescriptionGetDimensions(
	CMVideoFormatDescriptionRef CM_NONNULL videoDesc)	/*! @param videoDesc
											FormatDescription being interrogated. */ 
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMVideoFormatDescriptionGetPresentationDimensions
	@abstract	Returns the dimensions, adjusted to take pixel aspect ratio and/or clean aperture into account.
	@discussion
		Pixel aspect ratio is used to adjust the width, leaving the height alone.
*/
CM_EXPORT
CGSize CMVideoFormatDescriptionGetPresentationDimensions(
		CMVideoFormatDescriptionRef CM_NONNULL videoDesc,		/*! @param videoDesc
																	FormatDescription being interrogated. */
		Boolean usePixelAspectRatio,							/*! @param usePixelAspectRatio
																	Compute the dimensions maintaining pixel aspect ratio */
		Boolean useCleanAperture )								/*! @param useCleanAperture
																	Compute the dimensions using the clean aperture */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMVideoFormatDescriptionGetCleanAperture
	@abstract	Returns the clean aperture.
	@discussion
		The clean aperture is a rectangle that defines the portion of the encoded pixel dimensions
		that represents image data valid for display.  
*/
CM_EXPORT
CGRect CMVideoFormatDescriptionGetCleanAperture( 
		CMVideoFormatDescriptionRef CM_NONNULL videoDesc,		/*! @param videoDesc
																	FormatDescription being interrogated. */
		Boolean originIsAtTopLeft )								/*! @param originIsAtTopLeft
																	Pass true if the CGRect will be used in an environment
																	where (0,0) is at the top-left corner of an enclosing rectangle
																	and y coordinates increase as you go down.
																	Pass false if the CGRect will be used in an environment 
																	where (0,0) is at the bottom-left corner of an enclosing rectangle 
																	and y coordinates increase as you go up. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers
	@abstract	Returns an array of the keys that are used both as CMVideoFormatDescription extensions
				and CVImageBuffer attachments and attributes.
	@discussion	When specifying a CMFormatDescription for a CMSampleBuffer, the format description must
				be consistent with formatting information attached to the CVImageBuffer. The width, height,
				and codecType must match (for CVPixelBuffers the codec type is given by
				CVPixelBufferGetPixelFormatType(pixelBuffer); for other CVImageBuffers, the codecType must be 0).
				The format description extensions must match the image buffer attachments for all the keys in the
				list returned by this function (if absent in either they must be absent in both).
				
				Currently, the list is:
				
				kCMFormatDescriptionExtension_CleanAperture
				kCMFormatDescriptionExtension_FieldCount
				kCMFormatDescriptionExtension_FieldDetail
				kCMFormatDescriptionExtension_PixelAspectRatio
				kCMFormatDescriptionExtension_ColorPrimaries
				kCMFormatDescriptionExtension_TransferFunction
				kCMFormatDescriptionExtension_GammaLevel
				kCMFormatDescriptionExtension_YCbCrMatrix
				kCMFormatDescriptionExtension_ICCProfile
				kCMFormatDescriptionExtension_ChromaLocationTopField
				kCMFormatDescriptionExtension_ChromaLocationBottomField
*/
CM_EXPORT
CFArrayRef CM_NONNULL CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers(void)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMVideoFormatDescriptionMatchesImageBuffer
	@abstract	Checks to see if a given format description matches an image buffer.
	@discussion	This function uses the keys returned by CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers
				to compares the extensions of the given format description to the attachments of the
				given image buffer (if an attachment is absent in either it must be absent in both).
				It also checks kCMFormatDescriptionExtension_BytesPerRow against CVPixelBufferGetBytesPerRow, if applicable.
*/
CM_EXPORT
Boolean CMVideoFormatDescriptionMatchesImageBuffer(
	CMVideoFormatDescriptionRef CM_NONNULL desc,	/*! @param desc			format description to validate. */
	CVImageBufferRef CM_NONNULL imageBuffer)		/*! @param imageBuffer	image buffer validate against. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#pragma mark CMMuxedFormatDescription

/*! 
	@functiongroup	Muxed-specific functions
*/

/*!
	@typedef CMMuxedFormatDescriptionRef
	Synonym type used for manipulating muxed media CMFormatDescriptions
*/
typedef CMFormatDescriptionRef CMMuxedFormatDescriptionRef;

/*!
	@enum CMMuxedStreamType
	@discussion Muxed media format/subtype.
	@constant	kCMMuxedStreamType_MPEG1System	MPEG-1 System stream
	@constant	kCMMuxedStreamType_MPEG2Transport	MPEG-2 Transport stream
	@constant	kCMMuxedStreamType_MPEG2Program	MPEG-2 Program stream
	@constant	kCMMuxedStreamType_DV	DV stream
*/
typedef FourCharCode CMMuxedStreamType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMMuxedStreamType
#else
enum
#endif
{
	kCMMuxedStreamType_MPEG1System		= 'mp1s',
	kCMMuxedStreamType_MPEG2Transport	= 'mp2t',
	kCMMuxedStreamType_MPEG2Program		= 'mp2p',
	kCMMuxedStreamType_DV				= 'dv  '
};

#define CMMuxedFormatDescriptionGetStreamType(desc)  CMFormatDescriptionGetMediaSubType(desc)

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMMuxedFormatDescriptionCreate
	@abstract	Creates a format description for a muxed media stream.
	@discussion	A muxed format description does not know what the formats are of the substreams within the muxed stream.
				That information will only be discoverable by the demuxer software (or other software which understands
				the details of the muxed bitstream) which will need to produce separate format descriptions for each of
				its output streams. The caller owns the returned CMFormatDescription, and must release it when done
				with it. All input parameters are copied (the extensions are deep-copied).  The caller can deallocate
				them or re-use them after making this call.
*/
CM_EXPORT
OSStatus CMMuxedFormatDescriptionCreate(
	CFAllocatorRef CM_NULLABLE allocator,							/*! @param allocator		CFAllocator to be used. kCFAllocatorDefault if you don't care. */
	CMMuxedStreamType muxType,										/*! @param muxType			Type of the muxed stream (eg. kCMMuxedStreamType_MPEG2Transport
																		for MPEG-2 transport stream). This is the media subtype, and will
																		be returned if you subsequently call CMFormatDescriptionGetMediaSubType
																		(or CMMuxedFormatDescriptionGetStreamType). */
	CFDictionaryRef CM_NULLABLE extensions,							/*! @param extensions		Dictionary of extension key/value pairs. Keys are always CFStrings.
																		Values are always property list objects (ie. CFData, CFString, CFArray,
																		CFDictionary, CFDate, CFBoolean, or CFNumber). Can be NULL. */
	CM_RETURNS_RETAINED_PARAMETER CMMuxedFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)	/*! @param outDesc		Returned newly created muxed CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_ENABLED

#pragma mark CMClosedCaptionFormatDescription

/*! 
	@functiongroup	Closed caption-specific functions
*/

/*!
	@typedef CMClosedCaptionFormatDescriptionRef
	Synonym type used for manipulating closed-caption media CMFormatDescriptions
*/
typedef CMFormatDescriptionRef CMClosedCaptionFormatDescriptionRef;

/*!
	@enum CMClosedCaptionFormatType
	@discussion Closed-caption media format/subtype.
				Note:  use CMFormatDescriptionCreate to create a CMClosedCaptionFormatDescriptionRef.
	@constant	kCMClosedCaptionFormatType_CEA608	CEA 608-compliant samples
	@constant	kCMClosedCaptionFormatType_CEA708	CEA 708-compliant samples
	@constant	kCMClosedCaptionFormatType_ATSC		ATSC/52 part-4 compliant samples
*/
typedef FourCharCode CMClosedCaptionFormatType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMClosedCaptionFormatType
#else
enum
#endif
{
	kCMClosedCaptionFormatType_CEA608	= 'c608',
	kCMClosedCaptionFormatType_CEA708	= 'c708',
	kCMClosedCaptionFormatType_ATSC		= 'atcc'
};

#define CMClosedCaptionFormatDescriptionGetFormatType(desc)  CMFormatDescriptionGetMediaSubType(desc)


#pragma mark CMTextFormatDescription

/*! 
	@functiongroup	Text-specific functions
*/

/*!
	@typedef CMTextFormatDescriptionRef
	Synonym type used for manipulating Text media CMFormatDescriptions
*/
typedef CMFormatDescriptionRef CMTextFormatDescriptionRef;

/*!
	@enum CMTextFormatType
	@discussion Text media format/subtype.
	@constant	kCMTextFormatType_QTText	QuickTime Text media
	@constant	kCMTextFormatType_3GText	3GPP Text media
*/
typedef FourCharCode CMTextFormatType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMTextFormatType
#else
enum
#endif
{
    kCMTextFormatType_QTText           = 'text',
    kCMTextFormatType_3GText           = 'tx3g'
};

/*!
	@enum CMTextDisplayFlags
	@discussion Display mode flags for text media.
	@constant	kCMTextDisplayFlag_scrollIn		Text scrolls into the display region.
	@constant	kCMTextDisplayFlag_scrollOut	Text scrolls out of the display region.
	@constant	kCMTextDisplayFlag_scrollDirectionMask	The scrolling direction is set by a two-bit field, obtained from displayFlags using kCMTextDisplayFlag_scrollDirectionMask.
	@constant	kCMTextDisplayFlag_scrollDirection_bottomToTop	Text is vertically scrolled up ("credits style"), entering from the bottom and leaving towards the top.
	@constant	kCMTextDisplayFlag_scrollDirection_rightToLeft	Text is horizontally scrolled ("marquee style"), entering from the right and leaving towards the left.
	@constant	kCMTextDisplayFlag_scrollDirection_topToBottom	Text is vertically scrolled down, entering from the top and leaving towards the bottom.
	@constant	kCMTextDisplayFlag_scrollDirection_leftToRight	Text is horizontally scrolled, entering from the left and leaving towards the right.
	@constant	kCMTextDisplayFlag_continuousKaraoke	Enables the Continuous Karaoke mode where the range of karaoke highlighting extends to include additional ranges rather than the highlighting moves onto the next range.
	@constant	kCMTextDisplayFlag_writeTextVertically	Specifies the text to be rendered vertically.
	@constant	kCMTextDisplayFlag_fillTextRegion	The subtitle display bounds are to be filled with the color specified by kCMTextFormatDescriptionExtension_BackgroundColor.
	@constant	kCMTextDisplayFlag_obeySubtitleFormatting	Specifies that the subtitle display bounds should be used to determine if the subtitles should be placed near the top or the bottom of the video. Otherwise, subtitles should be placed at the bottom of the video.
	@constant	kCMTextDisplayFlag_forcedSubtitlesPresent	There are forced subtitles present, e.g., a subtitle which only displays during foreign language sections of the video. Check individual samples to determine what type of subtitle is contained.
	@constant	kCMTextDisplayFlag_allSubtitlesForced	Treat all subtitle samples as if they contain forced subtitles.
*/
typedef uint32_t CMTextDisplayFlags;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMTextDisplayFlags
#else
enum
#endif
{
    kCMTextDisplayFlag_scrollIn                    = 0x00000020,
    kCMTextDisplayFlag_scrollOut                   = 0x00000040,
    kCMTextDisplayFlag_scrollDirectionMask         = 0x00000180,
    kCMTextDisplayFlag_scrollDirection_bottomToTop = 0x00000000,
    kCMTextDisplayFlag_scrollDirection_rightToLeft = 0x00000080,
    kCMTextDisplayFlag_scrollDirection_topToBottom = 0x00000100,
    kCMTextDisplayFlag_scrollDirection_leftToRight = 0x00000180,
    kCMTextDisplayFlag_continuousKaraoke           = 0x00000800,
    kCMTextDisplayFlag_writeTextVertically         = 0x00020000,
    kCMTextDisplayFlag_fillTextRegion              = 0x00040000,
    kCMTextDisplayFlag_obeySubtitleFormatting      = 0x20000000,
    kCMTextDisplayFlag_forcedSubtitlesPresent      = 0x40000000,
    kCMTextDisplayFlag_allSubtitlesForced          = 0x80000000,
};

/*!
	@enum CMTextJustificationValue
	@discussion Justification modes for text media. Used when specifying either horizontal or vertical justification.
	@constant	kCMTextJustification_left_top	Left justification when specified for horizontal justification, top justification for vertical justification.
	@constant	kCMTextJustification_centered	Center justification (both horizontal and vertical justification).
	@constant	kCMTextJustification_bottom_right	Bottom justification when specified for vertical justification, right justification for horizontal justification.
*/
typedef int8_t CMTextJustificationValue;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMTextJustificationValue
#else
enum
#endif
{
	kCMTextJustification_left_top		=  0,
	kCMTextJustification_centered		=  1,
	kCMTextJustification_bottom_right	= -1
};

CM_ASSUME_NONNULL_BEGIN

// Extension keys and values common to kCMTextFormatType_QTText and kCMTextFormatType_3GText format descriptions
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_DisplayFlags                 // CFNumber (SInt32 holding CMTextDisplayFlags)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_BackgroundColor              // CFDictionary
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionColor_Red                          // CFNumber (SInt8 for 3G), (SInt16 for QT)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionColor_Green                        // CFNumber (SInt8 for 3G), (SInt16 for QT)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionColor_Blue                         // CFNumber (SInt8 for 3G), (SInt16 for QT)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionColor_Alpha                        // CFNumber (SInt8 for 3G), not applicable for QT text.
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_DefaultTextBox               // CFDictionary
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionRect_Top                           // CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionRect_Left                          // CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionRect_Bottom                        // CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionRect_Right                         // CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_DefaultStyle                 // CFDictionary
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_StartChar             		// CFNumber (SInt16 for 3G), (SInt32 for QT)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_Font                  		// CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_FontFace              		// CFNumber (SInt8)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_ForegroundColor       		// CFDictionary (kCMTextFormatDescriptionColor_Red, kCMTextFormatDescriptionColor_Green, etc)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_FontSize              		// CFNumber (SInt8 for 3G), (SInt16 for QT)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    
// Extension keys and values specific to kCMTextFormatType_3GText
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_HorizontalJustification      // CFNumber (SInt8 holding a CMTextJustificationValue)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_VerticalJustification        // CFNumber (SInt8 holding a CMTextJustificationValue)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    // Extension keys and values specific to the kCMTextFormatType_3GText kCMTextFormatDescriptionExtension_DefaultStyle dictionary
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_EndChar               		// CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_FontTable                    // CFDictionary (Keys are FontIDs as CFStrings, vals are font names as CFStrings)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    
// Extension keys and values specific to kCMTextFormatType_QTText
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_TextJustification            // CFNumber (SInt32 holding a CMTextJustificationValue)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    // Extension keys and values specific to the kCMTextFormatType_QTText kCMTextFormatDescriptionExtension_DefaultStyle dictionary
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_Height                		// CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
    CM_EXPORT const CFStringRef kCMTextFormatDescriptionStyle_Ascent                		// CFNumber (SInt16)
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTextFormatDescriptionExtension_DefaultFontName              // CFString
								__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CM_ASSUME_NONNULL_END

/*!
	@function	CMTextFormatDescriptionGetDisplayFlags
	@abstract	Returns the displayFlags.
	@discussion
		These are the flags that control how the text appears. The function can return kCMFormatDescriptionError_ValueNotAvailable for formats without display flags.
*/
CM_EXPORT
OSStatus CMTextFormatDescriptionGetDisplayFlags(
	CMFormatDescriptionRef CM_NONNULL desc,			/*! @param desc
											FormatDescription being interrogated. */
	CMTextDisplayFlags * CM_NONNULL outDisplayFlags)	/*! @param outDisplayFlags
											Receives the display flags. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTextFormatDescriptionGetJustification
	@abstract	Returns horizontal and vertical justification.
	@discussion
		Values are kCMTextJustification_* constants. The function returns kCMFormatDescriptionError_ValueNotAvailable for format descriptions that do not carry text justification.
*/
CM_EXPORT
OSStatus CMTextFormatDescriptionGetJustification(
	CMFormatDescriptionRef CM_NONNULL desc,					/*! @param desc
													FormatDescription being interrogated. */
	CMTextJustificationValue * CM_NULLABLE outHorizontalJust,/*! @param outHorizontalJust
													Horizontal justification mode. May be NULL. */
	CMTextJustificationValue * CM_NULLABLE outVerticalJust)		/*! @param outVerticalJust
													Vertical justification mode. May be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTextFormatDescriptionGetDefaultTextBox
	@abstract	Returns the default text box.
	@discussion
		Within a text track, text is rendered within a text box.  There is a default text box set, which can be over-ridden by a sample. The function can return kCMFormatDescriptionError_ValueNotAvailable for format descriptions that do not carry a default text box.
*/
CM_EXPORT
OSStatus CMTextFormatDescriptionGetDefaultTextBox(
	CMFormatDescriptionRef CM_NONNULL desc,		/*! @param desc
													FormatDescription being interrogated. */
	Boolean originIsAtTopLeft,					/*! @param originIsAtTopLeft
													Pass true if the CGRect will be used in an environment
													where (0,0) is at the top-left corner of an enclosing rectangle
													and y coordinates increase as you go down.
													Pass false if the CGRect will be used in an environment
													where (0,0) is at the bottom-left corner of an enclosing rectangle
													and y coordinates increase as you go up. */
	CGFloat heightOfTextTrack,					/*! @param heightOfTextTrack
													If originIsAtTopLeft is false, pass the height of the enclosing text track or destination.
													This value will be used to properly compute the default text box for the given origin.
													Ignored if originIsAtTopLeft is true. */
	CGRect * CM_NONNULL outDefaultTextBox)		/*! @param outDefaultTextBox
													Receives the default text box. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTextFormatDescriptionGetDefaultStyle
	@abstract	Returns the default style. 
	@discussion	
		The function returns kCMFormatDescriptionError_ValueNotAvailable for format descriptions that do not carry default style information.
*/
CM_EXPORT
OSStatus CMTextFormatDescriptionGetDefaultStyle(
	CMFormatDescriptionRef CM_NONNULL desc,		/*! @param desc
													FormatDescription being interrogated. */
	uint16_t * CM_NULLABLE outLocalFontID,		/*! @param localFontID
													Font number, local to the FormatDescription. May be NULL. */
	Boolean * CM_NULLABLE outBold,				/*! @param outBold
													Returned true if style includes Bold. May be NULL. */
	Boolean * CM_NULLABLE outItalic,				/*! @param outItalic
													Returned true if style includes Italic. May be NULL. */
	Boolean * CM_NULLABLE outUnderline,			/*! @param outUnderline
													Returned true if style includes Underline. May be NULL. */
	CGFloat * CM_NULLABLE outFontSize,			/*! @param outFontSize
													FontSize in points. May be NULL. */
	/* CM_NULLABLE */ CGFloat outColorComponents[4])	/*! @param outColorComponents
													Components are in order red, green, blue, alpha. May be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMTextFormatDescriptionGetFontName
	@abstract	Returns the font name for a local font ID.
	@discussion
		Some format descriptions carry a mapping from local font IDs to font names. The function returns kCMFormatDescriptionError_ValueNotAvailable for format descriptions that do not carry such a font mapping table.
*/
CM_EXPORT
OSStatus CMTextFormatDescriptionGetFontName(
	CMFormatDescriptionRef CM_NONNULL desc,					/*! @param desc
																FormatDescription being interrogated. */
	uint16_t localFontID,									/*! @param localFontID
																Font number, local to the FormatDescription. */
	CM_RETURNS_NOT_RETAINED_PARAMETER CFStringRef CM_NULLABLE * CM_NONNULL outFontName)		/*! @param outFontName
																Name of the font. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CF_IMPLICIT_BRIDGING_ENABLED

#pragma mark CMSubtitleFormatDescription

typedef FourCharCode CMSubtitleFormatType;
	
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMSubtitleFormatType
#else
enum
#endif
{
    kCMSubtitleFormatType_3GText = 'tx3g',
	kCMSubtitleFormatType_WebVTT = 'wvtt',
};
	
#define CMSubtitleFormatDescriptionGetFormatType(desc)	CMFormatDescriptionGetMediaSubType(desc)

#pragma mark CMTimeCodeFormatDescription

/*! 
	@functiongroup	TimeCode-specific functions
*/

/*!
	@typedef CMTimeCodeFormatDescriptionRef
	SYnonym type used for manipulating TimeCode media CMFormatDescriptions
*/
typedef CMFormatDescriptionRef CMTimeCodeFormatDescriptionRef;

/*!
	@enum CMTimeCodeFormatType
	@discussion The types of TimeCode.
	@constant	kCMTimeCodeFormatType_TimeCode32 32-bit timeCode sample.
	@constant	kCMTimeCodeFormatType_TimeCode64 64-bit timeCode sample.
	@constant	kCMTimeCodeFormatType_Counter32 32-bit counter-mode sample.
	@constant	kCMTimeCodeFormatType_Counter64 64-bit counter-mode sample.
*/
typedef FourCharCode CMTimeCodeFormatType;

#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMTimeCodeFormatType
#else
enum
#endif
{
	kCMTimeCodeFormatType_TimeCode32	= 'tmcd',
	kCMTimeCodeFormatType_TimeCode64	= 'tc64',
	kCMTimeCodeFormatType_Counter32		= 'cn32',
	kCMTimeCodeFormatType_Counter64		= 'cn64'
};

#define CMTimeCodeFormatDescriptionGetFormatType(desc)	CMFormatDescriptionGetMediaSubType(desc)

/*!
	@enum TimeCode Flags
	@discussion Flags passed to CMTimeCodeFormatDescriptionCreate.
	@constant	kCMTimeCodeFlag_DropFrame	Timecodes are to be rendered in drop-frame format.
	@constant	kCMTimeCodeFlag_24HourMax	Timecode rolls over every 24 hours.
	@constant	kCMTimeCodeFlag_NegTimesOK	Track may contain negative timecodes.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : uint32_t
#else
enum
#endif
{
	kCMTimeCodeFlag_DropFrame	= 1 << 0,
	kCMTimeCodeFlag_24HourMax	= 1 << 1,
	kCMTimeCodeFlag_NegTimesOK	= 1 << 2
};

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMTimeCodeFormatDescriptionCreate
	@abstract	Creates a format description for a timecode media.
	@discussion	The caller owns the returned CMFormatDescription, and must release it when done with it. All input parameters
				are copied (the extensions are deep-copied).  The caller can deallocate them or re-use them after making this call.
*/
CM_EXPORT
OSStatus CMTimeCodeFormatDescriptionCreate(
	CFAllocatorRef CM_NULLABLE allocator,								/*! @param allocator
																			Allocator to be used for creating the FormatDescription object */
	CMTimeCodeFormatType timeCodeFormatType,							/*! @param timeCodeFormatType
																			One of the CMTimeCodeFormatTypes */
	CMTime frameDuration,												/*! @param frameDuration
																			Duration of each frame (eg. 100/2997) */
	uint32_t frameQuanta,												/*! @param frameQuanta
																			Frames/sec for timecode (eg. 30) OR frames/tick for counter mode */
	uint32_t tcFlags,													/*! @param tcFlags
																			kCMTimeCodeFlag_DropFrame, kCMTimeCodeFlag_24HourMax, kCMTimeCodeFlag_NegTimesOK */
	CFDictionaryRef CM_NULLABLE extensions,								/*! @param extensions
																			Keys are always CFStrings. Values are always property list objects (ie. CFData). May be NULL. */
	CM_RETURNS_RETAINED_PARAMETER CMTimeCodeFormatDescriptionRef CM_NULLABLE * CM_NONNULL descOut)	/*! @param descOut
																			Receives the newly-created CMFormatDescription. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMTimeCodeFormatDescriptionGetFrameDuration
	@abstract	Returns the duration of each frame (eg. 100/2997)
*/
CM_EXPORT
CMTime CMTimeCodeFormatDescriptionGetFrameDuration(
	CMTimeCodeFormatDescriptionRef CM_NONNULL timeCodeFormatDescription)	/*! @param timeCodeFormatDescription
																FormatDescription being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeCodeFormatDescriptionGetFrameQuanta
	@abstract	Returns the frames/sec for timecode (eg. 30) OR frames/tick for counter mode
*/
CM_EXPORT
uint32_t CMTimeCodeFormatDescriptionGetFrameQuanta(
	CMTimeCodeFormatDescriptionRef CM_NONNULL timeCodeFormatDescription)	/*! @param timeCodeFormatDescription
																FormatDescription being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeCodeFormatDescriptionGetTimeCodeFlags
	@abstract	Returns the flags for kCMTimeCodeFlag_DropFrame, kCMTimeCodeFlag_24HourMax, kCMTimeCodeFlag_NegTimesOK
*/
CM_EXPORT
uint32_t CMTimeCodeFormatDescriptionGetTimeCodeFlags(
	CMTimeCodeFormatDescriptionRef CM_NONNULL desc)	/*! @param desc
											FormatDescription being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMTimeCodeFormatDescriptionExtension_SourceReferenceName	// CFDictionary containing the following two keys
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTimeCodeFormatDescriptionKey_Value						// CFString
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMTimeCodeFormatDescriptionKey_LangCode					// CFNumber
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CM_ASSUME_NONNULL_END

#pragma mark CMMetadataFormatDescription

/*! 
	@functiongroup	Metadata-specific functions
*/

/*!
	@typedef CMMetadataFormatDescriptionRef
	SYnonym type used for manipulating Metadata media CMFormatDescriptions
*/
typedef CMFormatDescriptionRef CMMetadataFormatDescriptionRef;

/*!
	@enum CMMetadataFormatType
	@discussion The subtypes of Metadata media type.
	@constant	kCMMetadataFormatType_ICY		SHOUTCast format.
	@constant	kCMMetadataFormatType_ID3		ID3 format.
	@constant	kCMMetadataFormatType_Boxed		Boxed format.
*/
typedef FourCharCode CMMetadataFormatType;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMMetadataFormatType
#else
enum
#endif
{
	kCMMetadataFormatType_ICY   = 'icy ',
	kCMMetadataFormatType_ID3   = 'id3 ',
	kCMMetadataFormatType_Boxed = 'mebx',
};

CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMFormatDescriptionExtensionKey_MetadataKeyTable
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_Namespace	// CFNumber(OSType) native endian
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_Value		// CFData
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_LocalID 	// CFNumber(OSType) native endian
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_DataType 	// CFData
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_DataTypeNamespace 	// CFNumber(SInt32) native endian
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_ConformingDataTypes // CFArray(CFDictionary) of DataType and DataTypeNamespace
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_LanguageTag	// CFString
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionKey_StructuralDependency	// CFDictionary
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CM_EXPORT const CFStringRef kCMMetadataFormatDescription_StructuralDependencyKey_DependencyIsInvalidFlag	// CFBoolean
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionMetadataSpecificationKey_Identifier				// CFString
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionMetadataSpecificationKey_DataType				// CFString
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionMetadataSpecificationKey_ExtendedLanguageTag	// CFString in BCP 47 format
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataFormatDescriptionMetadataSpecificationKey_StructuralDependency	// CFDictionary
							__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

CM_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

CM_EXPORT
OSStatus CMMetadataFormatDescriptionCreateWithKeys(
	CFAllocatorRef CM_NULLABLE allocator,								/*! @param allocator	CFAllocator to be used. kCFAllocatorDefault if you don't care. */
	CMMetadataFormatType metadataType,									/*! @param metadataType The type of metadata. */
	CFArrayRef CM_NULLABLE keys,											/*! @param keys			Array of metadata keys.  Required if metadataType is kCMMetadataFormatType_Boxed,
																			may be NULL for metadataTypes that do not have keys (such as kCMMetadataFormatType_ICY
																			and kCMMetadataFormatType_ID3).
																			Each key is a dictionary of key properties. The required properties are:
																			kCMMetadataFormatDescriptionKey_Namespace
																			kCMMetadataFormatDescriptionKey_Value
																			kCMMetadataFormatDescriptionKey_LocalID */
	CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)	/*! @param outDesc		Returned newly created metadata CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_EXPORT
OSStatus CMMetadataFormatDescriptionCreateWithMetadataSpecifications(
	CFAllocatorRef CM_NULLABLE allocator,								/*! @param allocator		CFAllocator to be used. kCFAllocatorDefault if you don't care. */
	CMMetadataFormatType metadataType,									/*! @param metadataType		Currently the type must be kCMMetadataFormatType_Boxed. */
	CFArrayRef CM_NONNULL metadataSpecifications,						/*! @param metadataSpecifications	An array of dictionaries, each dictionary supplies a metadata identifier, a datatype, and an optional language tag. */
	CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)	/*! @param outDesc			Returned newly created metadata CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CM_EXPORT
OSStatus CMMetadataFormatDescriptionCreateWithMetadataFormatDescriptionAndMetadataSpecifications(
	CFAllocatorRef CM_NULLABLE allocator,								/*! @param allocator		CFAllocator to be used. kCFAllocatorDefault if you don't care. */
	CMMetadataFormatDescriptionRef CM_NONNULL srcDesc,					/*! @param srcDesc			Source metadata format description being extended */
	CFArrayRef CM_NONNULL metadataSpecifications,						/*! @param metadataSpecifications	An array of dictionaries, each dictionary supplies a metadata identifier, a datatype, and an optional language tag. */
	CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)	/*! @param outDesc			Returned newly created metadata CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CM_EXPORT
OSStatus CMMetadataFormatDescriptionCreateByMergingMetadataFormatDescriptions(
	CFAllocatorRef CM_NULLABLE allocator,								/*! @param allocator		CFAllocator to be used. kCFAllocatorDefault if you don't care. */
	CMMetadataFormatDescriptionRef CM_NONNULL srcDesc1,					/*! @param srcDesc1			Metadata format description being merged */
	CMMetadataFormatDescriptionRef CM_NONNULL srcDesc2,					/*! @param srcDesc2			Metadata format description being merged */
	CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL outDesc)	/*! @param outDesc			Returned newly created metadata CMFormatDescription */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

CM_EXPORT
CFDictionaryRef CM_NULLABLE CMMetadataFormatDescriptionGetKeyWithLocalID( CMMetadataFormatDescriptionRef CM_NONNULL desc, OSType localKeyID)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_EXPORT
CFArrayRef CM_NULLABLE CMMetadataFormatDescriptionGetIdentifiers( CMMetadataFormatDescriptionRef CM_NONNULL desc)
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
		
#endif // FIGFORMATDESCRIPTION_H
// ==========  CoreMedia.framework/Headers/CMBase.h
/*
    File:  CMBase.h
	
	Framework:  CoreMedia
	
    Copyright 2006-2015 Apple Inc. All rights reserved.

*/

#ifndef CMBASE_H
#define	CMBASE_H

#include <TargetConditionals.h>
#include <Availability.h>
#include <AvailabilityMacros.h>

// Pre-10.11, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_11
	#define __AVAILABILITY_INTERNAL__MAC_10_11 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.10, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_10
	#define __AVAILABILITY_INTERNAL__MAC_10_10 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.7, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_7
	#define __AVAILABILITY_INTERNAL__MAC_10_7 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-4.3, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_4_3
	#define __AVAILABILITY_INTERNAL__IPHONE_4_3 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.8, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_8
	#define __AVAILABILITY_INTERNAL__MAC_10_8 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER
	#define AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER WEAK_IMPORT_ATTRIBUTE
#endif
// Pre-6.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_6_0
	#define __AVAILABILITY_INTERNAL__IPHONE_6_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
// Pre-10.9, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_9
	#define __AVAILABILITY_INTERNAL__MAC_10_9 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif
#ifndef AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER
	#define AVAILABLE_MAC_OS_X_VERSION_10_9_AND_LATER WEAK_IMPORT_ATTRIBUTE
#endif
// Pre-7.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_7_0
#define __AVAILABILITY_INTERNAL__IPHONE_7_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-7.1, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_7_1
#define __AVAILABILITY_INTERNAL__IPHONE_7_1 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-10.10, weak import
#ifndef __AVAILABILITY_INTERNAL__MAC_10_10
#define __AVAILABILITY_INTERNAL__MAC_10_10 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-9.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_9_0
#define __AVAILABILITY_INTERNAL__IPHONE_9_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Pre-8.0, weak import
#ifndef __AVAILABILITY_INTERNAL__IPHONE_8_0
#define __AVAILABILITY_INTERNAL__IPHONE_8_0 __AVAILABILITY_INTERNAL_WEAK_IMPORT
#endif

// Deprecations
#ifndef __AVAILABILITY_INTERNAL__IPHONE_3_0_DEP__IPHONE_7_0
#define __AVAILABILITY_INTERNAL__IPHONE_3_0_DEP__IPHONE_7_0 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11
#define __AVAILABILITY_INTERNAL__MAC_10_8_DEP__MAC_10_11 WEAK_IMPORT_ATTRIBUTE
#endif

#ifndef __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_0
#define __AVAILABILITY_INTERNAL__IPHONE_6_0_DEP__IPHONE_9_0 WEAK_IMPORT_ATTRIBUTE
#endif

#include <stdint.h>						// int32_t, etc.
#include <stddef.h>						// size_t

#include <CoreFoundation/CFBase.h>		// OSStatus, Boolean, Float32, Float64

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

#if TARGET_OS_MAC
	#define CM_EXPORT extern
	#define VT_EXPORT extern
	#define MT_EXPORT extern
#elif TARGET_OS_WIN32
	#define CM_EXPORT __declspec( dllimport ) extern
	#define VT_EXPORT __declspec( dllimport ) extern
	#define MT_EXPORT __declspec( dllimport ) extern
#else
	#error "specify your platform"
#endif

#if TARGET_OS_WINDOWS && TARGET_CPU_X86_64
typedef int64_t CMItemCount;
typedef int64_t CMItemIndex;
#else
typedef signed long	CMItemCount;
typedef signed long	CMItemIndex;
#endif

#define COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS	(__cplusplus && __cplusplus >= 201103L && (__has_extension(cxx_strong_enums) || __has_feature(objc_fixed_enum))) || (!__cplusplus && __has_feature(objc_fixed_enum))

#if (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature)
#if __has_feature(nullability)
	#define COREMEDIA_DECLARE_NULLABILITY 1
#endif
#if __has_feature(assume_nonnull)
	#define COREMEDIA_DECLARE_NULLABILITY_BEGIN_END 1
#endif
#if __has_feature(objc_bridge_id)
	#define COREMEDIA_DECLARE_BRIDGED_TYPES 1
#endif
#if __has_feature(attribute_cf_returns_retained)
	#define COREMEDIA_DECLARE_RETURNS_RETAINED 1
#endif
#if __has_feature(attribute_cf_returns_on_parameters)
	#define COREMEDIA_DECLARE_RETURNS_RETAINED_ON_PARAMETERS 1
	#define COREMEDIA_DECLARE_RETURNS_NOT_RETAINED_ON_PARAMETERS 1
#endif
#endif // (TARGET_OS_IPHONE || TARGET_OS_MAC) && defined(__has_feature)

#if COREMEDIA_DECLARE_NULLABILITY
#define CM_NULLABLE __nullable
#define CM_NONNULL __nonnull
#else
#define CM_NULLABLE
#define CM_NONNULL
#endif

#if COREMEDIA_DECLARE_NULLABILITY_BEGIN_END
#define CM_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define CM_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")
#else
#define CM_ASSUME_NONNULL_BEGIN
#define CM_ASSUME_NONNULL_END
#endif
	
#if COREMEDIA_DECLARE_BRIDGED_TYPES
#define CM_BRIDGED_TYPE(type)	CF_BRIDGED_TYPE(type)
#else
#define CM_BRIDGED_TYPE(type)
#endif
	
#if COREMEDIA_DECLARE_RETURNS_RETAINED
#define CM_RETURNS_RETAINED		CF_RETURNS_RETAINED
#else
#define CM_RETURNS_RETAINED
#endif
	
#if COREMEDIA_DECLARE_RETURNS_RETAINED_ON_PARAMETERS
#define CM_RETURNS_RETAINED_PARAMETER	CF_RETURNS_RETAINED
#else
#define CM_RETURNS_RETAINED_PARAMETER
#endif
	
#if COREMEDIA_DECLARE_RETURNS_NOT_RETAINED_ON_PARAMETERS
#define CM_RETURNS_NOT_RETAINED_PARAMETER	CF_RETURNS_NOT_RETAINED
#else
#define CM_RETURNS_NOT_RETAINED_PARAMETER
#endif
	
typedef int32_t CMPersistentTrackID;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMPersistentTrackID
#else
enum
#endif
{
	kCMPersistentTrackID_Invalid = 0
};

#if !defined(CM_INLINE)
	#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
		#define CM_INLINE static inline
	#elif defined(__MWERKS__) || defined(__cplusplus)
		#define CM_INLINE static inline
	#elif defined(__GNUC__)
		#define CM_INLINE static __inline__
	#elif defined(_MSC_VER)
		#define CM_INLINE static __inline
	#else
		#define CM_INLINE static    
	#endif
#endif

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // CMBASE_H
// ==========  CoreMedia.framework/Headers/CMBlockBuffer.h
/*
    File:  CMBlockBuffer.h
 
	Framework:  CoreMedia

    Copyright 2005-2015 Apple Inc. All rights reserved.

*/

#ifndef CMBLOCKBUFFER_H
#define CMBLOCKBUFFER_H

/*!
	@header	CMBlockBuffer.h
	@abstract	API for creating and manipulating BlockBuffers
	@discussion	BlockBuffers are CF objects that are used to move blocks of memory through a processing system.
	A CMBlockBuffer represents a contiguous range of data offsets, from zero to CMBlockBufferGetDataLength(), across a
	possibly noncontiguous memory region composed of memoryBlocks and buffer references which in turn could
	refer to addtional regions.
	<BR>
	IMPORTANT: Clients of CMBlockBuffer must explicitly manage the retain count by 
	calling CFRetain and CFRelease even in processes using garbage collection.  
	<BR>
	Objective-C code that may run under garbage collection should NOT use [bbuf retain],
	or [bbuf release]; these will not have the correct effect.
	<BR>
	Furthermore, if they may run under garbage collection, Objective-C objects that release 
	instance variable CMBlockBuffer objects during their -finalize methods should set those 
	object pointers to NULL immediately afterwards, to ensure that method calls received 
	after -finalize operate safely.
*/

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMAttachment.h>
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

/*!
	@enum CMBlockBuffer Errors
	@discussion The errors returned from the CMBlockBuffer APIs
	@constant	kCMBlockBufferNoErr Success
	@constant	kCMBlockBufferStructureAllocationFailedErr Returned when a CMBlockBuffer-creating API gets a failure
				from the CFAllocator provided for CMBlockBuffer construction.
	@constant	kCMBlockBufferBlockAllocationFailedErr Returned when the allocator provided to allocate a memory block
				(as distinct from CMBlockBuffer structures) fails.
	@constant	kCMBlockBufferBadCustomBlockSourceErr The custom block source’s Allocate() routine was NULL when an allocation was attempted.
	@constant	kCMBlockBufferBadOffsetParameterErr The offset provided to an API is out of the range of the relevent CMBlockBuffer.
	@constant	kCMBlockBufferBadLengthParameterErr The length provided to an API is out of the range of the relevent CMBlockBuffer,
				or is not allowed to be zero.
	@constant	kCMBlockBufferBadPointerParameterErr	A pointer parameter (e.g. CMBlockBuffer reference, destination memory) is NULL
				or otherwise invalid.
	@constant	kCMBlockBufferEmptyBBufErr	Expected a non-empty CMBlockBuffer.
	@constant	kCMBlockBufferUnallocatedBlockErr	An unallocated memory block was encountered.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMBlockBufferNoErr							= 0,
	kCMBlockBufferStructureAllocationFailedErr	= -12700,
	kCMBlockBufferBlockAllocationFailedErr		= -12701,
	kCMBlockBufferBadCustomBlockSourceErr		= -12702,
	kCMBlockBufferBadOffsetParameterErr			= -12703,
	kCMBlockBufferBadLengthParameterErr			= -12704,
	kCMBlockBufferBadPointerParameterErr		= -12705,
	kCMBlockBufferEmptyBBufErr					= -12706,
	kCMBlockBufferUnallocatedBlockErr			= -12707,
	kCMBlockBufferInsufficientSpaceErr			= -12708,
};

/*!
	@typedef CMBlockBufferFlags
	Type used for parameters containing CMBlockBuffer feature and control flags
*/
typedef uint32_t CMBlockBufferFlags;

/*!
	@enum CMBlockBuffer Flags
	@discussion Flags controlling behaviors and features of CMBlockBuffer APIs
	@constant kCMBlockBufferAssureMemoryNowFlag When passed to routines that accept block allocators, causes the memory block
				to be allocated immediately.
	@constant kCMBlockBufferAlwaysCopyDataFlag Used with CMBlockBufferCreateContiguous() to cause it to always produce an allocated
				copy of the desired data.
	@constant kCMBlockBufferDontOptimizeDepthFlag Passed to CMBlockBufferAppendBufferReference() and CMBlockBufferCreateWithBufferReference()
				to suppress reference depth optimization
	@constant kCMBlockBufferPermitEmptyReferenceFlag Passed to CMBlockBufferAppendBufferReference() and CMBlockBufferCreateWithBufferReference()
				to allow references into a CMBlockBuffer that may not yet be populated.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMBlockBufferFlags
#else
enum
#endif
{
	kCMBlockBufferAssureMemoryNowFlag		= (1L<<0),
	kCMBlockBufferAlwaysCopyDataFlag		= (1L<<1),
	kCMBlockBufferDontOptimizeDepthFlag		= (1L<<2),
	kCMBlockBufferPermitEmptyReferenceFlag	= (1L<<3)
};

/*!
	@typedef CMBlockBufferRef
	A reference to a CMBlockBuffer, a CF object that adheres to retain/release semantics. When CFRelease() is performed
	on the last reference to the CMBlockBuffer, any referenced BlockBuffers are released and eligible memory blocks are
	deallocated. These operations are recursive, so one release could result in many follow on releses.
*/
typedef struct CM_BRIDGED_TYPE(id) OpaqueCMBlockBuffer *CMBlockBufferRef;

/*!
	@typedef CMBlockBufferCustomBlockSource
	Used with functions that accept a memory block allocator, this structure allows a client to provide a custom facility for
	obtaining the memory block to be used in a CMBlockBuffer. The Allocate function must be non-zero if the CMBlockBuffer code will
	need to call for allocation (not required if a previously-obtained memory block is provided to the CMBlockBuffer API). The
	Free() routine, if non-NULL, will be called once when the CMBlockBuffer is disposed. It will not be called if no memory block
	is ever allocated or supplied. The refCon will be passed to both the Allocate and Free() calls. The client is responsible for
	its disposal (if any) during the Free() callback.
*/
typedef  struct {
	uint32_t	version;
	void* CM_NULLABLE (* CM_NULLABLE AllocateBlock)(void* CM_NULLABLE refCon, size_t sizeInBytes);
	void (* CM_NULLABLE FreeBlock)(void* CM_NULLABLE refCon, void* CM_NONNULL doomedMemoryBlock, size_t sizeInBytes);
	void* CM_NULLABLE refCon;
} CMBlockBufferCustomBlockSource;

#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : uint32_t
#else
enum
#endif
{
	kCMBlockBufferCustomBlockSourceVersion = 0
};

/*! 
 @functiongroup CMBlockBuffer creation and assembly functions
*/

/*!
	@function	CMBlockBufferCreateEmpty
	
	@abstract	Creates an empty CMBlockBuffer
	@discussion	Creates an empty CMBlockBuffer, i.e. one which has no memory block nor reference to a CMBlockBuffer
				supplying bytes to it. It is ready to be populated using CMBlockBufferAppendMemoryBlock()
				and/or CMBlockBufferAppendBufferReference(). CMBlockBufferGetDataLength() will return zero for
				an empty CMBlockBuffer and CMBlockBufferGetDataPointer() and CMBlockBufferAssureBufferMemory() will fail.
				The memory for the CMBlockBuffer object will be allocated using the given allocator.
				If NULL is passed for the allocator, the default allocator is used.

	@param	structureAllocator	Allocator to use for allocating the CMBlockBuffer object. NULL will cause the
								default allocator to be used.
	@param	subBlockCapacity	Number of subBlocks the newBlockBuffer shall accommodate before expansion occurs.
								A value of zero means "do the reasonable default"
	@param	flags				Feature and control flags
	@param	newBBufOut			Receives newly-created empty CMBlockBuffer object with retain count of 1. Must not be  NULL.
	
	@result	Returns kCMBlockBufferNoErr if successful.
*/
CM_EXPORT OSStatus	CMBlockBufferCreateEmpty(
		CFAllocatorRef CM_NULLABLE structureAllocator,
		uint32_t subBlockCapacity, 
		CMBlockBufferFlags flags, 
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL newBBufOut)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferCreateWithMemoryBlock
	
	@abstract	Creates a new CMBlockBuffer backed by a memory block (or promise thereof). 
	@discussion Creates a new CMBlockBuffer backed by a memory block. The memory block may be statically allocated, dynamically allocated
	using the given allocator (or customBlockSource) or not yet allocated. The returned CMBlockBuffer may be further expanded using
	CMBlockBufferAppendMemoryBlock() and/or CMBlockBufferAppendBufferReference(). 

	If the kCMBlockBufferAssureMemoryNowFlag is set in the flags parameter, the memory block is allocated immediately using the blockAllocator or
	customBlockSource. 
				
	@param	structureAllocator	Allocator to use for allocating the CMBlockBuffer object. NULL will cause the
								default allocator to be used.
	@param	memoryBlock			Block of memory to hold buffered data. If NULL, a memory block will be allocated when needed (via a call
								to CMBlockBufferAssureBlockMemory()) using the provided blockAllocator or customBlockSource. If non-NULL,
								the block will be used and will be deallocated when the new CMBlockBuffer is finalized (i.e. released for
								the last time).
	@param	blockLength			Overall length of the memory block in bytes. Must not be zero. This is the size of the
								supplied memory block or the size to allocate if memoryBlock is NULL.
	@param	blockAllocator		Allocator to be used for allocating the memoryBlock, if memoryBlock is NULL. If memoryBlock is non-NULL,
								this allocator will be used to deallocate it if provided. Passing NULL will cause the default allocator
								(as set at the time of the call) to be used. Pass kCFAllocatorNull if no deallocation is desired.
	@param	customBlockSource	If non-NULL, it will be used for the allocation and freeing of the memory block (the blockAllocator
								parameter is ignored). If provided, and the memoryBlock parameter is NULL, its Allocate() routine must
								be non-NULL. Allocate will be called once, if successful, when the memoryBlock is allocated. Free() will
								be called once when the CMBlockBuffer is disposed.
	@param	offsetToData		Offset within the memoryBlock at which the CMBlockBuffer should refer to data.
	@param	dataLength			Number of relevant data bytes, starting at offsetToData, within the memory block.
	@param	flags				Feature and control flags
	@param	newBBufOut			Receives newly-created CMBlockBuffer object with a retain count of 1. Must not be  NULL.

	@result	Returns kCMBlockBufferNoErr if successful.
*/
CM_EXPORT OSStatus	CMBlockBufferCreateWithMemoryBlock(
		CFAllocatorRef CM_NULLABLE structureAllocator,
		void * CM_NULLABLE memoryBlock,
		size_t blockLength,
		CFAllocatorRef CM_NULLABLE blockAllocator,
		const CMBlockBufferCustomBlockSource * CM_NULLABLE customBlockSource,
		size_t offsetToData, 
		size_t dataLength,
		CMBlockBufferFlags flags, 
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL newBBufOut)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferCreateWithBufferReference
	
	@abstract	Creates a new CMBlockBuffer that refers to another CMBlockBuffer.
	@discussion Creates a new CMBlockBuffer that refers to (a possibly subset portion of) another CMBlockBuffer.
				The returned CMBlockBuffer may be further expanded using CMBlockBufferAppendMemoryBlock() and/or CMBlockBufferAppendBufferReference(). 

	@param	structureAllocator	Allocator to use for allocating the CMBlockBuffer object. NULL will cause the
								default allocator to be used.
	@param	targetBuffer		CMBlockBuffer to refer to. This parameter must not be NULL. Unless the kCMBlockBufferPermitEmptyReferenceFlag
								is passed, it must not be empty and it must have a data length at least large enough to supply the data subset
								specified (i.e. offsetToData+dataLength bytes).
	@param	offsetToData		Offset within the target CMBlockBuffer at which the new CMBlockBuffer should refer to data.
	@param	dataLength			Number of relevant data bytes, starting at offsetToData, within the target CMBlockBuffer.
	@param	flags				Feature and control flags
	@param	newBBufOut			Receives newly-created CMBlockBuffer object with a retain count of 1. Must not be  NULL.

	@result	Returns kCMBlockBufferNoErr if successful.
*/
CM_EXPORT OSStatus	CMBlockBufferCreateWithBufferReference(
		CFAllocatorRef CM_NULLABLE structureAllocator,
		CMBlockBufferRef CM_NONNULL targetBuffer,
		size_t offsetToData,
		size_t dataLength, 
		CMBlockBufferFlags flags, 
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL newBBufOut)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferCreateContiguous
	
	@abstract	Produces a CMBlockBuffer containing a contiguous copy of or reference to the data specified by the parameters.
	@discussion	Produces a CMBlockBuffer containing a contiguous copy of or reference to the data specified by the parameters.
				The resulting new CMBlockBuffer may contain an allocated copy of the data, or may contain a contiguous CMBlockBuffer reference. 

				If the kCMBlockBufferAlwaysCopyDataFlag is set in the flags parameter, the resulting CMBlockBuffer will contain an allocated
				copy of the data rather than a reference to theSourceBuffer. 

	@param	structureAllocator	Allocator to use for allocating the CMBlockBuffer object. NULL will cause the
								default allocator to be used.
	@param	theSourceBuffer		CMBlockBuffer from which data will be copied or referenced. Must not be NULL nor empty,
	@param	blockAllocator		Allocator to be used for allocating the memoryBlock if a contiguous copy of the data is to be made. Passing NULL will cause the default
								allocator (as set at the time of the call) to be used.
	@param	customBlockSource	If non-NULL, it will be used for the allocation and freeing of the memory block (the blockAllocator
								parameter is ignored). If provided, and the memoryBlock parameter is NULL, its Allocate() routine must
								be non-NULL. Allocate will be called once, if successful, when the memoryBlock is allocated. Free() will
								be called once when the CMBlockBuffer is disposed.
	@param	offsetToData		Offset within the source CMBlockBuffer at which the new CMBlockBuffer should obtain data.
	@param	dataLength			Number of relevant data bytes, starting at offsetToData, within the source CMBlockBuffer. If zero, the
								target buffer's total available dataLength (starting at offsetToData) will be referenced.
	@param	flags				Feature and control flags
	@param	newBBufOut			Receives newly-created CMBlockBuffer object with a retain count of 1. Must not be  NULL.
	
	@result	Returns kCMBlockBufferNoErr if successful
*/
CM_EXPORT OSStatus	CMBlockBufferCreateContiguous(
		CFAllocatorRef CM_NULLABLE structureAllocator,
		CMBlockBufferRef CM_NONNULL sourceBuffer,
		CFAllocatorRef CM_NULLABLE blockAllocator,
		const CMBlockBufferCustomBlockSource * CM_NULLABLE customBlockSource,
		size_t offsetToData, 
		size_t dataLength, 
		CMBlockBufferFlags flags, 
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL newBBufOut)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@function	CMBlockBufferGetTypeID
	
	@abstract	Obtains the CoreFoundation type ID for the CMBlockBuffer type.
	@discussion	Obtains the CoreFoundation type ID for the CMBlockBuffer type.
	
	@result	Returns the CFTypeID corresponding to CMBlockBuffer.
*/
CM_EXPORT CFTypeID CMBlockBufferGetTypeID(void) __OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferAppendMemoryBlock
	
	@abstract	Adds a memoryBlock to an existing CMBlockBuffer.
	@discussion	Adds a memoryBlock to an existing CMBlockBuffer. The memory block may be statically allocated,
				dynamically allocated using the given allocator or not yet allocated. The CMBlockBuffer's total
				data length will be increased by the specified dataLength. 

				If the kCMBlockBufferAssureMemoryNowFlag is set in the flags parameter, the memory block is
				allocated immediately using the blockAllocator or customBlockSource. Note that append operations
				are not thread safe, so care must be taken when appending to BlockBuffers that are used by multiple threads.

	@param	theBuffer		CMBlockBuffer to which the new memoryBlock will be added. Must not be NULL
	@param	memoryBlock		Block of memory to hold buffered data. If NULL, a memory block will be allocated when needed
							(via a call to CMBlockBufferAssureBlockMemory()) using the provided blockAllocator or customBlockSource.
							If non-NULL, the block will be used and will be deallocated when the CMBlockBuffer is finalized (i.e. released
							for the last time).
	@param	blockLength		Overall length of the memory block in bytes. Must not be zero. This is the size of the supplied
							memory block or the size to allocate if memoryBlock is NULL.
	@param	blockAllocator	Allocator to be used for allocating the memoryBlock, if memoryBlock is NULL. If memoryBlock is
							non-NULL, this allocator will be used to deallocate it if provided. Passing NULL will cause
							the default allocator (as set at the time of the call) to be used. Pass kCFAllocatorNull if no
							deallocation is desired.
	@param	customBlockSource	If non-NULL, it will be used for the allocation and freeing of the memory block (the blockAllocator
								parameter is ignored). If provided, and the memoryBlock parameter is NULL, its Allocate() routine must
								be non-NULL. Allocate will be called once, if successful, when the memoryBlock is allocated. Free() will
								be called once when the CMBlockBuffer is disposed.
	@param	offsetToData	Offset within the memoryBlock at which the CMBlockBuffer should refer to data.
	@param	dataLength		Number of relevant data bytes, starting at offsetToData, within the memory block.
	@param	flags			Feature and control flags

	@result	Returns kCMBlockBufferNoErr if successful.
*/
CM_EXPORT OSStatus	CMBlockBufferAppendMemoryBlock(
		CMBlockBufferRef CM_NONNULL theBuffer,
		void * CM_NULLABLE memoryBlock,
		size_t blockLength, 
		CFAllocatorRef CM_NULLABLE blockAllocator,
		const CMBlockBufferCustomBlockSource * CM_NULLABLE customBlockSource,
		size_t offsetToData, 
		size_t dataLength, 
		CMBlockBufferFlags flags)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferAppendBufferReference
	
	@abstract	Adds a CMBlockBuffer reference to an existing CMBlockBuffer.
	@discussion	Adds a buffer reference to (a possibly subset portion of) another CMBlockBuffer to an existing CMBlockBuffer.
				The CMBlockBuffer's total data length will be increased by the specified dataLength. Note that append operations
				are not thread safe, so care must be taken when appending to BlockBuffers that are used by multiple threads.

	@param	theBuffer		CMBlockBuffer to which the new CMBlockBuffer reference will be added. Must not be NULL
	@param	targetBuffer	CMBlockBuffer to refer to. This parameter must not be NULL. Unless the kCMBlockBufferPermitEmptyReferenceFlag
							is passed, it must not be empty and it must have a data length at least large enough to supply the data subset
							specified (i.e. offsetToData+dataLength bytes).
	@param	offsetToData	Offset within the target CMBlockBuffer at which the CMBlockBuffer should refer to data.
	@param	dataLength		Number of relevant data bytes, starting at offsetToData, within the target CMBlockBuffer. If zero, the target
							buffer's total available dataLength (starting at offsetToData) will be referenced.
	@param	flags			Feature and control flags

	@result	Returns kCMBlockBufferNoErr if successful.
*/
CM_EXPORT OSStatus	CMBlockBufferAppendBufferReference(
		CMBlockBufferRef CM_NONNULL theBuffer,
		CMBlockBufferRef CM_NONNULL targetBBuf,
		size_t offsetToData, 
		size_t dataLength, 
		CMBlockBufferFlags flags)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferAssureBlockMemory
	
	@abstract	Assures all memory blocks in a CMBlockBuffer are allocated.
	@discussion	Traverses the possibly complex CMBlockBuffer, allocating the memory for any constituent
				memory blocks that are not yet allocated.

	@param	theBuffer		CMBlockBuffer to operate on. Must not be NULL

	@result	Returns kCMBlockBufferNoErr if successful.
*/
CM_EXPORT OSStatus	CMBlockBufferAssureBlockMemory(CMBlockBufferRef CM_NONNULL theBuffer)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*! 
 @functiongroup CMBlockBuffer access and query functions
*/

/*!
	@function	CMBlockBufferAccessDataBytes
	
	@abstract	Accesses potentially noncontiguous data in a CMBlockBuffer.
	@discussion	Used for accessing potentially noncontiguous data, this routine will return a pointer directly
				into the given CMBlockBuffer if possible, otherwise the data will be assembled and copied into the
				given temporary block and its pointer will be returned. 


	@param	theBuffer		CMBlockBuffer to operate on. Must not be NULL
	@param	offset			Offset within the CMBlockBuffer's offset range.
	@param	length			Desired number of bytes to access at offset
	@param	temporaryBlock	A piece of memory, assumed to be at least length bytes in size. Must not be NULL
	@param	returnedPointer	Receives NULL if the desired amount of data could not be accessed at the given offset.
							Receives non-NULL if it could. The value returned will either be a direct pointer into
							the CMBlockBuffer or temporaryBlock Must not be NULL.
							
	@result	Returns kCMBlockBufferNoErr if the desired amount of data could be accessed at the given offset.
*/
CM_EXPORT OSStatus CMBlockBufferAccessDataBytes(
		CMBlockBufferRef CM_NONNULL theBuffer,
		size_t offset, 
		size_t length, 
		void * CM_NONNULL temporaryBlock,
		char * CM_NULLABLE * CM_NONNULL returnedPointer)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferCopyDataBytes
	
	@abstract	Copies bytes from a CMBlockBuffer into a provided memory area.
	@discussion	This function is used to copy bytes out of a CMBlockBuffer into a provided piece of memory.
				It deals with the possibility of the desired range of data being noncontiguous. The function
				assumes that the memory at the destination is sufficient to hold the data. If length bytes
				of data are not available in the CMBlockBuffer, an error is returned and the contents of the
				destination are undefined. 
				
	@param	theSourceBuffer	The buffer from which data will be  copied into the destination
	@param	offsetToData	Offset within the source CMBlockBuffer at which the copy should begin.
	@param	dataLength		Number of bytes to copy, starting at offsetToData, within the source CMBlockBuffer. Must not be zero.
	@param	destination		Memory into which the data should be copied.
	
	@result	Returns kCMBlockBufferNoErr if the copy succeeded, returns an error otherwise.
*/
CM_EXPORT OSStatus	CMBlockBufferCopyDataBytes(
		CMBlockBufferRef CM_NONNULL theSourceBuffer,
		size_t offsetToData, 
		size_t dataLength, 
		void* CM_NONNULL destination)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferReplaceDataBytes
	
	@abstract	Copies bytes from a given memory block into a CMBlockBuffer, replacing bytes in the underlying data blocks
	@discussion	This function is used to replace bytes in a CMBlockBuffer's memory blocks with those from a provided piece of memory.
				It deals with the possibility of the destination range of data being noncontiguous. CMBlockBufferAssureBlockMemory() is
				called on the given CMBlockBuffer. If desired range is subsequently not accessible in the CMBlockBuffer, an error is returned
				and the contents of the CMBlockBuffer are untouched. 
				
	@param	sourceBytes				Memory block from which bytes are copied into the CMBlockBuffer
	@param	destinationBuffer		CMBlockBuffer whose range of bytes will be replaced by the sourceBytes.
	@param	offsetIntoDestination	Offset within the destination CMBlockBuffer at which replacement should begin.
	@param	dataLength				Number of bytes to be replaced, starting at offsetIntoDestination, in the destinationBuffer.
	
	@result	Returns kCMBlockBufferNoErr if the replacement succeeded, returns an error otherwise.
*/
CM_EXPORT OSStatus	CMBlockBufferReplaceDataBytes(
		const void* CM_NONNULL sourceBytes,
		CMBlockBufferRef CM_NONNULL destinationBuffer,
		size_t offsetIntoDestination, 
		size_t dataLength)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferFillDataBytes
	
	@abstract	Fills a CMBlockBuffer with a given byte value, replacing bytes in the underlying data blocks
	@discussion	This function is used to fill bytes in a CMBlockBuffer's memory blocks with a given byte value.
				It deals with the possibility of the destination range of data being noncontiguous. CMBlockBufferAssureBlockMemory() is
				called on the given CMBlockBuffer. If desired range is subsequently not accessible in the CMBlockBuffer, an error is returned
				and the contents of the CMBlockBuffer are untouched. 
				
	@param	fillByte				The value with which to fill the specified data range
	@param	destinationBuffer		CMBlockBuffer whose range of bytes will be filled.
	@param	offsetIntoDestination	Offset within the destination CMBlockBuffer at which filling should begin.
	@param	dataLength				Number of bytes to be filled, starting at offsetIntoDestination, in the destinationBuffer. If zero, the
									destinationBuffer's total available dataLength (starting at offsetToData) will be filled.
	
	@result	Returns kCMBlockBufferNoErr if the fill succeeded, returns an error otherwise.
*/
CM_EXPORT OSStatus	CMBlockBufferFillDataBytes(
		char fillByte, 
		CMBlockBufferRef CM_NONNULL destinationBuffer,
		size_t offsetIntoDestination, 
		size_t dataLength)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferGetDataPointer
	
	@abstract	Gains access to the data represented by a CMBlockBuffer.
	@discussion	Gains access to the data represented by a CMBlockBuffer. A pointer into a memory block is returned
				which corresponds to the offset within the CMBlockBuffer. The number of bytes addressable at the
				pointer can also be returned. This length-at-offset may be smaller than the number of bytes actually
				available starting at the offset if the dataLength of the CMBlockBuffer is covered by multiple memory
				blocks (a noncontiguous CMBlockBuffer). The data pointer returned will remain valid as long as the
				original CMBlockBuffer is referenced - once the CMBlockBuffer is released for the last time, any pointers
				into it will be invalid. 

	@param	theBuffer		CMBlockBuffer to operate on. Must not be NULL
	@param	offset			Offset within the buffer's offset range.
	@param	lengthAtOffset	On return, contains the amount of data available at the specified offset. May be NULL.
	@param	totalLength		On return, contains the block buffer's total data length (from offset 0). May be NULL.
							The caller can compare (offset+lengthAtOffset) with totalLength to determine whether
							the entire CMBlockBuffer has been referenced and whether it is possible to access the CMBlockBuffer's
							data with a contiguous reference.
	@param	dataPointer		On return, contains a pointer to the data byte at the specified offset; lengthAtOffset bytes are
							available at this address. May be NULL.

	@result	Returns kCMBlockBufferNoErr if data was accessible at the specified offset within the given CMBlockBuffer, false otherwise.
*/
CM_EXPORT OSStatus	CMBlockBufferGetDataPointer(
		CMBlockBufferRef CM_NONNULL theBuffer,
		size_t offset, 
		size_t * CM_NULLABLE lengthAtOffset,
		size_t * CM_NULLABLE totalLength,
		char * CM_NULLABLE * CM_NULLABLE dataPointer)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferGetDataLength
	
	@abstract	Obtains the total data length reachable via a CMBlockBuffer.
	@discussion	Obtains the total data length reachable via a CMBlockBuffer. This total is the sum of the dataLengths
				of the CMBlockBuffer's memoryBlocks and buffer references. Note that the dataLengths are
				the _portions_ of those constituents that this CMBlockBuffer subscribes to. This CMBlockBuffer presents a
				contiguous range of offsets from zero to its totalDataLength as returned by this routine.

	@param	theBuffer		CMBlockBuffer to examine.
	
	@result	Returns the total data length available via this CMBlockBuffer, or zero if it is empty, NULL, or somehow invalid.
*/
CM_EXPORT size_t	CMBlockBufferGetDataLength(CMBlockBufferRef CM_NONNULL theBuffer)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBlockBufferIsRangeContiguous
	
	@abstract	Determines whether the specified range within the given CMBlockBuffer is contiguous.
	@discussion	Determines whether the specified range within the given CMBlockBuffer is contiguous. if CMBlockBufferGetDataPointer()
				were to be called with the same parameters, the returned pointer would address the desired number of bytes.
	
	@param	theBuffer		CMBlockBuffer to examine. Must not be NULL
	@param	offset			Offset within the buffer's offset range.
	@param	length			Desired number of bytes to access at offset. If zero, the number of bytes available at offset
							(dataLength – offset), contiguous or not, is used.
							
	@result	Returns true if the specified range is contiguous within the CMBlockBuffer, false otherwise. Also returns false if the
			CMBlockBuffer is NULL or empty.
*/
CM_EXPORT Boolean	CMBlockBufferIsRangeContiguous(
		CMBlockBufferRef CM_NONNULL theBuffer,
		size_t offset, 
		size_t length)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@function	CMBlockBufferIsEmpty
	
	@abstract	Indicates whether the given CMBlockBuffer is empty.
	@discussion	Indicates whether the given CMBlockBuffer is empty, i.e., devoid of any memoryBlocks or CMBlockBuffer references.
				Note that a CMBlockBuffer containing a not-yet allocated memoryBlock is not considered empty.

	@param	theBuffer		CMBlockBuffer to examine. Must not be NULL
	
	@result	Returns the result of the emptiness test. Will return false if the CMBlockBuffer is NULL.
*/
CM_EXPORT Boolean	CMBlockBufferIsEmpty(CMBlockBufferRef CM_NONNULL theBuffer)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // CMBLOCKBUFFER_H
// ==========  CoreMedia.framework/Headers/CMBufferQueue.h
/*
	File:  CMBufferQueue.h
	
	Framework:  CoreMedia
 
    Copyright 2006-2015 Apple Inc. All rights reserved.
  
*/

#ifndef CMBUFFERQUEUE_H
#define CMBUFFERQUEUE_H

/*!
	@header
	@abstract	API for creating and using CMBufferQueues.
	@discussion	CMBufferQueues are CF-based objects that implement a queue of timed buffers.  These buffers can be of any
				CF-based type (CFTypeRef), but must have a concept of duration.  During CMBufferQueue creation,
				a set of callbacks is provided, one of which is a required callback that returns the duration of
				the CF-based buffer object.  A standard callback struct for CMSampleBuffers is provided as a
				convenience.  These callbacks are called synchronously from within various CMBufferQueue APIs,
				on the thread that called the API.
				
				CMBufferQueues are designed to be read and written from different threads in a producer/consumer
				model.  While this is generally two threads (one producer/enqueuer, one dequeuer/consumer),
				CMBufferQueues can service any number of threads enqueueing and/or dequeueing buffers.  Inside 
				the CMBufferQueue APIs, all operations (not just Enqueue and Dequeue, but GetDuration,
				InstallTrigger, etc) are made atomic by use of a single mutex (one mutex per created queue object).
				
				By default, a CMBufferQueue is a FIFO queue, but if a comparison callback is provided, the
				resulting CMBufferQueue will be sorted based on that callback.  For example, one might create
				a CMBufferQueue where the buffers are enqueued in decode order, and dequeued in presentation
				order, by providing a comparison callback that sorts by presentation timestamp.
				
				CMBufferQueues retain the enqueued buffer during Enqueue, so the client can release the buffer if it
				has no further need of the reference.  During DequeueAndRetain, the buffer is retained on behalf of
				the client, and released by the queue.  The result is that the retain count remains the same, and the
				ownership of the buffer is transferred from the queue to the client.
				
				If provided with a buffer-readiness callback, CMBufferQueues can check for buffer readiness during
				DequeueIfDataReadyAndRetain.  If that callback is not provided, all buffers are assumed to be ready, and
				there is no difference between DequeueAndRetain and DequeueIfDataReadyAndRetain.
				
				CMBufferQueues also implement GetMinDecodeTimeStamp and GetMinPresentationTimeStamp, with the
				help of optional callbacks that get decode and presentation timestamps from a buffer.  If either or both
				of these callbacks is not provided, kCMTimeInvalid will be returned for the missing timestamp(s).
				
				CMBufferQueues can be marked with an end-of-data (MarkEndOfData).  Once so marked, further enqueues will
				fail, and once all the buffers have been dequeued, the queue is permanently empty ("at end of data") until
				Reset is called.  Reset empties the queue and undoes the end-of-data marking.
				
				The current status of a CMBufferQueue can be interrogated.  Clients can test for emptiness (IsEmpty), current
				queue duration (GetDuration), and end-of-data status (ContainsEndOfData and IsAtEndOfData).
				
				Trigger callbacks can be installed by clients (InstallTrigger), to get notifications of various queue state
				transitions, such as "duration becomes less than 1 second".  The queue cannot be modified during a trigger
				callback, but it can be interrogated.  Trigger conditions can be tested explicitly as well (TestTrigger).
				Triggers with NULL callbacks can be added to a queue for this type of use, but triggers with callbacks can
				also have their conditions explicitly tested.
				
				Trigger callbacks may be called from any CMBufferQueue API that modifies the total duration of the queue
				(eg. Enqueue/Dequeue/Reset). Trigger callbacks are called synchronously, on the thread that called the API.
				
				Modifying the state of the queue in any way from within a trigger callback is forbidden, and will fail,
				returning kCMBufferQueueError_CannotModifyQueueFromTriggerCallback.
				
				An attempt to Enqueue onto a full queue or to Dequeue from an empty queue will not block, but will return
				immediately with an error (or with a NULL buffer).  Triggers should be installed by the client to manage
				the client's knowledge of queue fullness.  The use of repeated retries (polling) is discouraged as an
				inefficient use of resources.

				IMPORTANT: Clients of CMBufferQueue must explicitly manage the retain count by 
				calling CFRetain and CFRelease, even in processes using garbage collection.

				Objective-C code that may run under garbage collection should NOT use [bufq retain],
				or [bufq release]; these will not have the correct effect.

				Furthermore, if they may run under garbage collection, Objective-C objects that release 
				instance variable CMBufferQueue objects during their -finalize methods should set those 
				object pointers to NULL immediately afterwards, to ensure that method calls received 
				after -finalize operate safely.
*/

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>

#include <CoreMedia/CMTime.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@enum CMBufferQueue Errors
	@discussion The OSStatus errors returned from the CMBufferQueue APIs
	@constant	kCMBufferQueueError_AllocationFailed Returned when an allocation fails.
	@constant	kCMBufferQueueError_RequiredParameterMissing NULL or 0 was passed for a required parameter.
	@constant	kCMBufferQueueError_InvalidCMBufferCallbacksStruct Version was not 0, or getDuration was NULL.
	@constant	kCMBufferQueueError_EnqueueAfterEndOfData CMBufferQueueEnqueue was attempted after
				CMBufferQueueMarkEndOfData was called (without a call to CMBufferQueueReset in between).
	@constant	kCMBufferQueueError_QueueIsFull CMBufferQueueEnqueue was attempted on a full queue.
	@constant	kCMBufferQueueError_BadTriggerDuration Trigger time must be numeric, and epoch must be zero (non-zero epoch is only for timestamps, not durations)
	@constant	kCMBufferQueueError_CannotModifyQueueFromTriggerCallback Returned when an attempt is made to modify the queue from a trigger callback.
	@constant	kCMBufferQueueError_InvalidTriggerCondition Trigger condition is not a value from the CMBufferQueueTriggerCondition enum, or trigger condition is not supported by this buffer queue.
	@constant	kCMBufferQueueError_InvalidTriggerToken Trigger token is not a trigger that is currently associated with this queue.
	@constant	kCMBufferQueueError_InvalidBuffer Buffer was rejected by the CMBufferValidationCallback.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMBufferQueueError_AllocationFailed						= -12760,
	kCMBufferQueueError_RequiredParameterMissing				= -12761,
	kCMBufferQueueError_InvalidCMBufferCallbacksStruct			= -12762,
	kCMBufferQueueError_EnqueueAfterEndOfData					= -12763,
	kCMBufferQueueError_QueueIsFull								= -12764,
	kCMBufferQueueError_BadTriggerDuration						= -12765,
	kCMBufferQueueError_CannotModifyQueueFromTriggerCallback	= -12766,
	kCMBufferQueueError_InvalidTriggerCondition					= -12767,
	kCMBufferQueueError_InvalidTriggerToken						= -12768,
	kCMBufferQueueError_InvalidBuffer							= -12769,
};

/*!
	@typedef	CMBufferQueueRef
	@abstract	A reference to a CMBufferQueue, a CF object that implements a queue of timed buffers.
		
*/
typedef struct CM_BRIDGED_TYPE(id) opaqueCMBufferQueue *CMBufferQueueRef;

/*!
	@typedef	CMBufferRef
	@abstract	A reference to a CMBuffer.
	@discussion	A CMBuffer can be any CFTypeRef, as long as a getDuration callback can be provided.  Commonly used
				types are CMSampleBufferRef and CVPixelBufferRef.
*/
typedef CM_BRIDGED_TYPE(id) CFTypeRef CMBufferRef;

/*!
	@typedef	CMBufferGetTimeCallback
	@abstract	Client callback that returns a CMTime from a CMBufferRef
	@discussion	There are three callbacks of this type that can be provided to CMBufferQueueCreate: getDuration (required),
				getDecodeTimeStamp (optional), and getPresentationTimeStamp (optional).
*/
typedef CMTime (*CMBufferGetTimeCallback)(
	CMBufferRef CM_NONNULL buf,		/*! @param buf Buffer being interrogated. */
	void * CM_NULLABLE refcon);		/*! @param refcon Client refcon. Can be NULL. */

/*!
	@typedef	CMBufferGetBooleanCallback
	@abstract	Client callback that returns a Boolean from a CMBufferRef
	@discussion	There is one callback of this type that can be provided to CMBufferQueueCreate: isDataReady (optional).
*/
typedef Boolean (*CMBufferGetBooleanCallback)(
	CMBufferRef CM_NONNULL buf,		/*! @param buf Buffer being interrogated. */
	void * CM_NULLABLE refcon);		/*! @param refcon Client refcon. Can be NULL. */

/*!
	@typedef	CMBufferCompareCallback
	@abstract	Client callback that compares one CMBufferRef with another.
	@discussion	Note that a CFComparatorFunction can be used here.
*/
typedef CFComparisonResult (*CMBufferCompareCallback)(
	CMBufferRef CM_NONNULL buf1,	/*! @param buf Buffer being compared. */
	CMBufferRef CM_NONNULL buf2,	/*! @param buf Other buffer being compared. */
	void * CM_NULLABLE refcon);		/*! @param refcon Client refcon. Can be NULL. */

/*!
	 @typedef	CMBufferGetSizeCallback
	 @abstract	Client callback that returns a size_t from a CMBufferRef
	 @discussion	There is one callback of this type that can be provided to CMBufferQueueCreate: getTotalSize.
 */
typedef size_t (*CMBufferGetSizeCallback)(
	CMBufferRef CM_NONNULL buf,		/*! @param buf Buffer being interrogated. */
	void * CM_NULLABLE refcon);		/*! @param refcon Client refcon. Can be NULL. */
	
/*!
	@typedef	CMBufferCallbacks
	@abstract	Callbacks provided to CMBufferQueueCreate, for use by the queue in interrogating the buffers that it will see.
	@discussion	With the exception of isDataReady, all these callbacks must always return the same result for the same arguments.
				A buffer's duration, timestamps, or position relative to other buffers must not appear to change while it is in 
				the queue.  Once isDataReady has returned true for a given CMBuffer, it must always return true for that 
				CMBuffer.  Durations must always be positive.
*/
typedef struct {
	uint32_t					version;						/*! @field version
																	Must be 0 or 1. */
	void * CM_NULLABLE refcon;									/*! @field refcon
																	Client refcon to be passed to all callbacks (can be NULL,
																	if the callbacks don't require it). */
	CMBufferGetTimeCallback CM_NULLABLE		getDecodeTimeStamp;	/*! @field getDecodeTimeStamp
																	This callback is called from CMBufferQueueGetFirstDecodeTimeStamp (once),
																	and from CMBufferQueueGetMinDecodeTimeStamp (multiple times).  It should
																	return the decode timestamp of the buffer.  If there are multiple samples
																	in the buffer, this callback should return the minimum decode timestamp
																	in the buffer. Can be NULL (CMBufferQueueGetFirstDecodeTimeStamp and
																	CMBufferQueueGetMinDecodeTimeStamp will return kCMTimeInvalid). */
	CMBufferGetTimeCallback CM_NULLABLE getPresentationTimeStamp;/*! @field getPresentationTimeStamp
																	This callback is called from CMBufferQueueGetFirstPresentationTimeStamp
																	(once) and from CMBufferQueueGetMinPresentationTimeStamp (multiple times).
																	It should return the presentation timestamp of the buffer.  If there are
																	multiple samples in the buffer, this callback should return the minimum
																	presentation timestamp in the buffer. Can be NULL
																	(CMBufferQueueGetFirstPresentationTimeStamp and
																	CMBufferQueueGetMinPresentationTimeStamp will return kCMTimeInvalid). */
	CMBufferGetTimeCallback CM_NONNULL getDuration;				/*! @field getDuration
																	This callback is called (once) during enqueue and dequeue operations to
																	update the total duration of the queue.  Must not be NULL. */
	CMBufferGetBooleanCallback CM_NULLABLE isDataReady;			/*! @field isDataReady
																	This callback is called from CMBufferQueueDequeueIfDataReadyAndRetain, to
																	ask if the buffer that is about to be dequeued is ready.  Can be NULL
																	(data will be assumed to be ready). */
	CMBufferCompareCallback CM_NULLABLE compare;				/*! @field compare
																	This callback is called (multiple times) from CMBufferQueueEnqueue, to
																	perform an insertion sort. Can be NULL (queue will be FIFO). */
	CFStringRef CM_NULLABLE dataBecameReadyNotification;		/*! @field dataBecameReadyNotification
																	If triggers of type kCMBufferQueueTrigger_WhenDataBecomesReady are installed,
																	the queue will listen for this notification on the head buffer. 
																	Can be NULL (then the queue won't listen for it). */
	CMBufferGetSizeCallback CM_NULLABLE getSize;				/*! @field getSize
																	This callback is called (once) during enqueue and dequeue operation to
																	update the total size of the queue. Can be NULL.  Ignored if version < 1. */
} CMBufferCallbacks;

/*!
	@function	CMBufferQueueGetCallbacksForUnsortedSampleBuffers
	@abstract	Returns a pointer to a callback struct for unsorted CMSampleBuffers, provided as a convenience.
*/
CM_EXPORT const CMBufferCallbacks * CM_NONNULL CMBufferQueueGetCallbacksForUnsortedSampleBuffers(void)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	 @function	CMBufferQueueGetCallbacksForOutputPTSSortedSampleBuffers
	 @abstract	Returns a pointer to a callback struct for CMSampleBuffers sorted by output presentation timestamp, provided as a convenience.
 */
CM_EXPORT const CMBufferCallbacks * CM_NONNULL CMBufferQueueGetCallbacksForSampleBuffersSortedByOutputPTS(void)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);
	
CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMBufferQueueCreate
	@abstract	Creates a CMBufferQueue object.
	@discussion	On return, the caller owns the returned CMBufferQueue, and must release it when done with it.
*/
CM_EXPORT OSStatus CMBufferQueueCreate(
	CFAllocatorRef CM_NULLABLE allocator,	/*! @param allocator
												The allocator to use for allocating the CMBufferQueue object.
												Pass kCFAllocatorDefault to use the default allocator. */
	CMItemCount	capacity,					/*! @param capacity
												Maximum number of buffers in the queue.  Pass 0 to create
												a queue that will grow as needed. */
	const CMBufferCallbacks * CM_NONNULL callbacks,	/*! @param callbacks
												Callbacks the queue should use to interrogate the buffer objects.
												This struct is copied internally, so the client can pass a pointer
												to a temporary struct on the stack. */
	CM_RETURNS_RETAINED_PARAMETER CMBufferQueueRef CM_NULLABLE * CM_NONNULL queueOut)	/*! @param queueOut
												Returned newly created CMBufferQueue. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMBufferQueueGetTypeID
	@abstract	Returns the CFTypeID of CMBufferQueue objects.
	@discussion	You can check if a CFTypeRef object is actually a CMBufferQueue by comparing CFGetTypeID(object) with CMBufferQueueGetTypeID().
	@result		CFTypeID of CMBufferQueue objects.
*/
CM_EXPORT CFTypeID CMBufferQueueGetTypeID(void)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
    @function   CMBufferQueueEnqueue
    @abstract   Enqueues a buffer onto a CMBufferQueue.
    @discussion The buffer is retained by the queue, so the client can safely release the buffer if it has no further use for it.
				If the compare callback is non-NULL, this API performs an insertion sort using that compare operation.
				If the validation callback is non-NULL, this API calls it; if it returns a nonzero OSStatus, 
				the buffer will not be enqueued and this API will return the same error OSStatus.
*/
CM_EXPORT OSStatus CMBufferQueueEnqueue(
	CMBufferQueueRef CM_NONNULL queue,	/*! @param queue
											The CMBufferQueue on which to enqueue the buffer. */
	CMBufferRef CM_NONNULL buf)			/*! @param buf
											The buffer to enqueue. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
    @function   CMBufferQueueDequeueAndRetain
    @abstract   Dequeues a buffer from a CMBufferQueue.
    @discussion The buffer is released by the queue, but it is also retained for the client. Buffer ownership is thereby
				transferred from queue to client.  The client need not retain the buffer, but is responsible to release
				it when done with it.
	@result		The dequeued buffer.  Will be NULL if the queue is empty.
*/
CM_EXPORT CMBufferRef CM_NULLABLE CMBufferQueueDequeueAndRetain(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue from which to dequeue a buffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
    @function   CMBufferQueueDequeueIfDataReadyAndRetain
    @abstract   Dequeues a buffer from a CMBufferQueue if it is ready.
    @discussion The buffer is released by the queue, but it is also retained for the client. Buffer ownership is thereby
				transferred from queue to client.  The client need not retain the buffer, but is responsible to release
				it when done with it.
	@result		The dequeued buffer.  Will be NULL if the queue is empty, or if the buffer to be dequeued is not yet ready.
*/
CM_EXPORT CMBufferRef CM_NULLABLE CMBufferQueueDequeueIfDataReadyAndRetain(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue from which to dequeue a buffer (if the buffer is ready). */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
    @function   CMBufferQueueGetHead
    @abstract   Retrieves the next-to-dequeue buffer from a CMBufferQueue but leaves it in the queue.
    @discussion This follows CF "Get" semantics -- it does not retain the returned buffer.
    			Note that with non-FIFO queues it's not guaranteed that the next dequeue will return
    			this particular buffer (if an intervening Enqueue adds a buffer that will dequeue next).
	@result		The buffer.  Will be NULL if the queue is empty.
*/
CM_EXPORT CMBufferRef CM_NULLABLE CMBufferQueueGetHead(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue from which to retrieve a buffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueIsEmpty
	@abstract	Returns whether or not a CMBufferQueue is empty.
	@result		Whether or not the CMBufferQueue is empty. If queue is NULL, true is returned.
*/
CM_EXPORT Boolean CMBufferQueueIsEmpty(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueMarkEndOfData
	@abstract	Marks a CMBufferQueue with EOD.
	@discussion	All subsequent Enqueues will be rejected until CMBufferQueueReset is called.
				Subsequent Dequeues will succeed as long as the queue is not empty.
*/
CM_EXPORT OSStatus CMBufferQueueMarkEndOfData(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue being marked. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueContainsEndOfData
	@abstract	Returns whether or not a CMBufferQueue has been marked with EOD.
	@result		Whether or not the CMBufferQueue has been marked with EOD.
				If queue is NULL, true is returned (a NULL queue is considered to
				be empty, and permanently at EOD).
*/
CM_EXPORT Boolean CMBufferQueueContainsEndOfData(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueIsAtEndOfData
	@abstract	Returns whether or not a CMBufferQueue has been marked with EOD, and is now empty.
	@result		Whether or not the CMBufferQueue has been marked with EOD, and is now empty.
				If queue is NULL, true is returned (a NULL queue is considered to
				be empty, and permanently at EOD).
*/
CM_EXPORT Boolean CMBufferQueueIsAtEndOfData(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueReset
	@abstract	Resets a CMBufferQueue. Empties the queue, and clears any EOD mark.
	@discussion	All buffers in the queue are released.  Triggers are not removed, however,
				and will be called appropriately as the queue duration goes to zero.
*/
CM_EXPORT OSStatus CMBufferQueueReset(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												The CMBufferQueue being reset. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueResetWithCallback
	@abstract	Calls a function for every buffer in a queue, then resets the queue.
*/
CM_EXPORT OSStatus
CMBufferQueueResetWithCallback(
	CMBufferQueueRef CM_NONNULL queue,	/*! @param queue
											CMBufferQueue being reset, that may contain multiple buffers. */
	void (* CM_NONNULL callback)(CMBufferRef CM_NONNULL buffer, void * CM_NULLABLE refcon ),
										/*! @param callback
											Function to be called for each buffer.
											The callback should not make other calls to the buffer queue. */
	void * CM_NULLABLE refcon )			/*! @param refcon
											Refcon to be passed to the callback function. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueGetBufferCount
	@abstract	Gets the number of buffers in the queue.
*/
CM_EXPORT CMItemCount CMBufferQueueGetBufferCount(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueGetDuration
	@abstract	Gets the duration of a CMBufferQueue.
	@discussion	The duration of the CMBufferQueue is the sum of all the individual
				buffer durations, as reported by the getDuration callback (provided to
				CMBufferQueueCreate).  If there are no buffers in the queue,
				kCMTimeZero will be returned.
*/
CM_EXPORT CMTime CMBufferQueueGetDuration(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueGetMinDecodeTimeStamp
	@abstract	Gets the earliest decode timestamp of a CMBufferQueue.
	@discussion	The search for earliest decode timstamp is performed in this API.
				If you know your queue is in decode order, GetFirstDecodeTimeStamp
				is a faster alternative.  If the getDecodeTimeStamp callback is
				NULL, kCMTimeInvalid will be returned.
*/
CM_EXPORT CMTime CMBufferQueueGetMinDecodeTimeStamp(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueGetFirstDecodeTimeStamp
	@abstract	Gets the decode timestamp of the first buffer in a CMBufferQueue.
	@discussion	This API is is a faster alternative to GetMinDecodeTimeStamp,
				but only gives the same answer if your queue is in decode order.
				If the getDecodeTimeStamp callback is NULL, kCMTimeInvalid will
				be returned.
*/
CM_EXPORT CMTime CMBufferQueueGetFirstDecodeTimeStamp(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueGetMinPresentationTimeStamp
	@abstract	Gets the earliest presentation timestamp of a CMBufferQueue.
	@discussion	The search for earliest presentation timstamp is performed in
				this API. If you know your queue is sorted by presentation time,
				GetFirstPresentationTimeStamp is a faster alternative. If the
				getPresentationTimeStamp callback is NULL, kCMTimeInvalid will
				be returned.
*/
CM_EXPORT CMTime CMBufferQueueGetMinPresentationTimeStamp(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueGetFirstPresentationTimeStamp
	@abstract	Gets the decode timestamp of the first buffer in a CMBufferQueue.
	@discussion	This API is is a faster alternative to GetMinPresentationTimeStamp,
				but only works if you know your queue is sorted by presentation
				timestamp. If the getPresentationTimeStamp callback is NULL,
				kCMTimeInvalid will be returned.
*/
CM_EXPORT CMTime CMBufferQueueGetFirstPresentationTimeStamp(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@function	CMBufferQueueGetMaxPresentationTimeStamp
	@abstract	Gets the greatest presentation timestamp of a CMBufferQueue.
	@discussion	If the getPresentationTimeStamp callback is NULL, kCMTimeInvalid will
				be returned.
*/
CM_EXPORT CMTime CMBufferQueueGetMaxPresentationTimeStamp(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueGetEndPresentationTimeStamp
	@abstract	Gets the greatest end presentation timestamp of a CMBufferQueue.
	@discussion	This is the maximum end time (PTS + duration) of buffers in the queue.
				If the getPresentationTimeStamp callback is NULL, kCMTimeInvalid will
				be returned.
*/
CM_EXPORT CMTime CMBufferQueueGetEndPresentationTimeStamp(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

	
/*!
	 @function	CMBufferQueueGetTotalSize
	 @abstract	Gets the total size of all sample buffers of a CMBufferQueue.
 @discussion	The total size of the CMBufferQueue is the sum of all the individual
				buffer sizes, as reported by the getTotalSize callback (provided to
				CMBufferQueueCreate).  If there are no buffers in the queue,
				0 will be returned.
 */
CM_EXPORT size_t CMBufferQueueGetTotalSize(
	CMBufferQueueRef CM_NONNULL queue)		/*! @param queue
												CMBufferQueue being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_7_1);

/*!
	@typedef	CMBufferQueueTriggerToken
	@abstract	A reference to a CMBufferQueueTrigger object.  It is not a CF type; do not CFRetain or CFRelease it.
	@discussion	A trigger is a callback function that the queue calls every time the triggering condition becomes true.
				Trigger conditions include things like queue duration, queue buffer count, etc.
				Trigger callbacks are called from within CMBufferQueue routines that modify the trigger condition
				(eg. Enqueue/Dequeue/Reset).
				
				Trigger callbacks cannot modify the queue that called them; they can, however, interrogate it.
				Trigger callbacks should not block waiting for other threads to modify or interrogate the queue either.
				In fact, trigger callbacks should perform as little processing as possible, preferably arranging
				for processing to occur by signalling a semaphore, rescheduling a runloop timer, calling dispatch_async(), etc.
				
				Clients can install as many triggers as they like.  The order in which they are called is non-deterministic.
				
				Triggers with a NULL callback are valid, since even though no trigger callback will be called, the
				trigger condition can still be explicitly tested.

				The CMBufferQueueTriggerToken is returned from CMBufferQueueInstallTrigger, so clients can remove
				it later if necessary.  Triggers will automatically be removed when the queue is finalized.  Note
				that if more than one module has access to a queue, it may be hard for an individual module to know
				when the queue is finalized since other modules may retain it.  To address this concern, modules
				should remove their triggers before they themselves are finalized.
*/
typedef struct opaqueCMBufferQueueTriggerToken *CMBufferQueueTriggerToken;

/*!
	@typedef	CMBufferQueueTriggerCallback
	@abstract	A callback to be called when a CMBufferQueue trigger condition becomes true.
*/
typedef void (*CMBufferQueueTriggerCallback)(
	void * CM_NULLABLE triggerRefcon,						/*! @param triggerRefcon Refcon for trigger callback.  */
	CMBufferQueueTriggerToken CM_NONNULL triggerToken );	/*! @param triggerToken Trigger whose condition became true. */

/*!
	@enum		CMBufferQueueTriggerCondition
	@abstract	A condition to be associated with a CMBufferQueueTrigger.
	@constant	kCMBufferQueueTrigger_WhenDurationBecomesLessThan				Trigger fires when queue duration becomes < the specified duration.
	@constant	kCMBufferQueueTrigger_WhenDurationBecomesLessThanOrEqualTo		Trigger fires when queue duration becomes <= the specified duration.
	@constant	kCMBufferQueueTrigger_WhenDurationBecomesGreaterThan			Trigger fires when queue duration becomes > the specified duration.
	@constant	kCMBufferQueueTrigger_WhenDurationBecomesGreaterThanOrEqualTo	Trigger fires when queue duration becomes >= the specified duration.
	@constant	kCMBufferQueueTrigger_WhenMinPresentationTimeStampChanges		Trigger fires when minimum presentation timestamp changes (triggerTime is ignored).
	@constant	kCMBufferQueueTrigger_WhenMaxPresentationTimeStampChanges		Trigger fires when maximum presentation timestamp changes (triggerTime is ignored).
	@constant	kCMBufferQueueTrigger_WhenDataBecomesReady						Trigger fires when next dequeueable buffer becomes ready (ie, DequeueIfDataReadyAndRetain will now succeed).  (triggerTime is ignored.)
	@constant	kCMBufferQueueTrigger_WhenEndOfDataReached						Trigger fires when CMBufferQueueIsAtEndOfData's condition becomes true.  (triggerTime is ignored.)
	@constant	kCMBufferQueueTrigger_WhenReset									Trigger fires when CMBufferQueueReset called.  (triggerTime is ignored.)
	@constant	kCMBufferQueueTrigger_WhenBufferCountBecomesLessThan			Trigger fires when buffer count becomes < the specified threshold number.
	@constant	kCMBufferQueueTrigger_WhenBufferCountBecomesGreaterThan			Trigger fires when buffer count becomes > the specified threshold number.
*/
typedef int32_t CMBufferQueueTriggerCondition;
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : CMBufferQueueTriggerCondition
#else
enum
#endif
{
	kCMBufferQueueTrigger_WhenDurationBecomesLessThan = 1,
	kCMBufferQueueTrigger_WhenDurationBecomesLessThanOrEqualTo = 2,
	kCMBufferQueueTrigger_WhenDurationBecomesGreaterThan = 3,
	kCMBufferQueueTrigger_WhenDurationBecomesGreaterThanOrEqualTo = 4,
	kCMBufferQueueTrigger_WhenMinPresentationTimeStampChanges = 5,
	kCMBufferQueueTrigger_WhenMaxPresentationTimeStampChanges = 6,
	kCMBufferQueueTrigger_WhenDataBecomesReady = 7,
	kCMBufferQueueTrigger_WhenEndOfDataReached = 8,
	kCMBufferQueueTrigger_WhenReset = 9,
	kCMBufferQueueTrigger_WhenBufferCountBecomesLessThan = 10,
	kCMBufferQueueTrigger_WhenBufferCountBecomesGreaterThan = 11,
};

/*!
	@function	CMBufferQueueInstallTrigger
	@abstract	Installs a trigger on a CMBufferQueue.
	@discussion	The returned trigger token can be passed to CMBufferQueueTestTrigger and CMBufferQueueRemoveTrigger.
				The triggerTokenOut parameter can be NULL (client doesn't need to test or remove trigger), and the
				triggerCallback parameter can be NULL (client doesn't need callbacks, but rather will explicitly
				test the trigger).  One of these two parameters must be non-NULL, however, since an untestable
				trigger that does not perform a callback is meaningless.  If the trigger condition is already true,
				CMBufferQueueInstallTrigger will call the triggerCallback.  If it does this, it will first write
				the trigger token to *triggerTokenOut.
*/
CM_EXPORT OSStatus CMBufferQueueInstallTrigger(
	CMBufferQueueRef CM_NONNULL queue,					/*! @param queue
															CMBufferQueue on which the trigger is being set. */
	CMBufferQueueTriggerCallback CM_NULLABLE triggerCallback,	/*! @param triggerCallback
															Callback to be called when the trigger condition becomes true.
															Can be NULL, if client intends only to explicitly test the
															condition.  Cannot be NULL if triggerTokenOut is NULL,
															since then the trigger would be meaningless. */
	void * CM_NULLABLE triggerRefcon,					/*! @param triggerRefcon
															Refcon to be passed to the triggerCallback.
															Can be NULL if the callback doesn't need it, or is
															itself NULL. */
	CMBufferQueueTriggerCondition triggerCondition,		/*! @param triggerCondition
															The condition to be tested when evaluating the trigger. */
	CMTime triggerTime,									/*! @param triggerTime
															The time value to compare against when evaluating the trigger.
															Must be numeric (ie. not invalid, indefinite, or infinite),
															except for certain trigger conditions which ignore it
															(eg, kCMBufferQueueTrigger_WhenMinPresentationTimeStampChanges). */
	CMBufferQueueTriggerToken CM_NULLABLE * CM_NONNULL triggerTokenOut )	/*! @param triggerTokenOut
															Address where created trigger token will be written.
															Can be NULL, if client has no need to explicitly test
															or remove the trigger. Cannot be NULL if triggerCallback
															is NULL, since then the trigger would be meaningless. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueInstallTriggerWithIntegerThreshold
	@abstract	Installs a trigger on a CMBufferQueue.
	@discussion	This function behaves the same way as CMBufferQueueInstallTrigger() except the trigger is evaluated against
				the integer value rather than the time value.
*/
CM_EXPORT OSStatus CMBufferQueueInstallTriggerWithIntegerThreshold(
	CMBufferQueueRef CM_NONNULL queue,										/*! @param queue
																				CMBufferQueue on which the trigger is being set. */
	CMBufferQueueTriggerCallback CM_NULLABLE triggerCallback,				/*! @param triggerCallback
																				Callback to be called when the trigger condition becomes true.
																				Can be NULL, if client intends only to explicitly test the
																				condition.  Cannot be NULL if triggerTokenOut is NULL,
																				since then the trigger would be meaningless. */
	void * CM_NULLABLE triggerRefcon,										/*! @param triggerRefcon
																				Refcon to be passed to the triggerCallback.
																				Can be NULL if the callback doesn't need it, or is
																				itself NULL. */
	CMBufferQueueTriggerCondition triggerCondition,							/*! @param triggerCondition
																				The condition to be tested when evaluating the trigger.
																				Must be a valid condition for an integer threshold. */
	CMItemCount triggerThreshold,											/*! @param triggerThreshold
																				The integer value to compare against when evaluating the trigger. */
	CMBufferQueueTriggerToken CM_NULLABLE * CM_NONNULL triggerTokenOut )	/*! @param triggerTokenOut
																				Address where created trigger token will be written.
																				Can be NULL, if client has no need to explicitly test
																				or remove the trigger. Cannot be NULL if triggerCallback
																				is NULL, since then the trigger would be meaningless. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueRemoveTrigger
	@abstract	Removes a previously installed trigger from a CMBufferQueue.
	@discussion	Triggers will automatically be removed when a queue is finalized.  However, if more
				than one module has access to a queue, it may be hard for an individual module to know
				when the queue is finalized since other modules may retain it.  To address this concern,
				modules should remove their triggers before they themselves are finalized.
*/
CM_EXPORT OSStatus CMBufferQueueRemoveTrigger(
	CMBufferQueueRef CM_NONNULL queue,					/*! @param queue
															CMBufferQueue from which the trigger is to be removed. */
	CMBufferQueueTriggerToken CM_NONNULL triggerToken )	/*! @param triggerToken
															Trigger to remove from the queue. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueTestTrigger
	@abstract	Tests whether the trigger condition is true.
	@discussion	Whereas the trigger callback will only be called when the condition goes from false
				to true, CMBufferQueueTestTrigger always returns the condition's current status.
				The triggerToken must be one that has been installed on this queue.
*/
CM_EXPORT Boolean CMBufferQueueTestTrigger(
	CMBufferQueueRef CM_NONNULL queue,					/*! @param queue
															CMBufferQueue on which the trigger is to be tested. */
	CMBufferQueueTriggerToken CM_NONNULL triggerToken )	/*! @param triggerToken
															Trigger to test. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMBufferQueueCallForEachBuffer
	@abstract	Calls a function for every buffer in a queue.
	@discussion If the callback function returns an error, iteration will stop immediately
				and the error will be returned.
*/
CM_EXPORT OSStatus
CMBufferQueueCallForEachBuffer(
	CMBufferQueueRef CM_NONNULL queue,		/*! @param queue
												CMBufferQueue that may contain multiple buffers. */
	OSStatus (* CM_NONNULL callback)(CMBufferRef CM_NONNULL buffer, void * CM_NULLABLE refcon ),
											/*! @param callback
												Function to be called for each buffer.
												The callback may modify buffer attachments but should not modify sort-affecting
												properties (eg, timestamps).
												The callback should not make other calls to the buffer queue. */
	void * CM_NULLABLE refcon )				/*! @param refcon
												Refcon to be passed to the callback function. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@typedef	CMBufferValidationCallback
	@abstract	Tests whether a buffer is OK to add to a queue.
	@discussion
		CMBufferQueueEnqueue will call this function to validate buffers.
		Return noErr if the buffer is OK to add.  
		Return a nonzero error code if the buffer should be rejected; 
		CMBufferQueueEnqueue will return this error to the caller.
		If you do not have a more descriptive error code, use kCMBufferQueueError_InvalidBuffer.
*/
typedef OSStatus (*CMBufferValidationCallback)(CMBufferQueueRef CM_NONNULL queue, CMBufferRef CM_NONNULL buf, void * CM_NULLABLE validationRefCon );

/*!
	@function	CMBufferQueueSetValidationCallback
	@abstract	Sets a function that CMBufferQueueEnqueue will call to validate buffers before adding them to the queue.
*/
CM_EXPORT OSStatus CMBufferQueueSetValidationCallback( 
		CMBufferQueueRef CM_NONNULL queue,							/*! @param queue
																		CMBufferQueue that will use the validation callback. */
		CMBufferValidationCallback CM_NONNULL validationCallback,	/*! @param validationCallback
																		Callback that will validate each buffer enqueued. */
		void * CM_NULLABLE validationRefCon )						/*! @param validationRefCon
																		Context refcon for validation callback. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // CMBUFFERQUEUE_H
// ==========  CoreMedia.framework/Headers/CMSync.h
/*
	File:  CMSync.h
 
	Framework:  CoreMedia
 
	Copyright ¬© 2006-2015 Apple Inc. All rights reserved.
 
*/

#ifndef __CMSYNC__
#define __CMSYNC__

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTime.h>
#include <dispatch/dispatch.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	CMClock
	@abstract	A timing source object.
	@discussion
		A clock represents a source of time information: generally, a piece of hardware that measures the passage of time.  
		One example of a clock is the host time clock, accessible via CMClockGetHostTimeClock().  
		It measures time using the CPU system clock, which on Mac OS X is mach_absolute_time().
		Every audio device can also be considered a clock since the audio samples that it outputs or inputs each have a 
		defined duration (eg, 1/48000 of a second for 48 kHz audio).
		
		CMClocks are read-only: they cannot be stopped or started, and the current time cannot be set.
		A CMClock has one primary function, CMClockGetTime, which tells what time it is now.  
		Additionally, the CMSync infrastructure monitors relative drift between CMClocks.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueCMClock* CMClockRef; // a CF type; use CFRetain and CFRelease

/*!
	@typedef	CMTimebase
	@abstract	Models a timeline under application control.
	@discussion
		A timebase represents a timeline that clients can control by setting the rate and time.
		Each timebase has either a master clock or a master timebase.  
		The rate of the timebase is expressed relative to its master. 
		When a timebase has rate 0.0, its time is fixed and does not change as its master's time changes.
		When a timebase has rate 1.0, its time increases one second as its master's time increases by one second.
		When a timebase has rate 2.0, its time increases two seconds as its master's time increases by one second.
		When a timebase has rate -1.0, its time decreases one second as its master's time increases by one second.
		
		If a timebase has a master timebase, the master timebase's rate is a factor in determining the timebase's effective rate.
		In fact, a timebase's effective rate is defined as the product of its rate, its master timebase's rate, 
		its master timebase's master timebase's rate, and so on up to the ultimate master clock.  This is the rate at which
		the timebase's time changes relative to the ultimate master clock.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueCMTimebase* CMTimebaseRef; // a CF type; use CFRetain and CFRelease

typedef CM_BRIDGED_TYPE(id) CFTypeRef CMClockOrTimebaseRef; // used in argument lists and function results to indicate that either may be passed


// CMClock error codes
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMClockError_MissingRequiredParameter	= -12745,
	kCMClockError_InvalidParameter			= -12746,
	kCMClockError_AllocationFailed			= -12747,
	kCMClockError_UnsupportedOperation		= -12756,
};

// CMTimebase error codes
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMTimebaseError_MissingRequiredParameter	= -12748,
	kCMTimebaseError_InvalidParameter			= -12749,
	kCMTimebaseError_AllocationFailed			= -12750,
	kCMTimebaseError_TimerIntervalTooShort		= -12751,
	kCMTimebaseError_ReadOnly					= -12757,
};

// CMSync error codes
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMSyncError_MissingRequiredParameter	= -12752,
	kCMSyncError_InvalidParameter			= -12753,
	kCMSyncError_AllocationFailed			= -12754,
	kCMSyncError_RateMustBeNonZero			= -12755,
};

/*!
	@function	CMClockGetTypeID
	@abstract	Returns the CFTypeID for CMClock.
*/
CM_EXPORT CFTypeID
CMClockGetTypeID( void )
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMClockGetHostTimeClock
	@abstract	Returns a reference to the singleton clock logically identified with host time.
	@discussion
		On Mac OS X, the host time clock uses mach_absolute_time but returns a value 
		with a large integer timescale (eg, nanoseconds).
*/
CM_EXPORT CMClockRef CM_NONNULL
CMClockGetHostTimeClock( void )
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMClockConvertHostTimeToSystemUnits
	@abstract	Converts a host time from CMTime to the host time's native units.
	@discussion
		This function performs a scale conversion, not a clock conversion.
		It can be more accurate than CMTimeConvertScale because the system units may 
		have a non-integer timescale.
		On Mac OS X, this function converts to the units of mach_absolute_time.
*/
CM_EXPORT uint64_t
CMClockConvertHostTimeToSystemUnits( CMTime hostTime )
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMClockMakeHostTimeFromSystemUnits
	@abstract	Converts a host time from native units to CMTime.
	@discussion
		The returned value will have a large integer timescale (eg, nanoseconds).
		This function handles situations where host time's native units use a 
		non-integer timescale.
		On Mac OS X, this function converts from the units of mach_absolute_time.
*/
CM_EXPORT CMTime
CMClockMakeHostTimeFromSystemUnits( uint64_t hostTime )
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
		
/*!
	@function	CMClockGetTime
	@abstract	Retrieves the current time from a clock.
*/
CM_EXPORT CMTime
CMClockGetTime( 
		CMClockRef CM_NONNULL clock )
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMClockGetAnchorTime
	@abstract	Retrieves the current time from a clock and also the matching time from the clock's reference clock.
	@discussion	To make practical use of this, you may need to know what the clock's reference clock is.
*/
CM_EXPORT OSStatus
CMClockGetAnchorTime( 
		CMClockRef CM_NONNULL clock,
		CMTime * CM_NONNULL outClockTime,
		CMTime * CM_NONNULL outReferenceClockTime )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMClockMightDrift
	@abstract	Indicates whether it is possible for two clocks to drift relative to each other.
*/
CM_EXPORT Boolean
CMClockMightDrift(
		CMClockRef CM_NONNULL clock,
		CMClockRef CM_NONNULL otherClock )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMClockInvalidate
	@abstract	Makes the clock stop functioning.
	@discussion
		After invalidation, the clock will return errors from all APIs.
		This should only be called by the "owner" of the clock, who knows (for example) that some piece of hardware
		has gone away, and the clock will no longer work (and might even crash).
*/
CM_EXPORT void
CMClockInvalidate(
		CMClockRef CM_NONNULL clock )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
		

/*!
	@function	CMTimebaseGetTypeID
	@abstract	Returns the CFTypeID for CMTimebase.
*/
CM_EXPORT CFTypeID
CMTimebaseGetTypeID( void )
	__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMTimebaseCreateWithMasterClock
	@abstract	Creates a timebase driven by the given clock.  
	@discussion
		The timebase will initially have rate zero and time zero.
		Pass CMClockGetHostTimeClock() for masterClock to have the host time clock drive this timebase.
*/
CM_EXPORT OSStatus
CMTimebaseCreateWithMasterClock( 
		CFAllocatorRef CM_NULLABLE allocator,
		CMClockRef CM_NONNULL masterClock,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseCreateWithMasterTimebase
	@abstract	Creates a timebase driven by the given master timebase.  
	@discussion
		The timebase will initially have rate zero and time zero.
*/
CM_EXPORT OSStatus
CMTimebaseCreateWithMasterTimebase( 
		CFAllocatorRef CM_NULLABLE allocator,
		CMTimebaseRef CM_NONNULL masterTimebase,
		CM_RETURNS_RETAINED_PARAMETER CMTimebaseRef CM_NULLABLE * CM_NONNULL timebaseOut )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMTimebaseCopyMasterTimebase
	@abstract	Returns the immediate master timebase of a timebase.
	@discussion
		Returns NULL if the timebase actually has a master clock instead of a master timebase.
*/
CM_EXPORT CMTimebaseRef CM_NULLABLE
CMTimebaseCopyMasterTimebase(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/*!
	@function	CMTimebaseCopyMasterClock
	@abstract	Returns the immediate master clock of a timebase.  
	@discussion
		Returns NULL if the timebase actually has a master timebase instead of a master clock.
*/
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseCopyMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/*!
	@function	CMTimebaseCopyMaster
	@abstract	Returns the immediate master (either timebase or clock) of a timebase.  
	@discussion
		Only returns NULL if there was an error (such as timebase == NULL).
*/
CM_EXPORT CMClockOrTimebaseRef CM_NULLABLE
CMTimebaseCopyMaster(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);

/*!
	@function	CMTimebaseCopyUltimateMasterClock
	@abstract	Returns the master clock that is the master of all of a timebase's master timebases.
*/
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseCopyUltimateMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_11, __IPHONE_9_0);
		
/*!
	@function	CMTimebaseGetMasterTimebase
	@abstract	Returns the immediate master timebase of a timebase.
	@discussion
		Returns NULL if the timebase actually has a master clock instead of a master timebase.
		Please use CMTimebaseCopyMasterTimebase instead.
*/
CM_EXPORT CMTimebaseRef CM_NULLABLE
CMTimebaseGetMasterTimebase(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_10_11, __IPHONE_6_0, __IPHONE_9_0);

/*!
	@function	CMTimebaseGetMasterClock
	@abstract	Returns the immediate master clock of a timebase.  
	@discussion
		Returns NULL if the timebase actually has a master timebase instead of a master clock.
		Please use CMTimebaseCopyMasterClock instead.
*/
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseGetMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_10_11, __IPHONE_6_0, __IPHONE_9_0);

/*!
	@function	CMTimebaseGetMaster
	@abstract	Returns the immediate master (either timebase or clock) of a timebase.  
	@discussion
		Only returns NULL if there was an error (such as timebase == NULL).
		Example of use: time = CMSyncGetTime(CMTimebaseGetMaster(timebase));
		Please use CMTimebaseCopyMaster instead.
*/
CM_EXPORT CMClockOrTimebaseRef CM_NULLABLE
CMTimebaseGetMaster(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_10_11, __IPHONE_6_0, __IPHONE_9_0);

/*!
	@function	CMTimebaseGetUltimateMasterClock
	@abstract	Returns the master clock that is the master of all of a timebase's master timebases.
	@discussion
		Please use CMTimebaseCopyUltimateMasterClock instead.
*/
CM_EXPORT CMClockRef CM_NULLABLE
CMTimebaseGetUltimateMasterClock(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_8, __MAC_10_11, __IPHONE_6_0, __IPHONE_9_0);
		
/*!
	@function	CMTimebaseGetTime
	@abstract	Retrieves the current time from a timebase.
*/
CM_EXPORT CMTime
CMTimebaseGetTime( 
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseGetTimeWithTimeScale
	@abstract	Retrieves the current time from a timebase in the specified timescale.
*/
CM_EXPORT CMTime
CMTimebaseGetTimeWithTimeScale( 
		CMTimebaseRef CM_NONNULL timebase,
		CMTimeScale timescale,
		CMTimeRoundingMethod method)
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseSetTime
	@abstract	Sets the current time of a timebase.  
*/
CM_EXPORT OSStatus 
CMTimebaseSetTime( 
		CMTimebaseRef CM_NONNULL timebase,
		CMTime time )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseSetAnchorTime
	@abstract	Sets the time of a timebase at a particular master time.
	@discussion
		CMTimebaseGetTime's results will be interpolated from that anchor time.
		CMTimebaseSetTime(timebase, time) is equivalent to calling
			CMClockOrTimebaseRef master = CMTimebaseCopyMaster(timebase);
			CMTimebaseSetAnchorTime(timebase, time, CMSyncGetTime(master));
			CFRelease(master).
*/
CM_EXPORT OSStatus
CMTimebaseSetAnchorTime(
		CMTimebaseRef CM_NONNULL timebase,
		CMTime timebaseTime,
		CMTime immediateMasterTime)
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseGetRate
	@abstract	Retrieves the current rate of a timebase.  
	@discussion
		This is the rate relative to its immediate master clock or timebase.  
		For example, if a timebase is running at twice the rate of its master, its rate is 2.0.
*/
CM_EXPORT Float64 
CMTimebaseGetRate( 
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseGetTimeAndRate
	@abstract	Retrieves the current time and rate of a timebase.
	@discussion
		You can use this function to take a consistent snapshot of the two values,
		avoiding possible inconsistencies due to external changes between retrieval of time and rate.
*/
CM_EXPORT OSStatus 
CMTimebaseGetTimeAndRate( 
		CMTimebaseRef CM_NONNULL timebase,
		CMTime * CM_NONNULL outTime,
		Float64 * CM_NONNULL outRate )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseSetRate
	@abstract	Sets the rate of a timebase.
*/
CM_EXPORT OSStatus 
CMTimebaseSetRate( 
		CMTimebaseRef CM_NONNULL timebase,
		Float64 rate )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
		
/*!
	@function	CMTimebaseSetRateAndAnchorTime
	@abstract	Sets the time of a timebase at a particular master time, and changes the rate at exactly that time.
	@discussion
		CMTimebaseGetTime's results will be interpolated from that anchor time as though the timebase 
		has been running at the requested rate since that time.
		CMTimebaseSetRate(timebase, rate) is approximately equivalent to calling
			CMClockOrTimebaseRef master = CMTimebaseCopyMaster(timebase);
			CMTimebaseSetRateAndAnchorTime(timebase, rate, CMTimebaseGetTime(timebase), CMSyncGetTime(master)),
			CFRelease(master);
		except that CMTimebaseSetRate will not generate a TimeJumped notification, and
		CMTimebaseSetRateAndAnchorTime will.
*/
CM_EXPORT OSStatus
CMTimebaseSetRateAndAnchorTime(
		CMTimebaseRef CM_NONNULL timebase,
		Float64 rate,
		CMTime timebaseTime,
		CMTime immediateMasterTime)
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseGetEffectiveRate
	@abstract	Gets the effective rate of a timebase (which combines its rate with the rates of all its master timebases).
	@discussion
		Calling CMTimebaseGetEffectiveRate(timebase) is equivalent to calling
			CMClockRef clock = CMTimebaseCopyUltimateMasterClock(timebase);
			CMSyncGetRelativeRate(timebase, clock).
			CFRelease(clock);
*/
CM_EXPORT Float64
CMTimebaseGetEffectiveRate(
		CMTimebaseRef CM_NONNULL timebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseAddTimer
	@abstract
		Adds the timer to the list of timers managed by the timebase. 
	@discussion
		The timer must be a repeating run loop timer (with a very long interval at
		least as long as kCMTimebaseVeryLongCFTimeInterval), attached to a runloop.  
		The timebase will retain the timer, and will maintain its "NextFireDate" 
		according to the CMTime set using CMTimebaseSetTimerNextFireTime.
		Until the first call to CMTimebaseSetTimerNextFireTime, the "NextFireDate" 
		will be set far, far in the future. The runloop that timer is attached to must be
		passed in and the timebase will retain that runloop. The retained runloop will be
		used to call CFRunLoopWakeUp() any time the timebase modifies the timer's fire date.
*/
CM_EXPORT OSStatus
CMTimebaseAddTimer( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer,
		CFRunLoopRef CM_NONNULL runloop )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

#define kCMTimebaseVeryLongCFTimeInterval	(CFTimeInterval)(256.0 * 365.0 * 24.0 * 60.0 * 60.0)	// quite a while
#define kCMTimebaseFarFutureCFAbsoluteTime	((CFAbsoluteTime)kCMTimebaseVeryLongCFTimeInterval)		// quite a while from 2001

/*!
	@function	CMTimebaseRemoveTimer
	@abstract
		Removes the timer from the list of timers managed by the timebase. 
	@discussion
		The timebase will no longer maintain the timer's "NextFireDate".
		If the timer is invalidated, the timebase will eventually remove it 
		from its list and release it even if this function is not called.
*/
CM_EXPORT OSStatus
CMTimebaseRemoveTimer( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseSetTimerNextFireTime
	@abstract
		Sets the CMTime on the timebase's timeline at which the timer should next be fired.
	@discussion
		The timer must be on the list of timers managed by the timebase.
		The timebase will continue to update the timer's "NextFireDate" according to time jumps 
		and effective rate changes.
		If fireTime is not numeric, or if the timebase is not moving, the "NextFireDate"
		will be set to a date far, far in the future.
		<BR>
		IMPORTANT NOTE: Due to the way that CFRunLoopTimers are implemented, if a timer passes 
		through a state in which it is due to fire, it may fire even if its rescheduled before 
		the runloop runs again.  Clients should take care to avoid temporarily scheduling timers 
		in the past.  For example, set the timebase's rate or time before you set the timer's 
		next fire time, if you are doing both at once.  (If setting the timebase's rate or time
		might put the timer's fire time in the past, you may need to set the fire time to 
		kCMTimeInvalid across the timebase change.)
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerNextFireTime( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer,
		CMTime fireTime,
		uint32_t flags ) // reserved, pass zero
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseSetTimerToFireImmediately
	@abstract
		Sets the timer to fire immediately once, overriding any previous CMTimebaseSetTimerNextFireTime call.
	@discussion
		The timer must be on the list of timers managed by the timebase.
		This is equivalent to calling 
			CFRunLoopTimerSetNextFireDate( timer, CFAbsoluteTimeGetCurrent() );
		except that the timebase gets to know that it shouldn't interfere.
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerToFireImmediately( 
		CMTimebaseRef CM_NONNULL timebase,
		CFRunLoopTimerRef CM_NONNULL timer )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);


/*!
	@function	CMTimebaseAddTimerDispatchSource
	@abstract
		Adds the timer dispatch source to the list of timers managed by the timebase. 
	@discussion
		The timer source must have been created by calling
		dispatch_source_create( DISPATCH_SOURCE_TYPE_TIMER, 0, 0, some_dispatch_queue )
		and should have had an event handler associated with it via
		dispatch_source_set_event_handler( timerSource, some_handler_block )
		or dispatch_source_set_event_handler_f( timerSource, some_handler_function ).
		Don't forget to call dispatch_resume( timerSource ) as dispatch sources are 
		created suspended.
		
		The timebase will retain the timer source, and will maintain its start time
		according to the CMTime set using CMTimebaseSetTimerDispatchSourceNextFireTime.
		Until the first call to CMTimebaseSetTimerDispatchSourceNextFireTime, the start time 
		will be set to DISPATCH_TIME_FOREVER.
*/
CM_EXPORT OSStatus
CMTimebaseAddTimerDispatchSource( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);


/*!
	@function	CMTimebaseRemoveTimerDispatchSource
	@abstract
		Removes the timer dispatch source from the list of timers managed by the timebase. 
	@discussion
		The timebase will no longer maintain the timer source's start time.
		If the timer source is cancelled, the timebase will eventually remove it 
		from its list and release it even if this function is not called.
*/
CM_EXPORT OSStatus
CMTimebaseRemoveTimerDispatchSource( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseSetTimerDispatchSourceNextFireTime
	@abstract
		Sets the CMTime on the timebase's timeline at which the timer dispatch source should next be fired.
	@discussion
		The timer source must be on the list of timers managed by the timebase.
		The timebase will continue to update the timer dispatch source's start time 
		according to time jumps and effective rate changes.
		If fireTime is not numeric, or if the timebase is not moving, the start time
		will be set to DISPATCH_TIME_FOREVER.
		<BR>
		IMPORTANT NOTE: Due to the way that timer dispatch sources are implemented, if a timer passes 
		through a state in which it is due to fire, it may fire even if its rescheduled before 
		the event handler is run.  Clients should take care to avoid temporarily scheduling timers 
		in the past.  For example, set the timebase's rate or time before you set the timer's 
		next fire time, if you are doing both at once.  (If setting the timebase's rate or time
		might put the timer's fire time in the past, you may need to set the fire time to 
		kCMTimeInvalid across the timebase change.)
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerDispatchSourceNextFireTime( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource,
		CMTime fireTime,
		uint32_t flags ) // reserved, pass zero
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseSetTimerDispatchSourceToFireImmediately
	@abstract
		Sets the timer dispatch source to fire immediately once, overriding any previous
		CMTimebaseSetTimerDispatchSourceNextFireTime call.
	@discussion
		The timer source must be on the list of timers managed by the timebase.
		This is equivalent to calling 
			dispatch_source_set_timer( timerSource, DISPATCH_TIME_NOW, 0, 0 );
		except that the timebase gets to know that it shouldn't interfere.
*/
CM_EXPORT OSStatus
CMTimebaseSetTimerDispatchSourceToFireImmediately( 
		CMTimebaseRef CM_NONNULL timebase,
		dispatch_source_t CM_NONNULL timerSource )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);



/*!
	@function	CMSyncGetRelativeRate
	@abstract	Queries the relative rate of one timebase or clock relative to another timebase or clock.
	@discussion
		If both have a common master, this calculation is performed purely based on the rates in the common tree 
		rooted in that master.  
		If they have different master clocks (or are both clocks), this calculation takes into account the measured
		drift between the two clocks, using host time as a pivot.
		The rate of a moving timebase relative to a stopped timebase is a NaN.
		Calling CMTimebaseGetEffectiveRate(timebase) is equivalent to calling
			CMClockRef clock = CMTimebaseCopyUltimateMasterClock(timebase);
			CMSyncGetRelativeRate(timebase, clock).
			CFRelease(clock);
*/
CM_EXPORT Float64 
CMSyncGetRelativeRate( 
		CMClockOrTimebaseRef CM_NONNULL ofClockOrTimebase,
		CMClockOrTimebaseRef CM_NONNULL relativeToClockOrTimebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
		
/*!
	@function	CMSyncGetRelativeRateAndAnchorTime
	@abstract	Queries the relative rate of one timebase or clock relative to another timebase or clock and the times of each timebase or clock at which the relative rate went into effect.
	@discussion
		If both have a common master, this calculation is performed purely based on the rates in the common tree
		rooted in that master.  
		If they have different master clocks (or are both clocks), this calculation takes into account the measured
		drift between the two clocks, using host time as a pivot.
		The rate of a moving timebase relative to a stopped timebase is a NaN.
*/
CM_EXPORT OSStatus
CMSyncGetRelativeRateAndAnchorTime( 
		CMClockOrTimebaseRef CM_NONNULL ofClockOrTimebase,
		CMClockOrTimebaseRef CM_NONNULL relativeToClockOrTimebase,
		Float64* CM_NONNULL outRelativeRate,
		CMTime* CM_NONNULL outOfClockOrTimebaseAnchorTime,
		CMTime* CM_NONNULL outRelativeToClockOrTimebaseAnchorTime)
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMSyncConvertTime
	@abstract	Converts a time from one timebase or clock to another timebase or clock.
	@discussion
		If both have a common master, this calculation is performed purely based on the mathematical rates and offsets 
		in the common tree rooted in that master.  
		If they have different master clocks (or are both clocks), this calculation also compensates
		for measured drift between the clocks.
		To convert to or from host time, pass CMClockGetHostTimeClock() as the appropriate argument.
*/
CM_EXPORT CMTime
CMSyncConvertTime(
		CMTime time, 
		CMClockOrTimebaseRef CM_NONNULL fromClockOrTimebase,
		CMClockOrTimebaseRef CM_NONNULL toClockOrTimebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMSyncMightDrift
	@abstract	Reports whether it is possible for one timebase/clock to drift relative to the other.
	@discussion
		A timebase can drift relative to another if they are ultimately mastered by clocks that can drift relative
		to each other.
*/
CM_EXPORT Boolean
CMSyncMightDrift(
		CMClockOrTimebaseRef CM_NONNULL clockOrTimebase1,
		CMClockOrTimebaseRef CM_NONNULL clockOrTimebase2 )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
		
/*!
	@function	CMSyncGetTime
	@abstract	A helper function to get time from a clock or timebase.
	@discussion
		CMSyncGetTime simply calls either CMClockGetTime or CMTimebaseGetTime, as appropriate.
		It comes in handy for things like:
			CMClockOrTimebaseRef master = CMTimebaseCopyMaster(timebase);
			CMSyncGetTime(master);
			CFRelease(master);
*/
CM_EXPORT CMTime
CMSyncGetTime(
		CMClockOrTimebaseRef CM_NONNULL clockOrTimebase )
			__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMTimebaseNotificationBarrier
	@abstract	Requests that the timebase wait until it is not posting any notifications.
*/
CM_EXPORT OSStatus	CMTimebaseNotificationBarrier(CMTimebaseRef CM_NONNULL timebase )
						__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
	
CM_ASSUME_NONNULL_BEGIN

// Posted by a timebase after a change in effective rate.  
CM_EXPORT const CFStringRef kCMTimebaseNotification_EffectiveRateChanged
								__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

// Posted by a timebase after a discontinuous time jump.
CM_EXPORT const CFStringRef kCMTimebaseNotification_TimeJumped
								__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

// Payload key for the time at which a change in effective rate or a discontinuous time jump occurred.
CM_EXPORT const CFStringRef kCMTimebaseNotificationKey_EventTime
								__OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

CM_ASSUME_NONNULL_END
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif // __CMSYNC__
// ==========  CoreMedia.framework/Headers/CMTime.h
/*
	File:  CMTime.h
	
	Framework:  CoreMedia
 
    Copyright 2005-2015 Apple Inc. All rights reserved.
 
*/

#ifndef CMTIME_H
#define CMTIME_H

/*!
	@header
	@abstract	API for creating and manipulating CMTime structs.
	@discussion	CMTime structs are non-opaque mutable structs representing times (either timestamps or durations).
	
				A CMTime is represented as a rational number, with a numerator (int64_t value), and a denominator (int32_t timescale).
				A flags field allows various non-numeric values to be stored (+infinity, -infinity, indefinite, invalid).  There is also
				a flag to mark whether or not the time is completely precise, or had to be rounded at some point in its past.
				
				CMTimes contain an epoch number, which is usually set to 0, but can be used to distinguish unrelated
				timelines: for example, it could be incremented each time through a presentation loop,
				to differentiate between time N in loop 0 from time N in loop 1.
				
				CMTimes can be converted to/from immutable CFDictionaries, via CMTimeCopyAsDictionary and
				CMTimeMakeFromDictionary, for use in annotations and various CF containers.
*/

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@typedef	CMTimeValue
	@abstract	Numerator of rational CMTime.
*/
typedef int64_t CMTimeValue;

/*!
	@typedef	CMTimeScale
	@abstract	Denominator of rational CMTime.
	@discussion	Timescales must be positive.
				Note: kCMTimeMaxTimescale is NOT a good choice of timescale for movie files.  
				(Recommended timescales for movie files range from 600 to 90000.)
*/
typedef int32_t CMTimeScale;
#define kCMTimeMaxTimescale 0x7fffffffL

/*!
	@typedef	CMTimeEpoch
	@abstract	Epoch (eg, loop number) to which a CMTime refers.
*/
typedef int64_t CMTimeEpoch;

/*!
	@enum		CMTimeFlags
	@abstract	Flag bits for a CMTime.
	@constant	kCMTimeFlags_Valid Must be set, or the CMTime is considered invalid.
									Allows simple clearing (eg. with calloc or memset) for initialization
									of arrays of CMTime structs to "invalid". This flag must be set, even
									if other flags are set as well.
	@constant	kCMTimeFlags_HasBeenRounded Set whenever a CMTime value is rounded, or is derived from another rounded CMTime.													
	@constant	kCMTimeFlags_PositiveInfinity Set if the CMTime is +inf.	"Implied value" flag (other struct fields are ignored).													
	@constant	kCMTimeFlags_NegativeInfinity Set if the CMTime is -inf.	"Implied value" flag (other struct fields are ignored).														
	@constant	kCMTimeFlags_Indefinite Set if the CMTime is indefinite/unknown. Example of usage: duration of a live broadcast.
										 "Implied value" flag (other struct fields are ignored).
*/
typedef CF_OPTIONS( uint32_t, CMTimeFlags ) {
	kCMTimeFlags_Valid = 1UL<<0,
	kCMTimeFlags_HasBeenRounded = 1UL<<1,
	kCMTimeFlags_PositiveInfinity = 1UL<<2,
	kCMTimeFlags_NegativeInfinity = 1UL<<3,
	kCMTimeFlags_Indefinite = 1UL<<4,
	kCMTimeFlags_ImpliedValueFlagsMask = kCMTimeFlags_PositiveInfinity | kCMTimeFlags_NegativeInfinity | kCMTimeFlags_Indefinite
};

/*!
	@typedef	CMTime
	@abstract	Rational time value represented as int64/int32.
*/
typedef struct
{
	CMTimeValue	value;		/*! @field value The value of the CMTime. value/timescale = seconds. */
	CMTimeScale	timescale;	/*! @field timescale The timescale of the CMTime. value/timescale = seconds.  */
	CMTimeFlags	flags;		/*! @field flags The flags, eg. kCMTimeFlags_Valid, kCMTimeFlags_PositiveInfinity, etc. */
	CMTimeEpoch	epoch;		/*! @field epoch Differentiates between equal timestamps that are actually different because
												 of looping, multi-item sequencing, etc.  
												 Will be used during comparison: greater epochs happen after lesser ones. 
												 Additions/subtraction is only possible within a single epoch,
												 however, since epoch length may be unknown/variable. */
} CMTime;

/*!
	@function	CMTIME_IS_VALID
    @abstract   Returns whether a CMTime is valid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTime is valid, false if it is invalid.
*/
#define CMTIME_IS_VALID(time) ((Boolean)(((time).flags & kCMTimeFlags_Valid) != 0))

/*!
	@function	CMTIME_IS_INVALID
    @abstract   Returns whether a CMTime is invalid.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTime is invalid, false if it is valid.
*/
#define CMTIME_IS_INVALID(time) (! CMTIME_IS_VALID(time))

/*!
	@function	CMTIME_IS_POSITIVEINFINITY
    @abstract   Returns whether a CMTime is positive infinity.  Use this instead of (myTime == kCMTimePositiveInfinity),
				since there are many CMTime structs that represent positive infinity.  This is because the non-flags fields are ignored,
				so they can contain anything.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTime is positive infinity, false if it is not.
*/
#define CMTIME_IS_POSITIVE_INFINITY(time) ((Boolean)(CMTIME_IS_VALID(time) && (((time).flags & kCMTimeFlags_PositiveInfinity) != 0)))

/*!
	@function	CMTIME_IS_NEGATIVEINFINITY
    @abstract   Returns whether a CMTime is negative infinity.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTime is negative infinity, false if it is not.
*/
#define CMTIME_IS_NEGATIVE_INFINITY(time) ((Boolean)(CMTIME_IS_VALID(time) && (((time).flags & kCMTimeFlags_NegativeInfinity) != 0)))

/*!
	@function	CMTIME_IS_INDEFINITE
    @abstract   Returns whether a CMTime is indefinite.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTime is indefinite, false if it is not.
*/
#define CMTIME_IS_INDEFINITE(time) ((Boolean)(CMTIME_IS_VALID(time) && (((time).flags & kCMTimeFlags_Indefinite) != 0)))

/*!
	@function	CMTIME_IS_NUMERIC
    @abstract   Returns whether a CMTime is numeric (ie. contains a usable value/timescale/epoch).
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns false if the CMTime is invalid, indefinite or +/- infinity.
				Returns true otherwise.
*/
#define CMTIME_IS_NUMERIC(time) ((Boolean)(((time).flags & (kCMTimeFlags_Valid | kCMTimeFlags_ImpliedValueFlagsMask)) == kCMTimeFlags_Valid))

/*!
	@function	CMTIME_HAS_BEEN_ROUNDED
    @abstract   Returns whether a CMTime has been rounded.
    @discussion This is a macro that evaluates to a Boolean result.
    @result     Returns true if the CMTime has been rounded, false if it is completely accurate.
*/
#define CMTIME_HAS_BEEN_ROUNDED(time) ((Boolean)(CMTIME_IS_NUMERIC(time) && (((time).flags & kCMTimeFlags_HasBeenRounded) != 0)))


CM_EXPORT const CMTime kCMTimeInvalid			/*! @constant kCMTimeInvalid
													Use this constant to initialize an invalid CMTime.
													All fields are 0, so you can calloc or fill with 0's to make lots of them.
													Do not test against this using (time == kCMTimeInvalid), there are many
													CMTimes other than this that are also invalid.
													Use !CMTIME_IS_VALID(time) instead. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CMTime kCMTimeIndefinite		/*! @constant kCMTimeIndefinite
													Use this constant to initialize an indefinite CMTime (eg. duration of a live
													broadcast).  Do not test against this using (time == kCMTimeIndefinite),
													there are many CMTimes other than this that are also indefinite.
													Use CMTIME_IS_INDEFINITE(time) instead. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CMTime kCMTimePositiveInfinity	/*! @constant kCMTimePositiveInfinity 
													Use this constant to initialize a CMTime to +infinity.
													Do not test against this using (time == kCMTimePositiveInfinity),
													there are many CMTimes other than this that are also +infinity.
													Use CMTIME_IS_POSITIVEINFINITY(time) instead. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CMTime kCMTimeNegativeInfinity	/*! @constant kCMTimeNegativeInfinity 
													Use this constant to initialize a CMTime to -infinity.
													Do not test against this using (time == kCMTimeNegativeInfinity),
													there are many CMTimes other than this that are also -infinity.
													Use CMTIME_IS_NEGATIVEINFINITY(time) instead. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CMTime kCMTimeZero				/*! @constant kCMTimeZero 
													Use this constant to initialize a CMTime to 0.
													Do not test against this using (time == kCMTimeZero),
													there are many CMTimes other than this that are also 0.
													Use CMTimeCompare(time, kCMTimeZero) instead. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeMake
	@abstract	Make a valid CMTime with value and timescale.  Epoch is implied to be 0.
	@result		The resulting CMTime.
*/
CM_EXPORT 
CMTime CMTimeMake(
				int64_t value,		/*! @param value		Initializes the value field of the resulting CMTime. */
				int32_t timescale)	/*! @param timescale	Initializes the timescale field of the resulting CMTime. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeMakeWithEpoch
	@abstract	Make a valid CMTime with value, scale and epoch.
	@result		The resulting CMTime.
*/
CM_EXPORT 
CMTime CMTimeMakeWithEpoch(
				int64_t value,		/*! @param value Initializes the value field of the resulting CMTime. */
				int32_t timescale,	/*! @param timescale Initializes the scale field of the resulting CMTime. */
				int64_t epoch)		/*! @param epoch Initializes the epoch field of the resulting CMTime. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
				

/*!
	@function	CMTimeMakeWithSeconds
	@abstract	Make a CMTime from a Float64 number of seconds, and a preferred timescale.
	@discussion	The epoch of the result will be zero.  If preferredTimeScale is <= 0, the result
				will be an invalid CMTime.  If the preferred timescale will cause an overflow, the
				timescale will be halved repeatedly until the overflow goes away, or the timescale
				is 1.  If it still overflows at that point, the result will be +/- infinity.  The
				kCMTimeFlags_HasBeenRounded flag will be set if the result, when converted back to
				seconds, is not exactly equal to the original seconds value.
	@result		The resulting CMTime.
*/
CM_EXPORT 
CMTime CMTimeMakeWithSeconds(
				Float64 seconds,
				int32_t preferredTimeScale)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeGetSeconds
	@abstract	Converts a CMTime to seconds.
	@discussion	If the CMTime is invalid or indefinite, NAN is returned.  If the CMTime is infinite, +/- __inf()
				is returned.  If the CMTime is numeric, epoch is ignored, and time.value / time.timescale is
				returned.  The division is done in Float64, so the fraction is not lost in the returned result.
	@result		The resulting Float64 number of seconds.
*/
CM_EXPORT 
Float64 CMTimeGetSeconds(
				CMTime time)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@enum CMTimeRoundingMethod
	@abstract Rounding method to use when computing time.value during timescale conversions.
	@constant	kCMTimeRoundingMethod_RoundHalfAwayFromZero	Round towards zero if abs(fraction) is < 0.5,
																away from 0 if abs(fraction) is >= 0.5.
	@constant	kCMTimeRoundingMethod_Default					Synonym for kCMTimeRoundingMethod_RoundHalfAwayFromZero.
	@constant	kCMTimeRoundingMethod_RoundTowardZero			Round towards zero if fraction is != 0.
	@constant	kCMTimeRoundingMethod_RoundAwayFromZero		Round away from zero if abs(fraction) is > 0.
	@constant	kCMTimeRoundingMethod_QuickTime				Use kCMTimeRoundingMethod_RoundTowardZero if converting
																from larger to smaller scale (ie. from more precision to
																less precision), but use
																kCMTimeRoundingMethod_RoundAwayFromZero if converting
																from smaller to larger scale (ie. from less precision to
																more precision). Also, never round a negative number down
																to 0; always return the smallest magnitude negative
																CMTime in this case (-1/newTimescale).
	@constant	kCMTimeRoundingMethod_RoundTowardPositiveInfinity	Round towards +inf if fraction is != 0.
	@constant	kCMTimeRoundingMethod_RoundTowardNegativeInfinity	Round towards -inf if fraction is != 0.
*/
typedef CF_ENUM( uint32_t, CMTimeRoundingMethod ) {
	kCMTimeRoundingMethod_RoundHalfAwayFromZero = 1,
	kCMTimeRoundingMethod_RoundTowardZero = 2,
	kCMTimeRoundingMethod_RoundAwayFromZero = 3,
	kCMTimeRoundingMethod_QuickTime = 4,
	kCMTimeRoundingMethod_RoundTowardPositiveInfinity = 5,
	kCMTimeRoundingMethod_RoundTowardNegativeInfinity = 6,
	
	kCMTimeRoundingMethod_Default = kCMTimeRoundingMethod_RoundHalfAwayFromZero
};

/*!
	@function	CMTimeConvertScale
	@abstract	Returns a new CMTime containing the source CMTime converted to a new timescale (rounding as requested).
	@discussion If the value needs to be rounded, the kCMTimeFlags_HasBeenRounded flag will be set.
				See definition of CMTimeRoundingMethod for a discussion of the various rounding methods available. If
				the source time is non-numeric (ie. infinite, indefinite, invalid), the result will be similarly non-numeric.
	@result		The converted result CMTime.
*/
CM_EXPORT 
CMTime CMTimeConvertScale(
				CMTime time,					/*! @param time		Source CMTime. */
				int32_t newTimescale,			/*! @param newTimescale	The requested timescale for the converted result CMTime. */
				CMTimeRoundingMethod method)	/*! @param method	The requested rounding method. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeAdd
    @abstract   Returns the sum of two CMTimes.
    @discussion If the operands both have the same timescale, the timescale of the result will be the same as
				the operands' timescale.  If the operands have different timescales, the timescale of the result
				will be the least common multiple of the operands' timescales.  If that LCM timescale is 
				greater than kCMTimeMaxTimescale, the result timescale will be kCMTimeMaxTimescale,
				and default rounding will be applied when converting the result to this timescale.
				
				If the result value overflows, the result timescale will be repeatedly halved until the result
				value no longer overflows.  Again, default rounding will be applied when converting the
				result to this timescale.  If the result value still overflows when timescale == 1, then the
				result will be either positive or negative infinity, depending on the direction of the
				overflow.
				
				If any rounding occurs for any reason, the result's kCMTimeFlags_HasBeenRounded flag will be
				set.  This flag will also be set if either of the operands has kCMTimeFlags_HasBeenRounded set.
				
				If either of the operands is invalid, the result will be invalid.
				
				If the operands are valid, but just one operand is infinite, the result will be similarly
				infinite. If the operands are valid, and both are infinite, the results will be as follows:
<ul>			+infinity + +infinity == +infinity
<li>			-infinity + -infinity == -infinity
<li>			+infinity + -infinity == invalid
<li>			-infinity + +infinity == invalid
</ul>
				If the operands are valid, not infinite, and either or both is indefinite, the result
				will be indefinite. 								

				If the two operands are numeric (ie. valid, not infinite, not indefinite), but have
				different nonzero epochs, the result will be invalid.  If they have the same nonzero 
				epoch, the result will have epoch zero (a duration).  Times in different epochs 
				cannot be added or subtracted, because epoch length is unknown.  Times in epoch zero 
				are considered to be durations and can be added to times in other epochs.
				Times in different epochs can be compared, however, because numerically greater 
				epochs always occur after numerically lesser epochs. 
    @result     The sum of the two CMTimes (addend1 + addend2).
*/
CM_EXPORT 
CMTime CMTimeAdd(
				CMTime addend1,				/*! @param addend1			A CMTime to be added. */
				CMTime addend2)				/*! @param addend2			Another CMTime to be added. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@function	CMTimeSubtract
    @abstract   Returns the difference of two CMTimes.
    @discussion If the operands both have the same timescale, the timescale of the result will be the same as
				the operands' timescale.  If the operands have different timescales, the timescale of the result
				will be the least common multiple of the operands' timescales.  If that LCM timescale is 
				greater than kCMTimeMaxTimescale, the result timescale will be kCMTimeMaxTimescale,
				and default rounding will be applied when converting the result to this timescale.
				
				If the result value overflows, the result timescale will be repeatedly halved until the result
				value no longer overflows.  Again, default rounding will be applied when converting the
				result to this timescale.  If the result value still overflows when timescale == 1, then the
				result will be either positive or negative infinity, depending on the direction of the
				overflow.
				
				If any rounding occurs for any reason, the result's kCMTimeFlags_HasBeenRounded flag will be
				set.  This flag will also be set if either of the operands has kCMTimeFlags_HasBeenRounded set.

				If either of the operands is invalid, the result will be invalid.
				
				If the operands are valid, but just one operand is infinite, the result will be similarly
				infinite. If the operands are valid, and both are infinite, the results will be as follows:
<ul>			+infinity - +infinity == invalid
<li>			-infinity - -infinity == invalid
<li>			+infinity - -infinity == +infinity
<li>			-infinity - +infinity == -infinity
</ul>
				If the operands are valid, not infinite, and either or both is indefinite, the result
				will be indefinite. 								

				If the two operands are numeric (ie. valid, not infinite, not indefinite), but have
				different nonzero epochs, the result will be invalid.  If they have the same nonzero 
				epoch, the result will have epoch zero (a duration).  Times in different epochs 
				cannot be added or subtracted, because epoch length is unknown.  Times in epoch zero 
				are considered to be durations and can be subtracted from times in other epochs.
				Times in different epochs can be compared, however, because numerically greater 
				epochs always occur after numerically lesser epochs. 
    @result     The difference of the two CMTimes (minuend - subtrahend).
*/
CM_EXPORT 
CMTime CMTimeSubtract(
				CMTime minuend,		/*! @param minuend		The CMTime from which the subtrahend will be subtracted. */
				CMTime subtrahend)	/*! @param subtrahend	The CMTime that will be subtracted from the minuend. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@function	CMTimeMultiply
    @abstract   Returns the product of a CMTime and a 32-bit integer.
    @discussion The result will have the same timescale as the CMTime operand. If the result value overflows,
				the result timescale will be repeatedly halved until the result value no longer overflows.
				Again, default rounding will be applied when converting the result to this timescale.  If the
				result value still overflows when timescale == 1, then the result will be either positive or
				negative infinity, depending on the direction of the overflow.
				
				If any rounding occurs for any reason, the result's kCMTimeFlags_HasBeenRounded flag will be
				set.  This flag will also be set if the CMTime operand has kCMTimeFlags_HasBeenRounded set.

				If the CMTime operand is invalid, the result will be invalid.
				
				If the CMTime operand is valid, but infinite, the result will be infinite, and of an appropriate sign, given
				the signs of both operands.
				
				If the CMTime operand is valid, but indefinite, the result will be indefinite. 								

    @result     The product of the CMTime and the 32-bit integer.
*/
CM_EXPORT 
CMTime CMTimeMultiply(
				CMTime time,			/*! @param time			The CMTime that will be multiplied. */
				int32_t multiplier)		/*! @param multiplier	The integer it will be multiplied by. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeMultiplyByFloat64
	@abstract   Returns the product of a CMTime and a 64-bit float.
	@discussion The result will initially have the same timescale as the CMTime operand. 
				If the result timescale is less than 65536, it will be repeatedly doubled until it is at least 65536.
				If the result value overflows, the result timescale will be repeatedly halved until the 
				result value no longer overflows.
				Again, default rounding will be applied when converting the result to this timescale.  If the
				result value still overflows when timescale == 1, then the result will be either positive or
				negative infinity, depending on the direction of the overflow.
				
				If any rounding occurs for any reason, the result's kCMTimeFlags_HasBeenRounded flag will be
				set.  This flag will also be set if the CMTime operand has kCMTimeFlags_HasBeenRounded set.

				If the CMTime operand is invalid, the result will be invalid.
				
				If the CMTime operand is valid, but infinite, the result will be infinite, and of an appropriate sign, given
				the signs of both operands.
				
				If the CMTime operand is valid, but indefinite, the result will be indefinite.								

	@result     The product of the CMTime and the 64-bit float.
*/
CM_EXPORT 
CMTime CMTimeMultiplyByFloat64(
				CMTime time,			/*! @param time			The CMTime that will be multiplied. */
				Float64 multiplier)		/*! @param multiplier	The Float64 it will be multiplied by. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeMultiplyByRatio
    @abstract   Returns the result of multiplying a CMTime by an integer, then dividing by another integer.
    @discussion The exact rational value will be preserved, if possible without overflow.  If an overflow
				would occur, a new timescale will be chosen so as to minimize the rounding error.
				Default rounding will be applied when converting the result to this timescale.  If the
				result value still overflows when timescale == 1, then the result will be either positive
				or negative infinity, depending on the direction of the overflow.

				If any rounding occurs for any reason, the result's kCMTimeFlags_HasBeenRounded flag will be
				set.  This flag will also be set if the CMTime operand has kCMTimeFlags_HasBeenRounded set.

				If the denominator, and either the time or the numerator, are zero, the result will be
				kCMTimeInvalid.  If only the denominator is zero, the result will be either kCMTimePositiveInfinity
				or kCMTimeNegativeInfinity, depending on the signs of the other arguments.

				If time is invalid, the result will be invalid. If time is infinite, the result will be
				similarly infinite. If time is indefinite, the result will be indefinite. 								

    @result     (time * multiplier) / divisor
*/
CM_EXPORT
CMTime CMTimeMultiplyByRatio(
				CMTime time,			/*! @param time			The CMTime to be multiplied then divided. */
				int32_t multiplier,		/*! @param multiplier	The value by which to multiply. */
				int32_t divisor)		/*! @param divisor	The value by which to divide. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_7_1);

/*!
	@function	CMTimeCompare
    @abstract   Returns the numerical relationship (-1 = less than, 1 = greater than, 0 = equal) of two CMTimes.
    @discussion If the two CMTimes are numeric (ie. not invalid, infinite, or indefinite), and have
				different epochs, it is considered that times in numerically larger epochs are always
				greater than times in numerically smaller epochs. 
				
				Since this routine will be used to sort lists by time, it needs to give all values 
				(even invalid and indefinite ones) a strict ordering to guarantee that sort algorithms
				terminate safely. The order chosen is somewhat arbitrary:
				
				-infinity < all finite values < indefinite < +infinity < invalid
				
				Invalid CMTimes are considered to be equal to other invalid CMTimes, and greater than
				any other CMTime. Positive infinity is considered to be less than any invalid CMTime,
				equal to itself, and greater than any other CMTime. An indefinite CMTime is considered
				to be less than any invalid CMTime, less than positive infinity, equal to itself,
				and greater than any other CMTime.  Negative infinity is considered to be equal to itself,
				and less than any other CMTime.
				
				-1 is returned if time1 is less than time2. 0 is returned if they
				are equal. 1 is returned if time1 is greater than time2.
    @result     The numerical relationship of the two CMTimes (-1 = less than, 1 = greater than, 0 = equal).
*/
CM_EXPORT 
int32_t CMTimeCompare(
				CMTime time1,		/*! @param time1 First CMTime in comparison. */
				CMTime time2)		/*! @param time2 Second CMTime in comparison. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTIME_COMPARE_INLINE
    @abstract   Returns whether the specified comparison of two CMTimes is true.
    @discussion This is a macro that evaluates to a Boolean result.
				Example of usage:
					CMTIME_COMPARE_INLINE(time1, <=, time2) will return true if time1 <= time2.
	@param		time1 First time to compare
	@param		comparator Comparison operation to perform (eg. <=).
	@param		time2 Second time to compare
    @result     Returns the result of the specified CMTime comparison.
*/
#define CMTIME_COMPARE_INLINE(time1, comparator, time2) ((Boolean)(CMTimeCompare(time1, time2) comparator 0))

/*!
	@function	CMTimeMinimum
    @abstract   Returns the lesser of two CMTimes (as defined by CMTimeCompare).
    @result     The lesser of the two CMTimes.
*/
CM_EXPORT 
CMTime CMTimeMinimum(
				CMTime time1,	/*! @param time1 A CMTime */
				CMTime time2)	/*! @param time2 Another CMTime */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeMaximum
    @abstract   Returns the greater of two CMTimes (as defined by CMTimeCompare).
    @result     The greater of the two CMTimes.
*/
CM_EXPORT 
CMTime CMTimeMaximum(
				CMTime time1,	/*! @param time1 A CMTime */
				CMTime time2)	/*! @param time2 Another CMTime */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeAbsoluteValue
    @abstract   Returns the absolute value of a CMTime.
    @result     Same as the argument time, with sign inverted if negative.
*/
CM_EXPORT 
CMTime CMTimeAbsoluteValue(
				CMTime time)	/*! @param time A CMTime */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeCopyAsDictionary
    @abstract   Returns a CFDictionary version of a CMTime.
    @discussion This is useful when putting CMTimes in CF container types.
    @result     A CFDictionary version of the CMTime.
*/
CM_EXPORT 
CFDictionaryRef CM_NULLABLE CMTimeCopyAsDictionary(
					CMTime time,							/*! @param time			CMTime from which to create dictionary. */
					CFAllocatorRef CM_NULLABLE allocator)	/*! @param allocator	CFAllocator with which to create dictionary.
																					Pass kCFAllocatorDefault to use the default
																					allocator. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
/*!
	@function	CMTimeMakeFromDictionary
    @abstract   Reconstitutes a CMTime struct from a CFDictionary previously created by CMTimeCopyAsDictionary.
    @discussion This is useful when getting CMTimes from CF container types.  If the CFDictionary does not
				have the requisite keyed values, an invalid time is returned.
	@result		The created CMTime.  
*/
CM_EXPORT 
CMTime CMTimeMakeFromDictionary(
				CFDictionaryRef CM_NULLABLE dict)	/*! @param dict CFDictionary from which to create CMTime. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_BEGIN

/*!
	@constant kCMTimeValueKey
	@discussion CFDictionary key for value field of CMTime (CFNumber containing int64_t)
*/
CM_EXPORT const CFStringRef kCMTimeValueKey
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant kCMTimeScaleKey
	@discussion CFDictionary key for timescale field of CMTime (CFNumber containing int32_t)
*/
CM_EXPORT const CFStringRef kCMTimeScaleKey
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant kCMTimeEpochKey
	@discussion CFDictionary key for epoch field of CMTime (CFNumber containing int64_t)
*/
CM_EXPORT const CFStringRef kCMTimeEpochKey
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant kCMTimeFlagsKey
	@discussion CFDictionary key for flags field of CMTime (CFNumber containing uint32_t)
*/
CM_EXPORT const CFStringRef kCMTimeFlagsKey
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_END

/*!
	@function	CMTimeCopyDescription
    @abstract   Creates a CFString with a description of a CMTime (just like CFCopyDescription).
    @discussion This is used from within CFShow on an object that contains CMTime fields. It is
				also useful from other client debugging code.  The caller owns the returned
				CFString, and is responsible for releasing it.
	@result		The created CFString description.  
*/
CM_EXPORT 
CFStringRef CM_NULLABLE CMTimeCopyDescription(
	CFAllocatorRef CM_NULLABLE allocator,				/*! @param allocator	CFAllocator with which to create description. Pass
															kCFAllocatorDefault to use the default allocator. */
	CMTime time)										/*! @param time			CMTime to describe. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMTimeShow
    @abstract   Prints a description of the CMTime (just like CFShow).
    @discussion This is most useful from within gdb.
*/
CM_EXPORT 
void CMTimeShow(
	CMTime time)					/*! @param time			CMTime to show. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
	
#endif // CMTIME_H
// ==========  CoreMedia.framework/Headers/CMMemoryPool.h
/*
	File:  CMMemoryPool.h
 
	Framework:  CoreMedia
 
	Copyright 2006-2015 Apple Inc. All rights reserved.
 
*/

#ifndef CMMEMORYPOOL_H
#define CMMEMORYPOOL_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreMedia/CMBase.h>

#ifdef __cplusplus
extern "C" {
#endif
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@header		CMMemoryPool.h
	@abstract	Memory pool for optimizing repeated large block allocation.
	@discussion
		CMMemoryPool is a memory allocation service that holds onto a pool of
		recently deallocated memory so as to speed up subsequent allocations of the same size.  
		It's intended for cases where large memory blocks need to be repeatedly allocated --
		for example, the compressed data output by a video encoder.
		
		All of its allocations are on the granularity of page sizes; it does not suballocate
		memory within pages, so it is a poor choice for allocating tiny blocks.
		For example, it's appropriate to use as the blockAllocator argument to
		CMBlockBufferCreateWithMemoryBlock, but not the structureAllocator argument --
		use kCFAllocatorDefault instead.

		When you no longer need to allocate memory from the pool, call CMMemoryPoolInvalidate
		and CFRelease.  Calling CMMemoryPoolInvalidate tells the pool to stop holding onto
		memory for reuse.  Note that the pool's CFAllocator can outlive the pool, owing
		to the way that CoreFoundation is designed: CFAllocators are themselves CF objects,
		and every object allocated with a CFAllocator implicitly retains the CFAllocator 
		until it is finalized.  After the CMMemoryPool is invalidated or finalized,
		its CFAllocator allocates and deallocates with no pooling behavior.
		
		CMMemoryPool deallocates memory if it has not been recycled in 0.5 second,
		so that short-term peak usage does not cause persistent bloat.
		(This period may be overridden by specifying kCMMemoryPoolOption_AgeOutPeriod.)
		Such "aging out" is done during the pool's CFAllocatorAllocate and
		CFAllocatorDeallocate methods.
*/

typedef struct CM_BRIDGED_TYPE(id) OpaqueCMMemoryPool *CMMemoryPoolRef; // a CF type; use CFRetain and CFRelease.

CM_EXPORT CFTypeID CMMemoryPoolGetTypeID(void)
						__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@const		kCMMemoryPoolOption_AgeOutPeriod
	@abstract	Specifies how long memory should be allowed to hang out in the pool before being deallocated.
	@discussion	Pass this in the options dictionary to CMMemoryPoolCreate.
*/
CM_EXPORT const CFStringRef CM_NONNULL kCMMemoryPoolOption_AgeOutPeriod // CFNumber (seconds)
								__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMMemoryPoolCreate
	@abstract	Creates a new CMMemoryPool.
*/
CM_EXPORT CMMemoryPoolRef CM_NONNULL CMMemoryPoolCreate( CFDictionaryRef CM_NULLABLE options ) // pass NULL for defaults
								__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMMemoryPoolGetAllocator
	@abstract	Returns the pool's CFAllocator.
*/
CM_EXPORT CFAllocatorRef CM_NONNULL CMMemoryPoolGetAllocator( CMMemoryPoolRef CM_NONNULL pool )
								__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMMemoryPoolFlush
	@abstract	Deallocates all memory the pool was holding for recycling.
*/
CM_EXPORT void CMMemoryPoolFlush( CMMemoryPoolRef CM_NONNULL pool )
					__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);

/*!
	@function	CMMemoryPoolInvalidate
	@abstract	Stops the pool from recycling.
	@discussion
		When CMMemoryPoolInvalidate is called the pool's allocator stops recycling memory.
		The pool deallocates any memory it was holding for recycling.
		This also happens when the retain count of the CMMemoryPool drops to zero, 
		except that under GC it may be delayed.
*/
CM_EXPORT void CMMemoryPoolInvalidate( CMMemoryPoolRef CM_NONNULL pool )
					__OSX_AVAILABLE_STARTING(__MAC_10_8, __IPHONE_6_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

#ifdef __cplusplus
}
#endif

#endif // CMMEMORYPOOL_H
// ==========  CoreMedia.framework/Headers/CMFormatDescriptionBridge.h
/*
	File:  CMFormatDescriptionBridge.h

	Framework:  CoreMedia

	Copyright 2006-2015 Apple Inc. All rights reserved.

*/

#ifndef CMFORMATDESCRIPTIONBRIDGE_H
#define CMFORMATDESCRIPTIONBRIDGE_H

/*!
	@header
	@abstract	API for converting between CoreMedia's CMFormatDescription objects and the legacy QuickTime framework's sample description data structures.
	@discussion	Most developers will not need to use these functions.
				They are provided for advanced developers who need to work directly with QuickTime Movie or ISO family files, or to interface with the legacy QuickTime framework.
				There are functions for converting between big-endian buffers and CoreMedia format descriptions because sample descriptions are big-endian in the current file formats.
				There are also functions for converting between big-endian buffers and the host-endian layouts exposed in QuickTime APIs.
*/

#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMBlockBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 4)

/*!
	@enum CMFormatDescriptionBridge Errors
	@discussion OSStatus errors returned by CMFormatDescriptionBridge APIs.
	@constant	kCMFormatDescriptionBridgeError_InvalidParameter Invalid parameter.
	@constant	kCMFormatDescriptionBridgeError_AllocationFailed Returned when an allocation fails.
	@constant	kCMFormatDescriptionBridgeError_InvalidSerializedSampleDescription Returned when the sample description is invalid (e.g. invalid size).
	@constant	kCMFormatDescriptionBridgeError_InvalidFormatDescription Returned when the format description is invalid (e.g. invalid size).
	@constant	kCMFormatDescriptionBridgeError_IncompatibleFormatDescription Returned when the format description has an incompatible format (e.g. unknown format / incompatible atom).
	@constant	kCMFormatDescriptionBridgeError_UnsupportedSampleDescriptionFlavor Returned when the sample description is unsupported for the specified format flavor.
	@constant	kCMFormatDescriptionBridgeError_InvalidSlice Returned when the slice has an invalid value.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMFormatDescriptionBridgeError_InvalidParameter					= -12712,
	kCMFormatDescriptionBridgeError_AllocationFailed					= -12713,
	kCMFormatDescriptionBridgeError_InvalidSerializedSampleDescription	= -12714,
	kCMFormatDescriptionBridgeError_InvalidFormatDescription			= -12715,
	kCMFormatDescriptionBridgeError_IncompatibleFormatDescription		= -12716,
	kCMFormatDescriptionBridgeError_UnsupportedSampleDescriptionFlavor	= -12717,
	kCMFormatDescriptionBridgeError_InvalidSlice						= -12719,
};

/*! 
	@functiongroup	CMVideoFormatDescription and ImageDescription bridge functions
*/

/*!
	@constant	kCMImageDescriptionFlavor_QuickTimeMovie
	@abstract	Chooses the QuickTime Movie Image Description format.
	@discussion	Passing NULL is equivalent to passing this constant.

	@constant	kCMImageDescriptionFlavor_ISOFamily
	@abstract	Chooses the ISO family sample description format, used in MP4, M4V, etc.

	@constant	kCMImageDescriptionFlavor_3GPFamily
	@abstract	Chooses the 3GP family sample description format.
	@discussion	This implies kCMImageDescriptionFlavor_ISOFamily and adds additional rules specific to the 3GP family.
*/

CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMImageDescriptionFlavor_QuickTimeMovie	__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// equivalent to NULL
CM_EXPORT const CFStringRef kCMImageDescriptionFlavor_ISOFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// MP4, etc
CM_EXPORT const CFStringRef kCMImageDescriptionFlavor_3GPFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// 3GPP (implies ISO)

CM_ASSUME_NONNULL_END

/*!
	@function	CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionData
	@abstract	Creates a CMVideoFormatDescription from a big-endian ImageDescription data structure.

	@param	allocator						Allocator to use for allocating the CMVideoFormatDescription object. May be NULL.
	@param	imageDescriptionData			ImageDescription data structure in big-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
	@param	imageDescriptionStringEncoding	Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	imageDescriptionFlavor			kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	videoFormatDescriptionOut		Receives new CMVideoFormatDescription.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL imageDescriptionData,
		size_t imageDescriptionSize,
		CFStringEncoding imageDescriptionStringEncoding,
		CFStringRef CM_NULLABLE imageDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMVideoFormatDescriptionRef CM_NULLABLE * CM_NONNULL videoFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionBlockBuffer
	@abstract	Creates a CMVideoFormatDescription from a big-endian ImageDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMVideoFormatDescription object. May be NULL.
	@param	imageDescriptionBlockBuffer		CMBlockBuffer containing ImageDescription data structure in big-endian byte ordering.
	@param	imageDescriptionStringEncoding	Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	imageDescriptionFlavor			kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	videoFormatDescriptionOut		Receives new CMVideoFormatDescription.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCreateFromBigEndianImageDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL imageDescriptionBlockBuffer,
		CFStringEncoding imageDescriptionStringEncoding,
		CFStringRef CM_NULLABLE imageDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMVideoFormatDescriptionRef CM_NULLABLE * CM_NONNULL videoFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMVideoFormatDescriptionCopyAsBigEndianImageDescriptionBlockBuffer
	@abstract	Copies the contents of a CMVideoFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	videoFormatDescription			CMVideoFormatDescription to be copied.
	@param	imageDescriptionStringEncoding	Pass CFStringGetSystemEncoding() or GetApplicationTextEncoding().
	@param	imageDescriptionFlavor			kCMImageDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	imageDescriptionBlockBufferOut	Receives new CMBlockBuffer containing ImageDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMVideoFormatDescriptionCopyAsBigEndianImageDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMVideoFormatDescriptionRef CM_NONNULL videoFormatDescription,
		CFStringEncoding imageDescriptionStringEncoding,
		CFStringRef CM_NULLABLE imageDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL imageDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianImageDescriptionToHost
	@abstract	Converts an ImageDescription data structure from big-endian to host-endian in place.

	@param	imageDescriptionData			ImageDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianImageDescriptionToHost(
		uint8_t * CM_NONNULL imageDescriptionData,
		size_t imageDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianImageDescriptionToBig
	@abstract	Converts an ImageDescription data structure from host-endian to big-endian in place.

	@param	imageDescriptionData			ImageDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	imageDescriptionSize			Size of ImageDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianImageDescriptionToBig(
		uint8_t * CM_NONNULL imageDescriptionData,
		size_t imageDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianImageDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianImageDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	CMAudioFormatDescription and SoundDescription bridge functions
*/

/*!
	@constant	kCMSoundDescriptionFlavor_QuickTimeMovie
	@abstract	Chooses the most backwards-compatible QuickTime Movie Sound Description format.
	@discussion	A V1 sound description will be written if possible.
				If a V1 sound description is written for CBR or PCM audio, the sample tables will need to use the legacy CBR layout.

	@constant	kCMSoundDescriptionFlavor_QuickTimeMovieV2
	@abstract	Chooses the QuickTime Movie Sound Description V2 format.
	@discussion	A V2 sound description will be written.
				V2 Sound Descriptions contain no legacy CBR layout, and use 'lpcm' for all flavors of PCM.

	@constant	kCMSoundDescriptionFlavor_ISOFamily
	@abstract	Chooses the ISO family sample description format, used in MP4, M4A, etc.

	@constant	kCMSoundDescriptionFlavor_3GPFamily
	@abstract	Chooses the 3GP family sample description format.
	@discussion	This implies kCMSoundDescriptionFlavor_ISOFamily and adds additional rules specific to the 3GP family.
*/

CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_QuickTimeMovie	__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// equivalent to NULL
CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_QuickTimeMovieV2	__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_ISOFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// MP4, etc
CM_EXPORT const CFStringRef kCMSoundDescriptionFlavor_3GPFamily			__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);	// 3GPP (implies ISO)

CM_ASSUME_NONNULL_END

/*!
	@function	CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionData
	@abstract	Creates a CMAudioFormatDescription from a big-endian SoundDescription data structure.

	@param	allocator						Allocator to use for allocating the CMAudioFormatDescription object. May be NULL.
	@param	soundDescriptionData			SoundDescription data structure in big-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	audioFormatDescriptionOut		Receives new CMAudioFormatDescription.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionData(
		CM_NULLABLE CFAllocatorRef allocator,
		const uint8_t * CM_NONNULL soundDescriptionData,
		size_t soundDescriptionSize,
		CFStringRef CM_NULLABLE soundDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMAudioFormatDescriptionRef CM_NULLABLE * CM_NONNULL  audioFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionBlockBuffer
	@abstract	Creates a CMAudioFormatDescription from a big-endian SoundDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMAudioFormatDescription object. May be NULL.
	@param	soundDescriptionBlockBuffer		CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	audioFormatDescriptionOut		Receives new CMAudioFormatDescription.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCreateFromBigEndianSoundDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL soundDescriptionBlockBuffer,
		CFStringRef CM_NULLABLE soundDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMAudioFormatDescriptionRef CM_NULLABLE * CM_NONNULL audioFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMAudioFormatDescriptionCopyAsBigEndianSoundDescriptionBlockBuffer
	@abstract	Copies the contents of a CMAudioFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	audioFormatDescription			CMAudioFormatDescription to be copied.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
	@param	soundDescriptionBlockBufferOut	Receives new CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMAudioFormatDescriptionCopyAsBigEndianSoundDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMAudioFormatDescriptionRef CM_NONNULL audioFormatDescription,
		CFStringRef CM_NULLABLE soundDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL soundDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMDoesBigEndianSoundDescriptionRequireLegacyCBRSampleTableLayout
	@abstract	Examine a big-endian SoundDescription data structure in a CMBlockBuffer, and report whether the sample tables will need to use the legacy CBR layout.

	@param	soundDescriptionBlockBuffer		CMBlockBuffer containing SoundDescription data structure in big-endian byte ordering.
	@param	soundDescriptionFlavor			kCMSoundDescriptionFlavor constant or NULL for QuickTimeMovie flavor.
*/
CM_EXPORT Boolean CMDoesBigEndianSoundDescriptionRequireLegacyCBRSampleTableLayout(
		CMBlockBufferRef CM_NONNULL soundDescriptionBlockBuffer,
		CFStringRef CM_NULLABLE soundDescriptionFlavor )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianSoundDescriptionToHost
	@abstract	Converts a SoundDescription data structure from big-endian to host-endian in place.

	@param	soundDescriptionData			SoundDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianSoundDescriptionToHost(
		uint8_t * CM_NONNULL soundDescriptionData,
		size_t soundDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianSoundDescriptionToBig
	@abstract	Converts a SoundDescription data structure from host-endian to big-endian in place.

	@param	soundDescriptionData			SoundDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	soundDescriptionSize			Size of SoundDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianSoundDescriptionToBig(
		uint8_t * CM_NONNULL soundDescriptionData,
		size_t soundDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianSoundDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianSoundDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	CMTextFormatDescription and TextDescription bridge functions
*/

/*!
	@function	CMTextFormatDescriptionCreateFromBigEndianTextDescriptionData
	@abstract	Creates a CMTextFormatDescription from a big-endian TextDescription data structure.

	@param	allocator						Allocator to use for allocating the CMTextFormatDescription object. May be NULL.
	@param	textDescriptionData				TextDescription data structure in big-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
	@param	textDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	mediaType,						Pass kCMMediaType_Text or kCMMediaType_Subtitle.
	@param	textFormatDescriptionOut		Receives new CMTextFormatDescription.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCreateFromBigEndianTextDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL textDescriptionData,
		size_t textDescriptionSize,
		CFStringRef CM_NULLABLE textDescriptionFlavor,
		CMMediaType mediaType,
		CM_RETURNS_RETAINED_PARAMETER CMTextFormatDescriptionRef CM_NULLABLE * CM_NONNULL textFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTextFormatDescriptionCreateFromBigEndianTextDescriptionBlockBuffer
	@abstract	Creates a CMTextFormatDescription from a big-endian TextDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMTextFormatDescription object. May be NULL.
	@param	textDescriptionBlockBuffer		CMBlockBuffer containing TextDescription data structure in big-endian byte ordering.
	@param	textDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	mediaType,						Pass kCMMediaType_Text or kCMMediaType_Subtitle.
	@param	textFormatDescriptionOut		Receives new CMTextFormatDescription.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCreateFromBigEndianTextDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL textDescriptionBlockBuffer,
		CFStringRef CM_NULLABLE textDescriptionFlavor,
		CMMediaType mediaType,
		CM_RETURNS_RETAINED_PARAMETER CMTextFormatDescriptionRef CM_NULLABLE * CM_NONNULL textFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTextFormatDescriptionCopyAsBigEndianTextDescriptionBlockBuffer
	@abstract	Copies the contents of a CMTextFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator						Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	textFormatDescription			CMTextFormatDescription to be copied.
	@param	textDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	textDescriptionBlockBufferOut	Receives new CMBlockBuffer containing TextDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMTextFormatDescriptionCopyAsBigEndianTextDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTextFormatDescriptionRef CM_NONNULL textFormatDescription,
		CFStringRef CM_NULLABLE textDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL textDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianTextDescriptionToHost
	@abstract	Converts a TextDescription data structure from big-endian to host-endian in place.

	@param	textDescriptionData				TextDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianTextDescriptionToHost(
		uint8_t * CM_NONNULL textDescriptionData,
		size_t textDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianTextDescriptionToBig
	@abstract	Converts a TextDescription data structure from host-endian to big-endian in place.

	@param	textDescriptionData				TextDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	textDescriptionSize				Size of TextDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianTextDescriptionToBig(
		uint8_t * CM_NONNULL textDescriptionData,
		size_t textDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianTextDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianTextDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	CMClosedCaptionFormatDescription and ClosedCaptionDescription bridge functions
*/

/*!
	@function	CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionData
	@abstract	Creates a CMClosedCaptionFormatDescription from a big-endian ClosedCaptionDescription data structure.

	@param	allocator							Allocator to use for allocating the CMClosedCaptionFormatDescription object. May be NULL.
	@param	closedCaptionDescriptionData		ClosedCaptionDescription data structure in big-endian byte ordering.
	@param	closedCaptionDescriptionSize		Size of ClosedCaptionDescription data structure.
	@param	closedCaptionDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	closedCaptionFormatDescriptionOut	Receives new CMClosedCaptionFormatDescription.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize,
		CFStringRef CM_NULLABLE closedCaptionDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMClosedCaptionFormatDescriptionRef CM_NULLABLE * CM_NONNULL closedCaptionFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionBlockBuffer
	@abstract	Creates a CMClosedCaptionFormatDescription from a big-endian ClosedCaptionDescription data structure in a CMBlockBuffer.

	@param	allocator							Allocator to use for allocating the CMClosedCaptionFormatDescription object. May be NULL.
	@param	closedCaptionDescriptionBlockBuffer	CMBlockBuffer containing ClosedCaptionDescription data structure in big-endian byte ordering.
	@param	closedCaptionDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	closedCaptionFormatDescriptionOut	Receives new CMClosedCaptionFormatDescription.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCreateFromBigEndianClosedCaptionDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL closedCaptionDescriptionBlockBuffer,
		CFStringRef CM_NULLABLE closedCaptionDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMClosedCaptionFormatDescriptionRef CM_NULLABLE * CM_NONNULL closedCaptionFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMClosedCaptionFormatDescriptionCopyAsBigEndianClosedCaptionDescriptionBlockBuffer
	@abstract	Copies the contents of a CMClosedCaptionFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator								Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	closedCaptionFormatDescription			CMClosedCaptionFormatDescription to be copied.
	@param	closedCaptionDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	closedCaptionDescriptionBlockBufferOut	Receives new CMBlockBuffer containing ClosedCaptionDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMClosedCaptionFormatDescriptionCopyAsBigEndianClosedCaptionDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMClosedCaptionFormatDescriptionRef CM_NONNULL closedCaptionFormatDescription,
		CFStringRef CM_NULLABLE closedCaptionDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL closedCaptionDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianClosedCaptionDescriptionToHost
	@abstract	Converts a ClosedCaptionDescription data structure from big-endian to host-endian in place.

	@param	closedCaptionDescriptionData	ClosedCaptionDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	closedCaptionDescriptionSize	Size of ClosedCaptionDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianClosedCaptionDescriptionToHost(
		uint8_t * CM_NONNULL closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianClosedCaptionDescriptionToBig
	@abstract	Converts a ClosedCaptionDescription data structure from host-endian to big-endian in place.

	@param	closedCaptionDescriptionData	ClosedCaptionDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	closedCaptionDescriptionSize	Size of ClosedCaptionDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianClosedCaptionDescriptionToBig(
		uint8_t * CM_NONNULL closedCaptionDescriptionData,
		size_t closedCaptionDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianClosedCaptionDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianClosedCaptionDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	CMTimeCodeFormatDescription and TimeCodeDescription bridge functions
*/

/*!
	@function	CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionData
	@abstract	Creates a CMTimeCodeFormatDescription from a big-endian TimeCodeDescription data structure.

	@param	allocator						Allocator to use for allocating the CMTimeCodeFormatDescription object. May be NULL.
	@param	timeCodeDescriptionData			TimeCodeDescription data structure in big-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
	@param	timeCodeDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	timeCodeFormatDescriptionOut	Receives new CMTimeCodeFormatDescription.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL timeCodeDescriptionData,
		size_t timeCodeDescriptionSize, 
		CFStringRef CM_NULLABLE timeCodeDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMTimeCodeFormatDescriptionRef CM_NULLABLE * CM_NONNULL timeCodeFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionBlockBuffer
	@abstract	Creates a CMTimeCodeFormatDescription from a big-endian TimeCodeDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMTimeCodeFormatDescription object. May be NULL.
	@param	timeCodeDescriptionBlockBuffer	CMBlockBuffer containing TimeCodeDescription data structure in big-endian byte ordering.
	@param	timeCodeDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	timeCodeFormatDescriptionOut	Receives new CMTimeCodeFormatDescription.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCreateFromBigEndianTimeCodeDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL timeCodeDescriptionBlockBuffer,
		CFStringRef CM_NULLABLE timeCodeDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMTimeCodeFormatDescriptionRef CM_NULLABLE * CM_NONNULL timeCodeFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMTimeCodeFormatDescriptionCopyAsBigEndianTimeCodeDescriptionBlockBuffer
	@abstract	Copies the contents of a CMTimeCodeFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator							Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	timeCodeFormatDescription			CMTimeCodeFormatDescription to be copied.
	@param	timeCodeDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	timeCodeDescriptionBlockBufferOut	Receives new CMBlockBuffer containing TimeCodeDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMTimeCodeFormatDescriptionCopyAsBigEndianTimeCodeDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMTimeCodeFormatDescriptionRef CM_NONNULL timeCodeFormatDescription,
		CFStringRef CM_NULLABLE timeCodeDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL timeCodeDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianTimeCodeDescriptionToHost
	@abstract	Converts a TimeCodeDescription data structure from big-endian to host-endian in place.

	@param	timeCodeDescriptionData			TimeCodeDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianTimeCodeDescriptionToHost(
		uint8_t * CM_NONNULL timeCodeDescriptionData,
		size_t timeCodeDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianTimeCodeDescriptionToBig
	@abstract	Converts a TimeCodeDescription data structure from host-endian to big-endian in place.

	@param	timeCodeDescriptionData			TimeCodeDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	timeCodeDescriptionSize			Size of TimeCodeDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianTimeCodeDescriptionToBig(
		uint8_t * CM_NONNULL timeCodeDescriptionData,
		size_t timeCodeDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianTimeCodeDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianTimeCodeDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	CMMetadataFormatDescription and MetadataDescription bridge functions
*/

/*!
	@function	CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionData
	@abstract	Creates a CMMetadataFormatDescription from a big-endian MetadataDescription data structure.

	@param	allocator						Allocator to use for allocating the CMMetadataFormatDescription object. May be NULL.
	@param	metadataDescriptionData			MetadataDescription data structure in big-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
	@param	metadataDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	metadataFormatDescriptionOut	Receives new CMMetadataFormatDescriptionRef.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionData(
		CFAllocatorRef CM_NULLABLE allocator,
		const uint8_t * CM_NONNULL metadataDescriptionData,
		size_t metadataDescriptionSize,
		CFStringRef CM_NULLABLE metadataDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL metadataFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionBlockBuffer
	@abstract	Creates a CMMetadataFormatDescription from a big-endian MetadataDescription data structure in a CMBlockBuffer.

	@param	allocator						Allocator to use for allocating the CMMetadataFormatDescription object. May be NULL.
	@param	metadataDescriptionBlockBuffer	CMBlockBuffer containing MetadataDescription data structure in big-endian byte ordering.
	@param	metadataDescriptionFlavor		Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	metadataFormatDescriptionOut	Receives new CMMetadataFormatDescriptionRef.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCreateFromBigEndianMetadataDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMBlockBufferRef CM_NONNULL metadataDescriptionBlockBuffer,
		CFStringRef CM_NULLABLE metadataDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMMetadataFormatDescriptionRef CM_NULLABLE * CM_NONNULL metadataFormatDescriptionOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataFormatDescriptionCopyAsBigEndianMetadataDescriptionBlockBuffer
	@abstract	Copies the contents of a CMMetadataFormatDescription to a CMBlockBuffer in big-endian byte ordering.
	@discussion	On return, the caller owns the returned CMBlockBuffer, and must release it when done with it.
                Note that the dataRefIndex field of the SampleDescription is intentionally filled with
                garbage values (0xFFFF).  The caller must overwrite these values with a valid dataRefIndex
                if writing the SampleDescription to a QuickTime/ISO file.

	@param	allocator							Allocator to use for allocating the CMBlockBuffer object. May be NULL.
	@param	metadataFormatDescription			CMMetadataFormatDescriptionRef to be copied.
	@param	metadataDescriptionFlavor			Reserved for future use. Pass NULL for QuickTime Movie or ISO flavor.
	@param	metadataDescriptionBlockBufferOut	Receives new CMBlockBuffer containing MetadataDescription data structure in big-endian byte ordering.
*/
CM_EXPORT OSStatus CMMetadataFormatDescriptionCopyAsBigEndianMetadataDescriptionBlockBuffer(
		CFAllocatorRef CM_NULLABLE allocator,
		CMMetadataFormatDescriptionRef CM_NONNULL metadataFormatDescription,
		CFStringRef CM_NULLABLE metadataDescriptionFlavor,
		CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NONNULL metadataDescriptionBlockBufferOut )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CF_IMPLICIT_BRIDGING_ENABLED

#if TARGET_RT_LITTLE_ENDIAN

/*!
	@function	CMSwapBigEndianMetadataDescriptionToHost
	@abstract	Converts a MetadataDescription data structure from big-endian to host-endian in place.

	@param	metadataDescriptionData			MetadataDescription data structure in big-endian byte ordering to be converted to host-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
*/
CM_EXPORT OSStatus CMSwapBigEndianMetadataDescriptionToHost(
		uint8_t * CM_NONNULL metadataDescriptionData,
		size_t metadataDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSwapHostEndianMetadataDescriptionToBig
	@abstract	Converts a MetadataDescription data structure from host-endian to big-endian in place.

	@param	metadataDescriptionData			MetadataDescription data structure in host-endian byte ordering to be converted to big-endian byte ordering.
	@param	metadataDescriptionSize			Size of MetadataDescription data structure.
*/
CM_EXPORT OSStatus CMSwapHostEndianMetadataDescriptionToBig(
		uint8_t * CM_NONNULL metadataDescriptionData,
		size_t metadataDescriptionSize )
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

#else // TARGET_RT_BIG_ENDIAN

#define CMSwapBigEndianMetadataDescriptionToHost(d,s) (noErr)
#define CMSwapHostEndianMetadataDescriptionToBig(d,s) (noErr)

#endif // TARGET_RT_BIG_ENDIAN

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // CMFORMATDESCRIPTIONBRIDGE_H
// ==========  CoreMedia.framework/Headers/CMSampleBuffer.h
/*
    File:  CMSampleBuffer.h
	
	Framework:  CoreMedia
 
    Copyright 2005-2015 Apple Inc. All rights reserved.
 
*/

#ifndef CMSAMPLEBUFFER_H
#define CMSAMPLEBUFFER_H

/*!
	@header
	@abstract	API for creating and manipulating CMSampleBuffers.
	@discussion	CMSampleBuffers are CF objects containing zero or more compressed (or uncompressed)
				samples of a particular media type (audio, video, muxed, etc), that are used to move
				media sample data through the media system.
				
				A CMSampleBuffer can contain a CMBlockBuffer of one or more media samples or a CVImageBuffer,
				a reference to the format description for the stream of CMSampleBuffers, size and timing
				information for each of the contained media samples, and both buffer-level and sample-level
				attachments.  The buffer-level attachments of a CMSampleBuffer are distinct from the attachments
				of its contained CMBlockBuffer. An example of a sample-level attachment is an annotation about
				video frame dependencies (eg. "droppable", "other frames depend on me", "I depend on other frames", etc).
				Each sample (video frame) in the CMSampleBuffer would need its own attachment in this case.
				Another sample-level attachment example is SMPTE timecode acquired during capture. To get and
				set a CMSampleBuffer's buffer-level attachments, use the APIs in in CMAttachmentBearer.h
				(CMGetAttachment et al).

				It is possible for a CMSampleBuffer to describe samples it does not yet contain. For example, 
				some media services may have access to sample size, timing and format information before the
				data is read. Such services may create CMSampleBuffers with that information and insert them
				into queues early, and attach (or fill) the CMBlockBuffers of media data later, when the
				data becomes ready.  To this end, CMSampleBuffers have the concept of data-readiness, which can
				be tested, set, forced to become ready "now", etc.
				
				It is also possible for a CMSampleBuffer to contain nothing but a special buffer-level
				attachment that describes a media stream event (eg. "discontinuity: drain and reset decoder
				before processing the next CMSampleBuffer").  Such a special attachment can also be attached
				to regular CMSampleBuffers (ie. that contain media sample data), and if so, the event it
				describes is defined to occur after the samples in that CMSampleBuffer.

				IMPORTANT: Clients of CMSampleBuffer must explicitly manage the retain count by 
				calling CFRetain and CFRelease, even in processes using garbage collection.  

				Objective-C code that may run under garbage collection should NOT use [sbuf retain],
				or [sbuf release]; these will not have the correct effect.
*/

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>

#include <CoreMedia/CMTime.h>
#include <CoreMedia/CMBlockBuffer.h>
#include <CoreMedia/CMFormatDescription.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@enum CMSampleBuffer Errors
	@discussion The errors returned from the CMSampleBuffer APIs
	@constant	kCMSampleBufferError_AllocationFailed An allocation failed.
	@constant	kCMSampleBufferError_RequiredParameterMissing NULL or 0 was passed for a required parameter.
	@constant	kCMSampleBufferError_AlreadyHasDataBuffer Attempt was made to set a dataBuffer on a CMSampleBuffer that already has one.
	@constant   kCMSampleBufferError_BufferNotReady Buffer could not be made ready.
	@constant   kCMSampleBufferError_SampleIndexOutOfRange Sample index was not between 0 and numSamples-1, inclusive.
	@constant   kCMSampleBufferError_BufferHasNoSampleSizes Attempt to get sample size information when there was none.
	@constant   kCMSampleBufferError_BufferHasNoSampleTimingInfo Attempt to get sample timing information when there was none.
	@constant   kCMSampleBufferError_ArrayTooSmall Output array was not large enough for the array being requested.
	@constant   kCMSampleBufferError_InvalidEntryCount Timing info or size array entry count was not 0, 1, or numSamples.
	@constant	kCMSampleBufferError_CannotSubdivide Sample buffer does not contain sample sizes.  This can happen when the samples in the buffer are non-contiguous (eg. non-interleaved audio, where the channel values for a single sample are scattered through the buffer).
    @constant   kCMSampleBufferError_SampleTimingInfoInvalid buffer unexpectedly contains a non-numeric sample timing info
    @constant   kCMSampleBufferError_InvalidMediaTypeForOperation the media type specified by a format description is not valid for the given operation (eg. a CMSampleBuffer with a non-audio format description passed to CMSampleBufferGetAudioStreamPacketDescriptionsPtr).
	@constant	kCMSampleBufferError_InvalidSampleData Buffer contains bad data. Only returned by CMSampleBuffer functions that inspect its sample data.
    @constant   kCMSampleBufferError_InvalidMediaFormat the format of the given media does not match the given format description (eg. a format description paired with a CVImageBuffer that fails CMVideoFormatDescriptionMatchesImageBuffer).
	@constant	kCMSampleBufferError_Invalidated the sample buffer was invalidated.
	@constant	kCMSampleBufferError_DataFailed the sample buffer's data loading operation failed (generic error).
	@constant	kCMSampleBufferError_DataCanceled the sample buffer's data loading operation was canceled.
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMSampleBufferError_AllocationFailed				= -12730,
	kCMSampleBufferError_RequiredParameterMissing		= -12731,
	kCMSampleBufferError_AlreadyHasDataBuffer			= -12732,
	kCMSampleBufferError_BufferNotReady					= -12733,
	kCMSampleBufferError_SampleIndexOutOfRange			= -12734,
	kCMSampleBufferError_BufferHasNoSampleSizes			= -12735,
	kCMSampleBufferError_BufferHasNoSampleTimingInfo	= -12736,
	kCMSampleBufferError_ArrayTooSmall					= -12737,
	kCMSampleBufferError_InvalidEntryCount				= -12738,
	kCMSampleBufferError_CannotSubdivide				= -12739,
    kCMSampleBufferError_SampleTimingInfoInvalid      	= -12740,
    kCMSampleBufferError_InvalidMediaTypeForOperation	= -12741,
	kCMSampleBufferError_InvalidSampleData				= -12742,
    kCMSampleBufferError_InvalidMediaFormat				= -12743,
	kCMSampleBufferError_Invalidated					= -12744,
	kCMSampleBufferError_DataFailed						= -16750,
	kCMSampleBufferError_DataCanceled					= -16751,
};

/*!
	@enum CMSampleBuffer Flags
	@discussion Flags passed to various CMSampleBuffer APIs
	@constant	kCMSampleBufferFlag_AudioBufferList_Assure16ByteAlignment Make sure memory involved in audio buffer lists is 16-byte aligned
*/
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : uint32_t
#else
enum
#endif
{
	kCMSampleBufferFlag_AudioBufferList_Assure16ByteAlignment		= (1L<<0)
};

/*!
	@typedef	CMSampleBufferRef
	@abstract	A reference to a CMSampleBuffer, a CF object containing zero or more compressed (or uncompressed)
				samples of a particular media type (audio, video, muxed, etc).
		
*/
typedef struct CM_BRIDGED_TYPE(id) opaqueCMSampleBuffer *CMSampleBufferRef;

/*!
	@typedef	CMSampleTimingInfo
	@abstract	Collection of timing info for a sample in a CMSampleBuffer. A single CMSampleTimingInfo struct can
				describe every individual sample in a CMSampleBuffer, if the samples all have the same duration and
				are in presentation order with no gaps.
*/
typedef struct
{
	CMTime duration;				/*! @field duration
										The duration of the sample. If a single struct applies to
										each of the samples, they all will have this duration. */
	CMTime presentationTimeStamp;	/*! @field presentationTimeStamp
										The time at which the sample will be presented. If a single
										struct applies to each of the samples, this is the presentationTime of the
										first sample. The presentationTime of subsequent samples will be derived by
										repeatedly adding the sample duration. */
	CMTime decodeTimeStamp;			/*! @field decodeTimeStamp
										The time at which the sample will be decoded. If the samples
										are in presentation order, this must be set to kCMTimeInvalid. */
} CMSampleTimingInfo;

CM_EXPORT const CMSampleTimingInfo kCMTimingInfoInvalid		/*! @constant kCMTimingInfoInvalid
																Use this constant to initialize an invalid CMSampleTimingInfo struct.
																All fields are set to kCMTimeInvalid */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@typedef	CMSampleBufferMakeDataReadyCallback
	@abstract	Client callback called by CMSampleBufferMakeDataReady (client provides it when calling CMSampleBufferCreate).
	@discussion	This callback must make the data ready (e.g. force a scheduled read to finish). If this callback
				succeeds and returns 0, the CMSampleBuffer will then be marked as "data ready".
*/
typedef OSStatus (*CMSampleBufferMakeDataReadyCallback)
	(CMSampleBufferRef CM_NONNULL sbuf,	/*! @param sbuf
											The CMSampleBuffer to make ready. */
	void * CM_NULLABLE makeDataReadyRefcon);	/*! @param makeDataReadyRefcon
												Client refcon provided to CMSampleBufferCreate.
												For example, it could point at info about the
												scheduled read that needs to be forced to finish. */

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	Object management functions
*/

/*!
	@function	CMSampleBufferCreate
	@abstract	Creates a CMSampleBuffer.
	@discussion	Array parameters (sampleSizeArray, sampleTimingArray) should have only one element if that same
				element applies to all samples. All parameters are copied; on return, the caller can release them,
				free them, reuse them or whatever.  On return, the caller owns the returned CMSampleBuffer, and
				must release it when done with it.
				
				Example of usage for in-display-order video frames:
<ul>				dataBuffer: contains 7 Motion JPEG frames
<li>				dataFormatDescription: describes Motion JPEG video
<li>				numSamples: 7
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {duration = 1001/30000, presentationTimeStamp = 0/30000, decodeTimeStamp = invalid }
<li>				numSampleSizeEntries: 7
<li>				sampleSizeArray: {105840, 104456, 103464, 116460, 100412, 94808, 120400}
</ul>
				Example of usage for out-of-display-order video frames:
<ul>				dataBuffer: contains 6 H.264 frames in decode order (P2,B0,B1,I5,B3,B4)
<li>				dataFormatDescription: describes H.264 video
<li>				numSamples: 6
<li>				numSampleTimingEntries: 6
<li>				sampleTimingArray: 6 entries = {
<ul>					{duration = 1001/30000, presentationTimeStamp = 12012/30000, decodeTimeStamp = 10010/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 10010/30000, decodeTimeStamp = 11011/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 11011/30000, decodeTimeStamp = 12012/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 15015/30000, decodeTimeStamp = 13013/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 13013/30000, decodeTimeStamp = 14014/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 14014/30000, decodeTimeStamp = 15015/30000}}
</ul>
<li>				numSampleSizeEntries: 6
<li>				sampleSizeArray: {10580, 1234, 1364, 75660, 1012, 988}
</ul>
				Example of usage for compressed audio:
<ul>				dataBuffer: contains 24 compressed AAC packets
<li>				dataFormatDescription: describes 44.1kHz AAC audio
<li>				numSamples: 24
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {
<ul>					{duration = 1024/44100, presentationTimeStamp = 0/44100, decodeTimeStamp = invalid }}
</ul>
<li>				numSampleSizeEntries: 24
<li>				sampleSizeArray:
<ul>					{191, 183, 208, 213, 202, 206, 209, 206, 204, 192, 202, 277,
<li>					 282, 240, 209, 194, 193, 197, 196, 198, 168, 199, 171, 194}
</ul>
</ul>
				Example of usage for uncompressed interleaved audio:
<ul>				dataBuffer: contains 24000 uncompressed interleaved stereo frames, each containing 2 Float32s =
<ul>					{{L,R},
<li>					 {L,R},
<li>					 {L,R}, ...}
</ul>
<li>				dataFormatDescription: describes 48kHz Float32 interleaved audio
<li>				numSamples: 24000
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {
<ul>					{duration = 1/48000, presentationTimeStamp = 0/48000, decodeTimeStamp = invalid }}
</ul>
<li>				numSampleSizeEntries: 1
<li>				sampleSizeArray: {8}
</ul>
				Example of usage for uncompressed non-interleaved audio:
<ul>				dataBuffer: contains 24000 uncompressed non-interleaved stereo frames, each containing 2 (non-contiguous) Float32s =
<ul>					{{L,L,L,L,L,...},
<li>					 {R,R,R,R,R,...}}
</ul>
<li>				dataFormatDescription: describes 48kHz Float32 non-interleaved audio
<li>				numSamples: 24000
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {duration = 1/48000, presentationTimeStamp = 0/48000, decodeTimeStamp = invalid }
<li>				numSampleSizeEntries: 0
<li>				sampleSizeArray: NULL (because the samples are not contiguous)
</ul>
*/
CM_EXPORT
OSStatus CMSampleBufferCreate(
	CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
																The allocator to use for allocating the CMSampleBuffer object.
																Pass kCFAllocatorDefault to use the default allocator. */
	CMBlockBufferRef CM_NULLABLE dataBuffer,				/*! @param dataBuffer
																CMBlockBuffer for the media data. This can be NULL, a CMBlockBuffer with
																no backing memory, a CMBlockBuffer with backing memory but no data yet,
																or a CMBlockBuffer that already contains the media data. Only in that
																last case (or if NULL and numSamples is 0) should dataReady be true. */
	Boolean dataReady,										/*! @param dataReady
																Indicates whether or not the BlockBuffer already contains the media data. */
	CMSampleBufferMakeDataReadyCallback CM_NULLABLE makeDataReadyCallback,
															/*! @param makeDataReadyCallback
																Callback that CMSampleBufferMakeDataReady should call to make the
																data ready. Can be NULL. */
	void * CM_NULLABLE makeDataReadyRefcon,					/*! @param makeDataReadyRefcon
																Refcon CMSampleBufferMakeDataReady should pass to the callback. */
	CMFormatDescriptionRef CM_NULLABLE formatDescription,	/*! @param formatDescription
																A description of the media data's format. Can be NULL. */
	CMItemCount numSamples,									/*! @param numSamples
																Number of samples in the CMSampleBuffer. Can be 0. */
	CMItemCount numSampleTimingEntries,						/*! @param numSampleTimingEntries
																Number of entries in sampleTimingArray. Must be 0, 1, or numSamples. */
	const CMSampleTimingInfo * CM_NULLABLE sampleTimingArray,	/*! @param sampleTimingArray
																Array of CMSampleTimingInfo structs, one struct per sample.
																If all samples have the same duration and are in presentation order, you can pass a single
																CMSampleTimingInfo struct with duration set to the duration of one sample, presentationTimeStamp
																set to the presentation time of the numerically earliest sample, and decodeTimeStamp set to
																kCMTimeInvalid. Behaviour is undefined if samples in a CMSampleBuffer (or even in multiple
																buffers in the same stream) have the same presentationTimeStamp. Can be NULL. */
	CMItemCount numSampleSizeEntries,						/*! @param numSampleSizeEntries
																Number of entries in sampleSizeArray. Must be 0, 1, or numSamples. */
	const size_t * CM_NULLABLE sampleSizeArray,				/*! @param sampleSizeArray
																Array of size entries, one entry per sample. If all samples have the
																same size, you can pass a single size entry containing the size of one sample. Can be NULL. Must be
																NULL if the samples are non-contiguous in the buffer (eg. non-interleaved audio, where the channel
																values for a single sample are scattered through the buffer). */
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)		/*! @param sBufOut
																Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferCreateReady
	@abstract	Creates a CMSampleBuffer.
	@discussion	Array parameters (sampleSizeArray, sampleTimingArray) should have only one element if that same
				element applies to all samples. All parameters are copied; on return, the caller can release them,
				free them, reuse them or whatever.  On return, the caller owns the returned CMSampleBuffer, and
				must release it when done with it.
				CMSampleBufferCreateReady is identical to CMSampleBufferCreate except that dataReady is always true,
				and so no makeDataReadyCallback or refcon needs to be passed.
				
				Example of usage for in-display-order video frames:
<ul>				dataBuffer: contains 7 Motion JPEG frames
<li>				dataFormatDescription: describes Motion JPEG video
<li>				numSamples: 7
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {duration = 1001/30000, presentationTimeStamp = 0/30000, decodeTimeStamp = invalid }
<li>				numSampleSizeEntries: 7
<li>				sampleSizeArray: {105840, 104456, 103464, 116460, 100412, 94808, 120400}
</ul>
				Example of usage for out-of-display-order video frames:
<ul>				dataBuffer: contains 6 H.264 frames in decode order (P2,B0,B1,I5,B3,B4)
<li>				dataFormatDescription: describes H.264 video
<li>				numSamples: 6
<li>				numSampleTimingEntries: 6
<li>				sampleTimingArray: 6 entries = {
<ul>					{duration = 1001/30000, presentationTimeStamp = 12012/30000, decodeTimeStamp = 10010/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 10010/30000, decodeTimeStamp = 11011/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 11011/30000, decodeTimeStamp = 12012/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 15015/30000, decodeTimeStamp = 13013/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 13013/30000, decodeTimeStamp = 14014/30000},
<li>					{duration = 1001/30000, presentationTimeStamp = 14014/30000, decodeTimeStamp = 15015/30000}}
</ul>
<li>				numSampleSizeEntries: 6
<li>				sampleSizeArray: {10580, 1234, 1364, 75660, 1012, 988}
</ul>
				Example of usage for compressed audio:
<ul>				dataBuffer: contains 24 compressed AAC packets
<li>				dataFormatDescription: describes 44.1kHz AAC audio
<li>				numSamples: 24
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {
<ul>					{duration = 1024/44100, presentationTimeStamp = 0/44100, decodeTimeStamp = invalid }}
</ul>
<li>				numSampleSizeEntries: 24
<li>				sampleSizeArray:
<ul>					{191, 183, 208, 213, 202, 206, 209, 206, 204, 192, 202, 277,
<li>					 282, 240, 209, 194, 193, 197, 196, 198, 168, 199, 171, 194}
</ul>
</ul>
				Example of usage for uncompressed interleaved audio:
<ul>				dataBuffer: contains 24000 uncompressed interleaved stereo frames, each containing 2 Float32s =
<ul>					{{L,R},
<li>					 {L,R},
<li>					 {L,R}, ...}
</ul>
<li>				dataFormatDescription: describes 48kHz Float32 interleaved audio
<li>				numSamples: 24000
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {
<ul>					{duration = 1/48000, presentationTimeStamp = 0/48000, decodeTimeStamp = invalid }}
</ul>
<li>				numSampleSizeEntries: 1
<li>				sampleSizeArray: {8}
</ul>
				Example of usage for uncompressed non-interleaved audio:
<ul>				dataBuffer: contains 24000 uncompressed non-interleaved stereo frames, each containing 2 (non-contiguous) Float32s =
<ul>					{{L,L,L,L,L,...},
<li>					 {R,R,R,R,R,...}}
</ul>
<li>				dataFormatDescription: describes 48kHz Float32 non-interleaved audio
<li>				numSamples: 24000
<li>				numSampleTimingEntries: 1
<li>				sampleTimingArray: one entry = {duration = 1/48000, presentationTimeStamp = 0/48000, decodeTimeStamp = invalid }
<li>				numSampleSizeEntries: 0
<li>				sampleSizeArray: NULL (because the samples are not contiguous)
</ul>
*/
CM_EXPORT
OSStatus CMSampleBufferCreateReady(
	CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
																The allocator to use for allocating the CMSampleBuffer object.
																Pass kCFAllocatorDefault to use the default allocator. */
	CMBlockBufferRef CM_NULLABLE dataBuffer,					/*! @param dataBuffer
																CMBlockBuffer that already contains the media data. Must not be NULL. */
	CMFormatDescriptionRef CM_NULLABLE formatDescription,	/*! @param formatDescription
																A description of the media data's format. Can be NULL. */
	CMItemCount numSamples,									/*! @param numSamples
																Number of samples in the CMSampleBuffer. Can be 0. */
	CMItemCount numSampleTimingEntries,						/*! @param numSampleTimingEntries
																Number of entries in sampleTimingArray. Must be 0, 1, or numSamples. */
	const CMSampleTimingInfo * CM_NULLABLE sampleTimingArray,/*! @param sampleTimingArray
																Array of CMSampleTimingInfo structs, one struct per sample.
																If all samples have the same duration and are in presentation order, you can pass a single
																CMSampleTimingInfo struct with duration set to the duration of one sample, presentationTimeStamp
																set to the presentation time of the numerically earliest sample, and decodeTimeStamp set to
																kCMTimeInvalid. Behaviour is undefined if samples in a CMSampleBuffer (or even in multiple
																buffers in the same stream) have the same presentationTimeStamp. Can be NULL. */
	CMItemCount numSampleSizeEntries,						/*! @param numSampleSizeEntries
																Number of entries in sampleSizeArray. Must be 0, 1, or numSamples. */
	const size_t * CM_NULLABLE sampleSizeArray,				/*! @param sampleSizeArray
																Array of size entries, one entry per sample. If all samples have the
																same size, you can pass a single size entry containing the size of one sample. Can be NULL. Must be
																NULL if the samples are non-contiguous in the buffer (eg. non-interleaved audio, where the channel
																values for a single sample are scattered through the buffer). */
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)		/*! @param sBufOut
																Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMAudioSampleBufferCreateWithPacketDescriptions
	@abstract	Creates an CMSampleBuffer containing audio given packetDescriptions instead of sizing and timing info
	@discussion	Provides an optimization over CMSampleBufferCreate() when the caller already has packetDescriptions for
				the audio data. This routine will use the packetDescriptions to create the sizing and timing arrays required
				to make the sample buffer if necessary.
*/				
CM_EXPORT
OSStatus CMAudioSampleBufferCreateWithPacketDescriptions(
	CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
																The allocator to use for allocating the CMSampleBuffer object.
																Pass kCFAllocatorDefault to use the default allocator. */
	CMBlockBufferRef CM_NULLABLE dataBuffer,				/*! @param dataBuffer
																CMBlockBuffer for the media data. This can be NULL, a CMBlockBuffer with
																no backing memory, a CMBlockBuffer with backing memory but no data yet,
																or a CMBlockBuffer that already contains the media data. Only in that
																last case should dataReady be true. */
	Boolean dataReady,										/*! @param dataReady
																Indicates whether or not the BlockBuffer already contains the media data. */
	CMSampleBufferMakeDataReadyCallback CM_NULLABLE makeDataReadyCallback,
															/*! @param makeDataReadyCallback
																Callback that CMSampleBufferMakeDataReady should call to make the
																data ready. Can be NULL. */
	void * CM_NULLABLE makeDataReadyRefcon,					/*! @param makeDataReadyRefcon
																Refcon CMSampleBufferMakeDataReady should pass to the callback. */
	CMFormatDescriptionRef CM_NONNULL formatDescription,	/*! @param formatDescription
																A description of the media data's format. Cannot be NULL. */
	CMItemCount numSamples,									/*! @param numSamples
																Number of samples in the CMSampleBuffer. Must not be 0. */
	CMTime	sbufPTS,										/*! @param sbufPTS
																Timestamp of the first sample in the buffer. Must be a numeric CMTime. */
	const AudioStreamPacketDescription * CM_NULLABLE packetDescriptions,	/*! @param packetDescriptions
																Array of packetDescriptions, one for each of numSamples. May be NULL
																if the samples are known to have a constant number of frames per
																packet and a constant size. */
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)		/*! @param sBufOut
																Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMAudioSampleBufferCreateReadyWithPacketDescriptions
	@abstract	Creates an CMSampleBuffer containing audio given packetDescriptions instead of sizing and timing info
	@discussion	Provides an optimization over CMSampleBufferCreate() when the caller already has packetDescriptions for
				the audio data. This routine will use the packetDescriptions to create the sizing and timing arrays required
				to make the sample buffer if necessary.
				CMAudioSampleBufferCreateReadyWithPacketDescriptions is identical to CMAudioSampleBufferCreateWithPacketDescriptions 
				except that dataReady is always true, and so no makeDataReadyCallback or refcon needs to be passed.
*/				
CM_EXPORT
OSStatus CMAudioSampleBufferCreateReadyWithPacketDescriptions(
	CFAllocatorRef CM_NULLABLE allocator,								/*! @param allocator
																			The allocator to use for allocating the CMSampleBuffer object.
																			Pass kCFAllocatorDefault to use the default allocator. */
	CMBlockBufferRef CM_NULLABLE dataBuffer,							/*! @param dataBuffer
																			CMBlockBuffer already containing the media data. Must not be NULL. */
	CMFormatDescriptionRef CM_NONNULL formatDescription,				/*! @param formatDescription
																			A description of the media data's format. Cannot be NULL. */
	CMItemCount numSamples,												/*! @param numSamples
																			Number of samples in the CMSampleBuffer. Must not be 0. */
	CMTime	sbufPTS,													/*! @param sbufPTS
																			Timestamp of the first sample in the buffer. Must be a numeric CMTime. */
	const AudioStreamPacketDescription * CM_NULLABLE packetDescriptions,/*! @param packetDescriptions
																			Array of packetDescriptions, one for each of numSamples. May be NULL
																			if the samples are known to have a constant number of frames per
																			packet and a constant size. */
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)					/*! @param sBufOut
																			Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSampleBufferCreateForImageBuffer
	@abstract	Creates a CMSampleBuffer that contains a CVImageBuffer instead of a CMBlockBuffer.
	@discussion	Unlike a CMBlockBuffer which can reference many samples, a CVImageBuffer is defined to
				reference only one sample;  therefore this routine has fewer parameters then
				CMSampleBufferCreate.
				
				Sample timing information, which is a vector for CMSampleBufferCreate,
				consists of only one value for this routine.
				
				The concept of sample size does not apply to CVImageBuffers.  As such, CMSampleBufferGetSampleSizeArray
				will return kCMSampleBufferError_BufferHasNoSampleSizes, and CMSampleBufferGetSampleSize
				will return 0.
				
				Because CVImageBuffers hold visual data, the format description provided is a
				CMVideoFormatDescription.  The format description must be consistent with the attributes
				and formatting information attached to the CVImageBuffer. The width, height, and codecType must
				match (for CVPixelBuffers the codec type is given by CVPixelBufferGetPixelFormatType(pixelBuffer);
				for other CVImageBuffers, the codecType must be 0). The format description extensions must
				match the image buffer attachments for all the keys in the list returned by
				CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers (if absent in either they
				must be absent in both).
*/
CM_EXPORT
OSStatus CMSampleBufferCreateForImageBuffer(
	CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
																The allocator to use for allocating the CMSampleBuffer object.
																Pass kCFAllocatorDefault to use the default allocator. */
	CVImageBufferRef CM_NONNULL imageBuffer,				/*! @param imageBuffer
																CVImageBuffer for the media data. This can be a CVImageBuffer whose content
																has not yet been rendered, or a CVImageBuffer that already contains the media data
																(in which case dataReady should be true).  May not be NULL. */
	Boolean dataReady,										/*! @param dataReady
																Indicates whether or not the CVImageBuffer already contains the media data. */
	CMSampleBufferMakeDataReadyCallback CM_NULLABLE makeDataReadyCallback,
															/*! @param makeDataReadyCallback
																Callback that CMSampleBufferMakeDataReady should call to make the
																data ready. Can be NULL. */
	void * CM_NULLABLE makeDataReadyRefcon,					/*! @param makeDataReadyRefcon
																Refcon CMSampleBufferMakeDataReady should pass to the callback. */
	CMVideoFormatDescriptionRef CM_NONNULL formatDescription,/*! @param formatDescription
																A description of the media data's format. See discussion above for constraints.
																May not be NULL. */
	const CMSampleTimingInfo * CM_NONNULL sampleTiming,		/*! @param sampleTiming
																A CMSampleTimingInfo struct that provides the timing information for the media
																represented by the CVImageBuffer. */
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)		/*! @param sBufOut
																Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferCreateReadyWithImageBuffer
	@abstract	Creates a CMSampleBuffer that contains a CVImageBuffer instead of a CMBlockBuffer.
	@discussion	Unlike a CMBlockBuffer which can reference many samples, a CVImageBuffer is defined to
				reference only one sample;  therefore this routine has fewer parameters then
				CMSampleBufferCreate.
				
				Sample timing information, which is a vector for CMSampleBufferCreate,
				consists of only one value for this routine.
				
				The concept of sample size does not apply to CVImageBuffers.  As such, CMSampleBufferGetSampleSizeArray
				will return kCMSampleBufferError_BufferHasNoSampleSizes, and CMSampleBufferGetSampleSize
				will return 0.
				
				Because CVImageBuffers hold visual data, the format description provided is a
				CMVideoFormatDescription.  The format description must be consistent with the attributes
				and formatting information attached to the CVImageBuffer. The width, height, and codecType must
				match (for CVPixelBuffers the codec type is given by CVPixelBufferGetPixelFormatType(pixelBuffer);
				for other CVImageBuffers, the codecType must be 0). The format description extensions must
				match the image buffer attachments for all the keys in the list returned by
				CMVideoFormatDescriptionGetExtensionKeysCommonWithImageBuffers (if absent in either they
				must be absent in both).
				
				CMSampleBufferCreateReadyWithImageBuffer is identical to CMSampleBufferCreateForImageBuffer except that 
				dataReady is always true, and so no makeDataReadyCallback or refcon needs to be passed.
*/
CM_EXPORT
OSStatus CMSampleBufferCreateReadyWithImageBuffer(
	CFAllocatorRef CM_NULLABLE allocator,						/*! @param allocator
																	The allocator to use for allocating the CMSampleBuffer object.
																	Pass kCFAllocatorDefault to use the default allocator. */
	CVImageBufferRef CM_NONNULL imageBuffer,					/*! @param imageBuffer
																	CVImageBuffer already containing the media data. Must not be NULL. */
	CMVideoFormatDescriptionRef CM_NONNULL formatDescription,	/*! @param formatDescription
																	A description of the media data's format. See discussion above for constraints.
																	May not be NULL. */
	const CMSampleTimingInfo * CM_NONNULL sampleTiming,			/*! @param sampleTiming
																	A CMSampleTimingInfo struct that provides the timing information for the media
																	represented by the CVImageBuffer. */
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)			/*! @param sBufOut
																	Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);


/*!
	@function	CMSampleBufferCreateCopy
	@abstract	Creates a copy of a CMSampleBuffer.
	@discussion	The copy is shallow: scalar properties (sizes and timing) are copied directly,
				the data buffer and format description are retained, and
				the propogatable attachments are retained by the copy's dictionary.
				If sbuf's data is not ready, the copy will be set to track its readiness.
*/
CM_EXPORT
OSStatus CMSampleBufferCreateCopy(
	CFAllocatorRef CM_NULLABLE allocator,						/*! @param allocator
																	The allocator to use for allocating the CMSampleBuffer object.
																	Pass kCFAllocatorDefault to use the default allocator. */
	CMSampleBufferRef CM_NONNULL sbuf,							/*! @param sbuf
																	CMSampleBuffer being copied. */
	CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sbufCopyOut)		/*! @param sbufCopyOut
																	Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferCreateCopyWithNewTiming
	@abstract	Creates a CMSampleBuffer with new timing information from another sample buffer.
	@discussion	This emulates CMSampleBufferCreateCopy, but changes the timing.
				Array parameters (sampleTimingArray) should have only one element if that same
				element applies to all samples. All parameters are copied; on return, the caller can release them,
				free them, reuse them or whatever.  Any outputPresentationTimestamp that has been set on the original Buffer
				will not be copied because it is no longer relevant.	On return, the caller owns the returned 
				CMSampleBuffer, and must release it when done with it.
 
 */				
CM_EXPORT
OSStatus CMSampleBufferCreateCopyWithNewTiming(
  CFAllocatorRef CM_NULLABLE allocator,						/*! @param allocator
																The allocator to use for allocating the CMSampleBuffer object.
																Pass kCFAllocatorDefault to use the default allocator. */
  CMSampleBufferRef CM_NONNULL originalSBuf,            	/*!  @param originalSBuf
																CMSampleBuffer containing the original samples */
											  
  CMItemCount numSampleTimingEntries,						/*! @param numSampleTimingEntries
																Number of entries in sampleTimingArray. Must be 0, 1, or numSamples
																in original sampleBuffer. */
  const CMSampleTimingInfo * CM_NULLABLE sampleTimingArray,	/*! @param sampleTimingArray
																Array of CMSampleTimingInfo structs, one struct per sample.
																If all samples have the same duration and are in presentation order, you can pass a single
																CMSampleTimingInfo struct with duration set to the duration of one sample, presentationTimeStamp
																set to the presentation time of the numerically earliest sample, and decodeTimeStamp set to
																kCMTimeInvalid. Behaviour is undefined if samples in a CMSampleBuffer (or even in multiple
																buffers in the same stream) have the same presentationTimeStamp. Can be NULL. */
  CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufCopyOut)	/*! @param sBufCopyOut
																Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
	
/*!
	@function	CMSampleBufferCopySampleBufferForRange
	@abstract	Creates a CMSampleBuffer containing a range of samples from an existing CMSampleBuffer.
	@discussion	Samples containing non-interleaved audio are currently not supported.
 */				
CM_EXPORT
OSStatus CMSampleBufferCopySampleBufferForRange(
  CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
															The allocator to use for allocating the CMSampleBuffer object.
															Pass kCFAllocatorDefault to use the default allocator. */
  CMSampleBufferRef CM_NONNULL sbuf,					/*! @param sbuf
															CMSampleBuffer containing the original samples */
											  
  CFRange sampleRange,									/*! @param sampleRange
															The range of samples to copy from sbuf, where sample 0 is the first sample in the sbuf */
  CM_RETURNS_RETAINED_PARAMETER CMSampleBufferRef CM_NULLABLE * CM_NONNULL sBufOut)	/*! @param sBufOut
															Returned newly created CMSampleBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMSampleBufferGetTypeID
	@abstract	Returns the CFTypeID of CMSampleBuffer objects.
	@discussion	You can check if a CFTypeRef object is actually a CMSampleBuffer by comparing CFGetTypeID(object) with CMSampleBufferGetTypeID().
	@result		CFTypeID of CMSampleBuffer objects.
*/
CM_EXPORT
CFTypeID	CMSampleBufferGetTypeID(void)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*! 
	@functiongroup Data management functions
*/

/*!
	@function	CMSampleBufferSetDataBuffer
	@abstract	Associates a CMSampleBuffer with its CMBlockBuffer of media data.
	@discussion	If successful, this operation retains the dataBuffer thereafter, so the caller can release the dataBuffer
				after calling this API, if it has no further need to reference it. This is a write-once operation; it will fail if
				the CMSampleBuffer already has a dataBuffer. This API allows a CMSampleBuffer to exist, with timing and format
				information, before the associated data shows up. Example of usage: Some media services may have access to sample
				size, timing, and format information before the data is read.  Such services may create CMSampleBuffers with that
				information and insert them into queues early, and use this API to attach the CMBlockBuffers later, when the data
				becomes ready.
*/
CM_EXPORT
OSStatus CMSampleBufferSetDataBuffer(
	CMSampleBufferRef CM_NONNULL sbuf,			/*! @param sbuf
													CMSampleBuffer being modified. */
	CMBlockBufferRef CM_NONNULL dataBuffer)		/*! @param dataBuffer
													CMBlockBuffer of data being associated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetDataBuffer
	@abstract	Returns a CMSampleBuffer's CMBlockBuffer of media data.
	@discussion The caller does not own the returned dataBuffer, and must retain it explicitly if the caller needs to maintain a reference to it.
	@result		CMBlockBuffer of media data. The result will be NULL if the CMSampleBuffer does not contain a CMBlockBuffer, if the
				CMSampleBuffer contains a CVImageBuffer, or if there is some other error.
*/
CM_EXPORT
CMBlockBufferRef CM_NULLABLE CMSampleBufferGetDataBuffer(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
												CMSampleBuffer being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetImageBuffer
	@abstract	Returns a CMSampleBuffer's CVImageBuffer of media data.
	@discussion The caller does not own the returned dataBuffer, and must retain it explicitly if the caller needs to maintain a reference to it.
	@result		CVImageBuffer of media data. The result will be NULL if the CMSampleBuffer does not contain a CVImageBuffer, if the
				CMSampleBuffer contains a CMBlockBuffer, or if there is some other error.
*/
CM_EXPORT
CVImageBufferRef CM_NULLABLE CMSampleBufferGetImageBuffer(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
												CMSampleBuffer being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
									
/*!
	@function	CMSampleBufferSetDataBufferFromAudioBufferList
	@abstract	Creates a CMBlockBuffer containing a copy of the data from the AudioBufferList,
				and sets that as the CMSampleBuffer's data buffer. The resulting buffer(s) in the
				sample buffer will be 16-byte-aligned if  
				kCMSampleBufferFlag_AudioBufferList_Assure16ByteAlignment is passed in.
*/
CM_EXPORT
OSStatus CMSampleBufferSetDataBufferFromAudioBufferList(
	CMSampleBufferRef CM_NONNULL sbuf,				/*! @param sbuf
														CMSampleBuffer being modified. */
	CFAllocatorRef CM_NULLABLE bbufStructAllocator,	/*! @param bbufStructAllocator
														Allocator to use when creating the CMBlockBuffer structure. */
	CFAllocatorRef CM_NULLABLE bbufMemoryAllocator,	/*! @param bbufMemoryAllocator
														Allocator to use for memory block held by the CMBlockBuffer. */
	uint32_t flags,									/*! @param flags
														Flags controlling operation. */
	const AudioBufferList * CM_NONNULL bufferList)	/*! @param bufferList
														Buffer list whose data will be copied into the new CMBlockBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_DISABLED

/*!
	@function	CMSampleBufferGetAudioBufferListWithRetainedBlockBuffer
	@abstract	Creates an AudioBufferList containing the data from the CMSampleBuffer,
				and a CMBlockBuffer which references (and manages the lifetime of) the
				data in that AudioBufferList.  The data may or may not be copied,
				depending on the contiguity and 16-byte alignment of the CMSampleBuffer's
				data. The buffers placed in the AudioBufferList are guaranteed to be contiguous.
				The buffers in the AudioBufferList will be 16-byte-aligned if
				kCMSampleBufferFlag_AudioBufferList_Assure16ByteAlignment is passed in.
*/
CM_EXPORT
OSStatus CMSampleBufferGetAudioBufferListWithRetainedBlockBuffer(
	CMSampleBufferRef CM_NONNULL sbuf,							/*! @param sbuf
																	CMSampleBuffer being accessed. */
	size_t * CM_NULLABLE bufferListSizeNeededOut,				/*! @param bufferListSizeNeededOut
																	Receives the size of the AudioBufferList required to
																	accommodate the data. May be NULL. */
	AudioBufferList * CM_NULLABLE bufferListOut,				/*! @param bufferListOut
																	Allocated by the caller, sized as specified by bufferListSizeNeededOut.
																	It is filled in with pointers into the retained blockBufferOut.
																	May be NULL. */
	size_t bufferListSize,										/*! @param bufferListSize
																	Size of the bufferListOut allocated by the client. If bufferListOut
																	is not NULL and bufferListSize is insufficient, kFigSampleBufferError_ArrayTooSmall
																	is returned. */
	CFAllocatorRef CM_NULLABLE bbufStructAllocator,				/*! @param bbufStructAllocator
																	Allocator to use when creating the CMBlockBuffer structure. */
	CFAllocatorRef CM_NULLABLE bbufMemoryAllocator,				/*! @param bbufMemoryAllocator
																	Allocator to use for memory block held by the CMBlockBuffer. */
	uint32_t flags,												/*! @param flags
																	Flags controlling operation. */
	CM_RETURNS_RETAINED_PARAMETER CMBlockBufferRef CM_NULLABLE * CM_NULLABLE blockBufferOut)	/*! @param blockBufferOut
																	The retained CMBlockBuffer. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@function	CMSampleBufferGetAudioStreamPacketDescriptions
	@abstract	Creates an array of AudioStreamPacketDescriptions for the 
                variable bytes per packet or variable frames per packet
                audio data in the provided CMSampleBuffer.  Constant bitrate,
                constant frames-per-packet audio yields a return value of noErr 
                and no packet descriptions.  This API is specific to audio format
				sample buffers, and will return kCMSampleBufferError_InvalidMediaTypeForOperation
				if called with a non-audio sample buffer.
*/
CM_EXPORT
OSStatus CMSampleBufferGetAudioStreamPacketDescriptions(
    CMSampleBufferRef CM_NONNULL sbuf,								/*! @param sbuf
																		CMSampleBuffer being accessed. */
    size_t packetDescriptionsSize,									/*! @param packetDescriptionsSize
																		Size of packetDescriptionsOut as allocated by the caller. */
     AudioStreamPacketDescription * CM_NULLABLE packetDescriptionsOut,/*! @param packetDescriptionsOut
																		Allocated by the caller, receives the packet descriptions
																		for the samples in the CMSampleBuffer. If non-NULL and
																		packetDescriptionsSize is too small, kFigSampleBufferError_ArrayTooSmall
																		is returned. */
    size_t * CM_NULLABLE packetDescriptionsSizeNeededOut )			/*! @param packetDescriptionsSizeNeededOut
																		Used to query for the correct size required for packetDescriptionsOut. May be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);


/*!
	@function	CMSampleBufferGetAudioStreamPacketDescriptionsPtr
	@abstract	Returns a pointer to (and size of) a constant array of
				AudioStreamPacketDescriptions for the variable bytes per
				packet or variable frames per packet audio data in the
				provided CMSampleBuffer.  The pointer will remain valid
				as long as the sbuf continues to be retained.
				Constant bitrate, constant frames-per-packet audio yields a
				return value of noErr and no packet descriptions.  This API is
				specific to audio format sample buffers, and will return
				kCMSampleBufferError_InvalidMediaTypeForOperation if called
				with a non-audio sample buffer.
*/
CM_EXPORT
OSStatus CMSampleBufferGetAudioStreamPacketDescriptionsPtr(
    CMSampleBufferRef CM_NONNULL 						sbuf,							/*! @param sbuf CMSampleBuffer being modified. */
    const AudioStreamPacketDescription   * CM_NULLABLE * CM_NULLABLE packetDescriptionsPtrOut,		/*! @param packetDescriptionsPtrOut returned pointer to constant array of AudioStreamPacketDescriptions. May be NULL. */
    size_t								  * CM_NULLABLE packetDescriptionsSizeOut )		/*! @param packetDescriptionsSizeOut size in bytes of constant array of AudioStreamPacketDescriptions. May be NULL. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferCopyPCMDataIntoAudioBufferList
	@abstract	Copies PCM audio data from the given CMSampleBuffer into
				a pre-populated AudioBufferList. The AudioBufferList must
				contain the same number of channels and its data buffers
				must be sized to hold the specified number of frames.
				This API is	specific to audio format sample buffers, and
				will return kCMSampleBufferError_InvalidMediaTypeForOperation
				if called with a non-audio sample buffer. It will return an
				error if the CMSampleBuffer does not contain PCM audio data
				or if its dataBuffer is not ready.
*/

CM_EXPORT
OSStatus CMSampleBufferCopyPCMDataIntoAudioBufferList(
	CMSampleBufferRef CM_NONNULL   sbuf,				/*! @param sbuf Contains PCM audio data to be copied. */
	int32_t				frameOffset,					/*! @param frameOffset (zero-based) starting frame number to copy from. */
	int32_t				numFrames,						/*! @param numFrames number of frames to copy */
	AudioBufferList		* CM_NONNULL bufferList)		/*! @param  Pre-populated bufferlist */
							__OSX_AVAILABLE_STARTING(__MAC_10_9,__IPHONE_7_0);

/*!
	@function	CMSampleBufferSetDataReady
	@abstract	Marks a CMSampleBuffer's data as "ready".
	@discussion	There is no way to undo this operation.  The only way to get an "unready"
				CMSampleBuffer is to call CMSampleBufferCreate with the dataReady parameter
				set to false. Example of usage: in a read completion routine.
*/
CM_EXPORT
OSStatus CMSampleBufferSetDataReady(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being modified. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferDataIsReady
	@abstract	Returns whether or not a CMSampleBuffer's data is ready.
	@result		Whether or not the CMSampleBuffer's data is ready.  True is returned for special marker buffers, even
				though they have no data. False is returned if there is an error.
*/
CM_EXPORT
Boolean CMSampleBufferDataIsReady(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferSetDataFailed
	@abstract	Marks a CMSampleBuffer's data as "failed", to indicate that the data will not become ready.
*/
CM_EXPORT
OSStatus CMSampleBufferSetDataFailed(
	CMSampleBufferRef CM_NONNULL sbuf,		/*! @param sbuf
												CMSampleBuffer being modified. */
	OSStatus status)						/*! @param status
												Describes the failure. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSampleBufferHasDataFailed
	@abstract	Returns whether or not a CMSampleBuffer's data loading request has failed.
*/
CM_EXPORT
Boolean CMSampleBufferHasDataFailed(
	CMSampleBufferRef CM_NONNULL sbuf,	/*! @param sbuf
											CMSampleBuffer being interrogated. */
	OSStatus * CM_NONNULL statusOut)		/*! @param statusOut
											Points to an OSStatus to receive a status code describing the failure.
											Pass NULL if you do not want this information. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMSampleBufferMakeDataReady
	@abstract	Makes a CMSampleBuffer's data ready, by calling the client's CMSampleBufferMakeDataReadyCallback.
	@discussion	The CMSampleBufferMakeDataReadyCallback is passed in by the client during creation. It must return
				0 if successful, and in that case, CMSampleBufferMakeDataReady will set the data readiness of
				the CMSampleBuffer to true. Example of usage: when it is time to actually use the data. Example of
				callback routine: a routine to force a scheduled read to complete.  If the CMSampleBuffer is not
				ready, and there is no CMSampleBufferMakeDataReadyCallback to call, kCMSampleBufferError_BufferNotReady
				will be returned. Similarly, if the CMSampleBuffer is not ready, and the CMSampleBufferMakeDataReadyCallback
				fails and returns an error, kCMSampleBufferError_BufferNotReady will be returned.
*/
CM_EXPORT
OSStatus CMSampleBufferMakeDataReady(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
												CMSampleBuffer being modified. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferTrackDataReadiness
	@abstract	Associates a CMSampleBuffer's data readiness with another CMSampleBuffer's data readiness.
	@discussion	After calling this API, if CMSampleBufferDataIsReady(sbuf) is called, it will return sbufToTrack's data
				readiness. If CMSampleBufferMakeDataReady(sbuf) is called, it will do it by making sbufToTrack ready.
				Example of use: This allows bursting a multi-sample CMSampleBuffer into single-sample CMSampleBuffers
				before the data is ready. The single-sample CMSampleBuffers will all track the multi-sample
				CMSampleBuffer's data readiness.
*/
CM_EXPORT
OSStatus CMSampleBufferTrackDataReadiness(
	CMSampleBufferRef CM_NONNULL sbuf,				/*! @param sbuf
														CMSampleBuffer being modified. */
	CMSampleBufferRef CM_NONNULL sbufToTrack)		/*! @param sbufToTrack
														CMSampleBuffer being tracked. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferInvalidate
	@abstract	Makes the sample buffer invalid, calling any installed invalidation callback.
	@discussion	An invalid sample buffer cannot be used -- all accessors will return kCMSampleBufferError_Invalidated.
				It is not a good idea to do this to a sample buffer that another module may be accessing concurrently.
				Example of use: the invalidation callback could cancel pending I/O.
*/
CM_EXPORT 
OSStatus CMSampleBufferInvalidate( 
	CMSampleBufferRef CM_NONNULL sbuf )	/*! @param sbuf
											CMSampleBuffer being modified. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@typedef	CMSampleBufferInvalidateCallback
	@abstract	Client callback called by CMSampleBufferInvalidate.
*/
typedef void (*CMSampleBufferInvalidateCallback)
	(CMSampleBufferRef CM_NONNULL sbuf,	/*! @param sbuf
											The CMSampleBuffer being invalidated. */
	uint64_t invalidateRefCon);			/*! @param invalidateRefCon
											Reference constant provided when the callback was set up. */

/*!
	@function	CMSampleBufferSetInvalidateCallback
	@abstract	Sets the sample buffer's invalidation callback, which is called during CMSampleBufferInvalidate.
	@discussion	A sample buffer can only have one invalidation callback.  
				The invalidation callback is NOT called during ordinary sample buffer finalization.
*/
CM_EXPORT OSStatus 
CMSampleBufferSetInvalidateCallback( 
	CMSampleBufferRef CM_NONNULL sbuf,								/*! @param sbuf
																		The CMSampleBuffer being modified. */
	CMSampleBufferInvalidateCallback CM_NONNULL invalidateCallback,	/*! @param invalidateCallback
																		Pointer to function to be called during CMSampleBufferInvalidate. */
	uint64_t invalidateRefCon )										/*! @param invalidateRefCon
																		Reference constant to be passed to invalidateCallback. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#if __BLOCKS__
/*!
	@typedef	CMSampleBufferInvalidateHandler
	@abstract	Client callback called by CMSampleBufferInvalidate.
*/
typedef void (^CMSampleBufferInvalidateHandler)
	(CMSampleBufferRef CM_NONNULL sbuf);	/*! @param sbuf
									The CMSampleBuffer being invalidated. */

/*!
	@function	CMSampleBufferSetInvalidateHandler
	@abstract	Sets the sample buffer's invalidation handler block, which is called during CMSampleBufferInvalidate.
	@discussion	A sample buffer can only have one invalidation callback.  
				The invalidation callback is NOT called during ordinary sample buffer finalization.
*/
CM_EXPORT OSStatus 
CMSampleBufferSetInvalidateHandler( 
	CMSampleBufferRef CM_NONNULL sbuf,									/*! @param sbuf
																			The CMSampleBuffer being modified. */
	CMSampleBufferInvalidateHandler CM_NONNULL invalidateHandler )		/*! @param invalidateCallback
																			Block to be called during CMSampleBufferInvalidate. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
#endif // __BLOCKS__

/*!
	@function	CMSampleBufferIsValid
	@abstract	Queries whether a sample buffer is still valid.
	@discussion	Returns false if sbuf is NULL or CMSampleBufferInvalidate(sbuf) was called, true otherwise.
				Does not perform any kind of exhaustive validation of the sample buffer.
*/
CM_EXPORT 
Boolean CMSampleBufferIsValid( 
	CMSampleBufferRef CM_NONNULL sbuf )	/*! @param sbuf
								The CMSampleBuffer being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_BEGIN

/*!
	@constant	kCMSampleBufferNotification_DataBecameReady
	@abstract	Posted on a CMSampleBuffer by CMSampleBufferSetDataReady when the buffer becomes ready.
*/
CM_EXPORT const CFStringRef kCMSampleBufferNotification_DataBecameReady
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferNotification_DataFailed
	@abstract	Posted on a CMSampleBuffer by CMSampleBufferSetDataFailed to report that the buffer will never become ready.
*/
CM_EXPORT const CFStringRef kCMSampleBufferNotification_DataFailed
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMSampleBufferNotificationParameter_OSStatus
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@constant	kCMSampleBufferConduitNotification_InhibitOutputUntil
	@abstract	Posted on a conduit of CMSampleBuffers (eg, a CMBufferQueue) to announce a coming discontinuity and specify a tag value that will be attached to the first CMSampleBuffer following the discontinuity.  
	@discussion
		The first CMSampleBuffer following the discontinuity should have 
		a kCMSampleBufferAttachmentKey_ResumeOutput attachment with value containing 
		the same CFNumber as this notification's payload's
		kCMSampleBufferConduitNotificationParameter_ResumeTag.  
		The consumer should discard output data until it receives this CMSampleBuffer.
		If multiple kCMSampleBufferConduitNotification_InhibitOutputUntil notifications are
		received, the last one indicates the tag to trigger resuming.
*/
CM_EXPORT const CFStringRef kCMSampleBufferConduitNotification_InhibitOutputUntil  // payload: CFDictionary containing:
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleBufferConduitNotificationParameter_ResumeTag  // payload: CFNumber
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferConduitNotification_ResetOutput
	@abstract	Posted on a conduit of CMSampleBuffers (eg, a CMBufferQueue) to request invalidation of pending output data.
*/
CM_EXPORT const CFStringRef kCMSampleBufferConduitNotification_ResetOutput
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferConduitNotification_UpcomingOutputPTSRangeChanged
	@abstract	Posted on a conduit of video CMSampleBuffers (eg, a CMBufferQueue) to report information about the range of upcoming CMSampleBuffer output presentation timestamps.
*/
CM_EXPORT const CFStringRef kCMSampleBufferConduitNotification_UpcomingOutputPTSRangeChanged  // payload: CFDictionary containing:
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);
CM_EXPORT const CFStringRef kCMSampleBufferConduitNotificationParameter_UpcomingOutputPTSRangeMayOverlapQueuedOutputPTSRange  // payload: CFBoolean
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);
CM_EXPORT const CFStringRef kCMSampleBufferConduitNotificationParameter_MinUpcomingOutputPTS  // payload: CFDictionary(CMTime)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);
CM_EXPORT const CFStringRef kCMSampleBufferConduitNotificationParameter_MaxUpcomingOutputPTS  // payload: CFDictionary(CMTime)
							__OSX_AVAILABLE_STARTING(__MAC_10_8,__IPHONE_5_0);

/*!
	@constant	kCMSampleBufferConsumerNotification_BufferConsumed
	@abstract	Posted when a CMSampleBuffer that has kCMSampleBufferAttachmentKey_PostNotificationWhenConsumed is consumed.
	@discussion
		After an object consumes a CMSampleBuffer that has a kCMSampleBufferAttachmentKey_PostNotificationWhenConsumed
		attachment, it should post kCMSampleBufferConsumerNotification_BufferConsumed 
		with itself as the notifyingObject and the attachment value as the payload.
		Such an attachment value must be a CFDictionary but the contents are client-defined.
		
		Note that a NULL refcon cannot be attached to a CMSampleBuffer.
*/
CM_EXPORT const CFStringRef kCMSampleBufferConsumerNotification_BufferConsumed  // payload: CFDictionary
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_END

/*! 
	@functiongroup Buffer attribute functions
*/

/*!
	@function	CMSampleBufferGetNumSamples
	@abstract	Returns the number of media samples in a CMSampleBuffer.
	@result		The number of media samples in the CMSampleBuffer. 0 is returned if there is an error.
*/
CM_EXPORT
CMItemCount CMSampleBufferGetNumSamples(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetDuration
	@abstract	Returns the total duration of a CMSampleBuffer.
	@discussion	If the buffer contains out-of-presentation-order samples, any gaps in the presentation timeline are not represented in the returned duration.
				The returned duration is simply the sum of all the individual sample durations.
	@result		The duration of the CMSampleBuffer. kCMTimeInvalid is returned if there is an error.
*/
CM_EXPORT
CMTime CMSampleBufferGetDuration(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetPresentationTimeStamp
	@abstract	Returns the numerically earliest presentation timestamp of all the samples in a CMSampleBuffer.
	@discussion	For in-presentation-order samples, this is the presentation timestamp of the first sample.
				For out-of-presentation-order samples, this is the presentation timestamp of the sample that
				will be presented first, which is not necessarily the first sample in the buffer.
	@result		Numerically earliest sample presentation timestamp in the CMSampleBuffer.  kCMTimeInvalid is returned if there is an error.
*/
CM_EXPORT
CMTime CMSampleBufferGetPresentationTimeStamp(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetDecodeTimeStamp
	@abstract	Returns the numerically earliest decode timestamp of all the samples in a CMSampleBuffer.
	@discussion	The returned decode timestamp is always the decode timestamp of the first sample in the buffer,
				since even out-of-presentation-order samples are expected to be in decode order in the buffer.
	@result		Numerically earliest sample decode timestamp in the CMSampleBuffer.  kCMTimeInvalid is returned if there is an error.
*/
CM_EXPORT
CMTime CMSampleBufferGetDecodeTimeStamp(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetOutputDuration
	@abstract	Returns the output duration of a CMSampleBuffer.
	@discussion	The OutputDuration is the duration minus any trimmed duration, all divided by the SpeedMultiplier:
				(Duration - TrimDurationAtStart - TrimDurationAtEnd) / SpeedMultiplier
	@result		The output duration of the CMSampleBuffer. kCMTimeInvalid is returned if there is an error.
*/
CM_EXPORT
CMTime CMSampleBufferGetOutputDuration(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetOutputPresentationTimeStamp
	@abstract	Returns the output presentation timestamp of the CMSampleBuffer.
	@discussion	The output presentation timestamp is the time at which the decoded, trimmed, stretched 
				and possibly reversed samples should commence being presented.
				If CMSampleBufferSetOutputPresentationTimeStamp has been called to explicitly set the output PTS, 
				CMSampleBufferGetOutputPresentationTimeStamp returns it.  
				If not, CMSampleBufferGetOutputPresentationTimeStamp calculates its result as
				(PresentationTimeStamp + TrimDurationAtStart) 
				unless kCMSampleBufferAttachmentKey_Reverse is kCFBooleanTrue, in which case it calculates the result as
				(PresentationTimeStamp + Duration - TrimDurationAtEnd).
				These are generally correct for un-stretched, un-shifted playback.
				For general forward playback in a scaled edit, the OutputPresentationTimeStamp should be set to:
				((PresentationTimeStamp + TrimDurationAtStart - EditStartMediaTime) / EditSpeedMultiplier) + EditStartTrackTime.
				For general reversed playback:
				((PresentationTimeStamp + Duration - TrimDurationAtEnd - EditStartMediaTime) / EditSpeedMultiplier) + EditStartTrackTime.
	@result		kCMTimeInvalid is returned if there is an error.
*/
CM_EXPORT
CMTime CMSampleBufferGetOutputPresentationTimeStamp(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
									CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferSetOutputPresentationTimeStamp
	@abstract	Sets an output presentation timestamp to be used in place of a calculated value.
	@discussion	The output presentation timestamp is the time at which the decoded, trimmed, stretched 
				and possibly reversed samples should commence being presented.
				By default, this is calculated by CMSampleBufferGetOutputPresentationTimeStamp.
				Call CMSampleBufferSetOutputPresentationTimeStamp to explicitly set the value for
				CMSampleBufferGetOutputPresentationTimeStamp to return.
				For general forward playback in a scaled edit, the OutputPresentationTimeStamp should be set to:
				((PresentationTimeStamp + TrimDurationAtStart - EditStartMediaTime) / EditSpeedMultiplier) + EditStartTrackTime.
				For general reversed playback:
				((PresentationTimeStamp + Duration - TrimDurationAtEnd - EditStartMediaTime) / EditSpeedMultiplier) + EditStartTrackTime.
*/
CM_EXPORT
OSStatus CMSampleBufferSetOutputPresentationTimeStamp(
	CMSampleBufferRef CM_NONNULL sbuf,		/*! @param sbuf
												CMSampleBuffer being interrogated */
	CMTime outputPresentationTimeStamp)		/*! @param outputPresentationTimeStamp
												New value for OutputPresentationTimeStamp.
												Pass kCMTimeInvalid to go back to the default calculation. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetOutputDecodeTimeStamp
	@abstract	Returns the output decode timestamp of the CMSampleBuffer.
	@discussion	For consistency with CMSampleBufferGetOutputPresentationTimeStamp, this is calculated as:
				OutputPresentationTimeStamp + ((DecodeTimeStamp - PresentationTimeStamp) / SpeedMultiplier).
	@result		CMInvalidTime is returned if there is an error.
*/
CM_EXPORT
CMTime CMSampleBufferGetOutputDecodeTimeStamp(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
												CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetSampleTimingInfoArray
	@abstract	Returns an array of CMSampleTimingInfo structs, one for each sample in a CMSampleBuffer.
	@discussion	If only one CMSampleTimingInfo struct is returned, it applies to all samples in the buffer.
				See documentation of CMSampleTimingInfo for details of how a single CMSampleTimingInfo struct can apply to multiple samples.
				The timingArrayOut must be allocated by the caller, and the number of entries allocated must be passed in timingArrayEntries.
				If timingArrayOut is NULL, timingArrayEntriesNeededOut will return the required number of entries.  Similarly, 
				if timingArrayEntries is too small, kCMSampleBufferError_ArrayTooSmall will be returned, and timingArrayEntriesNeededOut
				will return the required number of entries. In either case, the caller can then make an appropriately-sized timingArrayOut and call again.
				For example, the caller might pass the address of a CMSampleTimingInfo struct on the stack (as timingArrayOut), and 1 (as
				timingArrayEntries). If all samples are describable with a single CMSampleTimingInfo struct (or there is only one sample
				in the CMSampleBuffer), this call will succeed. If not, it will fail, and will return the number of entries required in
				timingArrayEntriesNeededOut. Only in this case will the caller actually need to allocate an array.
				
				If there is no timingInfo in this CMSampleBuffer, kCMSampleBufferError_BufferHasNoSampleTimingInfo will be returned, and
				timingArrayEntriesNeededOut will be set to 0.
*/
CM_EXPORT
OSStatus CMSampleBufferGetSampleTimingInfoArray(
	CMSampleBufferRef CM_NONNULL sbuf,						/*! @param sbuf
																CMSampleBuffer being interrogated */
	CMItemCount timingArrayEntries,							/*! @param timingArrayEntries
																Number of entries in timingArray */
	CMSampleTimingInfo * CM_NULLABLE timingArrayOut,		/*! @param timingArrayOut
																Points to an array of CMSampleTimingInfo structs
																to receive the timing info. */
	CMItemCount * CM_NULLABLE timingArrayEntriesNeededOut)	/*! @param timingArrayEntriesNeededOut
																Number of entries needed for the result. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetOutputSampleTimingInfoArray
	@abstract	Returns an array of output CMSampleTimingInfo structs, one for each sample in a CMSampleBuffer.
	@discussion	If only one CMSampleTimingInfo struct is returned, it applies to all samples in the buffer.
				See documentation of CMSampleTimingInfo for details of how a single CMSampleTimingInfo struct can apply to multiple samples.
				The timingArrayOut must be allocated by the caller, and the number of entries allocated must be passed in timingArrayEntries.
				If timingArrayOut is NULL, timingArrayEntriesNeededOut will return the required number of entries.  Similarly,
				if timingArrayEntries is too small, kCMSampleBufferError_ArrayTooSmall will be returned, and timingArrayEntriesNeededOut
				will return the required number of entries. In either case, the caller can then make an appropriately-sized timingArrayOut and call again.
				For example, the caller might pass the address of a CMSampleTimingInfo struct on the stack (as timingArrayOut), and 1 (as
				timingArrayEntries). If all samples are describable with a single CMSampleTimingInfo struct (or there is only one sample
				in the CMSampleBuffer), this call will succeed. If not, it will fail, and will return the number of entries required in
				timingArrayEntriesNeededOut. Only in this case will the caller actually need to allocate an array.
				
				If there is no timingInfo in this CMSampleBuffer, kCMSampleBufferError_BufferHasNoSampleTimingInfo will be returned,
				and *timingArrayEntriesNeededOut will be set to 0.
*/
CM_EXPORT
OSStatus CMSampleBufferGetOutputSampleTimingInfoArray(
	CMSampleBufferRef CM_NONNULL sbuf,						/*! @param sbuf
																CMSampleBuffer being interrogated */
	CMItemCount timingArrayEntries,							/*! @param timingArrayEntries
																Number of entries in timingArray */
	CMSampleTimingInfo * CM_NULLABLE timingArrayOut,		/*! @param timingArrayOut
																Points to an array of CMSampleTimingInfo structs
																to receive the timing info. */
	CMItemCount * CM_NULLABLE timingArrayEntriesNeededOut)	/*! @param timingArrayEntriesNeededOut
																Number of entries needed for the result. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetSampleTimingInfo
	@abstract	Returns a CMSampleTimingInfo struct describing a specified sample in a CMSampleBuffer.
	@discussion	A sample-specific CMSampleTimingInfo struct will be returned (ie. with a sample-specific
				presentationTimeStamp and decodeTimeStamp), even if a single CMSampleTimingInfo struct was used
				during creation to describe all the samples in the buffer. The timingInfo struct must be
				allocated by the caller.  If the sample index is not in the range 0 .. numSamples-1,
				kCMSampleBufferError_SampleIndexOutOfRange will be returned.  If there is no timingInfo
				in this CMSampleBuffer, kCMSampleBufferError_BufferHasNoSampleTimingInfo will be returned.
*/
CM_EXPORT
OSStatus CMSampleBufferGetSampleTimingInfo(
	CMSampleBufferRef CM_NONNULL sbuf,					/*! @param sbuf
															CMSampleBuffer being interrogated */
	CMItemIndex sampleIndex,							/*! @param sampleIndex
															Sample index (0 is first sample in sbuf) */
	CMSampleTimingInfo * CM_NONNULL timingInfoOut)		/*! @param timingInfoOut
															Points to a single CMSampleTimingInfo
															struct to receive the timing info. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetSampleSizeArray
	@abstract	Returns an array of sample sizes, one for each sample in a CMSampleBuffer.
	@discussion	If only one size entry is returned, all samples in the buffer are of this size.
				The sizeArrayOut must be allocated by the caller, and the number of entries allocated must be passed in sizeArrayEntries.
				If sizeArrayOut is NULL, sizeArrayEntriesNeededOut will return the required number of entries.  Similarly, if sizeArrayEntries
				is too small, kCMSampleBufferError_ArrayTooSmall will be returned, and sizeArrayEntriesNeededOut will return the required number of entries.
				The caller can then make an appropriately-sized sizeArrayOut and call again. For example, the caller might pass the address
				of a size_t variable on the stack (as sizeArrayOut), and 1 (as sizeArrayEntries). If all samples are the same size (or there
				is only one sample in the CMSampleBuffer), this call would succeed. If not, it will fail, and will return the number of
				entries required in sizeArrayEntriesNeededOut. Only in this case (multiple samples of different sizes) will the caller
				need to allocate an array.  0 entries will be returned if the samples in the buffer are non-contiguous (eg. non-interleaved
				audio, where the channel values for a single sample are scattered through the buffer).
				
				If there are no sample sizes in this CMSampleBuffer, kCMSampleBufferError_BufferHasNoSampleSizes will be returned,
				and *sizeArrayEntriesNeededOut will be set to 0.  This will be true, for example,
				if the samples in the buffer are non-contiguous (eg. non-interleaved audio, where
				the channel values for a single sample are scattered through the buffer), or if
				this CMSampleBuffer contains a CVImageBuffer.
*/
CM_EXPORT
OSStatus CMSampleBufferGetSampleSizeArray(
	CMSampleBufferRef CM_NONNULL sbuf,						/*! @param sbuf
																CMSampleBuffer being interrogated */
	CMItemCount sizeArrayEntries,							/*! @param sizeArrayEntries
																Number of entries in sizeArray. */
	size_t * CM_NULLABLE sizeArrayOut,						/*! @param sizeArrayOut
																Points to an array of size_t values
																to receive the sample sizes. */
	CMItemCount * CM_NULLABLE sizeArrayEntriesNeededOut)	/*! @param sizeArrayEntriesNeededOut
																Number of entries needed for the result. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
									   
/*!
	@function	CMSampleBufferGetSampleSize
	@abstract	Returns the size in bytes of a specified sample in a CMSampleBuffer.
	@result		Size in bytes of the specified sample in the CMSampleBuffer.
				If the sample index is not in the range 0 .. numSamples-1,
				a size of 0 will be returned.  If there are no sample sizes
				in this CMSampleBuffer, a size of 0 will be returned.  This will be true, for example,
				if the samples in the buffer are non-contiguous (eg. non-interleaved audio, where
				the channel values for a single sample are scattered through the buffer),
				or if this CMSampleBuffer contains a CVImageBuffer.
				
*/
CM_EXPORT
size_t CMSampleBufferGetSampleSize(
	CMSampleBufferRef CM_NONNULL sbuf,		/*! @param sbuf
												CMSampleBuffer being interrogated */
	CMItemIndex sampleIndex)				/*! @param sampleIndex
												Sample index (0 is first sample in sbuf) */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetTotalSampleSize
	@abstract	Returns the total size in bytes of sample data in a CMSampleBuffer.
	@result		Total size in bytes of sample data in the CMSampleBuffer.
				If there are no sample sizes in this CMSampleBuffer, a size of 0 will be returned.  
*/
CM_EXPORT
size_t CMSampleBufferGetTotalSampleSize(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
												CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetFormatDescription
	@abstract	Returns the format description of the samples in a CMSampleBuffer.
	@discussion On return, the caller does not own the returned formatDesc, and must retain it explicitly if the caller needs to maintain a reference to it.
	@result		The format description of the samples in the CMSampleBuffer.  NULL is returned if there is an error.
*/
CM_EXPORT
CM_NULLABLE CMFormatDescriptionRef CMSampleBufferGetFormatDescription(
	CMSampleBufferRef CM_NONNULL sbuf)		/*! @param sbuf
												CMSampleBuffer being interrogated */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@function	CMSampleBufferGetSampleAttachmentsArray
	@abstract	Returns a reference to a CMSampleBuffer's immutable array of mutable sample attachments dictionaries (one dictionary
				per sample in the CMSampleBuffer).
	@discussion Attachments can then be added/removed directly by the caller, using CF APIs. On return, the caller does not
				own the returned array of attachments dictionaries, and must retain it if the caller needs to maintain a
				reference to it. If there are no sample attachments yet, and createIfNecessary is true, a new CFArray containing N empty
				CFMutableDictionaries is returned (where N is the number of samples in the CMSampleBuffer), so that
				attachments can be added directly by the caller. If there are no sample attachments yet, and createIfNecessary is
				false, NULL is returned.  Once the CFArray has been created, subsequent calls will return it, even if there are still
				no sample attachments in the array.
	@result		A reference to the CMSampleBuffer's immutable array of mutable sample attachments dictionaries (one dictionary per sample
				in the CMSampleBuffer). NULL is returned if there is an error.
*/
CM_EXPORT
CM_NULLABLE CFArrayRef CMSampleBufferGetSampleAttachmentsArray(
	CMSampleBufferRef CM_NONNULL sbuf,		/*! @param sbuf
												CMSampleBuffer being interrogated */
	Boolean createIfNecessary)				/*! @param createIfNecessary
												Specifies whether an empty array should be
												created (if there are no sample attachments yet). */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

CM_ASSUME_NONNULL_BEGIN

// The following keys may be attached to individual samples via the CMSampleBufferGetSampleAttachmentsArray() interface:
CM_EXPORT const CFStringRef kCMSampleAttachmentKey_NotSync  // CFBoolean (absence of this key implies Sync)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleAttachmentKey_PartialSync  // CFBoolean (absence of this key implies not Partial Sync. If NotSync is false, PartialSync should be ignored.)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleAttachmentKey_HasRedundantCoding  // kCFBooleanTrue, kCFBooleanFalse, or absent if unknown
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleAttachmentKey_IsDependedOnByOthers  // kCFBooleanTrue, kCFBooleanFalse, or absent if unknown
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleAttachmentKey_DependsOnOthers  // kCFBooleanTrue, kCFBooleanFalse, or absent if unknown
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleAttachmentKey_EarlierDisplayTimesAllowed  // CFBoolean
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
// A frame is considered droppable if and only if kCMSampleAttachmentKey_IsDependedOnByOthers is present and set to kCFBooleanFalse.

CM_EXPORT const CFStringRef kCMSampleAttachmentKey_DisplayImmediately  // CFBoolean
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleAttachmentKey_DoNotDisplay  // CFBoolean
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

// The following keys may be attached to sample buffers using CMSetAttachment():
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_ResetDecoderBeforeDecoding  // CFBoolean
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_DrainAfterDecoding  // CFBoolean
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_PostNotificationWhenConsumed  // CFDictionary (client-defined)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_ResumeOutput  // CFNumber (ResumeTag)
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_TransitionID
	@abstract	Marks a transition from one source of buffers (eg. song) to another
	@discussion
		For example, during gapless playback of a list of songs, this attachment marks the first buffer from the next song.
		If this attachment is on a buffer containing no samples, the first following buffer that contains samples is the
		buffer that contains the first samples from the next song.  The value of this attachment is a CFTypeRef.  This
		transition identifier should be unique within a playlist, so each transition in a playlist is uniquely
		identifiable.  A CFNumberRef counter that increments with each transition is a simple example.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_TransitionID
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_TrimDurationAtStart
	@abstract	The duration that should be removed at the beginning of the sample buffer, after decoding.
	@discussion
		If this attachment is not present, the trim duration is zero (nothing removed).
		This is a CMTime in CFDictionary format as made by CMTimeCopyAsDictionary; 
		use CMTimeMakeFromDictionary to convert to CMTime.
		In cases where all the output after decoding the sample buffer is to be discarded 
		(eg, the samples are only being decoded to prime the decoder) the usual convention
		is to set kCMSampleBufferAttachmentKey_TrimDurationAtStart to the whole duration 
		and not to set a kCMSampleBufferAttachmentKey_TrimDurationAtEnd attachment.
		Note that setting or removing kCMSampleBufferAttachmentKey_TrimDurationAtStart from
		a sample buffer will not adjust an explicitly-set OutputPresentationTimeStamp.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_TrimDurationAtStart  // CFDictionary/CMTime, default 0
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_TrimDurationAtEnd
	@abstract	The duration that should be removed at the end of the sample buffer, after decoding.
	@discussion
		If this attachment is not present, the trim duration is zero (nothing removed).
		This is a CMTime in CFDictionary format as made by CMTimeCopyAsDictionary; 
		use CMTimeMakeFromDictionary to convert to CMTime.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_TrimDurationAtEnd  // CFDictionary/CMTime, default 0
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_SpeedMultiplier
	@abstract	The factor by which the sample buffer's presentation should be accelerated (eg, in a scaled edit).
	@discussion
		For normal playback the speed multiplier would be 1.0 (which is used if this attachment is not present); 
		for double-speed playback the speed multiplier would be 2.0, which would halve the output duration.
		Speed-multiplication factors take effect after trimming; see CMSampleBufferGetOutputDuration.
		Note that this attachment principally provides information about the duration-stretching effect:
		by default, it should be implemented by rate conversion, but other attachments may specify richer 
		stretching operations -- for example, scaling without pitch shift, or pitch shift without changing duration.
		Sequences of speed-multiplied sample buffers should have explicit OutputPresentationTimeStamp attachments 
		to clarify when each should be output.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_SpeedMultiplier  // CFNumber, positive, default 1
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_Reverse
	@abstract	Indicates that the decoded contents of the sample buffer should be reversed.
		If this attachment is not present, the sample buffer should be played forwards as usual.
		Reversal occurs after trimming and speed multipliers.

*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_Reverse  // CFBoolean, default false
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_FillDiscontinuitiesWithSilence
	@abstract	Fill the difference between discontiguous sample buffers with silence.
	@discussion
		If a sample buffer enters a buffer queue and the presentation time stamp between the
		previous buffer and the buffer with this attachment are discontiguous, handle the
		discontinuity by generating silence for the time difference.
 */
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_FillDiscontinuitiesWithSilence  // CFBoolean, default false
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_EmptyMedia
	@abstract	Marks an intentionally empty interval in the sequence of samples.
	@discussion
		The sample buffer's output presentation timestamp indicates when the empty interval begins.
		Marker sample buffers with this attachment are used to announce the arrival of empty edits.
 */
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_EmptyMedia  // CFBoolean, default false
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_PermanentEmptyMedia
	@abstract	Marks the end of the sequence of samples.
	@discussion
		Marker sample buffers with this attachment in addition to kCMSampleBufferAttachmentKey_EmptyMedia
		are used to indicate that no further samples are expected.
 */
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_PermanentEmptyMedia  // CFBoolean, default false
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_DisplayEmptyMediaImmediately
	@abstract	Tells that the empty marker should be dequeued immediately regardless of its timestamp.
	@discussion
		Marker sample buffers with this attachment in addition to kCMSampleBufferAttachmentKey_EmptyMedia
		are used to tell that the empty sample buffer should be dequeued immediately regardless of its timestamp.
		This attachment should only be used with sample buffers with the kCMSampleBufferAttachmentKey_EmptyMedia
		attachment.
 */
CM_EXPORT const CFStringRef	kCMSampleBufferAttachmentKey_DisplayEmptyMediaImmediately
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_EndsPreviousSampleDuration
	@abstract	Indicates that sample buffer's decode timestamp may be used to define the previous sample buffer's duration.
	@discussion
		Marker sample buffers with this attachment may be used in situations where sample buffers are transmitted
		before their duration is known. In such situations, normally the recipient may use each sample buffer's timestamp
		to calculate the duration of the previous sample buffer. The marker sample buffer with this attachment is sent
		to provide the timestamp for calculating the final sample buffer's duration.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_EndsPreviousSampleDuration  // CFBoolean, default false
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_SampleReferenceURL
	@abstract	Indicates the URL where the sample data is.
	@discussion
		This key is only used for CMSampleBuffers representing sample references.  
		Such CMSampleBuffers:
		 - have dataBuffer == NULL and imageBuffer == NULL
		 - have dataReady == true and no makeDataReadyCallback
		 - have a non-NULL formatDescription
		 - have numSamples > 0
		 - have numSampleTimingEntries > 0 and numSampleSizeEntries > 0
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_SampleReferenceURL  // CFURL
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_SampleReferenceByteOffset
	@abstract	Indicates the byte offset at which the sample data begins.
	@discussion
		This key is only used for CMSampleBuffers representing sample references.  
		Such CMSampleBuffers:
		 - have dataBuffer == NULL and imageBuffer == NULL
		 - have dataReady == true and no makeDataReadyCallback
		 - have a non-NULL formatDescription
		 - have numSamples > 0
		 - have numSampleTimingEntries > 0 and numSampleSizeEntries > 0
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_SampleReferenceByteOffset  // CFNumber, byte offset from beginning of URL to contiguous data
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_GradualDecoderRefresh
	@abstract	Indicates the decoder refresh count.
	@discussion
		Sample buffers with this attachment may be used to identify the audio decoder refresh count.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_GradualDecoderRefresh  // CFNumber, audio decoder refresh count
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_3);
	
/*!
	@constant	kCMSampleBufferAttachmentKey_DroppedFrameReason
	@abstract	Indicates the reason the current video frame was dropped.
	@discussion
		Sample buffers with this attachment contain no image or data buffer.  They mark a dropped video
		frame.  This attachment identifies the reason for the droppage.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_DroppedFrameReason  // CFString, frame drop reason
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);

/*!
	@constant	kCMSampleBufferDroppedFrameReason_FrameWasLate
	@abstract	The frame was dropped because it was late
	@discussion
		The value of kCMSampleBufferAttachmentKey_DroppedFrameReason if a video capture client has indicated 
		that late video frames should be dropped and the current frame is late.  This condition is typically
		caused by the client's processing taking too long.
*/
CM_EXPORT const CFStringRef kCMSampleBufferDroppedFrameReason_FrameWasLate
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);
	
/*!
	@constant	kCMSampleBufferDroppedFrameReason_OutOfBuffers
	@abstract	The frame was dropped because the module providing frames is out of buffers
	@discussion
		The value of kCMSampleBufferAttachmentKey_DroppedFrameReason if the module providing sample buffers
		has run out of source buffers.  This condition is typically caused by the client holding onto
		buffers for too long and can be alleviated by returning buffers to the provider.
 */
CM_EXPORT const CFStringRef kCMSampleBufferDroppedFrameReason_OutOfBuffers
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);
	
/*!
	@constant	kCMSampleBufferDroppedFrameReason_Discontinuity
	@abstract	An unknown number of frames were dropped
	@discussion
		The value of kCMSampleBufferAttachmentKey_DroppedFrameReason if the module providing sample buffers
		has experienced a discontinuity, and an unknown number of frames have been lost.  This condition is 
		typically caused by the system being too busy.
 */
CM_EXPORT const CFStringRef kCMSampleBufferDroppedFrameReason_Discontinuity
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_6_0);
	
/*!
	@constant	kCMSampleBufferAttachmentKey_DroppedFrameReasonInfo
	@abstract	Indicates additional information regarding the dropped video frame.
	@discussion
		Sample buffers with this attachment contain no image or data buffer.  They mark a dropped video
		frame. If present, this attachment provides additional information about the kCMSampleBufferAttachmentKey_DroppedFrameReason.
 */
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_DroppedFrameReasonInfo  
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0); // CFString, dropped frame reason additional information
	
/*!
	@constant	kCMSampleBufferDroppedFrameReasonInfo_CameraModeSwitch
	@abstract	A discontinuity was caused by a camera mode switch.
	@discussion
		The value of kCMSampleBufferAttachmentKey_DroppedFrameReasonInfo if the module providing sample buffers
		has experienced a discontinuity due to a camera mode switch. Short discontinuities of this type can occur when the 
		session is configured for still image capture on some devices.
 */
CM_EXPORT const CFStringRef kCMSampleBufferDroppedFrameReasonInfo_CameraModeSwitch
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);
	
	
	
/*!
	@constant	kCMSampleBufferAttachmentKey_StillImageLensStabilizationInfo
	@abstract	Indicates information about the lens stabilization applied to the current still image buffer.
	@discussion
        Sample buffers that have been captured with a lens stabilization module may have an attachment of
		kCMSampleBufferAttachmentKey_StillImageLensStabilizationInfo which has information about the stabilization status
        during the capture.  This key will not be present in CMSampleBuffers coming from cameras without a lens stabilization module.
*/
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_StillImageLensStabilizationInfo  // CFString, one of kCMSampleBufferLensStabilizationInfo_*
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);

/*!
 @constant	kCMSampleBufferLensStabilizationInfo_Active
 @abstract	The lens stabilization module was active for the duration this buffer.
 @discussion
 */
CM_EXPORT const CFStringRef kCMSampleBufferLensStabilizationInfo_Active  // CFString
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);

/*!
 @constant	kCMSampleBufferLensStabilizationInfo_OutOfRange
 @abstract	The motion of the device or duration of the capture was outside of what the stabilization mechanism could support.
 @discussion
	The value of kCMSampleBufferAttachmentKey_StillImageLensStabilizationInfo if the module stabilizing the lens was unable to
	compensate for the movement.
 */
CM_EXPORT const CFStringRef kCMSampleBufferLensStabilizationInfo_OutOfRange  // CFString
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);

/*!
 @constant	kCMSampleBufferLensStabilizationInfo_Unavailable
 @abstract	The lens stabilization module was unavailable for use.
 @discussion
	The value of kCMSampleBufferAttachmentKey_StillImageLensStabilizationInfo if the lens stabilization module is unavailable
	to compensate for the motion of the device.  The module may be available at a later time.
 */
CM_EXPORT const CFStringRef kCMSampleBufferLensStabilizationInfo_Unavailable  // CFString
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);

/*!
 @constant	kCMSampleBufferLensStabilizationInfo_Off
 @abstract	The lens stabilization module was not used during this capture.
 @discussion
	The value of kCMSampleBufferAttachmentKey_StillImageLensStabilizationInfo if the lens stabilization module was not used for this capture.
 */
CM_EXPORT const CFStringRef kCMSampleBufferLensStabilizationInfo_Off  // CFString
							__OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_9_0);

/*!
	@constant	kCMSampleBufferAttachmentKey_ForceKeyFrame
	@abstract	Indicates that the current or next video sample buffer should be forced to be encoded as a key frame.
	@discussion
		A value of kCFBooleanTrue for kCMSampleBufferAttachmentKey_ForceKeyFrame indicates that the current or next video sample buffer processed in the stream should be forced to be encoded as a key frame.
		If this attachment is present and kCFBooleanTrue on a sample buffer with a video frame, that video frame will be forced to become a key frame.  If the sample buffer for which this is present and kCFBooleanTrue does not have a valid video frame, the next sample buffer processed that contains a valid video frame will be encoded as a key frame.
		
		Usual care should be taken when setting attachments on sample buffers whose orgins and destinations are ambiguous.  For example, CMSetAttachment() is not thread-safe, and CMSampleBuffers may be used in multiple sample buffer streams in a given system.  This can lead to crashes during concurrent access and/or unexpected behavior on alternate sample buffer streams.  Therefore, unless the orgin and destination of a sample buffer is known, the general recommended practice is to synthesize an empty sample buffer with this attachment alone and insert it into the sample buffer stream ahead of the concrete sample buffer rather than setting this attachment on the concrete sample buffer itself.
 */
CM_EXPORT const CFStringRef kCMSampleBufferAttachmentKey_ForceKeyFrame
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0); // CFBoolean

CM_ASSUME_NONNULL_END

// Use CMAttachmentBearer APIs to set, get, and remove buffer-level attachments on the CMSampleBuffer itself

/*!
	@function	CMSampleBufferCallForEachSample
	@abstract	Calls a function for every individual sample in a sample buffer.
	@discussion Temporary sample buffers will be created for individual samples,
				referring to the sample data and containing its timing, size and attachments.
				The callback function may retain these sample buffers if desired.
				If the callback function returns an error, iteration will stop immediately
				and the error will be returned.
				If there are no sample sizes in the provided sample buffer, kCMSampleBufferError_CannotSubdivide will be returned.
				This will happen, for example, if the samples in the buffer are non-contiguous (eg. non-interleaved audio, where
				the channel values for a single sample are scattered through the buffer).
*/
CM_EXPORT OSStatus
CMSampleBufferCallForEachSample(
	CMSampleBufferRef CM_NONNULL sbuf,		/*! @param sbuf
												CMSampleBuffer that may contain multiple samples. */
	OSStatus (* CM_NONNULL callback)( CMSampleBufferRef CM_NONNULL sampleBuffer, CMItemCount index, void * CM_NULLABLE refcon ),
											/*! @param callback
												Function to be called for each individual sample. */
	void * CM_NULLABLE refcon )				/*! @param refcon
												Refcon to be passed to the callback function. */
							__OSX_AVAILABLE_STARTING(__MAC_10_7,__IPHONE_4_0);

#if __BLOCKS__
/*!
	@function	CMSampleBufferCallBlockForEachSample
	@abstract	Calls a block for every individual sample in a sample buffer.
	@discussion Temporary sample buffers will be created for individual samples,
				referring to the sample data and containing its timing, size and attachments.
				The block may retain these sample buffers if desired.
				If the block returns an error, iteration will stop immediately
				and the error will be returned.
				If there are no sample sizes in the provided sample buffer, kCMSampleBufferError_CannotSubdivide will be returned.
				This will happen, for example, if the samples in the buffer are non-contiguous (eg. non-interleaved audio, where
				the channel values for a single sample are scattered through the buffer).
*/
CM_EXPORT OSStatus
CMSampleBufferCallBlockForEachSample(
	CMSampleBufferRef CM_NONNULL sbuf,		/*! @param sbuf
												CMSampleBuffer that may contain multiple samples. */
	OSStatus (^ CM_NONNULL handler)( CMSampleBufferRef CM_NONNULL sampleBuffer, CMItemCount index ) )
											/*! @param handler
												Block to be called for each individual sample. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
#endif // __BLOCKS__

CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif
	
#endif // CMSAMPLEBUFFER_H
// ==========  CoreMedia.framework/Headers/CMTextMarkup.h
/*
    File:  CMTextMarkup.h

    Framework:  CoreMedia
 
    Copyright 2012-2015 Apple Inc. All rights reserved.

*/

#ifndef CMTEXTMARKUP_H
#define CMTEXTMARKUP_H

/*!
    @header
    @abstract   Definition of text markup related attributes to which Core Media will respond.

    @discussion Core Media includes support for legible media streams such as subtitles, captions and text. In some
                cases, clients may need to specify style information to control the rendering. In other cases,
                information about the text and applied styling may be communicated from Core Media to the client.
                To carry this information, Core Media defines a set of attributes that may be used in dictionaries
                that Core Media uses. These attributes can also be used as CFAttributedString attributes.
*/

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)

CM_ASSUME_NONNULL_BEGIN

#pragma mark CMTextMarkup Attributes

/*!
    @const      kCMTextMarkupAttribute_ForegroundColorARGB
    @abstract   The foreground color for text.
 
    @discussion Value must be a CFArray of 4 CFNumbers representing alpha, red, green, and blue fields with values between 0.0 and 1.0. The
                red, green and blue components are interpreted in the sRGB color space. The alpha indicates the opacity from 0.0 for transparent to
                1.0 for 100% opaque.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_ForegroundColorARGB __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/*!
    @const      kCMTextMarkupAttribute_BackgroundColorARGB
    @abstract   The background color for the shape holding the text.
 
    @discussion Value must be a CFArray of 4 CFNumbers representing alpha, red, green, and blue fields with values between 0.0 and 1.0. The
                red, green and blue components are interpreted in the sRGB color space. The alpha indicates the opacity from 0.0 for transparent to
                1.0 for 100% opaque.

                The color applies to the geometry (e.g., a box) containing the text. The container's background color may have an 
                alpha of 0 so it is not displayed even though the text is displayed. The color behind individual characters
                is optionally controllable with the kCMTextMarkupAttribute_CharacterBackgroundColorARGB attribute. 
 
                If used, this attribute must be applied to the entire attributed string (i.e.,
                CFRangeMake(0, CFAttributedStringGetLength(...))).
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_BackgroundColorARGB __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/*!
    @const      kCMTextMarkupAttribute_CharacterBackgroundColorARGB
    @abstract   The background color behind individual text characters.
 
    @discussion Value must be a CFArray of 4 CFNumbers representing alpha, red, green, and blue fields with values between 0.0 and 1.0. The
                red, green and blue components are interpreted in the sRGB color space. The alpha indicates the opacity from 0.0 for transparent to
                1.0 for 100% opaque.
 */
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_CharacterBackgroundColorARGB __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
    @const      kCMTextMarkupAttribute_BoldStyle
    @abstract   Allows the setting of a bold style to be applied.

    @discussion Value must be a CFBoolean. The default is kCFBooleanFalse.
                If this attribute is kCFBooleanTrue, the text will be drawn 
                with a bold style. Other styles such as italic may or may 
                not be used as well.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_BoldStyle __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/*!
    @const      kCMTextMarkupAttribute_ItalicStyle
    @abstract   Allows the setting of an italic style to be applied.

    @discussion Value must be a CFBoolean. The default is kCFBooleanFalse.
                If this attribute is kCFBooleanTrue, the text will be rendered 
                with an italic style. Other styles such as bold may or may not 
                be used as well.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_ItalicStyle __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/*!
    @const      kCMTextMarkupAttribute_UnderlineStyle
    @abstract   Allows the setting of an underline to be applied at render
                time.

    @discussion Value must be a CFBoolean. The default is kCFBooleanFalse.
                If this attribute is kCFBooleanTrue, the text will be rendered 
                with an underline. Other styles such as bold may or may not 
                be used as well.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_UnderlineStyle __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/*!
    @const      kCMTextMarkupAttribute_FontFamilyName
    @abstract   The name of the font.
 
    @discussion Value must be a CFString holding the family name of an installed font
                (e.g., "Helvetica") that is used to render and/or measure text.
 
                When vended by legible output, an attributed string will have at most one of kCMTextMarkupAttribute_FontFamilyName or
                kCMTextMarkupAttribute_GenericFontFamilyName associated with each character.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_FontFamilyName __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/*!
    @const      kCMTextMarkupAttribute_GenericFontFamilyName
    @abstract   The attribute holding a generic font family identifier.
 
    @discussion	Value must be a CFString holding a generic font family name that is one of the kCMTextMarkupGenericFontName_* constants.
 				Generic fonts must be mapped to the family name of an installed font (e.g., kCMTextMarkupGenericFontName_SansSerif -> "Helvetica")
 				before rendering and/or measuring text.
 
                When vended by legible output, an attributed string will have at most one of kCMTextMarkupAttribute_FontFamilyName or
                kCMTextMarkupAttribute_GenericFontFamilyName associated with each character.
 
                Overview of Generic Font Family Names
                =====================================
                Some media formats allow the specification of font family names to be used to style text they carry. Sometimes, an
                external specification (e.g., CSS) may be used to style the text carried by the media format. In either case, the
                specification may be concrete, indicating an installed platform font (e.g., "Times New Roman", Helvetica). It may be
                abstract, indicating a category of font to use (e.g., serif, sans-serif). This abstract designation is often termed
                a "generic font family".

                CSS for example allows a 'font-family' property specification such as this:

                    font-family: Helvetica, sans-serif;

                This uses both the concrete family name "Helvetica" and the generic family name "sans-serif".

                Generic font families may be common across media formats (e.g., both CSS and 3GPP timed text allow "sans-serif" and "serif").
                Other formats may have generic font identifiers that do not align exactly (e.g., TTML allows "monospaceSerif and "monospaceSansSerif" in
                addition to "monospace"). Some formats might not carry names but have numeric values mapping to a generic font identifier.
                Simply put, different formats use different ways to express their generic fonts.

                The use of generic font families is also important for media accessibility. The Media Accessibility framework can map eight categories
                of abstract fonts to an installed font. Users may choose to override each of these categories to a different installed font. This
                remapping should work if the content or external styling indicates a generic font. It should not however try to remap a concrete font like "Helvetica".
                Consequently, it is important to distinguish between the generic and concrete fonts expressed by the author.

                To accommodate what is expressible in media formats and to support media accessibility overrides, generic font families can be
                specified with the kCMTextMarkupAttribute_GenericFontFamilyName attribute which carries the identifier for one of the various
                generic font specification forms supported across media formats. These generic font identifiers are the kCMTextMarkupGenericFontName_*
                prefixed constants also defined here. New identifers may be added in the future.
 
                Concrete fonts are specified using the kCMTextMarkupAttribute_FontFamilyName attribute also defined in this header.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_GenericFontFamilyName __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
	@abstract   Values for kCMTextMarkupAttribute_GenericFontFamilyName. 

	@const      kCMTextMarkupGenericFontName_Default
 				The generic font name indicating the default font. The default font may also be chosen if no font family is
 				specified (i.e., no kCMTextMarkupAttribute_FontFamilyName or kCMTextMarkupAttribute_GenericFontFamilyName is specified).

	@const      kCMTextMarkupGenericFontName_Serif
 				The generic font name indicating a font with serifs. The font may be proportional or monospaced. E.g., Times New Roman

	@const      kCMTextMarkupGenericFontName_SansSerif
 				The generic font name indicating a font without serifs. The font may be proportional or monospaced. E.g., Helvetica

	@const      kCMTextMarkupGenericFontName_Monospace
 				The generic font name indicating a monospaced font, with or without serifs. E.g., Courier

	@const      kCMTextMarkupGenericFontName_ProportionalSerif
 				The generic font name indicating a proportional font with serifs.

	@const      kCMTextMarkupGenericFontName_ProportionalSansSerif
 				The generic font name indicating a proportional font without serifs.

	@const      kCMTextMarkupGenericFontName_MonospaceSerif
 				The generic font name indicating a monospaced font with serifs.

	@const      kCMTextMarkupGenericFontName_MonospaceSansSerif
 				The generic font name indicating a monospaced font without serifs.

	@const      kCMTextMarkupGenericFontName_Casual
 				The generic font name indicating a "casual" font. E.g., Dom or Impress

	@const      kCMTextMarkupGenericFontName_Cursive
 				The generic font name indicating a cursive font. E.g., Coronet or Marigold

	@const      kCMTextMarkupGenericFontName_Fantasy
 				The generic font name indicating a "fantasy" font.

	@const      kCMTextMarkupGenericFontName_SmallCapital
 				The generic font name indicating a font with lowercase letters set as small capitals. E.g., Engravers Gothic
 */
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_Default               __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_Serif                 __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_SansSerif             __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_Monospace             __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_ProportionalSerif     __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_ProportionalSansSerif __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_MonospaceSerif        __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_MonospaceSansSerif    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_Casual                __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_Cursive               __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_Fantasy               __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupGenericFontName_SmallCapital          __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);


/*!
    @const      kCMTextMarkupAttribute_BaseFontSizePercentageRelativeToVideoHeight
    @abstract   The base font size expressed as a percentage of the video height.
 
    @discussion Value must be a non-negative CFNumber.  This is a number holding a percentage of the height of the video frame.  For example, a value of 5 indicates that the base font size should be 5% of the height of the video.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_BaseFontSizePercentageRelativeToVideoHeight __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
    @const      kCMTextMarkupAttribute_RelativeFontSize
    @abstract   The font size expressed as a percentage of the current default font size.
 
    @discussion Value must be a non-negative CFNumber. This is a number holding a percentage
                of the size of the calculated default font size.  A value
                of 120 indicates 20% larger than the default font size. A value of 80
                indicates 80% of the default font size.  The value 100 indicates no size
                difference and is the default.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_RelativeFontSize __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_6_0);

/*!
	@const      kCMTextMarkupAttribute_VerticalLayout
	@abstract   The kind of vertical layout of the text block.

	@discussion Value must be a CFString.
 				A CFString holding one of several values indicating the progression direction for new vertical
 				lines of text. If this attribute is present, it indicates the writing direction is vertical. The 
				attribute value indicates whether new vertical text lines are added from left to right or from 
				right to left. If this attribute is missing, the writing direction is horizontal.
				
				If used, this attribute must be applied to the entire attributed string (i.e., 
                CFRangeMake(0, CFAttributedStringGetLength(...))).
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_VerticalLayout __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
	@abstract   Values for kCMTextMarkupAttribute_VerticalLayout. 
	
	@const      kCMTextVerticalLayout_LeftToRight
				Newly added vertical lines are added from the left toward the right.
				
	@const      kCMTextVerticalLayout_RightToLeft
				Newly added vertical lines are added from the right toward the left.
*/
CM_EXPORT const CFStringRef kCMTextVerticalLayout_LeftToRight __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT const CFStringRef kCMTextVerticalLayout_RightToLeft __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);


/*!
	@const      kCMTextMarkupAttribute_Alignment
	@abstract   The alignment of text in the writing direction of the first line of text.

	@discussion Value must be a CFString.
				A CFString holding one of several values indicating the alignment 
				in the writing direction of the first line of text of the cue. 
				The writing direction is indicated by the value (or absence) of 
				the kCMTextMarkupAttribute_VerticalLayout. 
				
				If this attribute is missing, the kCMTextMarkupAlignmentType_Middle value should
				be used as the default.
				
				If used, this attribute must be applied to the entire attributed string (i.e., 
                CFRangeMake(0, CFAttributedStringGetLength(...))).
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_Alignment __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
	@abstract   Values for kCMTextMarkupAttribute_Alignment. 
	
	@const      kCMTextMarkupAlignmentType_Start
				The text is visually aligned at its starting side. For horizontally written text, the alignment is left for 
				left-to-right text and right for right-to-left text. For vertical text, alignment is always at the top.

	@const      kCMTextMarkupAlignmentType_Middle
				The text is visually center-aligned (i.e., aligned between its starting and ending sides). 

	@const      kCMTextMarkupAlignmentType_End
				The text is visually aligned at its ending side. For horizontally written text, the alignment is right for 
				left-to-right text and left for right-to-left text. For vertical text, alignment is always at the bottom.

	@const      kCMTextMarkupAlignmentType_Left
				For horizontally written text, the text alignment is always visually left-aligned (i.e., left-to-right and right-to-left 
				are treated uniformly). For vertical text, this is equivalent to kCMTextMarkupAlignmentType_Start. While readers
				should be prepared to account for kCMTextMarkupAlignmentType_Left being equivalent to 
				kCMTextMarkupAlignmentType_Start for vertical text, authors are discouraged from using kCMTextMarkupAlignmentType_Left
				for vertical text.

	@const      kCMTextMarkupAlignmentType_Right
				For horizontally written text, the text alignment is always visually right-aligned (i.e., left-to-right and right-to-left 
				are treated uniformly). For vertical text, this is equivalent to kCMTextMarkupAlignmentType_End. While readers
				should be prepared to account for kCMTextMarkupAlignmentType_Right being equivalent to 
				kCMTextMarkupAlignmentType_End for vertical text, authors are discouraged from using kCMTextMarkupAlignmentType_Right
				for vertical text.
*/
CM_EXPORT const CFStringRef kCMTextMarkupAlignmentType_Start __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT const CFStringRef kCMTextMarkupAlignmentType_Middle __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT const CFStringRef kCMTextMarkupAlignmentType_End __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT const CFStringRef kCMTextMarkupAlignmentType_Left __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT const CFStringRef kCMTextMarkupAlignmentType_Right __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);


/*!
	 @const      kCMTextMarkupAttribute_TextPositionPercentageRelativeToWritingDirection
	 @abstract   The placement of the block of text specified as a percentage in the writing direction.
	 
	 @discussion Value must be a non-negative CFNumber.
				 A CFNumber expressing the position of the
				 center of the text in the writing direction as a percentage of the video dimensions in 
				 the writing direction. For horizontal cues, this is the horizontal position. 
				 For vertical, it is the vertical position. The percentage is calculated 
				 from the edge of the frame where the text begins (so for left-to-right 
				 English, it is the left edge).
				 
				 If used, this attribute must be applied to the entire attributed string (i.e., 
                 CFRangeMake(0, CFAttributedStringGetLength(...))).
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_TextPositionPercentageRelativeToWritingDirection __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0); 

/*!
	@const      kCMTextMarkupAttribute_OrthogonalLinePositionPercentageRelativeToWritingDirection
	@abstract   The placement of the block of text's first line specified as a percentage in the 
				direction orthogonal to the writing direction.

	@discussion Value must be a non-negative CFNumber.
				A CFNumber expressing the position of the center of the
				cue relative to the writing direction. The line 
				position is orthogonal (or perpendicular) to the writing direction (i.e., 
				for a horizontal writing direction, it is vertical and for a vertical writing 
				direction, is is horizontal). This attribute expresses the line position as 
				a percentage of the dimensions of the video frame in the relevant direction. 
				For example, 0% is the top of the video frame and 100% is the bottom of the 
				video frame for horizontal writing layout.
				
				If used, this attribute must be applied to the entire attributed string (i.e., 
                CFRangeMake(0, CFAttributedStringGetLength(...))).
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_OrthogonalLinePositionPercentageRelativeToWritingDirection __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
	
/*!
	@const      kCMTextMarkupAttribute_WritingDirectionSizePercentage
	@abstract   The dimension (e.g., width) of the bounding box containing the text expressed as a percentage.

	@discussion Value must be a non-negative CFNumber.
				A CFNumber expressing the width of the 
				bounding box for text layout as a percentage of the video frame's dimension
				in the writing direction. 
				For a horizontal writing direction, it is the width. For a vertical writing 
				direction, it is the horizontal writing direction.
				
				If used, this attribute must be applied to the entire attributed string (i.e., 
                CFRangeMake(0, CFAttributedStringGetLength(...))).
*/
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_WritingDirectionSizePercentage __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
	@const      kCMTextMarkupAttribute_CharacterEdgeStyle
	@abstract   Allows the setting of the style of character edges at render time.

	@discussion Value must be a CFString. This controls the shape of the edges of
				drawn characters. Set a value of something other than kCMTextMarkupEdgeStyle_None
				to draw using an alternative shape for edges of characters from the set of constants
				prefixed with "kCMTextMarkupEdgeStyle_". These correspond to text edge styles available
				with Media Accessibility preferences (see <MediaAccessibility/MACaptionAppearance.h>)
				although the values are not enumerated integers here.
				
				The absence of this attribute should be treated as though kCMTextMarkupCharacterEdgeStyle_None
				is specified.
 */
CM_EXPORT const CFStringRef kCMTextMarkupAttribute_CharacterEdgeStyle __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

/*!
	@abstract   Values for kCMTextMarkupAttribute_CharacterEdgeStyle. 

	@const      kCMTextMarkupCharacterEdgeStyle_None
				The character edge style indicating no edge style.

	@const      kCMTextMarkupCharacterEdgeStyle_Raised
				The character edge style indicating a raised edge style should be drawn.

	@const      kCMTextMarkupCharacterEdgeStyle_Depressed
				The character edge style indicating a depressed edge style should be drawn.

	@const      kCMTextMarkupCharacterEdgeStyle_Uniform
				The character edge style indicating a uniform border around the character should be drawn.

	@const      kCMTextMarkupCharacterEdgeStyle_DropShadow
				The character edge style indicating a drop shadow should be drawn.
 */
CM_EXPORT  const CFStringRef kCMTextMarkupCharacterEdgeStyle_None       __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupCharacterEdgeStyle_Raised     __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupCharacterEdgeStyle_Depressed  __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupCharacterEdgeStyle_Uniform    __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);
CM_EXPORT  const CFStringRef kCMTextMarkupCharacterEdgeStyle_DropShadow __OSX_AVAILABLE_STARTING(__MAC_10_9, __IPHONE_7_0);

CM_ASSUME_NONNULL_END

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // CMTEXTMARKUP_H
// ==========  CoreMedia.framework/Headers/CoreMedia.h
/* 
	File:  CoreMedia.h
	
	Framework:  CoreMedia

    Copyright 2010-2014 Apple Inc. All rights reserved.
    
	To report bugs, go to:  http://developer.apple.com/bugreporter/

 */

#include <CoreMedia/CMBase.h>
#include <CoreMedia/CMTime.h>
#include <CoreMedia/CMTimeRange.h>
#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMFormatDescriptionBridge.h>
#include <CoreMedia/CMAttachment.h>
#include <CoreMedia/CMBufferQueue.h>
#include <CoreMedia/CMBlockBuffer.h>
#include <CoreMedia/CMSampleBuffer.h>
#include <CoreMedia/CMSimpleQueue.h>
#include <CoreMedia/CMMemoryPool.h>
#include <CoreMedia/CMSync.h>
#include <CoreMedia/CMTextMarkup.h>
#include <CoreMedia/CMMetadata.h>
#if TARGET_OS_IPHONE
#include <CoreMedia/CMAudioClock.h>
#else
#include <CoreMedia/CMAudioDeviceClock.h>
#endif
// ==========  CoreMedia.framework/Headers/CMMetadata.h
/*
    File:  CMMetadata.h
	
	Framework:  CoreMedia
 
    Copyright ¬© 2013-2015 Apple Inc. All rights reserved.
 
*/

#ifndef CMMETADATA_H
#define CMMETADATA_H

/*!
	@header
	@abstract	API for creating and manipulating metadata.
	@discussion	This API covers two services:  Metadata Identifier Services,
				and the Metadata Data Type Registry.
	
				Metadata Identifier Services provide a means of encoding the
				metadata identifying tuple (four byte key namespace and n-byte
				key value) into CFString, and back again.
				
				The Metadata Data Type Registry allows a process to register
				metadata data types that conform to a base data type
				and (optionally) other registered data types.  The registry
				simplifies the process of creating format descriptions for
				non-trivial metadata values, as well as allowing clients to
				indicate how metadata can be interpreted.
*/

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreMedia/CMFormatDescription.h>
#include <CoreMedia/CMBlockBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma pack(push, 4)
	
CF_IMPLICIT_BRIDGING_ENABLED

/*! 
	@group	Errors
*/

/*!
	@enum CMMetadata Identifier Errors
	@discussion The errors returned from the CMMetadata Identifier APIs
	@constant	kCMMetadataIdentifierError_AllocationFailed An allocation failed.
	@constant	kCMMetadataIdentifierError_RequiredParameterMissing NULL or 0 was passed for a required parameter.
	@constant	kCMMetadataIdentifierError_BadKey An invalid key was passed.
	@constant	kCMMetadataIdentifierError_BadKeyLength A key was passed that had an invalid length.
	@constant	kCMMetadataIdentifierError_BadKeyType A bad type was passed for a key.
	@constant	kCMMetadataIdentifierError_BadNumberKey The number passed for a key was not valid (not in the range 0-0xFFFFFFFF).
	@constant	kCMMetadataIdentifierError_BadKeySpace The keyspace passed in was invalid.
	@constant	kCMMetadataIdentifierError_BadIdentifier The identifier passed in was invalid.
	@constant	kCMMetadataIdentifierError_NoKeyValueAvailable A keyvalue was requested for the anonymous keyspace ('anon').
*/
// Range -16300 to -16309
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMMetadataIdentifierError_AllocationFailed				= -16300,
	kCMMetadataIdentifierError_RequiredParameterMissing		= -16301,
	kCMMetadataIdentifierError_BadKey						= -16302,
	kCMMetadataIdentifierError_BadKeyLength					= -16303,
	kCMMetadataIdentifierError_BadKeyType					= -16304,
	kCMMetadataIdentifierError_BadNumberKey					= -16305,
	kCMMetadataIdentifierError_BadKeySpace					= -16306,
	kCMMetadataIdentifierError_BadIdentifier				= -16307,
	kCMMetadataIdentifierError_NoKeyValueAvailable			= -16308,
};

/*!
	@enum CMMetadata DataType Registry Errors
	@discussion The errors returned from the CMMetadata DataType Registry APIs
	@constant	kCMMetadataDataTypeRegistryError_AllocationFailed An allocation failed.
	@constant	kCMMetadataDataTypeRegistryError_RequiredParameterMissing NULL or 0 was passed for a required parameter.
	@constant	kCMMetadataDataTypeRegistryError_BadDataTypeIdentifier Bad datatype identifier.
	@constant	kCMMetadataDataTypeRegistryError_DataTypeAlreadyRegistered Datatype already registered.
	@constant	kCMMetadataDataTypeRegistryError_RequiresConformingBaseType Data type passed in requires a conforming data type that resolves to a base data type.
	@constant	kCMMetadataDataTypeRegistryError_MultipleConformingBaseTypes Data type passed specified more than one base data type.
*/
// Range -16310 to -16319
#if COREMEDIA_USE_DERIVED_ENUMS_FOR_CONSTANTS
enum : OSStatus
#else
enum
#endif
{
	kCMMetadataDataTypeRegistryError_AllocationFailed				= -16310,
	kCMMetadataDataTypeRegistryError_RequiredParameterMissing		= -16311,
	kCMMetadataDataTypeRegistryError_BadDataTypeIdentifier			= -16312,
	kCMMetadataDataTypeRegistryError_DataTypeAlreadyRegistered		= -16313,
	kCMMetadataDataTypeRegistryError_RequiresConformingBaseType		= -16314,
	kCMMetadataDataTypeRegistryError_MultipleConformingBaseTypes	= -16315,
};


/*!
	@group	Metadata Identifier Services
*/

/*!
	@const kCMMetadataKeySpace_QuickTimeUserData
		Metadata keyspace for QuickTime User Data keys.
	@const kCMMetadataKeySpace_ISOUserData
		Metadata keyspace for MPEG-4 User Data keys.
	@const kCMMetadataKeySpace_QuickTimeMetadata
		Metadata keyspace for QuickTime Metadata keys.
	@const kCMMetadataKeySpace_iTunes
		Metadata keyspace for iTunes keys.
	@const kCMMetadataKeySpace_ID3
		Metadata keyspace for ID3 keys.
	@const kCMMetadataKeySpace_Icy
		Metadata keyspace for ShoutCast keys.
*/
CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMMetadataKeySpace_QuickTimeUserData
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataKeySpace_ISOUserData
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataKeySpace_QuickTimeMetadata
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataKeySpace_iTunes
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataKeySpace_ID3
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataKeySpace_Icy
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataLocation_ISO6709
		Location information in ISO-6709 format.
	@const kCMMetadataIdentifier_QuickTimeMetadataDirection_Facing
		Direction the observer is facing.
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataLocation_ISO6709
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataDirection_Facing
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataPreferredAffineTransform
		An affine transform that can be used in place of a track matrix for
		displaying a video track, to better reflect the current orientation
		of a video camera with respect to a scene.  For example, if the camera
		is rotated after a recording has started, the presence of this metadata
		will allow a player to adjust its rendering at the time the rotation occurred.
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataPreferredAffineTransform
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@const kCMMetadataIdentifier_QuickTimeMetadataVideoOrientation
		Video orientation as defined by TIFF/EXIF, which is enumerated by CGImagePropertyOrientation
		(see <ImageIO/CGImageProperties.h>).
*/
CM_EXPORT const CFStringRef kCMMetadataIdentifier_QuickTimeMetadataVideoOrientation
								__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
	
CM_ASSUME_NONNULL_END

CF_IMPLICIT_BRIDGING_DISABLED

/*! 
	@functiongroup	Metadata Identifier services
*/

/*!
	@function	CMMetadataCreateIdentifierForKeyAndKeySpace
	@abstract	Creates a URL-like string identifier that represents a key/keyspace tuple.
    @discussion Metadata entities are identified by a key whose interpretation
                is defined by its keyspace.  When writing metadata to a QuickTime
                Movie, this tuple is part of the track's format description.
				
                The following constants make up the current list of supported keyspaces,
				which are documented elsewhere in this file:
<ul>				kCMMetadataKeySpace_QuickTimeUserData
<li>				kCMMetadataKeySpace_ISOUserData
<li>				kCMMetadataKeySpace_iTunes
<li>				kCMMetadataKeySpace_ID3
<li>				kCMMetadataKeySpace_QuickTimeMetadata
<li>				kCMMetadataKeySpace_Icy
</ul>
				Some keyspaces use OSTypes (a.k.a. FourCharCodes) to define their
				keys, and as such their keys are four bytes in length. The keyspaces
				that fall into this category are: kCMMetadataKeySpace_QuickTimeUserData,
				kCMMetadataKeySpace_ISOUserData, kCMMetadataKeySpace_iTunes, and
				kCMMetadataKeySpace_ID3.
				
				The keyspace kCMMetadataKeySpace_QuickTimeMetadata defines its
				key values to be expressed as reverse-DNS strings, which allows
				third parties to define their own keys in a well established way
				that avoids collisions.
				
				As a matter of convenience, known keyspaces allow for a key
				to be passed in using a variety of CFTypes.  Note that what
				is returned by CMMetadataCreateKeyFromIdentifier depends upon the
				keyspace, and may be a different CFType than what is passed
				to this routine (see the discussion below for what CFTypes are
				returned for known keyspaces).  To get a key represented as
				CFData, call CMMetadataCreateKeyFromIdentifierAsCFData.
				
				For OSType keyspaces, a key may be passed as a CFNumber,
				a CFString, or a CFData. A key passed as a CFNumber will have
				its value retrieved as kCFNumberSInt32Type comprising the four
				bytes of the key‚Äôs numeric value in big-endian byte order.
				A key passed as a CFString must be a valid ASCII string of four
				characters. A key passed as a CFData must be comprised of the
				four bytes of the key‚Äôs numeric value in big-endian byte order.
				
				All other keyspaces allow the key to be passed as a CFString
				or CFData. In both cases, the key will be interpreted as an
				ASCII string for the purposes of identifier encoding.
*/
CM_EXPORT
OSStatus CMMetadataCreateIdentifierForKeyAndKeySpace(
	CFAllocatorRef CM_NULLABLE allocator,					/*! @param allocator
																Allocator to use for creating the identifier. */
	CFTypeRef CM_NONNULL key,								/*! @param key
																Key data;  may be CFString, CFNumber, or CFData. */
	CFStringRef CM_NONNULL keySpace,						/*! @param keySpace
																Keyspace;  must be string of one to four printable
																ASCII characters. */
	CM_RETURNS_RETAINED_PARAMETER CFStringRef CM_NULLABLE * CM_NONNULL identifierOut)		/*! @param identifierOut
																The created identifier. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataCreateKeyFromIdentifier
    @abstract   Creates a copy of the key encoded in the identifier as a CFType.
    @discussion	The returned CFType is based on the keyspace encoded in the identifier.
    			
    			For OSType keyspaces, the key will be returned as a CFNumber,
				where a big endian interpretation of its kCFNumberSInt32Type value
				represents the four bytes of the key's numeric value.
    			
    			For the keyspaces kCMMetadataKeySpace_QuickTimeMetadata and
				kCMMetadataKeySpace_Icy, the key will be returned as a CFString.
				
				All other keyspaces will have the function return the key as a CFData.
*/
CM_EXPORT
OSStatus CMMetadataCreateKeyFromIdentifier(
	CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator
													Allocator to use for creating the key. */
	CFStringRef CM_NONNULL identifier,			/*! @param identifier
										Identifier being inspected. */
	CM_RETURNS_RETAINED_PARAMETER CFTypeRef CM_NULLABLE * CM_NONNULL keyOut)				/*! @param keyOut
										The key data that was used create the identifier. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataCreateKeyFromIdentifierAsCFData
    @abstract   Creates a copy of the key value that was encoded in the identifier as CFData.
				The bytes in the CFData correpsond to how they are serialized in the file.
*/
CM_EXPORT
OSStatus CMMetadataCreateKeyFromIdentifierAsCFData(
	CFAllocatorRef CM_NULLABLE allocator,		/*! @param allocator
													Allocator to use for creating the key. */
	CFStringRef CM_NONNULL identifier,			/*! @param identifier
													Identifier being inspected. */
	CM_RETURNS_RETAINED_PARAMETER CFDataRef CM_NULLABLE * CM_NONNULL keyOut)	/*! @param keyOut
													The key data that was used create the identifier, as a CFData. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataCreateKeySpaceFromIdentifier
    @abstract   Creates a copy of the key value that was encoded in the identifier as CFData.
*/
CM_EXPORT
OSStatus CMMetadataCreateKeySpaceFromIdentifier(
	CFAllocatorRef CM_NULLABLE allocator,				/*! @param allocator
															Allocator to use for creating the keyspace. */
	CFStringRef CM_NONNULL identifier,					/*! @param identifier
															Identifier being inspected. */
	CM_RETURNS_RETAINED_PARAMETER CFStringRef CM_NULLABLE * CM_NONNULL keySpaceOut)	/*! @param keySpaceOut
															The key space that was used to create the identifier. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
CF_IMPLICIT_BRIDGING_ENABLED

/*!
	@group	Metadata Datatype Registry
*/

/*!
	@const kCMMetadataBaseDataType_RawData
		A sequence of bytes whose interpretation based upon an agreement between
		the reader and the writer.
	@const kCMMetadataBaseDataType_UTF8
		UTF-8 string.
	@const kCMMetadataBaseDataType_UTF16
		UTF-16 string.
	@const kCMMetadataBaseDataType_GIF
		GIF image.
	@const kCMMetadataBaseDataType_JPEG
		JPEG image.
	@const kCMMetadataBaseDataType_PNG
		PNG image.
	@const kCMMetadataBaseDataType_BMP
		BMP image.
	@const kCMMetadataBaseDataType_Float32
		32-bit big endian floating point number.
	@const kCMMetadataBaseDataType_Float64
		64-bit big endian floating point number.
	@const kCMMetadataBaseDataType_SInt8
		8-bit signed integer.
	@const kCMMetadataBaseDataType_SInt16
		16-bit big endian signed integer.
	@const kCMMetadataBaseDataType_SInt32
		32-bit big endian signed integer.
	@const kCMMetadataBaseDataType_SInt64
		64-bit big endian signed integer.
	@const kCMMetadataBaseDataType_UInt8
		8-bit unsigned integer.
	@const kCMMetadataBaseDataType_UInt16
		16-bit big endian unsigned integer.
	@const kCMMetadataBaseDataType_UInt32
		32-bit big endian unsigned integer.
	@const kCMMetadataBaseDataType_UInt64
		64-bit big endian unsigned integer.
	@const kCMMetadataBaseDataType_PointF32
		Consists of two 32-bit big endian floating point values, the x and y values, respectively.
	@const kCMMetadataBaseDataType_DimensionsF32
		Consists of a 32-bit big endian floating point x value followed by a 32-bit floating point y value.
	@const kCMMetadataBaseDataType_RectF32
		Consists of four 32-bit big endian floating point values, the origin's x, origin's y, width and height values, respectively.
		May also be interpreted as a 32-bit floating point origin followed by a 32-bit floating point dimension.
	@const kCMMetadataDataType_AffineTransformF64
		A 3x3 matrix of 64-bit big endian floating point numbers stored in row-major order that specify an affine transform.
	@const kCMMetadataBaseDataType_PolygonF32
		Three or more pairs of 32-bit floating point numbers (x and y values) that define the verticies of a polygon.
	@const kCMMetadataBaseDataType_PolylineF32
		Two or more pairs of 32-bit floating point numbers (x and y values) that define a multi-segmented line.
	@const kCMMetadataBaseDataType_JSON
		UTF-8 encoded JSON data.
*/
CM_ASSUME_NONNULL_BEGIN

CM_EXPORT const CFStringRef kCMMetadataBaseDataType_RawData
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UTF8
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UTF16
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_GIF
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_JPEG
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PNG
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_BMP
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_Float32
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_Float64
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt8
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt16
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt32
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_SInt64
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt8
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt16
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt32
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_UInt64
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PointF32
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_DimensionsF32
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_RectF32
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_AffineTransformF64
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PolygonF32
								__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_PolylineF32
								__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);
CM_EXPORT const CFStringRef kCMMetadataBaseDataType_JSON
								__OSX_AVAILABLE_STARTING(__MAC_10_11,__IPHONE_9_0);

/*!
	@const kCMMetadataDataType_Location_ISO6709
		A string supplying location information in ISO-6709 format.  Conforms to
		kCMMetadataBaseDataType_UTF8.
	@const kCMMetadataDataType_Direction
		A string supplying degrees offset from magnetic North.  Conforms to
		kCMMetadataBaseDataType_UTF8.
*/
CM_EXPORT const CFStringRef kCMMetadataDataType_QuickTimeMetadataLocation_ISO6709
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
CM_EXPORT const CFStringRef kCMMetadataDataType_QuickTimeMetadataDirection
								__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

CM_ASSUME_NONNULL_END

/*! 
	@functiongroup	Metadata DataType Registry
*/

/*!
	@function	CMMetadataDataTypeRegistryRegisterDataType
	@abstract	Register a data type with the data type registry.
	@discussion	This routine is called by clients to register a data type with
				the data type registry.  The list of conforming data type identifiers
				must include a base data type.  If the data type has already
				been registered, then it is not considered an error to re-register it
				as long as the list of conforming data type identifiers has the same
				entries as the original;  otherwise an error will be returned.
*/
CM_EXPORT
OSStatus CMMetadataDataTypeRegistryRegisterDataType(
	CFStringRef CM_NONNULL dataType,						/*! @param dataType
																Identifier of data type being registered. */
	CFStringRef CM_NONNULL description,						/*! @param description
																Human readable description of data type being registered
																(for aiding debugging operations) */
	CFArrayRef CM_NONNULL conformingDataTypes)				/*! @param conformingDataTypes
																Data types that this data type conforms to. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataDataTypeRegistryDataTypeIsRegistered
	@abstract	Tests a data type identifier to see if it has been registered.
*/
CM_EXPORT
Boolean CMMetadataDataTypeRegistryDataTypeIsRegistered(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being checked. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataDataTypeRegistryGetDataTypeDescription
	@abstract	Returns the data type's description (if any was provided when it was registered).
*/
CM_EXPORT
CFStringRef CM_NONNULL CMMetadataDataTypeRegistryGetDataTypeDescription(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataDataTypeRegistryGetConformingDataTypes
	@abstract	Returns the data type's conforming data types (if any were
				provided when it was registered).
	@returns	List of conforming data types registered for the given data type.
				NULL is returned if the data type has not been registered.
*/
CM_EXPORT
CFArrayRef CM_NONNULL CMMetadataDataTypeRegistryGetConformingDataTypes(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataDataTypeRegistryDataTypeConformsToDataType
	@abstract	Checks to see if a data type conforms to another data type.
	@discussion	A given data type will conform to a second data type if any of
				the following are true:
<ul>				1. The data type identifiers are the same.
<li>				2. The first data type identifier's conformance list contains the second data type identifier.
<li>				3. A recursive search of the conforming data types for each element in the first
<li>				   data type's conformance list yields the second data type identifer.
</ul>
	@returns	True if the first data type conforms to the second data type.
*/
CM_EXPORT
Boolean CMMetadataDataTypeRegistryDataTypeConformsToDataType(
	CFStringRef CM_NONNULL dataType,						/*! @param dataType
																Identifier of data type being interrogated. */
	CFStringRef CM_NONNULL conformsToDataType)				/*! @param conformsToDataType
																Identifier of data type being checked as as
																conforming data type. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataDataTypeRegistryGetBaseDataTypes
	@abstract	Returns an array of base data type identifiers.
	@discussion	There are a set of base data types that seed the data type
				registry.  All valid data types will have their conformance search
				end with a base data type.
*/
CM_EXPORT
CFArrayRef CM_NULLABLE CMMetadataDataTypeRegistryGetBaseDataTypes(void)
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataDataTypeRegistryDataTypeIsBaseDataType
	@abstract	Tests a data type identifier to see if it represents a base data type.
	@discussion	This is simply a convenience method to test to see if a given
				data type identifier is in the array returned by
				CMMetadataDataTypeRegistryGetBaseDataTypes.
*/
CM_EXPORT
Boolean CMMetadataDataTypeRegistryDataTypeIsBaseDataType(
	CFStringRef CM_NONNULL dataType)						/*! @param dataType
																Identifier of data type being checked. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);

/*!
	@function	CMMetadataDataTypeRegistryGetBaseDataTypeForConformingDataType
	@abstract	Returns the base data type identifier that the given data type
				conforms to.
	@discussion	There are a set of base data types that seed the data type
				registry.  All valid data types will have their conformance search
				end with a base data type.
*/
CM_EXPORT
CFStringRef CM_NONNULL CMMetadataDataTypeRegistryGetBaseDataTypeForConformingDataType(
	CFStringRef CM_NONNULL dataType)								/*! @param dataType
																		Identifier of data type being interrogated. */
							__OSX_AVAILABLE_STARTING(__MAC_10_10,__IPHONE_8_0);
	
CF_IMPLICIT_BRIDGING_DISABLED

#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif
	
#endif // CMMETADATA_H
