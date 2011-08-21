/**
 * @brief     rendering header for null device
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_RENDER_NULL_H_
#define TAA_RENDER_NULL_H_

#include <assert.h>
#include <stdio.h>
#include <string.h>

struct taa_indexbuffer_s
{
    void* null;
};

struct taa_texture2d_s
{
    void* null;
};

struct taa_vertexbuffer_s
{
    void* null;
};

//****************************************************************************
// index buffer functions

taa_INLINE void taa_indexbuffer_bind(
    taa_indexbuffer ib)
{
}

taa_INLINE void taa_indexbuffer_create(taa_indexbuffer* ibout)
{
    ibout->null = NULL;
}

taa_INLINE void taa_indexbuffer_data(
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
}

taa_INLINE void taa_indexbuffer_destroy(
    taa_indexbuffer ib)
{
}

taa_INLINE void* taa_indexbuffer_map(
    taa_bufaccess access)
{
    return NULL;
}

taa_INLINE void taa_indexbuffer_subdata(
    uint32_t offset,
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
}

taa_INLINE void taa_indexbuffer_unbind()
{
}

taa_INLINE void taa_indexbuffer_unmap()
{
}

//****************************************************************************
// texture2d functions

taa_INLINE void taa_texture2d_bind(
    taa_texture2d tex)
{
}

taa_INLINE void taa_texture2d_create(taa_texture2d* texout)
{
    texout->null = NULL;
}

taa_INLINE void taa_texture2d_setparameters(
    uint32_t maxmiplevel,
    taa_texfilter minfilter,
    taa_texfilter maxfilter,
    taa_texwrap wraps,
    taa_texwrap wrapt)
{
}

taa_INLINE void taa_texture2d_destroy(
    taa_texture2d tex)
{
}

taa_INLINE void taa_texture2d_setimage(
    uint32_t mipLevel,
    taa_texformat format,
    int32_t width,
    int32_t height,
    const void* data)
{
}

taa_INLINE void taa_texture2d_unbind()
{
}

//****************************************************************************
// vertex buffer functions

taa_INLINE void taa_vertexbuffer_bind(
    taa_vertexbuffer vb)
{
}

taa_INLINE void taa_vertexbuffer_create(taa_vertexbuffer* vbout)
{
    vbout->null = NULL;
}

taa_INLINE void taa_vertexbuffer_data(
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
}

taa_INLINE void taa_vertexbuffer_destroy(
    taa_vertexbuffer vb)
{
}

taa_INLINE void* taa_vertexbuffer_map(
    taa_bufaccess access)
{
    return NULL;
}

taa_INLINE void taa_vertexbuffer_subdata(
    uint32_t offset,
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
}

taa_INLINE void taa_vertexbuffer_unbind()
{
}

taa_INLINE void taa_vertexbuffer_unmap()
{
}

//****************************************************************************

taa_INLINE void taa_render_checkerrors()
{
}

taa_INLINE void taa_render_finish()
{
}

#endif // TAA_RENDER_NULL_H_
