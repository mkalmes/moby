// ==========  CoreML.framework/Headers/MLMultiArray.h
//
//  MLMultiArray.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

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
ML_EXPORT
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

    /// MLSequence. Ordered collection of feature values with the same type
    MLFeatureTypeSequence API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = 7,

} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));



// ==========  CoreML.framework/Headers/MLCustomLayer.h
//
//  MLCustomLayer.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLMultiArray.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MTLTexture;
@protocol MTLCommandBuffer;

/*
 * Protocol for specifying a custom layer implementation.
 */
API_AVAILABLE(macos(10.13.2), ios(11.2), watchos(4.2), tvos(11.2))
@protocol MLCustomLayer

/*
 * Initialize the custom layer implementation. The dictionary contains the contents of the
 * 'parameters' map from the model specification. This function is called once on model load.
 * We expect the implementation to return 'nil' and set an error in the event of failure
 * initializing the object.
 */
- (nullable instancetype)initWithParameterDictionary:(NSDictionary<NSString *, id> *)parameters
                                               error:(NSError **)error;

/*
 * The data encoded in the 'weights' field of the model specification will be loaded and made
 * available to the implementation here, with one entry of the array for each entry in the 'repeated'
 * weights field in the Core ML neural network specification . This is called when the model is loaded,
 * but is a separate call from the initialization. The pointer to weights should be stored, but modifying
 * or copying its contents can significantly increase an app's memory footprint. The implementation
 * should return 'YES' on success, or return 'NO' and set an error in the event of a failure.
 */
- (BOOL)setWeightData:(NSArray<NSData *> *)weights
                error:(NSError **)error;

/*
 * For the given input shapes, the implementation needs to return the output shape produced by this layer.
 * This will be called at least once at load time, and will be called any time the size of the inputs changes
 * in a call to predict. Consumes and returns 5D arrays of shapes in the usual Core ML convention - (Sequence,
 * Batch, Channel Height, Width). See the Core ML neural network protobuf specification for more details
 * about how layers use these dimensions. This will get called at load and run time. In the event of an error
 * the implementation should return 'nil' and set an error.
 */
- (nullable NSArray<NSArray<NSNumber *> *> *)outputShapesForInputShapes:(NSArray<NSArray<NSNumber *> *> *)inputShapes
                                                                  error:(NSError **)error;

/*
 * For the given inputs, populate the provide output memory. This will be called for each evaluation performed
 * on the CPU. The inputs and outputs will have the shapes of the most recent call to outputShapesForInputShapes.
 * The memory for both input and output arrays are preallocated, and should not be copied or moved. The
 * implementation should not alter the inputs. Should return 'YES' on sucess, or 'NO' and set the error on
 * failure.
 */
- (BOOL)evaluateOnCPUWithInputs:(NSArray<MLMultiArray *> *)inputs
                        outputs:(NSArray<MLMultiArray *> *)outputs
                          error:(NSError **)error;

@optional
/*
 * Optional selector for encoding a shader implementing the custom layer to a command buffer.
 * The execution of the buffer will occur inside Core ML. Providing this function does not guarantee
 * GPU evaluation for each prediction. If not provided, the execution of this layer will always be
 * on the CPU. Should return 'YES' on sucessfully encoding, or 'NO' and set an error if the encoding
 * fails.
 */
- (BOOL)encodeToCommandBuffer:(id<MTLCommandBuffer>)commandBuffer
                       inputs:(NSArray<id<MTLTexture>> *)inputs
                      outputs:(NSArray<id<MTLTexture>> *)outputs
                        error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END

// ==========  CoreML.framework/Headers/MLImageSize.h
//
//  MLImageSize.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLImageSize : NSObject

@property (readonly) NSInteger pixelsWide;

@property (readonly) NSInteger pixelsHigh;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLMultiArrayConstraint.h
//
//  MLMultiArrayConstraint.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLMultiArray.h>
#import <CoreML/MLMultiArrayShapeConstraint.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Constraint describing expected MLMultiArray properties
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLMultiArrayConstraint : NSObject

// Required or default shape of multiarray
@property (readonly, nonatomic) NSArray<NSNumber *> *shape;

// Required dataType
@property (readonly, nonatomic) MLMultiArrayDataType dataType;

// Detailed shape constraint
@property (readonly, nonatomic) MLMultiArrayShapeConstraint *shapeConstraint API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END

// ==========  CoreML.framework/Headers/MLMultiArrayShapeConstraint.h
//
//  MLMultiArrayShapeConstraint.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLMultiArrayShapeConstraintType.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLMultiArrayShapeConstraint : NSObject

@property (readonly, nonatomic) MLMultiArrayShapeConstraintType type;

// Size of each dimension i must fall within sizeRangeForDimension[i].rangeValue
@property (readonly, nonatomic) NSArray<NSValue *> * sizeRangeForDimension;

// If type == MLMultiArrayShapeConstraintTypeEnumerated then
// only shapes in this set are allowed
@property (readonly, nonatomic) NSArray<NSArray<NSNumber *> *> * enumeratedShapes;

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
#import <CoreML/MLBatchProvider.h>
#import <CoreML/MLArrayBatchProvider.h>
#import <CoreML/MLMultiArray.h>
#import <CoreML/MLSequence.h>

#import <CoreML/MLMultiArrayConstraint.h>
#import <CoreML/MLImageConstraint.h>
#import <CoreML/MLDictionaryConstraint.h>
#import <CoreML/MLSequenceConstraint.h>

#import <CoreML/MLImageSize.h>
#import <CoreML/MLImageSizeConstraint.h>
#import <CoreML/MLImageSizeConstraintType.h>

#import <CoreML/MLMultiArrayShapeConstraint.h>
#import <CoreML/MLMultiArrayShapeConstraintType.h>

#import <CoreML/MLModel.h>
#import <CoreML/MLModelDescription.h>
#import <CoreML/MLModelMetadataKeys.h>
#import <CoreML/MLPredictionOptions.h>
#import <CoreML/MLModelConfiguration.h>

#import <CoreML/MLModel+MLModelCompilation.h>

#import <CoreML/MLModelError.h>

#import <CoreML/MLCustomLayer.h>
#import <CoreML/MLCustomModel.h>

#import <CoreML/MLExport.h>
// ==========  CoreML.framework/Headers/MLImageSizeConstraint.h
//
//  MLImageSizeConstraint.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLImageSize.h>
#import <CoreML/MLImageSizeConstraintType.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLImageSizeConstraint  : NSObject

@property (readonly, nonatomic) MLImageSizeConstraintType type;

// Image size must fall within this range
@property (readonly, nonatomic) NSRange pixelsWideRange;
@property (readonly, nonatomic) NSRange pixelsHighRange;

// If type == MLImageSizeConstraintTypeEnumerated
// then the only image sizes present in this set are allowed.
@property (readonly, nonatomic) NSArray<MLImageSize *> *enumeratedImageSizes;

@end

NS_ASSUME_NONNULL_END
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
#import <CoreML/MLSequenceConstraint.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * Description of a feature
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
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

/// Constraint when type == MLFeatureTypeSequence, nil otherwise
@property (readonly, nullable, nonatomic) MLSequenceConstraint *sequenceConstraint API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

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
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLDictionaryConstraint
 *
 * Constraint describing expected NSDictionary properties
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
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

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureProvider.h>
#import <CoreML/MLFeatureValue.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A concrete convenience class conforming to MLFeatureProvider.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
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
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLMultiArray.h>
#import <CoreML/MLSequence.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <CoreML/MLExport.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 * An immutable variant holding a data value of a supported MLFeatureType
 *
 * MLFeatureValue does not support type conversion in its accessor properties. It
 * can also have a missing or undefined value of a well defined type.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
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

/// Populated value if the type is MLFeatureTypeSequence
@property (readonly, nullable, nonatomic) MLSequence *sequenceValue API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// Hold an object with the specified value
+ (instancetype)featureValueWithInt64:(int64_t)value;
+ (instancetype)featureValueWithDouble:(double)value;
+ (instancetype)featureValueWithString:(NSString *)value;
+ (instancetype)featureValueWithMultiArray:(MLMultiArray *)value;
+ (instancetype)featureValueWithPixelBuffer:(CVPixelBufferRef)value;
+ (instancetype)featureValueWithSequence:(MLSequence *)sequence API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

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
// ==========  CoreML.framework/Headers/MLImageSizeConstraintType.h
//
//  MLImageSizeConstraintType.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, MLImageSizeConstraintType) {

    MLImageSizeConstraintTypeUnspecified = 0,  // Any image size is allowed

    MLImageSizeConstraintTypeEnumerated = 2, // Limited to an enumerated set of image sizes

    MLImageSizeConstraintTypeRange = 3,      // Allow full width and height ranges

} API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// ==========  CoreML.framework/Headers/MLSequence.h
//
//  MLSequence.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureType.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * An immutable container holding an ordered collection of feature values
 * of the same type.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLSequence : NSObject

/// Type of values held
@property (readonly, nonatomic) MLFeatureType type;

/// Empty sequence of a sepcific type
+ (instancetype)emptySequenceWithType:(MLFeatureType)type;

/// String sequences, property will be empty array if type is MLFeatureTypeString
+ (instancetype)sequenceWithStringArray:(NSArray<NSString *> *)stringValues;
@property (readonly, nonatomic) NSArray<NSString *> *stringValues;

/// int64 sequence, propery will be empty array if type is MLFeatureTypeInt64
+ (instancetype)sequenceWithInt64Array:(NSArray<NSNumber *> *)int64Values;
@property (readonly, nonatomic) NSArray<NSNumber *> *int64Values;

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
FOUNDATION_EXPORT MLModelMetadataKey const MLModelDescriptionKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// A version number encoded as a string
FOUNDATION_EXPORT MLModelMetadataKey const MLModelVersionStringKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// The author of this model
FOUNDATION_EXPORT MLModelMetadataKey const MLModelAuthorKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// License information for the model
FOUNDATION_EXPORT MLModelMetadataKey const MLModelLicenseKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

/// Any additional pertinent information specified by the model creator
FOUNDATION_EXPORT MLModelMetadataKey const MLModelCreatorDefinedKey API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// ==========  CoreML.framework/Headers/MLMultiArrayShapeConstraintType.h
//
//  MLMultiArrayShapeConstraintType.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>


API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
typedef NS_ENUM(NSInteger, MLMultiArrayShapeConstraintType) {

    MLMultiArrayShapeConstraintTypeUnspecified = 1, // An unconstrained shape. Any multi array satisfies this constraint.

    MLMultiArrayShapeConstraintTypeEnumerated = 2, // Limited to an enumerated set of shapes

    MLMultiArrayShapeConstraintTypeRange = 3,      // Allow full specified range per dimension

};
// ==========  CoreML.framework/Headers/MLModelError.h
//
//  MLModelError.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const MLModelErrorDomain API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

typedef enum MLModelError : NSInteger {
    MLModelErrorGeneric = 0,
    MLModelErrorFeatureType = 1,
    MLModelErrorIO = 3,
    MLModelErrorCustomLayer API_AVAILABLE(macos(10.13.2), ios(11.2), watchos(4.2), tvos(11.2)) = 4,
    MLModelErrorCustomModel API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0)) = 5
} MLModelError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLModelConfiguration.h
//
//  MLModelConfiguration.h
//  CoreML_framework
//
//  Created by Bill March on 6/20/18.
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MLComputeUnits) {
    MLComputeUnitsCPUOnly = 0,
    MLComputeUnitsCPUAndGPU = 1

    ,
    MLComputeUnitsAll = 2

} API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/*!
 * An object to hold options for loading a model.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLModelConfiguration : NSObject <NSCopying>

@property (readwrite) MLComputeUnits computeUnits;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLBatchProvider.h
//
//  MLBatchProvider.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MLFeatureProvider;

/*!
 * Protocol for accessing a collection of feature providers
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
@protocol MLBatchProvider

/// Total number of feature providers
@property (readonly, nonatomic) NSInteger count;

/// Indexed access to collection
- (id<MLFeatureProvider>)featuresAtIndex:(NSInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLFeatureProvider.h
//
//  MLFeatureProvider.h
//  CoreML
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
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

#import <Foundation/Foundation.h>
#import <CoreML/MLFeatureDescription.h>
#import <CoreML/MLModelMetadataKeys.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A description of a model containing input and output feature descriptions, optionally outputted features
 * with special meaning and metadata.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
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
// ==========  CoreML.framework/Headers/MLSequenceConstraint.h
//
//  MLSequenceConstraint.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

@class MLFeatureDescription;

/*!
 * Constraint describing expected MLSequence properties
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLSequenceConstraint : NSObject

// Description all sequence elements / values must match
@property (readonly, nonatomic) MLFeatureDescription *valueDescription;

// Restriction on the length of the sequence
@property (readonly, nonatomic) NSRange countRange;

@end

NS_ASSUME_NONNULL_END
// ==========  CoreML.framework/Headers/MLExport.h
//
//  MLExport.h
//  CoreML_framework
//
//  Created by Steve Peters on 1/28/18.
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#ifndef MLExport_h
#define MLExport_h

#define ML_EXPORT extern __attribute__((visibility ("default")))

#endif /* MLExport_h */
// ==========  CoreML.framework/Headers/MLArrayBatchProvider.h
//
//  MLArrayBatchProvider.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <CoreML/MLBatchProvider.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * A concrete convenience class conforming to MLBatchProvider.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
ML_EXPORT
@interface MLArrayBatchProvider : NSObject<MLBatchProvider>

@property (readonly, nonatomic) NSArray<id<MLFeatureProvider>> *array;

/// Initalize with an array of feature providers
- (instancetype)initWithFeatureProviderArray:(NSArray<id<MLFeatureProvider>> *)array;

/// Initialize with a dictionary which maps feature names to an array of values [String : [Any]]
/// Error is returned if all arrays do not have equal length or if array values
/// for a specific feature name do not have the same type or not expressible as MLFeatureValue
- (nullable instancetype)initWithDictionary:(NSDictionary<NSString *, NSArray *> *)dictionary
                                      error:(NSError **)error;

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
#import <CoreML/MLImageSizeConstraint.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLImageConstraint
 *
 * Constraint on image properties.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLImageConstraint : NSObject

/// The required or default height of the image
@property (readonly, nonatomic) NSInteger pixelsHigh;

/// The required or default width of the image
@property (readonly, nonatomic) NSInteger pixelsWide;

/// The accepted kCVPixelFormatType for the image.
@property (readonly, nonatomic) OSType pixelFormatType;

/// Detailed image size constraint
@property (readonly, nonatomic) MLImageSizeConstraint *sizeConstraint API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

@end

NS_ASSUME_NONNULL_END

// ==========  CoreML.framework/Headers/MLCustomModel.h
//
//  MLCustomLayer.h
//  CoreML
//
//  Copyright © 2018 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreML/MLModelDescription.h>
#import <CoreML/MLFeatureProvider.h>
#import <CoreML/MLBatchProvider.h>
#import <CoreML/MLPredictionOptions.h>

NS_ASSUME_NONNULL_BEGIN

/*
 * Protocol for specifying a custom model implementation.
 */
API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0))
@protocol MLCustomModel

/*
 * Initialize the custom model implementation. The model description describes the input
 * and output feature types and metadata in the Model specificaiton.
 * The parameter dictionary contains the contents of the 'parameters' map from the CustomModel specification.
 * This function is called once on model load.
 * We expect the implementation to return 'nil' and set an error in the event of failure
 * initializing the object.
 */
- (nullable instancetype)initWithModelDescription:(MLModelDescription *)modelDescription
                              parameterDictionary:(NSDictionary<NSString *, id> *)parameters
                                            error:(NSError **)error;


/*
 * Required implemenationat of a single sample input prediction.
 */
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                 options:(MLPredictionOptions *)options
                                                   error:(NSError **)error;


@optional

/// Batch prediction with explict options, if not implemented the single input predictionFromFeatures:options:error will be used
- (nullable id<MLBatchProvider>)predictionsFromBatch:(id<MLBatchProvider>)inputBatch
                                             options:(MLPredictionOptions *)options
                                               error:(NSError **)error;

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
#import <CoreML/MLBatchProvider.h>
#import <CoreML/MLPredictionOptions.h>
#import <CoreML/MLModelConfiguration.h>
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLModel
 *
 * Construct a model and evaluate on a specific set of input features.
 * Inputs and outputs are accessed via the MLFeatureProvider protocol.
 * Returns a model or nil if there is an error.
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLModel : NSObject

/// A model holds a description of its required inputs and expected outputs.
@property (readonly, nonatomic) MLModelDescription *modelDescription;

/// The load-time parameters used to instantiate this MLModel object.
@property (readonly, nonatomic) MLModelConfiguration *configuration API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// Construct a model with a default MLModelConfiguration object
+ (nullable instancetype)modelWithContentsOfURL:(NSURL *)url
                                          error:(NSError **)error;

/// Construct a model given the location of its on-disk representation. Returns nil on error.
+ (nullable instancetype)modelWithContentsOfURL:(NSURL *)url
                                  configuration:(MLModelConfiguration *)configuration
                                          error:(NSError * _Nullable __autoreleasing *)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

/// All models can predict on a specific set of input features.
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                   error:(NSError **)error;

/// Prediction with explict options
- (nullable id<MLFeatureProvider>)predictionFromFeatures:(id<MLFeatureProvider>)input
                                                 options:(MLPredictionOptions *)options
                                                   error:(NSError **)error;

/// Batch prediction with explict options
- (nullable id<MLBatchProvider>)predictionsFromBatch:(id<MLBatchProvider>)inputBatch
                                             options:(MLPredictionOptions *)options
                                               error:(NSError **)error API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

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
#import <CoreML/MLExport.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * MLPredictionOptions
 *
 * An object to hold options / controls / parameters of how
 * model prediction is performed
 */
API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
ML_EXPORT
@interface MLPredictionOptions : NSObject

// Set to YES to force computation to be on the CPU only
@property (readwrite, nonatomic) BOOL usesCPUOnly;

@end

NS_ASSUME_NONNULL_END

