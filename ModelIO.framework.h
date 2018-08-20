// ==========  ModelIO.framework/Headers/MDLSubmesh.h
/*!
 @header MDLSubmesh.h
 @framework ModelIO
 @abstract Structures for describing renderable elements of a mesh
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLMaterial.h>
#import <ModelIO/MDLMeshBuffer.h>

NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLSubmeshTopology : NSObject

/*!
 @property faceTopologyBuffer
 @abstract A buffer of 8 bit unsigned integer values, where each entry corresponds
 to the number of vertices making up a face.
 
 @discussion A submesh containing two triangles, a four sided polygon, and a
 line, would contain the data 3 3 4 2.
 If geometryType is of a fixed type, such as triangles, the buffer
 is optional, and will be created on demand if read.
 
 Indices to the vertex buffer will be stored in the index buffer
 correspondingly. In the example above, the indices would be stored
 in order, three indices for the first triangle, followed by three
 for the second, followed by four for the polygon, and finally two
 indices for the line.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> faceTopology;

/*!
 @property faceCount
 @abstract The number of faces encoded in faceTopologyBuffer
 */
@property (nonatomic) NSUInteger faceCount;

/*! A crease value at a vertex to be applied during subdivision. Vertex creases
 A zero value is smooth, a one value is peaked. It is intended to be used
 with an index buffer, where the index buffer entries are vertex indices.
 The corresponding values in the corner sharpness attribute indicate the
 corner sharpness of those vertices. The index buffer is sparse. If a mesh
 has three sharp vertices, then the index buffer will have three entries.
 Since the number of entries in this vertex buffer is likely to be different
 than the number of entries in any other vertex buffer, it shouldn't be
 interleaved with other data.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> vertexCreaseIndices;
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> vertexCreases;

/*!
 @property vertexCreaseCount
 @abstract The number of vertex creases encoded in vertexCreases
 */
@property (nonatomic) NSUInteger vertexCreaseCount;

/*! A crease value at an edge to be applied during subdivision. Edge creases
 A zero value is smooth, a one value is peaked. It is intended to be used
 with an index buffer, where the index buffer entries are edge index pairs.
 Accordingly, there will be two index entries for each edge sharpness entry,
 and the sharpness entry corresponds to the edge itself.
 The corresponding values in the edge sharpness attribute indicate the
 edge sharpness of those edges.  The index buffer is sparse. If a mesh
 has three sharp edges, then the index buffer will have six entries.
 Since the number of entries in this vertex buffer is likely to be different
 than the number of entries in any other vertex buffer, it shouldn't be
 interleaved with other data.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> edgeCreaseIndices;
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> edgeCreases;

/*!
 @property edgeCreaseCount
 @abstract The number of edge creases encoded in edgeCreases
 */
@property (nonatomic) NSUInteger edgeCreaseCount;

/*! The hole attribute is a vertex attribute of single integer values where
 each integer is an index of a face that is to be used as a hole. If there
 are two holes in a mesh, then the vertex buffer will have two entries.
 Since the number of entries in this vertex buffer is likely to be different
 than the number of entries in any other vertex buffer, it shouldn't be
 interleaved with other data.
 */
@property (nonatomic, retain, nullable) id<MDLMeshBuffer> holes;

/*!
 @property holeCount
 @abstract The number of holes encoded in holes
 */
@property (nonatomic) NSUInteger holeCount;

@end

/*!
 @class MDLSubmesh
 @abstract A drawable subset of an MDLMesh, with its own material
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLSubmesh : NSObject<MDLNamed>

/*!
 @method initWithName:indexBuffer:indexCount:indexType:geometryType:material:
 @abstract Initialize submesh with all data necessary to make properties valid
 */
- (instancetype)initWithName:(NSString *)name
                 indexBuffer:(id<MDLMeshBuffer>)indexBuffer
                  indexCount:(NSUInteger)indexCount
                   indexType:(MDLIndexBitDepth)indexType
                geometryType:(MDLGeometryType)geometryType
                    material:(nullable MDLMaterial *)material;

/*!
 @method initWithIndexBuffer:indexCount:indexType:geometryType:material:
 @abstract Initialize submesh with all data necessary to make properties valid
 */
- (instancetype)initWithIndexBuffer:(id<MDLMeshBuffer>)indexBuffer
                         indexCount:(NSUInteger)indexCount
                          indexType:(MDLIndexBitDepth)indexType
                       geometryType:(MDLGeometryType)geometryType
                           material:(nullable MDLMaterial *)material;

/*!
 @method initWithIndexBuffer:indexCount:indexType:faceTopologyBuffer:geometryType:material:
 @abstract Initialize submesh with all data necessary to make properties valid
 
 @discussion The geometry type will typically be MDLGeometryTypeVariableTopology,
             if other types are used the faceTopologyBuffer contents should
             reflect that.
 */
- (instancetype)initWithName:(NSString *)name
                 indexBuffer:(id<MDLMeshBuffer>)indexBuffer
                  indexCount:(NSUInteger)indexCount
                   indexType:(MDLIndexBitDepth)indexType
                geometryType:(MDLGeometryType)geometryType
                    material:(nullable MDLMaterial *)material
                    topology:(nullable MDLSubmeshTopology *)topology;

/*!
 @method initWithMDLSubmesh:indexType:geometryType:
 @abstract Initialize submesh using another submesh as input.
 @discussion the resulting submesh will have a new index type if necessary.
  If a conversion from the source submesh's geometry type to the requested
  geometry type is possible, conversion will be performed. Otherwise nil will
  be returned.
 */
- (nullable instancetype)initWithMDLSubmesh:(nonnull MDLSubmesh*)submesh
                                  indexType:(MDLIndexBitDepth)indexType
                               geometryType:(MDLGeometryType)geometryType;

/*!
 @property indexBuffer
 @abstract Index data referencing vertex data in parent mesh
 */
@property (nonatomic, readonly, retain) id<MDLMeshBuffer> indexBuffer;

/*!
 @property indexCount
 @abstract Number of indices in the indexBuffer
 */
@property (nonatomic, readonly) NSUInteger indexCount;

/*!
 @property indexType
 @abstract Data type of indices in indexBuffer
 @discussion Support 8, 16, and 32 bit unsigned integer values
 */
@property (nonatomic, readonly) MDLIndexBitDepth indexType;

/*!
 @property geometryType
 @abstract Type of primitive that vertices referenced by the indexBuffer are 
           assembled into
 */
@property (nonatomic, readonly) MDLGeometryType geometryType;

/*!
 @property material
 @abstract Material to apply when rendering this object
 */
@property (nonatomic, retain, nullable) MDLMaterial *material;

/*!
 @property topology
 @abstract Topology data structure for use with MDLGeometryTypeVariableTopology
 
 @discussion ignored for geometry types other than MDLGeometryTypeVariableTopology.
             A submesh of type MDLGeometryTypeVariableTopology with no topology
             data is an empty submesh.
*/
@property (nonatomic, readonly, retain, nullable) MDLSubmeshTopology *topology;

/*!
 @property name
 @abstract Identifying name for this object
 */
@property (nonatomic, copy) NSString *name;

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLTransform.h
/*!
 @header MDLTransform.h
 @framework ModelIO
 @abstract Time sampled transformation of elements in 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <ModelIO/MDLObject.h>
#import <ModelIO/MDLTypes.h>
#import <Foundation/Foundation.h>
#include <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLObject;

/** MDLTransformComponent
    @summary a container for a time sampled local transformation
 
    @discussion Accessors to get the local transform and the global transform
    for a particular MDLObject are provided.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLTransformComponent <MDLComponent>
@required

/** The matrix, at minimumTime */
@property (nonatomic, assign) matrix_float4x4 matrix;

/** If no animation data is present, minimumTime and maximumTime will be zero
 */
@property (nonatomic, readonly) NSTimeInterval minimumTime;
@property (nonatomic, readonly) NSTimeInterval maximumTime;

@optional
- (void)setLocalTransform:(matrix_float4x4)transform forTime:(NSTimeInterval)time;

/**
 Resets any timing information, and makes transform valid at all times 
 */
- (void)setLocalTransform:(matrix_float4x4)transform;


/** Returns the transform governing this transformable at the specified time
    in the transformable's parent's space.
    If non-animated, all frame values will return the same result. 
 */
- (matrix_float4x4)localTransformAtTime:(NSTimeInterval)time;

/** Returns the transform governing this transformable at the specified frame in
    world space. If there is no parent, identity will be returned
 */
+ (matrix_float4x4)globalTransformWithObject:(MDLObject *)object atTime:(NSTimeInterval)time;

@end


/**
 Concrete implementation of <MDLTransformComponent>.
 For more complex transform components create a class that conforms to 
 <MDLTransformComponent>.
 
 @discussion Setting any of scale, translation, or rotation individually will 
 set the matrix property, and clear any timing information.
 
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLTransform : NSObject <MDLTransformComponent>

- (instancetype)initWithIdentity NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithTransformComponent:(id<MDLTransformComponent>)component;

/**
 Initialization with a matrix assumes the matrix is an invertible, homogeneous 
 affine transform matrix. Retrieving transform components after initialization 
 with a non-affine matrix will yield those of the identity transform.
 */
- (instancetype)initWithMatrix:(matrix_float4x4)matrix;

/**
 Set all transform components to identity
 */
- (void)setIdentity;

- (vector_float3)translationAtTime:(NSTimeInterval)time;
- (vector_float3)rotationAtTime:(NSTimeInterval)time;
- (vector_float3)shearAtTime:(NSTimeInterval)time;
- (vector_float3)scaleAtTime:(NSTimeInterval)time;
- (void)setTranslation:(vector_float3)translation forTime:(NSTimeInterval)time;
- (void)setRotation:(vector_float3)rotation forTime:(NSTimeInterval)time;
- (void)setShear:(vector_float3)shear forTime:(NSTimeInterval)time;
- (void)setScale:(vector_float3)scale forTime:(NSTimeInterval)time;

/**
 Construct a right handed rotation matrix at the specified time
 */
- (matrix_float4x4)rotationMatrixAtTime:(NSTimeInterval)time;

/**
 If these properties are read and animation data exists the earliest value is returned.
 Otherwise, if there is no animation data, the value of the property is the same at all times and that value is returned.
 If written, timing information for said property is removed. To retain or add timing information, use the set:forTime selectors instead.
 */
@property (nonatomic, readwrite) vector_float3 translation;
@property (nonatomic, readwrite) vector_float3 rotation;     // Euler XYZ radians
@property (nonatomic, readwrite) vector_float3 shear;
@property (nonatomic, readwrite) vector_float3 scale;

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLMeshBuffer.h
/*!
 @header MDLMeshBuffer.h
 @framework ModelIO
 @abstract Protocols for creating and backing mesh vertex and index buffers
 @discussion Apps can use these protocols to back buffers with custom memory 
             types such as GPU or File based memory
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @enum MDLMeshBufferType
 @abstract Type of data a MDLMeshBuffer has been allocated for
 */
typedef NS_ENUM(NSUInteger, MDLMeshBufferType) {
    MDLMeshBufferTypeVertex = 1,
    MDLMeshBufferTypeIndex = 2,
};

@protocol MDLMeshBuffer;
@protocol MDLMeshBufferAllocator;
@protocol MDLMeshBufferZone;

/*!
 @class MDLMeshBufferMap
 @abstract Represents a reference to memory of a mapped MeshBuffer
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMeshBufferMap : NSObject

/*!
 @method initWithBytes:deallocator:
 @abstract Called by implementor of MDLMeshBuffer protocol to create the map
           and arrange for unmapping on deallocation.
 */
-(instancetype) initWithBytes:(void*)bytes
                  deallocator:(nullable void (^)())deallocator;

/*!
 @property bytes
 @abstract Mutable pointer to data in a MDLMeshBuffer object.
 */
@property (nonatomic, readonly) void *bytes;

@end

/*!
 @protocol MDLMeshBuffer
 @abstract Used by ModelIO to represent a buffer to be filled with vertex and 
           index data
 @discussion Supports deep copy of data by conforming to the NSCopying protocol
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MDLMeshBuffer <NSObject, NSCopying>

/*!
 @method fillData:offset:
 @abstract Fills buffer with data at offset
 @param data Data to fill buffer with
 @param offset Byte offset in buffer to begin filling data
 @discussion Fills data.length bytes of data.  Will not write beyond length of 
             this buffer.
 */
- (void)fillData:(NSData *)data offset:(NSUInteger)offset;

/*!
 @method map
 @abstract CPU access to buffer's memory
 @return An MDLMeshBufferMap object to read or modify a buffer's memory
 @discussion The buffer will remain mapped as long as the returned MDLMeshBufferMap
             object exists. Mapping a buffer may impose restrictions on a system.
             For instance,  if the implementing class maps an OpenGL buffer, that
             buffer may be  unavailable for rendering while mapped, and cause a
             draw failure.  Precautions must be taken in such cases.
 */
- (MDLMeshBufferMap *)map;

/*!
 @property length
 @abstract Size in bytes of the buffer allocation
 */
@property (nonatomic, readonly) NSUInteger length;

/*!
 @property allocator
 @abstract Allocator object used to create this buffer.
 @discussion This allcoator used for copy and relayout operations (such as when 
             a new vertex descriptor is applied to a vertex buffer)
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> allocator;

/*!
 @property zone
 @abstract Zone from which this buffer was created
 @discussion This zone will be used for copy and relayout operations (such as 
             when a new vertex descriptor is applied to a vertex buffer).  If
             the default zone is used this will be nil.
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferZone> zone;

/*!
 @property type
 @abstract the intended type of the buffer
 */
@property (nonatomic, readonly) MDLMeshBufferType type;

@end


/*!
 @class MDLMeshBufferData
 @abstract A CPU memory backed mesh buffer
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMeshBufferData : NSObject <MDLMeshBuffer>

/*! 
 @method initWithType:length
 @abstract instantiate a new data backed mesh buffer
 @param type the intended use of the buffer
 @param length the size of buffer to allocate, in bytes
 */
- (instancetype)initWithType:(MDLMeshBufferType)type length:(NSUInteger)length;

/*!
 @method initWithType:data
 @abstract instantiate a new data backed mesh buffer
 @param type the intended use of the buffer
 @param data the data to be used as a mesh buffer. It will be copied.
 */
- (instancetype)initWithType:(MDLMeshBufferType)type data:(nullable NSData*)data;

@property (nonatomic, readonly, retain) NSData *data;

@end




/*!
 @protocol MDLMeshBufferZone
 @abstract A reference to a logical pool of memory from which mesh buffers would 
           be allocated
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MDLMeshBufferZone <NSObject>

/*!
 @property capacity
 @abstract Total size of memory in the zone
 */
@property (nonatomic, readonly) NSUInteger capacity;

/*!
 @property allocator
 @abstract Allocator used to create the zone
 */
@property (nonatomic, readonly) id<MDLMeshBufferAllocator> allocator;

@end



/*!
 @protocol MDLMeshBufferAllocator
 @abstract Object for allocating buffers to back vertex and index data
 @discussion Accepted by MDLAsset init method.  Implementor creates objects 
             implementing MDLMeshBuffer with memory to be filled with vertex and 
             index data during 3d file loading and parsing.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MDLMeshBufferAllocator <NSObject>

/*!
 @method newZone:
 @abstract Create a zone which can be used to allocate MDLMeshBuffer objects
 @param capacity Total size in bytes of all buffers which can be created from 
        this zone
 */
-(id<MDLMeshBufferZone>)newZone:(NSUInteger)capacity;

/*!
 @method newZoneForBuffersWithSize:andType:
 @abstract Create a zone which can be used to allocate MDLMeshBuffer objects
 @param sizes Sizes of each buffer to be created in this zone
 @param types Type of each buffer to be created in this zone. Values to be of
              MDLMeshBufferType
 @discussion Will create a zone from which MDLMeshBuffer objects can be 
             allocated.  This will allocate a zone with enough capacity
             for each of the buffers with sizes and types specified even taking
             into any alignment restrictions necessary to use these buffers.
 */
-(id<MDLMeshBufferZone>)newZoneForBuffersWithSize:(NSArray<NSNumber*>*)sizes
                                          andType:(NSArray<NSNumber*>*)types;

/*!
 @method newBuffer:type:
 @abstract Create a buffer in a default zone
 @param length Size of buffer to be created in bytes
 @param type Type of data to be stored in this buffer
 */
-(id<MDLMeshBuffer>)newBuffer:(NSUInteger)length
                        type:(MDLMeshBufferType)type;
/*!
 @method newBufferWithData:type:
 @abstract Create a buffer in a default zone and fill with data in the supplied 
           NSData object
 @param data Memory to fill the buffer with
 @param type Type of data to be stored in this buffer
 */
-(id<MDLMeshBuffer>)newBufferWithData:(NSData *)data
                                type:(MDLMeshBufferType)type;

/*!
 @method newBufferFromZone:length:type:
 @abstract Create a buffer from a given zone with the given length
 @return An object conforming to the MDLMeshBuffer protocol.  Returns nil the 
         buffer could not be allocated in the zone given.
 @param zone Zone from which to allocate the memory
 @param data Values with which to fill the buffer
 @param type Type of data to be stored in this buffer
 @discussion An implementing MDLMeshBufferAllocator object may increase the size 
             of the zone if the buffer could not be allocated with the current 
             zone size.  Alternatively the implementation may return nil if the 
             buffer could not be allocated.

 */
-(nullable id<MDLMeshBuffer>)newBufferFromZone:(nullable id<MDLMeshBufferZone>)zone
                                       length:(NSUInteger)length
                                         type:(MDLMeshBufferType)type;

/*!
 @method newBufferFromZone:data:type:
 @abstract Create a buffer from a given zone and fill with data in the supplied 
           NSData object
 @return An object conforming to the MDLMeshBuffer protocol.  Returns nil the 
         buffer could not be allocated in the given zone
 @param zone Zone from which to allocate the memory
 @param data Values with which to fill the buffer
 @param type Type of data to be stored in this buffer
 @discussion An implementing MDLMeshBufferAllocator object may increase the size 
             of the zone if the buffer could not be allocated with the current 
             zone size. Alternatively the implementation may return nil if the 
             buffer could not be allocated.
 */
-(nullable id<MDLMeshBuffer>)newBufferFromZone:(nullable id<MDLMeshBufferZone>)zone
                                         data:(NSData *)data
                                         type:(MDLMeshBufferType)type;

@end



/*!
 An allocator to use when backing with an NSData is appropriate.
 */
MDL_EXPORT
@interface MDLMeshBufferDataAllocator: NSObject <MDLMeshBufferAllocator>

@end

/*!
 A default zone that can be use for convenience 
 */
@interface MDLMeshBufferZoneDefault : NSObject <MDLMeshBufferZone>

@property (nonatomic, readonly) NSUInteger capacity;
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> allocator;

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLMesh.h
/*!
 @header MDLMesh.h
 @framework ModelIO
 @abstract Structures for describing meshes for rendering
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLLight.h>
#import <ModelIO/MDLTransform.h>
#import <ModelIO/MDLSubmesh.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <ModelIO/MDLVertexDescriptor.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class MDLVertexAttributeData
 @abstract convenience object to quickly access vertex attribute data
 @discussion created by MDLMesh's vertexAttributeData selector
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVertexAttributeData : NSObject

@property (nonatomic, retain) MDLMeshBufferMap *map;
@property (nonatomic) void *dataStart;
@property (nonatomic) NSUInteger stride;
@property (nonatomic) MDLVertexFormat format;

@end


/*!
 @class MDLMesh
 @abstract A vertex buffer with info to interpret vertex data
 @discussion Includes a collection of submeshs which have indexbuffer and
             material information
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMesh : MDLObject

/*!
 @method initWithVertexBuffer:vertexCount:descriptor:submeshes:
 @abstract Initialize object with a vertex buffer and a collection of submeshes
 @return Initialized mesh or nil if descriptor's layout array does not describe 
         a single buffer
 @param vertexBuffer MDLMeshBuffer object containing all vertex data for the mesh
 @param vertexCount Number of vertices in the vertexBuffer
 @param descriptor VertexDescriptor specifying how to interpret vertex data
 @param submeshes Array of submeshes with index buffers referencing vertex data 
        and/or materials to be applied to mesh
 */
- (instancetype)initWithVertexBuffer:(id<MDLMeshBuffer>)vertexBuffer
                         vertexCount:(NSUInteger)vertexCount
                          descriptor:(MDLVertexDescriptor *)descriptor
                           submeshes:(NSArray<MDLSubmesh*> *)submeshes;

/*!
 @method initWithVertexBuffer:vertexCount:descriptor:submeshes:
 @abstract Initialize object with an array of vertex buffers (Structure of 
           Arrays) and a collection of submeshes
 @return Initialized mesh or nil if descriptor's layout array is incompatible 
         with vertexBuffers array
 @param vertexCount Number of vertices in vertexBuffers
 @param vertexBuffer An array of MDLMeshBuffer objects containing vertex data 
         for the mesh
 @param descriptor VertexDescriptor specifying how to interpret vertex data
 @param submeshes Array of submeshes with index buffers referencing vertex data 
        and/or materials to be applied to mesh
 @discussion Allows initialization with the layout of the vertexBuffers in a 
        structure-of-arrays form, in other words, non-interleaved vertex attributes
 */
- (instancetype)initWithVertexBuffers:(NSArray<id<MDLMeshBuffer>> *)vertexBuffers
                          vertexCount:(NSUInteger)vertexCount
                           descriptor:(MDLVertexDescriptor *)descriptor
                            submeshes:(NSArray<MDLSubmesh*> *)submeshes;


/*!
 @method vertexAttributeDataForAttributeNamed:
 @abstract convenience selector to get quick access to vertex attribute data
 @discussion the vertex buffer will remain mapped until the MDLVertexAttributeData
             is freed.
 */
- (nullable MDLVertexAttributeData*)vertexAttributeDataForAttributeNamed:(NSString*)name;

/*!
 @property boundingBox
 @abstract Bounding box encompasing the mesh
 @discussion Calculated by iterating through MDLVertexAttributePosition to find
             min and max bounds. If no attribute is named MDLVertexAttributePosition
             this will be a invalid bounds where maxBounds is less than minBounds.
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox boundingBox;

/*!
 @property vertexDescriptor
 @abstract Immutable vertex descriptor for interpreting data in vertexBuffers
 @discussion Setting this applies the new layout in 'vertexBuffers' thus is a 
             heavyweight operation as structured copies of almost all vertex 
             buffer data could be made.  Additionally, if the new vertexDescriptor 
             does not have an attribute in the original vertexDescriptor, that 
             attribute will be deleted.  If the original vertexDescriptor does 
             not have an attribute in the new vertexDescriptor, the data for the 
             added attribute set as the added attribute's initializationValue 
             property.
 
             The allocator associated with each original meshbuffer is used to
             reallocate the corresponding resultant meshbuffer.
 */
@property (nonatomic, readwrite, copy) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property vertexCount
 @abstract Number of vertices in the vertexBuffers
 @discussion The size of vertex data in each buffer can be compute by multiplying 
             this value with the stride of the buffer in the vertexDescriptor's 
             layout
 */
@property (nonatomic, readonly) NSUInteger vertexCount;

/*!
 @property vertexBuffers
 @abstract Array of buffers containing vertex data
 @discussion The vertex buffers in this array are indexed by the vertex descriptor.
 */
@property (nonatomic, readonly, retain) NSArray<id<MDLMeshBuffer>> *vertexBuffers;

/*!
 @property submeshes
 @abstract Array of submeshes containing an indexbuffer referencing the vertex 
           data and material to be applied when the mesh is rendered
 */
@property (nonatomic, readonly, retain) NSMutableArray<MDLSubmesh*> *submeshes;

@end


@interface MDLMesh (Modifiers)

/*!
 @method addAttributeWithName:format
 @abstract Convenience method to add an attribute
 @discussion The mesh's allocator will be used to create storage for the new
             attribute.
 */
- (void)addAttributeWithName:(NSString*)name
                      format:(MDLVertexFormat)format;

/*!
 @method addNormalsWithAttributeNamed:bufferIndex:
 @abstract Calculate and add vertex normal data
 @param attributeName Name of vertex normal attribute.  If nil, vertex normals 
        will be added with the MDLVertexAttributeNormal name string
 @param creaseThreshold Threshold of the dot product between the 2 triangles after which 
                        their face normal will be smoothed out. Therefore, a threshold of 0 will
                        smooth everything and a threshold of 1 won't smooth anything.
 @discussion Uses the attribute named MDLVertexAttributePosition to calculate
             vertex normals. If the mesh does not have an attribute with 
             'attributeName', it will be added, otherwise the attribute name will 
             be overwritten with vertex normal data. 'vertexDescriptor' will be 
             updated to reflect the new attribute.
 */
- (void)addNormalsWithAttributeNamed:(nullable NSString *)attributeName
                     creaseThreshold:(float)creaseThreshold;


/*!
 @method addTangentBasisForTextureCoordinateAttributeNamed:tangentAttributeNamed:bitangentAttributeNamed
 @abstract Create tangent basis data
 @param textureCoordinateAttributeName texture coordinates to use in calculations
 @param tangentAttributeName Name of vertex tangent attribute.
 @param bitangentAttributeNamed Name of vertex bitangent attribute.
 @discussion Uses the attribute named MDLVertexAttributePosition and
             textureCoordinateAttributeName to calculate tangent and bitangent
             attributes. The mesh's vertexDescriptor will be updated to reflect 
             the new attributes if necessary.
 */
- (void)addTangentBasisForTextureCoordinateAttributeNamed:(NSString*)textureCoordinateAttributeName
                                    tangentAttributeNamed:(NSString *)tangentAttributeName
                                  bitangentAttributeNamed:(nullable NSString *)bitangentAttributeName;

/*!
 @method addTangentBasisForTextureCoordinateAttributeNamed:normalAttributeNamed:tangentAttributeNamed
 @abstract Create tangent basis data
 @param textureCoordinateAttributeName texture coordinates to use in calculations
 @param normalAttributeNamed normals to use in calculations
 @param tangentAttributeName Name of a four component vertex tangent attribute.
 @discussion Uses the attribute named MDLVertexAttributePosition and
             textureCoordinateAttributeName and the specified normals to calculate 
             tangent information. The mesh's vertexDescriptor will be updated to 
             reflect the new attribute if necessary.
             Note that the bitangent can be calculated from the normal and 
             tangent by B = (N x T) * T.w
 */
- (void)addTangentBasisForTextureCoordinateAttributeNamed:(NSString*)textureCoordinateAttributeName
                                     normalAttributeNamed:(NSString*)normalAttributeName
                                    tangentAttributeNamed:(NSString *)tangentAttributeName;

/*!
 @method makeVerticesUnique:
 @abstract Deindexes the vertex array
 @discussion If any vertices are shared on multiple faces, duplicate those 
             vertices so faces do not share vertices. The vertex buffer and index 
             buffers on submeshes may grow to accomadate any vertices added.
 */
- (void)makeVerticesUnique;


@end



@interface MDLMesh (Generators)

/*!
 @method newBoxWithDimensions:segments:inwardNormals:geometryType:allocator:
 @abstract Factory method for generating a mesh with a cube shape
 @return MDLMesh box with desired attributes
 @param dimensions Width, height, and depth of the box
 @param segments Number of slices in each dimension
 @param inwardNormals Generated Normal point inward
 @param geometryType Can be MDLGeometryTypeLines, MDLGeometryTypeQuads, or MDLGeometryTypeTriangles
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle or quad primitives.  Specifying inward 
             normals is useful for generating a skybox. The center of the box 
             is at(0, 0, 0).
             Will raise an exception if an unsupported geometry type is passed in.
 */
+ (instancetype)newBoxWithDimensions:(vector_float3)dimensions
                            segments:(vector_uint3)segments
                        geometryType:(MDLGeometryType)geometryType
                       inwardNormals:(BOOL)inwardNormals
                           allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method newEllipsoidWithRadii:radialSegments:verticalSegments:inwardNormals:hemisphere:allocator:
 @abstract Factory method for generating a mesh with an ellipsoid shape
 @return MDLMesh epllipsoid with desired attributes
 @param radii Width, height, and depth of ellipsoid.
 @param radialSegments Number of pie slices :)
 @param verticalSegments Number of slices in the vertical direction
 @param geometryType Must be MDLGeometryTypeTriangles
 @param inwardNormals If true, generated normals will face inwards. Useful for 
        generating a skydome.
 @param geometryType Must be  Must be MDLGeometryTypeTriangles
 @param hemisphere If true, only top half of elipsoid will be generated. The 
        actual nubmer of vertical slices will be half of 'vertical' segments
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Specifying inward normals and hemisphere is useful for generating a skydome.
             Specifying equal X, Y, and Z radii will generate a sphere.
             Specifying a y radius of 0.0 will generate a disc.
             Will raise an exception if radialSegments is < 3, verticalSegments is < 2,
             or an unsupported geometry type is passed in.
 */
+ (instancetype)newEllipsoidWithRadii:(vector_float3)radii
                       radialSegments:(NSUInteger)radialSegments
                     verticalSegments:(NSUInteger)verticalSegments
                         geometryType:(MDLGeometryType)geometryType
                        inwardNormals:(BOOL)inwardNormals
                           hemisphere:(BOOL)hemisphere
                            allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method newCylinderWithHeight:
 @abstract Factory method for generating a mesh with a cylindrical shape
 @return MDLMesh cylinder with desired attributes
 @param height Height of cylindoid.
 @param radii Radii of cylinder in X and Z directions.
 @param radialSegments Number of pie slices :)
 @param verticalSegments Number of slices along Y axis
 @param geometryType Must be MDLGeometryTypeTriangles
 @param inwardNormals Normals point toward center of cylinder
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Center of cylinder at (0, 0, 0) with a top at +Y and bottom at -Y.
             Specifying equal X and Z radia will generate a true cylinder.
             Specifying a height of 0.0 and verticalSegments of 0 will generate
             a disc.
             Will raise and exceiption radialSegments is < 3 or an unsupported
             geometry type is passed in.
             Generated texture coordinates are laid out as follows:
                                                      ___
                                                     /   \   <- T texcoord = 0.0
                 Texture for top of cylinder   ---> [     ]
                                                     \___/
                                                    [     ]  <- T texcoord = 0.3333
                                                    [     ]
                 Texture for sides of cylinder ---> [     ]
                                                    [_____]  <- T texcoord = 0.6666
                                                     /   \
                 Texture for base of cylinder  ---> [     ]
                                                     \___/   <- T texcoord = 1.0
 */
+ (instancetype)newCylinderWithHeight:(float)height
                                radii:(vector_float2)radii
                       radialSegments:(NSUInteger)radialSegments
                     verticalSegments:(NSUInteger)verticalSegments
                         geometryType:(MDLGeometryType)geometryType
                        inwardNormals:(BOOL)inwardNormals
                            allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method newEllipticalConeWithHeight:radii:radialSegments:verticalSegments:inwardNormals:allocator:
 @abstract Factory method for generating a mesh with an elipticalCone shape.
 @return MDLMesh cone with desired attributes
 @param height Height of elipticalCone from point to base.
 @param radii Radii of base in X and Z directions.  Values of vector should be 
        equal to create a true cone.
 @param radialSegments Number of pie slices :)
 @param verticalSegments Number of slices along Y axis
 @param geometryType Must be MDLGeometryTypeTriangles
 @param inwardNormals Normals point toward center of elipticalCone
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Point of cone at (0, 0, 0) while base of cone is -Y. 
             Will raise an exception if radialSegments is < 3, verticalSegments is < 1,
             or an unsupported geometry type is passed in.
             Generated texture coordinates are laid out as follows:
                                                 _____
                                                [     ]  <- T texcoord = 0.0
                                                [     ]
                 Texture for sides of cone ---> [     ]
                                                [     ]
                                                [_____]  <- T texcoord = 0.6666
                                                 /   \
                 Texture for base of cone  ---> [     ]
                                                 \___/   <- T texcoord = 1.0
 */
+ (instancetype)newEllipticalConeWithHeight:(float)height
                                      radii:(vector_float2)radii
                             radialSegments:(NSUInteger)radialSegments
                           verticalSegments:(NSUInteger)verticalSegments
                               geometryType:(MDLGeometryType)geometryType
                              inwardNormals:(BOOL)inwardNormals
                                  allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method newPlaneWithDimensions:segments:geometryType:allocator:
 @abstract Factory method for generating a mesh with an planar shape
 @return MDLMesh plane with desired attributes
 @param dimensions Dimensions of  of elipticalCone in X and Z directions.
 @param segments Number of segements in the X and Y dimensions
 @param geometryType Can be MDLGeometryTypeLines, MDLGeometryTypeQuads, or MDLGeometryTypeTriangles
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion Assembled with triangle or quad primitives. Creates a plane along 
             the X/Z axis. Center of plane at (0, 0, 0). All normals point up,
             towards positive Y
             Will raise an exception if an unsupported geometry type is passed in.
 */
+ (instancetype)newPlaneWithDimensions:(vector_float2)dimensions
                              segments:(vector_uint2)segments
                          geometryType:(MDLGeometryType)geometryType
                             allocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/*!
 @method newIcosahedronWithRadius:inwardNormals:allocator:
 @abstract Factory method for generating a mesh icosahedron
 @return MDLMesh icosahedron with desired attributes
 @param radius Distance from the center to the outermost point of the mesh
 @param inwardNormals Generated normals will face towards the center of the mesh
 @param allocator A mesh buffer allocator used to allocate memory to back buffers 
        for the returned mesh.  If nil, a default allocator will be used
 @discussion  Creates an icosahedron with center at (0, 0, 0).
 */
+ (instancetype)newIcosahedronWithRadius:(float)radius
                           inwardNormals:(BOOL)inwardNormals
                               allocator:(nullable id<MDLMeshBufferAllocator>)allocator;


/*!
 @method newSubdividedMesh:subdivisionLevels:allocator:
 @abstract Factory method that generates a subdivided mesh from a source mesh
 @param mesh Mesh from which to generate a subdivided mesh
 @param submeshIndex Index of submesh in Mesh's submesh array from which to
        generate a subdivided mesh
 @param subdivisionLevels The number of levels to subdivide mesh
 @discussion Subdivision levels over four are likely to generate more triangles 
             than can be reasonably displayed. Index and vertex data will use 
             the same allocator used for the source mesh. Loading an asset 
             using the topology preservation flag set to YES will result in the
             best subdivision results.
 @return Returns a mesh subdividied to index level, unless subdivision is 
         impossible.  Only triangle and quadrilateral meshes can be subdivided.
 */
+ (nullable instancetype)newSubdividedMesh:(MDLMesh*)mesh
                              submeshIndex:(NSUInteger)submeshIndex
                         subdivisionLevels:(NSUInteger)subdivisionLevels;

@end



@interface MDLMesh (MDLLightBaking)

/*!
 @method generateAmbientOcclusionTextureWithSize:
 @abstract Creates an Ambient Occlusion texture, returns true upon success, false 
           upon failure
 @param size  Texture Size in which to bake the ambient occlusion
 @param raysPerSample Number of rays to be sent out of every texture texel against
        the object for potential occlusion.
 @param attenuationFactor Float between 0 to 1 that defines how to attenuate the 
        AO value. 0 doesn't change it, and at 1, all AO values are white except 
        if they are originally completely black. Quadratic attenuation in between.
 @param objectsToConsider NSArray of MDLMeshes containing the objects to raytrace against
 @param vertexAttributeName NSString of the MDLVertexAttribute where the vertex 
        texture UVs will be stored. Creates it if it doesn't exist, otherwise 
        overwrites current values.
 @param materialPropertyName NSString of the MDLMaterialProperty that will store 
        the texture in the Mesh.
 @result Success or failure of the baking process.
 */
- (BOOL)generateAmbientOcclusionTextureWithSize:(vector_int2)textureSize
                                  raysPerSample:(NSInteger)raysPerSample
                              attenuationFactor:(float)attenuationFactor
                              objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                           vertexAttributeNamed:(NSString *)vertexAttributeName
                          materialPropertyNamed:(NSString *)materialPropertyName;

/*!
 @method generateAmbientOcclusionTextureWithQuality:
 @abstract Creates an Ambient Occlusion texture, returns true upon success, false
           upon failure
 @param quality Float between 0 and 1 that defines quality of the bake process.
        0 is of lower quality but bakes faster and uses less memory, where 1 is 
        of higher quality.
 @param attenuationFactor Float between 0 to 1 that defines how to attenuate the 
        AO value. 0 doesn't change it, and at 1, all AO values are white except 
        if they are originally completely black. Quadratic attenuation in between.
 @param objectsToConsider NSArray of MDLMeshes containing the objects to raytrace 
        against
 @param vertexAttributeName NSString of the MDLVertexAttribute where the vertex 
        texture UVs will be stored. Creates it if it doesn't exist, otherwise 
        overwrites current values.
 @param materialPropertyName NSString of the MDLMaterialProperty that will store 
        the texture in the Mesh.
 @result Success or failure of the baking process.
  */
- (BOOL)generateAmbientOcclusionTextureWithQuality:(float)bakeQuality
                                 attenuationFactor:(float)attenuationFactor
                                 objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                              vertexAttributeNamed:(NSString *)vertexAttributeName
                             materialPropertyNamed:(NSString *)materialPropertyName;

- (BOOL)generateAmbientOcclusionVertexColorsWithRaysPerSample:(NSInteger)raysPerSample
                                            attenuationFactor:(float)attenuationFactor
                                            objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                         vertexAttributeNamed:(NSString *)vertexAttributeName;

- (BOOL)generateAmbientOcclusionVertexColorsWithQuality:(float)bakeQuality
                                      attenuationFactor:(float)attenuationFactor
                                      objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                   vertexAttributeNamed:(NSString *)vertexAttributeName;

- (BOOL)generateLightMapTextureWithTextureSize:(vector_int2)textureSize
                              lightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                             objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                          vertexAttributeNamed:(NSString *)vertexAttributeName
                         materialPropertyNamed:(NSString *)materialPropertyName;

- (BOOL)generateLightMapTextureWithQuality:(float)bakeQuality
                          lightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                         objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                      vertexAttributeNamed:(NSString *)vertexAttributeName
                     materialPropertyNamed:(NSString *)materialPropertyName;

- (BOOL)generateLightMapVertexColorsWithLightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                                       objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                    vertexAttributeNamed:(NSString *)vertexAttributeName;

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLAsset.h
/*!
 @header MDLAsset.h
 @framework ModelIO
 @abstract Structures for representing contents of 3d model files
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLObject.h>
#import <ModelIO/MDLVertexDescriptor.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <Foundation/NSURL.h>
#import <simd/simd.h>

/*!
 @class MDLAsset
 
 @abstract An MDLAsset represents the contents of a model file.
 
@discussion

 Each asset contains a collection of hierarchies of objects, where each object 
 in the asset is the top level of a hierarchy. Objects include transforms, 
 lights, cameras, and meshes.
 
 MDLAssets are typically instantiated from NSURLs that refer to a model resource.

 The model resource may represented timed information, for example, a series of 
 mesh morphs. If the asset is timed, then the framerate will be non-zero, and the 
 firstFrame and lastFrame properties will indicate the range for which sample 
 data exists. Samples before or after that range will be clamped. Some model 
 resource representations allow continuous sampling, others are discrete. In the 
 discrete case, if a requested sample time is not on a discrete boundary the 
 returned sample will be the sample exactly on the sample time, or if no such is 
 available, the immediately preceding sample. If no time is specified for a 
 sample, the first data will be returned.
 
 An asset's bounding box can be queried without traversing the hierarchy of 
 objects.
 
 Fast enumeration of an MDLAsset iterates the top level objects contained within.
 */


NS_ASSUME_NONNULL_BEGIN

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLAsset : NSObject <NSCopying, NSFastEnumeration>

/*!
 @method initWithURL:
 @abstract Initialize an MDLAsset using the contents of the resource located at 
           the indicated URL
 @discussion Vertex layout (i.e. vertexDescriptor) will be specified by ModelIO 
             depending on attributes of the resource.  Buffers will be allocated 
             using a default NSData based allocator

             Submeshes will be converted to triangle topology.
 */
- (instancetype)initWithURL:(NSURL *)URL;

/*!
 @method initWithURL:vertexDescriptor:bufferAllocator:
 @abstract Initialize an MDLAsset using the contents of the resource located at 
           URL, ensuring that the asset conforms to the supplied vertexDescriptor, 
           and buffers are allocated in the supplied allocator
 
 @discussion The default behavior is to triangulate any discovered meshes and to
             conform the mesh to the supplied vertexDescriptor.
 
             If nil is passed as the vertexDescriptor, then a vertexDescriptor
             will be created according to the attributes of the resource.
 
             If nil is passed as the bufferAllocator, buffers will be allocated
             using a default NSData based allocator.
 
             Submeshes will be converted to triangle topology.
  */
- (instancetype)initWithURL:(NSURL *)URL
           vertexDescriptor:(nullable MDLVertexDescriptor*)vertexDescriptor
            bufferAllocator:(nullable id<MDLMeshBufferAllocator>)bufferAllocator;

/*! 
 @method initWithURL:vertexDescriptor:bufferAllocator:preserveTopology
 @abstract Same as initWithURL:vertexDescriptor:bufferAllocator: except that
           if preserveTopology is YES, a topology buffer might be created on the
           submeshes.
 
 @discussion If all faces in a submesh have the same vertex count, then the 
             submesh will a geometry type corresponding to that vertex count.
             For example, if all faces have four vertices, then the geometry
             type will be MDLGeometryTypeQuads. If faces have a varying number
             of vertices, then the the submesh type will be 
             MDLGeometryTypeVariableTopology, and a faceTopologyBuffer will be
             created.
 */

- (instancetype)initWithURL:(NSURL *)URL
           vertexDescriptor:(nullable MDLVertexDescriptor*)vertexDescriptor
            bufferAllocator:(nullable id<MDLMeshBufferAllocator>)bufferAllocator
           preserveTopology:(BOOL)preserveTopology
                      error:(NSError * __nullable * __nullable)error;


/*!
 @method exportAssetToURL:
 @abstract Export an asset to the specified URL.
 @return YES is returned if exporting proceeded successfully,
 */
- (BOOL)exportAssetToURL:(NSURL *)URL;
- (BOOL)exportAssetToURL:(NSURL *)URL error:(NSError * __nullable * __nullable)error;

/*!
 @method canImportFileExtension:
 @abstract Indicates whether MDLAsset object can be initialized with resource
           with the given extension
 @return YES is returned if MDLAsset is able to load and represent assets with 
           the given extension
 */
+ (BOOL)canImportFileExtension:(NSString *)extension;

/*!
 @method canImportFileExtension:
 @abstract Indicates whether MDLAsset object can export asset to resource with
           the given extension
 @return YES is returned if MDLAsset is able is able to export assets to 
         resources with the given extension
 */
+ (BOOL)canExportFileExtension:(NSString *)extension;

/*!
 @method boundingBoxAtTime:
 @abstract The bounds of the MDLAsset at the specified time
 */
- (MDLAxisAlignedBoundingBox)boundingBoxAtTime:(NSTimeInterval)time;

/*!
 @property bounds
 @abstract The bounds of the MDLAsset at the earliest time sample
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox boundingBox;

/*!
 @property frameInterval
 @abstract Inherent frame rate of an asset
 @discussion If no framerate was specified by resource or resource uncapable of 
             specifying framerate, this value defaults to 0
 */
@property (nonatomic, readwrite) NSTimeInterval frameInterval;

/*!
 @property startTime
 @abstract Start time bracket of animation data
 @discussion If no animation data was specified by resource or resource incapable 
             of specifying animation data, this value defaults to 0
 */
@property (nonatomic, readwrite) NSTimeInterval startTime;

/*!
 @property endTime
 @abstract End time bracket of animation data
 @discussion If no animation data was specified by resource or resource incapable
             of specifying animation data, this value defaults to 0
 */
@property (nonatomic, readwrite) NSTimeInterval endTime;

/*!
 @property URL
 @abstract  URL used to create the asset
 @discussion If no animation data was specified by resource or resource incapable 
             of specifying animation data, this value defaults to 0
 */
@property (nonatomic, readonly, retain, nullable) NSURL *URL;

/*!
 @property bufferAllocator
 @abstract  Allocator used to create vertex and index buffers
 */
@property (nonatomic, readonly, retain) id<MDLMeshBufferAllocator> bufferAllocator;

/*!
 @property vertexDescriptor
 @abstract  Vertex descriptor set upon asset initialization
 @discussion Will be nil if there was no descriptor set
 */
@property (nonatomic, readonly, retain, nullable) MDLVertexDescriptor *vertexDescriptor;

/*!
 @method addObject:
 @abstract Add a top level object to an asset.
 @discussion If the object was already in the asset, this has no effect.
 */
- (void)addObject:(MDLObject *)object;

/*!
 @method removeObject:
 @abstract Remove a top level object from an asset.
 @discussion If the object not in the asset, this has no effect.
 */
- (void)removeObject:(MDLObject *)object;

/*!
 The number of top level objects
 */
@property (nonatomic, readonly) NSUInteger count;

/*!
 @method objectAtIndexedSubscript:
 @abstract return the indexed top level object
 */
- (nullable MDLObject *)objectAtIndexedSubscript:(NSUInteger)index;

/*!
 @method objectAtIndex:
 @abstract return the indexed top level object
 */
- (MDLObject *)objectAtIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLObject.h
/*!
 @header MDLObject.h
 @framework ModelIO
 @abstract Base structures for representing components of 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLTransform.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MDLTransformComponent;

/*!
 @class MDLObject
 @abstract Base class for object in a ModelIO asset hierarchy
 @discussion Includes transformation and bounds info, links to parent and
             children in the hierachy
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLObject : NSObject<MDLNamed>

/*!
 @method setComponent:forProtocol:
 @abstract Extensible component support that allows user of ModelIO to customize 
           MDLObjects to fit their format and workflow.
 */
- (void)setComponent:(id<MDLComponent>)component forProtocol:(Protocol *)protocol;

/*!
 @method componentConformingToProtocol:
 @abstract Extensible component support that allows user of ModelIO to customize 
           MDLObjects to fit their format and workflow.
 */
- (nullable id<MDLComponent>)componentConformingToProtocol:(Protocol *)protocol;

/*!
 @property parent
 @abstract Parent object. Nil if no parent.
 @discussion Set to nil when you remove this from an object container inside the 
             parent object.
 */
@property (nonatomic, weak, nullable) MDLObject* parent;

/*!
 @property transform
 @abstract Short hand property for the MDLTransformComponent.
 @discussion 
 
 The default value is nil

 Getter is equivalent to "-[componentConformingToProtocol:@protocol(MDLTransformComponent)]"
 Setter is equivalent to "-[setComponent:forProtocol:@protocol(MDLTransformComponent)]"
 
 @see MDLTransformComponent
 */
@property (nonatomic, nullable, retain) id<MDLTransformComponent> transform;

/*!
 @property children
 @abstract Short hand property for the MDLObjectContainerComponent.
 @discussion
  The default value is nil
 
 Getter is equivalent to "-[componentConformingToProtocol:@protocol(MDLObjectContainerComponent)]"
 Setter is equivalent to "-[setComponent:forProtocol:@protocol(MDLObjectContainerComponent)]"
 
 @see MDLObjectContainerComponent
 */
@property (nonatomic, retain) id<MDLObjectContainerComponent> children;

/*!
 @method addChild:
 @abstract Short hand for adding a child to the current container component and 
           setting the parent to this object.
 @discussion  It will create a default container if none exists. If children are 
              explicitly disallowed for an object, then add a container component 
              that throws on addition.
 
 @see MDLObjectContainer
 */
- (void)addChild:(MDLObject *)child;

/*!
 @method boundingBoxAtTime:
 @abstract Bounds ob object at the specified time
 */
- (MDLAxisAlignedBoundingBox)boundingBoxAtTime:(NSTimeInterval)time;

@end

/*!
 @class MDLObjectContainer
 @abstract Default container object
 @discussion Subclass the object container to support custom containers. Such 
             custom containers might reference in memory representations, offline 
             databases, and so on.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLObjectContainer : NSObject<MDLObjectContainerComponent>

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLCamera.h
/*!
 @header MDLCamera.h
 @framework ModelIO
 @abstract Represent a physically plausible camera model
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLTransform.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLTexture;

/**
 MDLCamera
 
 @summary MDLCamera models a physically plausible camera.
 
 @discussion

 Note that values are represented as float in MDLCamera as it offers sufficient 
 precision, and because calculations will be identical on any processor 
 architecture. This consistency is a requirement of the model.

 MDLCamera provides the a model of the parameters governing the physical process 
 of transforming a scene into an image.

 This process is modeled as a series of steps, each governed by physically 
 plausible properties.
 
 
 1. The position and orientation of the camera
    @see MDLObject transform property
 
    The MDLTransformComponent on an MDLCamera is an MDLTransform.
 
 2. Visible Objects and Lights
    @property nearVisibilityDistance The minimum distance from the camera of a 
              visible object
    @property farVisibilityDistance The maximum distance from the camera of a 
              visible object
 
    Those objects existing between nearVisibilityDistance and farVisibilityDistance 
    are considered to be visible. All lights are considered, irrespective of 
    nearVisibilityDistance and farVisibilityDistance, to compute scene luminance.
 
    @property worldToMetersConversionScale
 
    Some calculations, such as the calculation of stereo view matrices, require
    calculations to occur in world space. Significant quantities measured in mm
    therefore use this conversion scale to perform the calculation. The default
    value is 1.0.
 
 3. Scene Luminance through the lens
 
    @property barrelDistorion
    @property fisheyeDistortion
 
    Illuminated objects result in scene luminance, which passes through the lens.
    All lenses impose some amount of radial distortion which can be computed from 
    focal length. However, some lenses introduce error, and radial distortion can 
    be used as an aesthetic control as well. Therefore radial distortion is 
    provided as a property. If r is the radial distance of a pixel from the center 
    of the projection, then radial distortion is computed as
 
         r' = r * (1 + barrelDistorion * r^2 + fisheyeDistortion * r^4)

    radialDistortion sufficiently describes the distortion characteristic of most 
    lenses. In order to simulate certain other lenses, such as those found in 
    security cameras, fisheye lenses, plastic toy lenses, sport cameras, or some 
    VR headsets, radialDistortion2 is introduced.
 
    The default for the radial distortion parameters is zero, resulting in a 
    rectilinear projection.
 
    @property opticalVignetting
 
    Optical vignetting occurs to some degree in all lenses. It results from light 
    at the edge of an image being blocked as it travels past the lens hood and 
    the internal lens apertures. It is more prevalent with wide apertures. A 
    value of zero indicates no optical vignetting is occuring, and a value of one 
    indicates that vignetting affects all locations in the image according to 
    radial distance. Optical vignetting also occurs in head mounted displays, and 
    the value here can be used as an intended amount of vignetting to apply to an
    image.
 
    @property chromaticAberration
    
    Chromatic aberration occurs to some degree in all lenses. It results from a 
    lens bringing different wavelengths of light to focus at different places on 
    the image plane. A value of zero indicates no chromatic aberration is 
    occurring, and one indicates maximum. Chromatic aberration affects all 
    locations in the image according to radial distance. Chromatic aberration 
    also occurs in head mounted displays, and the value here can be used as an 
    intended amount of chromatic aberration to apply to an image.
 
 4. Geometry of the lens
 
    @property focalLength
 
    The default focal length is 50mm, corresponding to a field of view of 54 
    degrees, and vertical sensor aperture of 24mm. Changing focalLength will 
    update the field of view property.
 
    @property focusDistance
 
    The distance, in meters, at which the lens is focused. The default is 2.5m.
 
    @property fieldOfView
 
    The field of view is calcualted from the focal length and sensor aperture.
    Changing the field of view will update the focalLength property with respect 
    to the sensor aperture. The default is 54 degrees, corresponding to a focal 
    length of 50mm, and a vertical sensor aperture of 24mm.
 
    @property fStop
 
    The f-stop is the ratio of the lens' focal length to the diameter of the 
    entrance pupil. The default is 5.6. It controls the amount of light that 
    reaches the sensor, as well as the size of out of focus parts of the image.
    The diameter of the entrance pupil, is therefore obtained
    by dividing the fStop by the focalLength.
 
 5. Lens exit aperture
 
    @property apertureBladeCount
 
    The shape of out of focus highlights in a scene is commonly known as "bokeh". 
    The aesthetic quality of a lens' bokeh is one of the characteristics that 
    drives the choice of a lens for a particular scene. To a large degree, the 
    appearance of bokeh is governed by the shape of the lens aperture. Typical 
    lens apertures are controlled by a series of overlapping blades that can be 
    irised open and closed. A lens with a five blade aperture will yield a five
    sided bokeh. The default is zero, which is to be interpreted as a perfectly 
    round aperture.
 
    Note that the effect of a filter on the front of the lens can be modeled 
    equivalently at the exit aperture. The MIOCamera does not explicitly provide 
    specification of such effects, but a simulation could incorporate them at 
    this stage.
 
    @property maximumCircleOfConfusion

    Although the size of an out of focus bokeh highlight can be computed from
    other camera properties, it is often necessary to limit the size of the 
    circle of confusion for aesthetic reasons. The circle of confusion is 
    specified in mm, and the default is 0.05mm. The units are mm on the sensor 
    plane.
 
    @property shutterOpenInterval
 
    The length of time in seconds the shutter is open, impacting the amount of 
    light that reaches the sensor and also the length of motion blur trails. The 
    shutter time is not the same thing as scene frame rate. The rule of thumb for 
    movies is that the shutter time should be half the frame rate, so to achieve
    a "filmic" look, the shutter time choice might be 1/48 of a second, since 
    films are usually projected at 24 frames per second. Shutter time is 
    independent of simulation frame rate because motion blur trails and exposure 
    times should be held constant in order to avoid flicker artifacts.
 
 6. Sensor illuminance
 
    @property sensorVerticalAperture
 
    The default aperture is 24mm, corresponding to a 35mm stills camera.
    _____________________
    [][][][][][][][][][][              ^
     \     |         |  \      ^       |
      \    |         |   \    24mm   35mm
       \   |         |    \    v       |
       ][][][][][][][][][][]           v
       ---------------------
           <- 36mm -->
 
    Changing the aperture will update the field of view property with respect to 
    the focal length. The horizontal aperture can be calculated from the aspect 
    property.
 
    @property sensorAspect
    aspect ratio of width versus height of the sensor aperture. The default is 
    36mm/24mm, ie: 1.5.
 
    @property sensorEnlargement

    The sensor enlargment property scales the active region of the sensor. A 
    zoom factor of 2 will result in the central portion of the image being 
    cropped and expanded to fill the image plane. The default is 1.
 
    @property sensorShift
    
    The sensor shift property moves the center of the sensor relative to the 
    lens. This is useful in certain calculations, such as shadow or reflection
    projections, as well as to provide vergence in a parallel stereoscopic camera.

 5. Exposure
 
    Finally, the sensor values need to be converted for display.
 
    @property flash
 
    Flashing is applied to a film stock some time before processing. It is a 
    small and even level of exposure added to the entire image intended shift 
    the brightness and color of darker areas of the image. Since exposure is 
    logarithmic, flash does not affect midtones or highlights.
    
    The equivalent to flash in a color grading system is known as lift. Typically 
    red, green, and blue can be controlled independently.
 
    A negative value for flash can be used to subtract color.
 
    @property exposure
 
    Finally, exposure should be applied to the compressed value. Red,
    green, and blue exposure can be specified separately. The default is 1.0.

    @property exposureCompression
 
    Gamma curve compression where values below the x value are to be passed through,
    about the y value, values are to be clamped at maximum display brightness,
    and a function such as a logarithmic ramp is to be applied in between. The
    default is (1,0, 1.0).

    A displayable value is therefore obtained via
       pow(exposureCompression((sensor value + flash) * exposure), displayGamma)

 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLCamera : MDLObject

/**
 The projection matrix is calculated from the near and far visibility distances,
 and the field of view.
 @see nearVisibilityDistance, nearVisibilityDistance
 */
@property (nonatomic, readonly) matrix_float4x4 projectionMatrix;

/**
 Move the camera back and orient the camera so that a bounding box is framed 
 within the current field of view. Uses the Y axis as up.
 If setNearAndFar is YES, the near and far visibility distances will be set.
 */
- (void)frameBoundingBox:(MDLAxisAlignedBoundingBox)boundingBox setNearAndFar:(BOOL)setNearAndFar;

/**
 Orient the camera so that the camera points at focusPosition. Assumes that the 
 Y axis is up.
 */
- (void)lookAt:(vector_float3)focusPosition;

/**
 Set the position of the camera and orient it so that it points at focusPosition. 
 Assumes that the Y axis is up.
 */
- (void)lookAt:(vector_float3)focusPosition from:(vector_float3)cameraPosition;

/**
 A convenience function to calculate a ray from the camera to a pixel in a 
 viewport of a given size
 */
- (vector_float3)rayTo:(vector_int2)pixel forViewPort:(vector_int2)size;

/**
 Bounding distance for visible objects 
 */
@property (nonatomic, assign) float nearVisibilityDistance;
@property (nonatomic, assign) float farVisibilityDistance;

/**
 World to meters conversion scale. Required for certain calculations.
 */
@property (nonatomic, assign) float worldToMetersConversionScale;

/**
 Radial distortion of the lens, second order term
 */
@property (nonatomic, assign) float barrelDistortion;

/**
 Radial distortion of the lens, fourth order term
 */
@property (nonatomic, assign) float fisheyeDistortion;

/**
 Amount of optical vignetting, rom zero to one.
 */
@property (nonatomic, assign) float opticalVignetting;

/**
 Amount of chromatic abberation, from zero to one.
 */
@property (nonatomic, assign) float chromaticAberration;

/**
 Lens focal length in mm.
 @see fieldOfView
 */
@property (nonatomic, assign) float focalLength;

/**
 Focus distance
 */
@property (nonatomic, assign) float focusDistance;

/**
 The field of view, in degrees.
 @see focalLength
 */
@property (nonatomic, assign) float fieldOfView;

/**
 f-stop, default is 5.6
 */
@property (nonatomic, assign) float fStop;

/**
  Aperture blade count, where zero indicates a circle.
 */
@property (nonatomic, assign) NSUInteger apertureBladeCount;

/**
 Maximum circle of confusion size in mm on the image plane
 */
@property (nonatomic, assign) float maximumCircleOfConfusion;

/**
 Create a bokeh kernel corresponding to the apertureBladeCount
 */
- (MDLTexture *)bokehKernelWithSize:(vector_int2)size;

/**
 Shutter open interval, in seconds
 */
@property (nonatomic, assign) NSTimeInterval shutterOpenInterval;

/**
 vertical aperture of the sensor or film gate, default is 24mm
 @see sensorAspect
*/
@property (nonatomic, assign) float sensorVerticalAperture;

/** 
 Sensor or film gate aperture aspect ratio, default is 1.5
 @see sensorVerticalAperture
 */
@property (nonatomic, assign) float sensorAspect;

/** 
 Sensor zoom factor
 */
@property (nonatomic, assign) vector_float2 sensorEnlargement;

/**
 Sensor shift factor in mm.
 */
@property (nonatomic, assign) vector_float2 sensorShift;

/**
 Flash amount, unit less
 */
@property (nonatomic, assign) vector_float3 flash;

/**
 exposure curve compression where values below the x value are to be passed through,
 above the y value, values are to be clamped at maximum display brightness, and a
 function such as a logarithmic ramp is to be applied in between.
 */
@property (nonatomic, assign) vector_float2 exposureCompression;

/**
 Exposure amount, unit less
 */
@property (nonatomic, assign) vector_float3 exposure;


@end


NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLStereoscopicCamera : MDLCamera

/**
 Inter-pupillary distance in mm.
 Default is 63mm.
 */
@property (nonatomic, assign) float interPupillaryDistance;

/**
 Vergence in a stereoscopic camera can be controlled in two ways. A toed-in 
 binocular stereoscopic camera rotates the lens and sensor together such that a 
 ray projected from the center of either sensor and lens meets at a point. A 
 parallel binocular stereoscopic camera accomplishes the same thing by shifting 
 the relative centers of the sensor and lens.
 
 If a parallel binocular stereoscopic camera is modeled, the sensor should be 
 considered to have shifted by an amount h. If left and right vergence are equal,
   h = (focal length * interOcularDistance) / distance to vergence point.
 
 Vergence is measured in degrees towards center and is usually positive.
 */

@property (nonatomic, assign) float leftVergence;
@property (nonatomic, assign) float rightVergence;

/**
 The amount, as a percentage of image width to offset an image towards the other 
 camera. This value is used in a stereo grade to enhance or reduce the intensity 
 of the stereoscopic effect
 */
@property (nonatomic, assign) float overlap;

/**
 Convenience utilities to create view and projection matrices. The view matrix
 calculations requires that the world to meters conversion scale be set.
 
 @see worldToMetersConversionScale
 */
@property (nonatomic, readonly) matrix_float4x4 leftViewMatrix;
@property (nonatomic, readonly) matrix_float4x4 rightViewMatrix;
@property (nonatomic, readonly) matrix_float4x4 leftProjectionMatrix;
@property (nonatomic, readonly) matrix_float4x4 rightProjectionMatrix;



@end

NS_ASSUME_NONNULL_END

// ==========  ModelIO.framework/Headers/MDLLight.h
/*!
 @header MDLLight.h
 @framework ModelIO
 @abstract Structures for describing lights for rendering
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTransform.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MDLLightType) {
    MDLLightTypeUnknown = 0,
    MDLLightTypeAmbient,
    MDLLightTypeDirectional,
    MDLLightTypeSpot,
    MDLLightTypePoint,
    MDLLightTypeLinear,
    MDLLightTypeDiscArea,
    MDLLightTypeRectangularArea,
    MDLLightTypeSuperElliptical,
    MDLLightTypePhotometric,
    MDLLightTypeProbe,
    MDLLightTypeEnvironment
};

@class MDLColorSpec;
@class MDLTexture;

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLLight : MDLObject

/** A utility function that returns the irradiance from the light at a given point.
    @discussion point is world space
  */
- (CGColorRef)irradianceAtPoint:(vector_float3)point;
- (CGColorRef)irradianceAtPoint:(vector_float3)point colorSpace:(CGColorSpaceRef)colorSpace;

@property (nonatomic, readwrite) MDLLightType lightType;

@end

/*!
 @class MDLPhysicallyPlausibleLight
 @abstract A light with characteristics representing plausible real world lights
 
 @property color The color of the light.
 @property lumens The brightness of the light.
 @property innerConeAngle Within this cone, light is at maximum brightness. Units are degrees.
 @property outerConeAngle Between the inner cone angle and the outer, light 
           quadratically attenuates to zero.
 @property attenuationStartDistance. Within the attenuation start distance, the
           light is maximally bright.
 @property attenuationEndDistance. Beyond this distance, there is no light.

 @discussion A good formula to calculate falloff is
 
   falloff = clamp((1 - (distance/attenuationStartDistance)^4) ^2), 0, 1) / (distance^2 + 1)
 
   Note that adding one to distance in the denominator prevents numerical issues 
   very close to the light's origin.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLPhysicallyPlausibleLight : MDLLight

/**
 Light color specified by color temperature, in degrees Kelvin
 @discussion default color is 6500K, cool daylight.
 */
- (void)setColorByTemperature:(float)temperature;

@property (nullable, nonatomic) CGColorRef color;

// default light intensity is 1000 lumens
@property (nonatomic, readwrite) float lumens;

// 90 means down the light axis to perpendicular is spanned (lightType will be MDLLightSpot)
// 180 means down the light axis to up the light axis is spanned (lightType will be MDLLightPoint)
// default is 22.5 degrees
@property (nonatomic, readwrite) float innerConeAngle;
@property (nonatomic, readwrite) float outerConeAngle;
@property (nonatomic, readwrite) float attenuationStartDistance;
@property (nonatomic, readwrite) float attenuationEndDistance;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLAreaLight : MDLPhysicallyPlausibleLight

@property (nonatomic, readwrite) float areaRadius;
@property (nonatomic, readwrite) vector_float2 superEllipticPower;
@property (nonatomic, readwrite) float aspect;

@end

/*!
 @class MDLPhotometricLight
 @abstract A light created from measurements at various angles.
 
 @property lightCubeMap A cube map that can be sampled at various directions to
           learn the intensity of the light in that direction.
 @property sphericalHarmonicsLevel The value generateSphericalHarmonicsFromLight: 
           used to calculate the spherical harmonics coefficients
 @property sphericalHarmonicsCoefficients The spherical harmonic coefficiencts
           calculated by generateSphericalHarmonicsFromLight:
*/

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLPhotometricLight : MDLPhysicallyPlausibleLight

// Init with an IES profile file, generate a light web of specified width and height
- (nullable instancetype)initWithIESProfile:(NSURL*)URL;

-(void)generateSphericalHarmonicsFromLight:(NSUInteger)sphericalHarmonicsLevel;

-(void)generateCubemapFromLight:(NSUInteger)textureSize;

@property (nonatomic, retain, nullable, readonly) MDLTexture *lightCubeMap;

@property (nonatomic, readonly) NSUInteger sphericalHarmonicsLevel;

@property (nonatomic, copy, nullable, readonly) NSData *sphericalHarmonicsCoefficients;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLLightProbe : MDLLight

-(instancetype)initWithReflectiveTexture:(nullable MDLTexture*)reflectiveTexture
                       irradianceTexture:(nullable MDLTexture*)irradianceTexture;

-(void)generateSphericalHarmonicsFromIrradiance:(NSUInteger)sphericalHarmonicsLevel;

@property (nonatomic, retain, nullable, readonly) MDLTexture *reflectiveTexture;
@property (nonatomic, retain, nullable, readonly) MDLTexture *irradianceTexture;
@property (nonatomic, readonly) NSUInteger sphericalHarmonicsLevel;
@property (nonatomic, copy, nullable, readonly) NSData *sphericalHarmonicsCoefficients;

@end


@interface MDLLightProbe (MDLLightBaking)

+ (nullable MDLLightProbe *)lightProbeWithTextureSize:(NSInteger)textureSize
                                          forLocation:(MDLTransform *)transform
                                     lightsToConsider:(NSArray<MDLLight*>*)lightsToConsider
                                    objectsToConsider:(NSArray<MDLObject*>*)objectsToConsider
                                    reflectiveCubemap:(nullable MDLTexture*)reflectiveCubemap
                                    irradianceCubemap:(nullable MDLTexture*)irradianceCubemap;

@end


NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLTypes.h
/*!
 @header MDLTypes.h
 @framework ModelIO
 @abstract A variety of types used in representing 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#define MDL_INLINE __attribute__((__always_inline__))
#define MDL_CONST_INLINE __attribute__((__always_inline__,__const__))

#import <ModelIO/ModelIOExports.h>
#import <Foundation/Foundation.h>
#include <simd/simd.h>
#include <math.h>

/* Alembic file format, file extension ABC, UTI public.alembic */
MDL_EXPORT NSString * __nonnull const kUTTypeAlembic NS_AVAILABLE(10_11, 9_0);

/* 3d Object file format, file extension OBJ, UTI public.geometry-definition-format */
MDL_EXPORT NSString * __nonnull const kUTType3dObject NS_AVAILABLE(10_11, 9_0);

/* Polygon file format, file extension PLY, UTI public.polygon-file-format */
MDL_EXPORT NSString * __nonnull const kUTTypePolygon NS_AVAILABLE(10_11, 9_0);

/* Stereolithography file format, file extension STL, UTI public.standard-tesselated-geometry-format */
MDL_EXPORT NSString * __nonnull const kUTTypeStereolithography NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSUInteger, MDLIndexBitDepth)
{
    MDLIndexBitDepthInvalid = 0,
    MDLIndexBitDepthUInt8 = 8,
    MDLIndexBitDepthUint8 = 8,
    MDLIndexBitDepthUInt16 = 16,
    MDLIndexBitDepthUint16 = 16,
    MDLIndexBitDepthUInt32 = 32,
    MDLIndexBitDepthUint32 = 32,
};

typedef NS_ENUM(NSInteger, MDLGeometryType) {
    MDLGeometryTypePoints = 0,
    MDLGeometryTypeLines,
    MDLGeometryTypeTriangles,
    MDLGeometryTypeTriangleStrips,
    MDLGeometryTypeQuads,
    MDLGeometryTypeVariableTopology,
    MDLGeometryKindPoints = 0,        // Legacy enumerations
    MDLGeometryKindLines,
    MDLGeometryKindTriangles,
    MDLGeometryKindTriangleStrips,
    MDLGeometryKindQuads
};

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLNamed
@required
@property (nonatomic, copy) NSString *name;
@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLComponent <NSObject>
@end

@class MDLObject;

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@protocol MDLObjectContainerComponent <MDLComponent, NSFastEnumeration>

- (void)addObject:(MDLObject*)object;
- (void)removeObject:(MDLObject*)object;

// returns an array of this object's contained objects, aka children
@property (nonatomic, readonly, retain) NSArray<MDLObject*> *objects;

@end

typedef struct MDL_EXPORT_CPPCLASS {
    vector_float3 maxBounds;
    vector_float3 minBounds;
} MDLAxisAlignedBoundingBox;

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLMaterial.h
/*!
 @header MDLMaterial.h
 @framework ModelIO
 @abstract Structures for describing rendering material properties
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#pragma once

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <simd/simd.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLTransform.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLTexture;

/**
 MDLMaterialSemantic
 
 @summary The material semantics are identifiers for material properties 
            formally identified by one of the standard material descriptors.
 
 @discussion When files containing material properties are loaded and translated 
             by ModelIO, an appropriate standard material descriptor will be 
             chosen, and any properties translated from the loaded file can be 
             retrieved using one of these semantics.
 
 MDLMaterialSemanticBaseColor
    The inherent color of a surface to be used as a modulator during shading. 
    Default is 50% gray
 
 MDLMaterialSemanticSubsurface,
    The degree to which light scatters under the surface of a material
 
 MDLMaterialSemanticMetallic
    A blend between a material behaving as a dielectric material at zero, and a 
    metal at one.
 
 MDLMaterialSemanticSpecular
    Specular response to incident light
 
 MDLMaterialSemanticSpecularExponent
    Power of the specular exponent in the case that a Blinn/Phong BSDF is in use.
 
 MDLMaterialSemanticSpecularTint
    At zero, the specular highlight will use the hue, saturation, and intensity 
    of incoming light to color the specular response; at one, the material's 
    base color, and the light's intensity will be used.
 
 MDLMaterialSemanticRoughness
    Controls diffuse and specular response. A value of zero is smooth and shiny. 
    At one, a diffuse material will retroreflect, and the specular highlight 
    will be very spread out.
 
 MDLMaterialSemanticAnisotropic
    The degree to which the specular highlight is elongated in the direction of 
    the local tangent basis. A mesh that does not have a tangent basis will not 
    respond to this parameter.
 
 MDLMaterialSemanticAnisotropicRotation
    The degree to which the anisotropy is rotated relative to the direction of the
    local tangent basis. Values from zero to one are mapped to zero to two PI.
 
 MDLMaterialSemanticSheen
    A specular tint that appears at glancing angles on an object
 
 MDLMaterialSemanticSheenTint
    At zero, the specular highlight will use the hue, saturation, and intensity 
    of incoming light to color the specular response; at one, the material's 
    base color, and the light's intensity will be used.
 
 MDLMaterialSemanticClearcoat
    A second specular highlight, much like the gloss that results from a clear 
    coat on an automotive finish
 
 MDLMaterialSemanticClearcoatGloss
    The glossiness of the clear coat highlight.

 MDLMaterialSemanticEmission
    A value that is to be emitted as radiance by a surface
 
 MDLMaterialSemanticBump
    A value that perturbs surface normals according to the local gradient of 
    the property
 
 MDLMaterialSemanticOpacity
    The opacity of the surface
 
 MDLMaterialSemanticInterfaceIndexOfRefraction
    n1 in Schlick's equation, typically 1.0 for air
 
 MDLMaterialSemanticMaterialIndexOfRefraction
    n2 in Schlick's equation

 MDLMaterialSemanticObjectSpaceNormal
    A value that perturbs surface normals in object space
 
 MDLMaterialSemanticTangentSpaceNormal
    A value that perturbs surface normals in a local tangent space

 MDLMaterialSemanticDisplacement
    Displacement of a surface relative to surface normal
 
 MDLMaterialSemanticDisplacementScale
    Scaling factor for displacement
 
 MDLMaterialSemanticAmbientOcclusion
    Ambient occlusion describes the accessibility of the surface to the 
    surrounding radiant environment and is typically used to attenuate it. It is 
    not intended to attenuate direct illumination sources.
 
 MDLMaterialSemanticAmbientOcclusionScale
    The degree to which the ambient occlusion values are applied
 
 MDLMaterialSemanticUserDefined = 0x8000
    Properties with this value are created when material properties are 
    translated for which no known semantic applies.
    Semantics defined at greater than this value are available to be user defined.
    The first value is also used to indicate

 */

typedef NS_ENUM(NSUInteger, MDLMaterialSemantic) {
    MDLMaterialSemanticBaseColor = 0,
    MDLMaterialSemanticSubsurface,
    MDLMaterialSemanticMetallic,
    MDLMaterialSemanticSpecular,
    MDLMaterialSemanticSpecularExponent,
    MDLMaterialSemanticSpecularTint,
    MDLMaterialSemanticRoughness,
    MDLMaterialSemanticAnisotropic,
    MDLMaterialSemanticAnisotropicRotation,
    MDLMaterialSemanticSheen,
    MDLMaterialSemanticSheenTint,
    MDLMaterialSemanticClearcoat,
    MDLMaterialSemanticClearcoatGloss,

    MDLMaterialSemanticEmission,
    MDLMaterialSemanticBump,
    MDLMaterialSemanticOpacity,
    MDLMaterialSemanticInterfaceIndexOfRefraction,
    MDLMaterialSemanticMaterialIndexOfRefraction,
    MDLMaterialSemanticObjectSpaceNormal,
    MDLMaterialSemanticTangentSpaceNormal,
    MDLMaterialSemanticDisplacement,
    MDLMaterialSemanticDisplacementScale,
    MDLMaterialSemanticAmbientOcclusion,
    MDLMaterialSemanticAmbientOcclusionScale,
    
    MDLMaterialSemanticNone = 0x8000,
    MDLMaterialSemanticUserDefined = 0x8001
};

typedef NS_ENUM(NSUInteger, MDLMaterialPropertyType) {
    MDLMaterialPropertyTypeNone = 0, // default resulting from [MDLMaterialProperty init]
    MDLMaterialPropertyTypeString,
    MDLMaterialPropertyTypeURL,
    MDLMaterialPropertyTypeTexture,
    MDLMaterialPropertyTypeColor,
    MDLMaterialPropertyTypeFloat,
    MDLMaterialPropertyTypeFloat2,
    MDLMaterialPropertyTypeFloat3,
    MDLMaterialPropertyTypeFloat4,
    MDLMaterialPropertyTypeMatrix44
};

/**
 Texture filtering
 */

typedef NS_ENUM(NSUInteger, MDLMaterialTextureWrapMode) {
    MDLMaterialTextureWrapModeClamp,
    MDLMaterialTextureWrapModeRepeat,
    MDLMaterialTextureWrapModeMirror,
};

typedef NS_ENUM(NSUInteger, MDLMaterialTextureFilterMode) {
    MDLMaterialTextureFilterModeNearest,
    MDLMaterialTextureFilterModeLinear,
};

typedef NS_ENUM(NSUInteger, MDLMaterialMipMapFilterMode) {
    MDLMaterialMipMapFilterModeNearest,
    MDLMaterialMipMapFilterModeLinear,
};

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLTextureFilter : NSObject
@property (nonatomic, assign) MDLMaterialTextureWrapMode sWrapMode;
@property (nonatomic, assign) MDLMaterialTextureWrapMode tWrapMode;
@property (nonatomic, assign) MDLMaterialTextureWrapMode rWrapMode;
@property (nonatomic, assign) MDLMaterialTextureFilterMode minFilter;
@property (nonatomic, assign) MDLMaterialTextureFilterMode magFilter;
@property (nonatomic, assign) MDLMaterialMipMapFilterMode mipFilter;
@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLTextureSampler : NSObject

@property (nonatomic, retain, nullable) MDLTexture *texture;
@property (nonatomic, retain, nullable) MDLTextureFilter *hardwareFilter;
@property (nonatomic, retain, nullable) MDLTransform *transform;

@end


/**
 If a color is encoded in a floatN property, it is to be interpreted as 
 a Rec 709 color.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMaterialProperty : NSObject<MDLNamed>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float:(float)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float2:(vector_float2)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float3:(vector_float3)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic float4:(vector_float4)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic matrix4x4:(matrix_float4x4)value;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic URL:(nullable NSURL*)URL;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic string:(nullable NSString *)string;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic textureSampler:(nullable MDLTextureSampler*)textureSampler;
- (instancetype)initWithName:(NSString *)name semantic:(MDLMaterialSemantic)semantic color:(CGColorRef)color;

- (void)setProperties:(MDLMaterialProperty *)property;

@property (nonatomic, assign) MDLMaterialSemantic semantic;
@property (nonatomic, readonly) MDLMaterialPropertyType type;

/** @see MDLNamed */
@property (nonatomic, copy) NSString *name;

@property (nonatomic, copy, nullable) NSString *stringValue;
@property (nonatomic, copy, nullable) NSURL *URLValue;
@property (nonatomic, retain, nullable) MDLTextureSampler *textureSamplerValue;
@property (nullable, nonatomic) CGColorRef color;
@property (nonatomic, assign) float floatValue;
@property (nonatomic, assign) vector_float2 float2Value;
@property (nonatomic, assign) vector_float3 float3Value;
@property (nonatomic, assign) vector_float4 float4Value;
@property (nonatomic, assign) matrix_float4x4 matrix4x4;

@end

/**
 The base scattering function is Lambertian, with a Blinn-Phong specular response.
 Specular power for Blinn-Phong can be derived from the roughness property using 
 an approximation.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLScatteringFunction : NSObject<MDLNamed>

/** @see MDLNamed */
@property (nonatomic, copy) NSString *name;

@property (nonatomic, readonly, retain) MDLMaterialProperty *baseColor;
@property (nonatomic, readonly, retain) MDLMaterialProperty *emission;
@property (nonatomic, readonly, retain) MDLMaterialProperty *specular;
@property (nonatomic, readonly, retain) MDLMaterialProperty *materialIndexOfRefraction;
@property (nonatomic, readonly, retain) MDLMaterialProperty *interfaceIndexOfRefraction;
@property (nonatomic, readonly, retain) MDLMaterialProperty *normal;
@property (nonatomic, readonly, retain) MDLMaterialProperty *ambientOcclusion;
@property (nonatomic, readonly, retain) MDLMaterialProperty *ambientOcclusionScale;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLPhysicallyPlausibleScatteringFunction : MDLScatteringFunction

@property (nonatomic, readonly) NSInteger version; // currently 1

@property (nonatomic, readonly, retain) MDLMaterialProperty *subsurface;           // diffuse shape
@property (nonatomic, readonly, retain) MDLMaterialProperty *metallic;             // 0 = dielectric, 1 = metallic
@property (nonatomic, readonly, retain) MDLMaterialProperty *specularAmount;       // specular value
@property (nonatomic, readonly, retain) MDLMaterialProperty *specularTint;         // bias towards surface color
@property (nonatomic, readonly, retain) MDLMaterialProperty *roughness;            // diffuse and specular response
@property (nonatomic, readonly, retain) MDLMaterialProperty *anisotropic;          // shape of specular highlight
@property (nonatomic, readonly, retain) MDLMaterialProperty *anisotropicRotation;  // shape of specular highlight
@property (nonatomic, readonly, retain) MDLMaterialProperty *sheen;                // like velvet
@property (nonatomic, readonly, retain) MDLMaterialProperty *sheenTint;            // bias towards surface color
@property (nonatomic, readonly, retain) MDLMaterialProperty *clearcoat;            // like clear acrylic on a car
@property (nonatomic, readonly, retain) MDLMaterialProperty *clearcoatGloss;       // 0 = satin, 1 = glossy

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLMaterial : NSObject<MDLNamed, NSFastEnumeration>

- (instancetype)initWithName:(NSString*)name scatteringFunction:(MDLScatteringFunction*)scatteringFunction;

- (void)setProperty:(MDLMaterialProperty*)property;
- (void)removeProperty:(MDLMaterialProperty*)property;
- (nullable MDLMaterialProperty*)propertyNamed:(NSString*)name;
- (nullable MDLMaterialProperty*)propertyWithSemantic:(MDLMaterialSemantic)semantic;
- (void)removeAllProperties;

@property (nonatomic, readonly, retain) MDLScatteringFunction *scatteringFunction;

/** @see MDLNamed */
@property (nonatomic, copy) NSString *name;

// If a property is not found by propertyForKey and baseMaterial is not nil,
// propertyForKey will invoke propertyForKey on baseMaterial.
// All other selectors disregard baseMaterial.
@property (nonatomic, retain, nullable) MDLMaterial *baseMaterial;

- (nullable MDLMaterialProperty *)objectAtIndexedSubscript:(NSUInteger)idx;
- (nullable MDLMaterialProperty *)objectForKeyedSubscript:(NSString*)name;
@property (nonatomic, readonly) NSUInteger count;

@end

NS_ASSUME_NONNULL_END

// ==========  ModelIO.framework/Headers/ModelIO.h
//
//  @header    ModelIO.h
//  @framework ModelIO
//
//  @copyright (c)2015 Apple, Inc. All rights reserved.
//

#import <ModelIO/ModelIOExports.h>

#import <ModelIO/MDLAsset.h>
#import <ModelIO/MDLCamera.h>
#import <ModelIO/MDLLight.h>
#import <ModelIO/MDLMaterial.h>
#import <ModelIO/MDLMesh.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <ModelIO/MDLObject.h>
#import <ModelIO/MDLSubmesh.h>
#import <ModelIO/MDLTexture.h>
#import <ModelIO/MDLTransform.h>
#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLVertexDescriptor.h>
#import <ModelIO/MDLVoxelArray.h>
// ==========  ModelIO.framework/Headers/MDLVoxelArray.h
//
//  MDLVoxelArray.h
// @framework ModelIO
//
// @copyright © 2015 Apple Inc. All rights reserved.
//

/*!
 @header MDLVoxelArray.h
 @framework ModelIO
 @abstract Structures for describing volumetric data obtained from 3d assets
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLMeshBuffer.h>
#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class MDLAsset;
@class MDLMesh;

/**
 MDLVoxelIndex is a four component voxel index.
 @discussion The index's x, y, and z components correspond to the voxel grid's
 x, y, and z indices. The w component corresponds to the voxel grid shell level.
 A shell level of zero corresponds to a voxel on the surface of an object.
 A positive shell index corresponds to a shell on the exterior of the object,
 and a negative index corresponds to a shell on the interior. A shell index of
 one is immediately adjacent to the zero shell, two is immediately adjacent
 one, and so on.
 */
typedef vector_int4 MDLVoxelIndex;

/**
 MDLVoxelIndexExtent is the index space bounds of the voxel grid.
 */
typedef struct {
    MDLVoxelIndex minimumExtent;
    MDLVoxelIndex maximumExtent;
} MDLVoxelIndexExtent;

/**
 @class MDLVoxelArray
 @summary Voxel data represented on a three dimensional grid. Voxel data can
          include voxels considered to be on the surface of an object, and a 
          series of shells on the outside and inside of the surface.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVoxelArray : NSObject

/**
 Initialize a voxel grid from an MDLAsset and dilate the resulting voxels by
 a number of interior and exterior shells. 
 Routine will attempt to create a closed volume model by applying patches of
 a given radius to any holes it may find in the asset.
 
 @param divisions The number of divisions to divide the vertical extent of the 
        model by.
 @param interiorShells The number of shells to compute inside the surface shell
 @param exteriorShells The number of shells to compute outside the surface shell
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (instancetype)initWithAsset:(MDLAsset*)asset
                    divisions:(int)divisions
               interiorShells:(int)interiorShells
               exteriorShells:(int)exteriorShells
                  patchRadius:(float)patchRadius;

/**
 Initialize a voxel grid from an MDLAsset and dilate the resulting voxels by
 a spatial distance in the interior and exterior directions.
 Routine will attempt to create a closed volume model by applying "patches" of
 a given radius to any holes it may find in the asset.
 
 @param divisions The number of divisions to divide the vertical extent of the
 model by.
 @param interiorNBWidth The interior narrow band width in world space units
 @param exteriorNBWidth The exterior narrow band width in world space units
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (instancetype)initWithAsset:(MDLAsset*)asset
                    divisions:(int)divisions
              interiorNBWidth:(float)interiorNBWidth
              exteriorNBWidth:(float)exteriorNBWidth
                  patchRadius:(float)patchRadius;


/**
 Initialize a voxel grid from an NSData containing an array of MDLVoxelIndex values.
 
 @param boundingBox The bounds defining the extent of the volume model in Cartesian space
 @param voxelExtent The extent of a single voxel
 */
- (instancetype)initWithData:(NSData*)voxelData
                 boundingBox:(MDLAxisAlignedBoundingBox)boundingBox
                 voxelExtent:(float)voxelExtent;

/**
 Create a mesh from the voxel grid
 */
- (nullable MDLMesh*)meshUsingAllocator:(nullable id<MDLMeshBufferAllocator>)allocator;

/**
 Determine if a sample exists at the specified index
 @discussion the allowAny parameters can be used to wildcard any dimensions. This 
             is useful to perform queries such as determining if any voxel 
             exists on the XY plane at a certain Z, or if any voxel exists at 
             any X, Y, Z, but a particular shell, and so on.
 */
- (BOOL)voxelExistsAtIndex:(MDLVoxelIndex)index
                 allowAnyX:(BOOL)allowAnyX allowAnyY:(BOOL)allowAnyY allowAnyZ:(BOOL)allowAnyZ
             allowAnyShell:(BOOL)allowAnyShell;

/**
 Set a sample at the specified index
 @discussion the extent, bounds, and shell properties may be modified
 */
- (void)setVoxelAtIndex:(MDLVoxelIndex)index;

/**
 Set voxels corresponding to a mesh
 Routine will attempt to create a closed volume model by applying "patches" of
 a given radius to any holes it may find in the mesh.
 
 @param divisions The number of divisions to divide the vertical extent of the
 model by.
 @param interiorShells The number of shells to compute inside the surface shell
 @param exteriorShells The number of shells to compute outside the surface shell
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (void)setVoxelsForMesh:(nonnull MDLMesh*)mesh
               divisions:(int)divisions
          interiorShells:(int)interiorShells
          exteriorShells:(int)exteriorShells
             patchRadius:(float)patchRadius;


/**
 Set voxels corresponding to a mesh
 Routine will attempt to create a closed volume model by applying "patches" of
 a given radius to any holes it may find in the mesh.
 
 @param divisions The number of divisions to divide the vertical extent of the
 model by.
 @param interiorNBWidth The interior narrow band width in world space units
 @param exteriorNBWidth The exterior narrow band width in world space units
 @param patchRadius The radius of the largest model mending patch in world space units
 */
- (void)setVoxelsForMesh:(nonnull MDLMesh*)mesh
               divisions:(int)divisions
         interiorNBWidth:(float)interiorNBWidth
         exteriorNBWidth:(float)exteriorNBWidth
             patchRadius:(float)patchRadius;


/**
 Returns an NSData containing the indices of all voxels found in the extent
 */
- (nullable NSData *)voxelsWithinExtent:(MDLVoxelIndexExtent)extent;

/**
 Returns an NSData containing the indices of all voxels in the voxel grid
 */
- (nullable NSData *)voxelIndices;

/**
 Union modifies the voxel grid to be the merger with the supplied voxel grid.
 It is assumed that the spatial voxel extent of one voxel in the supplied grid is the same as that of the voxel grid.
 Note that the shell level data will be cleared.
 */
- (void)unionWithVoxels:(MDLVoxelArray*)voxels;

/**
 Difference modifies the voxel grid so that voxels also in the supplied voxel grid are removed.
 It is assumed that the spatial voxel extent of one voxel in the supplied grid is the same as that of the voxel grid.
 Note that the shell level data will be cleared.
 */
- (void)differenceWithVoxels:(MDLVoxelArray*)voxels;

/**
 Intersection modifies the voxel grid so that only voxels that are also in the supplied voxel grid are retained.
 It is assumed that the spatial voxel extent of one voxel in the supplied grid is the same as that of the voxel grid.
 Note that the shell level data will be cleared.
 */
- (void)intersectWithVoxels:(MDLVoxelArray*)voxels;

/**
 Return the voxel index corresponding to a point in space
 */
- (MDLVoxelIndex)indexOfSpatialLocation:(vector_float3)location;

/**
 Return the spatial location of the center of the indexed voxel
 */
- (vector_float3)spatialLocationOfIndex:(MDLVoxelIndex)index;

/**
 The bounding box of an indexed voxel
 */
- (MDLAxisAlignedBoundingBox)voxelBoundingBoxAtIndex:(MDLVoxelIndex)index;

/**
 The number of voxels in the grid
 */
@property (nonatomic, readonly) NSUInteger count;

/**
 The extent of the voxel grid in index space
 */
@property (nonatomic, readonly) MDLVoxelIndexExtent voxelIndexExtent;

/**
 The extent of the voxel grid in Cartesian space
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox boundingBox;

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/ModelIOExports.h
//
// @header ModelIOExports.h
// @framework ModelIO
//
// @copyright (c) 2015 Apple. All rights reserved.
//
#pragma once

#ifdef __cplusplus
#   define MDL_EXPORT_CPPCLASS __attribute__((visibility ("default")))
#   define MDL_EXPORT extern "C" __attribute__((visibility ("default")))
#else
#   define MDL_EXPORT extern __attribute__((visibility ("default")))
#endif
// ==========  ModelIO.framework/Headers/MDLVertexDescriptor.h
/*!
 @header MDLVertexDescriptor.h
 @framework ModelIO
 @abstract Structures for describing layout of vertex data in buffers
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */
#import <Foundation/Foundation.h>
#import "ModelIOExports.h"
#import "MDLMeshBuffer.h"
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @group Default MDLVertexAttribute Names
 @abstract Default names for common vertex attribute types
 @discussion 

 These are names that are created during 3d asset file loading to correspond
 to data found in those files.
 */

/*! The attribute data describes the degree to which a surface’s appearance 
    changes in appearance when rotated about its normal vector. */
MDL_EXPORT NSString * const MDLVertexAttributeAnisotropy;

/*! The normal to a curve at a vertex position */
MDL_EXPORT NSString * const MDLVertexAttributeBinormal;

/*! The vector completing a tangent basis at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeBitangent;

/*! Color of a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeColor;

/*! A crease value along an edge to be applied during subdivision.
    A zero value indicates an edge is smooth, one is sharply creased. */
MDL_EXPORT NSString * const MDLVertexAttributeEdgeCrease;

/*! Indices of joints in an animation rig corresponding to weighting information */
MDL_EXPORT NSString * const MDLVertexAttributeJointIndices;

/*! Weights corresponding to joints for the purpose of blending animation */
MDL_EXPORT NSString * const MDLVertexAttributeJointWeights;

/*! The direction of a normal at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeNormal;

/*! A value indicating the degree to which a vertex is occluded by surrounding geometry */
MDL_EXPORT NSString * const MDLVertexAttributeOcclusionValue;

/*! The position of a vertex */
MDL_EXPORT NSString * const MDLVertexAttributePosition;

/*! The u direction of a shading basis at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeShadingBasisU;

/*! The v direction of a shading basis at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeShadingBasisV;

/*! Stencil values for subdivision at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeSubdivisionStencil;

/*! A vector tangent to a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeTangent;

/*! Texture coordinate mapping at a vertex */
MDL_EXPORT NSString * const MDLVertexAttributeTextureCoordinate;


/*!
 @enum MDLVertexFormat
 @abstract Describes the format of a an attribute in a vertex buffer
 @discussion Designed to be very similar to MTLVertexDescriptor to ease the 
             translation from one to the other. Values are chosen such that 
             packed types would all be less than 0x1000 and the bottom 5 bits 
             can be used to determine the number of channels/components in the 
             format.
 */
typedef NS_ENUM(NSUInteger, MDLVertexFormat)
{
    MDLVertexFormatInvalid = 0,
    
    MDLVertexFormatPackedBit = 0x1000,

    MDLVertexFormatUCharBits = 0x10000,
    MDLVertexFormatCharBits = 0x20000,
    MDLVertexFormatUCharNormalizedBits = 0x30000,
    MDLVertexFormatCharNormalizedBits = 0x40000,
    MDLVertexFormatUShortBits = 0x50000,
    MDLVertexFormatShortBits = 0x60000,
    MDLVertexFormatUShortNormalizedBits = 0x70000,
    MDLVertexFormatShortNormalizedBits = 0x80000,
    MDLVertexFormatUIntBits = 0x90000,
    MDLVertexFormatIntBits = 0xA0000,
    MDLVertexFormatHalfBits = 0xB0000,
    MDLVertexFormatFloatBits = 0xC0000,
    
    MDLVertexFormatUChar =  MDLVertexFormatUCharBits | 1,
    MDLVertexFormatUChar2 = MDLVertexFormatUCharBits | 2,
    MDLVertexFormatUChar3 = MDLVertexFormatUCharBits | 3,
    MDLVertexFormatUChar4 = MDLVertexFormatUCharBits | 4,

    MDLVertexFormatChar =  MDLVertexFormatCharBits | 1,
    MDLVertexFormatChar2 = MDLVertexFormatCharBits | 2,
    MDLVertexFormatChar3 = MDLVertexFormatCharBits | 3,
    MDLVertexFormatChar4 = MDLVertexFormatCharBits | 4,

    MDLVertexFormatUCharNormalized =  MDLVertexFormatUCharNormalizedBits | 1,
    MDLVertexFormatUChar2Normalized = MDLVertexFormatUCharNormalizedBits | 2,
    MDLVertexFormatUChar3Normalized = MDLVertexFormatUCharNormalizedBits | 3,
    MDLVertexFormatUChar4Normalized = MDLVertexFormatUCharNormalizedBits | 4,

    MDLVertexFormatCharNormalized =  MDLVertexFormatCharNormalizedBits | 1,
    MDLVertexFormatChar2Normalized = MDLVertexFormatCharNormalizedBits | 2,
    MDLVertexFormatChar3Normalized = MDLVertexFormatCharNormalizedBits | 3,
    MDLVertexFormatChar4Normalized = MDLVertexFormatCharNormalizedBits | 4,

    MDLVertexFormatUShort =  MDLVertexFormatUShortBits | 1,
    MDLVertexFormatUShort2 = MDLVertexFormatUShortBits | 2,
    MDLVertexFormatUShort3 = MDLVertexFormatUShortBits | 3,
    MDLVertexFormatUShort4 = MDLVertexFormatUShortBits | 4,

    MDLVertexFormatShort =  MDLVertexFormatShortBits | 1,
    MDLVertexFormatShort2 = MDLVertexFormatShortBits | 2,
    MDLVertexFormatShort3 = MDLVertexFormatShortBits | 3,
    MDLVertexFormatShort4 = MDLVertexFormatShortBits | 4,

    MDLVertexFormatUShortNormalized =  MDLVertexFormatUShortNormalizedBits | 1,
    MDLVertexFormatUShort2Normalized = MDLVertexFormatUShortNormalizedBits | 2,
    MDLVertexFormatUShort3Normalized = MDLVertexFormatUShortNormalizedBits | 3,
    MDLVertexFormatUShort4Normalized = MDLVertexFormatUShortNormalizedBits | 4,

    MDLVertexFormatShortNormalized =  MDLVertexFormatShortNormalizedBits | 1,
    MDLVertexFormatShort2Normalized = MDLVertexFormatShortNormalizedBits | 2,
    MDLVertexFormatShort3Normalized = MDLVertexFormatShortNormalizedBits | 3,
    MDLVertexFormatShort4Normalized = MDLVertexFormatShortNormalizedBits | 4,

    MDLVertexFormatUInt =  MDLVertexFormatUIntBits | 1,
    MDLVertexFormatUInt2 = MDLVertexFormatUIntBits | 2,
    MDLVertexFormatUInt3 = MDLVertexFormatUIntBits | 3,
    MDLVertexFormatUInt4 = MDLVertexFormatUIntBits | 4,

    MDLVertexFormatInt =  MDLVertexFormatIntBits | 1,
    MDLVertexFormatInt2 = MDLVertexFormatIntBits | 2,
    MDLVertexFormatInt3 = MDLVertexFormatIntBits | 3,
    MDLVertexFormatInt4 = MDLVertexFormatIntBits | 4,

    MDLVertexFormatHalf =  MDLVertexFormatHalfBits | 1,
    MDLVertexFormatHalf2 = MDLVertexFormatHalfBits | 2,
    MDLVertexFormatHalf3 = MDLVertexFormatHalfBits | 3,
    MDLVertexFormatHalf4 = MDLVertexFormatHalfBits | 4,

    MDLVertexFormatFloat =  MDLVertexFormatFloatBits | 1,
    MDLVertexFormatFloat2 = MDLVertexFormatFloatBits | 2,
    MDLVertexFormatFloat3 = MDLVertexFormatFloatBits | 3,
    MDLVertexFormatFloat4 = MDLVertexFormatFloatBits | 4,

    MDLVertexFormatInt1010102Normalized =  MDLVertexFormatIntBits  | MDLVertexFormatPackedBit | 4,
    MDLVertexFormatUInt1010102Normalized = MDLVertexFormatUIntBits | MDLVertexFormatPackedBit | 4
};




/*!
 @class MDLVertexBufferLayout
 @abstract Describes a vertex buffer's layout
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVertexBufferLayout : NSObject <NSCopying>

/*!
 @property stride
 @abstract stride in bytes of each vertex element of in the buffer
 */
@property (nonatomic, readwrite) NSUInteger stride;
@end





/*!
 @class MDLVertexAttribute
 @abstract Structure with properties of a vertex attribute
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVertexAttribute : NSObject <NSCopying>

/*!
 @method initWithName:format:offset:bufferIndex
 @abstract Initialize attribute object with all properties
 */
- (instancetype) initWithName:(NSString *)name
                               format:(MDLVertexFormat)format
                               offset:(NSUInteger)offset
                          bufferIndex:(NSUInteger)bufferIndex;
/*!
 @property name
 @abstract Identifying name of the attribute derived from model file, or one of 
           the predefined MDLVertexAttribute strings
 */
@property (nonatomic, copy) NSString *name;

/*!
 @property format
 @abstract Format (including number of components) of the attribute
 @discussion If the value is MDLVertexFormatInvalid.   Other values of this 
             object will be ignored when setting the MDLVertexDescriptor object 
             in a Mesh. The initial value is MDLVertexFormatInvalid.
 */
@property (nonatomic, readwrite) MDLVertexFormat format;

/*!
 @property offset
 @abstract offset in bytes of the attrbute in each element of the vertex buffer
 */
@property (nonatomic, readwrite)  NSUInteger offset;

/*!
 @property bufferIndex
 @abstract index of the buffer in mesh's vertexBuffer array in which this 
           attribute resides
 */
@property (nonatomic, readwrite) NSUInteger bufferIndex;

/*!
 @property initializationValue
 @abstract Value to initialize the attribute to in the vertex buffer if no values
 @discussion This values of this vector will be set in attribute in the vertex
 attribute if the attribute did not previously exist in the mesh when
 setting the MDLVertexDescriptor in the mesh.  Components of this
 vector will also be set in The initial value of initializationValue
 is (0, 0, 0, 1).
 */
@property (nonatomic, readwrite) vector_float4 initializationValue;

@end




/*!
 @class MDLVertexDescriptor
 @abstract Describes the layout of vertex buffers in MDLMesh objects
 @discussion 
 
 This object is a property of MDLMesh describing the current state of
 attributes and buffer layouts of the vertex buffers in the mesh. This must be 
 immutable otherwise even small changes could cause the buffers to be out of sync 
 with the layout described here.
 
 Designed to be very similar to MTLVertexDescriptor to ease creation of one from 
 the other
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLVertexDescriptor : NSObject <NSCopying>

/*!
 @method initVertexDescriptor:
 @abstract Initializes the object with values from supplied vertexDescriptor
 @discussion This performs a deep copy of all data in the supplied descriptor.
 */
-(instancetype) initWithVertexDescriptor:(MDLVertexDescriptor *)vertexDescriptor;

/*!
 @method attributeNamed:
 @abstract Retrieves the attribute with the given name
 @return The attribute with the supplied name or nil if attribute with the given 
         name does not exist in the descriptor object
 */
-(nullable MDLVertexAttribute *)attributeNamed:(NSString*)name;

/*!
 @method addOrReplaceAttribute:
 @abstract Replace any attribute with the same name, or add it if it does not
           already exist.
 */
- (void)addOrReplaceAttribute:(nonnull MDLVertexAttribute*)attribute;

/*! 
 @property attributes
 @abstract An array of MDLVertexAttribute objects
 @discussion An array describing the current attribute state of vertex buffers in an
             MDLMesh mesh
 */
@property (nonatomic, retain) NSMutableArray<MDLVertexAttribute*> *attributes;

/*!
 @property layouts
 @abstract An array of MDLVertexBufferLayout
 @discussion An array describing the current layout state of vertex buffers in an 
             MDLMesh mesh
 */
@property (nonatomic, retain) NSMutableArray<MDLVertexBufferLayout*> *layouts;

/*!
 @method reset
 @abstract Tesets the descriptor to initial values
 */
- (void)reset;

/*!
 @method setPackedStrides
 @abstract Sets the stride in each VertexBufferLout in the layouts array to the 
           minimum value encompassing all attributes in the vertex buffer
 */
- (void)setPackedStrides;

/*!
  @method setPackedOffsets
  @abstract Sets the stride in each VertexAttribute in the attributes array to 
            the minimum value to pack each attribute next to each other in its 
            vertexbuffer
  */
- (void)setPackedOffsets;

@end

NS_ASSUME_NONNULL_END
// ==========  ModelIO.framework/Headers/MDLTexture.h
/*!
 @header MDLTexture.h
 @framework ModelIO
 @abstract Representation of textures for use in rendering
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#pragma once

#import <Foundation/Foundation.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLObject.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreGraphics/CGImage.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN


@class NSURL;
@class NSString;

/**
 The enoding of texel channel elements
 */

typedef NS_ENUM(NSInteger, MDLTextureChannelEncoding) {
    MDLTextureChannelEncodingUInt8 = 1,
    MDLTextureChannelEncodingUint8 = 1,
    MDLTextureChannelEncodingUInt16 = 2,
    MDLTextureChannelEncodingUint16 = 2,
    MDLTextureChannelEncodingUInt24 = 3,
    MDLTextureChannelEncodingUint24 = 3,
    MDLTextureChannelEncodingUInt32 = 4,
    MDLTextureChannelEncodingUint32 = 4,
    MDLTextureChannelEncodingFloat16 = 0x102,
    MDLTextureChannelEncodingFloat32 = 0x104,
};

/**
 MDLTexture
 @summary a description of texels provided by a texture object.
 
 @discussion A texture optionally generates or loads texels
             through an access to the data property, or one of the other 
             properties, otherwise the texture object is a lightweight descriptor 
             only.
 
 @property data 
           Texel data that will exist when referenced; it may or may not exist 
           before
 @property dimensions
           texel width and height of the texture
 @property rowStride
           The number of bytes from the first texel in a row to the first texel 
           in the next row. A rowStride of zero indicates that interleaved x,y 
           addressing of texels is not possible. This might be the case if the
           texture was compressed in some manner, for example.
 @property channelCount
           The number of channels incoded in a single texel. For example, an RGB 
           texture has 3 channels. All channels must have the same encoding.
 @property channelEncoding
           The encoding of a channel in a single texel.
 @property isCube
           The texture encodes a cube map. If YES, then the layout of the cube 
           map is deduced as a vertical strip if dimension.y is six times 
           dimension.x. Other layouts are possible in the future.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLTexture : NSObject<MDLNamed>

/**
 Creates a texture from a source in the main bundle named in a manner matching
  name.
 */
+ (nullable instancetype)textureNamed:(NSString *)name;
+ (nullable instancetype)textureNamed:(NSString *)name bundle:(nullable NSBundle*)bundleOrNil;

/**
  Creates a cube texture map image using 6 faces of the same dimensions, 
  ordered +X,-X,+Y,-Y,+Z,-Z If the data is read back the image will be compacted 
  into a single vertical stack where dimensions.y = 6 * dimensions.x
  isCube will return YES
 
  @param names a collection of mosaiced images in a cross formation or column or row.
  - If 6 individual images are given they are assumed to be in order and will be 
    loaded as is.
  - if 3 images of double height or width are given they will be treated as 
    pairs of + and - in each axis, the order is must be x, then y, then z.
  - if 2 images of triple height or width are given they will be treates as a 
    positive set and a negative set in the order +x, +y, +z, then -x, -y, -z.
  - if a single image is given it will be used without conversion if in column 
    orientation and demosaiced in all other instances.
 */
+ (nullable instancetype)textureCubeWithImagesNamed:(NSArray<NSString *> *)names;
+ (nullable instancetype)textureCubeWithImagesNamed:(NSArray<NSString *> *)names bundle:(nullable NSBundle*)bundleOrNil;

+ (instancetype)irradianceTextureCubeWithTexture:(MDLTexture*)texture
                                            name:(nullable NSString*)name
                                      dimensions:(vector_int2)dimensions;

+ (instancetype)irradianceTextureCubeWithTexture:(MDLTexture*)texture
                                            name:(nullable NSString*)name
                                      dimensions:(vector_int2)dimensions
                                       roughness:(float)roughness;

- (instancetype)initWithData:(nullable NSData *)pixelData
               topLeftOrigin:(BOOL)topLeftOrigin
                        name:(nullable NSString*)name
                  dimensions:(vector_int2)dimensions
                   rowStride:(NSInteger)rowStride
                channelCount:(NSUInteger)channelCount
             channelEncoding:(MDLTextureChannelEncoding)channelEncoding
                      isCube:(BOOL)isCube NS_DESIGNATED_INITIALIZER;

/** writeToURL, deducing type from path extension */
- (BOOL)writeToURL:(NSURL *)URL;

/** writeToURL using a specific UT type */
- (BOOL)writeToURL:(NSURL *)nsurl type:(CFStringRef)type;

- (nullable CGImageRef)imageFromTexture;

- (nullable NSData *)texelDataWithTopLeftOrigin;
- (nullable NSData *)texelDataWithBottomLeftOrigin;

- (nullable NSData *)texelDataWithTopLeftOriginAtMipLevel:(NSInteger)level create:(BOOL)create;
- (nullable NSData *)texelDataWithBottomLeftOriginAtMipLevel:(NSInteger)level create:(BOOL)create;

@property (nonatomic, readonly) vector_int2 dimensions;
@property (nonatomic, readonly) NSInteger rowStride;
@property (nonatomic, readonly) NSUInteger channelCount;
@property (nonatomic, readonly) NSUInteger mipLevelCount;
@property (nonatomic, readonly) MDLTextureChannelEncoding channelEncoding;
@property (nonatomic) BOOL isCube;

@end

/** 
 MDLURLTexture
 @summary a texture provider initialized with a URL or file path.
 @discussion if any of the properties of the texture, such as data, are referenced,
             then the texture may be loaded, otherwise, the MDLURLTexture is merely
             a lightweight reference to something that could be loaded
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLURLTexture : MDLTexture

- (instancetype)initWithURL:(NSURL*)URL name:(nullable NSString*)name;

@property (nonatomic, copy) NSURL* URL;

@end

/** 
MDLCheckerboardTexture
 A two color checkboard with a certain number of divisions
 
 @discussion the texture will be created if data is referenced, otherwise, this
             object is merely a description
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLCheckerboardTexture : MDLTexture

- (instancetype)initWithDivisions:(float)divisions
                             name:(nullable NSString*)name
                       dimensions:(vector_int2)dimensions
                     channelCount:(int)channelCount
                  channelEncoding:(MDLTextureChannelEncoding)channelEncoding
                           color1:(CGColorRef)color1
                           color2:(CGColorRef)color2;

@property (nonatomic, assign) float divisions;
@property (nullable, nonatomic) CGColorRef color1;
@property (nullable, nonatomic) CGColorRef color2;

@end

/**
MDLSkyCubeTexture
 @summary A physically realistic sky as a cube texture
 
 @property sunElevation A value of zero is at the zenith, 0.5 is at the horizon,
           1.0 is at the nadir. Use in conjunction with turbidity to give a dawn, 
           dusk, or noon look.
 @property turbidity A value of zero simulates the effect of a clear sky, the sun
           will impart very little color to the sky. A value of one simulates a
           great deal of dust and moisture in the sky, and will cause the sun's
           color to spread across the atmosphere.
 @property upperAtmosphereScattering A value of zero will give very dusky colors,
           a value of one will give noon-ish saturated colors.
 @property groundAlbedo controls the amount of light that bounces back up into
           the sky from the ground. A value of zero will yield a clear sky, a
           value of one will reduce the contrast of the sky, making it a bit foggy.
 
 @property horizonElevation If the lower half of the environment is being replaced
           by a color, horizonElevation is angle, in radians, below which the
           replacement should occur. Negative values are below the horizon.

 @property groundColor If this value is set, the environment will be replaced with
           the color below the horizonElevation value.
 
 @property gamma Modifies the amount of gamma correction applied during
           tone mapping.
 @property exposure Modifies the exposure applied during tone mapping.
 @property brighness Modifies the brightness of the image during tone mapping.
 @property contrast Modifies the contrast of the image during tone mapping.
 @property saturation Modifes the saturation of the image during tone mapping.
 @property highDynamicRangeCompression values below the x component of this value 
           are not compressed during tone mapping. Values between the x component
           and y component are compressed to the maximum brightness value during
           tone mapping. Values above the limit are clamped.
 
 @discussion the texture will be created if data is referenced, otherwise, this
 object is merely a description. All parameters have legal values between zero and one.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLSkyCubeTexture : MDLTexture

- (instancetype)initWithName:(nullable NSString*)name
             channelEncoding:(MDLTextureChannelEncoding)channelEncoding
           textureDimensions:(vector_int2)textureDimensions   // the size of one cube face
                   turbidity:(float)turbidity                 // the clearness of the sky
                sunElevation:(float)sunElevation              // from 0 to 1 zenith to nadir
   upperAtmosphereScattering:(float)upperAtmosphereScattering // how intense the sun looks, 0 to 1
                groundAlbedo:(float)groundAlbedo;             // how much sky color is reflected from the Earth

/**
 Call updateTexture if parameters have been changed and a new sky is required.
 */
- (void)updateTexture;

@property (nonatomic, assign) float turbidity;
@property (nonatomic, assign) float sunElevation;
@property (nonatomic, assign) float upperAtmosphereScattering;
@property (nonatomic, assign) float groundAlbedo;

@property (nonatomic, assign) float horizonElevation;
@property (nullable, nonatomic) CGColorRef groundColor;

@property (nonatomic, assign) float gamma;
@property (nonatomic, assign) float exposure;
@property (nonatomic, assign) float brightness;
@property (nonatomic, assign) float contrast;
@property (nonatomic, assign) float saturation;
@property (nonatomic, assign) vector_float2 highDynamicRangeCompression;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLColorSwatchTexture : MDLTexture

/**
 Create a color gradient from one color temperature to another. The units are 
 blackbody temperatures. The gradient will be vertical.
 */

- (instancetype) initWithColorTemperatureGradientFrom:(float)colorTemperature1
                                   toColorTemperature:(float)colorTemperature2
                                                 name:(nullable NSString*)name
                                    textureDimensions:(vector_int2)textureDimensions;

/**
 Create a color gradient from one color to another. The color will interpolate 
 according to hue. The gradient will be vertical.
 */

- (instancetype) initWithColorGradientFrom:(CGColorRef)color1
                                   toColor:(CGColorRef)color2
                                      name:(nullable NSString*)name
                         textureDimensions:(vector_int2)textureDimensions;

@end


/**
 MDLNoiseTexture
 @summary a noise texture containing vector or scalar noise
 @discussion the texture will be created if data is referenced, otherwise, this
 object is merely a description
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLNoiseTexture : MDLTexture


/**
 Create a four channel texture containing directional noise. The RGBA values in this
 texture can be used as a normal map or as direction possibly with length. XYZ are a 
 three dimensional direction, and A is a magnitude.
 
 @param smoothness how similar neighboring pixels are. A value of zero is like static, 
 one is smooth.
 */
- (instancetype)initVectorNoiseWithSmoothness:(float)smoothness
                                         name:(nullable NSString*)name
                            textureDimensions:(vector_int2)textureDimensions
                              channelEncoding:(MDLTextureChannelEncoding)channelEncoding;

/**
 Create a texture containing colored noise. The noise texture is tileable with itself.
 
 @param smoothness how similar neighboring pixels are. A value of zero is like 
        static, one is smooth.
 @param grayscale if YES, RGB and A will all be the same. If no, RGB and A will 
        all be different. A is not pre-multiplied, because the intent is that if 
        you read a texel in a shader, all four values will be exactly the same 
        value if grayscale, or four different, uncorrelated values if not grayscale.
 */
- (instancetype)initScalarNoiseWithSmoothness:(float)smoothness
                                         name:(nullable NSString*)name
                            textureDimensions:(vector_int2)textureDimensions
                                 channelCount:(int)channelCount
                              channelEncoding:(MDLTextureChannelEncoding)channelEncoding
                                    grayscale:(BOOL)grayscale;


@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLNormalMapTexture : MDLTexture

- (instancetype)initByGeneratingNormalMapWithTexture:(MDLTexture*)sourceTexture
                                                name:(nullable NSString*)name
                                          smoothness:(float)smoothness
                                            contrast:(float)contrast;

@end

NS_ASSUME_NONNULL_END

