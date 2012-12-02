/**
 * @brief     target agnostic rendering header
 * @details   This interface is designed based on the assumption that the
 *            rendering implementation itself will vary significantly based on
 *            the target GL version. It does not attempt to abstract the
 *            drawing interface. Instead, it provides abstraction for setup
 *            routines that need to be accessed from outside the render core.
 *            enum values are mapped directly to OpenGL specifications when
 *            available. This file was written with the purpose of allowing
 *            access to the api without adding dependencis on the native GL
 *            header in order to support features such as NULL device support
 *            and multiple GL revision targets. This requires duplicating a
 *            number of OpenGL enum values. When possible, these values are
 *            mapped directly to the spec.
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_GL_H_
#define taa_GL_H_

#include "window.h"

//****************************************************************************
// enums

/**
 * @details these enum values match the OpenGL enum spec directly.
 */
enum taa_bufusage_e
{
    taa_BUFUSAGE_STREAM_DRAW = 0x88E0,
    taa_BUFUSAGE_STREAM_READ = 0x88E1,
    taa_BUFUSAGE_STREAM_COPY = 0x88E2,
    taa_BUFUSAGE_STATIC_DRAW = 0x88E4,
    taa_BUFUSAGE_STATIC_READ = 0x88E5,
    taa_BUFUSAGE_STATIC_COPY = 0x88E6,
    taa_BUFUSAGE_DYNAMIC_DRAW = 0x88E8,
    taa_BUFUSAGE_DYNAMIC_READ = 0x88E9,
    taa_BUFUSAGE_DYNAMIC_COPY = 0x88EA
};

/**
 * @details these enum values match the OpenGL enum spec directly.
 */
enum taa_texparam_e
{
    taa_TEXPARAM_MAG_FILTER = 0x2800,
    taa_TEXPARAM_MIN_FILTER = 0x2801,
    taa_TEXPARAM_WRAP_S = 0x2802,
    taa_TEXPARAM_WRAP_T = 0x2803,
    taa_TEXPARAM_MAX_LEVEL = 0x813D
};

/**
 * @details these enum values match the OpenGL enum spec directly.
 */
enum taa_texfilter_e
{
    taa_TEXFILTER_NEAREST = 0x2600,
    taa_TEXFILTER_LINEAR  = 0x2601,
    taa_TEXFILTER_NEAREST_MIPMAP_NEAREST = 0x2700,
    taa_TEXFILTER_LINEAR_MIPMAP_NEAREST = 0x2701,
    taa_TEXFILTER_NEAREST_MIPMAP_LINEAR = 0x2702,
    taa_TEXFILTER_LINEAR_MIPMAP_LINEAR = 0x2703
};

/**
 * @details these enum values match the OpenGL enum spec directly.
 */
enum taa_texwrap_e
{
    taa_TEXWRAP_CLAMP  = 0x2900,
    taa_TEXWRAP_REPEAT = 0x2901,
    taa_TEXWRAP_CLAMP_TO_EDGE = 0x812F
};

/**
 * @details this enum does NOT directly map to OpenGL
 */
enum taa_texformat_e
{
    taa_TEXFORMAT_ALPHA8,
    taa_TEXFORMAT_LUM8,
    taa_TEXFORMAT_BGR8,
    taa_TEXFORMAT_BGRA8,
    taa_TEXFORMAT_RGB8,
    taa_TEXFORMAT_RGBA8
};

//****************************************************************************
// typedefs

typedef enum taa_bufaccess_e taa_bufaccess;
typedef enum taa_bufusage_e taa_bufusage;
typedef enum taa_texfilter_e taa_texfilter;
typedef enum taa_texparam_e taa_texparam;
typedef enum taa_texwrap_e taa_texwrap;
typedef enum taa_texformat_e taa_texformat;

/**
 * @details For OpenGL 1.1, this is a (void**). To access the contents of the
 * buffer, cast to (void**) and dereference the pointer. For OpenGL 2.1+, this
 * is a uintptr_t containing the GLuint buffer object name.
 */
typedef uintptr_t taa_indexbuffer;

/**
 * @details This is a uintptr_t containing the GLuint texture name.
 */
typedef uintptr_t taa_texture2d;

/**
 * @details For OpenGL 1.1, this is a (void**). To access the contents of the
 * buffer, cast to (void**) and dereference the pointer. For OpenGL 2.1+, this
 * is a uintptr_t containing the GLuint buffer object name.
 */
typedef uintptr_t taa_vertexbuffer;

//****************************************************************************
// index buffer functions

taa_SDK_LINKAGE void taa_indexbuffer_bind(
    taa_indexbuffer ib);

taa_SDK_LINKAGE void taa_indexbuffer_create(
    taa_indexbuffer* ib_out);

taa_SDK_LINKAGE void taa_indexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage);

taa_SDK_LINKAGE void taa_indexbuffer_destroy(
    taa_indexbuffer ib);

taa_SDK_LINKAGE void taa_indexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data);

//****************************************************************************
// texture2d functions

taa_SDK_LINKAGE void taa_texture2d_bind(
    taa_texture2d tex);

taa_SDK_LINKAGE void taa_texture2d_create(
    taa_texture2d* tex_out);

taa_SDK_LINKAGE void taa_texture2d_setparameter(
    taa_texparam param,
    int value);

taa_SDK_LINKAGE void taa_texture2d_destroy(
    taa_texture2d tex);

taa_SDK_LINKAGE void taa_texture2d_image(
    int mipLevel,
    taa_texformat format,
    int width,
    int height,
    const void* data);

taa_SDK_LINKAGE void taa_texture2d_subimage(
    int mipLevel,
    taa_texformat format,
    int x,
    int y,
    int width,
    int height,
    const void* data);

//****************************************************************************
// vertex buffer functions

taa_SDK_LINKAGE void taa_vertexbuffer_bind(
    taa_vertexbuffer vb);

taa_SDK_LINKAGE void taa_vertexbuffer_create(
    taa_vertexbuffer* vb_out);

taa_SDK_LINKAGE void taa_vertexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage);

taa_SDK_LINKAGE void taa_vertexbuffer_destroy(
    taa_vertexbuffer vb);

taa_SDK_LINKAGE void taa_vertexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data);

//****************************************************************************

taa_SDK_LINKAGE int taa_gl_get_error();

taa_SDK_LINKAGE void taa_gl_finish();

taa_SDK_LINKAGE void taa_gl_flush();

#endif // taa_GL_H_
