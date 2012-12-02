/**
 * @brief     rendering implementation for OpenGL 2.1
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by render.c
#ifdef taa_GL_C_
#include <taa/gl.h>
#include <taa/log.h>
#include <GL/glew.h>
#include <assert.h>

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
}

void taa_indexbuffer_create(taa_indexbuffer* ib_out)
{
    GLuint name;
    glGenBuffers(1, &name);
    *ib_out = (taa_indexbuffer) name;
}

void taa_indexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void taa_indexbuffer_destroy(
    taa_indexbuffer ib)
{
    GLuint name = ib;
    glDeleteBuffers(1, &name);
}

void taa_indexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data)
{
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
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
    glBindBuffer(GL_ARRAY_BUFFER, vb);
}

void taa_vertexbuffer_create(taa_vertexbuffer* vb_out)
{
    GLuint name;
    glGenBuffers(1, &name);
    *vb_out = (taa_vertexbuffer) name;
}

void taa_vertexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void taa_vertexbuffer_destroy(
    taa_vertexbuffer vb)
{
    GLuint name = vb;
    glDeleteBuffers(1, &name);
}

void taa_vertexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
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
