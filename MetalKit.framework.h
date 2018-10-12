// ==========  MetalKit.framework/Headers/MTKModel.h
/*!
 @header MTKModel.h
 @framework MetalKit
 @abstract MetalKit helper functionality for using Model I/O with Metal
 @discussion Provides utilities to efficiently load Model assets using Model I/O directly into metal buffers and textures.  Provides container structures for renderable meshes and submeshes.
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <MetalKit/MTKDefines.h>

#import <ModelIO/ModelIO.h>
#import <Metal/Metal.h>
#import <simd/simd.h>


/*!
 @group MTKModelErrors
 */
typedef NSString * MTKModelError NS_STRING_ENUM;

/*!
 @constant MTKModelErrorDomain
 */
MTK_EXTERN MTKModelError __nonnull const MTKModelErrorDomain NS_AVAILABLE(10_11, 9_0);
/*!
 @constant MTKModelErrorKey
 */
MTK_EXTERN MTKModelError __nonnull const MTKModelErrorKey NS_AVAILABLE(10_11, 9_0);


/*!
 @class MTKMeshBufferAllocator
 @abstract Allocator passed to MDLAsset init method to load vertex and index data directly into Metal buffers.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMeshBufferAllocator : NSObject<MDLMeshBufferAllocator>

/*!
 @method init
 @abstract Must initialize with device
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithDevice
 @abstract Initialize the allocator with a device to be used to create buffers.
 @discussion The designated initializer for this class.
 */
- (nonnull instancetype)initWithDevice:(nonnull id<MTLDevice>) device;

/*!
 @property device
 @abstract Device used to create buffers.
 */
@property (nonatomic, readonly, nonnull) id<MTLDevice> device;

@end

/*!
 @class MTKMeshBuffer
 @abstract Mesh buffer created by MTKMeshBufferAllocator when Model I/O needs to memory for vertex or index data backing.
 @discussion Memory backing these buffer are Metal buffers.  Model I/O will load index and vertex data from from a model asset directly in to the Metal buffer.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMeshBuffer : NSObject <MDLMeshBuffer, MDLNamed>

/*!
 @method init
 @abstract Only an MTKMeshBufferAllocator object can initilize a MTKMeshBuffer object
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @method length
 @abstract Size in bytes of the buffer allocation.
 */
@property (nonatomic, readonly) NSUInteger length;

/*!
 @property allocator
 @abstract Allocator object used to create this buffer.
 @discussion This allcoator is stored so that it can be used by Model I/O for copy and relayout operations (such as when a new vertex descriptor is applied to a vertex buffer).
 */
@property (nonatomic, readonly,  nonnull)  MTKMeshBufferAllocator *allocator;

/*!
 @property zone
 @abstract Zone from which this buffer was created (if it was created from a zone).
 @discussion A single MetalBuffer is allocated for each zone.  Each zone could have many MTKMeshBuffers, each with it's own offset.  If a MTKMeshBufferAllocator is used, Model I/O will attempt to load all vertex and index data of a single mesh into a single zone.  This allows the GPU to achieve a higher cache hit rate when drawing the mesh.  So although there maybe many MTKMeshBuffers for a model they will be backed with the same contigous MetalBuffer.
 */
@property (nonatomic, readonly, nullable)  id<MDLMeshBufferZone> zone;

/*!
 @property buffer
 @abstract Metal Buffer backing vertex/index data.
 @discussion Many MTKMeshBuffers may reference the same buffer, but each with it's own offset.  (i.e. Many MTKMeshBuffers may be suballocated from a single buffer)
 */
@property (nonatomic, readonly, nonnull) id<MTLBuffer> buffer;

/*!
 @property offset
 @abstract Byte offset of the data within the metal buffer.
 */
@property (nonatomic, readonly) NSUInteger offset;

/*!
 @property type
 @abstract the intended type of the buffer
 */
@property (nonatomic, readonly) MDLMeshBufferType type;

@end

@class MTKMesh;

/*!
 @class MTKSubmesh
 @abstract A segment of a mesh and properties to render the segement.
 @discussion Container for data that can be rendered in a single draw call. 1:1 mapping to MDLSubmesh.  Each submesh contains an index Buffer with which the parents mesh data can be rendered.  Actual vertex data resides in the submesh's parent MTKMesh object.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKSubmesh : NSObject

/*!
 @method init
 @abstract Applicatiohs must not explicity allocate or initialize.  Must initialize as part of MTKMesh object.
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @property primitiveType
 @abstract Metal primitive type with which to draw this object.
 @discussion Value to use for primitiveType parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.
 */
@property (nonatomic, readonly) MTLPrimitiveType primitiveType;

/*!
 @property indexType
 @abstract Metal index type of data in indexBuffer.
 @discussion Value to use for indexType parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.

 */
@property (nonatomic, readonly) MTLIndexType indexType;

/*!
 @property indexBuffer
 @abstract IndexBuffer (including indexCount) to render the object.
 @discussion The MTLBuffer to use for indexBuffer parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.
 */
@property (nonatomic, readonly, nonnull) MTKMeshBuffer *indexBuffer;

/*!
 @property indexCount
 @abstract Number of indicies in indexBuffer.
 @discussion Value to use for indexCount parameter in a [MTLRenderCommandEncoder drawIndexedPrimitives] call.

 */
@property (nonatomic, readonly) NSUInteger indexCount;

/*!
 @property mesh
 @abstract Parent MTKMesh object containing vertex data of this object.
 @discussion The buffer of this parent mesh should be set in the encoder before a drawIndexedPrimitives call is made.
 */
@property (nonatomic, readonly, weak, nullable) MTKMesh *mesh;


/*!
 @property name
 @abstract Name from the original MDLSubmesh object.
 @discussion Although not directly used by this object, the application may use this to identify the submesh in the renderer/scene/world.
 */
@property (nonatomic, copy, nonnull) NSString *name;

@end

/*!
 @class MTKMesh
 @abstract Container for vertex data of a mesh and submeshes to render it.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKMesh : NSObject

/*!
 @method init
 @abstract Cannot use default init.  Must initialize with mesh and metal device.
 */
- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithMesh:device:error:
 @abstract Initialize the mesh and the mesh's submeshes.
 @param mesh Model I/O Mesh from which to create this MetalKit mesh
 @param device Metal device on which to create mesh resources
 @param error Pointer to an NSError object set if an error occurred
 @discussion The designated initializer for this class.  This does NOT initialize any meshes that are children of the Model I/O mesh, only submeshes that are part of the given mesh.  An exception is raised if vertexBuffer objects in the given mesh and the indexBuffer of any submesh in this mesh have not been created with a MTKMeshBufferAllocator object.  If a submesh using MDLGeometryTypeQuads or MDLGeometryTypeTopology is used, that submesh will be copied, and recreated to use MDLGeometryTypeTriangles, before this routine creates the MTKSubmesh.
 */
- (nullable instancetype)initWithMesh:(nonnull MDLMesh *)mesh
                               device:(nonnull id<MTLDevice>)device
                                error:(NSError * __nullable * __nullable)error;

/*!
 @method newMeshesFromAsset:device:sourceMeshes:error:
 @abstract Initialize all meshes in a Model I/O asset.
 @param asset Model I/O asset from which to create MetalKit meshes
 @param device Metal device on which to create mesh resources
 @param sourceMeshes Array built by this method containing MDLMesh objects corresponding the returned MTKMesh objects
 @param error Pointer to an NSError object set if an error occurred
 @return MetalKit Meshes created from the Model I/O asset
 @discussion A convenience method to create MetalKit meshes from each mesh in a Model I/O asset.  resulting meshes are returned while the corresponding Model I/O meshes from which they were generated will appear in the sourceMeshes array.  All vertexBuffer objects in each MDLMesh object in the asset and the indexBuffer of each submesh within each of these meshes must have been created using a MTKMeshBufferAllocator object.  Thus 
 */
+ (nullable NSArray<MTKMesh*>*)newMeshesFromAsset:(nonnull MDLAsset *)asset
                                           device:(nonnull id<MTLDevice>)device
                                     sourceMeshes:(NSArray<MDLMesh*>* __nullable * __nullable)sourceMeshes
                                            error:(NSError * __nullable * __nullable)error;

/*!
 @property vertexBuffers
 @abstract Array of buffers in which mesh vertex data resides.
 @discussion This is filled with mesh buffer objects using the layout described by the vertexDescriptor property.  Elements in this array can be [NSNull null] if the vertexDescriptor does not specify elements for buffer for the given index
 */
@property (nonatomic, readonly, nonnull) NSArray<MTKMeshBuffer *> *vertexBuffers;

/*!
 @property vertexDescriptor
 @abstract Model I/O vertex descriptor specifying the layout of data in vertexBuffers.
 @discussion This is not directly used by this object, but the application can use this information to determine rendering state or create a Metal vertex descriptor to build a RenderPipelineState object capable of interpreting data in 'vertexBuffers'.  Changing propties in the object will not result in the relayout data in vertex descriptor and thus will make the vertex descriptor no loger describe the layout of vertes data and verticies. (i.e. don't change properties in this vertexDescriptor)
 */
@property (nonatomic, readonly, nonnull) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property submeshes
 @abstract Submeshes containing index buffers to rendering mesh vertices.
 */
@property (nonatomic, readonly, nonnull) NSArray<MTKSubmesh *> *submeshes;

/*!
 @property vertexCount
 @abstract Number of vertices in the vertexBuffers.
 */
@property (nonatomic, readonly) NSUInteger vertexCount;

/*!
 @property name
 @abstract Name of the mesh copies from the originating Model I/O mesh.
 @discussion Can be used by the app to identify the mesh in its scene/world/renderer etc.
 */
@property (nonatomic, copy, nonnull) NSString *name;

@end


/*!
 @group MTKModelFunctions
 */


/*!
 @function MTKModelIOVertexDescriptorFromMetal
 @abstract Partially converts a Metal vertex descriptor to a Model I/O vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced Model I/O vertex descriptor.  It does not add any semantic information such at attributes names.  Names must be set in the returned Model I/O vertex descriptor before it can be applied to a a Model I/O mesh.
 */
MTK_EXTERN MDLVertexDescriptor* __nonnull MTKModelIOVertexDescriptorFromMetal(MTLVertexDescriptor* __nonnull metalDescriptor) NS_AVAILABLE(10_11, 9_0);

/*!
 @function MTKModelIOVertexDescriptorFromMetalWithError
 @abstract Partially converts a Metal vertex descriptor to a Model I/O vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced Model I/O vertex descriptor.  It does not add any semantic information such at attributes names.  Names must be set in the returned Model I/O vertex descriptor before it can be applied to a a Model I/O mesh. If error is nonnull, and the conversion cannot be made, it will be set.
 */
MTK_EXTERN MDLVertexDescriptor* __nonnull MTKModelIOVertexDescriptorFromMetalWithError(MTLVertexDescriptor* __nonnull metalDescriptor, NSError * __nullable * __nullable error) NS_AVAILABLE(10_12, 10_0);

/*!
 @function MTKMetalVertexDescriptorFromModelIO
 @abstract Partially converts a Model I/O vertex descriptor to a Metal vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced Metal vertex descriptor. It simply copies attributes 1 for 1. Thus attributes in the given Model I/O vertex descriptor must be arranged in the correct order for the resulting descriptor to properly map mesh data to vertex shader inputs.  Layout stepFunction and stepRates for the resulting MTLVertexDescriptor must also be set by application.
 */
MTK_EXTERN MTLVertexDescriptor* __nullable MTKMetalVertexDescriptorFromModelIO(MDLVertexDescriptor* __nonnull modelIODescriptor) NS_AVAILABLE(10_11, 9_0);

/*!
 @function MTKMetalVertexDescriptorFromModelIOWithError
 @abstract Partially converts a Model I/O vertex descriptor to a Metal vertex descriptor
 @discussion This method can only set vertex format, offset, bufferIndex, and stride information in the produced Metal vertex descriptor. It simply copies attributes 1 for 1. Thus attributes in the given Model I/O vertex descriptor must be arranged in the correct order for the resulting descriptor to properly map mesh data to vertex shader inputs.  Layout stepFunction and stepRates for the resulting MTLVertexDescriptor must also be set by application.  If error is nonnull, and the conversion cannot be made, it will be set.
 */
MTK_EXTERN MTLVertexDescriptor* __nullable MTKMetalVertexDescriptorFromModelIOWithError(MDLVertexDescriptor* __nonnull modelIODescriptor, NSError * __nullable * __nullable error) NS_AVAILABLE(10_12, 10_0);

/*!
 @function MTKModelIOVertexFormatFromMetal
 @abstract Converts a Metal vertex format to a Model I/O vertex format
 @return A Model I/O vertexformat correspoinding to the given Metal vertex format.  Returns MDLVertexFormatInvalid if no matching Model I/O vertex format exists.
 */
MTK_EXTERN MDLVertexFormat MTKModelIOVertexFormatFromMetal(MTLVertexFormat vertexFormat) NS_AVAILABLE(10_11, 9_0);

/*!
@function MTKMetalVertexFormatFromModelIO
@abstract Converts a Model I/O vertex format to a Metal vertex format
@return A Metal vertexformat correspoinding to the given Model I/O vertex format.  Returns MTLVertexFormatInvalid if no matching Metal vertex format exists.
*/
MTK_EXTERN MTLVertexFormat MTKMetalVertexFormatFromModelIO(MDLVertexFormat vertexFormat) NS_AVAILABLE(10_11, 9_0);

// ==========  MetalKit.framework/Headers/MTKView.h
/*!
 @header MTKView.h
 @framework MetalKit
 @abstract MetalKit helper functionality for creating a view
 @discussion This view class provides functionality to setup metal drawable textures for common rendering scenarios
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <MetalKit/MTKDefines.h>

#import <UIKit/UIKit.h>

#import <QuartzCore/CAMetalLayer.h>

#import <Metal/Metal.h>

@protocol MTKViewDelegate;

/*!
 @class MTKView
 @abstract View for rendering metal content
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKView : UIView <NSCoding,CALayerDelegate>

/*!
 @method initWithFrame:device
 @abstract Initalize the view with a frame and device
 @param frameRect The frame rectangle for the created view object.
 @param device The MTLDevice to be used by the view to create Metal objects
 */
- (nonnull instancetype)initWithFrame:(CGRect)frameRect device:(nullable id<MTLDevice>)device NS_DESIGNATED_INITIALIZER;

/*!
 @method initWithCoder:
 @abstract Returns a view initalized from data in a given unarchiver
 @param coder An unarchiver object
 */
- (nonnull instancetype)initWithCoder:(nonnull NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/*!
 @property delegate
 @abstract The delegate handling common view operations
 */
@property (nonatomic, weak, nullable) id <MTKViewDelegate> delegate;

/*!
 @property device
 @abstract The MTLDevice used to create Metal objects
 @discussion This must be explicitly set by the application unless it was passed into the initializer. Defaults to nil
  */
@property (nonatomic, nullable) id <MTLDevice> device;

/*!
 @property currentDrawable
 @abstract The drawable to be used for the current frame.
 @discussion currentDrawable is updated at the end -draw (i.e. after the delegate's drawInMTKView method is called)
 */
@property (nonatomic, readonly, nullable) id <CAMetalDrawable> currentDrawable;

/*!
 @property framebufferOnly
 @abstract If the currentDrawable can be used for sampling or texture read operations
 @discussion This defaults to YES. This property controls whether or not the returned drawables' MTLTextures may only be used for framebuffer attachments (YES) or whether they may also be used for texture sampling and pixel read/write operations (NO). A value of YES allows the CAMetalLayer to allocate the MTLTexture objects in ways that are optimized for display purposes that makes them unsuitable for sampling. The recommended value for most applications is YES.
 */
@property (nonatomic) BOOL framebufferOnly;

/*!
 @property presentsWithTransaction
 @abstract If the layer should be presented synchronously
 @discussion Defaults to NO. When NO, changes to the layer's render buffer appear on-screen asynchronously to normal layer updates. When YES, changes to the MTL content are sent to the screen via the standard CATransaction mechanisms.
*/
@property (nonatomic) BOOL presentsWithTransaction;

/*!
 @property colorPixelFormat
 @abstract The pixelFormat for the drawable's texture.
 */
@property (nonatomic) MTLPixelFormat colorPixelFormat;

/*!
 @property depthStencilPixelFormat
 @abstract The pixelFormat used to create depthStencilTexture
 */
@property (nonatomic) MTLPixelFormat depthStencilPixelFormat;

/*!
 @property sampleCount
 @abstract The sample count used to to create multisampleColorTexture
 @discussion This defaults to 1.  If sampleCount is greater than 1 a multisampled color texture will be created and the currentDrawable's texture will be set as the resolve texture in the currentRenderPassDescriptor and the store action will be set to MTLStoreActionMultisampleResolve
 */
@property (nonatomic) NSUInteger sampleCount;

/*!
 @property clearColor
 @abstract The clear color value used to generate the currentRenderPassDescriptor
 @discussion This defaults to (0.0, 0.0, 0.0, 1.0)
 */
@property (nonatomic) MTLClearColor clearColor;

/*!
 @property clearDepth
 @abstract The clear depth value used to generate the currentRenderPassDescriptor
 @discussion This defaults to 1.0
 */
@property (nonatomic) double clearDepth;

/*!
 @property clearStencil
 @abstract The clear stencil value used to generate currentRenderPassDescriptor
 @discussion This defaults to 0
 */
@property (nonatomic) uint32_t clearStencil;

/*!
 @property depthStencilTexture
 @abstract A packed depth and stencil texture to be attached to a MTLRenderPassDescriptor
 @discussion The view will generate the depth buffer using the specified depthPixelFormat.  This will be nil if depthStencilPixelFormat is MTLPixelFormatInvalid.
 */
@property (nonatomic, readonly, nullable) id <MTLTexture> depthStencilTexture;

/*!
 @property multisampleColorTexture
 @abstract A multisample color texture that will be resolved into the currentDrawable's texture
 @discussion The view will generate the multisample color buffer using the specified colorPixelFormat.  This will be nil if sampleCount is less than or equal to 1.
 */
@property (nonatomic, readonly, nullable) id <MTLTexture> multisampleColorTexture;

/*!
 @method releaseDrawables
 @abstract Release the depthStencilTexture and multisampleColorTexture
 @discussion Can be called by the app to release the textures in order to conserve memory when it goes into the background.   The view will recreate multisampleColorTexture or depthStencilTexture upon the next access of the respective properties.  Both multisampleColorTexture and depthStencilTexture will be recreated in the access to currentRenderPassDescriptor.
 */
- (void)releaseDrawables;

/*!
 @property currentRenderPassDescriptor
 @abstract A render pass descriptor generated from the currentDrawable's texture and the view's depth, stencil, and sample buffers and clear values.
 @discussion This is a convience property.  The view does not use this descriptor and there is no requirement for an app to use this descriptor.
 */
@property (nonatomic, readonly, nullable) MTLRenderPassDescriptor *currentRenderPassDescriptor;

/*!
 @property preferredFramesPerSecond
 @abstract The rate you want the view to redraw its contents.
 @discussion When your application sets its preferred frame rate, the view chooses a frame rate as close to that as possible based on the capabilities of the screen the view is displayed on. The actual frame rate chosen is usually a factor of the maximum refresh rate of the screen to provide a consistent frame rate. For example, if the maximum refresh rate of the screen is 60 frames per second, that is also the highest frame rate the view sets as the actual frame rate. However, if you ask for a lower frame rate, it might choose 30, 20, 15 or some other factor to be the actual frame rate. Your application should choose a frame rate that it can consistently maintain. The default value is 60 frames per second.
 */
@property(nonatomic) NSInteger preferredFramesPerSecond;

/*!
  @property enableSetNeedsDisplay
  @abstract Controls whether the view responds to setNeedsDisplay.
  @discussion If true, then the view behaves similarily to a UIView or NSView, responding to calls to setNeedsDisplay. When the view has been marked for display, the view is automatically redisplayed on each pass through the application’s event loop. Setting enableSetNeedsDisplay to true will also pause the MTKView's internal render loop and updates will instead be event driven. The default value is false.
 */
@property (nonatomic) BOOL enableSetNeedsDisplay;

/*!
 @property autoResizeDrawable
 @abstract Controls whether to resize the drawable as the view changes size.
 @discussion If true, the size of the currentDrawable's texture, depthStencilTexture, and multisampleColorTexture will automatically resize as the view resizes.  If false, these textures will take on the size of drawableSize and drawableSize will not change. The default value is true.
 */
@property (nonatomic) BOOL autoResizeDrawable;

/*!
 @property drawableSize
 @abstract The current size of drawable textures
 @discussion The size currentDrawable's texture, depthStencilTexture, and multisampleColorTexture.  If autoResizeDrawable is true this value will be updated as the view's size changes. If autoResizeDrawable is false, this can be set to fix the size of the drawable textures.
 */
@property (nonatomic) CGSize drawableSize;

/*!
 @property paused
 @abstract Controls whether the draw methods should countinue at preferredFramesPerSecond
 @discussion If true, the delegate will receive drawInMTKView: messages or the subclass will receive drawRect: messages at a rate of preferredFramesPerSecond based on an internal timer. The default value is false.
 */
@property (nonatomic, getter=isPaused) BOOL paused;

/*!
 @property colorspace
 @abstract The colorspace of the rendered frames. '
 @discussion If nil, no colormatching occurs.  If non-nil, the rendered content will be colormatched to the colorspace of the context containing this layer (typically the display's colorspace).  This property aliases the olorspace property or the view's CAMetalLayer
 */
@property (nonatomic, nullable) CGColorSpaceRef colorspace NS_AVAILABLE_MAC(10_12);

/*!
 @method draw
 @abstract Manually ask the view to draw new contents. This causes the view to call either the drawInMTKView (delegate) or drawRect (subclass) method.
 @discussion Manually ask the view to draw new contents. This causes the view to call either the drawInMTKView (delegate) or drawRect (subclass) method. This should be used when the view's paused proprety is set to true and enableSetNeedsDisplay is set to false.
 */
- (void)draw;

@end

/*!
 @class MTKViewDelegate
 @abstract Allows an object to render into the view and respond to resize events
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MTKViewDelegate <NSObject>

/*!
 @method mtkView:drawableSizeWillChange:
 @abstract Called whenever the drawableSize of the view will change
 @discussion Delegate can recompute view and projection matricies or regenerate any buffers to be compatible with the new view size or resolution
 @param view MTKView which called this method
 @param size New drawable size in pixels
 */
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size;

/*!
 @method drawInMTKView:
 @abstract Called on the delegate when it is asked to render into the view
 @discussion Called on the delegate when it is asked to render into the view
 */
- (void)drawInMTKView:(nonnull MTKView *)view;

@end
// ==========  MetalKit.framework/Headers/MTKTextureLoader.h
/*!
 @header MTKTextureLoader.h
 @framework MetalKit
 @abstract MetalKit helper functionality for loading a Metal texture from image file data
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */
#import <TargetConditionals.h>
#import <MetalKit/MTKDefines.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>



@protocol MTLDevice;
@protocol MTLTexture;
@class MDLTexture;

/*!
 @group MTKTextureLoaderErrors
 */

typedef NSString * MTKTextureLoaderError NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.Error);

/*!
 @constant MTKTextureLoaderErrorDomain
 */
MTK_EXTERN MTKTextureLoaderError __nonnull const MTKTextureLoaderErrorDomain NS_AVAILABLE(10_11, 9_0);
/*!
 @constant MTKTextureLoaderErrorKey
 */
MTK_EXTERN MTKTextureLoaderError __nonnull const MTKTextureLoaderErrorKey NS_AVAILABLE(10_11, 9_0);

/*!
 @group MTKTextureLoaderOptions
 */

typedef NSString * MTKTextureLoaderOption NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.Option);

/*!
 @constant MTKTextureLoaderOptionAllocateMipmaps
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to allocate memory for mipmaps when creating the texture
 @discussion If the boolean value specified with this string is true, the resulting Metal texture will have been created with mipmaps whose contents are undefined. It is the responsibility of the caller to fill out the contents of the mipmap data unless MTLTextureLoaderOptionGenerateMipmaps is specified. If the file being loaded contains data for mipmaps (such as in a PVR or KTX file) this option does not need to be specified. In those cases the mipmap memory will be allocated and the image data loaded.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionAllocateMipmaps NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionGenerateMipmaps
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to generate mipmaps when creating the texture
 @discussion If the boolean value specified with this string is true, the resulting Metal texture will be created with mipmaps. If the file being loaded contains data for mipmaps (such as in a PVR or KTX file), specifying this option will overwrite the existing mipmap data in the loaded texture. This option can only be used if the pixel format of the texture is color filterable and color renderable. This option implies MTKTextureLoaderOptionAllocateMipmaps. Specifying this option will cause the MTKTextureLoader to submit work to the GPU on behalf of the caller.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionGenerateMipmaps NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOptionSRGB
 @abstract Identifier to be used in an options NSDictionary with a boolean NSNumber specifying whether to create the texture with an sRGB (gamma corrected) pixel format
 @discussion If the boolean value specified with this string is true, the texture will be created with an sRGB pixel format regardless of whether the image file specifies that the data has already been gamma corrected. Likewise, if false, the texture will be created with a non-sRGB pixel format regardless of whether the image file specifies that the data has been gamma corrected. To use the sRGB information specified in the file, do not specify this in the options dictionary.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionSRGB NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionTextureUsage
 @abstract Identifier to be used with an NSNumber specifying the MTLTextureUsage flags
 @discussion The resulting Metal texture will be created with the MTLTextureUsage flags indicated by the NSNumber associated with this string.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionTextureUsage NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionTextureCPUCacheMode
 @abstract Identifier to be used with an NSNumber specifying the MTLCPUCacheMode
 @discussion The resulting Metal texture will be created with the MTLCPUCacheMode indicated by the NSNumber associated with this string.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionTextureCPUCacheMode NS_AVAILABLE(10_11, 9_0);

/*!
 @constant MTKTextureLoaderOptionTextureStorageMode
 @abstract Identifier to be used with an NSNumber specifying the MTLStorageMode
 @discussion The resulting Metal texture will be created with the MTLStorageMode indicated by the NSNumber associated with this string. If this option is omitted, the texture will be created with the default storage mode for Metal textures: MTLStorageModeShared on iOS, and MTLStorageModeManaged on OS X. Specifying this option with MTLTextureStorageModePrivate cause the MTKTextureLoader to submit work to the GPU on behalf of the caller.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionTextureStorageMode NS_AVAILABLE(10_12, 10_0);


typedef NSString * MTKTextureLoaderCubeLayout NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.CubeLayout);

/*!
 * @constant MTKTextureLoaderOptionCubeLayout
 * @abstract Identifier to be used in an options NSDictionary with an MTKTextureLoaderCubeLayout NSString specifying whether to create a cubemap from a 2D image
 * @discussion The NSString value specified with this string must be one option of MTKTextureLoaderCubeLayout. If this option is omitted, the texture loader will not create cubemaps from 2D textures. This option cannot be used with PVR files, KTX files, or MDLTextures, which support cube textures directly.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionCubeLayout NS_AVAILABLE(10_12, 10_0);

/*!
 * @constant MTKTextureLoaderCubeLayoutVertical
 * @abstract Identifier specifying that the texture loader will create a cube texture from six faces arranged vertically within a single 2D image
 * @discussion A texture cube will be created from six faces arranged vertically within a single 2D image. The image height must be six times the image width, with faces arranged in the following order from top to bottom: +X, -X, +Y, -Y, +Z, -Z.
 */
MTK_EXTERN MTKTextureLoaderCubeLayout __nonnull const MTKTextureLoaderCubeLayoutVertical NS_AVAILABLE(10_12, 10_0);

typedef NSString * MTKTextureLoaderOrigin NS_STRING_ENUM NS_SWIFT_NAME(MTKTextureLoader.Origin);

/*!
 * @constant MTKTextureLoaderOptionOrigin
 * @abstract Identifier to be used in an options NSDictionary with an MTKTextureLoaderOrigin NSString specifying whether to flip textures vertically
 * @discussion The NSString value specified with this string must be one option of MTKTextureLoaderOrigin. If this option is omitted, the texture loader will not flip loaded textures. This option cannot be used with block-compressed texture formats, and can only be used with 2D, 2D array, and cube map textures. Each mipmap level and slice of a texture will be flipped.
 */
MTK_EXTERN MTKTextureLoaderOption __nonnull const MTKTextureLoaderOptionOrigin NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOriginTopLeft
 @abstract Identifier specifying that the texture loader should flip textures whose origin is in the bottom-left corner
 @discussion The texture will be flipped vertically if metadata in the file being loaded indicates that the source data starts with the bottom-left corner of the texture.
 */
MTK_EXTERN MTKTextureLoaderOrigin __nonnull const MTKTextureLoaderOriginTopLeft NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOriginBottomLeft
 @abstract Identifier specifying that the texture loader should flip textures whose origin is in the top-left corner
 @discussion The texture will be flipped vertically if metadata in the file being loaded indicates that the source data starts with the top-left corner of the texture.
 */
MTK_EXTERN MTKTextureLoaderOrigin __nonnull const MTKTextureLoaderOriginBottomLeft NS_AVAILABLE(10_12, 10_0);

/*!
 @constant MTKTextureLoaderOriginFlippedVertically
 @abstract Identifier specifying that the texture loader should always flip textures
 @discussion The texture will be flipped vertically regardless of any metadata in the file indicating the placement of the origin in the source data
 */
MTK_EXTERN MTKTextureLoaderOrigin __nonnull const MTKTextureLoaderOriginFlippedVertically NS_AVAILABLE(10_12, 10_0);

typedef void (^MTKTextureLoaderCallback) (id <MTLTexture> __nullable texture, NSError * __nullable error) NS_SWIFT_NAME(MTKTextureLoader.Callback);

typedef void (^MTKTextureLoaderArrayCallback) (NSArray<id <MTLTexture>> * __nonnull textures, NSError * __nullable error) NS_SWIFT_NAME(MTKTextureLoader.ArrayCallback) NS_AVAILABLE(10_12, 10_0);

/*!
 @class MTKTextureLoader
 @abstract Load Metal textures from files with the device specified at initialization
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKTextureLoader : NSObject

/*!
 @property device
 @abstract Metal device with which to create Metal textures
 */
@property (nonatomic, readonly, nonnull) id <MTLDevice> device;

- (nonnull instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithDevice:
 @abstract Initialize the loader
 @param device Metal device with which to create Metal textures
 */
- (nonnull instancetype)initWithDevice:(nonnull id <MTLDevice>)device;

/*!
 @method newTextureWithContentsOfURL:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the file at URL
 @param URL Location of image file from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when the texture has been loaded and fully initialized
 */
- (void)newTextureWithContentsOfURL:(nonnull NSURL *)URL
                            options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                  completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method newTextureWithName:scaleFactor:bundle:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from a given texture or image 
           asset name
 @param name A texture or image asset name
 @param scaleFactor scale factor of the texture to retrieve from the asset catalog.  Typically the 
                    value retrieved from -[UIView contentScale] or -[NSWindow backingScaleFactor].
 @param bundle Resource bundle in which the asset is located.  Main bundle used if nil.
 @param options Dictonary of MTKTextureLoaderOptions. The following options are ignormed when used
                to load a texture asset but can be used when creating a texture from an image asset:
                    MTKTextureLoaderOptionGenerateMipmaps
                    MTKTextureLoaderOptionSRGB
                    MTKTextureLoaderOptionCubeFromVerticalTexture
                    MTKTextureLoaderOptionOrigin
 @param completionHandler Block called when texture has been loaded and fully initialized
 @discussion Uses texture data from version of the texture from the texture set in the asset catalog
             which mathces the device's traits.
             This method attempts to load a texture asset with thw name iven.  If a texture asset
             with the name given does not exist, it will attempt to create a texture from an
             image asset with the given name
 */
- (void)newTextureWithName:(nonnull NSString *)name
               scaleFactor:(CGFloat)scaleFactor
                    bundle:(nullable NSBundle *)bundle
                   options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
         completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler NS_AVAILABLE(10_12, 10_0);


/*!
 @method newTexturesWithContentsOfURLs:options:completionHandler:
 @abstract Asynchronously create an array of Metal textures and load image data from the files at URLs
 @param URLs Locations of image files from which to create the textures
 @param options Dictonary of MTKTextureLoaderOptions, which will be used for every texture loaded
 @param completionHandler Block called when all of the textures have been loaded and fully initialized. The array of MTLTextures will be the same length and in the same order as the requested array of paths. If an error occurs while loading a texture, the corresponding array index will contain NSNull. The NSError will be null if all of the textures are loaded successfully, or will correspond to one of the textures which failed to load.
 */
- (void)newTexturesWithContentsOfURLs:(nonnull NSArray<NSURL *> *)URLs
                              options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                    completionHandler:(nonnull MTKTextureLoaderArrayCallback)completionHandler NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTexturesWithNames:scaleFactor:bundle:options:completionHandler:
 @abstract Asynchronously create Metal textures and load image data from a given texture or image
           asset names
 @param names An array texture or image asset names.  If an error occurs while loading a texture,
              the corresponding index in the returned array contain [NSNull null]
 @param scaleFactor scale factor of the texture to retrieve from the asset catalog.  Typically the
                    value retrieved from -[UIView contentScale] or -[NSWindow backingScaleFactor].
 @param bundle Resource bundle in which the assets are located.  Main bundle used if nil.
 @param options Dictonary of MTKTextureLoaderOptions. The following options are ignormed when used
                to load a texture asset but can be used when creating a texture from an image asset
                    MTKTextureLoaderOptionGenerateMipmaps
                    MTKTextureLoaderOptionSRGB
                    MTKTextureLoaderOptionCubeFromVerticalTexture
                    MTKTextureLoaderOptionOrigin
 @param completionHandler Block called when all of the textures have been loaded and fully
                          initialized. The NSError will be null if all of the textures are loaded
                          successfully, or will correspond to one of the textures which failed to
                          load.
 @discussion Uses texture data from version of the texture from the texture set in the asset catalog
             which mathces the device's traits.
             This method attempts to load a texture asset with each name iven.  If a texture asset
             with the name given does not exist, it will attempt to create a texture from an
             image asset with the given name.
 */
- (void)newTexturesWithNames:(nonnull NSArray<NSString *> *)names
                 scaleFactor:(CGFloat)scaleFactor
                      bundle:(nullable NSBundle *)bundle
                     options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
           completionHandler:(nonnull MTKTextureLoaderArrayCallback)completionHandler NS_AVAILABLE(10_12, 10_0);


/*!
 @method newTextureWithData:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the NSData object provided
 @param data NSData object containing image file data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)newTextureWithData:(nonnull NSData *)data
                   options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
         completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method newTextureWithCGImage:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the given CGImageRef
 @param cgImage CGImageRef containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)newTextureWithCGImage:(nonnull CGImageRef)cgImage
                      options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
            completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler;

/*!
 @method newTextureWithMDLTexture:options:completionHandler:
 @abstract Asynchronously create a Metal texture and load image data from the given MDLTexture
 @param texture MDLTexture containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param completionHandler Block called when texture has been loaded and fully initialized
 */
- (void)newTextureWithMDLTexture:(nonnull MDLTexture *)texture
                         options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
               completionHandler:(nonnull MTKTextureLoaderCallback)completionHandler NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTextureWithContentsOfURL:options:error:
 @abstract Synchronously create a Metal texture and load image data from the file at URL
 @return The Metal texture. nil if an error occured
 @param URL Location of image file from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithContentsOfURL:(nonnull NSURL *)URL
                                                options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                                  error:(NSError *__nullable *__nullable)error;

/*!
 @method newTexturesWithContentsOfURLs:options:completionHandler:
 @abstract Synchronously create an array of Metal textures and load image data from the files at URLs
 @return An array of MTLTextures of the same length and in the same order as the requested array of
         paths.  If an error occurs while loading a texture, the corresponding array index will
         contain [NSNull null].
 @param URLs Locations of image files from which to create the textures
 @param options Dictonary of MTKTextureLoaderOptions, which will be used for every texture loaded
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred.
              Will be null if all of the textures are loaded successfully, or will correspond to
              one of the textures which failed to load.
 */
- (NSArray <id <MTLTexture>> * __nonnull)newTexturesWithContentsOfURLs:(nonnull NSArray <NSURL *> *)URLs
                                                               options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                                                 error:(NSError *__nullable *__nullable)error NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTextureWithData:options:error:
 @abstract Synchronously create a Metal texture and load image data from the NSData object provided
 @return The Metal texture. nil if an error occured
 @param data NSData object containing image file data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithData:(nonnull NSData *)data
                                       options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                         error:(NSError *__nullable *__nullable)error;

/*!
 @method newTextureWithCGImage:options:error:
 @abstract Synchronously create a Metal texture and load image data from the given CGImageRef
 @return The Metal texture. nil if an error occured
 @param cgImage CGImageRef containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithCGImage:(nonnull CGImageRef)cgImage
                                          options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                            error:(NSError *__nullable *__nullable)error;

/*!
 @method newTextureWithMDLTexture:options:error:
 @abstract Synchronously create a Metal texture and load image data from the given MDLTexture
 @return The Metal texture. nil if an error occured
 @param texture MDLTexture containing image data from which to create the texture
 @param options Dictonary of MTKTextureLoaderOptions
 @param error Pointer to an autoreleased NSError object which will be set if an error occurred
 */
- (nullable id <MTLTexture>)newTextureWithMDLTexture:(nonnull MDLTexture *)texture
                                             options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                               error:(NSError *__nullable *__nullable)error NS_AVAILABLE(10_12, 10_0);

/*!
 @method newTextursWithName:scaleFactor:bundle:options:error:
 @abstract Synchronously create a Metal texture with texture data from a given texture or image 
           asset name
 @return The Metal texture. nil if an error occured
 @param names An array of texture asset names
 @param scaleFactor scale factor of the texture to retrieve from the asset catalog.  Typically the
                    value retrieved from -[UIView contentScale] or -[NSWindow backingScaleFactor].
 @param bundle Resource bundle in which the asset is located.  Main bundle used if nil.
 @param options Dictonary of MTKTextureLoaderOptions. The following options are ignormed when used
                to load a texture asset but can be used when creating a texture from an image asset
                    MTKTextureLoaderOptionGenerateMipmaps
                    MTKTextureLoaderOptionSRGB
                    MTKTextureLoaderOptionCubeFromVerticalTexture
                    MTKTextureLoaderOptionOrigins
 @discussion Uses texture data from version of the texture from the texture set in the asset catalog
             which mathces the device's traits.
             This method attempts to load a texture asset with the name given.  If a texture asset
             with the name given does not exist, it will attempt to create a texture from an
             image asset with the given name.
  */
- (nullable id <MTLTexture>)newTextureWithName:(nonnull NSString *)name
                                   scaleFactor:(CGFloat)scaleFactor
                                        bundle:(nullable NSBundle *)bundle
                                       options:(nullable NSDictionary <MTKTextureLoaderOption, id> *)options
                                         error:(NSError *__nullable *__nullable)error NS_AVAILABLE(10_12, 10_0);


@end
// ==========  MetalKit.framework/Headers/MetalKit.h
//
//  MetalKit.h
//  MetalKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <MetalKit/MTKView.h>
#import <MetalKit/MTKTextureLoader.h>
#import <MetalKit/MTKModel.h>
// ==========  MetalKit.framework/Headers/MTKDefines.h
//
//  MTKDefines.h
//  MetalKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <TargetConditionals.h>

#define MTK_EXPORT __attribute__((visibility ("default")))

#define MTK_INLINE static __inline__

#ifdef __cplusplus
#define MTK_EXTERN extern "C" MTK_EXPORT
#else
#define MTK_EXTERN extern MTK_EXPORT
#endif
