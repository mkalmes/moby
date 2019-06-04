// ==========  SoundAnalysis.framework/Headers/SNError.h
//
//  SNError.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SoundAnalysis/SNDefines.h>

SN_EXPORT NSString * const SNErrorDomain API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
typedef NS_ERROR_ENUM(SNErrorDomain, SNErrorCode)
{
    SNErrorCodeUnknownError = 1,
    SNErrorCodeOperationFailed,
    SNErrorCodeInvalidFormat,
    SNErrorCodeInvalidModel
};
// ==========  SoundAnalysis.framework/Headers/SoundAnalysis.h
//
//  SoundAnalysis.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

/** @framework SoundAnalysis
 @abstract A high-level framework for analyzing sound.
 */

#import <Foundation/Foundation.h>

#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNError.h>
#import <SoundAnalysis/SNRequest.h>
#import <SoundAnalysis/SNResult.h>
#import <SoundAnalysis/SNAnalyzer.h>

#import <SoundAnalysis/SNClassifySoundRequest.h>
#import <SoundAnalysis/SNClassificationResult.h>
// ==========  SoundAnalysis.framework/Headers/SNClassificationResult.h
//
//  SNClassificationResult.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNResult.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief The likelihood of a sound belonging to identified class
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNClassification : NSObject

/*!
 @brief The identifier of a classification request. An example classification could be a string like 'laughter' or 'applause'. The string is defined in the model that was used for the classification. Usually these are technical labels that are not localized and not meant to be used directly to be presented to an end user in the UI.
 */
@property (readonly) NSString *identifier;

/*!
 @brief The level of confidence normalized to [0, 1], where 1 is most confident
 */
@property (readonly) double confidence;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/*!
 @brief A result containing the most likely classification candidates in the time range specified
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNClassificationResult : NSObject <SNResult>

/*!
 @brief The top classification candidates, sorted with highest confidence first
 */
@property (readonly) NSArray<SNClassification *> *classifications;

/*!
 @brief The time range in the client-provided audio stream to which this classification result corresponds
 @discussion Each CMTime contains of a value (audio frame count) and timescale (client sample rate). This enables the client to precisely identify the frame range in the original audio stream to which this result corresponds. Time ranges will often be in the past compared to the frame count of the most recent audio buffer provided to the analyzer, due to the inherent audio buffering operations required to deliver a full block of audio to an MLModel.
 */
@property (readonly) CMTimeRange timeRange;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  SoundAnalysis.framework/Headers/SNRequest.h
//
//  SNRequest.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SoundAnalysis/SNDefines.h>

/*!
 @brief The base protocol to which analysis requests conform
 @discussion An analysis request is a configuration that defines the analysis the client wishes to perform on the audio stream. Each request has a corresponding result type, which contains information describing the analysis results. This protocol is designed for all requests provided by the framework to conform to, and shouldn't be conformed to by client objects.
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@protocol SNRequest <NSObject>
@end
// ==========  SoundAnalysis.framework/Headers/SNClassifySoundRequest.h
//
//  SNClassifySoundRequest.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/CoreML.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNRequest.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief Configure an analyzer to perform sound classification using the provided MLModel.
 @discussion When a new classification result is produced, the results observer will be called with an SNClassificationResult. Audio buffers provided to SNAudioStreamAnalyzer may vary in size, and the analyzer will reblock the audio data to the block size expected by the MLModel. By default, analysis will occur on the first audio channel in the audio stream, and the analyzer will apply sample rate conversion if the provided audio does not match the sample rate required by the MLModel.
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNClassifySoundRequest : NSObject <SNRequest>

/*!
 @brief The overlap factor of the windows of audio data provided to the classifier, if the model operates on fixed audio block sizes.
 @discussion When performing audio analysis on fixed audio block sizes, it is common for the analysis windows to overlap by some factor. Without overlapping the analysis windows (when the overlap factor is 0.0), a sound might be split across two analysis windows, which could negatively affect classification performance. Overlapping the analysis windows by 50% ensures each sound will fall near the center of at least one analysis window. The supported range is [0.0, 1.0), and the default value is 0.5. Increasing the overlap factor increases computational complexity, so values greater than 0.5 should be used with care.
 */
@property (readwrite) double overlapFactor;

/*!
 @brief Initializes a sound classification request with the provided MLModel
 @param mlModel The CoreML audio classification model to be used with this request
 @discussion The provided model must accept audio data as input, and output a classification dictionary containing the probability of each category.
 */
- (nullable instancetype)initWithMLModel:(MLModel *)mlModel error:(NSError **)error;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  SoundAnalysis.framework/Headers/SNDefines.h
//
//  SNDefines.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef SNDEFINES_H
#define SNDEFINES_H

#ifdef __cplusplus
# define SN_EXPORT extern "C" __attribute__((visibility("default")))
#else
# define SN_EXPORT extern __attribute__((visibility("default")))
#endif

#endif /* SNDEFINES_H */
// ==========  SoundAnalysis.framework/Headers/SNAnalyzer.h
//
//  SNAnalyzer.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNResult.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief Analyzes a stream of audio data and provides analysis results to the client
 @discussion SNAudioStreamAnalyzer should be used to analyze a stream of audio, represented by a sequence of audio buffers over time.
 */

SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNAudioStreamAnalyzer : NSObject

/*!
 @brief Creates a new analyzer
 @param format The format of the audio stream to be analyzed. Only PCM formats are supported.
 */
- (instancetype)initWithFormat:(AVAudioFormat *)format NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief Adds a new analysis request to the analyzer
 @param request An audio analysis request to be performed on the audio stream
 @param observer The object that will receive the analysis results for the supplied request. The observer is weakly retained by the analyzer.
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify nil for this parameter if you do not want the error information.
 @return YES if the request was successfully added, and NO otherwise.
 @discussion Requests can be added while analysis is in progress. If the analyzer cannot perform the requested analysis, an error will be returned. For example, an error could be returned if the request requires a stream format that doesn't match the analyzer's stream format.
 */
- (BOOL)addRequest:(id<SNRequest>)request withObserver:(id<SNResultsObserving>)observer error:(NSError **)error;

/*!
 @brief Removes an existing analysis request from the analyzer
 @param request An audio analysis request to be removed
 @discussion Requests can be removed while analysis is in progress. Once the removeRequest method returns, the previously registered observer will not receive any more callbacks.
 */
- (void)removeRequest:(id<SNRequest>)request;

/*!
 @brief Removes all requests from the analyzer
 */
- (void)removeAllRequests;

/*!
 @brief Provides the next buffer for analysis
 @param audioBuffer The buffer containing the audio to be processed
 @param audioFramePosition The frame position of the data in the buffer
 @discussion The framePosition should be a monotonically increasing sample timestamp. If the sample timeline is detected to be non-continuous, the analyzer's internal state may reset to account for the jump. Some types of audio analysis are performed at a fixed block size, which may differ from the buffer sizes provided for analysis. For this reason, an analysis request observer may be called zero times, one time, or many times, depending on the relationship between the input buffer size, current analyzer state, and native analysis block size. Any errors produced during analysis will be provided though the request observers. This method may block as a means of indicating backpressure to the caller. These methods are not safe to call from a realtime audio context but may be called from lower priority threads (i.e. AVAudioEngine tap callback or AudioQueue callback).
 */
- (void)analyzeAudioBuffer:(AVAudioBuffer *)audioBuffer atAudioFramePosition:(AVAudioFramePosition)audioFramePosition;

/*!
 @brief Indicates that the audio stream has ended, and no more audio buffers will be analyzed
 @discussion After this method has been called, it is invalid to provide any more audio data for analysis, and any provided buffers will be ignored. This method is useful for types of analysis that may have final results to provide upon the completion of the stream.
 */
- (void)completeAnalysis;

@end


/*!
 @brief Analyzes an audio file and provides analysis results to the client
 */

SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNAudioFileAnalyzer : NSObject

/*!
 @brief Creates a new analyzer
 @param url The url for the audio file to be analyzed
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify nil for this parameter if you do not want the error information.
 */
- (nullable instancetype)initWithURL:(NSURL *)url error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief Adds a new analysis request to the analyzer
 @param request An audio analysis request to be performed on the audio stream
 @param observer The object that will receive the analysis results for the supplied request. The observer is weakly retained by the analyzer.
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify nil for this parameter if you do not want the error information.
 @return YES if the request was successfully added, and NO otherwise.
 @discussion If addRequest is called while the file is being processed, an error will be returned.
 */
- (BOOL)addRequest:(id<SNRequest>)request withObserver:(id<SNResultsObserving>)observer error:(NSError **)error;

/*!
 @brief Removes an existing analysis request from the analyzer
 @param request An audio analysis request to be removed
 @discussion Requests can be removed while analysis is in progress. Once the removeRequest method returns, the previously registered observer will not receive any more callbacks.
 */
- (void)removeRequest:(id<SNRequest>)request;

/*!
 @brief Removes all requests from the analyzer
 */
- (void)removeAllRequests;

/*!
 @brief Analyzes the audio file synchronously
 @discussion This function executes synchronously. Any errors produced during analysis will flow downstream to the request observers. This method may block for a long period of time, so be careful to ensure this call does not block UI or other important tasks.
 */
- (void)analyze;

/*!
 @brief Analyzes the audio file asynchronously
 @discussion This function executes asynchronously, calling the completion after the entire file has completed analysis. Any errors produced during analysis will flow downstream to the request observers. If the cancelAnalysis method is called, the completionHandler will still be called, but with didReachEndOfFile set to NO.
 */
- (void)analyzeWithCompletionHandler:(void (^)(BOOL didReachEndOfFile))completionHandler;

/*!
 @brief Cancels any in-progress analysis of the audio file
 @discussion This function executes asynchronously, and will trigger the completion handler provided in the analyzeWithCompletionHandler method after the cancellation is complete.
 */
- (void)cancelAnalysis;

@end

NS_ASSUME_NONNULL_END
// ==========  SoundAnalysis.framework/Headers/SNResult.h
//
//  SNResult.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNRequest.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief The base protocol to which analysis results conform
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@protocol SNResult <NSObject>
@end

/*!
 @brief The interface through which clients receive the results of an analysis request
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@protocol SNResultsObserving <NSObject>
/*!
 @brief Provides a new analysis result to the client with the specified time range
 @discussion This function will be called each time a new analysis result is available. Different types of analysis may produce results at different rates, spanning different time ranges.
 */
- (void)request:(id<SNRequest>)request didProduceResult:(id<SNResult>)result;

@optional
/*!
 @brief Informs the client of an error produced during analysis
 @discussion If an error is produced by a request, that request will not produce any more results, and is in a terminal state. The request:didFailWithError and requestDidComplete methods are mutually exclusive.
 */
- (void)request:(id<SNRequest>)request didFailWithError:(NSError *)error;

/*!
 @brief Informs the client that the analysis request was completed normally
 @discussion If an analysis request completes normally, that request will not produce any more results, and is in a terminal state. The request:didFailWithError and requestDidComplete methods are mutually exclusive.
 */
- (void)requestDidComplete:(id<SNRequest>)request;

@end

NS_ASSUME_NONNULL_END
