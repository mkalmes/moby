// ==========  Speech.framework/Headers/SFSpeechRecognitionTask.h
//
//  SFSpeechRecognitionTask.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSpeechRecognitionResult;
@class SFTranscription;

typedef NS_ENUM(NSInteger, SFSpeechRecognitionTaskState) {
    SFSpeechRecognitionTaskStateStarting = 0,       // Speech processing (potentially including recording) has not yet begun
    SFSpeechRecognitionTaskStateRunning = 1,        // Speech processing (potentially including recording) is running
    SFSpeechRecognitionTaskStateFinishing = 2,      // No more audio is being recorded, but more recognition results may arrive
    SFSpeechRecognitionTaskStateCanceling = 3,      // No more recognition reuslts will arrive, but recording may not have stopped yet
    SFSpeechRecognitionTaskStateCompleted = 4,      // No more results will arrive, and recording is stopped.
} API_AVAILABLE(ios(10.0));

API_AVAILABLE(ios(10.0))
@interface SFSpeechRecognitionTask : NSObject

@property (nonatomic, readonly) SFSpeechRecognitionTaskState state;

// True if recognition audio input has stopped
@property (nonatomic, readonly, getter=isFinishing) BOOL finishing;
// Instructs the task to stop accepting new audio (e.g. stop recording) but complete processing on audio already buffered.
// This has no effect on URL-based recognition requests, which effectively buffer the entire file immediately.
- (void)finish;

// True if recognition has been cancelled
@property (nonatomic, readonly, getter=isCancelled) BOOL cancelled;
- (void)cancel;

// Reports error that occurred during recognition, if applicable
@property (nonatomic, readonly, copy, nullable) NSError *error;

@end

// Recognition result receiver, to be used for complex or multi-utterance speech recognition requests
API_AVAILABLE(ios(10.0))
@protocol SFSpeechRecognitionTaskDelegate <NSObject>

@optional

// Called when the task first detects speech in the source audio
- (void)speechRecognitionDidDetectSpeech:(SFSpeechRecognitionTask *)task;

// Called for all recognitions, including non-final hypothesis
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didHypothesizeTranscription:(SFTranscription *)transcription;

// Called only for final recognitions of utterances. No more about the utterance will be reported
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didFinishRecognition:(SFSpeechRecognitionResult *)recognitionResult;

// Called when the task is no longer accepting new audio but may be finishing final processing
- (void)speechRecognitionTaskFinishedReadingAudio:(SFSpeechRecognitionTask *)task;

// Called when the task has been cancelled, either by client app, the user, or the system
- (void)speechRecognitionTaskWasCancelled:(SFSpeechRecognitionTask *)task;

// Called when recognition of all requested utterances is finished.
// If successfully is false, the error property of the task will contain error information
- (void)speechRecognitionTask:(SFSpeechRecognitionTask *)task didFinishSuccessfully:(BOOL)successfully;

@end

NS_ASSUME_NONNULL_END
// ==========  Speech.framework/Headers/SFSpeechRecognizer.h
//
//  SFSpeechRecognizer.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//


#import <AVFoundation/AVAudioBuffer.h>
#import <Foundation/Foundation.h>

#import <Speech/SFSpeechRecognitionTaskHint.h>

NS_ASSUME_NONNULL_BEGIN

@class SFSpeechRecognitionRequest;
@class SFSpeechRecognitionResult;
@class SFSpeechRecognitionTask;

@protocol SFSpeechRecognizerDelegate;
@protocol SFSpeechRecognitionTaskDelegate;

typedef NS_ENUM(NSInteger, SFSpeechRecognizerAuthorizationStatus) {
    SFSpeechRecognizerAuthorizationStatusNotDetermined,
    SFSpeechRecognizerAuthorizationStatusDenied,
    SFSpeechRecognizerAuthorizationStatusRestricted,
    SFSpeechRecognizerAuthorizationStatusAuthorized,
} API_AVAILABLE(ios(10.0));

API_AVAILABLE(ios(10.0))
@interface SFSpeechRecognizer : NSObject

// Locales which support speech recognition.
// Note that supported does not mean currently available; some locales may require an internet connection, for example.
+ (NSSet<NSLocale *> *)supportedLocales;

+ (SFSpeechRecognizerAuthorizationStatus)authorizationStatus;
+ (void)requestAuthorization:(void(^)(SFSpeechRecognizerAuthorizationStatus status))handler;

- (nullable instancetype)init; // Returns speech recognizer with user's current locale, or nil if is not supported
- (nullable instancetype)initWithLocale:(NSLocale *)locale NS_DESIGNATED_INITIALIZER; // returns nil if the locale is not supported

@property (nonatomic, readonly, getter=isAvailable) BOOL available;
@property (nonatomic, readonly, copy) NSLocale *locale;

@property (nonatomic, weak) id<SFSpeechRecognizerDelegate> delegate;

// Default task for requests, overrides SFSpeechRecognitionTaskHintUnspecified for requests
@property (nonatomic) SFSpeechRecognitionTaskHint defaultTaskHint;

// Recognize speech utterance with a request
// If request.shouldReportPartialResults is true, result handler will be called
// repeatedly with partial results, then finally with a final result or an error.
- (SFSpeechRecognitionTask *)recognitionTaskWithRequest:(SFSpeechRecognitionRequest *)request
                                          resultHandler:(void (^)(SFSpeechRecognitionResult * __nullable result, NSError * __nullable error))resultHandler;

// Advanced API: Recognize a custom request with with a delegate
// The delegate will be weakly referenced by the returned task
- (SFSpeechRecognitionTask *)recognitionTaskWithRequest:(SFSpeechRecognitionRequest *)request
                                               delegate:(id <SFSpeechRecognitionTaskDelegate>)delegate;

// Queue used the recognizer for recognition task handlers and delegate messages
// Defaults to the main queue
@property (nonatomic, strong) NSOperationQueue *queue;

@end

API_AVAILABLE(ios(10.0))
@protocol SFSpeechRecognizerDelegate <NSObject>
@optional

// Called when the availability of the given recognizer changes
- (void)speechRecognizer:(SFSpeechRecognizer *)speechRecognizer availabilityDidChange:(BOOL)available;

@end

NS_ASSUME_NONNULL_END
// ==========  Speech.framework/Headers/SFSpeechRecognitionRequest.h
//
//  SFSpeechRecognitionRequest.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#import <Speech/SFSpeechRecognitionTaskHint.h>

NS_ASSUME_NONNULL_BEGIN

// A request for a speech recognition from an audio source
API_AVAILABLE(ios(10.0))
@interface SFSpeechRecognitionRequest : NSObject

@property (nonatomic) SFSpeechRecognitionTaskHint taskHint;

// If true, partial (non-final) results for each utterance will be reported.
// Default is true
@property (nonatomic) BOOL shouldReportPartialResults;

// Phrases which should be recognized even if they are not in the system vocabulary
@property (nonatomic, copy) NSArray<NSString *> *contextualStrings;

// String which can be used to identify the receiver by the developer
@property (nonatomic, copy, nullable) NSString *interactionIdentifier;

@end

// A request to recognize speech from a recorded audio file
API_AVAILABLE(ios(10.0))
@interface SFSpeechURLRecognitionRequest : SFSpeechRecognitionRequest

- (instancetype)init NS_UNAVAILABLE;

// Request to transcribe speech from an audio file from the given URL.
- (instancetype)initWithURL:(NSURL *)URL NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, copy) NSURL *URL;

@end

// A request to recognize speech from arbitrary audio buffers
API_AVAILABLE(ios(10.0))
@interface SFSpeechAudioBufferRecognitionRequest : SFSpeechRecognitionRequest

// Preferred audio format for optimal speech recognition
@property (nonatomic, readonly) AVAudioFormat *nativeAudioFormat;

// Append audio to the end of the recognition stream. Must currently be in native format.
- (void)appendAudioPCMBuffer:(AVAudioPCMBuffer *)audioPCMBuffer;
- (void)appendAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

// Indicate that the audio source is finished and no more audio will be appended
- (void)endAudio;

@end

NS_ASSUME_NONNULL_END
// ==========  Speech.framework/Headers/SFSpeechRecognitionTaskHint.h
//
//  SFSpeechRecognitionTaskHint.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>

//  Hints on kind of speech recognition being performed
typedef NS_ENUM(NSInteger, SFSpeechRecognitionTaskHint) {
    SFSpeechRecognitionTaskHintUnspecified = 0,     // Unspecified recognition

    SFSpeechRecognitionTaskHintDictation = 1,       // General dictation/keyboard-style
    SFSpeechRecognitionTaskHintSearch = 2,          // Search-style requests
    SFSpeechRecognitionTaskHintConfirmation = 3,    // Short, confirmation-style requests ("Yes", "No", "Maybe")
} API_AVAILABLE(ios(10.0));
// ==========  Speech.framework/Headers/SFTranscriptionSegment.h
//
//  SFTranscriptionSegment.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// Substrings of a hypothesized transcription
API_AVAILABLE(ios(10.0))
@interface SFTranscriptionSegment : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) NSString *substring;
@property (nonatomic, readonly) NSRange substringRange;

// Relative to start of utterance
@property (nonatomic, readonly) NSTimeInterval timestamp;
@property (nonatomic, readonly) NSTimeInterval duration;

// Confidence in the accuracy of transcription. Scale is 0 (least confident) to 1.0 (most confident)
@property (nonatomic, readonly) float confidence;

// Other possible interpretations of this segment
@property (nonatomic, readonly) NSArray<NSString *> *alternativeSubstrings;

@end

NS_ASSUME_NONNULL_END
// ==========  Speech.framework/Headers/Speech.h
//
//  Speech.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Speech/SFSpeechRecognitionResult.h>
#import <Speech/SFSpeechRecognitionRequest.h>
#import <Speech/SFSpeechRecognitionTask.h>
#import <Speech/SFSpeechRecognitionTaskHint.h>
#import <Speech/SFSpeechRecognizer.h>
#import <Speech/SFTranscriptionSegment.h>
#import <Speech/SFTranscription.h>


// ==========  Speech.framework/Headers/SFTranscription.h
//
//  SFTranscription.h
//  Copyright (c) 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFTranscriptionSegment;

// A hypothesized text form of a speech recording
API_AVAILABLE(ios(10.0))
@interface SFTranscription : NSObject <NSCopying, NSSecureCoding>

// Contains the entire recognition, formatted into a single user-displayable string
@property (nonatomic, readonly, copy) NSString *formattedString;

@property (nonatomic, readonly, copy) NSArray<SFTranscriptionSegment *> *segments;

@end

NS_ASSUME_NONNULL_END
// ==========  Speech.framework/Headers/SFSpeechRecognitionResult.h
//
//  SFSpeechRecognitionResult.h
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SFTranscription;

// A recognized utterance, corresponding to a segment of recorded audio with speech and containing one or more transcriptions hypotheses
API_AVAILABLE(ios(10.0))
@interface SFSpeechRecognitionResult : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) SFTranscription *bestTranscription;

// Hypotheses for possible transcriptions, sorted in decending order of confidence (more likely first)
@property (nonatomic, readonly, copy) NSArray<SFTranscription *> *transcriptions;

// True if the hypotheses will not change; speech processing is complete.
@property (nonatomic, readonly, getter=isFinal) BOOL final;

@end

NS_ASSUME_NONNULL_END
