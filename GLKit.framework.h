// ==========  GLKit.framework/Headers/GLKEffectPropertyLight.h
//
//  GLKEffectPropertyLight.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//
#import <GLKit/GLKitBase.h>
#import <GLKit/GLKEffectProperty.h>
#import <GLKit/GLKEffectPropertyTransform.h>

typedef NS_ENUM(GLint, GLKLightingType)
{
    GLKLightingTypePerVertex,
    GLKLightingTypePerPixel
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 GLKEffectPropertyLight

 GLKEffectPropertyLight provides a single directional or spot light for an GLKEffect
 in accordance with the OpenGL ES 1.1 specification.

 Per the OpenGL ES 1.1 specification, light position and directions are transformed
 by the modelview matrix.  Accordingly, GLKEffectPropertyLight has a transform property.
 If light transformation is required the transform property must be explicitly set
 for light properties.

 In order for lighting calculations to function properly, clients of GLKEffectPropertyLight
 must enable the vertex attribute array GLKVertexAttribNormal to provide normals for
 lighting calculations. The normals are always normalized.

 The default values for GLKEffectPropertyLight properties are as follows:

    { 0, 0, 1, 0},  // position
    { 0, 0, 0, 1},  // ambient color
    { 1, 1, 1, 1},  // diffuse color
    { 1, 1, 1, 1},  // specular color
    { 0, 0, -1},    // spot direction
    0,              // spot exponent
    180,            // spot cutoff
    1,              // constant attenuation
    0,              // linear attenuation
    0,              // quadratic attenuation

 Note that, as with OpenGL ES 1.1 differentiation between a directional and spot light
 pivots on the value specified for _spotCutoff.  A _spotCutoff of 180.0, the default
 value, indicates a directional light while values less than 180.0 indicates a 
 spot light.
*/
NS_ASSUME_NONNULL_BEGIN

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKEffectPropertyLight : GLKEffectProperty 
{
    @private
    
    // Light parameters
    GLboolean   _enabled;
    GLKVector4  _position;
    GLKVector4  _ambientColor, _diffuseColor, _specularColor;
    GLKVector3  _spotDirection;
    GLfloat     _spotExponent, _spotCutoff;
    GLfloat     _constantAttenuation, _linearAttenuation, _quadraticAttenuation;

    // Transform for independent transformation of light position and direction
    GLKEffectPropertyTransform *_transform;
}

// Properties                                                                                              // Default Value
@property (nonatomic, assign) GLboolean    enabled;                                                        // GL_TRUE
@property (nonatomic, assign) GLKVector4   position;                                                       // { 0.0, 0.0, 0.0, 1.0 }
@property (nonatomic, assign) GLKVector4   ambientColor;                                                   // { 0.0, 0.0, 0.0, 1.0 }
@property (nonatomic, assign) GLKVector4   diffuseColor;                                                   // { 1.0, 1.0, 1.0, 1.0 }
@property (nonatomic, assign) GLKVector4   specularColor;                                                  // { 1.0, 1.0, 1.0, 1.0 }
@property (nonatomic, assign) GLKVector3   spotDirection;                                                  // { 0.0, 0.0, -1.0 }
@property (nonatomic, assign) GLfloat      spotExponent;                                                   // 0.0
@property (nonatomic, assign) GLfloat      spotCutoff;                                                     // 180.0
@property (nonatomic, assign) GLfloat      constantAttenuation, linearAttenuation, quadraticAttenuation;   // 1.0, 0.0, 0.0

@property (nonatomic, retain) GLKEffectPropertyTransform *transform;                                       // All identity matrices

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKView.h
//
//  GLKView.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKitBase.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
/*
 Enums for color buffer formats.
 */
typedef NS_ENUM(GLint, GLKViewDrawableColorFormat)
{
	GLKViewDrawableColorFormatRGBA8888 = 0,
	GLKViewDrawableColorFormatRGB565,
	GLKViewDrawableColorFormatSRGBA8888,
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 Enums for depth buffer formats.
 */
typedef NS_ENUM(GLint, GLKViewDrawableDepthFormat)
{
	GLKViewDrawableDepthFormatNone = 0,
	GLKViewDrawableDepthFormat16,
	GLKViewDrawableDepthFormat24,
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 Enums for stencil buffer formats.
 */
typedef NS_ENUM(GLint, GLKViewDrawableStencilFormat)
{
	GLKViewDrawableStencilFormatNone = 0,
	GLKViewDrawableStencilFormat8,
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 Enums for MSAA.
 */
typedef NS_ENUM(GLint, GLKViewDrawableMultisample)
{
	GLKViewDrawableMultisampleNone = 0,
	GLKViewDrawableMultisample4X,
} NS_ENUM_AVAILABLE(10_8, 5_0);

@class EAGLContext;
@protocol GLKViewDelegate;

#pragma mark -
#pragma mark GLKView
#pragma mark -


OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
API_UNAVAILABLE(macos)
@interface GLKView : UIView <NSCoding>
{

}

- (instancetype)initWithFrame:(CGRect)frame context:(EAGLContext *)context;

@property (nullable, nonatomic, assign) IBOutlet id <GLKViewDelegate> delegate;

@property (nonatomic, retain) EAGLContext *context;

@property (nonatomic, readonly) NSInteger drawableWidth;
@property (nonatomic, readonly) NSInteger drawableHeight;

@property (nonatomic) GLKViewDrawableColorFormat drawableColorFormat;
@property (nonatomic) GLKViewDrawableDepthFormat drawableDepthFormat;
@property (nonatomic) GLKViewDrawableStencilFormat drawableStencilFormat;
@property (nonatomic) GLKViewDrawableMultisample drawableMultisample;

/*
 Binds the context and drawable. This needs to be called when the currently bound framebuffer
 has been changed during the draw method.
 */
- (void)bindDrawable;

/*
 deleteDrawable is normally invoked by the GLKViewController when an application is backgrounded, etc.
 It is the responsibility of the developer to call deleteDrawable when a GLKViewController isn't being used.
 */
- (void)deleteDrawable;

/*
 Returns a UIImage of the resulting draw. Snapshot should never be called from within the draw method.
 */
@property (readonly, strong) UIImage *snapshot;

/*
 Controls whether the view responds to setNeedsDisplay. If true, then the view behaves similarily to a UIView.
 When the view has been marked for display, the draw method is called during the next drawing cycle. If false,
 the view's draw method will never be called during the next drawing cycle. It is expected that -display will be
 called directly in this case. enableSetNeedsDisplay is automatically set to false when used in conjunction with
 the GLKViewController. This value is true by default.
 */
@property (nonatomic) BOOL enableSetNeedsDisplay;

/*
 -display should be called when the view has been set to ignore calls to setNeedsDisplay. This method is used by
 the GLKViewController to invoke the draw method. It can also be used when not using a GLKViewController and custom
 control of the display loop is needed.
 */
- (void)display;

@end

#pragma mark -
#pragma mark GLKViewDelegate
#pragma mark -

@protocol GLKViewDelegate <NSObject>

@required
/*
 Required method for implementing GLKViewDelegate. This draw method variant should be used when not subclassing GLKView.
 This method will not be called if the GLKView object has been subclassed and implements -(void)drawRect:(CGRect)rect.
 */
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect;

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKMatrix3.h
//
//  GLKMatrix3.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATRIX_3_H
#define __GLK_MATRIX_3_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <GLKit/GLKMathTypes.h>
#include <GLKit/GLKVector3.h>
#include <GLKit/GLKQuaternion.h>

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
extern const GLKMatrix3 GLKMatrix3Identity;

GLK_INLINE GLKMatrix3 GLKMatrix3Make(float m00, float m01, float m02,
                                            float m10, float m11, float m12,
                                            float m20, float m21, float m22);

GLK_INLINE GLKMatrix3 GLKMatrix3MakeAndTranspose(float m00, float m01, float m02,
                                                        float m10, float m11, float m12,
                                                        float m20, float m21, float m22);

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithArray(float values[9]);

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithArrayAndTranspose(float values[9]);

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithRows(GLKVector3 row0,
                                                    GLKVector3 row1, 
                                                    GLKVector3 row2);

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithColumns(GLKVector3 column0,
                                                       GLKVector3 column1, 
                                                       GLKVector3 column2);

/*
 The quaternion will be normalized before conversion.
 */
GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithQuaternion(GLKQuaternion quaternion);

GLK_INLINE GLKMatrix3 GLKMatrix3MakeScale(float sx, float sy, float sz);	
GLK_INLINE GLKMatrix3 GLKMatrix3MakeRotation(float radians, float x, float y, float z);

GLK_INLINE GLKMatrix3 GLKMatrix3MakeXRotation(float radians);
GLK_INLINE GLKMatrix3 GLKMatrix3MakeYRotation(float radians);
GLK_INLINE GLKMatrix3 GLKMatrix3MakeZRotation(float radians);

/*
 Returns the upper left 2x2 portion of the 3x3 matrix.
 */
GLK_INLINE GLKMatrix2 GLKMatrix3GetMatrix2(GLKMatrix3 matrix);

GLK_INLINE GLKVector3 GLKMatrix3GetRow(GLKMatrix3 matrix, int row);
GLK_INLINE GLKVector3 GLKMatrix3GetColumn(GLKMatrix3 matrix, int column);

GLK_INLINE GLKMatrix3 GLKMatrix3SetRow(GLKMatrix3 matrix, int row, GLKVector3 vector);
GLK_INLINE GLKMatrix3 GLKMatrix3SetColumn(GLKMatrix3 matrix, int column, GLKVector3 vector);
    
GLK_INLINE GLKMatrix3 GLKMatrix3Transpose(GLKMatrix3 matrix);

GLKMatrix3 GLKMatrix3Invert(GLKMatrix3 matrix, bool *isInvertible);
GLKMatrix3 GLKMatrix3InvertAndTranspose(GLKMatrix3 matrix, bool *isInvertible);

GLK_INLINE GLKMatrix3 GLKMatrix3Multiply(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight);

GLK_INLINE GLKMatrix3 GLKMatrix3Add(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight);
GLK_INLINE GLKMatrix3 GLKMatrix3Subtract(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight);
    
GLK_INLINE GLKMatrix3 GLKMatrix3Scale(GLKMatrix3 matrix, float sx, float sy, float sz);
GLK_INLINE GLKMatrix3 GLKMatrix3ScaleWithVector3(GLKMatrix3 matrix, GLKVector3 scaleVector);
/*
 The last component of the GLKVector4, scaleVector, is ignored.
 */
GLK_INLINE GLKMatrix3 GLKMatrix3ScaleWithVector4(GLKMatrix3 matrix, GLKVector4 scaleVector);

GLK_INLINE GLKMatrix3 GLKMatrix3Rotate(GLKMatrix3 matrix, float radians, float x, float y, float z);
GLK_INLINE GLKMatrix3 GLKMatrix3RotateWithVector3(GLKMatrix3 matrix, float radians, GLKVector3 axisVector);
/*
 The last component of the GLKVector4, axisVector, is ignored.
 */
GLK_INLINE GLKMatrix3 GLKMatrix3RotateWithVector4(GLKMatrix3 matrix, float radians, GLKVector4 axisVector);

GLK_INLINE GLKMatrix3 GLKMatrix3RotateX(GLKMatrix3 matrix, float radians);
GLK_INLINE GLKMatrix3 GLKMatrix3RotateY(GLKMatrix3 matrix, float radians);
GLK_INLINE GLKMatrix3 GLKMatrix3RotateZ(GLKMatrix3 matrix, float radians);

GLK_INLINE GLKVector3 GLKMatrix3MultiplyVector3(GLKMatrix3 matrixLeft, GLKVector3 vectorRight);

GLK_INLINE void GLKMatrix3MultiplyVector3Array(GLKMatrix3 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount);

#pragma mark -
#pragma mark Implementations
#pragma mark -

GLK_INLINE GLKMatrix3 GLKMatrix3Make(float m00, float m01, float m02,
                                            float m10, float m11, float m12,
                                            float m20, float m21, float m22)
{
    GLKMatrix3 m = { m00, m01, m02,
                     m10, m11, m12,
                     m20, m21, m22 };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeAndTranspose(float m00, float m01, float m02,
                                                        float m10, float m11, float m12,
                                                        float m20, float m21, float m22)
{
    GLKMatrix3 m = { m00, m10, m20,
                     m01, m11, m21,
                     m02, m12, m22 };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithArray(float values[9])
{
    GLKMatrix3 m = { values[0], values[1], values[2],
                     values[3], values[4], values[5],
                     values[6], values[7], values[8] };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithArrayAndTranspose(float values[9])
{
    GLKMatrix3 m = { values[0], values[3], values[6],
                     values[1], values[4], values[7],
                     values[2], values[5], values[8] };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithRows(GLKVector3 row0,
                                                    GLKVector3 row1, 
                                                    GLKVector3 row2)
{
    GLKMatrix3 m = { row0.v[0], row1.v[0], row2.v[0],
                     row0.v[1], row1.v[1], row2.v[1],
                     row0.v[2], row1.v[2], row2.v[2] };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithColumns(GLKVector3 column0,
                                                       GLKVector3 column1, 
                                                       GLKVector3 column2)
{
    GLKMatrix3 m = { column0.v[0], column0.v[1], column0.v[2],
                     column1.v[0], column1.v[1], column1.v[2],
                     column2.v[0], column2.v[1], column2.v[2] };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeWithQuaternion(GLKQuaternion quaternion)
{
    quaternion = GLKQuaternionNormalize(quaternion);
    
    float x = quaternion.q[0];
    float y = quaternion.q[1];
    float z = quaternion.q[2];
    float w = quaternion.q[3];
    
    float _2x = x + x;
    float _2y = y + y;
    float _2z = z + z;
    float _2w = w + w;
    
    GLKMatrix3 m = { 1.0f - _2y * y - _2z * z,
                    _2x * y + _2w * z,
                    _2x * z - _2w * y,

                    _2x * y - _2w * z,
                    1.0f - _2x * x - _2z * z,
                    _2y * z + _2w * x,

                    _2x * z + _2w * y,
                    _2y * z - _2w * x,
                    1.0f - _2x * x - _2y * y };
    
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeScale(float sx, float sy, float sz)
{
    GLKMatrix3 m = GLKMatrix3Identity;
    m.m[0] = sx;
    m.m[4] = sy;
    m.m[8] = sz;
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeRotation(float radians, float x, float y, float z)
{
    GLKVector3 v = GLKVector3Normalize(GLKVector3Make(x, y, z));
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    GLKMatrix3 m = { cos + cosp * v.v[0] * v.v[0],
                     cosp * v.v[0] * v.v[1] + v.v[2] * sin,
                     cosp * v.v[0] * v.v[2] - v.v[1] * sin,

                     cosp * v.v[0] * v.v[1] - v.v[2] * sin,
                     cos + cosp * v.v[1] * v.v[1],
                     cosp * v.v[1] * v.v[2] + v.v[0] * sin,

                     cosp * v.v[0] * v.v[2] + v.v[1] * sin,
                     cosp * v.v[1] * v.v[2] - v.v[0] * sin,
                     cos + cosp * v.v[2] * v.v[2] };
    
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix3 m = { 1.0f, 0.0f, 0.0f,
                     0.0f, cos, sin,
                     0.0f, -sin, cos };
    
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix3 m = { cos, 0.0f, -sin,
                     0.0f, 1.0f, 0.0f,
                     sin, 0.0f, cos };
    
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3MakeZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix3 m = { cos, sin, 0.0f,
                     -sin, cos, 0.0f,
                     0.0f, 0.0f, 1.0f };
    
    return m;
}

GLK_INLINE GLKMatrix2 GLKMatrix3GetMatrix2(GLKMatrix3 matrix)
{
    GLKMatrix2 m = { matrix.m[0], matrix.m[1],
                     matrix.m[3], matrix.m[4] };
    return m;
}

GLK_INLINE GLKVector3 GLKMatrix3GetRow(GLKMatrix3 matrix, int row)
{
    GLKVector3 v = { matrix.m[row], matrix.m[3 + row], matrix.m[6 + row] };
    return v;
}

GLK_INLINE GLKVector3 GLKMatrix3GetColumn(GLKMatrix3 matrix, int column)
{
    GLKVector3 v = { matrix.m[column * 3 + 0], matrix.m[column * 3 + 1], matrix.m[column * 3 + 2] };
    return v;
}

GLK_INLINE GLKMatrix3 GLKMatrix3SetRow(GLKMatrix3 matrix, int row, GLKVector3 vector)
{
    matrix.m[row] = vector.v[0];
    matrix.m[row + 3] = vector.v[1];
    matrix.m[row + 6] = vector.v[2];
    
    return matrix;
}

GLK_INLINE GLKMatrix3 GLKMatrix3SetColumn(GLKMatrix3 matrix, int column, GLKVector3 vector)
{
    matrix.m[column * 3 + 0] = vector.v[0];
    matrix.m[column * 3 + 1] = vector.v[1];
    matrix.m[column * 3 + 2] = vector.v[2];
    
    return matrix;
}
    
GLK_INLINE GLKMatrix3 GLKMatrix3Transpose(GLKMatrix3 matrix)
{
    GLKMatrix3 m = { matrix.m[0], matrix.m[3], matrix.m[6],
                     matrix.m[1], matrix.m[4], matrix.m[7],
                     matrix.m[2], matrix.m[5], matrix.m[8] };
    return m;
}
 
GLK_INLINE GLKMatrix3 GLKMatrix3Multiply(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight)
{
#if defined(__ARM_NEON__)
    GLKMatrix3 m;
    float32x4x3_t iMatrixLeft;
    float32x4x3_t iMatrixRight;
    float32x4x3_t mm;
    
    iMatrixLeft.val[0] = vld1q_f32(&matrixLeft.m[0]); // 0 1 2 3
    iMatrixLeft.val[1] = vld1q_f32(&matrixLeft.m[3]); // 3 4 5 6
    iMatrixLeft.val[2] = vld1q_f32(&matrixLeft.m[5]); // 5 6 7 8

    iMatrixRight.val[0] = vld1q_f32(&matrixRight.m[0]); // 0 1 2 3
    iMatrixRight.val[1] = vld1q_f32(&matrixRight.m[3]); // 3 4 5 6
    iMatrixRight.val[2] = vld1q_f32(&matrixRight.m[5]); // 5 6 7 8
        
    iMatrixLeft.val[2] = vextq_f32(iMatrixLeft.val[2], iMatrixLeft.val[2], 1); // 6 7 8 x
    
    mm.val[0] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[0], 0));
    mm.val[1] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[0], 3));
    mm.val[2] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[1], 3));
    
    mm.val[0] = vmlaq_n_f32(mm.val[0], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[0], 1));
    mm.val[1] = vmlaq_n_f32(mm.val[1], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[1], 1));
    mm.val[2] = vmlaq_n_f32(mm.val[2], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[2], 2));

    mm.val[0] = vmlaq_n_f32(mm.val[0], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[0], 2));
    mm.val[1] = vmlaq_n_f32(mm.val[1], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[1], 2));
    mm.val[2] = vmlaq_n_f32(mm.val[2], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[2], 3));

    memcpy(&m.m[0], (char *)&(mm.val[0]), 16);
    memcpy(&m.m[3], (char *)&(mm.val[1]), 16);
    float32x2_t vlow = vget_low_f32(mm.val[2]);
    memcpy(&m.m[6], (char *)&vlow, 8);
    m.m[8] = vgetq_lane_f32(mm.val[2], 2);
    
    return m;
#elif defined(GLK_SSE3_INTRINSICS)
	struct {
		GLKMatrix3 m;
		char pad[16*4 - sizeof(GLKMatrix3)];
	} ret;
    
    const __m128 iMatrixLeft0 = _mm_loadu_ps(&matrixLeft.m[0]); // 0 1 2 3 // unaligned load
    const __m128 iMatrixLeft1 = _mm_loadu_ps(&matrixLeft.m[3]); // 3 4 5 6 // unaligned load
    const __m128 iMatrixLeft2Tmp = _mm_loadu_ps(&matrixLeft.m[5]); // 5 6 7 8 // unaligned load
    const __m128 iMatrixLeft2 = _mm_shuffle_ps(iMatrixLeft2Tmp, iMatrixLeft2Tmp, _MM_SHUFFLE(0, 3, 2, 1)); // 6 7 8 x
    
    const __m128 iMatrixRight0 = _mm_loadu_ps(&matrixRight.m[0]);
    const __m128 iMatrixRight1 = _mm_loadu_ps(&matrixRight.m[3]);
    const __m128 iMatrixRight2 = _mm_loadu_ps(&matrixRight.m[5]);
    
    const __m128 mm0 = iMatrixLeft0 * _mm_shuffle_ps(iMatrixRight0, iMatrixRight0, _MM_SHUFFLE(0, 0, 0, 0))  // mm0 = L0*R0 L1*R0 L2*R0 L3*R0
                     + iMatrixLeft1 * _mm_shuffle_ps(iMatrixRight0, iMatrixRight0, _MM_SHUFFLE(1, 1, 1, 1))  // mm0 = L0*R0+L3*R1 L1*R0+L4*R1 L2*R0+L5*R1 L3*R0+L6*R1
                     + iMatrixLeft2 * _mm_shuffle_ps(iMatrixRight0, iMatrixRight0, _MM_SHUFFLE(2, 2, 2, 2));
		
    const __m128 mm1 = iMatrixLeft0 * _mm_shuffle_ps(iMatrixRight0, iMatrixRight0, _MM_SHUFFLE(3, 3, 3, 3))  // mm1 = L0*R3 L1*R3 L2*R3 L3*R3
                     + iMatrixLeft1 * _mm_shuffle_ps(iMatrixRight1, iMatrixRight1, _MM_SHUFFLE(1, 1, 1, 1))  // mm1 = L0*R3+L3*R4 L1*R3+L4*R4 L2*R3+L5*R4 L3*R3+
                     + iMatrixLeft2 * _mm_shuffle_ps(iMatrixRight1, iMatrixRight1, _MM_SHUFFLE(2, 2, 2, 2));
	
    const __m128 mm2 = iMatrixLeft0 * _mm_shuffle_ps(iMatrixRight1, iMatrixRight1, _MM_SHUFFLE(3, 3, 3, 3)) // mm2 = L0*R6 L1*R6 L2*R6 L3*R6
                     + iMatrixLeft1 * _mm_shuffle_ps(iMatrixRight2, iMatrixRight2, _MM_SHUFFLE(2, 2, 2, 2))
                     + iMatrixLeft2 * _mm_shuffle_ps(iMatrixRight2, iMatrixRight2, _MM_SHUFFLE(3, 3, 3, 3));
    
    _mm_storeu_ps(&ret.m.m[0], mm0); //unaligned store to indices: 0 1 2 3
    _mm_storeu_ps(&ret.m.m[3], mm1); //unaligned store to indices: 3 4 5 6
    _mm_storeu_ps(&ret.m.m[6], mm2); //unaligned store to indices: 6 7 8
		
    return ret.m;
#else
    GLKMatrix3 m;
    
    m.m[0] = matrixLeft.m[0] * matrixRight.m[0] + matrixLeft.m[3] * matrixRight.m[1] + matrixLeft.m[6] * matrixRight.m[2];
    m.m[3] = matrixLeft.m[0] * matrixRight.m[3] + matrixLeft.m[3] * matrixRight.m[4] + matrixLeft.m[6] * matrixRight.m[5];
    m.m[6] = matrixLeft.m[0] * matrixRight.m[6] + matrixLeft.m[3] * matrixRight.m[7] + matrixLeft.m[6] * matrixRight.m[8];
    
    m.m[1] = matrixLeft.m[1] * matrixRight.m[0] + matrixLeft.m[4] * matrixRight.m[1] + matrixLeft.m[7] * matrixRight.m[2];
    m.m[4] = matrixLeft.m[1] * matrixRight.m[3] + matrixLeft.m[4] * matrixRight.m[4] + matrixLeft.m[7] * matrixRight.m[5];
    m.m[7] = matrixLeft.m[1] * matrixRight.m[6] + matrixLeft.m[4] * matrixRight.m[7] + matrixLeft.m[7] * matrixRight.m[8];
    
    m.m[2] = matrixLeft.m[2] * matrixRight.m[0] + matrixLeft.m[5] * matrixRight.m[1] + matrixLeft.m[8] * matrixRight.m[2];
    m.m[5] = matrixLeft.m[2] * matrixRight.m[3] + matrixLeft.m[5] * matrixRight.m[4] + matrixLeft.m[8] * matrixRight.m[5];
    m.m[8] = matrixLeft.m[2] * matrixRight.m[6] + matrixLeft.m[5] * matrixRight.m[7] + matrixLeft.m[8] * matrixRight.m[8];
    
    return m;
#endif
}

GLK_INLINE GLKMatrix3 GLKMatrix3Add(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight)
{
#if defined(GLK_SSE3_INTRINSICS)
    GLKMatrix3 m;
    
    _mm_storeu_ps(&m.m[0], _mm_loadu_ps(&matrixLeft.m[0]) + _mm_loadu_ps(&matrixRight.m[0]));
    _mm_storeu_ps(&m.m[4], _mm_loadu_ps(&matrixLeft.m[4]) + _mm_loadu_ps(&matrixRight.m[4]));
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    
    return m;
#else
    GLKMatrix3 m;
    
    m.m[0] = matrixLeft.m[0] + matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] + matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] + matrixRight.m[2];
    
    m.m[3] = matrixLeft.m[3] + matrixRight.m[3];
    m.m[4] = matrixLeft.m[4] + matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] + matrixRight.m[5];
    
    m.m[6] = matrixLeft.m[6] + matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] + matrixRight.m[7];
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    
    return m;
#endif
}

GLK_INLINE GLKMatrix3 GLKMatrix3Subtract(GLKMatrix3 matrixLeft, GLKMatrix3 matrixRight)
{
#if defined(GLK_SSE3_INTRINSICS)
    GLKMatrix3 m;
    
    _mm_storeu_ps(&m.m[0], _mm_loadu_ps(&matrixLeft.m[0]) - _mm_loadu_ps(&matrixRight.m[0]));
    _mm_storeu_ps(&m.m[4], _mm_loadu_ps(&matrixLeft.m[4]) - _mm_loadu_ps(&matrixRight.m[4]));
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    
    return m;
#else
    GLKMatrix3 m;
    
    m.m[0] = matrixLeft.m[0] - matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] - matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] - matrixRight.m[2];
    
    m.m[3] = matrixLeft.m[3] - matrixRight.m[3];
    m.m[4] = matrixLeft.m[4] - matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] - matrixRight.m[5];
    
    m.m[6] = matrixLeft.m[6] - matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] - matrixRight.m[7];
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    
    return m;
#endif
}
    
GLK_INLINE GLKMatrix3 GLKMatrix3Scale(GLKMatrix3 matrix, float sx, float sy, float sz)
{
    GLKMatrix3 m = { matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx,
                     matrix.m[3] * sy, matrix.m[4] * sy, matrix.m[5] * sy,
                     matrix.m[6] * sz, matrix.m[7] * sz, matrix.m[8] * sz };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3ScaleWithVector3(GLKMatrix3 matrix, GLKVector3 scaleVector)
{
    GLKMatrix3 m = { matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0],
                     matrix.m[3] * scaleVector.v[1], matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1],
                     matrix.m[6] * scaleVector.v[2], matrix.m[7] * scaleVector.v[2], matrix.m[8] * scaleVector.v[2] };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3ScaleWithVector4(GLKMatrix3 matrix, GLKVector4 scaleVector)
{
    GLKMatrix3 m = { matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0],
                     matrix.m[3] * scaleVector.v[1], matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1],
                     matrix.m[6] * scaleVector.v[2], matrix.m[7] * scaleVector.v[2], matrix.m[8] * scaleVector.v[2] };
    return m;
}

GLK_INLINE GLKMatrix3 GLKMatrix3Rotate(GLKMatrix3 matrix, float radians, float x, float y, float z)
{
    GLKMatrix3 rm = GLKMatrix3MakeRotation(radians, x, y, z);
    return GLKMatrix3Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix3 GLKMatrix3RotateWithVector3(GLKMatrix3 matrix, float radians, GLKVector3 axisVector)
{
    GLKMatrix3 rm = GLKMatrix3MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return GLKMatrix3Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix3 GLKMatrix3RotateWithVector4(GLKMatrix3 matrix, float radians, GLKVector4 axisVector)
{
    GLKMatrix3 rm = GLKMatrix3MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return GLKMatrix3Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix3 GLKMatrix3RotateX(GLKMatrix3 matrix, float radians)
{
    GLKMatrix3 rm = GLKMatrix3MakeXRotation(radians);
    return GLKMatrix3Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix3 GLKMatrix3RotateY(GLKMatrix3 matrix, float radians)
{
    GLKMatrix3 rm = GLKMatrix3MakeYRotation(radians);
    return GLKMatrix3Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix3 GLKMatrix3RotateZ(GLKMatrix3 matrix, float radians)
{
    GLKMatrix3 rm = GLKMatrix3MakeZRotation(radians);
    return GLKMatrix3Multiply(matrix, rm);
}

GLK_INLINE GLKVector3 GLKMatrix3MultiplyVector3(GLKMatrix3 matrixLeft, GLKVector3 vectorRight)
{
    GLKVector3 v = { matrixLeft.m[0] * vectorRight.v[0] + matrixLeft.m[3] * vectorRight.v[1] + matrixLeft.m[6] * vectorRight.v[2],
                     matrixLeft.m[1] * vectorRight.v[0] + matrixLeft.m[4] * vectorRight.v[1] + matrixLeft.m[7] * vectorRight.v[2],
                     matrixLeft.m[2] * vectorRight.v[0] + matrixLeft.m[5] * vectorRight.v[1] + matrixLeft.m[8] * vectorRight.v[2] };
    return v;
}

GLK_INLINE void GLKMatrix3MultiplyVector3Array(GLKMatrix3 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix3MultiplyVector3(matrix, vectors[i]);
}
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATRIX_3_H */
// ==========  GLKit.framework/Headers/GLKEffectProperty.h
//
//  GLKEffectProperty.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKitBase.h>
#import <GLKit/GLKMath.h>


/*
 GLKEffectProperty

 GLKEffectProperties are objects that allow piecewise characterization of NamedEffects.
 Examples of GLKEffectProperty classes are GLKEffectPropertyTransform and GLKEffectPropertyTexture.
 GLKBaseEffect, for instance, has obj-c properties "transform" and "texture2d0" of the aforementioned
 types respectively.  By specifying proper parameters on these two properties along with the
 proper OpenGL vertex array object configuration, a, for instance, textured, rotated quad can
 be drawn.

 GLKEffectProperty is an abstract class.  Instantiation of this class via its -init method will
 result in an error.  GLKEffectProperty maintains a few instance variables that are shared by
 its descendants.

 All descendants of GLKEffectProperty are concrete, mutable classes.
 */

NS_ASSUME_NONNULL_BEGIN
typedef struct GLKEffectPropertyPrv *GLKEffectPropertyPrvPtr;


OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKEffectProperty : NSObject 
{
    @protected
    
    GLint                   _location;         // Shader location
    GLchar                  *_nameString;      // Shader location name
    
    GLKEffectPropertyPrvPtr _prv;
}

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKVector3.h
//
//  GLKVector3.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_VECTOR_3_H
#define __GLK_VECTOR_3_H

#include <stdbool.h>
#include <math.h>

#include <GLKit/GLKMathTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
GLK_INLINE GLKVector3 GLKVector3Make(float x, float y, float z);
GLK_INLINE GLKVector3 GLKVector3MakeWithArray(float values[3]);

GLK_INLINE GLKVector3 GLKVector3Negate(GLKVector3 vector);

GLK_INLINE GLKVector3 GLKVector3Add(GLKVector3 vectorLeft, GLKVector3 vectorRight);
GLK_INLINE GLKVector3 GLKVector3Subtract(GLKVector3 vectorLeft, GLKVector3 vectorRight);
GLK_INLINE GLKVector3 GLKVector3Multiply(GLKVector3 vectorLeft, GLKVector3 vectorRight);
GLK_INLINE GLKVector3 GLKVector3Divide(GLKVector3 vectorLeft, GLKVector3 vectorRight);
        
GLK_INLINE GLKVector3 GLKVector3AddScalar(GLKVector3 vector, float value);
GLK_INLINE GLKVector3 GLKVector3SubtractScalar(GLKVector3 vector, float value);
GLK_INLINE GLKVector3 GLKVector3MultiplyScalar(GLKVector3 vector, float value);
GLK_INLINE GLKVector3 GLKVector3DivideScalar(GLKVector3 vector, float value);
	
/*
 Returns a vector whose elements are the larger of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector3 GLKVector3Maximum(GLKVector3 vectorLeft, GLKVector3 vectorRight);
/*
 Returns a vector whose elements are the smaller of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector3 GLKVector3Minimum(GLKVector3 vectorLeft, GLKVector3 vectorRight);
    
/*
 Returns true if all of the first vector's elements are equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector3AllEqualToVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight);
/*
 Returns true if all of the vector's elements are equal to the provided value.
 */
GLK_INLINE bool GLKVector3AllEqualToScalar(GLKVector3 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector3AllGreaterThanVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight);
/*
 Returns true if all of the vector's elements are greater than the provided value.
 */
GLK_INLINE bool GLKVector3AllGreaterThanScalar(GLKVector3 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than or equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector3AllGreaterThanOrEqualToVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight);
/*
 Returns true if all of the vector's elements are greater than or equal to the provided value.
 */
GLK_INLINE bool GLKVector3AllGreaterThanOrEqualToScalar(GLKVector3 vector, float value);
    
GLK_INLINE GLKVector3 GLKVector3Normalize(GLKVector3 vector);

GLK_INLINE float GLKVector3DotProduct(GLKVector3 vectorLeft, GLKVector3 vectorRight);
GLK_INLINE float GLKVector3Length(GLKVector3 vector);
GLK_INLINE float GLKVector3Distance(GLKVector3 vectorStart, GLKVector3 vectorEnd);

GLK_INLINE GLKVector3 GLKVector3Lerp(GLKVector3 vectorStart, GLKVector3 vectorEnd, float t);

GLK_INLINE GLKVector3 GLKVector3CrossProduct(GLKVector3 vectorLeft, GLKVector3 vectorRight);
    
/*
 Project the vector, vectorToProject, onto the vector, projectionVector.
 */
GLK_INLINE GLKVector3 GLKVector3Project(GLKVector3 vectorToProject, GLKVector3 projectionVector);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKVector3 GLKVector3Make(float x, float y, float z)
{
    GLKVector3 v = { x, y, z };
    return v;
}

GLK_INLINE GLKVector3 GLKVector3MakeWithArray(float values[3])
{
    GLKVector3 v = { values[0], values[1], values[2] };
    return v;
}
   
GLK_INLINE GLKVector3 GLKVector3Negate(GLKVector3 vector)
{
    GLKVector3 v = { -vector.v[0], -vector.v[1], -vector.v[2] };
    return v;
}
    
GLK_INLINE GLKVector3 GLKVector3Add(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    GLKVector3 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1],
                     vectorLeft.v[2] + vectorRight.v[2] };
    return v;
}

GLK_INLINE GLKVector3 GLKVector3Subtract(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    GLKVector3 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1],
                     vectorLeft.v[2] - vectorRight.v[2] };
    return v;
}

GLK_INLINE GLKVector3 GLKVector3Multiply(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    GLKVector3 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[2] };
    return v;
}

GLK_INLINE GLKVector3 GLKVector3Divide(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    GLKVector3 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1],
                     vectorLeft.v[2] / vectorRight.v[2] };
    return v;
}

GLK_INLINE GLKVector3 GLKVector3AddScalar(GLKVector3 vector, float value)
{
    GLKVector3 v = { vector.v[0] + value,
                     vector.v[1] + value,
                     vector.v[2] + value };
    return v;
}

GLK_INLINE GLKVector3 GLKVector3SubtractScalar(GLKVector3 vector, float value)
{
    GLKVector3 v = { vector.v[0] - value,
                     vector.v[1] - value,
                     vector.v[2] - value };
    return v;    
}

GLK_INLINE GLKVector3 GLKVector3MultiplyScalar(GLKVector3 vector, float value)
{
    GLKVector3 v = { vector.v[0] * value,
                     vector.v[1] * value,
                     vector.v[2] * value };
    return v;   
}

GLK_INLINE GLKVector3 GLKVector3DivideScalar(GLKVector3 vector, float value)
{
    GLKVector3 v = { vector.v[0] / value,
                     vector.v[1] / value,
                     vector.v[2] / value };
    return v;
}
    
GLK_INLINE GLKVector3 GLKVector3Maximum(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    GLKVector3 max = vectorLeft;
    if (vectorRight.v[0] > vectorLeft.v[0])
        max.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] > vectorLeft.v[1])
        max.v[1] = vectorRight.v[1];
    if (vectorRight.v[2] > vectorLeft.v[2])
        max.v[2] = vectorRight.v[2];
    return max;
}
    
GLK_INLINE GLKVector3 GLKVector3Minimum(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    GLKVector3 min = vectorLeft;
    if (vectorRight.v[0] < vectorLeft.v[0])
        min.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] < vectorLeft.v[1])
        min.v[1] = vectorRight.v[1];
    if (vectorRight.v[2] < vectorLeft.v[2])
        min.v[2] = vectorRight.v[2];
    return min;
}
    
GLK_INLINE bool GLKVector3AllEqualToVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1] &&
        vectorLeft.v[2] == vectorRight.v[2])
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector3AllEqualToScalar(GLKVector3 vector, float value)
{
    bool compare = false;
    if (vector.v[0] == value &&
        vector.v[1] == value &&
        vector.v[2] == value)
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector3AllGreaterThanVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] > vectorRight.v[0] &&
        vectorLeft.v[1] > vectorRight.v[1] &&
        vectorLeft.v[2] > vectorRight.v[2])
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector3AllGreaterThanScalar(GLKVector3 vector, float value)
{
    bool compare = false;
    if (vector.v[0] > value &&
        vector.v[1] > value &&
        vector.v[2] > value)
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector3AllGreaterThanOrEqualToVector3(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] >= vectorRight.v[0] &&
        vectorLeft.v[1] >= vectorRight.v[1] &&
        vectorLeft.v[2] >= vectorRight.v[2])
        compare = true;
    return compare;
}

GLK_INLINE bool GLKVector3AllGreaterThanOrEqualToScalar(GLKVector3 vector, float value)
{
    bool compare = false;
    if (vector.v[0] >= value &&
        vector.v[1] >= value &&
        vector.v[2] >= value)
        compare = true;
    return compare;
}
    
GLK_INLINE GLKVector3 GLKVector3Normalize(GLKVector3 vector)
{
    float scale = 1.0f / GLKVector3Length(vector);
    GLKVector3 v = { vector.v[0] * scale, vector.v[1] * scale, vector.v[2] * scale };
    return v;
}
    
GLK_INLINE float GLKVector3DotProduct(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1] + vectorLeft.v[2] * vectorRight.v[2];
}

GLK_INLINE float GLKVector3Length(GLKVector3 vector)
{
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1] + vector.v[2] * vector.v[2]);
}

GLK_INLINE float GLKVector3Distance(GLKVector3 vectorStart, GLKVector3 vectorEnd)
{
    return GLKVector3Length(GLKVector3Subtract(vectorEnd, vectorStart));
}
    
GLK_INLINE GLKVector3 GLKVector3Lerp(GLKVector3 vectorStart, GLKVector3 vectorEnd, float t)
{
    GLKVector3 v = { vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                     vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t),
                     vectorStart.v[2] + ((vectorEnd.v[2] - vectorStart.v[2]) * t) };
    return v;
}
 
GLK_INLINE GLKVector3 GLKVector3CrossProduct(GLKVector3 vectorLeft, GLKVector3 vectorRight)
{
    GLKVector3 v = { vectorLeft.v[1] * vectorRight.v[2] - vectorLeft.v[2] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[0] - vectorLeft.v[0] * vectorRight.v[2],
                     vectorLeft.v[0] * vectorRight.v[1] - vectorLeft.v[1] * vectorRight.v[0] };
    return v;
}
        
GLK_INLINE GLKVector3 GLKVector3Project(GLKVector3 vectorToProject, GLKVector3 projectionVector)
{
    float scale = GLKVector3DotProduct(projectionVector, vectorToProject) / GLKVector3DotProduct(projectionVector, projectionVector);
    GLKVector3 v = GLKVector3MultiplyScalar(projectionVector, scale);
    return v;
}
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_VECTOR_3_H */
// ==========  GLKit.framework/Headers/GLKEffectPropertyTransform.h
//
//  GLKEffectPropertyTransform.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//
#import <GLKit/GLKitBase.h>
#import <GLKit/GLKEffectProperty.h>
#import <GLKit/GLKMath.h>

/*
 GLKEffectPropertyTransformm 

 GLKEffectPropertyTransform maintains three primary matrices:
      
      _projectionMatrix
      _modelviewMatrix

 and 1 derived matrix: _normalMatrix.

 When the modelview matrix is changed the normalMatrix is marked as stale.
 If the normalMatrix is subsequently retrieved after being marked stale
 the normalMatrix selector will recalculate the normalMatrix to return
 a current result with respect to the modelviewMatrix.
*/
NS_ASSUME_NONNULL_BEGIN

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKEffectPropertyTransform : GLKEffectProperty 
{
    @private
    
    // Primary matrices
    GLKMatrix4  _modelviewMatrix, _projectionMatrix;
    
    // Derived matrix
    GLKMatrix3  _normalMatrix;
}

// Properties                                                                                    // Default Value
@property (nonatomic, assign)   GLKMatrix4   modelviewMatrix, projectionMatrix;                  // Identity for all
@property (nonatomic, readonly) GLKMatrix3   normalMatrix;                                       // Identity 

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKBaseEffect.h
//
//  GLKBaseEffect.h
//  GLKit
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKitBase.h>
#import <GLKit/GLKNamedEffect.h>
#import <GLKit/GLKEffectPropertyTransform.h>
#import <GLKit/GLKEffectPropertyLight.h>
#import <GLKit/GLKEffectPropertyMaterial.h>
#import <GLKit/GLKEffectPropertyTexture.h>
#import <GLKit/GLKEffectPropertyFog.h>

/*
 GLKBaseEffect 

 GLKBaseEffect is designed to simplify visual effects common to many OpenGL applications today.  
 For iOS, GLKBaseEffect requires at least OpenGL ES 2.0 and for OS X, GLKBaseEffect requires
 at least an OpenGL Core Profile.  An appropriate context must be created and made current prior
 to instantiating and initializing GLKBaseEffect objects.

 GLKBaseEffect is designed to freely interoperate with custom OpenGL code.  It is also
 designed to minimally impact OpenGL state settings.  During initialization of a GLKBaseEffect
 object and its properties, OpenGL state settings are preserved.
 
 GLKBaseEffect is program based and, with the binding of its underlying GLSL program, it modifies 
 GL_CURRENT_PROGRAM state setting implicitly when -[GLKBaseEffect prepareToDraw] is called.  For 
 performance reasons GL_CURRENT_PROGRAM is not saved and restored by GLKBaseEffect so clients of 
 this class must set/save/restore the GL_CURRENT_PROGRAM before and/or after a call to 
 -[GLKBaseEffect prepareToDraw] as is applicable for their application.

 If texturing properties have been specified and are enabled, GLKBaseEffect will also modify
 the OpenGL state element GL_TEXTURE_BINDING_2D.  This state must also be handled in the manner
 described for GL_CURRENT_PROGRAM above.

 GLKBaseEffect uses named vertex attributes so client applications can refer to the following
 vertex attribute names when configuring/enabling/binding the vertex attribute data to be used with 
 GLKBaseEffect:

      GLKVertexAttribPosition      0
      GLKVertexAttribNormal        1
      GLKVertexAttribColor         2
      GLKVertexAttribTexCoord0     3
      GLKVertexAttribTexCoord1     4

      Note that normals for GLKVertexAttribNormal are always normalized.

 The (4) canonical steps to use GLKBaseEffect are:

      (1) Allocate and initialize an instance of GLKBaseEffect

      directionalLightEffect = [[GLKBaseEffect alloc] init];

      (2) Set the desired properties on the effect

      // Configure light0
      directionalLightEffect.light0.position = lightPosition;
      directionalLightEffect.light0.diffuseColor = diffuseColor;
      directionalLightEffect.light0.ambientColor = ambientColor;

      // Configure material
      directionalLightEffect.material.diffuseColor = materialDiffuseColor;
      directionalLightEffect.material.ambientColor = materialAmbientColor;
      directionalLightEffect.material.specularColor = materialSpecularColor;
      directionalLightEffect.material.shininess = 10.0;

      (3) Initialize vertex attribute / vertex array state preferrably with a vertex array object
          for the model or scene to be drawn.

      glGenVertexArraysOES(1, &vaoName);
      glBindVertexArrayOES(vaoName);

      // Create and initialize VBO for each vertex attribute
      // The example below shows an example of setup up the position vertex attribute.
      // Repeat the steps below for each additional desired attribute: normal, color, texCoord0, texCoord1.
      
      glGenBuffers(1, &positionVBO);
      glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
      glBufferData(GL_ARRAY_BUFFER, vboSize, dataBufPtr, GL_STATIC_DRAW);
      glVertexAttribPointer(GLKVertexAttribPosition, size, type, normalize, stride, NULL);
      glEnableVertexAttribArray(GLKVertexAttribPosition);

      ... repeat the steps above for other desired vertex attributes

      glBindVertexArrayOES(0);   // unbind the VAO we created above

      (4) For each frame drawn:  Update properties that change per frame.  Synchronize the changed effect state
          by calling -[GLKBaseEffect prepareToDraw].  Draw the model with the effect

      directionalLightEffect.transform.modelviewMatrix = modelviewMatrix;
      [directionalLightEffect prepareToDraw];
      glBindVertexArrayOES(vaoName);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, vertCt);
*/

@class GLKEffectPropertyTexture;

NS_ASSUME_NONNULL_BEGIN

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKBaseEffect : NSObject <GLKNamedEffect>
{
    @protected
    
    // Switches to turn effect features on and off
    GLboolean                           _colorMaterialEnabled;
    GLboolean                           _fogEnabled;
    
    // Modelview, projection, texture and derived matrices for transformation
    GLKEffectPropertyTransform          *_transform;

    // Lights
    GLKLightingType                     _lightingType;
    GLKEffectPropertyLight              *_light0, *_light1, *_light2;

    // Material for lighting
    GLKEffectPropertyMaterial           *_material;

    // GL Texture Names
    GLKEffectPropertyTexture            *_texture2d0, *_texture2d1;

    // Texture ordering array
    NSArray                             *_textureOrder;
    
    // Constant color (fixed color value to supplant the use of the "color" named vertex attrib array)
    GLKVector4                          _constantColor;

    // Fog
    GLKEffectPropertyFog                *_fog;
    
    // Label for effect
    NSString                            *_label;
}

// Sync all effect changes for consistent state when drawing
- (void) prepareToDraw;


// Properties                                                                                         // Default Value

@property (nonatomic, assign)         GLboolean                          colorMaterialEnabled;        // GL_FALSE
@property (nonatomic, assign)         GLboolean                          lightModelTwoSided;          // GL_FALSE
@property (nonatomic, assign)         GLboolean                          useConstantColor;            // GL_TRUE

@property (nonatomic, readonly)       GLKEffectPropertyTransform         *transform;                  // Identity Matrices
@property (nonatomic, readonly)       GLKEffectPropertyLight             *light0, *light1, *light2;   // Disabled
@property (nonatomic, assign)         GLKLightingType                    lightingType;                // GLKLightingTypePerVertex
@property (nonatomic, assign)         GLKVector4                         lightModelAmbientColor;      // { 0.2, 0.2, 0.2, 1.0 }
@property (nonatomic, readonly)       GLKEffectPropertyMaterial          *material;                   // Default material state
@property (nonatomic, readonly)       GLKEffectPropertyTexture           *texture2d0, *texture2d1;    // Disabled
@property (nullable, nonatomic, copy) NSArray<GLKEffectPropertyTexture*> *textureOrder;               // texture2d0, texture2d1
@property (nonatomic, assign)         GLKVector4                         constantColor;               // { 1.0, 1.0, 1.0, 1.0 }
@property (nonatomic, readonly)       GLKEffectPropertyFog               *fog;                        // Disabled
@property (nullable, nonatomic, copy) NSString                           *label;                      // @"GLKBaseEffect"

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKEffectPropertyTexture.h
//
//  GLKEffectPropertyTexture.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//
#import <GLKit/GLKitBase.h>
#if TARGET_OS_IPHONE
#import <OpenGLES/ES2/gl.h>
#else // !TARGET_OS_IPHONE
#import <OpenGL/gl3.h>
#endif // !TARGET_OS_IPHONE

#import <GLKit/GLKEffectProperty.h>

NS_ASSUME_NONNULL_BEGIN
// Texture target
typedef NS_ENUM(GLenum, GLKTextureTarget)
{
    GLKTextureTarget2D = GL_TEXTURE_2D,
    GLKTextureTargetCubeMap = GL_TEXTURE_CUBE_MAP,
    GLKTextureTargetCt = 2
} NS_ENUM_AVAILABLE(10_8, 5_0);

// Texture env mode
typedef NS_ENUM(GLint, GLKTextureEnvMode)
{
    GLKTextureEnvModeReplace,
    GLKTextureEnvModeModulate,
    GLKTextureEnvModeDecal
} NS_ENUM_AVAILABLE(10_8, 5_0);


// GLKEffectPropertyTexture
//
// GLKEffectPropertyTexture simply contains properties to configure GL texture rendering.
//

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKEffectPropertyTexture : GLKEffectProperty
{
    // Texture Enabled
    GLboolean           _enabled;

    // Texture Name
    GLuint              _name;

    // Texture Target 2D or Cube Map
    GLKTextureTarget    _target;

    // Texture Env Mode Replace, Modulate or Decal
    GLKTextureEnvMode   _envMode;
}

// Properties                                                  // Default Value
@property (nonatomic, assign) GLboolean            enabled;    // Is this texture enabled
@property (nonatomic, assign) GLuint               name;       // Texture name from glGenTextures()
@property (nonatomic, assign) GLKTextureTarget     target;     // GLKTextureTarget2D
@property (nonatomic, assign) GLKTextureEnvMode    envMode;    // GLKTextureEnvModeModulate

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKMatrix4.h
//
//  GLKMatrix4.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATRIX_4_H
#define __GLK_MATRIX_4_H

#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif


#include <GLKit/GLKMathTypes.h>
#include <GLKit/GLKVector3.h>
#include <GLKit/GLKVector4.h>
#include <GLKit/GLKQuaternion.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
extern const GLKMatrix4 GLKMatrix4Identity;

/*
 m30, m31, and m32 correspond to the translation values tx, ty, tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4Make(float m00, float m01, float m02, float m03,
                                            float m10, float m11, float m12, float m13,
                                            float m20, float m21, float m22, float m23,
                                            float m30, float m31, float m32, float m33);
    
/*
 m03, m13, and m23 correspond to the translation values tx, ty, tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeAndTranspose(float m00, float m01, float m02, float m03,
                                                        float m10, float m11, float m12, float m13,
                                                        float m20, float m21, float m22, float m23,
                                                        float m30, float m31, float m32, float m33);

/*
 m[12], m[13], and m[14] correspond to the translation values tx, ty, and tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArray(float values[16]);

/*
 m[3], m[7], and m[11] correspond to the translation values tx, ty, and tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArrayAndTranspose(float values[16]);
    
/*
 row0, row1, and row2's last component should correspond to the translation values tx, ty, and tz, respectively.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithRows(GLKVector4 row0,
                                                    GLKVector4 row1, 
                                                    GLKVector4 row2,
                                                    GLKVector4 row3);
    
/*
 column3's first three components should correspond to the translation values tx, ty, and tz.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithColumns(GLKVector4 column0,
                                                       GLKVector4 column1, 
                                                       GLKVector4 column2,
                                                       GLKVector4 column3);
    
/*
 The quaternion will be normalized before conversion.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithQuaternion(GLKQuaternion quaternion);
	
GLK_INLINE GLKMatrix4 GLKMatrix4MakeTranslation(float tx, float ty, float tz);
GLK_INLINE GLKMatrix4 GLKMatrix4MakeScale(float sx, float sy, float sz);	
GLK_INLINE GLKMatrix4 GLKMatrix4MakeRotation(float radians, float x, float y, float z);

GLK_INLINE GLKMatrix4 GLKMatrix4MakeXRotation(float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4MakeYRotation(float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4MakeZRotation(float radians);

/*
 Equivalent to gluPerspective.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ);

/*
 Equivalent to glFrustum.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeFrustum(float left, float right,
                                                   float bottom, float top,
                                                   float nearZ, float farZ);

/*
 Equivalent to glOrtho.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeOrtho(float left, float right,
                                                 float bottom, float top,
                                                 float nearZ, float farZ);

/*
 Equivalent to gluLookAt.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4MakeLookAt(float eyeX, float eyeY, float eyeZ,
                                                  float centerX, float centerY, float centerZ,
                                                  float upX, float upY, float upZ);
	
/*
 Returns the upper left 3x3 portion of the 4x4 matrix.
 */
GLK_INLINE GLKMatrix3 GLKMatrix4GetMatrix3(GLKMatrix4 matrix);
/*
 Returns the upper left 2x2 portion of the 4x4 matrix.
 */
GLK_INLINE GLKMatrix2 GLKMatrix4GetMatrix2(GLKMatrix4 matrix);
	
/*
 GLKMatrix4GetRow returns vectors for rows 0, 1, and 2 whose last component will be the translation value tx, ty, and tz, respectively.
 Valid row values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKVector4 GLKMatrix4GetRow(GLKMatrix4 matrix, int row);
/*
 GLKMatrix4GetColumn returns a vector for column 3 whose first three components will be the translation values tx, ty, and tz.
 Valid column values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKVector4 GLKMatrix4GetColumn(GLKMatrix4 matrix, int column);
    
/*
 GLKMatrix4SetRow expects that the vector for row 0, 1, and 2 will have a translation value as its last component.
 Valid row values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4SetRow(GLKMatrix4 matrix, int row, GLKVector4 vector);
/*
 GLKMatrix4SetColumn expects that the vector for column 3 will contain the translation values tx, ty, and tz as its first three components, respectively.
 Valid column values range from 0 to 3, inclusive.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4SetColumn(GLKMatrix4 matrix, int column, GLKVector4 vector);
    
GLK_INLINE GLKMatrix4 GLKMatrix4Transpose(GLKMatrix4 matrix);
    
GLKMatrix4 GLKMatrix4Invert(GLKMatrix4 matrix, bool * __nullable isInvertible);
GLKMatrix4 GLKMatrix4InvertAndTranspose(GLKMatrix4 matrix, bool * __nullable isInvertible);

GLK_INLINE GLKMatrix4 GLKMatrix4Multiply(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);

GLK_INLINE GLKMatrix4 GLKMatrix4Add(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);
GLK_INLINE GLKMatrix4 GLKMatrix4Subtract(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight);
    
GLK_INLINE GLKMatrix4 GLKMatrix4Translate(GLKMatrix4 matrix, float tx, float ty, float tz);
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector3(GLKMatrix4 matrix, GLKVector3 translationVector);
/*
 The last component of the GLKVector4, translationVector, is ignored.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector4(GLKMatrix4 matrix, GLKVector4 translationVector);

GLK_INLINE GLKMatrix4 GLKMatrix4Scale(GLKMatrix4 matrix, float sx, float sy, float sz);
GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector3(GLKMatrix4 matrix, GLKVector3 scaleVector);
/*
 The last component of the GLKVector4, scaleVector, is ignored.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector4(GLKMatrix4 matrix, GLKVector4 scaleVector);
    
GLK_INLINE GLKMatrix4 GLKMatrix4Rotate(GLKMatrix4 matrix, float radians, float x, float y, float z);
GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector3(GLKMatrix4 matrix, float radians, GLKVector3 axisVector);
/*
 The last component of the GLKVector4, axisVector, is ignored.
 */
GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector4(GLKMatrix4 matrix, float radians, GLKVector4 axisVector);
        
GLK_INLINE GLKMatrix4 GLKMatrix4RotateX(GLKMatrix4 matrix, float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4RotateY(GLKMatrix4 matrix, float radians);
GLK_INLINE GLKMatrix4 GLKMatrix4RotateZ(GLKMatrix4 matrix, float radians);

/*
 Assumes 0 in the w component.
 */
GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);
/*
 Assumes 1 in the w component.
 */
GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3WithTranslation(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);
/*
 Assumes 1 in the w component and divides the resulting vector by w before returning.
 */
GLK_INLINE GLKVector3 GLKMatrix4MultiplyAndProjectVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight);

/*
 Assumes 0 in the w component.
 */
GLK_INLINE void GLKMatrix4MultiplyVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount);
/*
 Assumes 1 in the w component.
 */
GLK_INLINE void GLKMatrix4MultiplyVector3ArrayWithTranslation(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount);
/*
 Assumes 1 in the w component and divides the resulting vector by w before returning.
 */
GLK_INLINE void GLKMatrix4MultiplyAndProjectVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount);
    
GLK_INLINE GLKVector4 GLKMatrix4MultiplyVector4(GLKMatrix4 matrixLeft, GLKVector4 vectorRight);

GLK_INLINE void GLKMatrix4MultiplyVector4Array(GLKMatrix4 matrix, GLKVector4 *__nonnull vectors, size_t vectorCount);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKMatrix4 GLKMatrix4Make(float m00, float m01, float m02, float m03,
                                            float m10, float m11, float m12, float m13,
                                            float m20, float m21, float m22, float m23,
                                            float m30, float m31, float m32, float m33)
{
    GLKMatrix4 m = { m00, m01, m02, m03,
                     m10, m11, m12, m13,
                     m20, m21, m22, m23,
                     m30, m31, m32, m33 };
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeAndTranspose(float m00, float m01, float m02, float m03,
                                                        float m10, float m11, float m12, float m13,
                                                        float m20, float m21, float m22, float m23,
                                                        float m30, float m31, float m32, float m33)
{
    GLKMatrix4 m = { m00, m10, m20, m30,
                     m01, m11, m21, m31,
                     m02, m12, m22, m32,
                     m03, m13, m23, m33 };
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArray(float values[16])
{
    GLKMatrix4 m = { values[0], values[1], values[2], values[3],
                     values[4], values[5], values[6], values[7],
                     values[8], values[9], values[10], values[11],
                     values[12], values[13], values[14], values[15] };
    return m;
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithArrayAndTranspose(float values[16])
{
#if defined(__ARM_NEON__)
    float32x4x4_t m = vld4q_f32(values);
    return *(GLKMatrix4 *)&m;
#else
    GLKMatrix4 m = { values[0], values[4], values[8], values[12],
                     values[1], values[5], values[9], values[13],
                     values[2], values[6], values[10], values[14],
                     values[3], values[7], values[11], values[15] };
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithRows(GLKVector4 row0,
                                                    GLKVector4 row1, 
                                                    GLKVector4 row2,
                                                    GLKVector4 row3)
{
    GLKMatrix4 m = { row0.v[0], row1.v[0], row2.v[0], row3.v[0],
                     row0.v[1], row1.v[1], row2.v[1], row3.v[1],
                     row0.v[2], row1.v[2], row2.v[2], row3.v[2],
                     row0.v[3], row1.v[3], row2.v[3], row3.v[3] };
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithColumns(GLKVector4 column0,
                                                       GLKVector4 column1, 
                                                       GLKVector4 column2,
                                                       GLKVector4 column3)
{
#if defined(__ARM_NEON__)
    float32x4x4_t m;
    m.val[0] = vld1q_f32(column0.v);
    m.val[1] = vld1q_f32(column1.v);
    m.val[2] = vld1q_f32(column2.v);
    m.val[3] = vld1q_f32(column3.v);
    return *(GLKMatrix4 *)&m;
#elif defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    *((__m128*)&m.m[0])  = *(__m128*)&column0;
    *((__m128*)&m.m[4])  = *(__m128*)&column1;
    *((__m128*)&m.m[8])  = *(__m128*)&column2;
    *((__m128*)&m.m[12]) = *(__m128*)&column3;
    return m;
#else
    GLKMatrix4 m = { column0.v[0], column0.v[1], column0.v[2], column0.v[3],
                     column1.v[0], column1.v[1], column1.v[2], column1.v[3],
                     column2.v[0], column2.v[1], column2.v[2], column2.v[3],
                     column3.v[0], column3.v[1], column3.v[2], column3.v[3] };
    return m;
#endif
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeWithQuaternion(GLKQuaternion quaternion)
{
    quaternion = GLKQuaternionNormalize(quaternion);
    
    float x = quaternion.q[0];
    float y = quaternion.q[1];
    float z = quaternion.q[2];
    float w = quaternion.q[3];
    
    float _2x = x + x;
    float _2y = y + y;
    float _2z = z + z;
    float _2w = w + w;
    
    GLKMatrix4 m = { 1.0f - _2y * y - _2z * z,
                     _2x * y + _2w * z,
                     _2x * z - _2w * y,
                     0.0f,
                     _2x * y - _2w * z,
                     1.0f - _2x * x - _2z * z,
                     _2y * z + _2w * x,
                     0.0f,
                     _2x * z + _2w * y,
                     _2y * z - _2w * x,
                     1.0f - _2x * x - _2y * y,
                     0.0f,
                     0.0f,
                     0.0f,
                     0.0f,
                     1.0f };
    
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeTranslation(float tx, float ty, float tz)
{
    GLKMatrix4 m = GLKMatrix4Identity;
    m.m[12] = tx;
    m.m[13] = ty;
    m.m[14] = tz;
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeScale(float sx, float sy, float sz)
{
    GLKMatrix4 m = GLKMatrix4Identity;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeRotation(float radians, float x, float y, float z)
{
    GLKVector3 v = GLKVector3Normalize(GLKVector3Make(x, y, z));
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    GLKMatrix4 m = { cos + cosp * v.v[0] * v.v[0],
                     cosp * v.v[0] * v.v[1] + v.v[2] * sin,
                     cosp * v.v[0] * v.v[2] - v.v[1] * sin,
                     0.0f,
                     cosp * v.v[0] * v.v[1] - v.v[2] * sin,
                     cos + cosp * v.v[1] * v.v[1],
                     cosp * v.v[1] * v.v[2] + v.v[0] * sin,
                     0.0f,
                     cosp * v.v[0] * v.v[2] + v.v[1] * sin,
                     cosp * v.v[1] * v.v[2] - v.v[0] * sin,
                     cos + cosp * v.v[2] * v.v[2],
                     0.0f,
                     0.0f,
                     0.0f,
                     0.0f,
                     1.0f };

    return m;
}
   
GLK_INLINE GLKMatrix4 GLKMatrix4MakeXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix4 m = { 1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, cos, sin, 0.0f,
                     0.0f, -sin, cos, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix4 m = { cos, 0.0f, -sin, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     sin, 0.0f, cos, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

GLK_INLINE GLKMatrix4 GLKMatrix4MakeZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    GLKMatrix4 m = { cos, sin, 0.0f, 0.0f,
                     -sin, cos, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float cotan = 1.0f / tanf(fovyRadians / 2.0f);
    
    GLKMatrix4 m = { cotan / aspect, 0.0f, 0.0f, 0.0f,
                     0.0f, cotan, 0.0f, 0.0f,
                     0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
                     0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f };
    
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeFrustum(float left, float right,
                                                   float bottom, float top,
                                                   float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tsb = top - bottom;
    float tab = top + bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    GLKMatrix4 m = { 2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
                     0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
                     ral / rsl, tab / tsb, -fan / fsn, -1.0f,
                     0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f };
    
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4MakeOrtho(float left, float right,
                                                 float bottom, float top,
                                                 float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    GLKMatrix4 m = { 2.0f / rsl, 0.0f, 0.0f, 0.0f,
                     0.0f, 2.0f / tsb, 0.0f, 0.0f,
                     0.0f, 0.0f, -2.0f / fsn, 0.0f,
                     -ral / rsl, -tab / tsb, -fan / fsn, 1.0f };
                     
    return m;
}
   
GLK_INLINE GLKMatrix4 GLKMatrix4MakeLookAt(float eyeX, float eyeY, float eyeZ,
                                                  float centerX, float centerY, float centerZ,
                                                  float upX, float upY, float upZ)
{
    GLKVector3 ev = { eyeX, eyeY, eyeZ };
    GLKVector3 cv = { centerX, centerY, centerZ };
    GLKVector3 uv = { upX, upY, upZ };
    GLKVector3 n = GLKVector3Normalize(GLKVector3Add(ev, GLKVector3Negate(cv)));
    GLKVector3 u = GLKVector3Normalize(GLKVector3CrossProduct(uv, n));
    GLKVector3 v = GLKVector3CrossProduct(n, u);
    
    GLKMatrix4 m = { u.v[0], v.v[0], n.v[0], 0.0f,
                     u.v[1], v.v[1], n.v[1], 0.0f,
                     u.v[2], v.v[2], n.v[2], 0.0f,
                     GLKVector3DotProduct(GLKVector3Negate(u), ev),
                     GLKVector3DotProduct(GLKVector3Negate(v), ev),
                     GLKVector3DotProduct(GLKVector3Negate(n), ev),
                     1.0f };
    
    return m;
}
  
GLK_INLINE GLKMatrix3 GLKMatrix4GetMatrix3(GLKMatrix4 matrix)
{
    GLKMatrix3 m = { matrix.m[0], matrix.m[1], matrix.m[2],
                     matrix.m[4], matrix.m[5], matrix.m[6],
                     matrix.m[8], matrix.m[9], matrix.m[10] };
    return m;
}

GLK_INLINE GLKMatrix2 GLKMatrix4GetMatrix2(GLKMatrix4 matrix)
{
    GLKMatrix2 m = { matrix.m[0], matrix.m[1],
                     matrix.m[4], matrix.m[5] };
    return m;
}

GLK_INLINE GLKVector4 GLKMatrix4GetRow(GLKMatrix4 matrix, int row)
{
    GLKVector4 v = { matrix.m[row], matrix.m[4 + row], matrix.m[8 + row], matrix.m[12 + row] };
    return v;
}

GLK_INLINE GLKVector4 GLKMatrix4GetColumn(GLKMatrix4 matrix, int column)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vld1q_f32(&(matrix.m[column * 4]));
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&matrix.m[column * 4]);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { matrix.m[column * 4 + 0], matrix.m[column * 4 + 1], matrix.m[column * 4 + 2], matrix.m[column * 4 + 3] };
    return v;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4SetRow(GLKMatrix4 matrix, int row, GLKVector4 vector)
{
    matrix.m[row] = vector.v[0];
    matrix.m[row + 4] = vector.v[1];
    matrix.m[row + 8] = vector.v[2];
    matrix.m[row + 12] = vector.v[3];
    
    return matrix;
}

GLK_INLINE GLKMatrix4 GLKMatrix4SetColumn(GLKMatrix4 matrix, int column, GLKVector4 vector)
{
#if defined(__ARM_NEON__)
    float *dst = &(matrix.m[column * 4]);
    vst1q_f32(dst, vld1q_f32(vector.v));
    return matrix;
#elif defined(GLK_SSE3_INTRINSICS)
    *((__m128*)&matrix.m[column*4]) = *(__m128*)&vector;
    return matrix;
#else
    matrix.m[column * 4 + 0] = vector.v[0];
    matrix.m[column * 4 + 1] = vector.v[1];
    matrix.m[column * 4 + 2] = vector.v[2];
    matrix.m[column * 4 + 3] = vector.v[3];
    
    return matrix;
#endif
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4Transpose(GLKMatrix4 matrix)
{
#if defined(__ARM_NEON__)
    float32x4x4_t m = vld4q_f32(matrix.m);
    return *(GLKMatrix4 *)&m;
#else
    GLKMatrix4 m = { matrix.m[0], matrix.m[4], matrix.m[8], matrix.m[12],
                     matrix.m[1], matrix.m[5], matrix.m[9], matrix.m[13],
                     matrix.m[2], matrix.m[6], matrix.m[10], matrix.m[14],
                     matrix.m[3], matrix.m[7], matrix.m[11], matrix.m[15] };
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4Multiply(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrixLeft = *(float32x4x4_t *)&matrixLeft;
    float32x4x4_t iMatrixRight = *(float32x4x4_t *)&matrixRight;
    float32x4x4_t m;

    m.val[0] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[0], 0));
    m.val[1] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[1], 0));
    m.val[2] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[2], 0));
    m.val[3] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[3], 0));

    m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[0], 1));
    m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[1], 1));
    m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[2], 1));
    m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[3], 1));

    m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[0], 2));
    m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[1], 2));
    m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[2], 2));
    m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[3], 2));

    m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[0], 3));
    m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[1], 3));
    m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[2], 3));
    m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[3], 3));

    return *(GLKMatrix4 *)&m;
#elif defined(GLK_SSE3_INTRINSICS)
    
	const __m128 l0 = _mm_load_ps(&matrixLeft.m[0]);
	const __m128 l1 = _mm_load_ps(&matrixLeft.m[4]);
	const __m128 l2 = _mm_load_ps(&matrixLeft.m[8]);
	const __m128 l3 = _mm_load_ps(&matrixLeft.m[12]);

	const __m128 r0 = _mm_load_ps(&matrixRight.m[0]);
	const __m128 r1 = _mm_load_ps(&matrixRight.m[4]);
	const __m128 r2 = _mm_load_ps(&matrixRight.m[8]);
	const __m128 r3 = _mm_load_ps(&matrixRight.m[12]);
	
	const __m128 m0 = l0 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(3, 3, 3, 3));

	const __m128 m1 = l0 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(3, 3, 3, 3));

	const __m128 m2 = l0 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 3, 3, 3));

	const __m128 m3 = l0 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(0, 0, 0, 0))
					+ l1 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(1, 1, 1, 1))
					+ l2 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(2, 2, 2, 2))
					+ l3 * _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(3, 3, 3, 3));
				
	GLKMatrix4 m;
	_mm_store_ps(&m.m[0], m0);
	_mm_store_ps(&m.m[4], m1);
	_mm_store_ps(&m.m[8], m2);
	_mm_store_ps(&m.m[12], m3);
    return m;

#else
    GLKMatrix4 m;
    
    m.m[0]  = matrixLeft.m[0] * matrixRight.m[0]  + matrixLeft.m[4] * matrixRight.m[1]  + matrixLeft.m[8] * matrixRight.m[2]   + matrixLeft.m[12] * matrixRight.m[3];
	m.m[4]  = matrixLeft.m[0] * matrixRight.m[4]  + matrixLeft.m[4] * matrixRight.m[5]  + matrixLeft.m[8] * matrixRight.m[6]   + matrixLeft.m[12] * matrixRight.m[7];
	m.m[8]  = matrixLeft.m[0] * matrixRight.m[8]  + matrixLeft.m[4] * matrixRight.m[9]  + matrixLeft.m[8] * matrixRight.m[10]  + matrixLeft.m[12] * matrixRight.m[11];
	m.m[12] = matrixLeft.m[0] * matrixRight.m[12] + matrixLeft.m[4] * matrixRight.m[13] + matrixLeft.m[8] * matrixRight.m[14]  + matrixLeft.m[12] * matrixRight.m[15];
    
	m.m[1]  = matrixLeft.m[1] * matrixRight.m[0]  + matrixLeft.m[5] * matrixRight.m[1]  + matrixLeft.m[9] * matrixRight.m[2]   + matrixLeft.m[13] * matrixRight.m[3];
	m.m[5]  = matrixLeft.m[1] * matrixRight.m[4]  + matrixLeft.m[5] * matrixRight.m[5]  + matrixLeft.m[9] * matrixRight.m[6]   + matrixLeft.m[13] * matrixRight.m[7];
	m.m[9]  = matrixLeft.m[1] * matrixRight.m[8]  + matrixLeft.m[5] * matrixRight.m[9]  + matrixLeft.m[9] * matrixRight.m[10]  + matrixLeft.m[13] * matrixRight.m[11];
	m.m[13] = matrixLeft.m[1] * matrixRight.m[12] + matrixLeft.m[5] * matrixRight.m[13] + matrixLeft.m[9] * matrixRight.m[14]  + matrixLeft.m[13] * matrixRight.m[15];
    
	m.m[2]  = matrixLeft.m[2] * matrixRight.m[0]  + matrixLeft.m[6] * matrixRight.m[1]  + matrixLeft.m[10] * matrixRight.m[2]  + matrixLeft.m[14] * matrixRight.m[3];
	m.m[6]  = matrixLeft.m[2] * matrixRight.m[4]  + matrixLeft.m[6] * matrixRight.m[5]  + matrixLeft.m[10] * matrixRight.m[6]  + matrixLeft.m[14] * matrixRight.m[7];
	m.m[10] = matrixLeft.m[2] * matrixRight.m[8]  + matrixLeft.m[6] * matrixRight.m[9]  + matrixLeft.m[10] * matrixRight.m[10] + matrixLeft.m[14] * matrixRight.m[11];
	m.m[14] = matrixLeft.m[2] * matrixRight.m[12] + matrixLeft.m[6] * matrixRight.m[13] + matrixLeft.m[10] * matrixRight.m[14] + matrixLeft.m[14] * matrixRight.m[15];
    
	m.m[3]  = matrixLeft.m[3] * matrixRight.m[0]  + matrixLeft.m[7] * matrixRight.m[1]  + matrixLeft.m[11] * matrixRight.m[2]  + matrixLeft.m[15] * matrixRight.m[3];
	m.m[7]  = matrixLeft.m[3] * matrixRight.m[4]  + matrixLeft.m[7] * matrixRight.m[5]  + matrixLeft.m[11] * matrixRight.m[6]  + matrixLeft.m[15] * matrixRight.m[7];
	m.m[11] = matrixLeft.m[3] * matrixRight.m[8]  + matrixLeft.m[7] * matrixRight.m[9]  + matrixLeft.m[11] * matrixRight.m[10] + matrixLeft.m[15] * matrixRight.m[11];
	m.m[15] = matrixLeft.m[3] * matrixRight.m[12] + matrixLeft.m[7] * matrixRight.m[13] + matrixLeft.m[11] * matrixRight.m[14] + matrixLeft.m[15] * matrixRight.m[15];
    
    return m;
#endif
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4Add(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrixLeft = *(float32x4x4_t *)&matrixLeft;
    float32x4x4_t iMatrixRight = *(float32x4x4_t *)&matrixRight;
    float32x4x4_t m;
    
    m.val[0] = vaddq_f32(iMatrixLeft.val[0], iMatrixRight.val[0]);
    m.val[1] = vaddq_f32(iMatrixLeft.val[1], iMatrixRight.val[1]);
    m.val[2] = vaddq_f32(iMatrixLeft.val[2], iMatrixRight.val[2]);
    m.val[3] = vaddq_f32(iMatrixLeft.val[3], iMatrixRight.val[3]);
    
    return *(GLKMatrix4 *)&m;
#elif defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrixLeft.m[0])  + _mm_load_ps(&matrixRight.m[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrixLeft.m[4])  + _mm_load_ps(&matrixRight.m[4]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrixLeft.m[8])  + _mm_load_ps(&matrixRight.m[8]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrixLeft.m[12]) + _mm_load_ps(&matrixRight.m[12]));
	    
    return m;
#else
    GLKMatrix4 m;
    
    m.m[0] = matrixLeft.m[0] + matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] + matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] + matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] + matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] + matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] + matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] + matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] + matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] + matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] + matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] + matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] + matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] + matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] + matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] + matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] + matrixRight.m[15];
    
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4Subtract(GLKMatrix4 matrixLeft, GLKMatrix4 matrixRight)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrixLeft = *(float32x4x4_t *)&matrixLeft;
    float32x4x4_t iMatrixRight = *(float32x4x4_t *)&matrixRight;
    float32x4x4_t m;
    
    m.val[0] = vsubq_f32(iMatrixLeft.val[0], iMatrixRight.val[0]);
    m.val[1] = vsubq_f32(iMatrixLeft.val[1], iMatrixRight.val[1]);
    m.val[2] = vsubq_f32(iMatrixLeft.val[2], iMatrixRight.val[2]);
    m.val[3] = vsubq_f32(iMatrixLeft.val[3], iMatrixRight.val[3]);
    
    return *(GLKMatrix4 *)&m;
#elif defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrixLeft.m[0])  - _mm_load_ps(&matrixRight.m[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrixLeft.m[4])  - _mm_load_ps(&matrixRight.m[4]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrixLeft.m[8])  - _mm_load_ps(&matrixRight.m[8]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrixLeft.m[12]) - _mm_load_ps(&matrixRight.m[12]));
	    
    return m;
#else
    GLKMatrix4 m;
    
    m.m[0] = matrixLeft.m[0] - matrixRight.m[0];
    m.m[1] = matrixLeft.m[1] - matrixRight.m[1];
    m.m[2] = matrixLeft.m[2] - matrixRight.m[2];
    m.m[3] = matrixLeft.m[3] - matrixRight.m[3];
    
    m.m[4] = matrixLeft.m[4] - matrixRight.m[4];
    m.m[5] = matrixLeft.m[5] - matrixRight.m[5];
    m.m[6] = matrixLeft.m[6] - matrixRight.m[6];
    m.m[7] = matrixLeft.m[7] - matrixRight.m[7];
    
    m.m[8] = matrixLeft.m[8] - matrixRight.m[8];
    m.m[9] = matrixLeft.m[9] - matrixRight.m[9];
    m.m[10] = matrixLeft.m[10] - matrixRight.m[10];
    m.m[11] = matrixLeft.m[11] - matrixRight.m[11];
    
    m.m[12] = matrixLeft.m[12] - matrixRight.m[12];
    m.m[13] = matrixLeft.m[13] - matrixRight.m[13];
    m.m[14] = matrixLeft.m[14] - matrixRight.m[14];
    m.m[15] = matrixLeft.m[15] - matrixRight.m[15];
    
    return m;
#endif
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4Translate(GLKMatrix4 matrix, float tx, float ty, float tz)
{
    GLKMatrix4 m = { matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                     matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                     matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                     matrix.m[0] * tx + matrix.m[4] * ty + matrix.m[8] * tz + matrix.m[12],
                     matrix.m[1] * tx + matrix.m[5] * ty + matrix.m[9] * tz + matrix.m[13],
                     matrix.m[2] * tx + matrix.m[6] * ty + matrix.m[10] * tz + matrix.m[14],
                     matrix.m[3] * tx + matrix.m[7] * ty + matrix.m[11] * tz + matrix.m[15] };
    return m;
}
 
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector3(GLKMatrix4 matrix, GLKVector3 translationVector)
{
    GLKMatrix4 m = { matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                     matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                     matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                     matrix.m[0] * translationVector.v[0] + matrix.m[4] * translationVector.v[1] + matrix.m[8] * translationVector.v[2] + matrix.m[12],
                     matrix.m[1] * translationVector.v[0] + matrix.m[5] * translationVector.v[1] + matrix.m[9] * translationVector.v[2] + matrix.m[13],
                     matrix.m[2] * translationVector.v[0] + matrix.m[6] * translationVector.v[1] + matrix.m[10] * translationVector.v[2] + matrix.m[14],
                     matrix.m[3] * translationVector.v[0] + matrix.m[7] * translationVector.v[1] + matrix.m[11] * translationVector.v[2] + matrix.m[15] };
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4TranslateWithVector4(GLKMatrix4 matrix, GLKVector4 translationVector)
{
    GLKMatrix4 m = { matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
                     matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
                     matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
                     matrix.m[0] * translationVector.v[0] + matrix.m[4] * translationVector.v[1] + matrix.m[8] * translationVector.v[2] + matrix.m[12],
                     matrix.m[1] * translationVector.v[0] + matrix.m[5] * translationVector.v[1] + matrix.m[9] * translationVector.v[2] + matrix.m[13],
                     matrix.m[2] * translationVector.v[0] + matrix.m[6] * translationVector.v[1] + matrix.m[10] * translationVector.v[2] + matrix.m[14],
                     matrix.m[3] * translationVector.v[0] + matrix.m[7] * translationVector.v[1] + matrix.m[11] * translationVector.v[2] + matrix.m[15] };
    return m;
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4Scale(GLKMatrix4 matrix, float sx, float sy, float sz)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrix = *(float32x4x4_t *)&matrix;
    float32x4x4_t m;
    
    m.val[0] = vmulq_n_f32(iMatrix.val[0], (float32_t)sx);
    m.val[1] = vmulq_n_f32(iMatrix.val[1], (float32_t)sy);
    m.val[2] = vmulq_n_f32(iMatrix.val[2], (float32_t)sz);
    m.val[3] = iMatrix.val[3];
    
    return *(GLKMatrix4 *)&m;
#elif defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrix.m[0])  * _mm_load1_ps(&sx));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrix.m[4])  * _mm_load1_ps(&sy));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrix.m[8])  * _mm_load1_ps(&sz));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrix.m[12]));
	    
    return m;
#else
    GLKMatrix4 m = { matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx, matrix.m[3] * sx,
                     matrix.m[4] * sy, matrix.m[5] * sy, matrix.m[6] * sy, matrix.m[7] * sy,
                     matrix.m[8] * sz, matrix.m[9] * sz, matrix.m[10] * sz, matrix.m[11] * sz,
                     matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] };
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector3(GLKMatrix4 matrix, GLKVector3 scaleVector)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrix = *(float32x4x4_t *)&matrix;
    float32x4x4_t m;
    
    m.val[0] = vmulq_n_f32(iMatrix.val[0], (float32_t)scaleVector.v[0]);
    m.val[1] = vmulq_n_f32(iMatrix.val[1], (float32_t)scaleVector.v[1]);
    m.val[2] = vmulq_n_f32(iMatrix.val[2], (float32_t)scaleVector.v[2]);
    m.val[3] = iMatrix.val[3];
    
    return *(GLKMatrix4 *)&m;
#elif defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrix.m[0])  * _mm_load1_ps(&scaleVector.v[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrix.m[4])  * _mm_load1_ps(&scaleVector.v[1]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrix.m[8])  * _mm_load1_ps(&scaleVector.v[2]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrix.m[12]));
	    
    return m;
#else
    GLKMatrix4 m = { matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0], matrix.m[3] * scaleVector.v[0],
                     matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1], matrix.m[6] * scaleVector.v[1], matrix.m[7] * scaleVector.v[1],
                     matrix.m[8] * scaleVector.v[2], matrix.m[9] * scaleVector.v[2], matrix.m[10] * scaleVector.v[2], matrix.m[11] * scaleVector.v[2],
                     matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] };
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4ScaleWithVector4(GLKMatrix4 matrix, GLKVector4 scaleVector)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrix = *(float32x4x4_t *)&matrix;
    float32x4x4_t m;
    
    m.val[0] = vmulq_n_f32(iMatrix.val[0], (float32_t)scaleVector.v[0]);
    m.val[1] = vmulq_n_f32(iMatrix.val[1], (float32_t)scaleVector.v[1]);
    m.val[2] = vmulq_n_f32(iMatrix.val[2], (float32_t)scaleVector.v[2]);
    m.val[3] = iMatrix.val[3];
    
    return *(GLKMatrix4 *)&m;
#elif defined(GLK_SSE3_INTRINSICS)
    GLKMatrix4 m;
    
    _mm_store_ps(&m.m[0],  _mm_load_ps(&matrix.m[0])  * _mm_load1_ps(&scaleVector.v[0]));
    _mm_store_ps(&m.m[4],  _mm_load_ps(&matrix.m[4])  * _mm_load1_ps(&scaleVector.v[1]));
    _mm_store_ps(&m.m[8],  _mm_load_ps(&matrix.m[8])  * _mm_load1_ps(&scaleVector.v[2]));
    _mm_store_ps(&m.m[12], _mm_load_ps(&matrix.m[12]));
	    
    return m;
#else
    GLKMatrix4 m = { matrix.m[0] * scaleVector.v[0], matrix.m[1] * scaleVector.v[0], matrix.m[2] * scaleVector.v[0], matrix.m[3] * scaleVector.v[0],
                     matrix.m[4] * scaleVector.v[1], matrix.m[5] * scaleVector.v[1], matrix.m[6] * scaleVector.v[1], matrix.m[7] * scaleVector.v[1],
                     matrix.m[8] * scaleVector.v[2], matrix.m[9] * scaleVector.v[2], matrix.m[10] * scaleVector.v[2], matrix.m[11] * scaleVector.v[2],
                     matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] };
    return m;
#endif
}

GLK_INLINE GLKMatrix4 GLKMatrix4Rotate(GLKMatrix4 matrix, float radians, float x, float y, float z)
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(radians, x, y, z);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector3(GLKMatrix4 matrix, float radians, GLKVector3 axisVector)
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateWithVector4(GLKMatrix4 matrix, float radians, GLKVector4 axisVector)
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
    return GLKMatrix4Multiply(matrix, rm);    
}
    
GLK_INLINE GLKMatrix4 GLKMatrix4RotateX(GLKMatrix4 matrix, float radians)
{
    GLKMatrix4 rm = GLKMatrix4MakeXRotation(radians);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateY(GLKMatrix4 matrix, float radians)
{
    GLKMatrix4 rm = GLKMatrix4MakeYRotation(radians);
    return GLKMatrix4Multiply(matrix, rm);
}

GLK_INLINE GLKMatrix4 GLKMatrix4RotateZ(GLKMatrix4 matrix, float radians)
{
    GLKMatrix4 rm = GLKMatrix4MakeZRotation(radians);
    return GLKMatrix4Multiply(matrix, rm);
}
    
GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight)
{
    GLKVector4 v4 = GLKMatrix4MultiplyVector4(matrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 0.0f));
    return GLKVector3Make(v4.v[0], v4.v[1], v4.v[2]);
}

GLK_INLINE GLKVector3 GLKMatrix4MultiplyVector3WithTranslation(GLKMatrix4 matrixLeft, GLKVector3 vectorRight)
{
    GLKVector4 v4 = GLKMatrix4MultiplyVector4(matrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 1.0f));
    return GLKVector3Make(v4.v[0], v4.v[1], v4.v[2]);
}
    
GLK_INLINE GLKVector3 GLKMatrix4MultiplyAndProjectVector3(GLKMatrix4 matrixLeft, GLKVector3 vectorRight)
{
    GLKVector4 v4 = GLKMatrix4MultiplyVector4(matrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 1.0f));
    return GLKVector3MultiplyScalar(GLKVector3Make(v4.v[0], v4.v[1], v4.v[2]), 1.0f / v4.v[3]);
}

GLK_INLINE void GLKMatrix4MultiplyVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyVector3(matrix, vectors[i]);
}

GLK_INLINE void GLKMatrix4MultiplyVector3ArrayWithTranslation(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyVector3WithTranslation(matrix, vectors[i]);
}
    
GLK_INLINE void GLKMatrix4MultiplyAndProjectVector3Array(GLKMatrix4 matrix, GLKVector3 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyAndProjectVector3(matrix, vectors[i]);
}

GLK_INLINE GLKVector4 GLKMatrix4MultiplyVector4(GLKMatrix4 matrixLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4x4_t iMatrix = *(float32x4x4_t *)&matrixLeft;
    float32x4_t v;
    
    iMatrix.val[0] = vmulq_n_f32(iMatrix.val[0], (float32_t)vectorRight.v[0]);
    iMatrix.val[1] = vmulq_n_f32(iMatrix.val[1], (float32_t)vectorRight.v[1]);
    iMatrix.val[2] = vmulq_n_f32(iMatrix.val[2], (float32_t)vectorRight.v[2]);
    iMatrix.val[3] = vmulq_n_f32(iMatrix.val[3], (float32_t)vectorRight.v[3]);
    
    iMatrix.val[0] = vaddq_f32(iMatrix.val[0], iMatrix.val[1]);
    iMatrix.val[2] = vaddq_f32(iMatrix.val[2], iMatrix.val[3]);
    
    v = vaddq_f32(iMatrix.val[0], iMatrix.val[2]);
    
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 v = _mm_load_ps(&vectorRight.v[0]);

	const __m128 r = _mm_load_ps(&matrixLeft.m[0])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0))
	               + _mm_load_ps(&matrixLeft.m[4])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))
	               + _mm_load_ps(&matrixLeft.m[8])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))
	               + _mm_load_ps(&matrixLeft.m[12]) * _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
    
	GLKVector4 ret;
	*(__m128*)&ret = r;
    return ret;
#else
    GLKVector4 v = { matrixLeft.m[0] * vectorRight.v[0] + matrixLeft.m[4] * vectorRight.v[1] + matrixLeft.m[8] * vectorRight.v[2] + matrixLeft.m[12] * vectorRight.v[3],
                     matrixLeft.m[1] * vectorRight.v[0] + matrixLeft.m[5] * vectorRight.v[1] + matrixLeft.m[9] * vectorRight.v[2] + matrixLeft.m[13] * vectorRight.v[3],
                     matrixLeft.m[2] * vectorRight.v[0] + matrixLeft.m[6] * vectorRight.v[1] + matrixLeft.m[10] * vectorRight.v[2] + matrixLeft.m[14] * vectorRight.v[3],
                     matrixLeft.m[3] * vectorRight.v[0] + matrixLeft.m[7] * vectorRight.v[1] + matrixLeft.m[11] * vectorRight.v[2] + matrixLeft.m[15] * vectorRight.v[3] };
    return v;
#endif
}

GLK_INLINE void GLKMatrix4MultiplyVector4Array(GLKMatrix4 matrix, GLKVector4 *__nonnull vectors, size_t vectorCount)
{
    int i;
    for (i=0; i < vectorCount; i++)
        vectors[i] = GLKMatrix4MultiplyVector4(matrix, vectors[i]);
}
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATRIX_4_H */
// ==========  GLKit.framework/Headers/GLKEffectPropertyMaterial.h
//
//  GLKEffectPropertyMaterial.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//
#import <GLKit/GLKitBase.h>
#import <GLKit/GLKEffectProperty.h>

/*
 GLKEffectPropertyMaterial

 GLKEffectPropertyMaterial encapsulates material properties for an GLKEffect in
 accordance with the specification and lighting behavior of OpenGL ES 1.1.
*/
NS_ASSUME_NONNULL_BEGIN

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKEffectPropertyMaterial : GLKEffectProperty
{    
    @private
    
    // Material parameters
    GLKVector4      _ambientColor, _diffuseColor, _specularColor, _emissiveColor;
    GLfloat         _shininess;
}

// Properties                                                          // Default Values
@property (nonatomic, assign) GLKVector4       ambientColor;           // { 0.2, 0.2, 0.2, 1.0}
@property (nonatomic, assign) GLKVector4       diffuseColor;           // { 0.8, 0.8, 0.8, 1.0}
@property (nonatomic, assign) GLKVector4       specularColor;          // { 0.0, 0.0, 0.0, 1.0}
@property (nonatomic, assign) GLKVector4       emissiveColor;          // { 0.0, 0.0, 0.0, 1.0}
@property (nonatomic, assign) GLfloat          shininess;              // 0.0

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKVector4.h
//
//  GLKVector4.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_VECTOR_4_H
#define __GLK_VECTOR_4_H

#include <stdbool.h>
#include <math.h>

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#include <GLKit/GLKMathTypes.h>


#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
GLK_INLINE GLKVector4 GLKVector4Make(float x, float y, float z, float w);
GLK_INLINE GLKVector4 GLKVector4MakeWithArray(float values[4]);
GLK_INLINE GLKVector4 GLKVector4MakeWithVector3(GLKVector3 vector, float w);

GLK_INLINE GLKVector4 GLKVector4Negate(GLKVector4 vector);

GLK_INLINE GLKVector4 GLKVector4Add(GLKVector4 vectorLeft, GLKVector4 vectorRight);
GLK_INLINE GLKVector4 GLKVector4Subtract(GLKVector4 vectorLeft, GLKVector4 vectorRight);
GLK_INLINE GLKVector4 GLKVector4Multiply(GLKVector4 vectorLeft, GLKVector4 vectorRight);
GLK_INLINE GLKVector4 GLKVector4Divide(GLKVector4 vectorLeft, GLKVector4 vectorRight);
        
GLK_INLINE GLKVector4 GLKVector4AddScalar(GLKVector4 vector, float value);
GLK_INLINE GLKVector4 GLKVector4SubtractScalar(GLKVector4 vector, float value);
GLK_INLINE GLKVector4 GLKVector4MultiplyScalar(GLKVector4 vector, float value);
GLK_INLINE GLKVector4 GLKVector4DivideScalar(GLKVector4 vector, float value);
	
/*
 Returns a vector whose elements are the larger of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector4 GLKVector4Maximum(GLKVector4 vectorLeft, GLKVector4 vectorRight);
/*
 Returns a vector whose elements are the smaller of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector4 GLKVector4Minimum(GLKVector4 vectorLeft, GLKVector4 vectorRight);

/*
 Returns true if all of the first vector's elements are equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector4AllEqualToVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight);
/*
 Returns true if all of the vector's elements are equal to the provided value.
 */
GLK_INLINE bool GLKVector4AllEqualToScalar(GLKVector4 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector4AllGreaterThanVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight);
/*
 Returns true if all of the vector's elements are greater than the provided value.
 */
GLK_INLINE bool GLKVector4AllGreaterThanScalar(GLKVector4 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than or equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector4AllGreaterThanOrEqualToVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight);
/*
 Returns true if all of the vector's elements are greater than or equal to the provided value.
 */
GLK_INLINE bool GLKVector4AllGreaterThanOrEqualToScalar(GLKVector4 vector, float value);
    
GLK_INLINE GLKVector4 GLKVector4Normalize(GLKVector4 vector);

GLK_INLINE float GLKVector4DotProduct(GLKVector4 vectorLeft, GLKVector4 vectorRight);
GLK_INLINE float GLKVector4Length(GLKVector4 vector);
GLK_INLINE float GLKVector4Distance(GLKVector4 vectorStart, GLKVector4 vectorEnd);

GLK_INLINE GLKVector4 GLKVector4Lerp(GLKVector4 vectorStart, GLKVector4 vectorEnd, float t);

/*
 Performs a 3D cross product. The last component of the resulting cross product will be zeroed out.
 */
GLK_INLINE GLKVector4 GLKVector4CrossProduct(GLKVector4 vectorLeft, GLKVector4 vectorRight);
	
/*
 Project the vector, vectorToProject, onto the vector, projectionVector.
 */
GLK_INLINE GLKVector4 GLKVector4Project(GLKVector4 vectorToProject, GLKVector4 projectionVector);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKVector4 GLKVector4Make(float x, float y, float z, float w)
{
    GLKVector4 v = { x, y, z, w };
    return v;
}

GLK_INLINE GLKVector4 GLKVector4MakeWithArray(float values[4])
{
#if defined(__ARM_NEON__)
    float32x4_t v = vld1q_f32(values);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(values);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { values[0], values[1], values[2], values[3] };
    return v;
#endif
}
    
GLK_INLINE GLKVector4 GLKVector4MakeWithVector3(GLKVector3 vector, float w)
{
    GLKVector4 v = { vector.v[0], vector.v[1], vector.v[2], w };
    return v;
}
    
GLK_INLINE GLKVector4 GLKVector4Negate(GLKVector4 vector)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vnegq_f32(*(float32x4_t *)&vector);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_set1_ps(0) - _mm_load_ps(&vector.v[0]);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { -vector.v[0], -vector.v[1], -vector.v[2], -vector.v[3] };
    return v;
#endif
}

GLK_INLINE GLKVector4 GLKVector4Add(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vaddq_f32(*(float32x4_t *)&vectorLeft,
                              *(float32x4_t *)&vectorRight);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vectorLeft.v[0]) + _mm_load_ps(&vectorRight.v[0]);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1],
                     vectorLeft.v[2] + vectorRight.v[2],
                     vectorLeft.v[3] + vectorRight.v[3] };
    return v;
#endif
}

GLK_INLINE GLKVector4 GLKVector4Subtract(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vsubq_f32(*(float32x4_t *)&vectorLeft,
                              *(float32x4_t *)&vectorRight);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vectorLeft.v[0]) - _mm_load_ps(&vectorRight.v[0]);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1],
                     vectorLeft.v[2] - vectorRight.v[2],
                     vectorLeft.v[3] - vectorRight.v[3] };
    return v;
#endif
}

GLK_INLINE GLKVector4 GLKVector4Multiply(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&vectorLeft,
                              *(float32x4_t *)&vectorRight);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vectorLeft.v[0]) * _mm_load_ps(&vectorRight.v[0]);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[2],
                     vectorLeft.v[3] * vectorRight.v[3] };
    return v;
#endif
}

GLK_INLINE GLKVector4 GLKVector4Divide(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t *vLeft = (float32x4_t *)&vectorLeft;
    float32x4_t *vRight = (float32x4_t *)&vectorRight;
    float32x4_t estimate = vrecpeq_f32(*vRight);    
    estimate = vmulq_f32(vrecpsq_f32(*vRight, estimate), estimate);
    estimate = vmulq_f32(vrecpsq_f32(*vRight, estimate), estimate);
    float32x4_t v = vmulq_f32(*vLeft, estimate);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vectorLeft.v[0]) / _mm_load_ps(&vectorRight.v[0]);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1],
                     vectorLeft.v[2] / vectorRight.v[2],
                     vectorLeft.v[3] / vectorRight.v[3] };
    return v;
#endif
}

GLK_INLINE GLKVector4 GLKVector4AddScalar(GLKVector4 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vaddq_f32(*(float32x4_t *)&vector,
                              vdupq_n_f32((float32_t)value));
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vector.v[0]) + _mm_set1_ps(value);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vector.v[0] + value,
                     vector.v[1] + value,
                     vector.v[2] + value,
                     vector.v[3] + value };
    return v;
#endif
}

GLK_INLINE GLKVector4 GLKVector4SubtractScalar(GLKVector4 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vsubq_f32(*(float32x4_t *)&vector,
                              vdupq_n_f32((float32_t)value));
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vector.v[0]) - _mm_set1_ps(value);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vector.v[0] - value,
                     vector.v[1] - value,
                     vector.v[2] - value,
                     vector.v[3] - value };
    return v;
#endif
}

GLK_INLINE GLKVector4 GLKVector4MultiplyScalar(GLKVector4 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&vector,
                              vdupq_n_f32((float32_t)value));
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vector.v[0]) * _mm_set1_ps(value);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vector.v[0] * value,
                     vector.v[1] * value,
                     vector.v[2] * value,
                     vector.v[3] * value };
    return v;   
#endif
}

GLK_INLINE GLKVector4 GLKVector4DivideScalar(GLKVector4 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x4_t values = vdupq_n_f32((float32_t)value);
    float32x4_t estimate = vrecpeq_f32(values);    
    estimate = vmulq_f32(vrecpsq_f32(values, estimate), estimate);
    estimate = vmulq_f32(vrecpsq_f32(values, estimate), estimate);
    float32x4_t v = vmulq_f32(*(float32x4_t *)&vector, estimate);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&vector.v[0]) / _mm_set1_ps(value);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vector.v[0] / value,
                     vector.v[1] / value,
                     vector.v[2] / value,
                     vector.v[3] / value };
    return v;
#endif
}
    
GLK_INLINE GLKVector4 GLKVector4Maximum(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmaxq_f32(*(float32x4_t *)&vectorLeft,
                              *(float32x4_t *)&vectorRight);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_max_ps(_mm_load_ps(&vectorLeft.v[0]), _mm_load_ps(&vectorRight.v[0]));
    return *(GLKVector4 *)&v;
#else
    GLKVector4 max = vectorLeft;
    if (vectorRight.v[0] > vectorLeft.v[0])
        max.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] > vectorLeft.v[1])
        max.v[1] = vectorRight.v[1];
    if (vectorRight.v[2] > vectorLeft.v[2])
        max.v[2] = vectorRight.v[2];
    if (vectorRight.v[3] > vectorLeft.v[3])
        max.v[3] = vectorRight.v[3];
    return max;
#endif
}

GLK_INLINE GLKVector4 GLKVector4Minimum(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
        float32x4_t v = vminq_f32(*(float32x4_t *)&vectorLeft,
                                  *(float32x4_t *)&vectorRight);
        return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_min_ps(_mm_load_ps(&vectorLeft.v[0]), _mm_load_ps(&vectorRight.v[0]));
    return *(GLKVector4 *)&v;
#else
        GLKVector4 min = vectorLeft;
        if (vectorRight.v[0] < vectorLeft.v[0])
            min.v[0] = vectorRight.v[0];
        if (vectorRight.v[1] < vectorLeft.v[1])
            min.v[1] = vectorRight.v[1];
        if (vectorRight.v[2] < vectorLeft.v[2])
            min.v[2] = vectorRight.v[2];
        if (vectorRight.v[3] < vectorLeft.v[3])
            min.v[3] = vectorRight.v[3];
        return min;
#endif
}
   
GLK_INLINE bool GLKVector4AllEqualToVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v1 = *(float32x4_t *)&vectorLeft;
    float32x4_t v2 = *(float32x4_t *)&vectorRight;
    uint32x4_t vCmp = vceqq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vget_low_u32(vCmp), vget_high_u32(vCmp));
    vAnd = vand_u32(vAnd, vext_u32(vAnd, vAnd, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#elif defined(GLK_SSE3_INTRINSICS)
    return _mm_movemask_ps(_mm_cmpeq_ps(_mm_load_ps(&vectorLeft.v[0]), _mm_load_ps(&vectorRight.v[0]))) == 0xF;
#else
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1] &&
        vectorLeft.v[2] == vectorRight.v[2] &&
        vectorLeft.v[3] == vectorRight.v[3])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector4AllEqualToScalar(GLKVector4 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x4_t v1 = *(float32x4_t *)&vector;
    float32x4_t v2 = vdupq_n_f32(value);
    uint32x4_t vCmp = vceqq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vget_low_u32(vCmp), vget_high_u32(vCmp));
    vAnd = vand_u32(vAnd, vext_u32(vAnd, vAnd, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#elif defined(GLK_SSE3_INTRINSICS)
    return _mm_movemask_ps(_mm_cmpeq_ps(_mm_load_ps(&vector.v[0]), _mm_set1_ps(value))) == 0xF;
#else
    bool compare = false;
    if (vector.v[0] == value &&
        vector.v[1] == value &&
        vector.v[2] == value &&
        vector.v[3] == value)
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector4AllGreaterThanVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v1 = *(float32x4_t *)&vectorLeft;
    float32x4_t v2 = *(float32x4_t *)&vectorRight;
    uint32x4_t vCmp = vcgtq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vget_low_u32(vCmp), vget_high_u32(vCmp));
    vAnd = vand_u32(vAnd, vext_u32(vAnd, vAnd, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#elif defined(GLK_SSE3_INTRINSICS)
    return _mm_movemask_ps(_mm_cmpgt_ps(_mm_load_ps(&vectorLeft.v[0]), _mm_load_ps(&vectorRight.v[0]))) == 0xF;
#else
    bool compare = false;
    if (vectorLeft.v[0] > vectorRight.v[0] &&
        vectorLeft.v[1] > vectorRight.v[1] &&
        vectorLeft.v[2] > vectorRight.v[2] &&
        vectorLeft.v[3] > vectorRight.v[3])
        compare = true;
    return compare;
#endif
}
    
GLK_INLINE bool GLKVector4AllGreaterThanScalar(GLKVector4 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x4_t v1 = *(float32x4_t *)&vector;
    float32x4_t v2 = vdupq_n_f32(value);
    uint32x4_t vCmp = vcgtq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vget_low_u32(vCmp), vget_high_u32(vCmp));
    vAnd = vand_u32(vAnd, vext_u32(vAnd, vAnd, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#elif defined(GLK_SSE3_INTRINSICS)
    return _mm_movemask_ps(_mm_cmpgt_ps(_mm_load_ps(&vector.v[0]), _mm_set1_ps(value))) == 0xF;
#else
    bool compare = false;
    if (vector.v[0] > value &&
        vector.v[1] > value &&
        vector.v[2] > value &&
        vector.v[3] > value)
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector4AllGreaterThanOrEqualToVector4(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v1 = *(float32x4_t *)&vectorLeft;
    float32x4_t v2 = *(float32x4_t *)&vectorRight;
    uint32x4_t vCmp = vcgeq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vget_low_u32(vCmp), vget_high_u32(vCmp));
    vAnd = vand_u32(vAnd, vext_u32(vAnd, vAnd, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#elif defined(GLK_SSE3_INTRINSICS)
    return _mm_movemask_ps(_mm_cmpge_ps(_mm_load_ps(&vectorLeft.v[0]), _mm_load_ps(&vectorRight.v[0]))) == 0xF;
#else
    bool compare = false;
    if (vectorLeft.v[0] >= vectorRight.v[0] &&
        vectorLeft.v[1] >= vectorRight.v[1] &&
        vectorLeft.v[2] >= vectorRight.v[2] &&
        vectorLeft.v[3] >= vectorRight.v[3])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector4AllGreaterThanOrEqualToScalar(GLKVector4 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x4_t v1 = *(float32x4_t *)&vector;
    float32x4_t v2 = vdupq_n_f32(value);
    uint32x4_t vCmp = vcgeq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vget_low_u32(vCmp), vget_high_u32(vCmp));
    vAnd = vand_u32(vAnd, vext_u32(vAnd, vAnd, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#elif defined(GLK_SSE3_INTRINSICS)
    return _mm_movemask_ps(_mm_cmpge_ps(_mm_load_ps(&vector.v[0]), _mm_set1_ps(value))) == 0xF;
#else
    bool compare = false;
    if (vector.v[0] >= value &&
        vector.v[1] >= value &&
        vector.v[2] >= value &&
        vector.v[3] >= value)
        compare = true;
    return compare;
#endif
}
    
GLK_INLINE GLKVector4 GLKVector4Normalize(GLKVector4 vector)
{
    float scale = 1.0f / GLKVector4Length(vector);
    GLKVector4 v = GLKVector4MultiplyScalar(vector, scale);
    return v;
}

GLK_INLINE float GLKVector4DotProduct(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&vectorLeft,
                              *(float32x4_t *)&vectorRight);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return vget_lane_f32(v2, 0);
#elif defined(GLK_SSE3_INTRINSICS) 
	const __m128 product = _mm_load_ps(&vectorLeft.v[0]) * _mm_load_ps(&vectorRight.v[0]);
	const __m128 halfsum = _mm_hadd_ps(product, product);
	return _mm_cvtss_f32(_mm_hadd_ps(halfsum, halfsum));
#else
    return vectorLeft.v[0] * vectorRight.v[0] +
           vectorLeft.v[1] * vectorRight.v[1] +
           vectorLeft.v[2] * vectorRight.v[2] +
           vectorLeft.v[3] * vectorRight.v[3];
#endif
}

GLK_INLINE float GLKVector4Length(GLKVector4 vector)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&vector,
                              *(float32x4_t *)&vector);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return sqrt(vget_lane_f32(v2, 0));
#elif defined(GLK_SSE3_INTRINSICS) 
	const __m128 q = _mm_load_ps(&vector.v[0]);
	const __m128 product = q * q;
	const __m128 halfsum = _mm_hadd_ps(product, product);
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_hadd_ps(halfsum, halfsum)));
#else
    return sqrt(vector.v[0] * vector.v[0] +
                vector.v[1] * vector.v[1] +
                vector.v[2] * vector.v[2] +
                vector.v[3] * vector.v[3]);
#endif
}

GLK_INLINE float GLKVector4Distance(GLKVector4 vectorStart, GLKVector4 vectorEnd)
{
    return GLKVector4Length(GLKVector4Subtract(vectorEnd, vectorStart));
}

GLK_INLINE GLKVector4 GLKVector4Lerp(GLKVector4 vectorStart, GLKVector4 vectorEnd, float t)
{
#if defined(__ARM_NEON__)
    float32x4_t vDiff = vsubq_f32(*(float32x4_t *)&vectorEnd,
                                  *(float32x4_t *)&vectorStart);
    vDiff = vmulq_f32(vDiff, vdupq_n_f32((float32_t)t));
    float32x4_t v = vaddq_f32(*(float32x4_t *)&vectorStart, vDiff);
    return *(GLKVector4 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 s =  _mm_load_ps(&vectorStart.v[0]);
    const __m128 v = s + (_mm_load_ps(&vectorEnd.v[0]) - s) * _mm_set1_ps(t);
    return *(GLKVector4 *)&v;
#else
    GLKVector4 v = { vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                     vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t),
                     vectorStart.v[2] + ((vectorEnd.v[2] - vectorStart.v[2]) * t),
                     vectorStart.v[3] + ((vectorEnd.v[3] - vectorStart.v[3]) * t) };
    return v;
#endif
}
    
GLK_INLINE GLKVector4 GLKVector4CrossProduct(GLKVector4 vectorLeft, GLKVector4 vectorRight)
{
#if defined(GLK_SSE3_INTRINSICS)
	const __m128 vl = _mm_load_ps(&vectorLeft.v[0]);
	const __m128 vr = _mm_load_ps(&vectorRight.v[0]);

    __m128 vLeft1  = _mm_shuffle_ps(vl, vl, _MM_SHUFFLE(3, 0, 2, 1));
    __m128 vRight1 = _mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 vLeft2  = _mm_shuffle_ps(vl, vl, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 vRight2 = _mm_shuffle_ps(vr, vr, _MM_SHUFFLE(3, 0, 2, 1));
    vLeft1 = vLeft1 * vRight1;
    vLeft2 = vLeft2 * vRight2;
    vLeft1 = vLeft1 - vLeft2;
    //Set last element to 0
    uint32_t mask[4] __attribute__((aligned(16))) = {0xffffffff, 0xffffffff, 0xffffffff, 0x0};
    vLeft1 = _mm_and_ps(vLeft1, _mm_load_ps((float *)mask));
    return *(GLKVector4 *)&vLeft1;
#else
    GLKVector4 v = { vectorLeft.v[1] * vectorRight.v[2] - vectorLeft.v[2] * vectorRight.v[1],
                     vectorLeft.v[2] * vectorRight.v[0] - vectorLeft.v[0] * vectorRight.v[2],
                     vectorLeft.v[0] * vectorRight.v[1] - vectorLeft.v[1] * vectorRight.v[0],
                     0.0f };
    return v;
#endif
}
    
GLK_INLINE GLKVector4 GLKVector4Project(GLKVector4 vectorToProject, GLKVector4 projectionVector)
{
    float scale = GLKVector4DotProduct(projectionVector, vectorToProject) / GLKVector4DotProduct(projectionVector, projectionVector);
    GLKVector4 v = GLKVector4MultiplyScalar(projectionVector, scale);
    return v;
}
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_VECTOR_4_H */
// ==========  GLKit.framework/Headers/GLKEffects.h
//
//  GLKEffects.h
//  GLKEffects
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKNamedEffect.h>
#import <GLKit/GLKBaseEffect.h>
#import <GLKit/GLKReflectionMapEffect.h>
#import <GLKit/GLKSkyboxEffect.h>

// Named vertex attributes for mapping GLKEffects logic to client vertex attrib enables
typedef NS_ENUM(GLint, GLKVertexAttrib)
{
    GLKVertexAttribPosition,
    GLKVertexAttribNormal,
    GLKVertexAttribColor,
    GLKVertexAttribTexCoord0,
    GLKVertexAttribTexCoord1
} NS_ENUM_AVAILABLE(10_8, 5_0);
// ==========  GLKit.framework/Headers/GLKEffectPropertyFog.h
//
//  GLKEffectPropertyFog.h
//  GLKit
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//
#import <GLKit/GLKitBase.h>
#import <GLKit/GLKEffectProperty.h>

// Fog modes per the OpenGL ES 1.1 specification
typedef NS_ENUM(GLint, GLKFogMode)
{
    GLKFogModeExp=0,
    GLKFogModeExp2,
    GLKFogModeLinear
} NS_ENUM_AVAILABLE(10_8, 5_0);


/*
 GLKEffectPropertyFog

 GLKEffectPropertyFog allows specification of fog parameters and operation per the OpenGL ES 1.1 specification.
 Fog properties may be enabled or disabled through their enabled property.

 The default values of the properties of this class are as follows:

      enabled         GL_TRUE
      mode            GLKFogModeExp
      color           { 0.0, 0.0, 0.0, 0.0 }
      density         1.0
      start           0.0
      end             1.0
*/
NS_ASSUME_NONNULL_BEGIN

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKEffectPropertyFog : GLKEffectProperty 
{
    @private
    
    GLboolean     _enabled;    // Switch fog on or off
    GLint         _mode;       // GLKFogMode as defined above
    GLKVector4    _color;      // Fog color
    GLfloat       _density;    // Fog density
    GLfloat       _start;      // Fog start boundary for GLKFogModeLinear
    GLfloat       _end;        // Fog end boundary for GLKFogModeLinear    
}

// Properties                                              // Default Value
@property (nonatomic, assign)    GLboolean     enabled;    // GL_FALSE
@property (nonatomic, assign)    GLint         mode;       // GLKFogModeExp
@property (nonatomic, assign)    GLKVector4    color;      // { 0.0, 0.0, 0.0, 0.0 }
@property (nonatomic, assign)    GLfloat       density;    // 1.0
@property (nonatomic, assign)    GLfloat       start;      // 0.0
@property (nonatomic, assign)    GLfloat       end;        // 1.0

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKQuaternion.h
//
//  GLKQuaternion.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_QUATERNION_H
#define __GLK_QUATERNION_H

#include <stddef.h>
#include <math.h>

#include <GLKit/GLKMathTypes.h>

#include <GLKit/GLKVector3.h>
#include <GLKit/GLKVector4.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma mark -
#pragma mark Prototypes
#pragma mark -
    
extern const GLKQuaternion GLKQuaternionIdentity; 
	
/*
 x, y, and z represent the imaginary values.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMake(float x, float y, float z, float w);
    
/*
 vector represents the imaginary values.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithVector3(GLKVector3 vector, float scalar);

/*
 values[0], values[1], and values[2] represent the imaginary values.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithArray(float values[4]);
    
/*
 Assumes the axis is already normalized.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndAxis(float radians, float x, float y, float z);
/*
 Assumes the axis is already normalized.
 */
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndVector3Axis(float radians, GLKVector3 axisVector);
    
GLKQuaternion GLKQuaternionMakeWithMatrix3(GLKMatrix3 matrix);
GLKQuaternion GLKQuaternionMakeWithMatrix4(GLKMatrix4 matrix);

/*
 Calculate and return the angle component of the angle and axis form.
 */
float GLKQuaternionAngle(GLKQuaternion quaternion);

/*
 Calculate and return the axis component of the angle and axis form.
 */
GLKVector3 GLKQuaternionAxis(GLKQuaternion quaternion);
    
GLK_INLINE GLKQuaternion GLKQuaternionAdd(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
GLK_INLINE GLKQuaternion GLKQuaternionSubtract(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
GLK_INLINE GLKQuaternion GLKQuaternionMultiply(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight);
	
GLKQuaternion GLKQuaternionSlerp(GLKQuaternion quaternionStart, GLKQuaternion quaternionEnd, float t);

GLK_INLINE float GLKQuaternionLength(GLKQuaternion quaternion);

GLK_INLINE GLKQuaternion GLKQuaternionConjugate(GLKQuaternion quaternion);
GLK_INLINE GLKQuaternion GLKQuaternionInvert(GLKQuaternion quaternion);
GLK_INLINE GLKQuaternion GLKQuaternionNormalize(GLKQuaternion quaternion);

GLK_INLINE GLKVector3 GLKQuaternionRotateVector3(GLKQuaternion quaternion, GLKVector3 vector);
void GLKQuaternionRotateVector3Array(GLKQuaternion quaternion, GLKVector3 *__nonnull vectors, size_t vectorCount);
    
/*
 The fourth component of the vector is ignored when calculating the rotation.
 */
GLK_INLINE GLKVector4 GLKQuaternionRotateVector4(GLKQuaternion quaternion, GLKVector4 vector);
void GLKQuaternionRotateVector4Array(GLKQuaternion quaternion, GLKVector4 *__nonnull vectors, size_t vectorCount);
    
#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKQuaternion GLKQuaternionMake(float x, float y, float z, float w)
{
    GLKQuaternion q = { x, y, z, w };
    return q;
}

GLK_INLINE GLKQuaternion GLKQuaternionMakeWithVector3(GLKVector3 vector, float scalar)
{
    GLKQuaternion q = { vector.v[0], vector.v[1], vector.v[2], scalar };
    return q;
}
    
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithArray(float values[4])
{
#if defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(values);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { values[0], values[1], values[2], values[3] };
    return q;
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndAxis(float radians, float x, float y, float z)
{
    float halfAngle = radians * 0.5f;
    float scale = sinf(halfAngle);
    GLKQuaternion q = { scale * x, scale * y, scale * z, cosf(halfAngle) };
    return q;
}
    
GLK_INLINE GLKQuaternion GLKQuaternionMakeWithAngleAndVector3Axis(float radians, GLKVector3 axisVector)
{
    return GLKQuaternionMakeWithAngleAndAxis(radians, axisVector.v[0], axisVector.v[1], axisVector.v[2]);
}
    
GLK_INLINE GLKQuaternion GLKQuaternionAdd(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vaddq_f32(*(float32x4_t *)&quaternionLeft,
                              *(float32x4_t *)&quaternionRight);
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&quaternionLeft.q[0]) + _mm_load_ps(&quaternionRight.q[0]);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { quaternionLeft.q[0] + quaternionRight.q[0],
                        quaternionLeft.q[1] + quaternionRight.q[1],
                        quaternionLeft.q[2] + quaternionRight.q[2],
                        quaternionLeft.q[3] + quaternionRight.q[3] };
    return q;
#endif
}

GLK_INLINE GLKQuaternion GLKQuaternionSubtract(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vsubq_f32(*(float32x4_t *)&quaternionLeft,
                              *(float32x4_t *)&quaternionRight);
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v = _mm_load_ps(&quaternionLeft.q[0]) - _mm_load_ps(&quaternionRight.q[0]);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { quaternionLeft.q[0] - quaternionRight.q[0],
                        quaternionLeft.q[1] - quaternionRight.q[1],
                        quaternionLeft.q[2] - quaternionRight.q[2],
                        quaternionLeft.q[3] - quaternionRight.q[3] };
    return q;
#endif
}

GLK_INLINE GLKQuaternion GLKQuaternionMultiply(GLKQuaternion quaternionLeft, GLKQuaternion quaternionRight)
{
#if defined(GLK_SSE3_INTRINSICS)
	const __m128 ql = _mm_load_ps(&quaternionLeft.q[0]);
	const __m128 qr = _mm_load_ps(&quaternionRight.q[0]);

	const __m128 ql3012 = _mm_shuffle_ps(ql, ql, _MM_SHUFFLE(2, 1, 0, 3));
	const __m128 ql3120 = _mm_shuffle_ps(ql, ql, _MM_SHUFFLE(0, 2, 1, 3));
	const __m128 ql3201 = _mm_shuffle_ps(ql, ql, _MM_SHUFFLE(1, 0, 2, 3));

	const __m128 qr0321 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(1, 2, 3, 0));
	const __m128 qr1302 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(2, 0, 3, 1));
	const __m128 qr2310 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(0, 1, 3, 2));
	const __m128 qr3012 = _mm_shuffle_ps(qr, qr, _MM_SHUFFLE(2, 1, 0, 3));

    uint32_t signBit = 0x80000000;
    uint32_t zeroBit = 0x0;
    uint32_t __attribute__((aligned(16))) mask0001[4] = {zeroBit, zeroBit, zeroBit, signBit};
    uint32_t __attribute__((aligned(16))) mask0111[4] = {zeroBit, signBit, signBit, signBit};
    const __m128 m0001 = _mm_load_ps((float *)mask0001);
    const __m128 m0111 = _mm_load_ps((float *)mask0111);

	const __m128 aline = ql3012 * _mm_xor_ps(qr0321, m0001);
	const __m128 bline = ql3120 * _mm_xor_ps(qr1302, m0001);
	const __m128 cline = ql3201 * _mm_xor_ps(qr2310, m0001);
	const __m128 dline = ql3012 * _mm_xor_ps(qr3012, m0111);
	const __m128 r = _mm_hadd_ps(_mm_hadd_ps(aline, bline), _mm_hadd_ps(cline, dline));
				   
    return *(GLKQuaternion *)&r;
#else

    GLKQuaternion q = { quaternionLeft.q[3] * quaternionRight.q[0] +
                        quaternionLeft.q[0] * quaternionRight.q[3] +
                        quaternionLeft.q[1] * quaternionRight.q[2] -
                        quaternionLeft.q[2] * quaternionRight.q[1],
        
                        quaternionLeft.q[3] * quaternionRight.q[1] +
                        quaternionLeft.q[1] * quaternionRight.q[3] +
                        quaternionLeft.q[2] * quaternionRight.q[0] -
                        quaternionLeft.q[0] * quaternionRight.q[2],
        
                        quaternionLeft.q[3] * quaternionRight.q[2] +
                        quaternionLeft.q[2] * quaternionRight.q[3] +
                        quaternionLeft.q[0] * quaternionRight.q[1] -
                        quaternionLeft.q[1] * quaternionRight.q[0],
        
                        quaternionLeft.q[3] * quaternionRight.q[3] -
                        quaternionLeft.q[0] * quaternionRight.q[0] -
                        quaternionLeft.q[1] * quaternionRight.q[1] -
                        quaternionLeft.q[2] * quaternionRight.q[2] };
    return q;
#endif
}
 
GLK_INLINE float GLKQuaternionLength(GLKQuaternion quaternion)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&quaternion,
                              *(float32x4_t *)&quaternion);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return sqrt(vget_lane_f32(v2, 0)); 
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
	const __m128 product = q * q;
	const __m128 halfsum = _mm_hadd_ps(product, product);
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_hadd_ps(halfsum, halfsum)));
#else
    return sqrt(quaternion.q[0] * quaternion.q[0] +
                quaternion.q[1] * quaternion.q[1] +
                quaternion.q[2] * quaternion.q[2] +
                quaternion.q[3] * quaternion.q[3]);
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionConjugate(GLKQuaternion quaternion)
{
#if defined(__ARM_NEON__)
    float32x4_t *q = (float32x4_t *)&quaternion;
    
    uint32_t signBit = 0x80000000;
    uint32_t zeroBit = 0x0;
    uint32x4_t mask = vdupq_n_u32(signBit);
    mask = vsetq_lane_u32(zeroBit, mask, 3);
    *q = vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(*q), mask));
    
    return *(GLKQuaternion *)q;
#elif defined(GLK_SSE3_INTRINSICS)
    // Multiply first three elements by -1
    const uint32_t signBit = 0x80000000;
    const uint32_t zeroBit = 0x0;
    const uint32_t __attribute__((aligned(16))) mask[4] = {signBit, signBit, signBit, zeroBit};
    __m128 v_mask = _mm_load_ps((float *)mask);
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
    __m128 v = _mm_xor_ps(q, v_mask);
    
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { -quaternion.q[0], -quaternion.q[1], -quaternion.q[2], quaternion.q[3] };
    return q;
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionInvert(GLKQuaternion quaternion)
{
#if defined(__ARM_NEON__)
    float32x4_t *q = (float32x4_t *)&quaternion;
    float32x4_t v = vmulq_f32(*q, *q);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    float32_t scale = 1.0f / vget_lane_f32(v2, 0);
    v = vmulq_f32(*q, vdupq_n_f32(scale));
    
    uint32_t signBit = 0x80000000;
    uint32_t zeroBit = 0x0;
    uint32x4_t mask = vdupq_n_u32(signBit);
    mask = vsetq_lane_u32(zeroBit, mask, 3);
    v = vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(v), mask));
    
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
    const uint32_t signBit = 0x80000000;
    const uint32_t zeroBit = 0x0;
    const uint32_t __attribute__((aligned(16))) mask[4] = {signBit, signBit, signBit, zeroBit};
    const __m128 v_mask = _mm_load_ps((float *)mask);
	const __m128 product = q * q;
	const __m128 halfsum = _mm_hadd_ps(product, product);
	const __m128 v = _mm_xor_ps(q, v_mask) / _mm_hadd_ps(halfsum, halfsum);
    return *(GLKQuaternion *)&v;
#else
    float scale = 1.0f / (quaternion.q[0] * quaternion.q[0] + 
                          quaternion.q[1] * quaternion.q[1] +
                          quaternion.q[2] * quaternion.q[2] +
                          quaternion.q[3] * quaternion.q[3]);
    GLKQuaternion q = { -quaternion.q[0] * scale, -quaternion.q[1] * scale, -quaternion.q[2] * scale, quaternion.q[3] * scale };
    return q;
#endif
}
    
GLK_INLINE GLKQuaternion GLKQuaternionNormalize(GLKQuaternion quaternion)
{
    float scale = 1.0f / GLKQuaternionLength(quaternion);
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&quaternion,
                              vdupq_n_f32((float32_t)scale));
    return *(GLKQuaternion *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(&quaternion.q[0]);
    __m128 v = q * _mm_set1_ps(scale);
    return *(GLKQuaternion *)&v;
#else
    GLKQuaternion q = { quaternion.q[0] * scale, quaternion.q[1] * scale, quaternion.q[2] * scale, quaternion.q[3] * scale };
    return q;
#endif
}
    
GLK_INLINE GLKVector3 GLKQuaternionRotateVector3(GLKQuaternion quaternion, GLKVector3 vector)
{
    GLKQuaternion rotatedQuaternion = GLKQuaternionMake(vector.v[0], vector.v[1], vector.v[2], 0.0f);
    rotatedQuaternion = GLKQuaternionMultiply(GLKQuaternionMultiply(quaternion, rotatedQuaternion), GLKQuaternionInvert(quaternion));
    
    return GLKVector3Make(rotatedQuaternion.q[0], rotatedQuaternion.q[1], rotatedQuaternion.q[2]);
}
    
GLK_INLINE GLKVector4 GLKQuaternionRotateVector4(GLKQuaternion quaternion, GLKVector4 vector)
{
    GLKQuaternion rotatedQuaternion = GLKQuaternionMake(vector.v[0], vector.v[1], vector.v[2], 0.0f);
    rotatedQuaternion = GLKQuaternionMultiply(GLKQuaternionMultiply(quaternion, rotatedQuaternion), GLKQuaternionInvert(quaternion));
    
    return GLKVector4Make(rotatedQuaternion.q[0], rotatedQuaternion.q[1], rotatedQuaternion.q[2], vector.v[3]);
}
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_QUATERNION_H */
// ==========  GLKit.framework/Headers/GLKitBase.h
/*
  GLKitBase.h
  GLKit

  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
*/

#import <TargetConditionals.h>
#import <os/availability.h>
#if TARGET_OS_IPHONE && (!defined(TARGET_OS_UIKITFORMAC) || !TARGET_OS_UIKITFORMAC)
#import <OpenGLES/gltypes.h>
#else // !TARGET_OS_IPHONE
#import <OpenGL/gltypes.h>
#endif // !TARGET_OS_IPHONE
#define GLK_INLINE	static __inline__

#ifdef __cplusplus
	#define GLK_EXTERN extern "C"
#else
	#define GLK_EXTERN extern 
#endif

#if TARGET_OS_IPHONE && (!defined(TARGET_OS_UIKITFORMAC) || !TARGET_OS_UIKITFORMAC)
#import <OpenGLES/OpenGLESAvailability.h>
#define OPENGL_DEPRECATED(...)
#else
#import <OpenGL/OpenGLAvailability.h>
#define OPENGLES_DEPRECATED(...)
#endif

// ==========  GLKit.framework/Headers/GLKViewController.h
//
//  GLKViewController.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <UIKit/UIKit.h>

#import <GLKit/GLKView.h>

NS_ASSUME_NONNULL_BEGIN
@protocol GLKViewControllerDelegate;

#pragma mark -
#pragma mark GLKViewController
#pragma mark -

OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
API_UNAVAILABLE(macos)
@interface GLKViewController : UIViewController <NSCoding, GLKViewDelegate>
{
    
}

@property (nullable, nonatomic, assign) IBOutlet id <GLKViewControllerDelegate> delegate;

/*
 For setting the desired frames per second at which the update and drawing will take place.
 The default is 30.
 */
@property (nonatomic) NSInteger preferredFramesPerSecond;

/*
 The actual frames per second that was decided upon given the value for preferredFramesPerSecond
 and the screen for which the GLKView resides. The value chosen will be as close to
 preferredFramesPerSecond as possible, without exceeding the screen's refresh rate. This value
 does not account for dropped frames, so it is not a measurement of your statistical frames per
 second. It is the static value for which updates will take place.
 */
@property (nonatomic, readonly) NSInteger framesPerSecond;

/*
 Used to pause and resume the controller.
 */
@property (nonatomic, getter=isPaused) BOOL paused;

/*
 The total number of frames displayed since drawing began.
 */
@property (nonatomic, readonly) NSInteger framesDisplayed;

/*
 Time interval since properties.
 */
@property (nonatomic, readonly) NSTimeInterval timeSinceFirstResume;
@property (nonatomic, readonly) NSTimeInterval timeSinceLastResume;
@property (nonatomic, readonly) NSTimeInterval timeSinceLastUpdate;
@property (nonatomic, readonly) NSTimeInterval timeSinceLastDraw;

/*
 If true, the controller will pause when the application recevies a willResignActive notification.
 If false, the controller will not pause and it is expected that some other mechanism will pause
 the controller when necessary.
 The default is true.
 */
@property (nonatomic) BOOL pauseOnWillResignActive;

/*
 If true, the controller will resume when the application recevies a didBecomeActive notification.
 If false, the controller will not resume and it is expected that some other mechanism will resume
 the controller when necessary.
 The default is true.
 */
@property (nonatomic) BOOL resumeOnDidBecomeActive;

@end

#pragma mark -
#pragma mark GLKViewControllerDelegate
#pragma mark -

@protocol GLKViewControllerDelegate <NSObject>

@required
/*
 Required method for implementing GLKViewControllerDelegate. This update method variant should be used
 when not subclassing GLKViewController. This method will not be called if the GLKViewController object
 has been subclassed and implements -(void)update.
 */
- (void)glkViewControllerUpdate:(GLKViewController *)controller;

@optional
/*
 Delegate method that gets called when the pause state changes. 
 */
- (void)glkViewController:(GLKViewController *)controller willPause:(BOOL)pause;

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKNamedEffect.h
//
//  GLKNamedEffect.h
//  GLKit
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

@protocol GLKNamedEffect

@required
- (void) prepareToDraw;

@end

// ==========  GLKit.framework/Headers/GLKMath.h
//
//  GLKMath.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#include <GLKit/GLKMathTypes.h>

#include <GLKit/GLKMatrix3.h>
#include <GLKit/GLKMatrix4.h>
#include <GLKit/GLKVector2.h>
#include <GLKit/GLKVector3.h>
#include <GLKit/GLKVector4.h>
#include <GLKit/GLKQuaternion.h>

#include <GLKit/GLKMatrixStack.h>

#include <GLKit/GLKMathUtils.h>
// ==========  GLKit.framework/Headers/GLKMathTypes.h
//
//  GLKMathTypes.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATH_TYPES_H
#define __GLK_MATH_TYPES_H

#import <GLKit/GLKitBase.h>

#if TARGET_OS_MAC && !TARGET_OS_IPHONE
	#ifndef __SSE3__
		#warning "SSE3 instruction set not enabled. GLKit math routines will be slower."
	#else
		#include <immintrin.h>
		#include <stdint.h>
		#define GLK_SSE3_INTRINSICS 1
	#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STRICT_ANSI__)
struct _GLKMatrix2
{
    float m[4];
};
typedef struct _GLKMatrix2 GLKMatrix2;
#else
union _GLKMatrix2
{
    struct
    {
        float m00, m01;
        float m10, m11;
    };
    float m2[2][2];
    float m[4];
};
typedef union _GLKMatrix2 GLKMatrix2;
#endif
    
#if defined(__STRICT_ANSI__)
struct _GLKMatrix3
{
    float m[9];
};
typedef struct _GLKMatrix3 GLKMatrix3; 
#else
union _GLKMatrix3
{
    struct
    {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    float m[9];
};
typedef union _GLKMatrix3 GLKMatrix3;
#endif
    
/*
 m30, m31, and m32 correspond to the translation values tx, ty, and tz, respectively.
 m[12], m[13], and m[14] correspond to the translation values tx, ty, and tz, respectively.
 */
#if defined(__STRICT_ANSI__)
struct _GLKMatrix4
{
    float m[16];
} __attribute__((aligned(16)));
typedef struct _GLKMatrix4 GLKMatrix4;    
#else
union _GLKMatrix4
{
    struct
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    float m[16];
} __attribute__((aligned(16)));
typedef union _GLKMatrix4 GLKMatrix4;
#endif
    
#if defined(__STRICT_ANSI__)
struct _GLKVector2
{
    float v[2];
} __attribute__((aligned(8)));
typedef struct _GLKVector2 GLKVector2;
#else
union _GLKVector2
{
    struct { float x, y; };
    struct { float s, t; };
    float v[2];
} __attribute__((aligned(8)));
typedef union _GLKVector2 GLKVector2;
#endif
    
#if defined(__STRICT_ANSI__)
struct _GLKVector3
{
    float v[3];
};
typedef struct _GLKVector3 GLKVector3;   
#else
union _GLKVector3
{
    struct { float x, y, z; };
    struct { float r, g, b; };
    struct { float s, t, p; };
    float v[3];
};
typedef union _GLKVector3 GLKVector3;
#endif
    
#if defined(__STRICT_ANSI__)
struct _GLKVector4
{
    float v[4];
} __attribute__((aligned(16)));
typedef struct _GLKVector4 GLKVector4;  
#else
union _GLKVector4
{
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    struct { float s, t, p, q; };
    float v[4];
} __attribute__((aligned(16)));
typedef union _GLKVector4 GLKVector4;
#endif
    
/*
 x, y, and z represent the imaginary values.
 Vector v represents the imaginary values.
 q[0], q[1], and q[2] represent the imaginary values.
 */
#if defined(__STRICT_ANSI__)
struct _GLKQuaternion
{
    float q[4];
} __attribute__((aligned(16)));
typedef struct _GLKQuaternion GLKQuaternion;
#else
union _GLKQuaternion
{
    struct { GLKVector3 v; float s; };
    struct { float x, y, z, w; };
    float q[4];
} __attribute__((aligned(16)));
typedef union _GLKQuaternion GLKQuaternion;    
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATH_TYPES_H */
// ==========  GLKit.framework/Headers/GLKit.h
//
//  GLKit.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#import <GLKit/GLKitBase.h>

#if TARGET_OS_IPHONE
#import <GLKit/GLKView.h>
#import <GLKit/GLKViewController.h>
#endif

#import <GLKit/GLKModel.h>

#import <GLKit/GLKEffects.h>

#import <GLKit/GLKMath.h>

#import <GLKit/GLKTextureLoader.h>
// ==========  GLKit.framework/Headers/GLKMatrixStack.h
//
//  GLKMatrixStack.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATRIX_STACK_H
#define __GLK_MATRIX_STACK_H

#include <CoreFoundation/CoreFoundation.h>

#include <GLKit/GLKMathTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 GLKMatrixStack is a CFType that allows for the creation of a 4x4 matrix stack similar to OpenGL's matrix
 stack. Any number of matrix stacks can be created and operated on with functions similar to those found
 in fixed function versions of OpenGL.
 */
    
typedef struct CF_BRIDGED_TYPE(id) _GLKMatrixStack *GLKMatrixStackRef;

/* 
 CFType GLKMatrixStack creation routine. Pass NULL or kCFAllocatorDefault to use the current default
 allocator. A newly created stack is initialized with the identity matrix.
 */
GLKMatrixStackRef __nullable GLKMatrixStackCreate(CFAllocatorRef __nullable alloc);

/*
 Returns the type identifier for the GLKMatrixStack opaque type.
 */
CFTypeID GLKMatrixStackGetTypeID(void);

/*
 Pushes all of the matrices down one level and copies the topmost matrix.
 */
void GLKMatrixStackPush(GLKMatrixStackRef __nonnull stack);
/*
 Pops the topmost matrix off of the stack, moving the rest of the matrices up one level.
 */
void GLKMatrixStackPop(GLKMatrixStackRef __nonnull stack);

/*
 Returns the number of matrices currently on the stack.
 */
int GLKMatrixStackSize(GLKMatrixStackRef __nonnull stack);

/*
 Replaces the topmost matrix with the matrix provided.
 */
void GLKMatrixStackLoadMatrix4(GLKMatrixStackRef __nonnull stack, GLKMatrix4 matrix);

/*
 Returns the 4x4 matrix currently residing on top of the stack.
 */
GLKMatrix4 GLKMatrixStackGetMatrix4(GLKMatrixStackRef __nonnull stack);
/*
 Returns the upper left 3x3 portion of the matrix currently residing on top of the stack.
 */
GLKMatrix3 GLKMatrixStackGetMatrix3(GLKMatrixStackRef __nonnull stack);
/*
 Returns the upper left 2x2 portion of the matrix currently residing on top of the stack.
 */
GLKMatrix2 GLKMatrixStackGetMatrix2(GLKMatrixStackRef __nonnull stack);

/*
 Calculate and return the inverse matrix from the matrix currently residing on top of stack.
 */
GLKMatrix4 GLKMatrixStackGetMatrix4Inverse(GLKMatrixStackRef __nonnull stack);
/*
 Calculate and return the inverse transpose matrix from the matrix currently residing on top of stack.
 */
GLKMatrix4 GLKMatrixStackGetMatrix4InverseTranspose(GLKMatrixStackRef __nonnull stack);

/*
 Calculate and return the upper left 3x3 inverse matrix from the matrix currently residing on top of stack.
 */
GLKMatrix3 GLKMatrixStackGetMatrix3Inverse(GLKMatrixStackRef __nonnull stack);
/*
 Calculate and return the upper left 3x3 inverse transpose matrix from the matrix currently residing on top of stack.
 */
GLKMatrix3 GLKMatrixStackGetMatrix3InverseTranspose(GLKMatrixStackRef __nonnull stack);

/*
 Multiply the topmost matrix with the matrix provided.
 */
void GLKMatrixStackMultiplyMatrix4(GLKMatrixStackRef __nonnull stack, GLKMatrix4 matrix);

/*
 Multiply the topmost matrix of the stackLeft with the topmost matrix of stackRight and store in stackLeft.
 */
void GLKMatrixStackMultiplyMatrixStack(GLKMatrixStackRef __nonnull stackLeft, GLKMatrixStackRef __nonnull stackRight);
    
/*
 Translate the topmost matrix.
 */
void GLKMatrixStackTranslate(GLKMatrixStackRef __nonnull stack, float tx, float ty, float tz);
void GLKMatrixStackTranslateWithVector3(GLKMatrixStackRef __nonnull stack, GLKVector3 translationVector);
void GLKMatrixStackTranslateWithVector4(GLKMatrixStackRef __nonnull stack, GLKVector4 translationVector);
    
/*
 Scale the topmost matrix.
 */
void GLKMatrixStackScale(GLKMatrixStackRef __nonnull stack, float sx, float sy, float sz);
void GLKMatrixStackScaleWithVector3(GLKMatrixStackRef __nonnull stack, GLKVector3 scaleVector);
void GLKMatrixStackScaleWithVector4(GLKMatrixStackRef __nonnull stack, GLKVector4 scaleVector);
    
/*
 Rotate the topmost matrix about the specified axis.
 */
void GLKMatrixStackRotate(GLKMatrixStackRef __nonnull stack, float radians, float x, float y, float z);
void GLKMatrixStackRotateWithVector3(GLKMatrixStackRef __nonnull stack, float radians, GLKVector3 axisVector);
void GLKMatrixStackRotateWithVector4(GLKMatrixStackRef __nonnull stack, float radians, GLKVector4 axisVector);
     
/*
 Rotate the topmost matrix about the x, y, or z axis.
 */
void GLKMatrixStackRotateX(GLKMatrixStackRef __nonnull stack, float radians);
void GLKMatrixStackRotateY(GLKMatrixStackRef __nonnull stack, float radians);
void GLKMatrixStackRotateZ(GLKMatrixStackRef __nonnull stack, float radians);

#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATRIX_STACK_H */
// ==========  GLKit.framework/Headers/GLKTextureLoader.h
//
//  GLKTextureLoader.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

/*
 Convenience library for loading textures into OpenGL
 
 - Synchronous and asynchronous loading of textures
 - Supports most ImageIO formats as well as PVR files on iOS
 
 Default Texture Parameters
 
 - The following values will be set as the default for the OpenGL filter and wrap texture parameters:
 
 GL_TEXTURE_MIN_FILTER: GL_LINEAR_MIPMAP_LINEAR if textures are mipmapped, GL_LINEAR otherwise
 
 GL_TEXTURE_MAG_FILTER: GL_LINEAR
 
 GL_TEXTURE_WRAP_S / GL_TEXTURE_WRAP_T: GL_CLAMP_TO_EDGE
 
 Any texture parameter not specified above will be set to OpenGL's default value.
 */

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#import <GLKit/GLKitBase.h>
#if TARGET_OS_IPHONE
#import <OpenGLES/EAGL.h>
#else //!TARGET_OS_IPHONE
#import <AppKit/AppKit.h>
#endif //!TARGET_OS_IPHONE

NS_ASSUME_NONNULL_BEGIN
#pragma mark -
#pragma mark Definitions
#pragma mark -

/*
 Dictionary keys for texture loader properties
 */
/*
 GLKTextureLoaderApplyPremultiplication - A boolean NSNumber.
 Non-alpha channels are premultiplied by corresponding alpha channel values.
 For compressed formats, this option must be omitted, or false.
 False by default.
 */
GLK_EXTERN NSString *const GLKTextureLoaderApplyPremultiplication NS_AVAILABLE(10_8, 5_0) OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0));

/*
 GLKTextureLoaderGenerateMipmaps - A boolean NSNumber
 Generates all levels of mipmaps for the current image being loaded as a texture.
 Generates mipmap levels for all faces when used with cube maps.
 Sets GL_TEXTURE_MIN_FILTER parameter to GL_LINEAR_MIPMAP_LINEAR when true.
 False by default. */
GLK_EXTERN NSString *const GLKTextureLoaderGenerateMipmaps NS_AVAILABLE(10_8, 5_0) OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0));

/*
 GLKTextureLoaderOriginBottomLeft - A boolean NSNumber.
 Transform image data to match OpenGL's bottom left orientation specification.
 False by default. */
GLK_EXTERN NSString *const GLKTextureLoaderOriginBottomLeft NS_AVAILABLE(10_8, 5_0) OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0));

/*
 GLKTextureLoaderGrayscaleAsAlpha - A boolean NSNumber.
 If true, a single channel grayscale image is loaded as GL_ALPHA.
 If false, it will be loaded as GL_LUMINANCE.
 Has no effect on non-grayscale images and on OS X.
 False by default.
 */
GLK_EXTERN NSString *const GLKTextureLoaderGrayscaleAsAlpha; API_UNAVAILABLE(macos) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0));


/*
 GLKTextureLoaderSRGB - A boolean NSNumber.
 If true, the texture will be loaded as sRGB.
 If false, it will be loaded as linear.
 False by default.
 */
#if TARGET_OS_IPHONE || defined(MAC_OS_X_VERSION_10_9)
GLK_EXTERN NSString *const GLKTextureLoaderSRGB  OPENGL_DEPRECATED(10.9,10.14) OPENGLES_DEPRECATED(ios(7.0,12.0), tvos(9.0,12.0));
#else
GLK_EXTERN NSString *const GLKTextureLoaderSRGB;
#endif

/*
 Error domain for GLKTextureLoader
 */
GLK_EXTERN NSString *const GLKTextureLoaderErrorDomain OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0));

/*
 Error keys for obtaining more error information
 */
GLK_EXTERN NSString *const GLKTextureLoaderErrorKey OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0));
GLK_EXTERN NSString *const GLKTextureLoaderGLErrorKey OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0));

/*
 Error codes
 */
typedef NS_ENUM(GLuint, GLKTextureLoaderError)
{
    GLKTextureLoaderErrorFileOrURLNotFound = 0,
    GLKTextureLoaderErrorInvalidNSData = 1,
    GLKTextureLoaderErrorInvalidCGImage = 2,
    GLKTextureLoaderErrorUnknownPathType = 3,
    GLKTextureLoaderErrorUnknownFileType = 4,
    GLKTextureLoaderErrorPVRAtlasUnsupported = 5,
    GLKTextureLoaderErrorCubeMapInvalidNumFiles = 6,
    GLKTextureLoaderErrorCompressedTextureUpload = 7,
    GLKTextureLoaderErrorUncompressedTextureUpload = 8,
    GLKTextureLoaderErrorUnsupportedCubeMapDimensions = 9,
    GLKTextureLoaderErrorUnsupportedBitDepth = 10,
    GLKTextureLoaderErrorUnsupportedPVRFormat = 11,
    GLKTextureLoaderErrorDataPreprocessingFailure = 12,
    GLKTextureLoaderErrorMipmapUnsupported = 13,
    GLKTextureLoaderErrorUnsupportedOrientation = 14,
    GLKTextureLoaderErrorReorientationFailure = 15,
    GLKTextureLoaderErrorAlphaPremultiplicationFailure = 16,
    GLKTextureLoaderErrorInvalidEAGLContext = 17,
    GLKTextureLoaderErrorIncompatibleFormatSRGB = 18,
    GLKTextureLoaderErrorUnsupportedTextureTarget = 19,
} NS_ENUM_AVAILABLE(10_8, 5_0);

#pragma mark -
#pragma mark GLKTextureInfo
#pragma mark -

/*
 Alpha state of loaded texture
 */
typedef NS_ENUM(GLint, GLKTextureInfoAlphaState)
{
    GLKTextureInfoAlphaStateNone = 0,
    GLKTextureInfoAlphaStateNonPremultiplied,
    GLKTextureInfoAlphaStatePremultiplied
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 Image origin of loaded texture
 */
typedef NS_ENUM(GLint, GLKTextureInfoOrigin)
{
    GLKTextureInfoOriginUnknown = 0,
    GLKTextureInfoOriginTopLeft,
    GLKTextureInfoOriginBottomLeft
} NS_ENUM_AVAILABLE(10_8, 5_0);

/*
 Immutable Texture Object Data
 */

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKTextureInfo : NSObject <NSCopying>
{
@private
    GLuint                      name;
    GLenum                      target;
    GLuint                      width;
    GLuint                      height;
    GLuint                      depth;
    GLKTextureInfoAlphaState    alphaState;
    GLKTextureInfoOrigin        textureOrigin;
    BOOL                        containsMipmaps;
    GLuint                      mimapLevelCount;
    GLuint                      arrayLength;
}

@property (readonly) GLuint                     name;
@property (readonly) GLenum                     target;
@property (readonly) GLuint                     width;
@property (readonly) GLuint                     height;
@property (readonly) GLuint                     depth;
@property (readonly) GLKTextureInfoAlphaState   alphaState;
@property (readonly) GLKTextureInfoOrigin       textureOrigin;
@property (readonly) BOOL                       containsMipmaps;
@property (readonly) GLuint                     mimapLevelCount;
@property (readonly) GLuint                     arrayLength;

@end

#pragma mark -
#pragma mark GLKTextureLoader
#pragma mark -

typedef void (^GLKTextureLoaderCallback) (GLKTextureInfo * __nullable textureInfo, NSError * __nullable outError);


OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKTextureLoader : NSObject
{
    
}

#pragma mark Synchronous Methods

/*
 Synchronously load an image from disk into an OpenGL texture.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error', which is nil otherwise.
 */
+ (nullable GLKTextureInfo *)textureWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                                               options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                 error:(NSError * __nullable * __nullable)outError;           /* Error description. */

+ (nullable GLKTextureInfo *)textureWithContentsOfURL:(NSURL *)url                                           /* The URL from which to read. */
                                              options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously load a named texture asset from a given bundled into an OpenGL texture
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error', which is nil otherwise.
 */
+ (nullable GLKTextureInfo *)textureWithName:(NSString *)name                                       /* The asset name */
                                 scaleFactor:(CGFloat)scaleFactor                                   /* scale factor of asset to be retrieved */
                                      bundle:(nullable NSBundle*)bundle                             /* The bundle where the named texture is located */
                                     options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                       error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously create a texture from data residing in memory.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error', which is nil otherwise.
 */
+ (nullable GLKTextureInfo *)textureWithContentsOfData:(NSData *)data                                         /* NSData containing image contents. */
                                               options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                 error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously create a texture from a CGImageRef.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error', which is nil otherwise.
 */
+ (nullable GLKTextureInfo *)textureWithCGImage:(CGImageRef)cgImage                                    /* CGImage reference. */
                                        options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                          error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously load six images from disk into an OpenGL cubemap texture.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error' which is nil otherwise.
 */
+ (nullable GLKTextureInfo*)cubeMapWithContentsOfFiles:(NSArray<id> *)paths                                   /* An array of paths (NSStrings or NSURLs). */
                                               options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Otions that control how the image is loaded. */
                                                 error:(NSError * __nullable * __nullable)outError;           /* Error description. */

/*
 Synchronously creates an OpenGL cubemap texture by splitting one image into six parts.
 Takes a single image file where height = 6 * width or width = 6 * height.
 The former (vertical orientation) is preferred to avoid image data extraction overhead.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Returns the generated texture object when the operation is complete, or the operation terminates with an error (returning nil).
 Returned error can be queried via 'error' which is nil otherwise.
 */
+ (nullable GLKTextureInfo*)cubeMapWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                                              options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                                error:(NSError * __nullable * __nullable)outError;           /* Error description. */


+ (nullable GLKTextureInfo*)cubeMapWithContentsOfURL:(NSURL *)url                                           /* File path of image. */
                                             options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                                               error:(NSError * __nullable * __nullable)outError;           /* Error description. */

#pragma mark Asynchronous Methods

/*
 Internally creates a new shared context that will handle the texture creation operations.
 The sharegroup will be released upon releasing the GLKTextureLoader object.
 */
#if TARGET_OS_IPHONE
- (instancetype)initWithSharegroup:(EAGLSharegroup *)sharegroup;
#else
- (instancetype)initWithShareContext:(NSOpenGLContext *)context;
#endif

/*
 Asynchronously load an image from disk into an OpenGL texture.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)textureWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                          options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                            queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

- (void)textureWithContentsOfURL:(NSURL *)url                                           /* File path of image. */
                         options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                           queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
               completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

/*
 Asynchronously load a named texture asset from a given bundled into an OpenGL texture
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)textureWithName:(NSString *)name                                       /* The asset name */
            scaleFactor:(CGFloat)scaleFactor                                   /* scale factor of asset to be retrieved */
                 bundle:(nullable NSBundle*)bundle                             /* The bundle where the named texture is located */
                options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                  queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
      completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

/*
 Asynchronously create a texture from data residing in memory.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)textureWithContentsOfData:(NSData *)data                                         /* NSData containing image contents. */
                          options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                            queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

/*
 Asynchronously create a texture from a CGImageRef.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)textureWithCGImage:(CGImageRef)cgImage                                    /* CGImage reference. */
                   options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                     queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
         completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */


/*
 Asynchronously load six images from disk into an OpenGL cubemap texture.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)cubeMapWithContentsOfFiles:(NSArray<id> *)paths                                   /* An array of paths (NSStrings or NSURLs). */
                           options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                             queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                 completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */


/*
 Asynchronously creates an OpenGL cubemap texture by splitting one image into six parts.
 Takes a single image file where height = 6 * width or width = 6 * height.
 The former (vertical orientation) is preferred to avoid image data extraction overhead.
 Face ordering will always be interpreted as Right(+x), Left(-x), Top(+y), Bottom(-y), Front(+z), Back(-z).
 This coordinate system is left-handed if you think of yourself within the cube. The coordinate system is right-handed if you think of yourself outside of the cube.
 Invokes the block on the provided queue when the operation is complete. If queue is NULL, the main queue will be used.
 */
- (void)cubeMapWithContentsOfFile:(NSString *)path                                       /* File path of image. */
                          options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                            queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
                completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */


- (void)cubeMapWithContentsOfURL:(NSURL *)url                                           /* File path of image. */
                         options:(nullable NSDictionary<NSString*, NSNumber*> *)options /* Options that control how the image is loaded. */
                           queue:(nullable dispatch_queue_t)queue                       /* Dispatch queue, or NULL to use the main queue. */
               completionHandler:(GLKTextureLoaderCallback)block;                       /* Block to be invoked on the above dispatch queue. */

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKVector2.h
//
//  GLKVector2.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_VECTOR_2_H
#define __GLK_VECTOR_2_H

#include <stdbool.h>
#include <math.h>

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#include <GLKit/GLKMathTypes.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#pragma mark -
#pragma mark Prototypes
#pragma mark -

GLK_INLINE GLKVector2 GLKVector2Make(float x, float y);
GLK_INLINE GLKVector2 GLKVector2MakeWithArray(float values[2]);

GLK_INLINE GLKVector2 GLKVector2Negate(GLKVector2 vector);

GLK_INLINE GLKVector2 GLKVector2Add(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE GLKVector2 GLKVector2Subtract(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE GLKVector2 GLKVector2Multiply(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE GLKVector2 GLKVector2Divide(GLKVector2 vectorLeft, GLKVector2 vectorRight);
        
GLK_INLINE GLKVector2 GLKVector2AddScalar(GLKVector2 vector, float value);
GLK_INLINE GLKVector2 GLKVector2SubtractScalar(GLKVector2 vector, float value);
GLK_INLINE GLKVector2 GLKVector2MultiplyScalar(GLKVector2 vector, float value);
GLK_INLINE GLKVector2 GLKVector2DivideScalar(GLKVector2 vector, float value);
        
/*
 Returns a vector whose elements are the larger of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector2 GLKVector2Maximum(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns a vector whose elements are the smaller of the corresponding elements of the vector arguments.
 */
GLK_INLINE GLKVector2 GLKVector2Minimum(GLKVector2 vectorLeft, GLKVector2 vectorRight);
    
/*
 Returns true if all of the first vector's elements are equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector2AllEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns true if all of the vector's elements are equal to the provided value.
 */
GLK_INLINE bool GLKVector2AllEqualToScalar(GLKVector2 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector2AllGreaterThanVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns true if all of the vector's elements are greater than the provided value.
 */
GLK_INLINE bool GLKVector2AllGreaterThanScalar(GLKVector2 vector, float value);
/*
 Returns true if all of the first vector's elements are greater than or equal to all of the second vector's arguments.
 */
GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight);
/*
 Returns true if all of the vector's elements are greater than or equal to the provided value.
 */
GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToScalar(GLKVector2 vector, float value);
    
GLK_INLINE GLKVector2 GLKVector2Normalize(GLKVector2 vector);

GLK_INLINE float GLKVector2DotProduct(GLKVector2 vectorLeft, GLKVector2 vectorRight);
GLK_INLINE float GLKVector2Length(GLKVector2 vector);
GLK_INLINE float GLKVector2Distance(GLKVector2 vectorStart, GLKVector2 vectorEnd);

GLK_INLINE GLKVector2 GLKVector2Lerp(GLKVector2 vectorStart, GLKVector2 vectorEnd, float t);

/*
 Project the vector, vectorToProject, onto the vector, projectionVector.
 */
GLK_INLINE GLKVector2 GLKVector2Project(GLKVector2 vectorToProject, GLKVector2 projectionVector);

#pragma mark -
#pragma mark Implementations
#pragma mark -
    
GLK_INLINE GLKVector2 GLKVector2Make(float x, float y)
{
    GLKVector2 v = { x, y };
    return v;
}
    
GLK_INLINE GLKVector2 GLKVector2MakeWithArray(float values[2])
{
#if defined(__ARM_NEON__)
    float32x2_t v = vld1_f32(values);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_loadl_pi(v, (__m64 *)values);
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { values[0], values[1] };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Negate(GLKVector2 vector)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vneg_f32(*(float32x2_t *)&vector);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_setzero_ps(), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { -vector.v[0] , -vector.v[1] };
    return v;
#endif
}
 
GLK_INLINE GLKVector2 GLKVector2Add(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vadd_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_add_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] + vectorRight.v[0],
                     vectorLeft.v[1] + vectorRight.v[1] };
    return v;
#endif
}
  
GLK_INLINE GLKVector2 GLKVector2Subtract(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vsub_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] - vectorRight.v[0],
                     vectorLeft.v[1] - vectorRight.v[1] };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Multiply(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_mul_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] * vectorRight.v[0],
                     vectorLeft.v[1] * vectorRight.v[1] };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Divide(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t *vLeft = (float32x2_t *)&vectorLeft;
    float32x2_t *vRight = (float32x2_t *)&vectorRight;
    float32x2_t estimate = vrecpe_f32(*vRight);    
    estimate = vmul_f32(vrecps_f32(*vRight, estimate), estimate);
    estimate = vmul_f32(vrecps_f32(*vRight, estimate), estimate);
    float32x2_t v = vmul_f32(*vLeft, estimate);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_div_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorLeft.v[0] / vectorRight.v[0],
                     vectorLeft.v[1] / vectorRight.v[1] };
    return v;
#endif
}

GLK_INLINE GLKVector2 GLKVector2AddScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vadd_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_add_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vector.v[0] + value,
                     vector.v[1] + value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2SubtractScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vsub_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_sub_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else    
    GLKVector2 v = { vector.v[0] - value,
                     vector.v[1] - value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2MultiplyScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector,
                             vdup_n_f32((float32_t)value));
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_mul_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vector.v[0] * value,
                     vector.v[1] * value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2DivideScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t values = vdup_n_f32((float32_t)value);
    float32x2_t estimate = vrecpe_f32(values);    
    estimate = vmul_f32(vrecps_f32(values, estimate), estimate);
    estimate = vmul_f32(vrecps_f32(values, estimate), estimate);
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector, estimate);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_div_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vector), _mm_set1_ps(value));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vector.v[0] / value,
                     vector.v[1] / value };
    return v;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Maximum(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmax_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_max_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 max = vectorLeft;
    if (vectorRight.v[0] > vectorLeft.v[0])
        max.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] > vectorLeft.v[1])
        max.v[1] = vectorRight.v[1];
    return max;
#endif
}

GLK_INLINE GLKVector2 GLKVector2Minimum(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmin_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    return *(GLKVector2 *)&v;
#elif defined(GLK_SSE3_INTRINSICS)
    __m128 v;
    v = _mm_min_ps(_mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorLeft), _mm_loadl_pi(_mm_setzero_ps(), (__m64 *)&vectorRight));
    return *(GLKVector2 *)&v;
#else
    GLKVector2 min = vectorLeft;
    if (vectorRight.v[0] < vectorLeft.v[0])
        min.v[0] = vectorRight.v[0];
    if (vectorRight.v[1] < vectorLeft.v[1])
        min.v[1] = vectorRight.v[1];
    return min;
#endif
}
   
GLK_INLINE bool GLKVector2AllEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vceq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllEqualToScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vceq_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] == value &&
        vector.v[1] == value)
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vcgt_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] > vectorRight.v[0] &&
        vectorLeft.v[1] > vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vcgt_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] > value &&
        vector.v[1] > value)
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToVector2(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v1 = *(float32x2_t *)&vectorLeft;
    float32x2_t v2 = *(float32x2_t *)&vectorRight;
    uint32x2_t vCmp = vcge_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vectorLeft.v[0] >= vectorRight.v[0] &&
        vectorLeft.v[1] >= vectorRight.v[1])
        compare = true;
    return compare;
#endif
}

GLK_INLINE bool GLKVector2AllGreaterThanOrEqualToScalar(GLKVector2 vector, float value)
{
#if defined(__ARM_NEON__)
    float32x2_t v1 = *(float32x2_t *)&vector;
    float32x2_t v2 = vdup_n_f32(value);
    uint32x2_t vCmp = vcge_f32(v1, v2);
    uint32x2_t vAnd = vand_u32(vCmp, vext_u32(vCmp, vCmp, 1));
    vAnd = vand_u32(vAnd, vdup_n_u32(1));
    return (bool)vget_lane_u32(vAnd, 0);
#else
    bool compare = false;
    if (vector.v[0] >= value &&
        vector.v[1] >= value)
        compare = true;
    return compare;
#endif
}
    
GLK_INLINE GLKVector2 GLKVector2Normalize(GLKVector2 vector)
{
    float scale = 1.0f / GLKVector2Length(vector);
    GLKVector2 v = GLKVector2MultiplyScalar(vector, scale);
    return v;
}

GLK_INLINE float GLKVector2DotProduct(GLKVector2 vectorLeft, GLKVector2 vectorRight)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vectorLeft,
                             *(float32x2_t *)&vectorRight);
    v = vpadd_f32(v, v);
    return vget_lane_f32(v, 0);
#else
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1];
#endif
}

GLK_INLINE float GLKVector2Length(GLKVector2 vector)
{
#if defined(__ARM_NEON__)
    float32x2_t v = vmul_f32(*(float32x2_t *)&vector,
                             *(float32x2_t *)&vector);
    v = vpadd_f32(v, v);
    return sqrt(vget_lane_f32(v, 0)); 
#else
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1]);
#endif
}

GLK_INLINE float GLKVector2Distance(GLKVector2 vectorStart, GLKVector2 vectorEnd)
{
    return GLKVector2Length(GLKVector2Subtract(vectorEnd, vectorStart));
}
    
GLK_INLINE GLKVector2 GLKVector2Lerp(GLKVector2 vectorStart, GLKVector2 vectorEnd, float t)
{
#if defined(__ARM_NEON__)
    float32x2_t vDiff = vsub_f32(*(float32x2_t *)&vectorEnd,
                                 *(float32x2_t *)&vectorStart);
    vDiff = vmul_f32(vDiff, vdup_n_f32((float32_t)t));
    float32x2_t v = vadd_f32(*(float32x2_t *)&vectorStart, vDiff);
    return *(GLKVector2 *)&v;
#else
    GLKVector2 v = { vectorStart.v[0] + ((vectorEnd.v[0] - vectorStart.v[0]) * t),
                     vectorStart.v[1] + ((vectorEnd.v[1] - vectorStart.v[1]) * t) };
    return v;
#endif
}

GLK_INLINE GLKVector2 GLKVector2Project(GLKVector2 vectorToProject, GLKVector2 projectionVector)
{
    float scale = GLKVector2DotProduct(projectionVector, vectorToProject) / GLKVector2DotProduct(projectionVector, projectionVector);
    GLKVector2 v = GLKVector2MultiplyScalar(projectionVector, scale);
    return v;
}

#ifdef __cplusplus
}
#endif

#endif /* __GLK_VECTOR_2_H */
// ==========  GLKit.framework/Headers/GLKSkyboxEffect.h
//
//  GLKSkyboxEffect.h
//  GLKit
//
//  Copyright 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKBaseEffect.h>


/*
 GLKSkyboxEffect

 GLKSkyboxEffect implements common skybox functionality as is used by many of todays games
 and simulations.  A skybox is a textured cube that encloses the boundaries of the object
 space of a 3D graphics application or game.  It provides a visual horizon in all camera
 directions within 3D object space.

 GLKSkyboxEffect requires at least an OpenGL ES 2.0 context on iOS and an OpenGL Core
 Profile context on OS X. This context must be initialized and made current prior to creating
 or initializing GLKSkyboxEffect instances.  No OpenGL context state settings are
 modified when a GLKSkyboxEffect instance is created or its properties set.  When
 -[GLKSkyboxEffect prepareToDraw] is called it modifies the following state:

      GL_CURRENT_PROGRAM
      GL_TEXTURE_BINDING_CUBE_MAP
      GL_VERTEX_ARRAY_BINDING_OES
      GL_ARRAY_BUFFER_BINDING
      GL_VERTEX_ATTRIB_ARRAY_ENABLED (GLKVertexAttribPosition)

 For performance reasons GLKSkyboxEffect does not restore any of these state settings.
 It is up to the client application to save/restore/set these state elements as they choose.

 A cube mapped texture name must be provided to GLKSkyboxEffect to provide it texture
 data for the 6 faces of the skybox cube.  Care must be taken when preparing the 
 cubemap texture to prevent seams from appearing at the interfaces between adjacent
 faces.

 Unlike other named effects, GLKSkyboxEffect provides a -draw method and requires no ancillary
 vertex attribute setup because the class maintains the simple, unambiguous geometry data
 required to draw the skybox internally.


 The following (4) steps are required to use GLKSkyboxEffect:

      (1) Allocate and initialize an instance of GLKSkyboxEffect
      
      skybox = [[GLKSkyboxEffect alloc] init];

      (2) Create a cube map texture for the skybox

      glGenTextures(1, &cubeMapName);
      glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapName);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      
      GLenum cubeMapBase = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
      
      for(face = 0; face < 6; face++)
          glTexImage2D(cubeMapBase + face, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, faceData[face]);

      (3) Configure the skybox effect transform, location, size, and texture properties

      skybox.center = center;
      skybox.xSize = xSize;
      skybox.ySize = ySize;
      skybox.zSize = zSize;
      skybox.textureCubeMap = cubeMapName;     // created in step (2) above

      (4) For each frame drawn:  Update properties that change per frame.  Synchronize the changed effect state
          by calling -[GLKSkyboxEffect prepareToDraw].  Draw the the skybox.

      skybox.transform.modelviewMatrix = modelviewMatrix;
      [skybox prepareToDraw];
      [skybox draw];
*/

NS_ASSUME_NONNULL_BEGIN

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKSkyboxEffect : NSObject <GLKNamedEffect>
{
    @private
    
    // Center of the skybox in object/world coordinates
    GLKVector3                      _center;                       // 3 element vector of GLfloats
    
    // Dimensions of our skybox.  X extents, for example, are (center[0] - xSize / 2.0) & (center[0] + xSize / 2.0)
    GLfloat                         _xSize, _ySize, _zSize;
    
    // Cube map GL texture name
    GLKEffectPropertyTexture        *_textureCubeMap;
    
    // Skybox Transform
    GLKEffectPropertyTransform      *_transform;
    
    // Label for effect
    NSString                        *_label;
}


// Sync all effect changes for consistent state when drawing
- (void) prepareToDraw;

// Draw skybox
- (void) draw;

// Properties                                                                           // Default Value
@property (nonatomic, assign)         GLKVector3                 center;                // { 0.0, 0.0, 0.0 }
@property (nonatomic, assign)         GLfloat                    xSize, ySize, zSize;   // 1.0, 1.0, 1.0
@property (nonatomic, readonly)       GLKEffectPropertyTexture   *textureCubeMap;       // name == 0, target == GL_TEXTURE_CUBE_MAP
@property (nonatomic, readonly)       GLKEffectPropertyTransform *transform;            // Identity for all matrices
@property (nullable, nonatomic, copy) NSString                   *label;                // nil
@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKModel.h
//
//  GLKModel.h
//
//  Copyright (c) 2014 Apple. All rights reserved.
//
#import <Availability.h>
#import <ModelIO/ModelIO.h>
#import <GLKit/GLKitBase.h>

/*!
 @group GLKModelErrors
 */

/*!
 @constant kGLKModelErrorDomain
 */
GLK_EXTERN NSString * __nonnull const kGLKModelErrorDomain OPENGL_DEPRECATED(10.11,10.14) OPENGLES_DEPRECATED(ios(9.0, 12.0), tvos(9.0, 12.0));
/*!
 @constant kGLKModelErrorKey
 */
GLK_EXTERN NSString * __nonnull const kGLKModelErrorKey OPENGL_DEPRECATED(10.11,10.14) OPENGLES_DEPRECATED(ios(9.0,12.0), tvos(9.0,12.0));



/*!
 @class GLKMeshBufferAllocator
 @abstract Allocator passed to MDLAsset init method to load vertex and index data directly into OpenGL buffer object
 */

OPENGL_DEPRECATED(10.11,10.14) OPENGLES_DEPRECATED(ios(9.0,12.0), tvos(9.0,12.0))
@interface GLKMeshBufferAllocator : NSObject<MDLMeshBufferAllocator>

@end

/*!
 @class GLKMeshBuffer
 @abstract Mesh buffers created when  needs to allocate memory to back vertex or index data
 @discussion Memory backing these buffer are OpenGL buffers. Model I/O will load index and vertex data from from a model asset directly in to the OpenGL buffer object.
 */

OPENGL_DEPRECATED(10.11,10.14) OPENGLES_DEPRECATED(ios(9.0,12.0), tvos(9.0, 12.0))
@interface GLKMeshBuffer : NSObject <MDLMeshBuffer>

/*!
 @method length
 @abstract Size in bytes of the buffer allocation
 */
@property (nonatomic, readonly) NSUInteger length;

/*!
 @property allocator
 @abstract Allocator object used to create this buffer.
 @discussion This allcoator used for copy and relayout operations (such as when a new vertex descriptor is applied to a vertex buffer)
 */
@property (nonatomic, readonly, nonnull) GLKMeshBufferAllocator *allocator;

/*!
 @property glBufferName
 @abstract glBufferName for buffer object backing vertex/index data
 @discussion Many GLKMeshBuffers may reference the same OpenGL buffer object, but each with its own offset.  (i.e. Many GLKMeshBuffers may be suballocated from a single OpenGL buffer object)
 */
@property (nonatomic, readonly) GLuint glBufferName;

/*!
 @property offset
 @abstract Byte offset of the data within the OpenGL buffer
 */
@property (nonatomic, readonly) NSUInteger offset;


/*!
 @property zone
 @abstract Zone from which this buffer was created (if it was created witha zone)
 @discussion A single GL buffer is allocated for each zone.  Each zone could have many GLKMeshBuffers, each with it's own offset.  If a GLKMeshBufferAllocator is used, Model I/O will attempt to load all vertex and indexData of a single model into a single zone.  So although there maybe many GLKMeshBuffers for a model they will be backed with the same contigous GL buffer.
 */
@property (nonatomic, readonly, nullable) id <MDLMeshBufferZone> zone;

/*!
 @property type
 @abstract the intended type of the buffer
 */
@property (nonatomic, readonly) MDLMeshBufferType type;

@end

@class GLKMesh;


OPENGL_DEPRECATED(10.11,10.14) OPENGLES_DEPRECATED(ios(9.0,12.0), tvos(9.0, 12.0))
@interface GLKSubmesh : NSObject

/*!
 @method init
 @abstract Must be initialized by a GLKMesh object
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/*!
 @property type
 @abstract Type of data in the elementBuffer (aka indexBuffer)
 @discussion This value should be used for the type parameter of glDrawElements
 */
@property (nonatomic, readonly) GLenum type;

/*!
 @property mode
 @abstract Primitive type mode value of data in the elementBuffer (aka indexBuffer)
 @discussion This value should be used for the mode parameter in glDrawElements
 */
@property (nonatomic, readonly) GLenum mode;

/*!
 @property elementCount
 @abstract Number of elements (aka indicies) in the elementBuffer (aka indexBuffer)
 @discussion This value should be used for the count parameter in glDrawElements
*/
@property (nonatomic, readonly) GLsizei elementCount;

/*!
 @property elementBuffer
 @abstract Name of buffer object with index data
 @discussion The buffer name to be used with DrawElements
 */
@property (nonatomic, readonly, nonnull) GLKMeshBuffer *elementBuffer;

/*!
 @property mesh
 @abstract Parent GLKit mesh containing vertex data of this object
 @discussion Buffer of this parent mesh should be set in the encoder before a drawIndexedPrimitives call is made
 */
@property (nonatomic, readonly, weak, nullable) GLKMesh *mesh;

/*!
 @property name
 @abstract Name from the original MDLSubmesh object.
 @discussion Although not directly used by this object, the application may use this to identify the submesh in it renderer/scene/world.
 */
@property (nonatomic, readonly, nonnull) NSString *name;

@end


OPENGL_DEPRECATED(10.11,10.14) OPENGLES_DEPRECATED(ios(9.0,12.0), tvos(9.0, 12.0))
@interface GLKMesh : NSObject

/*!
 @method init
 @abstract Must initialize with a mesh
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithMesh:error:
 @abstract Initialize the mesh and the mesh's submeshes
 @discussion This does NOT initialize any meshes that are children of the Model I/O mesh
 @error Pointer to an NSError object which will be set if an error occurred
 @param mesh Model I/O Mesh from which to create this GLKit mesh
 */
- (nullable instancetype)initWithMesh:(nonnull MDLMesh*)mesh
                                error:(NSError * __nullable * __nullable)error;

/*!
 @method newMeshesFromAsset:sourceMeshes:error:
 @abstract Initialize all meshes in a Model I/O asset.
 @result An array of GLKit meshes built an asset
 @param asset Model I/O asset from which to create GLKit meshes
 @param sourceMeshes Model I/O meshes corresponding the newly created GLKMeshes
 @param error Pointer to an NSError object set if an error occurred
 @param return GLKit meshes created from the Model I/O asset
 @dicussion A convenience method to create GLKit meshes from each mesh in a Model/IO asset.  Resulting meshes are returned while Model I/O meshes from which they were generated will appear in the sourceMeshes array.
 */
+ (nullable NSArray<GLKMesh*>*) newMeshesFromAsset:(nonnull MDLAsset *)asset
                                      sourceMeshes:(NSArray<MDLMesh*>* __nullable * __nullable)sourceMeshes
                                             error:(NSError * __nullable * __nullable)error;

/*!
 @property vertexCount
 @abstract Number of verticies in the vertexBuffers
 */
@property (nonatomic, readonly) NSUInteger vertexCount;

/*!
 @property vertexBuffers
 @abstract Array of buffers in which mesh vertex data resides
 */
@property (nonatomic, readonly, nonnull) NSArray<GLKMeshBuffer*> *vertexBuffers;

/*!
 @property vertexDescriptor
 @abstract Model I/O vertex descriptor specifying the layout of data in vertexBuffers
 @discussion This is not directly used by this object, but the application can use this information to determine rendering state or setup a vertex attribute object.
 */
@property (nonatomic, readonly, nonnull) MDLVertexDescriptor *vertexDescriptor;

/*!
 @property submeshes
 @abstract Submeshes containing index buffers to rendering mesh verticies.
 @discussion Submeshes may also contain texture materials to apply when rendering this object
 */
@property (nonatomic, readonly, nonnull) NSArray<GLKSubmesh *> *submeshes;

/*!
 @property name
 @abstract Name of the mesh copies from the originating Model I/O mesh
 @discussion Can be used by the app to identiry the mesh in it's scene/world/renderer etc.
 */
@property (nonatomic, readonly, nonnull) NSString* name;

@end

/*!
 @struct GLKVertexAttributeParameters
 @abstract Structure for parameters to use in glVertexAttribPointer given a MDLVertexForamt
 */
struct _GLKVertexAttributeParameters{
    GLenum    type;
    GLint     size;
    GLboolean normalized;
};
typedef struct _GLKVertexAttributeParameters GLKVertexAttributeParameters;

/*!
 @struct GLKVertexAttributeParametersFromModelIO
 @abstract Returns parameters to use in a call to glVertexAttribPointer given a MDLVertexFormat
 */
GLK_EXTERN
GLKVertexAttributeParameters GLKVertexAttributeParametersFromModelIO(MDLVertexFormat vertexFormat);
// ==========  GLKit.framework/Headers/GLKReflectionMapEffect.h
//
//  GLKReflectionMapEffect.h
//  GLKit
//
//  Copyright (c) 2011-2012 Apple Inc. All rights reserved.
//

#import <GLKit/GLKBaseEffect.h>

/*
 GLKReflectionMapEffect

 GLKReflectionMapEffect is a subclass of GLKBaseEffect.  It is expected that GLKBaseEffect 
 functionality will be used in combination with GLKReflectionMapEffect.

 GLKReflectionMapEffect implements common reflection mapping functionality as is used by many of
 todays games and simulations.  A reflection or environment map can be thought of as a texture
 mapped polyhedral or spherical mesh that encloses a 3D model.  When the model is rendered
 surface normals from the model are used to calculate reflection vectors which intersect
 the environment map at some location.  The environment map texture color at this location
 is used to impart a modulated environment map color on the model giving the appearance that
 the shiny model is reflecting its surroundings to the viewer.

 The polyhedral shape used for GLKReflectionMapEffect is a cube.

 Because reflection mapping relies on surface normals to compute the intersection between
 reflected rays and the environment map the GLKVertexAttribNormal array must be enabled
 in order for GLKReflectionMapEffect to work properly. The normals are always normalized.

 GLKReflectionMapEffect requires at least an OpenGL ES 2.0 context on iOS and an OpenGL Core
 Profile context on OS X. This context must be initialized and made current prior to creating
 or initializing GLKReflectionMapEffect instances.  No OpenGL context state settings are
 modified when a GLKReflectionMapEffect instance is created or its properties set.  When
 -[GLKReflectionMapEffect prepareToDraw] is called it modifies the following state:

      GL_CURRENT_PROGRAM
      GL_TEXTURE_BINDING_CUBE_MAP

 For performance reasons GLKReflectionMapEffect does not restore any of these state settings.
 It is up to the client application to save/restore/set these state elements as they choose.

 A cube mapped texture name must be provided to GLKReflectionMapEffect to provide it texture
 data for the 6 faces of the environment map.

 GLKReflectionMapEffect reflection vectors are computed in eye space per section 2.11.4 of the
 OpenGL 2.1 desktop specification for the GL_REFLECTION_MAP texgen mode.  Typical reflection
 mapping uses an environment map with a fixed position (e.g. the sky in a real world rendering)
 and will accurately map the reflection map on the model regardless of the modelview transformation.
 To achieve this effect decompose the modelview matrix into its model and view components
 (i.e. the transforms on the object are the model and the transforms on the view are the camera).
 Then undo the viewing transform by inverting the viewing matrix - call this Vinv.  Now, starting
 with Vinv, treat it as the canonical normal matrix by applying an inverse transpose to it and
 choosing the upper 3x3 elements of the result.  inverseTranspose(Vinv) simplifies to Vtranspose.
 To apply this result to GLKReflectionMapEffect set its matrix property as follows:

      reflectionMapEffect.matrix = GLKMatrix4GetMatrix3(Vtranspose);

 to get correct, view-angle independent reflection mapping.


 The following (5) steps are required to use GLKReflectionMapEffect:

      (1) Allocate and initialize an instance of GLKReflectionMapEffect
      
      reflectionMapEffect = [[GLKReflectionMapEffect alloc] init];
   
      (2) Initialize vertex attribute / vertex array state preferrably with a vertex array object
          for the model or scene to be drawn.
   
      glGenVertexArraysOES(1, &vaoName);
      glBindVertexArrayOES(vaoName);

      // Create and initialize VBO for each vertex attribute
      // The example below shows an example of setup up the position and normal vertex attributes.
      // Specifying and binding a GLKVertexAttribNormal array attribute is required for GLKReflectionMapEffect
      // to work properly. The normals are always normalized.

      glGenBuffers(1, &positionVBO);
      glBindBuffer(positionVBO);
      glBufferData(GL_ARRAY_BUFFER, vboSize, dataBufPtr, GL_STATIC_DRAW);
      glVertexAttribPointer(GLKVertexAttribPosition, size, type, normalize, stride, NULL);

      glGenBuffers(1, &normalVBO);
      glBindBuffer(normalVBO);
      glBufferData(GL_ARRAY_BUFFER, vboSize, dataBufPtr, GL_STATIC_DRAW);
      glVertexAttribPointer(GLKVertexAttribNormal, size, type, normalize, stride, NULL);

      ... repeat the steps above for other desired vertex attributes

      glBindVertexArrayOES(0);   // unbind the VAO we created above

      (3) Create a cube map texture for the reflection map

      glGenTextures(1, &textureCubeMap);
      glBindTexture(GL_TEXTURE_CUBE_MAP, textureCubeMap);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      
      GLenum cubeMapBase = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
      
      for(face = 0; face < 6; face++)
          glTexImage2D(cubeMapBase + face, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, faceData[face]);

      (4) Set the textureCubeMap property to our new GL cube map and turn on reflection mapping

      reflectionMapEffect.enable = GL_TRUE;
      reflectionMapEffect.textureCubeMap = textureCubeMap;     // created in step (2) above

      (5) For each frame drawn:  Update properties that change per frame.  Synchronize the changed effect state
          by calling -[GLKReflectionMapEffect prepareToDraw].  Draw the model with the effect

      reflectionMapEffect.transform.modelviewMatrix = modelviewMatrix;
      [reflectionMapEffect prepareToDraw];
      glBindVertexArrayOES(vaoName);
      glDrawArrays(GL_TRIANGLE_STRIP, 0, vertCt);
*/

NS_ASSUME_NONNULL_BEGIN

OPENGL_DEPRECATED(10.8,10.14) OPENGLES_DEPRECATED(ios(5.0,12.0), tvos(9.0,12.0))
@interface GLKReflectionMapEffect : GLKBaseEffect <GLKNamedEffect>
{
    @private

    // Cube map GL texture name
    GLKEffectPropertyTexture        *_textureCubeMap;
    
    // Reflection map matrix
    GLKMatrix3                      _matrix;
}


// Sync all effect changes for consistent state when drawing
- (void) prepareToDraw;

// Properties                                                                           // Default Value
@property (nonatomic, readonly) GLKEffectPropertyTexture           *textureCubeMap;     // GL Texture Name == 0
@property (nonatomic, assign)   GLKMatrix3                         matrix;              // Identity

@end
NS_ASSUME_NONNULL_END
// ==========  GLKit.framework/Headers/GLKMathUtils.h
//
//  GLKMathUtils.h
//  GLKit
//
//  Copyright (c) 2011-2012, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATH_UTILS_H
#define __GLK_MATH_UTILS_H

#include <math.h>
#include <stdbool.h>

#include <GLKit/GLKMathTypes.h>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN
#endif

#ifdef __cplusplus
extern "C" {
#endif

GLK_INLINE float GLKMathDegreesToRadians(float degrees) { return degrees * (M_PI / 180); };
GLK_INLINE float GLKMathRadiansToDegrees(float radians) { return radians * (180 / M_PI); };
    
GLKVector3 GLKMathProject(GLKVector3 object, GLKMatrix4 model, GLKMatrix4 projection, int *viewport);
GLKVector3 GLKMathUnproject(GLKVector3 window, GLKMatrix4 model, GLKMatrix4 projection, int *viewport, bool  * __nullable success);

#ifdef __OBJC__
NSString * NSStringFromGLKMatrix2(GLKMatrix2 matrix);
NSString * NSStringFromGLKMatrix3(GLKMatrix3 matrix);
NSString * NSStringFromGLKMatrix4(GLKMatrix4 matrix);
    
NSString * NSStringFromGLKVector2(GLKVector2 vector);
NSString * NSStringFromGLKVector3(GLKVector3 vector);
NSString * NSStringFromGLKVector4(GLKVector4 vector);
    
NSString * NSStringFromGLKQuaternion(GLKQuaternion quaternion);
NS_ASSUME_NONNULL_END
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATH_UTILS_H */
