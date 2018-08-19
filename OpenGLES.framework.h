// ==========  OpenGLES.framework/Headers/EAGLDrawable.h
/*
    Copyright:  (c) 2006-2013 Apple Inc. All rights reserved.
*/

#ifndef _EAGL_DRAWABLE_H_
#define _EAGL_DRAWABLE_H_

#include <OpenGLES/EAGL.h>
#include <OpenGLES/OpenGLESAvailability.h>


/************************************************************************/
/* Keys for EAGLDrawable drawableProperties dictionary                  */
/*                                                                      */
/* kEAGLDrawablePropertyRetainedBacking:                                */
/*  Type: NSNumber (boolean)                                            */
/*  Legal Values: True/False                                            */
/*  Default Value: False                                                */
/*  Description: True if EAGLDrawable contents are retained after a     */
/*               call to presentRenderbuffer.  False, if they are not   */
/*                                                                      */
/* kEAGLDrawablePropertyColorFormat:                                    */
/*  Type: NSString                                                      */
/*  Legal Values: kEAGLColorFormat*                                     */
/*  Default Value: kEAGLColorFormatRGBA8                                */
/*  Description: Format of pixels in renderbuffer                       */
/************************************************************************/
EAGL_EXTERN NSString * const kEAGLDrawablePropertyRetainedBacking;
EAGL_EXTERN NSString * const kEAGLDrawablePropertyColorFormat;

/************************************************************************/
/* Values for kEAGLDrawablePropertyColorFormat key                      */
/************************************************************************/
EAGL_EXTERN NSString * const kEAGLColorFormatRGBA8;
EAGL_EXTERN NSString * const kEAGLColorFormatRGB565;
EAGL_EXTERN NSString * const kEAGLColorFormatSRGBA8 NS_AVAILABLE_IOS(7_0);

/************************************************************************/
/* EAGLDrawable Interface                                               */
/************************************************************************/

@protocol EAGLDrawable 

/* Contains keys from kEAGLDrawableProperty* above */
@property(copy) NSDictionary* drawableProperties;

@end

/* Extends EAGLContext interface */
OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0))
@interface EAGLContext (EAGLContextDrawableAdditions)

/* Attaches an EAGLDrawable as storage for the OpenGL ES renderbuffer object bound to <target> */
- (BOOL)renderbufferStorage:(NSUInteger)target fromDrawable:(id<EAGLDrawable>)drawable;

/* Request the native window system display the OpenGL ES renderbuffer bound to <target> */
- (BOOL)presentRenderbuffer:(NSUInteger)target;

@end /* EAGLDrawable protocol */


#endif /* _EAGL_DRAWABLE_H_ */

// ==========  OpenGLES.framework/Headers/gltypes.h
/*
	Copyright:	(c) 2010-2012 Apple Inc. All rights reserved.
*/
#ifndef __gltypes_h_
#define __gltypes_h_

#include <stdint.h>

typedef uint32_t GLbitfield;
typedef uint8_t  GLboolean;
typedef int8_t   GLbyte;
typedef float    GLclampf;
typedef uint32_t GLenum;
typedef float    GLfloat;
typedef int32_t  GLint;
typedef int16_t  GLshort;
typedef int32_t  GLsizei;
typedef uint8_t  GLubyte;
typedef uint32_t GLuint;
typedef uint16_t GLushort;
typedef void     GLvoid;

#if !defined(GL_ES_VERSION_2_0)
typedef char     GLchar;
#endif
typedef int32_t  GLclampx;
typedef int32_t  GLfixed;
#if !defined(GL_ES_VERSION_3_0)
typedef uint16_t GLhalf;
#endif
#if !defined(GL_APPLE_sync) && !defined(GL_ES_VERSION_3_0)
typedef int64_t  GLint64;
typedef struct __GLsync *GLsync;
typedef uint64_t GLuint64;
#endif
typedef intptr_t GLintptr;
typedef intptr_t GLsizeiptr;

#endif
// ==========  OpenGLES.framework/Headers/ES2/glext.h
#ifndef __gl_es20ext_h_
#define __gl_es20ext_h_

#include <OpenGLES/ES2/gl.h>
#include <Availability.h>
#ifndef GLES_API_DEPRICATED
#define GLES_API_DEPRICATED(__version__) __API_DEPRECATED("OpenGLES is depricated on iOS", ios(__version__, 12.0))
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
**
** http://oss.sgi.com/projects/FreeB
**
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
**
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
**
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif

#define GL_APPLE_clip_distance                                  1
#define GL_APPLE_color_buffer_packed_float                      1
#define GL_APPLE_copy_texture_levels                            1
#define GL_APPLE_framebuffer_multisample                        1
#define GL_APPLE_rgb_422                                        1
#define GL_APPLE_sync                                           1
#define GL_APPLE_texture_format_BGRA8888                        1
#define GL_APPLE_texture_max_level                              1
#define GL_APPLE_texture_packed_float                           1
#define GL_EXT_blend_minmax                                     1
#define GL_EXT_color_buffer_half_float                          1
#define GL_EXT_debug_label                                      1
#define GL_EXT_debug_marker                                     1
#define GL_EXT_discard_framebuffer                              1
#define GL_EXT_draw_instanced                                   1
#define GL_EXT_instanced_arrays                                 1
#define GL_EXT_map_buffer_range                                 1
#define GL_EXT_occlusion_query_boolean                          1
#define GL_EXT_pvrtc_sRGB                                       1
#define GL_EXT_read_format_bgra                                 1
#define GL_EXT_separate_shader_objects                          1
#define GL_EXT_shader_framebuffer_fetch                         1
#define GL_EXT_shader_texture_lod                               1
#define GL_EXT_shadow_samplers                                  1
#define GL_EXT_sRGB                                             1
#define GL_EXT_texture_filter_anisotropic                       1
#define GL_EXT_texture_rg                                       1
#define GL_EXT_texture_storage                                  1
#define GL_IMG_read_format                                      1
#define GL_IMG_texture_compression_pvrtc                        1
#define GL_OES_depth_texture                                    1
#define GL_OES_depth24                                          1
#define GL_OES_element_index_uint                               1
#define GL_OES_fbo_render_mipmap                                1
#define GL_OES_mapbuffer                                        1
#define GL_OES_packed_depth_stencil                             1
#define GL_OES_rgb8_rgba8                                       1
#define GL_OES_standard_derivatives                             1
#define GL_OES_texture_float                                    1
#define GL_OES_texture_half_float                               1
#define GL_OES_texture_half_float_linear                        1
#define GL_OES_vertex_array_object                              1

/**************************************************************************/

/*------------------------------------------------------------------------*
 * APPLE extension tokens
 *------------------------------------------------------------------------*/
#if GL_APPLE_color_buffer_packed_float
#define GL_R11F_G11F_B10F_APPLE                                 0x8C3A
#define GL_RGB9_E5_APPLE                                        0x8C3D
#endif

#if GL_APPLE_clip_distance
#define GL_CLIP_DISTANCE0_APPLE           0x3000
#define GL_CLIP_DISTANCE1_APPLE           0x3001
#define GL_CLIP_DISTANCE2_APPLE           0x3002
#define GL_CLIP_DISTANCE3_APPLE           0x3003
#define GL_CLIP_DISTANCE4_APPLE           0x3004
#define GL_CLIP_DISTANCE5_APPLE           0x3005
#define GL_CLIP_DISTANCE6_APPLE           0x3006
#define GL_CLIP_DISTANCE7_APPLE           0x3007
#define GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#endif

#if GL_APPLE_framebuffer_multisample
#define GL_RENDERBUFFER_SAMPLES_APPLE                           0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE             0x8D56
#define GL_MAX_SAMPLES_APPLE                                    0x8D57
#define GL_READ_FRAMEBUFFER_APPLE                               0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE                               0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE                       0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE                       0x8CAA
#endif

#if GL_APPLE_texture_packed_float
#define GL_UNSIGNED_INT_10F_11F_11F_REV_APPLE                   0x8C3B
#define GL_UNSIGNED_INT_5_9_9_9_REV_APPLE                       0x8C3E
#endif

#if GL_APPLE_rgb_422
#define GL_RGB_422_APPLE                                        0x8A1F
#define GL_UNSIGNED_SHORT_8_8_APPLE                             0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE                         0x85BB
#endif

#if GL_APPLE_sync
#define GL_MAX_SERVER_WAIT_TIMEOUT_APPLE                        0x9111
#define GL_OBJECT_TYPE_APPLE                                    0x9112
#define GL_SYNC_CONDITION_APPLE                                 0x9113
#define GL_SYNC_STATUS_APPLE                                    0x9114
#define GL_SYNC_FLAGS_APPLE                                     0x9115
#define GL_SYNC_FENCE_APPLE                                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE                     0x9117
#define GL_UNSIGNALED_APPLE                                     0x9118
#define GL_SIGNALED_APPLE                                       0x9119
#define GL_ALREADY_SIGNALED_APPLE                               0x911A
#define GL_TIMEOUT_EXPIRED_APPLE                                0x911B
#define GL_CONDITION_SATISFIED_APPLE                            0x911C
#define GL_WAIT_FAILED_APPLE                                    0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT_APPLE                        0x00000001
#define GL_TIMEOUT_IGNORED_APPLE                                0xFFFFFFFFFFFFFFFFull
#define GL_SYNC_OBJECT_APPLE                                    0x8A53
#endif

#if GL_APPLE_texture_format_BGRA8888
#define GL_BGRA_EXT                                             0x80E1
#endif

#if GL_APPLE_texture_format_BGRA8888 || GL_IMG_read_format
#define GL_BGRA                                                 0x80E1
#endif

#if GL_APPLE_texture_max_level
#define GL_TEXTURE_MAX_LEVEL_APPLE                              0x813D
#endif

/*------------------------------------------------------------------------*
 * EXT extension tokens
 *------------------------------------------------------------------------*/
#if GL_EXT_blend_minmax
#define GL_MIN_EXT                                              0x8007
#define GL_MAX_EXT                                              0x8008
#endif

#if GL_EXT_color_buffer_half_float
#define GL_RGBA16F_EXT                                          0x881A
#define GL_RGB16F_EXT                                           0x881B
#define GL_RG16F_EXT                                            0x822F
#define GL_R16F_EXT                                             0x822D
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT            0x8211
#define GL_UNSIGNED_NORMALIZED_EXT                              0x8C17
#endif

#if GL_EXT_debug_label
#define GL_BUFFER_OBJECT_EXT                                    0x9151
#define GL_SHADER_OBJECT_EXT                                    0x8B48
#define GL_PROGRAM_OBJECT_EXT                                   0x8B40
#define GL_QUERY_OBJECT_EXT                                     0x9153
#define GL_VERTEX_ARRAY_OBJECT_EXT                              0x9154
#define GL_PROGRAM_PIPELINE_OBJECT_EXT                          0x8A4F
/*      GL_SYNC_OBJECT_APPLE */
#endif

#if GL_EXT_discard_framebuffer
#define GL_COLOR_EXT                                            0x1800
#define GL_DEPTH_EXT                                            0x1801
#define GL_STENCIL_EXT                                          0x1802
#endif

#if GL_EXT_instanced_arrays
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR_EXT                      0x88FE
#endif

#if GL_EXT_map_buffer_range
#define GL_MAP_READ_BIT_EXT                                     0x0001
#define GL_MAP_WRITE_BIT_EXT                                    0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT                         0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT                        0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT                           0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT                           0x0020
#endif

#if GL_EXT_occlusion_query_boolean
#define GL_ANY_SAMPLES_PASSED_EXT                               0x8C2F
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT                  0x8D6A
#define GL_CURRENT_QUERY_EXT                                    0x8865
#define GL_QUERY_RESULT_EXT                                     0x8866
#define GL_QUERY_RESULT_AVAILABLE_EXT                           0x8867
#endif

#if GL_EXT_pvrtc_sRGB
#define GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT                     0x8A54
#define GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT                     0x8A55
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT               0x8A56
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT               0x8A57
#endif

#if GL_EXT_read_format_bgra
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT                       0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT                       0x8366
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                           0x8366
#endif

#if GL_EXT_read_format_bgra || GL_IMG_read_format
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
#endif

#if GL_EXT_separate_shader_objects
#define GL_VERTEX_SHADER_BIT_EXT                                0x00000001
#define GL_FRAGMENT_SHADER_BIT_EXT                              0x00000002
#define GL_ALL_SHADER_BITS_EXT                                  0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE_EXT                                0x8258
#define GL_ACTIVE_PROGRAM_EXT                                   0x8259
#define GL_PROGRAM_PIPELINE_BINDING_EXT                         0x825A
#endif

#if GL_EXT_shader_framebuffer_fetch
#define GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT                 0x8A52
#endif

#if GL_EXT_shadow_samplers
#define GL_TEXTURE_COMPARE_MODE_EXT                             0x884C
#define GL_TEXTURE_COMPARE_FUNC_EXT                             0x884D
#define GL_COMPARE_REF_TO_TEXTURE_EXT                           0x884E
#define GL_SAMPLER_2D_SHADOW_EXT                                0x8B62
#endif

#if GL_EXT_sRGB
#define GL_SRGB_EXT                                             0x8C40
#define GL_SRGB_ALPHA_EXT                                       0x8C42
#define GL_SRGB8_ALPHA8_EXT                                     0x8C43
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT            0x8210
#endif

#if GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF
#endif

#if GL_EXT_texture_rg
#define GL_RED_EXT                                              0x1903
#define GL_RG_EXT                                               0x8227
#define GL_R8_EXT                                               0x8229
#define GL_RG8_EXT                                              0x822B
#endif

#if GL_EXT_texture_storage
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT                         0x912F
#define GL_ALPHA8_EXT                                           0x803C
#define GL_LUMINANCE8_EXT                                       0x8040
#define GL_LUMINANCE8_ALPHA8_EXT                                0x8045
#define GL_BGRA8_EXT                                            0x93A1
#define GL_RGBA32F_EXT                                          0x8814
#define GL_RGB32F_EXT                                           0x8815
#define GL_RG32F_EXT                                            0x8230
#define GL_R32F_EXT                                             0x822E
#define GL_ALPHA32F_EXT                                         0x8816
#define GL_LUMINANCE32F_EXT                                     0x8818
#define GL_LUMINANCE_ALPHA32F_EXT                               0x8819
#define GL_ALPHA16F_EXT                                         0x881C
#define GL_LUMINANCE16F_EXT                                     0x881E
#define GL_LUMINANCE_ALPHA16F_EXT                               0x881F
#define GL_DEPTH_COMPONENT32_OES                                0x81A7
#define GL_RGB_RAW_422_APPLE                                    0x8A51
#endif

/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/
#if GL_IMG_read_format
#define GL_BGRA_IMG                                             0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG                       0x8365
#endif

#if GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03
#endif

/*------------------------------------------------------------------------*
 * OES extension tokens
 *------------------------------------------------------------------------*/
#if GL_OES_depth24
#define GL_DEPTH_COMPONENT24_OES                                0x81A6
#endif

#if GL_OES_mapbuffer
#define GL_WRITE_ONLY_OES                                       0x88B9
#define GL_BUFFER_ACCESS_OES                                    0x88BB
#define GL_BUFFER_MAPPED_OES                                    0x88BC
#define GL_BUFFER_MAP_POINTER_OES                               0x88BD
#endif

#if GL_OES_packed_depth_stencil
#define GL_DEPTH_STENCIL_OES                                    0x84F9
#define GL_UNSIGNED_INT_24_8_OES                                0x84FA
#define GL_DEPTH24_STENCIL8_OES                                 0x88F0
#endif

#if GL_OES_rgb8_rgba8
#define GL_RGB8_OES                                             0x8051
#define GL_RGBA8_OES                                            0x8058
#endif

#if GL_OES_standard_derivatives
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES                  0x8B8B
#endif

#if GL_OES_texture_half_float
#define GL_HALF_FLOAT_OES                                       0x8D61
#endif

#if GL_OES_vertex_array_object
#define GL_VERTEX_ARRAY_BINDING_OES                             0x85B5
#endif

/**************************************************************************/

/*------------------------------------------------------------------------*
 * APPLE extension functions
 *------------------------------------------------------------------------*/
#if GL_APPLE_copy_texture_levels
GL_API GLvoid glCopyTextureLevelsAPPLE(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_APPLE_framebuffer_multisample
GL_API GLvoid glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glResolveMultisampleFramebufferAPPLE(void)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_APPLE_sync
GL_API GLsync glFenceSyncAPPLE(GLenum condition, GLbitfield flags)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean glIsSyncAPPLE(GLsync sync)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API void glDeleteSyncAPPLE(GLsync sync)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum glClientWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API void glWaitSyncAPPLE(GLsync sync, GLbitfield flags, GLuint64 timeout)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API void glGetInteger64vAPPLE(GLenum pname, GLint64 *params)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API void glGetSyncivAPPLE(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

/*------------------------------------------------------------------------*
 * EXT extension functions
 *------------------------------------------------------------------------*/
#if GL_EXT_debug_label
GL_API GLvoid glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar *label)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_debug_marker
GL_API GLvoid glInsertEventMarkerEXT(GLsizei length, const GLchar *marker)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glPushGroupMarkerEXT(GLsizei length, const GLchar *marker)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glPopGroupMarkerEXT(void)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_discard_framebuffer
GL_API GLvoid GL_APIENTRY glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_draw_instanced
GL_API GLvoid glDrawArraysInstancedEXT(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices, GLsizei instanceCount)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_instanced_arrays
GL_API GLvoid glVertexAttribDivisorEXT(GLuint index, GLuint divisor)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_map_buffer_range
GL_API GLvoid *glMapBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glFlushMappedBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_occlusion_query_boolean
GL_API GLvoid glGenQueriesEXT(GLsizei n, GLuint *ids)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glDeleteQueriesEXT(GLsizei n, const GLuint *ids)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean glIsQueryEXT(GLuint id)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glBeginQueryEXT(GLenum target, GLuint id)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glEndQueryEXT(GLenum target)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetQueryivEXT(GLenum target, GLenum pname, GLint *params)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetQueryObjectuivEXT(GLuint id, GLenum pname, GLuint *params)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0)); 
#endif

#if GL_EXT_separate_shader_objects
GL_API GLvoid glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glActiveShaderProgramEXT(GLuint pipeline, GLuint program)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLuint glCreateShaderProgramvEXT(GLenum type, GLsizei count, const GLchar* const *strings)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glBindProgramPipelineEXT(GLuint pipeline)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glDeleteProgramPipelinesEXT(GLsizei n, const GLuint *pipelines)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGenProgramPipelinesEXT(GLsizei n, GLuint *pipelines)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean glIsProgramPipelineEXT(GLuint pipeline)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramParameteriEXT(GLuint program, GLenum pname, GLint value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint *params)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glValidateProgramPipelineEXT(GLuint pipeline)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1iEXT(GLuint program, GLint location, GLint x)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2iEXT(GLuint program, GLint location, GLint x, GLint y)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1fEXT(GLuint program, GLint location, GLfloat x)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2fEXT(GLuint program, GLint location, GLfloat x, GLfloat y)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_texture_storage
GL_API GLvoid glTexStorage2DEXT(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

/*------------------------------------------------------------------------*
 * OES extension functions
 *------------------------------------------------------------------------*/
#if GL_OES_mapbuffer
GL_API GLvoid GL_APIENTRY glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid * GL_APIENTRY glMapBufferOES (GLenum target, GLenum access) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean GL_APIENTRY glUnmapBufferOES (GLenum target) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_OES_vertex_array_object
GL_API GLvoid glBindVertexArrayOES(GLuint array)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGenVertexArraysOES(GLsizei n, GLuint *arrays)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean glIsVertexArrayOES(GLuint array)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
#endif

#ifdef __cplusplus
}
#endif

#endif /* __gl_es20ext_h_ */
// ==========  OpenGLES.framework/Headers/ES2/gl.h
#ifndef __gl_es20_h_
#define __gl_es20_h_

#include <Availability.h>
#include <OpenGLES/OpenGLESAvailability.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
**
** http://oss.sgi.com/projects/FreeB
**
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
**
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
**
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/


#define GL_APIENTRY
#define GL_API extern


/*-------------------------------------------------------------------------
 * Data type definitions
 *-----------------------------------------------------------------------*/

#include <OpenGLES/gltypes.h>

/*-------------------------------------------------------------------------
 * Token definitions
 *-----------------------------------------------------------------------*/

/* OpenGL ES core versions */
#define GL_ES_VERSION_2_0                                1

/* ClearBufferMask */
#define GL_DEPTH_BUFFER_BIT                              0x00000100
#define GL_STENCIL_BUFFER_BIT                            0x00000400
#define GL_COLOR_BUFFER_BIT                              0x00004000

/* Boolean */
#define GL_FALSE                                         0
#define GL_TRUE                                          1

/* BeginMode */
#define GL_POINTS                                        0x0000
#define GL_LINES                                         0x0001
#define GL_LINE_LOOP                                     0x0002
#define GL_LINE_STRIP                                    0x0003
#define GL_TRIANGLES                                     0x0004
#define GL_TRIANGLE_STRIP                                0x0005
#define GL_TRIANGLE_FAN                                  0x0006

/* BlendingFactorDest */
#define GL_ZERO                                          0
#define GL_ONE                                           1
#define GL_SRC_COLOR                                     0x0300
#define GL_ONE_MINUS_SRC_COLOR                           0x0301
#define GL_SRC_ALPHA                                     0x0302
#define GL_ONE_MINUS_SRC_ALPHA                           0x0303
#define GL_DST_ALPHA                                     0x0304
#define GL_ONE_MINUS_DST_ALPHA                           0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                                     0x0306
#define GL_ONE_MINUS_DST_COLOR                           0x0307
#define GL_SRC_ALPHA_SATURATE                            0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* BlendEquationSeparate */
#define GL_FUNC_ADD                                      0x8006
#define GL_BLEND_EQUATION                                0x8009
#define GL_BLEND_EQUATION_RGB                            0x8009    /* same as BLEND_EQUATION */
#define GL_BLEND_EQUATION_ALPHA                          0x883D

/* BlendSubtract */
#define GL_FUNC_SUBTRACT                                 0x800A
#define GL_FUNC_REVERSE_SUBTRACT                         0x800B

/* Separate Blend Functions */
#define GL_BLEND_DST_RGB                                 0x80C8
#define GL_BLEND_SRC_RGB                                 0x80C9
#define GL_BLEND_DST_ALPHA                               0x80CA
#define GL_BLEND_SRC_ALPHA                               0x80CB
#define GL_CONSTANT_COLOR                                0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR                      0x8002
#define GL_CONSTANT_ALPHA                                0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA                      0x8004
#define GL_BLEND_COLOR                                   0x8005

/* Buffer Objects */
#define GL_ARRAY_BUFFER                                  0x8892
#define GL_ELEMENT_ARRAY_BUFFER                          0x8893
#define GL_ARRAY_BUFFER_BINDING                          0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING                  0x8895

#define GL_STREAM_DRAW                                   0x88E0
#define GL_STATIC_DRAW                                   0x88E4
#define GL_DYNAMIC_DRAW                                  0x88E8

#define GL_BUFFER_SIZE                                   0x8764
#define GL_BUFFER_USAGE                                  0x8765

#define GL_CURRENT_VERTEX_ATTRIB                         0x8626

/* CullFaceMode */
#define GL_FRONT                                         0x0404
#define GL_BACK                                          0x0405
#define GL_FRONT_AND_BACK                                0x0408

/* DepthFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* EnableCap */
#define GL_TEXTURE_2D                                    0x0DE1
#define GL_CULL_FACE                                     0x0B44
#define GL_BLEND                                         0x0BE2
#define GL_DITHER                                        0x0BD0
#define GL_STENCIL_TEST                                  0x0B90
#define GL_DEPTH_TEST                                    0x0B71
#define GL_SCISSOR_TEST                                  0x0C11
#define GL_POLYGON_OFFSET_FILL                           0x8037
#define GL_SAMPLE_ALPHA_TO_COVERAGE                      0x809E
#define GL_SAMPLE_COVERAGE                               0x80A0

/* ErrorCode */
#define GL_NO_ERROR                                      0
#define GL_INVALID_ENUM                                  0x0500
#define GL_INVALID_VALUE                                 0x0501
#define GL_INVALID_OPERATION                             0x0502
#define GL_OUT_OF_MEMORY                                 0x0505

/* FrontFaceDirection */
#define GL_CW                                            0x0900
#define GL_CCW                                           0x0901

/* GetPName */
#define GL_LINE_WIDTH                                    0x0B21
#define GL_ALIASED_POINT_SIZE_RANGE                      0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE                      0x846E
#define GL_CULL_FACE_MODE                                0x0B45
#define GL_FRONT_FACE                                    0x0B46
#define GL_DEPTH_RANGE                                   0x0B70
#define GL_DEPTH_WRITEMASK                               0x0B72
#define GL_DEPTH_CLEAR_VALUE                             0x0B73
#define GL_DEPTH_FUNC                                    0x0B74
#define GL_STENCIL_CLEAR_VALUE                           0x0B91
#define GL_STENCIL_FUNC                                  0x0B92
#define GL_STENCIL_FAIL                                  0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL                       0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS                       0x0B96
#define GL_STENCIL_REF                                   0x0B97
#define GL_STENCIL_VALUE_MASK                            0x0B93
#define GL_STENCIL_WRITEMASK                             0x0B98
#define GL_STENCIL_BACK_FUNC                             0x8800
#define GL_STENCIL_BACK_FAIL                             0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL                  0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS                  0x8803
#define GL_STENCIL_BACK_REF                              0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK                       0x8CA4
#define GL_STENCIL_BACK_WRITEMASK                        0x8CA5
#define GL_VIEWPORT                                      0x0BA2
#define GL_SCISSOR_BOX                                   0x0C10
/*      GL_SCISSOR_TEST */
#define GL_COLOR_CLEAR_VALUE                             0x0C22
#define GL_COLOR_WRITEMASK                               0x0C23
#define GL_UNPACK_ALIGNMENT                              0x0CF5
#define GL_PACK_ALIGNMENT                                0x0D05
#define GL_MAX_TEXTURE_SIZE                              0x0D33
#define GL_MAX_VIEWPORT_DIMS                             0x0D3A
#define GL_SUBPIXEL_BITS                                 0x0D50
#define GL_RED_BITS                                      0x0D52
#define GL_GREEN_BITS                                    0x0D53
#define GL_BLUE_BITS                                     0x0D54
#define GL_ALPHA_BITS                                    0x0D55
#define GL_DEPTH_BITS                                    0x0D56
#define GL_STENCIL_BITS                                  0x0D57
#define GL_POLYGON_OFFSET_UNITS                          0x2A00
/*      GL_POLYGON_OFFSET_FILL */
#define GL_POLYGON_OFFSET_FACTOR                         0x8038
#define GL_TEXTURE_BINDING_2D                            0x8069
#define GL_SAMPLE_BUFFERS                                0x80A8
#define GL_SAMPLES                                       0x80A9
#define GL_SAMPLE_COVERAGE_VALUE                         0x80AA
#define GL_SAMPLE_COVERAGE_INVERT                        0x80AB

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */

#define GL_NUM_COMPRESSED_TEXTURE_FORMATS                0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS                    0x86A3

/* HintMode */
#define GL_DONT_CARE                                     0x1100
#define GL_FASTEST                                       0x1101
#define GL_NICEST                                        0x1102

/* HintTarget */
#define GL_GENERATE_MIPMAP_HINT                          0x8192

/* DataType */
#define GL_BYTE                                          0x1400
#define GL_UNSIGNED_BYTE                                 0x1401
#define GL_SHORT                                         0x1402
#define GL_UNSIGNED_SHORT                                0x1403
#define GL_INT                                           0x1404
#define GL_UNSIGNED_INT                                  0x1405
#define GL_FLOAT                                         0x1406
#define GL_FIXED                                         0x140C

/* PixelFormat */
#define GL_DEPTH_COMPONENT                               0x1902
#define GL_ALPHA                                         0x1906
#define GL_RGB                                           0x1907
#define GL_RGBA                                          0x1908
#define GL_LUMINANCE                                     0x1909
#define GL_LUMINANCE_ALPHA                               0x190A

/* PixelType */
/*      GL_UNSIGNED_BYTE */
#define GL_UNSIGNED_SHORT_4_4_4_4                        0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1                        0x8034
#define GL_UNSIGNED_SHORT_5_6_5                          0x8363

/* Shaders */
#define GL_FRAGMENT_SHADER                               0x8B30
#define GL_VERTEX_SHADER                                 0x8B31
#define GL_MAX_VERTEX_ATTRIBS                            0x8869
#define GL_MAX_VERTEX_UNIFORM_VECTORS                    0x8DFB
#define GL_MAX_VARYING_VECTORS                           0x8DFC
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS              0x8B4D
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS                0x8B4C
#define GL_MAX_TEXTURE_IMAGE_UNITS                       0x8872
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS                  0x8DFD
#define GL_SHADER_TYPE                                   0x8B4F
#define GL_DELETE_STATUS                                 0x8B80
#define GL_LINK_STATUS                                   0x8B82
#define GL_VALIDATE_STATUS                               0x8B83
#define GL_ATTACHED_SHADERS                              0x8B85
#define GL_ACTIVE_UNIFORMS                               0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH                     0x8B87
#define GL_ACTIVE_ATTRIBUTES                             0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH                   0x8B8A
#define GL_SHADING_LANGUAGE_VERSION                      0x8B8C
#define GL_CURRENT_PROGRAM                               0x8B8D

/* StencilFunction */
#define GL_NEVER                                         0x0200
#define GL_LESS                                          0x0201
#define GL_EQUAL                                         0x0202
#define GL_LEQUAL                                        0x0203
#define GL_GREATER                                       0x0204
#define GL_NOTEQUAL                                      0x0205
#define GL_GEQUAL                                        0x0206
#define GL_ALWAYS                                        0x0207

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                                          0x1E00
#define GL_REPLACE                                       0x1E01
#define GL_INCR                                          0x1E02
#define GL_DECR                                          0x1E03
#define GL_INVERT                                        0x150A
#define GL_INCR_WRAP                                     0x8507
#define GL_DECR_WRAP                                     0x8508

/* StringName */
#define GL_VENDOR                                        0x1F00
#define GL_RENDERER                                      0x1F01
#define GL_VERSION                                       0x1F02
#define GL_EXTENSIONS                                    0x1F03

/* TextureMagFilter */
#define GL_NEAREST                                       0x2600
#define GL_LINEAR                                        0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST                        0x2700
#define GL_LINEAR_MIPMAP_NEAREST                         0x2701
#define GL_NEAREST_MIPMAP_LINEAR                         0x2702
#define GL_LINEAR_MIPMAP_LINEAR                          0x2703

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER                            0x2800
#define GL_TEXTURE_MIN_FILTER                            0x2801
#define GL_TEXTURE_WRAP_S                                0x2802
#define GL_TEXTURE_WRAP_T                                0x2803

/* TextureTarget */
/*      GL_TEXTURE_2D */
#define GL_TEXTURE                                       0x1702

#define GL_TEXTURE_CUBE_MAP                              0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP                      0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X                   0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X                   0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y                   0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                   0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z                   0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                   0x851A
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE                     0x851C

/* TextureUnit */
#define GL_TEXTURE0                                      0x84C0
#define GL_TEXTURE1                                      0x84C1
#define GL_TEXTURE2                                      0x84C2
#define GL_TEXTURE3                                      0x84C3
#define GL_TEXTURE4                                      0x84C4
#define GL_TEXTURE5                                      0x84C5
#define GL_TEXTURE6                                      0x84C6
#define GL_TEXTURE7                                      0x84C7
#define GL_TEXTURE8                                      0x84C8
#define GL_TEXTURE9                                      0x84C9
#define GL_TEXTURE10                                     0x84CA
#define GL_TEXTURE11                                     0x84CB
#define GL_TEXTURE12                                     0x84CC
#define GL_TEXTURE13                                     0x84CD
#define GL_TEXTURE14                                     0x84CE
#define GL_TEXTURE15                                     0x84CF
#define GL_TEXTURE16                                     0x84D0
#define GL_TEXTURE17                                     0x84D1
#define GL_TEXTURE18                                     0x84D2
#define GL_TEXTURE19                                     0x84D3
#define GL_TEXTURE20                                     0x84D4
#define GL_TEXTURE21                                     0x84D5
#define GL_TEXTURE22                                     0x84D6
#define GL_TEXTURE23                                     0x84D7
#define GL_TEXTURE24                                     0x84D8
#define GL_TEXTURE25                                     0x84D9
#define GL_TEXTURE26                                     0x84DA
#define GL_TEXTURE27                                     0x84DB
#define GL_TEXTURE28                                     0x84DC
#define GL_TEXTURE29                                     0x84DD
#define GL_TEXTURE30                                     0x84DE
#define GL_TEXTURE31                                     0x84DF
#define GL_ACTIVE_TEXTURE                                0x84E0

/* TextureWrapMode */
#define GL_REPEAT                                        0x2901
#define GL_CLAMP_TO_EDGE                                 0x812F
#define GL_MIRRORED_REPEAT                               0x8370

/* Uniform Types */
#define GL_FLOAT_VEC2                                    0x8B50
#define GL_FLOAT_VEC3                                    0x8B51
#define GL_FLOAT_VEC4                                    0x8B52
#define GL_INT_VEC2                                      0x8B53
#define GL_INT_VEC3                                      0x8B54
#define GL_INT_VEC4                                      0x8B55
#define GL_BOOL                                          0x8B56
#define GL_BOOL_VEC2                                     0x8B57
#define GL_BOOL_VEC3                                     0x8B58
#define GL_BOOL_VEC4                                     0x8B59
#define GL_FLOAT_MAT2                                    0x8B5A
#define GL_FLOAT_MAT3                                    0x8B5B
#define GL_FLOAT_MAT4                                    0x8B5C
#define GL_SAMPLER_2D                                    0x8B5E
#define GL_SAMPLER_CUBE                                  0x8B60

/* Vertex Arrays */
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED                   0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE                      0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE                    0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE                      0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED                0x886A
#define GL_VERTEX_ATTRIB_ARRAY_POINTER                   0x8645
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING            0x889F

/* Read Format */
#define GL_IMPLEMENTATION_COLOR_READ_TYPE                0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT              0x8B9B

/* Shader Source */
#define GL_COMPILE_STATUS                                0x8B81
#define GL_INFO_LOG_LENGTH                               0x8B84
#define GL_SHADER_SOURCE_LENGTH                          0x8B88
#define GL_SHADER_COMPILER                               0x8DFA

/* Shader Binary */
#define GL_SHADER_BINARY_FORMATS                         0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS                     0x8DF9

/* Shader Precision-Specified Types */
#define GL_LOW_FLOAT                                     0x8DF0
#define GL_MEDIUM_FLOAT                                  0x8DF1
#define GL_HIGH_FLOAT                                    0x8DF2
#define GL_LOW_INT                                       0x8DF3
#define GL_MEDIUM_INT                                    0x8DF4
#define GL_HIGH_INT                                      0x8DF5

/* Framebuffer Object. */
#define GL_FRAMEBUFFER                                   0x8D40
#define GL_RENDERBUFFER                                  0x8D41

#define GL_RGBA4                                         0x8056
#define GL_RGB5_A1                                       0x8057
#define GL_RGB565                                        0x8D62
#define GL_DEPTH_COMPONENT16                             0x81A5
#define GL_STENCIL_INDEX8                                0x8D48

#define GL_RENDERBUFFER_WIDTH                            0x8D42
#define GL_RENDERBUFFER_HEIGHT                           0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT                  0x8D44
#define GL_RENDERBUFFER_RED_SIZE                         0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE                       0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE                        0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE                       0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE                       0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE                     0x8D55

#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE            0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME            0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL          0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE  0x8CD3

#define GL_COLOR_ATTACHMENT0                             0x8CE0
#define GL_DEPTH_ATTACHMENT                              0x8D00
#define GL_STENCIL_ATTACHMENT                            0x8D20

#define GL_NONE                                          0

#define GL_FRAMEBUFFER_COMPLETE                          0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT             0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT     0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS             0x8CD9
#define GL_FRAMEBUFFER_UNSUPPORTED                       0x8CDD

#define GL_FRAMEBUFFER_BINDING                           0x8CA6
#define GL_RENDERBUFFER_BINDING                          0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE                         0x84E8

#define GL_INVALID_FRAMEBUFFER_OPERATION                 0x0506

/*-------------------------------------------------------------------------
 * Entrypoint definitions
 *-----------------------------------------------------------------------*/

GL_API void           GL_APIENTRY glActiveTexture (GLenum texture) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glAttachShader (GLuint program, GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindTexture (GLenum target, GLuint texture) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendEquation (GLenum mode)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum         GL_APIENTRY glCheckFramebufferStatus (GLenum target)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClear (GLbitfield mask) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearDepthf (GLclampf depth) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearStencil (GLint s) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompileShader (GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLuint         GL_APIENTRY glCreateProgram (void)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLuint         GL_APIENTRY glCreateShader (GLenum type)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCullFace (GLenum mode) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint* buffers) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteShader (GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint* textures) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDepthFunc (GLenum func) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDepthMask (GLboolean flag) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDepthRangef (GLclampf zNear, GLclampf zFar) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDetachShader (GLuint program, GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDisable (GLenum cap) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDisableVertexAttribArray (GLuint index)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glEnable (GLenum cap) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glEnableVertexAttribArray (GLuint index)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFinish (void) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFlush (void) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFrontFace (GLenum mode) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenBuffers (GLsizei n, GLuint* buffers) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenerateMipmap (GLenum target)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint* framebuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint* renderbuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenTextures (GLsizei n, GLuint* textures) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API int            GL_APIENTRY glGetAttribLocation (GLuint program, const GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum         GL_APIENTRY glGetError (void) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetFloatv (GLenum pname, GLfloat* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetIntegerv (GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API const GLubyte* GL_APIENTRY glGetString (GLenum name) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API int            GL_APIENTRY glGetUniformLocation (GLuint program, const GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glHint (GLenum target, GLenum mode) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsBuffer (GLuint buffer) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsEnabled (GLenum cap) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsFramebuffer (GLuint framebuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsProgram (GLuint program) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsShader (GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsTexture (GLuint texture) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glLineWidth (GLfloat width) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glLinkProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glPixelStorei (GLenum pname, GLint param) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glReleaseShaderCompiler (void)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glSampleCoverage (GLclampf value, GLboolean invert) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilMask (GLuint mask) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1f (GLint location, GLfloat x)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1i (GLint location, GLint x)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2f (GLint location, GLfloat x, GLfloat y)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2i (GLint location, GLint x, GLint y)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3i (GLint location, GLint x, GLint y, GLint z)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUseProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glValidateProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib1f (GLuint indx, GLfloat x)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib1fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib2fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib3fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib4fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));

#ifdef __cplusplus
}
#endif

#endif /* __gl_es20_h_ */
// ==========  OpenGLES.framework/Headers/ES3/glext.h
#ifndef __gl_es30ext_h_
#define __gl_es30ext_h_

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/OpenGLESAvailability.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
**
** http://oss.sgi.com/projects/FreeB
**
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
**
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
**
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif

#define GL_APPLE_clip_distance                                  1
#define GL_APPLE_color_buffer_packed_float                      1
#define GL_APPLE_copy_texture_levels                            1
#define GL_APPLE_rgb_422                                        1
#define GL_APPLE_texture_format_BGRA8888                        1
#define GL_EXT_color_buffer_half_float                          1
#define GL_EXT_debug_label                                      1
#define GL_EXT_debug_marker                                     1
#define GL_EXT_pvrtc_sRGB                                       1
#define GL_EXT_read_format_bgra                                 1
#define GL_EXT_separate_shader_objects                          1
#define GL_EXT_shader_framebuffer_fetch                         1
#define GL_EXT_shader_texture_lod                               1
#define GL_EXT_shadow_samplers                                  1
#define GL_EXT_shader_framebuffer_fetch                         1
#define GL_EXT_texture_filter_anisotropic                       1
#define GL_IMG_read_format                                      1
#define GL_IMG_texture_compression_pvrtc                        1
#define GL_KHR_texture_compression_astc_ldr                     1
#define GL_OES_standard_derivatives                             1

/*------------------------------------------------------------------------*
 * APPLE extension tokens
 *------------------------------------------------------------------------*/
#if GL_APPLE_color_buffer_packed_float
#define GL_R11F_G11F_B10F_APPLE                                 0x8C3A
#define GL_RGB9_E5_APPLE                                        0x8C3D
#endif

#if GL_APPLE_clip_distance
#define GL_CLIP_DISTANCE0_APPLE           0x3000
#define GL_CLIP_DISTANCE1_APPLE           0x3001
#define GL_CLIP_DISTANCE2_APPLE           0x3002
#define GL_CLIP_DISTANCE3_APPLE           0x3003
#define GL_CLIP_DISTANCE4_APPLE           0x3004
#define GL_CLIP_DISTANCE5_APPLE           0x3005
#define GL_CLIP_DISTANCE6_APPLE           0x3006
#define GL_CLIP_DISTANCE7_APPLE           0x3007
#define GL_MAX_CLIP_DISTANCES_APPLE       0x0D32
#endif

#if GL_APPLE_rgb_422
#define GL_RGB_422_APPLE                                        0x8A1F
#define GL_UNSIGNED_SHORT_8_8_APPLE                             0x85BA
#define GL_UNSIGNED_SHORT_8_8_REV_APPLE                         0x85BB
#define GL_RGB_RAW_422_APPLE                                    0x8A51
#endif

#if GL_APPLE_texture_format_BGRA8888
#define GL_BGRA_EXT                                             0x80E1
#define GL_BGRA8_EXT                                            0x93A1
#endif

#if GL_APPLE_texture_format_BGRA8888 || GL_IMG_read_format
#define GL_BGRA                                                 0x80E1
#endif

/*------------------------------------------------------------------------*
 * EXT extension tokens
 *------------------------------------------------------------------------*/
#if GL_EXT_color_buffer_half_float
#define GL_RGBA16F_EXT                                          0x881A
#define GL_RGB16F_EXT                                           0x881B
#define GL_RG16F_EXT                                            0x822F
#define GL_R16F_EXT                                             0x822D
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT            0x8211
#define GL_UNSIGNED_NORMALIZED_EXT                              0x8C17
#endif

#if GL_EXT_debug_label
#define GL_BUFFER_OBJECT_EXT                                    0x9151
#define GL_SHADER_OBJECT_EXT                                    0x8B48
#define GL_PROGRAM_OBJECT_EXT                                   0x8B40
#define GL_QUERY_OBJECT_EXT                                     0x9153
#define GL_VERTEX_ARRAY_OBJECT_EXT                              0x9154
#define GL_PROGRAM_PIPELINE_OBJECT_EXT                          0x8A4F
#define GL_SYNC_OBJECT_APPLE                                    0x8A53
#define GL_SAMPLER                                              0x82E6
#endif

#if GL_EXT_pvrtc_sRGB
#define GL_COMPRESSED_SRGB_PVRTC_2BPPV1_EXT                   0x8A54
#define GL_COMPRESSED_SRGB_PVRTC_4BPPV1_EXT                   0x8A55
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_2BPPV1_EXT             0x8A56
#define GL_COMPRESSED_SRGB_ALPHA_PVRTC_4BPPV1_EXT             0x8A57
#endif

#if GL_EXT_read_format_bgra
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT                       0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT                       0x8366
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                           0x8366
#endif

#if GL_EXT_read_format_bgra || GL_IMG_read_format
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
#endif

#if GL_EXT_separate_shader_objects
#define GL_VERTEX_SHADER_BIT_EXT                                0x00000001
#define GL_FRAGMENT_SHADER_BIT_EXT                              0x00000002
#define GL_ALL_SHADER_BITS_EXT                                  0xFFFFFFFF
#define GL_PROGRAM_SEPARABLE_EXT                                0x8258
#define GL_ACTIVE_PROGRAM_EXT                                   0x8259
#define GL_PROGRAM_PIPELINE_BINDING_EXT                         0x825A
#endif

#if GL_EXT_shader_framebuffer_fetch
#define GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT                 0x8A52
#endif

#if GL_EXT_shadow_samplers
#define GL_TEXTURE_COMPARE_MODE_EXT                             0x884C
#define GL_TEXTURE_COMPARE_FUNC_EXT                             0x884D
#define GL_COMPARE_REF_TO_TEXTURE_EXT                           0x884E
#define GL_SAMPLER_2D_SHADOW_EXT                                0x8B62
#endif

#if GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF
#endif


/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/
#if GL_IMG_read_format
#define GL_BGRA_IMG                                             0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG                       0x8365
#endif

#if GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03
#endif

/*------------------------------------------------------------------------*
 * KHR extension tokens
 *------------------------------------------------------------------------*/
#if GL_KHR_texture_compression_astc_ldr
#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR                         0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR                         0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR                         0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR                         0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR                         0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR                         0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR                         0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR                         0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR                        0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR                        0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR                        0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR                       0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR                       0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR                       0x93BD
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR                 0x93D0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR                 0x93D1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR                 0x93D2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR                 0x93D3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR                 0x93D4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR                 0x93D5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR                 0x93D6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR                 0x93D7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR                0x93D8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR                0x93D9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR                0x93DA
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR               0x93DB
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR               0x93DC
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR               0x93DD
#endif

/*------------------------------------------------------------------------*
 * OES extension tokens
 *------------------------------------------------------------------------*/
#if GL_OES_standard_derivatives
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES                  0x8B8B
#endif

/**************************************************************************/

/*------------------------------------------------------------------------*
 * APPLE extension functions
 *------------------------------------------------------------------------*/
#if GL_APPLE_copy_texture_levels
GL_API GLvoid glCopyTextureLevelsAPPLE(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount)  OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

/*------------------------------------------------------------------------*
 * EXT extension functions
 *------------------------------------------------------------------------*/
#if GL_EXT_debug_label
GL_API GLvoid glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar *label)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_debug_marker
GL_API GLvoid glInsertEventMarkerEXT(GLsizei length, const GLchar *marker)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glPushGroupMarkerEXT(GLsizei length, const GLchar *marker)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glPopGroupMarkerEXT(void)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_separate_shader_objects
GL_API GLvoid glUseProgramStagesEXT(GLuint pipeline, GLbitfield stages, GLuint program)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glActiveShaderProgramEXT(GLuint pipeline, GLuint program)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLuint glCreateShaderProgramvEXT(GLenum type, GLsizei count, const GLchar* const *strings)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glBindProgramPipelineEXT(GLuint pipeline)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glDeleteProgramPipelinesEXT(GLsizei n, const GLuint *pipelines)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGenProgramPipelinesEXT(GLsizei n, GLuint *pipelines)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean glIsProgramPipelineEXT(GLuint pipeline)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramParameteriEXT(GLuint program, GLenum pname, GLint value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetProgramPipelineivEXT(GLuint pipeline, GLenum pname, GLint *params)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glValidateProgramPipelineEXT(GLuint pipeline)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetProgramPipelineInfoLogEXT(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1iEXT(GLuint program, GLint location, GLint x)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2iEXT(GLuint program, GLint location, GLint x, GLint y)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4iEXT(GLuint program, GLint location, GLint x, GLint y, GLint z, GLint w)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1fEXT(GLuint program, GLint location, GLfloat x)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2fEXT(GLuint program, GLint location, GLfloat x, GLfloat y)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4fEXT(GLuint program, GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1uiEXT(GLuint program, GLint location, GLuint x)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2uiEXT(GLuint program, GLint location, GLuint x, GLuint y)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3uiEXT(GLuint program, GLint location, GLuint x, GLuint y, GLuint z)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4uiEXT(GLuint program, GLint location, GLuint x, GLuint y, GLuint z, GLuint w)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniform1uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform2uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform3uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniform4uivEXT(GLuint program, GLint location, GLsizei count, const GLuint *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));

GL_API GLvoid glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix2x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix3x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix2x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix4x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix3x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glProgramUniformMatrix4x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
#endif

#ifdef __cplusplus
}
#endif

#endif /* __gl_es30ext_h_ */
// ==========  OpenGLES.framework/Headers/ES3/gl.h
#ifndef __gl_es30_h_
#define __gl_es30_h_

#include <Availability.h>
#include <OpenGLES/OpenGLESAvailability.h>
#ifdef __cplusplus
extern "C" {
#endif

/*
** Copyright (c) 2007-2012 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/


#define GL_APIENTRY
#define GL_API extern


/*-------------------------------------------------------------------------
 * Data type definitions
 *-----------------------------------------------------------------------*/

/* OpenGL ES 2.0 */

#include <OpenGLES/gltypes.h>

/*-------------------------------------------------------------------------
 * Token definitions
 *-----------------------------------------------------------------------*/

/* OpenGL ES core versions */
#define GL_ES_VERSION_3_0                                1
#define GL_ES_VERSION_2_0                                1

/* OpenGL ES 2.0 */

/* ClearBufferMask */
#define GL_DEPTH_BUFFER_BIT                              0x00000100
#define GL_STENCIL_BUFFER_BIT                            0x00000400
#define GL_COLOR_BUFFER_BIT                              0x00004000

/* Boolean */
#define GL_FALSE                                         0
#define GL_TRUE                                          1

/* BeginMode */
#define GL_POINTS                                        0x0000
#define GL_LINES                                         0x0001
#define GL_LINE_LOOP                                     0x0002
#define GL_LINE_STRIP                                    0x0003
#define GL_TRIANGLES                                     0x0004
#define GL_TRIANGLE_STRIP                                0x0005
#define GL_TRIANGLE_FAN                                  0x0006

/* BlendingFactorDest */
#define GL_ZERO                                          0
#define GL_ONE                                           1
#define GL_SRC_COLOR                                     0x0300
#define GL_ONE_MINUS_SRC_COLOR                           0x0301
#define GL_SRC_ALPHA                                     0x0302
#define GL_ONE_MINUS_SRC_ALPHA                           0x0303
#define GL_DST_ALPHA                                     0x0304
#define GL_ONE_MINUS_DST_ALPHA                           0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                                     0x0306
#define GL_ONE_MINUS_DST_COLOR                           0x0307
#define GL_SRC_ALPHA_SATURATE                            0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* BlendEquationSeparate */
#define GL_FUNC_ADD                                      0x8006
#define GL_BLEND_EQUATION                                0x8009
#define GL_BLEND_EQUATION_RGB                            0x8009    /* same as BLEND_EQUATION */
#define GL_BLEND_EQUATION_ALPHA                          0x883D

/* BlendSubtract */
#define GL_FUNC_SUBTRACT                                 0x800A
#define GL_FUNC_REVERSE_SUBTRACT                         0x800B

/* Separate Blend Functions */
#define GL_BLEND_DST_RGB                                 0x80C8
#define GL_BLEND_SRC_RGB                                 0x80C9
#define GL_BLEND_DST_ALPHA                               0x80CA
#define GL_BLEND_SRC_ALPHA                               0x80CB
#define GL_CONSTANT_COLOR                                0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR                      0x8002
#define GL_CONSTANT_ALPHA                                0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA                      0x8004
#define GL_BLEND_COLOR                                   0x8005

/* Buffer Objects */
#define GL_ARRAY_BUFFER                                  0x8892
#define GL_ELEMENT_ARRAY_BUFFER                          0x8893
#define GL_ARRAY_BUFFER_BINDING                          0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING                  0x8895

#define GL_STREAM_DRAW                                   0x88E0
#define GL_STATIC_DRAW                                   0x88E4
#define GL_DYNAMIC_DRAW                                  0x88E8

#define GL_BUFFER_SIZE                                   0x8764
#define GL_BUFFER_USAGE                                  0x8765

#define GL_CURRENT_VERTEX_ATTRIB                         0x8626

/* CullFaceMode */
#define GL_FRONT                                         0x0404
#define GL_BACK                                          0x0405
#define GL_FRONT_AND_BACK                                0x0408

/* DepthFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* EnableCap */
#define GL_TEXTURE_2D                                    0x0DE1
#define GL_CULL_FACE                                     0x0B44
#define GL_BLEND                                         0x0BE2
#define GL_DITHER                                        0x0BD0
#define GL_STENCIL_TEST                                  0x0B90
#define GL_DEPTH_TEST                                    0x0B71
#define GL_SCISSOR_TEST                                  0x0C11
#define GL_POLYGON_OFFSET_FILL                           0x8037
#define GL_SAMPLE_ALPHA_TO_COVERAGE                      0x809E
#define GL_SAMPLE_COVERAGE                               0x80A0

/* ErrorCode */
#define GL_NO_ERROR                                      0
#define GL_INVALID_ENUM                                  0x0500
#define GL_INVALID_VALUE                                 0x0501
#define GL_INVALID_OPERATION                             0x0502
#define GL_OUT_OF_MEMORY                                 0x0505

/* FrontFaceDirection */
#define GL_CW                                            0x0900
#define GL_CCW                                           0x0901

/* GetPName */
#define GL_LINE_WIDTH                                    0x0B21
#define GL_ALIASED_POINT_SIZE_RANGE                      0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE                      0x846E
#define GL_CULL_FACE_MODE                                0x0B45
#define GL_FRONT_FACE                                    0x0B46
#define GL_DEPTH_RANGE                                   0x0B70
#define GL_DEPTH_WRITEMASK                               0x0B72
#define GL_DEPTH_CLEAR_VALUE                             0x0B73
#define GL_DEPTH_FUNC                                    0x0B74
#define GL_STENCIL_CLEAR_VALUE                           0x0B91
#define GL_STENCIL_FUNC                                  0x0B92
#define GL_STENCIL_FAIL                                  0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL                       0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS                       0x0B96
#define GL_STENCIL_REF                                   0x0B97
#define GL_STENCIL_VALUE_MASK                            0x0B93
#define GL_STENCIL_WRITEMASK                             0x0B98
#define GL_STENCIL_BACK_FUNC                             0x8800
#define GL_STENCIL_BACK_FAIL                             0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL                  0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS                  0x8803
#define GL_STENCIL_BACK_REF                              0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK                       0x8CA4
#define GL_STENCIL_BACK_WRITEMASK                        0x8CA5
#define GL_VIEWPORT                                      0x0BA2
#define GL_SCISSOR_BOX                                   0x0C10
/*      GL_SCISSOR_TEST */
#define GL_COLOR_CLEAR_VALUE                             0x0C22
#define GL_COLOR_WRITEMASK                               0x0C23
#define GL_UNPACK_ALIGNMENT                              0x0CF5
#define GL_PACK_ALIGNMENT                                0x0D05
#define GL_MAX_TEXTURE_SIZE                              0x0D33
#define GL_MAX_VIEWPORT_DIMS                             0x0D3A
#define GL_SUBPIXEL_BITS                                 0x0D50
#define GL_RED_BITS                                      0x0D52
#define GL_GREEN_BITS                                    0x0D53
#define GL_BLUE_BITS                                     0x0D54
#define GL_ALPHA_BITS                                    0x0D55
#define GL_DEPTH_BITS                                    0x0D56
#define GL_STENCIL_BITS                                  0x0D57
#define GL_POLYGON_OFFSET_UNITS                          0x2A00
/*      GL_POLYGON_OFFSET_FILL */
#define GL_POLYGON_OFFSET_FACTOR                         0x8038
#define GL_TEXTURE_BINDING_2D                            0x8069
#define GL_SAMPLE_BUFFERS                                0x80A8
#define GL_SAMPLES                                       0x80A9
#define GL_SAMPLE_COVERAGE_VALUE                         0x80AA
#define GL_SAMPLE_COVERAGE_INVERT                        0x80AB

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */

#define GL_NUM_COMPRESSED_TEXTURE_FORMATS                0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS                    0x86A3

/* HintMode */
#define GL_DONT_CARE                                     0x1100
#define GL_FASTEST                                       0x1101
#define GL_NICEST                                        0x1102

/* HintTarget */
#define GL_GENERATE_MIPMAP_HINT                          0x8192

/* DataType */
#define GL_BYTE                                          0x1400
#define GL_UNSIGNED_BYTE                                 0x1401
#define GL_SHORT                                         0x1402
#define GL_UNSIGNED_SHORT                                0x1403
#define GL_INT                                           0x1404
#define GL_UNSIGNED_INT                                  0x1405
#define GL_FLOAT                                         0x1406
#define GL_FIXED                                         0x140C

/* PixelFormat */
#define GL_DEPTH_COMPONENT                               0x1902
#define GL_ALPHA                                         0x1906
#define GL_RGB                                           0x1907
#define GL_RGBA                                          0x1908
#define GL_LUMINANCE                                     0x1909
#define GL_LUMINANCE_ALPHA                               0x190A

/* PixelType */
/*      GL_UNSIGNED_BYTE */
#define GL_UNSIGNED_SHORT_4_4_4_4                        0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1                        0x8034
#define GL_UNSIGNED_SHORT_5_6_5                          0x8363

/* Shaders */
#define GL_FRAGMENT_SHADER                               0x8B30
#define GL_VERTEX_SHADER                                 0x8B31
#define GL_MAX_VERTEX_ATTRIBS                            0x8869
#define GL_MAX_VERTEX_UNIFORM_VECTORS                    0x8DFB
#define GL_MAX_VARYING_VECTORS                           0x8DFC
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS              0x8B4D
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS                0x8B4C
#define GL_MAX_TEXTURE_IMAGE_UNITS                       0x8872
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS                  0x8DFD
#define GL_SHADER_TYPE                                   0x8B4F
#define GL_DELETE_STATUS                                 0x8B80
#define GL_LINK_STATUS                                   0x8B82
#define GL_VALIDATE_STATUS                               0x8B83
#define GL_ATTACHED_SHADERS                              0x8B85
#define GL_ACTIVE_UNIFORMS                               0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH                     0x8B87
#define GL_ACTIVE_ATTRIBUTES                             0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH                   0x8B8A
#define GL_SHADING_LANGUAGE_VERSION                      0x8B8C
#define GL_CURRENT_PROGRAM                               0x8B8D

/* StencilFunction */
#define GL_NEVER                                         0x0200
#define GL_LESS                                          0x0201
#define GL_EQUAL                                         0x0202
#define GL_LEQUAL                                        0x0203
#define GL_GREATER                                       0x0204
#define GL_NOTEQUAL                                      0x0205
#define GL_GEQUAL                                        0x0206
#define GL_ALWAYS                                        0x0207

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                                          0x1E00
#define GL_REPLACE                                       0x1E01
#define GL_INCR                                          0x1E02
#define GL_DECR                                          0x1E03
#define GL_INVERT                                        0x150A
#define GL_INCR_WRAP                                     0x8507
#define GL_DECR_WRAP                                     0x8508

/* StringName */
#define GL_VENDOR                                        0x1F00
#define GL_RENDERER                                      0x1F01
#define GL_VERSION                                       0x1F02
#define GL_EXTENSIONS                                    0x1F03

/* TextureMagFilter */
#define GL_NEAREST                                       0x2600
#define GL_LINEAR                                        0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST                        0x2700
#define GL_LINEAR_MIPMAP_NEAREST                         0x2701
#define GL_NEAREST_MIPMAP_LINEAR                         0x2702
#define GL_LINEAR_MIPMAP_LINEAR                          0x2703

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER                            0x2800
#define GL_TEXTURE_MIN_FILTER                            0x2801
#define GL_TEXTURE_WRAP_S                                0x2802
#define GL_TEXTURE_WRAP_T                                0x2803

/* TextureTarget */
/*      GL_TEXTURE_2D */
#define GL_TEXTURE                                       0x1702

#define GL_TEXTURE_CUBE_MAP                              0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP                      0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X                   0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X                   0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y                   0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                   0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z                   0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                   0x851A
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE                     0x851C

/* TextureUnit */
#define GL_TEXTURE0                                      0x84C0
#define GL_TEXTURE1                                      0x84C1
#define GL_TEXTURE2                                      0x84C2
#define GL_TEXTURE3                                      0x84C3
#define GL_TEXTURE4                                      0x84C4
#define GL_TEXTURE5                                      0x84C5
#define GL_TEXTURE6                                      0x84C6
#define GL_TEXTURE7                                      0x84C7
#define GL_TEXTURE8                                      0x84C8
#define GL_TEXTURE9                                      0x84C9
#define GL_TEXTURE10                                     0x84CA
#define GL_TEXTURE11                                     0x84CB
#define GL_TEXTURE12                                     0x84CC
#define GL_TEXTURE13                                     0x84CD
#define GL_TEXTURE14                                     0x84CE
#define GL_TEXTURE15                                     0x84CF
#define GL_TEXTURE16                                     0x84D0
#define GL_TEXTURE17                                     0x84D1
#define GL_TEXTURE18                                     0x84D2
#define GL_TEXTURE19                                     0x84D3
#define GL_TEXTURE20                                     0x84D4
#define GL_TEXTURE21                                     0x84D5
#define GL_TEXTURE22                                     0x84D6
#define GL_TEXTURE23                                     0x84D7
#define GL_TEXTURE24                                     0x84D8
#define GL_TEXTURE25                                     0x84D9
#define GL_TEXTURE26                                     0x84DA
#define GL_TEXTURE27                                     0x84DB
#define GL_TEXTURE28                                     0x84DC
#define GL_TEXTURE29                                     0x84DD
#define GL_TEXTURE30                                     0x84DE
#define GL_TEXTURE31                                     0x84DF
#define GL_ACTIVE_TEXTURE                                0x84E0

/* TextureWrapMode */
#define GL_REPEAT                                        0x2901
#define GL_CLAMP_TO_EDGE                                 0x812F
#define GL_MIRRORED_REPEAT                               0x8370

/* Uniform Types */
#define GL_FLOAT_VEC2                                    0x8B50
#define GL_FLOAT_VEC3                                    0x8B51
#define GL_FLOAT_VEC4                                    0x8B52
#define GL_INT_VEC2                                      0x8B53
#define GL_INT_VEC3                                      0x8B54
#define GL_INT_VEC4                                      0x8B55
#define GL_BOOL                                          0x8B56
#define GL_BOOL_VEC2                                     0x8B57
#define GL_BOOL_VEC3                                     0x8B58
#define GL_BOOL_VEC4                                     0x8B59
#define GL_FLOAT_MAT2                                    0x8B5A
#define GL_FLOAT_MAT3                                    0x8B5B
#define GL_FLOAT_MAT4                                    0x8B5C
#define GL_SAMPLER_2D                                    0x8B5E
#define GL_SAMPLER_CUBE                                  0x8B60

/* Vertex Arrays */
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED                   0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE                      0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE                    0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE                      0x8625
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED                0x886A
#define GL_VERTEX_ATTRIB_ARRAY_POINTER                   0x8645
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING            0x889F

/* Read Format */
#define GL_IMPLEMENTATION_COLOR_READ_TYPE                0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT              0x8B9B

/* Shader Source */
#define GL_COMPILE_STATUS                                0x8B81
#define GL_INFO_LOG_LENGTH                               0x8B84
#define GL_SHADER_SOURCE_LENGTH                          0x8B88
#define GL_SHADER_COMPILER                               0x8DFA

/* Shader Binary */
#define GL_SHADER_BINARY_FORMATS                         0x8DF8
#define GL_NUM_SHADER_BINARY_FORMATS                     0x8DF9

/* Shader Precision-Specified Types */
#define GL_LOW_FLOAT                                     0x8DF0
#define GL_MEDIUM_FLOAT                                  0x8DF1
#define GL_HIGH_FLOAT                                    0x8DF2
#define GL_LOW_INT                                       0x8DF3
#define GL_MEDIUM_INT                                    0x8DF4
#define GL_HIGH_INT                                      0x8DF5

/* Framebuffer Object. */
#define GL_FRAMEBUFFER                                   0x8D40
#define GL_RENDERBUFFER                                  0x8D41

#define GL_RGBA4                                         0x8056
#define GL_RGB5_A1                                       0x8057
#define GL_RGB565                                        0x8D62
#define GL_DEPTH_COMPONENT16                             0x81A5
#define GL_STENCIL_INDEX8                                0x8D48

#define GL_RENDERBUFFER_WIDTH                            0x8D42
#define GL_RENDERBUFFER_HEIGHT                           0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT                  0x8D44
#define GL_RENDERBUFFER_RED_SIZE                         0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE                       0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE                        0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE                       0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE                       0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE                     0x8D55

#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE            0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME            0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL          0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE  0x8CD3

#define GL_COLOR_ATTACHMENT0                             0x8CE0
#define GL_DEPTH_ATTACHMENT                              0x8D00
#define GL_STENCIL_ATTACHMENT                            0x8D20

#define GL_NONE                                          0

#define GL_FRAMEBUFFER_COMPLETE                          0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT             0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT     0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS             0x8CD9
#define GL_FRAMEBUFFER_UNSUPPORTED                       0x8CDD

#define GL_FRAMEBUFFER_BINDING                           0x8CA6
#define GL_RENDERBUFFER_BINDING                          0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE                         0x84E8

#define GL_INVALID_FRAMEBUFFER_OPERATION                 0x0506

/* OpenGL ES 3.0 */

#define GL_READ_BUFFER                                   0x0C02
#define GL_UNPACK_ROW_LENGTH                             0x0CF2
#define GL_UNPACK_SKIP_ROWS                              0x0CF3
#define GL_UNPACK_SKIP_PIXELS                            0x0CF4
#define GL_PACK_ROW_LENGTH                               0x0D02
#define GL_PACK_SKIP_ROWS                                0x0D03
#define GL_PACK_SKIP_PIXELS                              0x0D04
#define GL_COLOR                                         0x1800
#define GL_DEPTH                                         0x1801
#define GL_STENCIL                                       0x1802
#define GL_RED                                           0x1903
#define GL_RGB8                                          0x8051
#define GL_RGBA8                                         0x8058
#define GL_RGB10_A2                                      0x8059
#define GL_TEXTURE_BINDING_3D                            0x806A
#define GL_UNPACK_SKIP_IMAGES                            0x806D
#define GL_UNPACK_IMAGE_HEIGHT                           0x806E
#define GL_TEXTURE_3D                                    0x806F
#define GL_TEXTURE_WRAP_R                                0x8072
#define GL_MAX_3D_TEXTURE_SIZE                           0x8073
#define GL_UNSIGNED_INT_2_10_10_10_REV                   0x8368
#define GL_MAX_ELEMENTS_VERTICES                         0x80E8
#define GL_MAX_ELEMENTS_INDICES                          0x80E9
#define GL_TEXTURE_MIN_LOD                               0x813A
#define GL_TEXTURE_MAX_LOD                               0x813B
#define GL_TEXTURE_BASE_LEVEL                            0x813C
#define GL_TEXTURE_MAX_LEVEL                             0x813D
#define GL_MIN                                           0x8007
#define GL_MAX                                           0x8008
#define GL_DEPTH_COMPONENT24                             0x81A6
#define GL_MAX_TEXTURE_LOD_BIAS                          0x84FD
#define GL_TEXTURE_COMPARE_MODE                          0x884C
#define GL_TEXTURE_COMPARE_FUNC                          0x884D
#define GL_CURRENT_QUERY                                 0x8865
#define GL_QUERY_RESULT                                  0x8866
#define GL_QUERY_RESULT_AVAILABLE                        0x8867
#define GL_BUFFER_MAPPED                                 0x88BC
#define GL_BUFFER_MAP_POINTER                            0x88BD
#define GL_STREAM_READ                                   0x88E1
#define GL_STREAM_COPY                                   0x88E2
#define GL_STATIC_READ                                   0x88E5
#define GL_STATIC_COPY                                   0x88E6
#define GL_DYNAMIC_READ                                  0x88E9
#define GL_DYNAMIC_COPY                                  0x88EA
#define GL_MAX_DRAW_BUFFERS                              0x8824
#define GL_DRAW_BUFFER0                                  0x8825
#define GL_DRAW_BUFFER1                                  0x8826
#define GL_DRAW_BUFFER2                                  0x8827
#define GL_DRAW_BUFFER3                                  0x8828
#define GL_DRAW_BUFFER4                                  0x8829
#define GL_DRAW_BUFFER5                                  0x882A
#define GL_DRAW_BUFFER6                                  0x882B
#define GL_DRAW_BUFFER7                                  0x882C
#define GL_DRAW_BUFFER8                                  0x882D
#define GL_DRAW_BUFFER9                                  0x882E
#define GL_DRAW_BUFFER10                                 0x882F
#define GL_DRAW_BUFFER11                                 0x8830
#define GL_DRAW_BUFFER12                                 0x8831
#define GL_DRAW_BUFFER13                                 0x8832
#define GL_DRAW_BUFFER14                                 0x8833
#define GL_DRAW_BUFFER15                                 0x8834
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS               0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS                 0x8B4A
#define GL_SAMPLER_3D                                    0x8B5F
#define GL_SAMPLER_2D_SHADOW                             0x8B62
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT               0x8B8B
#define GL_PIXEL_PACK_BUFFER                             0x88EB
#define GL_PIXEL_UNPACK_BUFFER                           0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING                     0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING                   0x88EF
#define GL_FLOAT_MAT2x3                                  0x8B65
#define GL_FLOAT_MAT2x4                                  0x8B66
#define GL_FLOAT_MAT3x2                                  0x8B67
#define GL_FLOAT_MAT3x4                                  0x8B68
#define GL_FLOAT_MAT4x2                                  0x8B69
#define GL_FLOAT_MAT4x3                                  0x8B6A
#define GL_SRGB                                          0x8C40
#define GL_SRGB8                                         0x8C41
#define GL_SRGB8_ALPHA8                                  0x8C43
#define GL_COMPARE_REF_TO_TEXTURE                        0x884E
#define GL_MAJOR_VERSION                                 0x821B
#define GL_MINOR_VERSION                                 0x821C
#define GL_NUM_EXTENSIONS                                0x821D
#define GL_RGBA32F                                       0x8814
#define GL_RGB32F                                        0x8815
#define GL_RGBA16F                                       0x881A
#define GL_RGB16F                                        0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER                   0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS                      0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET                      0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET                      0x8905
#define GL_MAX_VARYING_COMPONENTS                        0x8B4B
#define GL_TEXTURE_2D_ARRAY                              0x8C1A
#define GL_TEXTURE_BINDING_2D_ARRAY                      0x8C1D
#define GL_R11F_G11F_B10F                                0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV                  0x8C3B
#define GL_RGB9_E5                                       0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV                      0x8C3E
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH         0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE                0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS    0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS                   0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START               0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE                0x8C85
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN         0x8C88
#define GL_RASTERIZER_DISCARD                            0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS       0x8C8B
#define GL_INTERLEAVED_ATTRIBS                           0x8C8C
#define GL_SEPARATE_ATTRIBS                              0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER                     0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING             0x8C8F
#define GL_RGBA32UI                                      0x8D70
#define GL_RGB32UI                                       0x8D71
#define GL_RGBA16UI                                      0x8D76
#define GL_RGB16UI                                       0x8D77
#define GL_RGBA8UI                                       0x8D7C
#define GL_RGB8UI                                        0x8D7D
#define GL_RGBA32I                                       0x8D82
#define GL_RGB32I                                        0x8D83
#define GL_RGBA16I                                       0x8D88
#define GL_RGB16I                                        0x8D89
#define GL_RGBA8I                                        0x8D8E
#define GL_RGB8I                                         0x8D8F
#define GL_RED_INTEGER                                   0x8D94
#define GL_RGB_INTEGER                                   0x8D98
#define GL_RGBA_INTEGER                                  0x8D99
#define GL_SAMPLER_2D_ARRAY                              0x8DC1
#define GL_SAMPLER_2D_ARRAY_SHADOW                       0x8DC4
#define GL_SAMPLER_CUBE_SHADOW                           0x8DC5
#define GL_UNSIGNED_INT_VEC2                             0x8DC6
#define GL_UNSIGNED_INT_VEC3                             0x8DC7
#define GL_UNSIGNED_INT_VEC4                             0x8DC8
#define GL_INT_SAMPLER_2D                                0x8DCA
#define GL_INT_SAMPLER_3D                                0x8DCB
#define GL_INT_SAMPLER_CUBE                              0x8DCC
#define GL_INT_SAMPLER_2D_ARRAY                          0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_2D                       0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D                       0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE                     0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY                 0x8DD7
#define GL_BUFFER_ACCESS_FLAGS                           0x911F
#define GL_BUFFER_MAP_LENGTH                             0x9120
#define GL_BUFFER_MAP_OFFSET                             0x9121
#define GL_DEPTH_COMPONENT32F                            0x8CAC
#define GL_DEPTH32F_STENCIL8                             0x8CAD
#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV                0x8DAD
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING         0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE         0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE               0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE             0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE              0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE             0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE             0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE           0x8217
#define GL_FRAMEBUFFER_DEFAULT                           0x8218
#define GL_FRAMEBUFFER_UNDEFINED                         0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT                      0x821A
#define GL_DEPTH_STENCIL                                 0x84F9
#define GL_UNSIGNED_INT_24_8                             0x84FA
#define GL_DEPTH24_STENCIL8                              0x88F0
#define GL_UNSIGNED_NORMALIZED                           0x8C17
#define GL_DRAW_FRAMEBUFFER_BINDING                      GL_FRAMEBUFFER_BINDING
#define GL_READ_FRAMEBUFFER                              0x8CA8
#define GL_DRAW_FRAMEBUFFER                              0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING                      0x8CAA
#define GL_RENDERBUFFER_SAMPLES                          0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER          0x8CD4
#define GL_MAX_COLOR_ATTACHMENTS                         0x8CDF
#define GL_COLOR_ATTACHMENT1                             0x8CE1
#define GL_COLOR_ATTACHMENT2                             0x8CE2
#define GL_COLOR_ATTACHMENT3                             0x8CE3
#define GL_COLOR_ATTACHMENT4                             0x8CE4
#define GL_COLOR_ATTACHMENT5                             0x8CE5
#define GL_COLOR_ATTACHMENT6                             0x8CE6
#define GL_COLOR_ATTACHMENT7                             0x8CE7
#define GL_COLOR_ATTACHMENT8                             0x8CE8
#define GL_COLOR_ATTACHMENT9                             0x8CE9
#define GL_COLOR_ATTACHMENT10                            0x8CEA
#define GL_COLOR_ATTACHMENT11                            0x8CEB
#define GL_COLOR_ATTACHMENT12                            0x8CEC
#define GL_COLOR_ATTACHMENT13                            0x8CED
#define GL_COLOR_ATTACHMENT14                            0x8CEE
#define GL_COLOR_ATTACHMENT15                            0x8CEF
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE            0x8D56
#define GL_MAX_SAMPLES                                   0x8D57
#define GL_HALF_FLOAT                                    0x140B
#define GL_MAP_READ_BIT                                  0x0001
#define GL_MAP_WRITE_BIT                                 0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT                      0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT                     0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT                        0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT                        0x0020
#define GL_RG                                            0x8227
#define GL_RG_INTEGER                                    0x8228
#define GL_R8                                            0x8229
#define GL_RG8                                           0x822B
#define GL_R16F                                          0x822D
#define GL_R32F                                          0x822E
#define GL_RG16F                                         0x822F
#define GL_RG32F                                         0x8230
#define GL_R8I                                           0x8231
#define GL_R8UI                                          0x8232
#define GL_R16I                                          0x8233
#define GL_R16UI                                         0x8234
#define GL_R32I                                          0x8235
#define GL_R32UI                                         0x8236
#define GL_RG8I                                          0x8237
#define GL_RG8UI                                         0x8238
#define GL_RG16I                                         0x8239
#define GL_RG16UI                                        0x823A
#define GL_RG32I                                         0x823B
#define GL_RG32UI                                        0x823C
#define GL_VERTEX_ARRAY_BINDING                          0x85B5
#define GL_R8_SNORM                                      0x8F94
#define GL_RG8_SNORM                                     0x8F95
#define GL_RGB8_SNORM                                    0x8F96
#define GL_RGBA8_SNORM                                   0x8F97
#define GL_SIGNED_NORMALIZED                             0x8F9C
#define GL_PRIMITIVE_RESTART_FIXED_INDEX                 0x8D69
#define GL_COPY_READ_BUFFER                              0x8F36
#define GL_COPY_WRITE_BUFFER                             0x8F37
#define GL_COPY_READ_BUFFER_BINDING                      GL_COPY_READ_BUFFER
#define GL_COPY_WRITE_BUFFER_BINDING                     GL_COPY_WRITE_BUFFER
#define GL_UNIFORM_BUFFER                                0x8A11
#define GL_UNIFORM_BUFFER_BINDING                        0x8A28
#define GL_UNIFORM_BUFFER_START                          0x8A29
#define GL_UNIFORM_BUFFER_SIZE                           0x8A2A
#define GL_MAX_VERTEX_UNIFORM_BLOCKS                     0x8A2B
#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS                   0x8A2D
#define GL_MAX_COMBINED_UNIFORM_BLOCKS                   0x8A2E
#define GL_MAX_UNIFORM_BUFFER_BINDINGS                   0x8A2F
#define GL_MAX_UNIFORM_BLOCK_SIZE                        0x8A30
#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS        0x8A31
#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS      0x8A33
#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT               0x8A34
#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH          0x8A35
#define GL_ACTIVE_UNIFORM_BLOCKS                         0x8A36
#define GL_UNIFORM_TYPE                                  0x8A37
#define GL_UNIFORM_SIZE                                  0x8A38
#define GL_UNIFORM_NAME_LENGTH                           0x8A39
#define GL_UNIFORM_BLOCK_INDEX                           0x8A3A
#define GL_UNIFORM_OFFSET                                0x8A3B
#define GL_UNIFORM_ARRAY_STRIDE                          0x8A3C
#define GL_UNIFORM_MATRIX_STRIDE                         0x8A3D
#define GL_UNIFORM_IS_ROW_MAJOR                          0x8A3E
#define GL_UNIFORM_BLOCK_BINDING                         0x8A3F
#define GL_UNIFORM_BLOCK_DATA_SIZE                       0x8A40
#define GL_UNIFORM_BLOCK_NAME_LENGTH                     0x8A41
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS                 0x8A42
#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES          0x8A43
#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER     0x8A44
#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER   0x8A46
#define GL_INVALID_INDEX                                 0xFFFFFFFFu
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS                  0x9122
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS                 0x9125
#define GL_MAX_SERVER_WAIT_TIMEOUT                       0x9111
#define GL_OBJECT_TYPE                                   0x9112
#define GL_SYNC_CONDITION                                0x9113
#define GL_SYNC_STATUS                                   0x9114
#define GL_SYNC_FLAGS                                    0x9115
#define GL_SYNC_FENCE                                    0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE                    0x9117
#define GL_UNSIGNALED                                    0x9118
#define GL_SIGNALED                                      0x9119
#define GL_ALREADY_SIGNALED                              0x911A
#define GL_TIMEOUT_EXPIRED                               0x911B
#define GL_CONDITION_SATISFIED                           0x911C
#define GL_WAIT_FAILED                                   0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT                       0x00000001
#define GL_TIMEOUT_IGNORED                               0xFFFFFFFFFFFFFFFFull
#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR                   0x88FE
#define GL_ANY_SAMPLES_PASSED                            0x8C2F
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE               0x8D6A
#define GL_SAMPLER_BINDING                               0x8919
#define GL_RGB10_A2UI                                    0x906F
#define GL_TEXTURE_SWIZZLE_R                             0x8E42
#define GL_TEXTURE_SWIZZLE_G                             0x8E43
#define GL_TEXTURE_SWIZZLE_B                             0x8E44
#define GL_TEXTURE_SWIZZLE_A                             0x8E45
#define GL_GREEN                                         0x1904
#define GL_BLUE                                          0x1905
#define GL_INT_2_10_10_10_REV                            0x8D9F
#define GL_TRANSFORM_FEEDBACK                            0x8E22
#define GL_TRANSFORM_FEEDBACK_PAUSED                     0x8E23
#define GL_TRANSFORM_FEEDBACK_ACTIVE                     0x8E24
#define GL_TRANSFORM_FEEDBACK_BINDING                    0x8E25
#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT               0x8257
#define GL_PROGRAM_BINARY_LENGTH                         0x8741
#define GL_NUM_PROGRAM_BINARY_FORMATS                    0x87FE
#define GL_PROGRAM_BINARY_FORMATS                        0x87FF
#define GL_COMPRESSED_R11_EAC                            0x9270
#define GL_COMPRESSED_SIGNED_R11_EAC                     0x9271
#define GL_COMPRESSED_RG11_EAC                           0x9272
#define GL_COMPRESSED_SIGNED_RG11_EAC                    0x9273
#define GL_COMPRESSED_RGB8_ETC2                          0x9274
#define GL_COMPRESSED_SRGB8_ETC2                         0x9275
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2      0x9276
#define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2     0x9277
#define GL_COMPRESSED_RGBA8_ETC2_EAC                     0x9278
#define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC              0x9279
#define GL_TEXTURE_IMMUTABLE_FORMAT                      0x912F
#define GL_MAX_ELEMENT_INDEX                             0x8D6B
#define GL_NUM_SAMPLE_COUNTS                             0x9380
#define GL_TEXTURE_IMMUTABLE_LEVELS                      0x82DF

/*-------------------------------------------------------------------------
 * Entrypoint definitions
 *-----------------------------------------------------------------------*/

/* OpenGL ES 2.0 */

GL_API void           GL_APIENTRY glActiveTexture (GLenum texture) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glAttachShader (GLuint program, GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindTexture (GLenum target, GLuint texture) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendEquation (GLenum mode)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendEquationSeparate (GLenum modeRGB, GLenum modeAlpha)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum         GL_APIENTRY glCheckFramebufferStatus (GLenum target)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClear (GLbitfield mask) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearDepthf (GLclampf depth) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearStencil (GLint s) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompileShader (GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLuint         GL_APIENTRY glCreateProgram (void)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLuint         GL_APIENTRY glCreateShader (GLenum type)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCullFace (GLenum mode) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint* buffers) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteFramebuffers (GLsizei n, const GLuint* framebuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteShader (GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint* textures) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDepthFunc (GLenum func) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDepthMask (GLboolean flag) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDepthRangef (GLclampf zNear, GLclampf zFar) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDetachShader (GLuint program, GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDisable (GLenum cap) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDisableVertexAttribArray (GLuint index)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glEnable (GLenum cap) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glEnableVertexAttribArray (GLuint index)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFinish (void) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFlush (void) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFrontFace (GLenum mode) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenBuffers (GLsizei n, GLuint* buffers) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenerateMipmap (GLenum target)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenFramebuffers (GLsizei n, GLuint* framebuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenRenderbuffers (GLsizei n, GLuint* renderbuffers)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenTextures (GLsizei n, GLuint* textures) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API int            GL_APIENTRY glGetAttribLocation (GLuint program, const GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum         GL_APIENTRY glGetError (void) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetFloatv (GLenum pname, GLfloat* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetIntegerv (GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderiv (GLuint shader, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderInfoLog (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderPrecisionFormat (GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetShaderSource (GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API const GLubyte* GL_APIENTRY glGetString (GLenum name) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API int            GL_APIENTRY glGetUniformLocation (GLuint program, const GLchar* name)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribPointerv (GLuint index, GLenum pname, GLvoid** pointer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glHint (GLenum target, GLenum mode) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsBuffer (GLuint buffer) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsEnabled (GLenum cap) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsFramebuffer (GLuint framebuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsProgram (GLuint program) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsRenderbuffer (GLuint renderbuffer)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsShader (GLuint shader)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsTexture (GLuint texture) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glLineWidth (GLfloat width) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glLinkProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glPixelStorei (GLenum pname, GLint param) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glReleaseShaderCompiler (void)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glSampleCoverage (GLclampf value, GLboolean invert) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glShaderBinary (GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glShaderSource (GLuint shader, GLsizei count, const GLchar* const *string, const GLint* length)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilFuncSeparate (GLenum face, GLenum func, GLint ref, GLuint mask)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilMask (GLuint mask) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilMaskSeparate (GLenum face, GLuint mask)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glStencilOpSeparate (GLenum face, GLenum fail, GLenum zfail, GLenum zpass)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint* params) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1f (GLint location, GLfloat x)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1i (GLint location, GLint x)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2f (GLint location, GLfloat x, GLfloat y)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2i (GLint location, GLint x, GLint y)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3i (GLint location, GLint x, GLint y, GLint z)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4fv (GLint location, GLsizei count, const GLfloat* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4i (GLint location, GLint x, GLint y, GLint z, GLint w)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4iv (GLint location, GLsizei count, const GLint* v)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUseProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glValidateProgram (GLuint program)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib1f (GLuint indx, GLfloat x)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib1fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib2f (GLuint indx, GLfloat x, GLfloat y)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib2fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib3f (GLuint indx, GLfloat x, GLfloat y, GLfloat z)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib3fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib4f (GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttrib4fv (GLuint indx, const GLfloat* values)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)   OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(3.0, 12.0), tvos(9.0, 12.0));

/* OpenGL ES 3.0 */

GL_API void           GL_APIENTRY glReadBuffer (GLenum mode)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenQueries (GLsizei n, GLuint* ids)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteQueries (GLsizei n, const GLuint* ids)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsQuery (GLuint id)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBeginQuery (GLenum target, GLuint id)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glEndQuery (GLenum target)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetQueryiv (GLenum target, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetQueryObjectuiv (GLuint id, GLenum pname, GLuint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glUnmapBuffer (GLenum target)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetBufferPointerv (GLenum target, GLenum pname, GLvoid** params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawBuffers (GLsizei n, const GLenum* bufs)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix2x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix3x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix2x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix4x2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix3x4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformMatrix4x3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glRenderbufferStorageMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFramebufferTextureLayer (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid*        GL_APIENTRY glMapBufferRange (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glFlushMappedBufferRange (GLenum target, GLintptr offset, GLsizeiptr length)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindVertexArray (GLuint array)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteVertexArrays (GLsizei n, const GLuint* arrays)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenVertexArrays (GLsizei n, GLuint* arrays)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsVertexArray (GLuint array)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetIntegeri_v (GLenum target, GLuint index, GLint* data)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBeginTransformFeedback (GLenum primitiveMode)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glEndTransformFeedback (void)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindBufferRange (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindBufferBase (GLenum target, GLuint index, GLuint buffer)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTransformFeedbackVaryings (GLuint program, GLsizei count, const GLchar* const *varyings, GLenum bufferMode)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetTransformFeedbackVarying (GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribIPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribIiv (GLuint index, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetVertexAttribIuiv (GLuint index, GLenum pname, GLuint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribI4i (GLuint index, GLint x, GLint y, GLint z, GLint w)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribI4ui (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribI4iv (GLuint index, const GLint* v)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribI4uiv (GLuint index, const GLuint* v)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetUniformuiv (GLuint program, GLint location, GLuint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLint          GL_APIENTRY glGetFragDataLocation (GLuint program, const GLchar *name)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1ui (GLint location, GLuint v0)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform1uiv (GLint location, GLsizei count, const GLuint* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform2uiv (GLint location, GLsizei count, const GLuint* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform3uiv (GLint location, GLsizei count, const GLuint* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniform4uiv (GLint location, GLsizei count, const GLuint* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearBufferiv (GLenum buffer, GLint drawbuffer, const GLint* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearBufferuiv (GLenum buffer, GLint drawbuffer, const GLuint* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearBufferfv (GLenum buffer, GLint drawbuffer, const GLfloat* value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glClearBufferfi (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API const GLubyte* GL_APIENTRY glGetStringi (GLenum name, GLuint index)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glCopyBufferSubData (GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetUniformIndices (GLuint program, GLsizei uniformCount, const GLchar* const *uniformNames, GLuint* uniformIndices)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetActiveUniformsiv (GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLuint         GL_APIENTRY glGetUniformBlockIndex (GLuint program, const GLchar* uniformBlockName)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetActiveUniformBlockiv (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetActiveUniformBlockName (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glUniformBlockBinding (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawArraysInstanced (GLenum mode, GLint first, GLsizei count, GLsizei instancecount)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDrawElementsInstanced (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instancecount)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLsync         GL_APIENTRY glFenceSync (GLenum condition, GLbitfield flags)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsSync (GLsync sync)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteSync (GLsync sync)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum         GL_APIENTRY glClientWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glWaitSync (GLsync sync, GLbitfield flags, GLuint64 timeout)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetInteger64v (GLenum pname, GLint64* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetSynciv (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetInteger64i_v (GLenum target, GLuint index, GLint64* data)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetBufferParameteri64v (GLenum target, GLenum pname, GLint64* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenSamplers (GLsizei count, GLuint* samplers)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteSamplers (GLsizei count, const GLuint* samplers)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsSampler (GLuint sampler)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindSampler (GLuint unit, GLuint sampler)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glSamplerParameteri (GLuint sampler, GLenum pname, GLint param)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glSamplerParameteriv (GLuint sampler, GLenum pname, const GLint* param)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glSamplerParameterf (GLuint sampler, GLenum pname, GLfloat param)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glSamplerParameterfv (GLuint sampler, GLenum pname, const GLfloat* param)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetSamplerParameteriv (GLuint sampler, GLenum pname, GLint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetSamplerParameterfv (GLuint sampler, GLenum pname, GLfloat* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glVertexAttribDivisor (GLuint index, GLuint divisor)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glBindTransformFeedback (GLenum target, GLuint id)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glDeleteTransformFeedbacks (GLsizei n, const GLuint* ids)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGenTransformFeedbacks (GLsizei n, GLuint* ids)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean      GL_APIENTRY glIsTransformFeedback (GLuint id)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glPauseTransformFeedback (void)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glResumeTransformFeedback (void)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetProgramBinary (GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glProgramBinary (GLuint program, GLenum binaryFormat, const GLvoid* binary, GLsizei length)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glProgramParameteri (GLuint program, GLenum pname, GLint value)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glInvalidateFramebuffer (GLenum target, GLsizei numAttachments, const GLenum* attachments)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glInvalidateSubFramebuffer (GLenum target, GLsizei numAttachments, const GLenum* attachments, GLint x, GLint y, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexStorage2D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glTexStorage3D (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));
GL_API void           GL_APIENTRY glGetInternalformativ (GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint* params)   OPENGLES_DEPRECATED(ios(7.0, 12.0), tvos(9.0, 12.0));

#ifdef __cplusplus
}
#endif

#endif /* __gl_es30_h_ */
// ==========  OpenGLES.framework/Headers/EAGL.h
/*
    Copyright:  (c) 2006-2013 Apple Inc. All rights reserved.
*/

#ifndef _EAGL_H_
#define _EAGL_H_

#include <Foundation/Foundation.h>
#include <Availability.h>
#include <OpenGLES/OpenGLESAvailability.h>


#ifdef __cplusplus
#define EAGL_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define EAGL_EXTERN extern __attribute__((visibility ("default")))
#endif

#define EAGL_EXTERN_CLASS __attribute__((visibility("default")))

/************************************************************************/
/* EAGL API Version                                                     */
/************************************************************************/
#define EAGL_MAJOR_VERSION   1
#define EAGL_MINOR_VERSION   0


/************************************************************************/
/* EAGL Enumerated values                                               */
/************************************************************************/

/* EAGL rendering API */
typedef NS_ENUM(NSUInteger, EAGLRenderingAPI)
{
	kEAGLRenderingAPIOpenGLES1 = 1,
	kEAGLRenderingAPIOpenGLES2 = 2,
	kEAGLRenderingAPIOpenGLES3 = 3,
};


/************************************************************************/
/* EAGL Functions                                                       */
/************************************************************************/

EAGL_EXTERN void EAGLGetVersion(unsigned int* major, unsigned int* minor) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

/************************************************************************/
/* EAGL Sharegroup                                                      */
/************************************************************************/

EAGL_EXTERN_CLASS
@interface EAGLSharegroup : NSObject
{
@package
	struct _EAGLSharegroupPrivate *_private;
}

@property (copy, nonatomic) NSString* debugLabel NS_AVAILABLE_IOS(6_0);

@end

/************************************************************************/
/* EAGL Context                                                         */
/************************************************************************/

EAGL_EXTERN_CLASS
OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0))
@interface EAGLContext : NSObject 
{
@public
	struct _EAGLContextPrivate *_private;
}

- (instancetype) init NS_UNAVAILABLE;
- (instancetype) initWithAPI:(EAGLRenderingAPI) api;
- (instancetype) initWithAPI:(EAGLRenderingAPI) api sharegroup:(EAGLSharegroup*) sharegroup NS_DESIGNATED_INITIALIZER;

+ (BOOL)            setCurrentContext:(EAGLContext*) context;
+ (EAGLContext*)    currentContext;

@property (readonly) EAGLRenderingAPI   API;
@property (readonly) EAGLSharegroup*    sharegroup;

@property (copy, nonatomic) NSString* debugLabel NS_AVAILABLE_IOS(6_0);
@property (getter=isMultiThreaded, nonatomic) BOOL multiThreaded NS_AVAILABLE_IOS(7_1);
@end


#endif /* _EAGL_H_ */

// ==========  OpenGLES.framework/Headers/ES1/glext.h
#ifndef ES1_GLEXT_H_GUARD
#define ES1_GLEXT_H_GUARD

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/OpenGLESAvailability.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
**
** http://oss.sgi.com/projects/FreeB
**
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
**
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
**
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

#define GL_APPLE_copy_texture_levels                            1
#define GL_APPLE_framebuffer_multisample                        1
#define GL_APPLE_texture_2D_limited_npot                        1
#define GL_APPLE_texture_format_BGRA8888                        1
#define GL_APPLE_texture_max_level                              1
#define GL_EXT_blend_minmax                                     1
#define GL_EXT_debug_label                                      1
#define GL_EXT_debug_marker                                     1
#define GL_EXT_discard_framebuffer                              1
#define GL_EXT_map_buffer_range                                 1
#define GL_EXT_read_format_bgra                                 1
#define GL_EXT_texture_filter_anisotropic                       1
#define GL_EXT_texture_lod_bias                                 1
#define GL_EXT_texture_storage                                  1
#define GL_IMG_read_format                                      1
#define GL_IMG_texture_compression_pvrtc                        1
#define GL_OES_blend_equation_separate                          1
#define GL_OES_blend_func_separate                              1
#define GL_OES_blend_subtract                                   1
#define GL_OES_depth24                                          1
#define GL_OES_element_index_uint                               1
#define GL_OES_fbo_render_mipmap                                1
#define GL_OES_framebuffer_object                               1
#define GL_OES_mapbuffer                                        1
#define GL_OES_packed_depth_stencil                             1
#define GL_OES_rgb8_rgba8                                       1
#define GL_OES_stencil_wrap                                     1
#define GL_OES_stencil8                                         1
#define GL_OES_texture_mirrored_repeat                          1
#define GL_OES_vertex_array_object                              1


/*------------------------------------------------------------------------*
 * APPLE extension tokens
 *------------------------------------------------------------------------*/
#if GL_APPLE_framebuffer_multisample
#define GL_RENDERBUFFER_SAMPLES_APPLE                           0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE             0x8D56
#define GL_MAX_SAMPLES_APPLE                                    0x8D57
#define GL_READ_FRAMEBUFFER_APPLE                               0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE                               0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE                       0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE                       0x8CAA
#endif

#if GL_APPLE_texture_format_BGRA8888
#define GL_BGRA_EXT                                             0x80E1
#endif

#if GL_APPLE_texture_format_BGRA8888 || GL_IMG_read_format
#define GL_BGRA                                                 0x80E1
#endif

#if GL_APPLE_texture_max_level
#define GL_TEXTURE_MAX_LEVEL_APPLE                              0x813D
#endif

/*------------------------------------------------------------------------*
 * EXT extension tokens
 *------------------------------------------------------------------------*/
#if GL_EXT_blend_minmax
#define GL_MIN_EXT                                              0x8007
#define GL_MAX_EXT                                              0x8008
#endif

#if GL_EXT_debug_label
#define GL_BUFFER_OBJECT_EXT                                    0x9151
#define GL_VERTEX_ARRAY_OBJECT_EXT                              0x9154
#endif

#if GL_EXT_discard_framebuffer
#define GL_COLOR_EXT                                            0x1800
#define GL_DEPTH_EXT                                            0x1801
#define GL_STENCIL_EXT                                          0x1802
#endif

#if GL_EXT_map_buffer_range
#define GL_MAP_READ_BIT_EXT                                     0x0001
#define GL_MAP_WRITE_BIT_EXT                                    0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT                         0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT                        0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT                           0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT                           0x0020
#endif

#if GL_EXT_read_format_bgra
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT                       0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT                       0x8366
#define GL_UNSIGNED_SHORT_1_5_5_5_REV                           0x8366
#endif

#if GL_EXT_read_format_bgra || GL_IMG_read_format
#define GL_UNSIGNED_SHORT_4_4_4_4_REV                           0x8365
#endif

#if GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF
#endif

#if GL_EXT_texture_lod_bias
#define GL_MAX_TEXTURE_LOD_BIAS_EXT                             0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT                           0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                                 0x8501
#endif

#if GL_EXT_texture_storage
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT                         0x912F
#define GL_ALPHA8_EXT                                           0x803C
#define GL_LUMINANCE8_EXT                                       0x8040
#define GL_LUMINANCE8_ALPHA8_EXT                                0x8045
#define GL_BGRA8_EXT                                            0x93A1
#endif

/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/
#if GL_IMG_read_format
#define GL_BGRA_IMG                                             0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG                       0x8365
#endif

#if GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03
#endif

/*------------------------------------------------------------------------*
 * OES extension tokens
 *------------------------------------------------------------------------*/
#if GL_OES_blend_equation_separate
#define GL_BLEND_EQUATION_RGB_OES                               0x8009
#define GL_BLEND_EQUATION_ALPHA_OES                             0x883D
#endif

#if GL_OES_blend_func_separate
#define GL_BLEND_DST_RGB_OES                                    0x80C8
#define GL_BLEND_SRC_RGB_OES                                    0x80C9
#define GL_BLEND_DST_ALPHA_OES                                  0x80CA
#define GL_BLEND_SRC_ALPHA_OES                                  0x80CB
#endif

#if GL_OES_blend_subtract
#define GL_BLEND_EQUATION_OES                                   0x8009
#define GL_FUNC_ADD_OES                                         0x8006
#define GL_FUNC_SUBTRACT_OES                                    0x800A
#define GL_FUNC_REVERSE_SUBTRACT_OES                            0x800B
#endif

#if GL_OES_depth24
#define GL_DEPTH_COMPONENT24_OES                                0x81A6
#endif

#if GL_OES_element_index_uint
#define GL_UNSIGNED_INT_OES                                     0x1405
#endif

#if GL_OES_framebuffer_object
#define GL_FRAMEBUFFER_OES                                      0x8D40
#define GL_RENDERBUFFER_OES                                     0x8D41
#define GL_RGBA4_OES                                            0x8056
#define GL_RGB5_A1_OES                                          0x8057
#define GL_RGB565_OES                                           0x8D62
#define GL_DEPTH_COMPONENT16_OES                                0x81A5
#define GL_RENDERBUFFER_WIDTH_OES                               0x8D42
#define GL_RENDERBUFFER_HEIGHT_OES                              0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_OES                     0x8D44
#define GL_RENDERBUFFER_RED_SIZE_OES                            0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_OES                          0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_OES                           0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_OES                          0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_OES                          0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_OES                        0x8D55
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES               0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES               0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES             0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES     0x8CD3
#define GL_COLOR_ATTACHMENT0_OES                                0x8CE0
#define GL_DEPTH_ATTACHMENT_OES                                 0x8D00
#define GL_STENCIL_ATTACHMENT_OES                               0x8D20
#define GL_FRAMEBUFFER_COMPLETE_OES                             0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES                0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES        0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES                0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES                   0x8CDA
#define GL_FRAMEBUFFER_UNSUPPORTED_OES                          0x8CDD
#define GL_FRAMEBUFFER_BINDING_OES                              0x8CA6
#define GL_RENDERBUFFER_BINDING_OES                             0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE_OES                            0x84E8
#define GL_INVALID_FRAMEBUFFER_OPERATION_OES                    0x0506
#endif

#if GL_OES_mapbuffer
#define GL_WRITE_ONLY_OES                                       0x88B9
#define GL_BUFFER_ACCESS_OES                                    0x88BB
#define GL_BUFFER_MAPPED_OES                                    0x88BC
#define GL_BUFFER_MAP_POINTER_OES                               0x88BD
#endif

#if GL_OES_packed_depth_stencil
#define GL_DEPTH_STENCIL_OES                                    0x84F9
#define GL_UNSIGNED_INT_24_8_OES                                0x84FA
#define GL_DEPTH24_STENCIL8_OES                                 0x88F0
#endif

#if GL_OES_rgb8_rgba8
#define GL_RGB8_OES                                             0x8051
#define GL_RGBA8_OES                                            0x8058
#endif

#if GL_OES_stencil_wrap
#define GL_INCR_WRAP_OES                                        0x8507
#define GL_DECR_WRAP_OES                                        0x8508
#endif

#if GL_OES_stencil8
#define GL_STENCIL_INDEX8_OES                                   0x8D48
#endif

#if GL_OES_texture_mirrored_repeat
#define GL_MIRRORED_REPEAT_OES                                  0x8370
#endif

#if GL_OES_vertex_array_object
#define GL_VERTEX_ARRAY_BINDING_OES                             0x85B5
#endif

/**************************************************************************/

/*------------------------------------------------------------------------*
 * APPLE extension functions
 *------------------------------------------------------------------------*/
#if GL_APPLE_copy_texture_levels
GL_API GLvoid glCopyTextureLevelsAPPLE(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount)   OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_APPLE_framebuffer_multisample
GL_API GLvoid glRenderbufferStorageMultisampleAPPLE(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glResolveMultisampleFramebufferAPPLE(void)  ;
#endif

/*------------------------------------------------------------------------*
 * EXT extension functions
 *------------------------------------------------------------------------*/
#if GL_EXT_debug_label
GL_API GLvoid glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const char *label)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, char *label)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_debug_marker
GL_API GLvoid glInsertEventMarkerEXT(GLsizei length, const char *marker)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glPushGroupMarkerEXT(GLsizei length, const char *marker)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glPopGroupMarkerEXT(void)   OPENGLES_DEPRECATED(ios(5.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_discard_framebuffer
GL_API GLvoid GL_APIENTRY glDiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum *attachments)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_map_buffer_range
GL_API GLvoid *glMapBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)   OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glFlushMappedBufferRangeEXT(GLenum target, GLintptr offset, GLsizeiptr length)   OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_EXT_texture_storage
GL_API GLvoid glTexStorage2DEXT(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)   OPENGLES_DEPRECATED(ios(6.0, 12.0), tvos(9.0, 12.0));
#endif

/*------------------------------------------------------------------------*
 * OES extension functions
 *------------------------------------------------------------------------*/
#if GL_OES_blend_equation_separate
GL_API GLvoid GL_APIENTRY glBlendEquationSeparateOES (GLenum modeRGB, GLenum modeAlpha)   OPENGLES_DEPRECATED(ios(3.1, 12.0), tvos(9.0, 12.0));
#endif

#if GL_OES_blend_func_separate
GL_API GLvoid GL_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)   OPENGLES_DEPRECATED(ios(3.1, 12.0), tvos(9.0, 12.0));
#endif

#if GL_OES_blend_subtract
GL_API GLvoid GL_APIENTRY glBlendEquationOES (GLenum mode);
#endif

#if GL_OES_framebuffer_object
GL_API GLboolean GL_APIENTRY glIsRenderbufferOES (GLuint renderbuffer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glDeleteRenderbuffersOES (GLsizei n, const GLuint* renderbuffers) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint* renderbuffers) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean GL_APIENTRY glIsFramebufferOES (GLuint framebuffer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glDeleteFramebuffersOES (GLsizei n, const GLuint* framebuffers) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint* framebuffers) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum GL_APIENTRY glCheckFramebufferStatusOES (GLenum target) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint* params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid GL_APIENTRY glGenerateMipmapOES (GLenum target) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_OES_mapbuffer
GL_API GLvoid GL_APIENTRY glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid **params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid * GL_APIENTRY glMapBufferOES (GLenum target, GLenum access) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean GL_APIENTRY glUnmapBufferOES (GLenum target) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
#endif

#if GL_OES_vertex_array_object
GL_API GLvoid glBindVertexArrayOES(GLuint array)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLvoid glGenVertexArraysOES(GLsizei n, GLuint *arrays)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean glIsVertexArrayOES(GLuint array)   OPENGLES_DEPRECATED(ios(4.0, 12.0), tvos(9.0, 12.0));
#endif

#ifdef __cplusplus
}
#endif

#endif /* ES1_GLEXT_H_GUARD */
// ==========  OpenGLES.framework/Headers/ES1/gl.h
#ifndef ES1_GL_H_GUARD
#define ES1_GL_H_GUARD

#ifdef __cplusplus
extern "C" {
#endif

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
**
** http://oss.sgi.com/projects/FreeB
**
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
**
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
**
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

#define GL_APIENTRY
#define GL_API extern

#include <OpenGLES/OpenGLESAvailability.h>
#include <OpenGLES/gltypes.h>


/*************************************************************/

/* OpenGL ES core versions */
#define GL_VERSION_ES_CM_1_0              1
#define GL_VERSION_ES_CL_1_0              1
#define GL_VERSION_ES_CM_1_1              1
#define GL_VERSION_ES_CL_1_1              1

/* Legacy core versions */
#define GL_OES_VERSION_1_0                1
#define GL_OES_VERSION_1_1                1

/* Extensions */
#define GL_OES_byte_coordinates           1
#define GL_OES_compressed_paletted_texture 1
#define GL_OES_draw_texture               1
#define GL_OES_fixed_point                1
#define GL_OES_matrix_get                 1
#define GL_OES_matrix_palette             1
#define GL_OES_point_size_array           1
#define GL_OES_point_sprite               1
#define GL_OES_read_format                1
#define GL_OES_single_precision           1

/* ClearBufferMask */
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

/* Boolean */
#define GL_FALSE                          0
#define GL_TRUE                           1

/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

/* AlphaFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* ClipPlaneName */
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

/* ColorMaterialFace */
/*      GL_FRONT_AND_BACK */

/* ColorMaterialParameter */
/*      GL_AMBIENT_AND_DIFFUSE */

/* ColorPointerType */
/*      GL_UNSIGNED_BYTE */
/*      GL_FLOAT */
/*      GL_FIXED */

/* CullFaceMode */
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408

/* DepthFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* EnableCap */
#define GL_FOG                            0x0B60
#define GL_LIGHTING                       0x0B50
#define GL_TEXTURE_2D                     0x0DE1
#define GL_CULL_FACE                      0x0B44
#define GL_ALPHA_TEST                     0x0BC0
#define GL_BLEND                          0x0BE2
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_DITHER                         0x0BD0
#define GL_STENCIL_TEST                   0x0B90
#define GL_DEPTH_TEST                     0x0B71
/*      GL_LIGHT0 */
/*      GL_LIGHT1 */
/*      GL_LIGHT2 */
/*      GL_LIGHT3 */
/*      GL_LIGHT4 */
/*      GL_LIGHT5 */
/*      GL_LIGHT6 */
/*      GL_LIGHT7 */
#define GL_POINT_SMOOTH                   0x0B10
#define GL_LINE_SMOOTH                    0x0B20
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_MATERIAL                 0x0B57
#define GL_NORMALIZE                      0x0BA1
#define GL_RESCALE_NORMAL                 0x803A
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_TEXTURE_COORD_ARRAY            0x8078
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0

/* ErrorCode */
#define GL_NO_ERROR                       0
#define GL_INVALID_ENUM                   0x0500
#define GL_INVALID_VALUE                  0x0501
#define GL_INVALID_OPERATION              0x0502
#define GL_STACK_OVERFLOW                 0x0503
#define GL_STACK_UNDERFLOW                0x0504
#define GL_OUT_OF_MEMORY                  0x0505

/* FogMode */
/*      GL_LINEAR */
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801

/* FogParameter */
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66

/* FrontFaceDirection */
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

/* GetPName */
#define GL_CURRENT_COLOR                  0x0B00
#define GL_CURRENT_NORMAL                 0x0B02
#define GL_CURRENT_TEXTURE_COORDS         0x0B03
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_MIN                 0x8126
#define GL_POINT_SIZE_MAX                 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_POINT_DISTANCE_ATTENUATION     0x8129
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_LINE_WIDTH                     0x0B21
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_SHADE_MODEL                    0x0B54
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_MATRIX_MODE                    0x0BA0
#define GL_VIEWPORT                       0x0BA2
#define GL_MODELVIEW_STACK_DEPTH          0x0BA3
#define GL_PROJECTION_STACK_DEPTH         0x0BA4
#define GL_TEXTURE_STACK_DEPTH            0x0BA5
#define GL_MODELVIEW_MATRIX               0x0BA6
#define GL_PROJECTION_MATRIX              0x0BA7
#define GL_TEXTURE_MATRIX                 0x0BA8
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAX_LIGHTS                     0x0D31
#define GL_MAX_CLIP_PLANES                0x0D32
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define GL_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_MAX_TEXTURE_UNITS              0x84E2
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_POLYGON_OFFSET_UNITS           0x2A00
#define GL_POLYGON_OFFSET_FILL            0x8037
#define GL_POLYGON_OFFSET_FACTOR          0x8038
#define GL_TEXTURE_BINDING_2D             0x8069
#define GL_VERTEX_ARRAY_SIZE              0x807A
#define GL_VERTEX_ARRAY_TYPE              0x807B
#define GL_VERTEX_ARRAY_STRIDE            0x807C
#define GL_NORMAL_ARRAY_TYPE              0x807E
#define GL_NORMAL_ARRAY_STRIDE            0x807F
#define GL_COLOR_ARRAY_SIZE               0x8081
#define GL_COLOR_ARRAY_TYPE               0x8082
#define GL_COLOR_ARRAY_STRIDE             0x8083
#define GL_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define GL_VERTEX_ARRAY_POINTER           0x808E
#define GL_NORMAL_ARRAY_POINTER           0x808F
#define GL_COLOR_ARRAY_POINTER            0x8090
#define GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB

/* GetTextureParameter */
/*      GL_TEXTURE_MAG_FILTER */
/*      GL_TEXTURE_MIN_FILTER */
/*      GL_TEXTURE_WRAP_S */
/*      GL_TEXTURE_WRAP_T */

#define GL_IMPLEMENTATION_COLOR_READ_TYPE_OES   0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES 0x8B9B
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS       0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS           0x86A3

/* HintMode */
#define GL_DONT_CARE                      0x1100
#define GL_FASTEST                        0x1101
#define GL_NICEST                         0x1102

/* HintTarget */
#define GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define GL_POINT_SMOOTH_HINT              0x0C51
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_FOG_HINT                       0x0C54
#define GL_GENERATE_MIPMAP_HINT           0x8192

/* LightModelParameter */
#define GL_LIGHT_MODEL_AMBIENT            0x0B53
#define GL_LIGHT_MODEL_TWO_SIDE           0x0B52

/* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_FLOAT                          0x1406
#define GL_FIXED                          0x140C

/* LogicOp */
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F

/* MaterialFace */
/*      GL_FRONT_AND_BACK */

/* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */

/* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701
#define GL_TEXTURE                        0x1702

/* NormalPointerType */
/*      GL_BYTE */
/*      GL_SHORT */
/*      GL_FLOAT */
/*      GL_FIXED */

/* PixelFormat */
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

/* PixelStoreParameter */
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_ALIGNMENT                 0x0D05

/* PixelType */
/*      GL_UNSIGNED_BYTE */
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_SHORT_5_6_5           0x8363

/* ShadingModel */
#define GL_FLAT                           0x1D00
#define GL_SMOOTH                         0x1D01

/* StencilFunction */
/*      GL_NEVER */
/*      GL_LESS */
/*      GL_EQUAL */
/*      GL_LEQUAL */
/*      GL_GREATER */
/*      GL_NOTEQUAL */
/*      GL_GEQUAL */
/*      GL_ALWAYS */

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
/*      GL_INVERT */

/* StringName */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03

/* TexCoordPointerType */
/*      GL_SHORT */
/*      GL_FLOAT */
/*      GL_FIXED */
/*      GL_BYTE */

/* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
/*      GL_BLEND */
#define GL_ADD                            0x0104
/*      GL_REPLACE */

/* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

/* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

/* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

/* TextureMinFilter */
/*      GL_NEAREST */
/*      GL_LINEAR */
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_GENERATE_MIPMAP                0x8191

/* TextureTarget */
/*      GL_TEXTURE_2D */

/* TextureUnit */
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1

/* TextureWrapMode */
#define GL_REPEAT                         0x2901
#define GL_CLAMP_TO_EDGE                  0x812F

/* PixelInternalFormat */
#define GL_PALETTE4_RGB8_OES              0x8B90
#define GL_PALETTE4_RGBA8_OES             0x8B91
#define GL_PALETTE4_R5_G6_B5_OES          0x8B92
#define GL_PALETTE4_RGBA4_OES             0x8B93
#define GL_PALETTE4_RGB5_A1_OES           0x8B94
#define GL_PALETTE8_RGB8_OES              0x8B95
#define GL_PALETTE8_RGBA8_OES             0x8B96
#define GL_PALETTE8_R5_G6_B5_OES          0x8B97
#define GL_PALETTE8_RGBA4_OES             0x8B98
#define GL_PALETTE8_RGB5_A1_OES           0x8B99

/* VertexPointerType */
/*      GL_SHORT */
/*      GL_FLOAT */
/*      GL_FIXED */
/*      GL_BYTE */

/* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

/* Buffer Objects */
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

#define GL_ARRAY_BUFFER_BINDING           0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING    0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING    0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING     0x8898
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A

#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8

#define GL_BUFFER_SIZE                    0x8764
#define GL_BUFFER_USAGE                   0x8765

/* Texture combine + dot3 */
#define GL_SUBTRACT                       0x84E7
#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_RGB_SCALE                      0x8573
#define GL_ADD_SIGNED                     0x8574
#define GL_INTERPOLATE                    0x8575
#define GL_CONSTANT                       0x8576
#define GL_PRIMARY_COLOR                  0x8577
#define GL_PREVIOUS                       0x8578
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA                 0x8599
#define GL_OPERAND2_ALPHA                 0x859A

#define GL_ALPHA_SCALE                    0x0D1C

#define GL_SRC0_RGB                       0x8580
#define GL_SRC1_RGB                       0x8581
#define GL_SRC2_RGB                       0x8582
#define GL_SRC0_ALPHA                     0x8588
#define GL_SRC1_ALPHA                     0x8589
#define GL_SRC2_ALPHA                     0x858A

#define GL_DOT3_RGB                       0x86AE
#define GL_DOT3_RGBA                      0x86AF

/*****************************************************************************************/
/*                                 OES extension functions                               */
/*****************************************************************************************/

/* OES_draw_texture */
#define GL_TEXTURE_CROP_RECT_OES          0x8B9D

/* OES_matrix_get */
#define GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES   0x898D
#define GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES  0x898E
#define GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES     0x898F

/* OES_matrix_palette */
#define GL_MAX_VERTEX_UNITS_OES           0x86A4
#define GL_MAX_PALETTE_MATRICES_OES       0x8842
#define GL_MATRIX_PALETTE_OES             0x8840
#define GL_MATRIX_INDEX_ARRAY_OES         0x8844
#define GL_WEIGHT_ARRAY_OES               0x86AD
#define GL_CURRENT_PALETTE_MATRIX_OES     0x8843

#define GL_MATRIX_INDEX_ARRAY_SIZE_OES    0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_OES    0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_OES  0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_OES 0x8849
#define GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES 0x8B9E

#define GL_WEIGHT_ARRAY_SIZE_OES          0x86AB
#define GL_WEIGHT_ARRAY_TYPE_OES          0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_OES        0x86AA
#define GL_WEIGHT_ARRAY_POINTER_OES       0x86AC
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_OES 0x889E

/* OES_point_size_array */
#define GL_POINT_SIZE_ARRAY_OES           0x8B9C
#define GL_POINT_SIZE_ARRAY_TYPE_OES      0x898A
#define GL_POINT_SIZE_ARRAY_STRIDE_OES    0x898B
#define GL_POINT_SIZE_ARRAY_POINTER_OES   0x898C
#define GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES 0x8B9F

/* OES_point_sprite */
#define GL_POINT_SPRITE_OES               0x8861
#define GL_COORD_REPLACE_OES              0x8862


/*************************************************************/

GL_API void GL_APIENTRY glAlphaFunc (GLenum func, GLclampf ref) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClearDepthf (GLclampf depth) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClipPlanef (GLenum plane, const GLfloat *equation) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDepthRangef (GLclampf zNear, GLclampf zFar) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFogf (GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFogfv (GLenum pname, const GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetClipPlanef (GLenum pname, GLfloat *equation) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightModelf (GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightModelfv (GLenum pname, const GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLineWidth (GLfloat width) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLoadMatrixf (const GLfloat *m) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMultMatrixf (const GLfloat *m) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glOrthof (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPointParameterf (GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPointParameterfv (GLenum pname, const GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPointSize (GLfloat size) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPolygonOffset (GLfloat factor, GLfloat units) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glSampleCoverage (GLclampf value, GLboolean invert) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

GL_API void GL_APIENTRY glActiveTexture (GLenum texture) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glAlphaFuncx (GLenum func, GLclampx ref) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glBindBuffer (GLenum target, GLuint buffer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glBindTexture (GLenum target, GLuint texture) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glBufferData (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glBufferSubData (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClear (GLbitfield mask) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClearDepthx (GLclampx depth) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClearStencil (GLint s) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClientActiveTexture (GLenum texture) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glClipPlanex (GLenum plane, const GLfixed *equation) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glCullFace (GLenum mode) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDeleteBuffers (GLsizei n, const GLuint *buffers) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDepthFunc (GLenum func) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDepthMask (GLboolean flag) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDepthRangex (GLclampx zNear, GLclampx zFar) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDisable (GLenum cap) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDisableClientState (GLenum array) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glEnable (GLenum cap) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glEnableClientState (GLenum array) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFinish (void) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFlush (void) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFogx (GLenum pname, GLfixed param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFogxv (GLenum pname, const GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFrontFace (GLenum mode) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGenBuffers (GLsizei n, GLuint *buffers) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGenTextures (GLsizei n, GLuint *textures) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetBufferParameteriv (GLenum target, GLenum pname, GLint *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetClipPlanex (GLenum pname, GLfixed eqn[4]) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLenum GL_APIENTRY glGetError (void) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetIntegerv (GLenum pname, GLint *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetPointerv (GLenum pname, void **params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API const GLubyte * GL_APIENTRY glGetString (GLenum name) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetTexEnviv (GLenum env, GLenum pname, GLint *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glGetTexParameterxv (GLenum target, GLenum pname, GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glHint (GLenum target, GLenum mode) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean GL_APIENTRY glIsBuffer (GLuint buffer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API GLboolean GL_APIENTRY glIsTexture (GLuint texture) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightModelx (GLenum pname, GLfixed param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightModelxv (GLenum pname, const GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightx (GLenum light, GLenum pname, GLfixed param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLightxv (GLenum light, GLenum pname, const GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLineWidthx (GLfixed width) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLoadIdentity (void) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLoadMatrixx (const GLfixed *m) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLogicOp (GLenum opcode) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMaterialx (GLenum face, GLenum pname, GLfixed param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMaterialxv (GLenum face, GLenum pname, const GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMatrixMode (GLenum mode) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMultMatrixx (const GLfixed *m) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMultiTexCoord4x (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glNormal3x (GLfixed nx, GLfixed ny, GLfixed nz) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glOrthox (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPixelStorei (GLenum pname, GLint param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPointParameterx (GLenum pname, GLfixed param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPointParameterxv (GLenum pname, const GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPointSizex (GLfixed size) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPolygonOffsetx (GLfixed factor, GLfixed units) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPopMatrix (void) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glPushMatrix (void) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glRotatex (GLfixed angle, GLfixed x, GLfixed y, GLfixed z) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glSampleCoveragex (GLclampx value, GLboolean invert) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glScalex (GLfixed x, GLfixed y, GLfixed z) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glShadeModel (GLenum mode) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glStencilMask (GLuint mask) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexEnvx (GLenum target, GLenum pname, GLfixed param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexEnvxv (GLenum target, GLenum pname, const GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexParameterx (GLenum target, GLenum pname, GLfixed param) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexParameterxv (GLenum target, GLenum pname, const GLfixed *params) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glTranslatex (GLfixed x, GLfixed y, GLfixed z) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

/*****************************************************************************************/
/*                                 OES extension functions                               */
/*****************************************************************************************/
/* OES_matrix_palette */
GL_API void GL_APIENTRY glCurrentPaletteMatrixOES (GLuint matrixpaletteindex) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glLoadPaletteFromModelViewMatrixOES (void) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glMatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glWeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

/* OES_point_size_array */
GL_API void GL_APIENTRY glPointSizePointerOES (GLenum type, GLsizei stride, const GLvoid *pointer) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

/* OES_draw_texture */
GL_API void GL_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

GL_API void GL_APIENTRY glDrawTexsvOES (const GLshort *coords) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDrawTexivOES (const GLint *coords) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDrawTexxvOES (const GLfixed *coords) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

GL_API void GL_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));
GL_API void GL_APIENTRY glDrawTexfvOES (const GLfloat *coords) OPENGLES_DEPRECATED(ios(2.0, 12.0), tvos(9.0, 12.0));

#ifdef __cplusplus
}
#endif

#endif /* ES1_GL_H_GUARD */

// ==========  OpenGLES.framework/Headers/OpenGLESAvailability.h
#ifndef _OpenGLESAvailability_H
#define _OpenGLESAvailability_H

#include <os/availability.h>


#ifdef GLES_SILENCE_DEPRECATION
  #define OPENGLES_DEPRECATED(...)
#else
  #define OPENGLES_DEPRECATED(...) API_DEPRECATED("OpenGLES API deprecated. (Define GLES_SILENCE_DEPRECATION to silence these warnings)", __VA_ARGS__)
#endif

#endif
