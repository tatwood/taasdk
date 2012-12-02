/**
 * @brief     rendering implementation for OpenGL 1.1
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by render.c
#ifdef taa_GL_C_
#include <taa/gl.h>
#include <taa/log.h>
#include <GL/gl.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

taa_THREADLOCAL taa_indexbuffer taa_tlg_indexbuf;
taa_THREADLOCAL taa_vertexbuffer taa_tlg_vertexbuf;

static const int taa_gl_texfmt[][3] =
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

//****************************************************************************
// index buffer functions

void taa_indexbuffer_bind(
    taa_indexbuffer ib)
{
    taa_tlg_indexbuf = ib;
}

void taa_indexbuffer_create(taa_indexbuffer* ib_out)
{
    void** pp = (void**) malloc(2 * sizeof(*pp));
    pp[0] = NULL;
    pp[1] = 0;
    *ib_out = (taa_indexbuffer) pp;
}

void taa_indexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage)
{
    void** pp = (void**) taa_tlg_indexbuf;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(size > capacity)
    {
        taa_memalign_free(buf);
        buf = taa_memalign(64, size);
        pp[0] = buf;
        pp[1] = (void*) (uintptr_t) size;
    }
    if(data != NULL)
    {
        memcpy(buf, data, size);
    }
}

void taa_indexbuffer_destroy(
    taa_indexbuffer ib)
{
    void* buf = *((void**) ib);
    if(buf != NULL)
    {
        taa_memalign_free(buf);
    }
    free((void**) ib);
}

void taa_indexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data)
{
    size_t total = offset + size;
    void** pp = (void**) taa_tlg_indexbuf;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(total > capacity)
    {
        void* nbuf = taa_memalign(64, total);
        memcpy(nbuf, buf, capacity);
        taa_memalign_free(buf);
        buf = nbuf;
        pp[0] = buf;
        pp[1] = (void*)(uintptr_t) total;
    }
    if(data != NULL)
    {
        memcpy(((uint8_t*) buf) + offset, data, size);
    }
}

//****************************************************************************
// texture2d functions

void taa_texture2d_bind(
    taa_texture2d tex)
{
    glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t) tex);
}

void taa_texture2d_create(taa_texture2d* tex_out)
{
    glGenTextures (1, (GLuint*) tex_out);
}

void taa_texture2d_setparameter(
    taa_texparam param,
    int value)
{
    glTexParameteri(GL_TEXTURE_2D, param, value);
}

void taa_texture2d_destroy(
    taa_texture2d tex)
{
    glDeleteTextures(1, (GLuint*) &tex);
}

void taa_texture2d_image(
    int miplevel,
    taa_texformat format,
    int width,
    int height,
    const void* data)
{
    const int* fmt = taa_gl_texfmt[format];
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
}

void taa_texture2d_subimage(
    int miplevel,
    taa_texformat format,
    int x,
    int y,
    int width,
    int height,
    const void* data)
{
    const int* fmt = taa_gl_texfmt[format];
    glTexSubImage2D(
        GL_TEXTURE_2D,
        miplevel,
        x,
        y,
        width,
        height,
        fmt[1],
        fmt[2],
        data);
}

//****************************************************************************
// vertex buffer functions

void taa_vertexbuffer_bind(
    taa_vertexbuffer vb)
{
    taa_tlg_vertexbuf = vb;
}

void taa_vertexbuffer_create(taa_vertexbuffer* vb_out)
{
    void** pp = (void**) malloc(2 * sizeof(*pp));
    pp[0] = NULL;
    pp[1] = 0;
    *vb_out = (taa_vertexbuffer) pp;
}

void taa_vertexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage)
{
    void** pp = (void**) taa_tlg_vertexbuf;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(size > capacity)
    {
        taa_memalign_free(buf);
        buf = taa_memalign(64, size);
        pp[0] = buf;
        pp[1] = (void*)(uintptr_t) size;
    }
    if(data != NULL)
    {
        memcpy(buf, data, size);
    }
}

void taa_vertexbuffer_destroy(
    taa_vertexbuffer vb)
{
    void* buf = *((void**) vb);
    if(buf != NULL)
    {
        taa_memalign_free(buf);
    }
    free((void**) vb);
}

void taa_vertexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data)
{
    size_t total = offset + size;
    void** pp = (void**) taa_tlg_vertexbuf;
    void* buf = pp[0];
    uintptr_t capacity = (uintptr_t) pp[1];
    if(total > capacity)
    {
        void* nbuf = taa_memalign(64, total);
        memcpy(nbuf, buf, capacity);
        taa_memalign_free(buf);
        buf = nbuf;
        pp[0] = buf;
        pp[1] = (void*)(uintptr_t) total;
    }
    if(data != NULL)
    {
        memcpy(((uint8_t*) buf) + offset, data, size);
    }
}

//****************************************************************************

int taa_gl_get_error()
{
    int err = glGetError();
    if(err != GL_NO_ERROR)
    {
        taa_LOG_DEBUG("GL error: %x", err)
    }
    return (err == GL_NO_ERROR) ? 0 : -1;
}

void taa_gl_finish()
{
    glFinish();
}

void taa_gl_flush()
{
    glFlush();
}

#endif // taa_GL_C_
