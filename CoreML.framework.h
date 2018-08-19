// ==========  CoreML.framework/Headers/MLMultiArray.h
//
//  MLMultiArray.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Allowed data types for multidimensional arrays
 */
typedef NS_ENUM(NSInteger, MLMultiArrayDataType) {
    MLMultiArrayDataTypeDouble = 0x10000 | 64,
    MLMultiArrayDataTypeFloat32 = 0x10000 | 32,
    MLMultiArrayDataTypeInt32 = 0x20000 | 32
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


/*!
 * Multidimensional Array
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLMultiArray : NSObject

/// Unsafe pointer to underlying buffer holding the data
@property (readonly, nonatomic) void *dataPointer;

/// Type of element held
@property (readonly, nonatomic) MLMultiArrayDataType dataType;

/// An array containing the sizes of each dimension in the multiarray
@property (readonly, nonatomic) NSArray<NSNumber *> *shape;

/*!
 * An array containing the stride in memory for each dimension.
 * The element referred to by a multidimensional index is located at an offset equal to
 * sum_d index[d]*strides[d]. This offset is in the units of the specified dataType.
 */
@property (readonly, nonatomic) NSArray<NSNumber *> *strides;

/// Count of total number of elements
@property (readonly, nonatomic) NSInteger count;

@end

@interface MLMultiArray (Creation)

/// Create by C-style contiguous array by allocating and managing the necessary memory
- (nullable instancetype)initWithShape:(NSArray<NSNumber *> *)shape
                              dataType:(MLMultiArrayDataType)dataType
                                 error:(NSError **)error;


/// Create by wrapping existing data
- (nullable instancetype)initWithDataPointer:(void *)dataPointer
                                       shape:(NSArray<NSNumber *> *)shape
                                    dataType:(MLMultiArrayDataType)dataType
                                     strides:(NSArray<NSNumber *> *)strides
                                 deallocator:(void (^_Nullable)(void *bytes))deallocator
                                       error:(NSError **)error;

@end

@interface MLMultiArray (NSNumberDataAccess)

/// Get a value by its linear index (assumes C-style index ordering)
- (NSNumber *)objectAtIndexedSubscript:(NSInteger)idx;

/// Get a value by its multidimensional index (NSArray<NSNumber *>)
- (NSNumber *)objectForKeyedSubscript:(NSArray<NSNumber *> *)key;

/// Set a value by its linear index (assumes C-style index ordering)
- (void)setObject:(NSNumber *)obj atIndexedSubscript:(NSInteger)idx;

/// Set a value by subindicies (NSArray<NSNumber *>)
- (void)setObject:(NSNumber *)obj forKeyedSubscript:(NSArray<NSNumber *> *)key;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLFeatureType.h
//
//  MLFeatureType.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * Supported data type enumeration
 */
typedef NS_ENUM(NSInteger, MLFeatureType) {
    // MUST be kept in sync with DataTypes.proto in libmlmodelspec!
    // TODO -- make this handle parameterized types and remove constraints
    // in the Objective-C layer.

    MLFeatureTypeInvalid = 0,

    /// Discrete values, sometimes used to hold numeric encoding of a categorical value
    MLFeatureTypeInt64 = 1,

    /// Continuous values
    MLFeatureTypeDouble = 2,

    // Text or categorical strings
    MLFeatureTypeString = 3,
    
    /// CVPixelBufferRef
    MLFeatureTypeImage = 4,

    /// MLMultiArray
    MLFeatureTypeMultiArray = 5,

    /// Numerically weighted hashable objects (e.g. word counts)
    MLFeatureTypeDictionary = 6,

} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));



// ==========  CoreML.framework/Headers/MLMultiArrayConstraint.h
//
//  MLMultiArrayConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLMultiArray.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Constraint describing expected MLMultiArray properties
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLMultiArrayConstraint : NSObject

/// Required shape of array
@property (readonly, nonatomic) NSArray<NSNumber *> *shape;

/// Required dataType
@property (readonly, nonatomic) MLMultiArrayDataType dataType;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreML.framework/Headers/CoreML.h
//
//  CoreML.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CoreML/MLFeatureType.h>
#import <CoreML/MLFeatureValue.h>
#import <CoreML/MLFeatureDescription.h>
#import <CoreML/MLFeatureProvider.h>
#import <CoreML/MLDictionaryFeatureProvider.h>
#import <CoreML/MLMultiArray.h>

#import <CoreML/MLMultiArrayConstraint.h>
#import <CoreML/MLImageConstraint.h>
#import <CoreML/MLDictionaryConstraint.h>

#import <CoreML/MLModel.h>
#import <CoreML/MLModelDescription.h>
#import <CoreML/MLModelMetadataKeys.h>
#import <CoreML/MLPredictionOptions.h>

#import <CoreML/MLModel+MLModelCompilation.h>

#import <CoreML/MLModelError.h>
// ==========  CoreML.framework/Headers/MLFeatureDescription.h
//
//  MLFeatureDescription.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLFeatureValue.h>
#import <CoreML/MLDictionaryConstraint.h>
#import <CoreML/MLMultiArrayConstraint.h>
#import <CoreML/MLImageConstraint.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Description of a feature
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLFeatureDescription : NSObject<NSCopying>

/// Name of feature
@property (readonly, nonatomic, copy) NSString *name;

/// Type of data
@property (readonly, nonatomic) MLFeatureType type;

/// Whether this feature can take an undefined value or not
@property (readonly, nonatomic, getter=isOptional) BOOL optional;

/// Check if MLFeatureValue is valid based on this description
- (BOOL)isAllowedValue:(MLFeatureValue *)value;

@end

/*!
 * Feature value constraints for specific types
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLFeatureDescription (MLFeatureValueConstraints)

/// Constraint when type == MLFeatureTypeMultiArray, nil otherwise
@property (readonly, nullable, nonatomic) MLMultiArrayConstraint *multiArrayConstraint;

/// Constraint when type == MLFeatureTypeImage, nil otherwise
@property (readonly, nullable, nonatomic) MLImageConstraint *imageConstraint;

/// Constraint when type == MLFeatureTypeDictionary, nil otherwise
@property (readonly, nullable, nonatomic) MLDictionaryConstraint *dictionaryConstraint;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLDictionaryConstraint.h
//
//  MLDictionaryConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureType.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLDictionaryConstraint
 *
 * Constraint describing expected NSDictionary properties
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLDictionaryConstraint : NSObject

/// Required key type, described as MLFeatureType
@property (readonly, nonatomic) MLFeatureType keyType;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreML.framework/Headers/MLDictionaryFeatureProvider.h
//
//  MLDictionaryFeatureProvider.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreML/MLFeatureProvider.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A concrete convenience class conforming to MLFeatureProvider.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLDictionaryFeatureProvider : NSObject<MLFeatureProvider, NSFastEnumeration>

/// Dictionary holding the feature values
@property (readonly, nonatomic) NSDictionary<NSString *, MLFeatureValue *> *dictionary;

/*!
 * Create from a generic dictionary by converting all values to MLFeatureValues
 * or from a dictionary with values already stored as MLFeatureValues.
 *
 * An error results if the values are not or cannot be represented as MLFeatureValues.
 */
- (nullable instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary
                                      error:(NSError **)error;

/// Get the value for specified feature
- (nullable MLFeatureValue *)objectForKeyedSubscript:(NSString *)featureName;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLFeatureValue.h
//
//  MLFeatureValue.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TargetConditionals.h>
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLMultiArray.h>
#import <CoreVideo/CVPixelBuffer.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 * An immutable variant holding a data value of a supported MLFeatureType
 *
 * MLFeatureValue does not support type conversion in its accessor properties. It
 * can also have a missing or undefined value of a well defined type.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLFeatureValue : NSObject<NSCopying>

/// Type of the value for which the corresponding property below is held
@property (readonly, nonatomic) MLFeatureType type;

/// True if the value represents a missing or undefined value
@property (readonly, nonatomic, getter=isUndefined) BOOL undefined;

/// Populated value if the type is MLFeatureTypeInt64
@property (readonly, nonatomic) int64_t int64Value;

/// Populated value if the type is MLFeatureTypeDouble
@property (readonly, nonatomic) double doubleValue;

/// Populated value if the type is MLFeatureTypeString
@property (readonly, nonatomic, copy) NSString *stringValue;

/// Populated value if the type is MLFeatureTypeMultiArray
@property (readonly, nullable, nonatomic) MLMultiArray *multiArrayValue;

/// Populated value if the type is MLFeatureTypeDictionary
@property (readonly, nonatomic) NSDictionary<id, NSNumber *> *dictionaryValue;

/// Populated value if the type is MLFeatureTypeImage
@property (readonly, nullable, nonatomic) CVPixelBufferRef imageBufferValue;

/// Hold an object with the specified value
+ (instancetype)featureValueWithInt64:(int64_t)value;
+ (instancetype)featureValueWithDouble:(double)value;
+ (instancetype)featureValueWithString:(NSString *)value;
+ (instancetype)featureValueWithMultiArray:(MLMultiArray *)value;
+ (instancetype)featureValueWithPixelBuffer:(CVPixelBufferRef)value;

/// Represent an undefined value of a specified type
+ (instancetype)undefinedFeatureValueWithType:(MLFeatureType)type;

/*!
 * For encoding a sparse feature set or for encoding probabilities. Input keys that are not
 * NSNumber * or NSString * are rejected on construction and return a MLModelErrorFeatureTypeMismatch
 * error. Further validation for consistency occurs on evaluation
 */
+ (nullable instancetype)featureValueWithDictionary:(NSDictionary<id, NSNumber *> *)value
                                              error:(NSError **)error;

- (BOOL)isEqualToFeatureValue:(MLFeatureValue *)value;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLModelMetadataKeys.h
//
//  MLModelMetadataKeys.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * Keys to a dictionary that holds useful information about a model.
 * All are optional with the aim of being helpful to a developer or user
 * for descriptive purposes.
 */
typedef NSString * MLModelMetadataKey NS_STRING_ENUM;

/// A short description of what the model does and/or its purpose
extern MLModelMetadataKey const MLModelDescriptionKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A version number encoded as a string
extern MLModelMetadataKey const MLModelVersionStringKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// The author of this model
extern MLModelMetadataKey const MLModelAuthorKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// License information for the model
extern MLModelMetadataKey const MLModelLicenseKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Any additional pertinent information specified by the model creator
extern MLModelMetadataKey const MLModelCreatorDefinedKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// ==========  CoreML.framework/Headers/MLModelError.h
//
//  MLModelError.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString * const MLModelErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

typedef enum MLModelError : NSInteger {
    MLModelErrorGeneric = 0,
    MLModelErrorFeatureType = 1,
    MLModelErrorIO = 3,
} MLModelError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLFeatureProvider.h
//
//  MLFeatureProvider.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreML/MLFeatureValue.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * Protocol for accessing a feature value for a feature name
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@protocol MLFeatureProvider

@property (readonly, nonatomic) NSSet<NSString *> *featureNames;

/// Returns nil if the provided featureName is not in the set of featureNames
- (nullable MLFeatureValue *)featureValueForName:(NSString *)featureName;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreML.framework/Headers/MLModel+MLModelCompilation.h
//
//  MLModel+MLModelCompilation.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <CoreML/MLModel.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModel (MLModelCompilation)
 *
 * Class with utilties for performing .mlmodel compilation
 */
@interface MLModel (MLModelCompilation)

/*!
 * Compile a .mlmodel for this device
 *
 * @param modelURL URL file path to .mlmodel file you wish to compile
 * @param error Any errors are surfaced here
 *
 * @returns a URL to the compiled .mlmodelc bundle if successful
 * The model is compiled to a temporary location on disk
 * You must move the compiled model to a permenant location if you wish to keep it
 *
 * @discussion the returned model can be loaded using:
 * @code
 * [MLModel modelWithContentsOfURL:error:]
 * @endcode
 *
 */
+ (nullable NSURL *)compileModelAtURL:(NSURL *)modelURL
                                error:(NSError **)error
                                API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) __WATCHOS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLModelDescription.h
//
//  MLModelDescription.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <CoreML/MLFeatureDescription.h>
#import <CoreML/MLModelMetadataKeys.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A description of a model containing input and output feature descriptions, optionally outputted features
 * with special meaning and metadata.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLModelDescription : NSObject

/// Description of the inputs to the model
@property (readonly, nonatomic) NSDictionary<NSString *, MLFeatureDescription *> *inputDescriptionsByName;

/// Description of the outputs from the model
@property (readonly, nonatomic) NSDictionary<NSString *, MLFeatureDescription *> *outputDescriptionsByName;

/// Name of the primary target / predicted output feature in the output descriptions
@property (readonly, nullable, nonatomic, copy) NSString *predictedFeatureName;

/// Key for all predicted probabilities stored as a MLFeatureTypeDictionary in the output descriptions
@property (readonly, nullable, nonatomic, copy) NSString *predictedProbabilitiesName;

/// Optional metadata describing the model
@property (readonly, nonatomic) NSDictionary<MLModelMetadataKey, id> *metadata;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLImageConstraint.h
//
//  MLImageConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLImageConstraint
 *
 * Constraint on image properties.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLImageConstraint : NSObject

/// The required height of the image
@property (readonly, nonatomic) NSInteger pixelsHigh;

/// The required width of the image
@property (readonly, nonatomic) NSInteger pixelsWide;

/// The accepted kCVPixelFormatType for the image.
@property (readonly, nonatomic) OSType pixelFormatType;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreML.framework/Headers/MLModel.h
//
//  MLModel.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLModelDescription.h>
#import <CoreML/MLFeatureProvider.h>
#import <CoreML/MLPredictionOptions.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModel
 *
 * Construct a model and evaluate on a specific set of input features. 
 * Inputs and outputs are accessed via the MLFeatureProvider protocol.
 * Returns a model or nil if there is an error.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLModel : NSObject

/// A model holds a description of its required inputs and expected outputs.
@property (readonly, nonatomic) MLModelDescription *modelDescription;

/// Construct a model given the location of its on-disk representation. Returns nil on error.
+ (nullable instancetype)modelWithContentsOfURL:(NSURL *)url
                                          error:(NSError **)error;

/// All models can predict on a specific set of input features.
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                   error:(NSError **)error;

/// Prediction with explict options
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                 options:(MLPredictionOptions *)options
                                                   error:(NSError **)error;
@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLPredictionOptions.h
//
//  MLPredictionOptions.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLPredictionOptions
 *
 * An object to hold options / controls / parameters of how
 * model prediction is performed
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MLPredictionOptions : NSObject

// Set to YES to force computation to be on the CPU only
@property (readwrite, nonatomic) BOOL usesCPUOnly;

@end

NS_ASSUME_NONNULL_END

