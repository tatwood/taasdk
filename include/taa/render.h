/**
 * @brief     target agnostic rendering header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_RENDER_H_
#define TAA_RENDER_H_

#include "window.h"
#include <stdlib.h>

typedef enum taa_bufaccess_e taa_bufaccess;
typedef enum taa_bufusage_e taa_bufusage;
typedef enum taa_texfilter_e taa_texfilter;
typedef enum taa_texwrap_e taa_texwrap;
typedef enum taa_texformat_e taa_texformat;

typedef struct taa_rendercontext_s taa_rendercontext;
typedef struct taa_indexbuffer_s taa_indexbuffer;
typedef struct taa_texture2d_s taa_texture2d;
typedef struct taa_vertexbuffer_s taa_vertexbuffer;

//****************************************************************************

// these enum values match directly with the OpenGL enum spec.
enum taa_bufaccess_e
{
    taa_BUFACCESS_READ_ONLY = 0x88B8,
    taa_BUFACCESS_WRITE_ONLY = 0x88B9,
    taa_BUFACCESS_READ_WRITE = 0x88BA
};

// these enum values match directly with the OpenGL enum spec.
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

// these enum values match directly with the OpenGL enum spec.
enum taa_texfilter_e
{
    taa_TEXFILTER_NEAREST = 0x2600,
    taa_TEXFILTER_LINEAR  = 0x2601,
    taa_TEXFILTER_NEAREST_MIPMAP_NEAREST = 0x2700,
    taa_TEXFILTER_LINEAR_MIPMAP_NEAREST = 0x2701,
    taa_TEXFILTER_NEAREST_MIPMAP_LINEAR = 0x2702,
    taa_TEXFILTER_LINEAR_MIPMAP_LINEAR = 0x2703
};

// these enum values match directly with the OpenGL enum spec.
enum taa_texwrap_e
{
    taa_TEXWRAP_CLAMP  = 0x2900,
    taa_TEXWRAP_REPEAT = 0x2901,
    taa_TEXWRAP_CLAMP_TO_EDGE = 0x812F
};

// this enum does NOT directly map to OpenGL
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
// index buffer functions

taa_INLINE void taa_indexbuffer_bind(
    taa_indexbuffer ib);

taa_INLINE void taa_indexbuffer_create(
    taa_indexbuffer* ibout);

taa_INLINE void taa_indexbuffer_data(
    uint32_t size,
    const void* data,
    taa_bufusage usage);

taa_INLINE void taa_indexbuffer_destroy(
    taa_indexbuffer ib);

taa_INLINE void* taa_indexbuffer_map(
    taa_bufaccess access);

taa_INLINE void taa_indexbuffer_subdata(
    uint32_t offset,
    uint32_t size,
    const void* data,
    taa_bufusage usage);

taa_INLINE void taa_indexbuffer_unbind();

taa_INLINE void taa_indexbuffer_unmap();

//****************************************************************************
// texture2d functions

taa_INLINE void taa_texture2d_bind(
    taa_texture2d tex);

taa_INLINE void taa_texture2d_create(
    taa_texture2d* texout);

taa_INLINE void taa_texture2d_setparameters(
    uint32_t maxmiplevel,
    taa_texfilter minfilter,
    taa_texfilter maxfilter,
    taa_texwrap wraps,
    taa_texwrap wrapt);

taa_INLINE void taa_texture2d_destroy(
    taa_texture2d tex);

taa_INLINE void taa_texture2d_setimage(
    uint32_t mipLevel,
    taa_texformat format,
    int32_t width,
    int32_t height,
    const void* data);

taa_INLINE void taa_texture2d_unbind();

//****************************************************************************
// vertex buffer functions

taa_INLINE void taa_vertexbuffer_bind(
    taa_vertexbuffer vb);

taa_INLINE void taa_vertexbuffer_create(
    taa_vertexbuffer* vbout);

taa_INLINE void taa_vertexbuffer_data(
    uint32_t size,
    const void* data,
    taa_bufusage usage);

taa_INLINE void taa_vertexbuffer_destroy(
    taa_vertexbuffer vb);

taa_INLINE void* taa_vertexbuffer_map(
    taa_bufaccess access);

taa_INLINE void taa_vertexbuffer_subdata(
    uint32_t offset,
    uint32_t size,
    const void* data,
    taa_bufusage usage);

taa_INLINE void taa_vertexbuffer_unbind();

taa_INLINE void taa_vertexbuffer_unmap();

//****************************************************************************
taa_INLINE void taa_render_checkerrors();

taa_INLINE void taa_render_finish();

//****************************************************************************
// render content functions

taa_EXTERN_C void taa_rendercontext_choosevisualinfo(
    taa_window_display* display,
    taa_window_visualinfo* viout);

taa_EXTERN_C void taa_rendercontext_create(
    taa_window* win,
    taa_rendercontext* rcout);

taa_EXTERN_C void taa_rendercontext_createshared(
    taa_rendercontext* rcparent,
    taa_rendercontext* rcout);

taa_EXTERN_C void taa_rendercontext_destroy(
    taa_rendercontext* rc);

taa_EXTERN_C void taa_rendercontext_makecurrent(
    taa_window_display* disp,
    taa_rendercontext* rc);

taa_EXTERN_C void taa_rendercontext_swapbuffers(
    taa_rendercontext* rc);

#if taa_RENDER_GL11
// OpenGL 1.1 render platform
#include <GL/gl.h>
#ifdef WIN32
#include "render_win32.h"
#else
#include "render_x11.h"
#endif
#include "render_gl11.h"
#elif taa_RENDER_NULL
// NULL render platorm
#include "render_null.h"
#else
#error render mode not supported

#endif

#endif // TAA_RENDER_H_
