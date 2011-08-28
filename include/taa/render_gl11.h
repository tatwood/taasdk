/**
 * @brief     rendering header for OpenGL 1.1
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_RENDER_GL11_H_
#define TAA_RENDER_GL11_H_

#include <assert.h>
#include <stdio.h>
#include <string.h>

struct taa_indexbuffer_s
{
    void** gl11;
};

struct taa_texture2d_s
{
    GLuint gl11;
};

struct taa_vertexbuffer_s
{
    void** gl11;
};

//****************************************************************************
// index buffer functions

taa_INLINE static void taa_indexbuffer_bind(
    taa_indexbuffer ib)
{
    taa_THREADLOCAL_EXTERN taa_indexbuffer taa_tlg_indexbuf;
    taa_tlg_indexbuf = ib;
}

taa_INLINE static void taa_indexbuffer_create(taa_indexbuffer* ibout)
{
    ibout->gl11 = (void**) calloc(2, sizeof(*ibout->gl11));
}

taa_INLINE static void taa_indexbuffer_data(
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
    taa_THREADLOCAL_EXTERN taa_indexbuffer taa_tlg_indexbuf;
    void** pp = taa_tlg_indexbuf.gl11;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(size > capacity)
    {
        buf = realloc(buf, size);
        pp[0] = buf;
        pp[1] = (void*) size;
    }
    if(data != NULL)
    {
        memcpy(buf, data, size);
    }
}

taa_INLINE static void taa_indexbuffer_destroy(
    taa_indexbuffer ib)
{
    void* buf = ib.gl11[0];
    if(buf != NULL)
    {
        free(buf);
    }
    free(ib.gl11);
}

taa_INLINE static void* taa_indexbuffer_map(
    taa_bufaccess access)
{
    taa_THREADLOCAL_EXTERN taa_indexbuffer taa_tlg_indexbuf;
    return *taa_tlg_indexbuf.gl11;
}

taa_INLINE static void taa_indexbuffer_subdata(
    uint32_t offset,
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
    taa_THREADLOCAL_EXTERN taa_indexbuffer taa_tlg_indexbuf;
    uint32_t total = offset + size;
    void** pp = taa_tlg_indexbuf.gl11;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(total > capacity)
    {
        buf = realloc(buf, total);
        pp[0] = buf;
        pp[1] = (void*) total;
    }
    if(data != NULL)
    {
        memcpy(((uint8_t*) buf) + offset, data, size);
    }
}

taa_INLINE static void taa_indexbuffer_unbind()
{
    taa_THREADLOCAL_EXTERN taa_indexbuffer taa_tlg_indexbuf;
    taa_tlg_indexbuf.gl11 = NULL;
}

taa_INLINE static void taa_indexbuffer_unmap()
{
}

//****************************************************************************
// texture2d functions

taa_INLINE static void taa_texture2d_bind(
    taa_texture2d tex)
{
    glBindTexture(GL_TEXTURE_2D, tex.gl11);
}

taa_INLINE static void taa_texture2d_create(taa_texture2d* texout)
{
    glGenTextures (1, &texout->gl11);
}

taa_INLINE static void taa_texture2d_setparameters(
    uint32_t maxmiplevel,
    taa_texfilter minfilter,
    taa_texfilter maxfilter,
    taa_texwrap wraps,
    taa_texwrap wrapt)
{
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, maxmiplevel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxfilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraps);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapt);
    taa_render_checkerrors();
}

taa_INLINE static void taa_texture2d_destroy(
    taa_texture2d tex)
{
    glDeleteTextures(1, &tex.gl11);
}

taa_INLINE static void taa_texture2d_setimage(
    uint32_t miplevel,
    taa_texformat format,
    int32_t width,
    int32_t height,
    const void* data)
{
    static const int fmttable[][3] =
    {
        // taa_TEXFORMAT_ALPHA8
        { GL_ALPHA8    , GL_ALPHA    , GL_UNSIGNED_BYTE },
        // taa_TEXTURE_LUM8
        { GL_LUMINANCE8, GL_LUMINANCE, GL_UNSIGNED_BYTE },
        // taa_TEXTURE_BGR8
        { GL_RGB8      , GL_BGR_EXT  , GL_UNSIGNED_BYTE },
        // taa_TEXTURE_BGRA8
        { GL_RGBA8     , GL_BGRA_EXT , GL_UNSIGNED_BYTE },
        // taa_TEXTURE_RGB8
        { GL_RGB8      , GL_RGB      , GL_UNSIGNED_BYTE },
        // taa_TEXTURE_RGBA8
        { GL_RGBA8     , GL_RGBA     , GL_UNSIGNED_BYTE },
    };
    const int* fmt = fmttable[format];
    taa_render_checkerrors();
    glTexImage2D(
        GL_TEXTURE_2D,
        miplevel,
        fmt[0],
        width,
        height,
        0,
        fmt[1],
        fmt[2],
        data);
    taa_render_checkerrors();
}

taa_INLINE static void taa_texture2d_unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

//****************************************************************************
// vertex buffer functions

taa_INLINE static void taa_vertexbuffer_bind(
    taa_vertexbuffer vb)
{
    taa_THREADLOCAL_EXTERN taa_vertexbuffer taa_tlg_vertexbuf;
    taa_tlg_vertexbuf = vb;
}

taa_INLINE static void taa_vertexbuffer_create(taa_vertexbuffer* vbout)
{
    vbout->gl11 = (void**) calloc(2, sizeof(*vbout->gl11));
}

taa_INLINE static void taa_vertexbuffer_data(
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
    taa_THREADLOCAL_EXTERN taa_vertexbuffer taa_tlg_vertexbuf;
    void** pp = taa_tlg_vertexbuf.gl11;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(size > capacity)
    {
        buf = realloc(buf, size);
        pp[0] = buf;
        pp[1] = (void*) size;
    }
    if(data != NULL)
    {
        memcpy(buf, data, size);
    }
}

taa_INLINE static void taa_vertexbuffer_destroy(
    taa_vertexbuffer vb)
{
    void* buf = vb.gl11[0];
    if(buf != NULL)
    {
        free(buf);
    }
    free(vb.gl11);
}

taa_INLINE static void* taa_vertexbuffer_map(
    taa_bufaccess access)
{
    taa_THREADLOCAL_EXTERN taa_vertexbuffer taa_tlg_vertexbuf;
    return *taa_tlg_vertexbuf.gl11;
}

taa_INLINE static void taa_vertexbuffer_subdata(
    uint32_t offset,
    uint32_t size,
    const void* data,
    taa_bufusage usage)
{
    taa_THREADLOCAL_EXTERN taa_vertexbuffer taa_tlg_vertexbuf;
    uint32_t total = offset + size;
    void** pp = taa_tlg_vertexbuf.gl11;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(total > capacity)
    {
        buf = realloc(buf, total);
        pp[0] = buf;
        pp[1] = (void*) total;
    }
    if(data != NULL)
    {
        memcpy(((uint8_t*) buf) + offset, data, size);
    }
}

taa_INLINE static void taa_vertexbuffer_unbind()
{
    taa_THREADLOCAL_EXTERN taa_vertexbuffer taa_tlg_vertexbuf;
    taa_tlg_vertexbuf.gl11 = NULL;
}


taa_INLINE static void taa_vertexbuffer_unmap()
{
}

//****************************************************************************

taa_INLINE static void taa_render_checkerrors()
{
#if 1 //ifndef NDEBUG
    GLuint errCode = glGetError();
    if(errCode != GL_NO_ERROR)
    {
        printf("GL Error: %x\n", errCode);
        assert(0);
    }
#endif
}

taa_INLINE static void taa_render_finish()
{
    glFinish();
}


#endif // TAA_RENDER_GL11_H_
