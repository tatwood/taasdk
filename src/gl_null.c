/**
 * @brief     rendering implementation for null device
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by render.c
#ifdef taa_GL_C_
#include <taa/gl.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

//****************************************************************************
// index buffer functions

void taa_indexbuffer_bind(
    taa_indexbuffer ib)
{
}

void taa_indexbuffer_create(taa_indexbuffer* ib_out)
{
}

void taa_indexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage)
{
}

void taa_indexbuffer_destroy(
    taa_indexbuffer ib)
{
}

void taa_indexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data)
{
}

//****************************************************************************
// texture2d functions

void taa_texture2d_bind(
    taa_texture2d tex)
{
}

void taa_texture2d_create(taa_texture2d* tex_out)
{
}

void taa_texture2d_setparameter(
    taa_texparam param,
    int value)
{
}

void taa_texture2d_destroy(
    taa_texture2d tex)
{
}

void taa_texture2d_image(
    int mipLevel,
    taa_texformat format,
    int width,
    int height,
    const void* data)
{
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
}

//****************************************************************************
// vertex buffer functions

void taa_vertexbuffer_bind(
    taa_vertexbuffer vb)
{
}

void taa_vertexbuffer_create(taa_vertexbuffer* vb_out)
{
}

void taa_vertexbuffer_data(
    size_t size,
    const void* data,
    taa_bufusage usage)
{
}

void taa_vertexbuffer_destroy(
    taa_vertexbuffer vb)
{
}

void taa_vertexbuffer_subdata(
    size_t offset,
    size_t size,
    const void* data)
{
}

//****************************************************************************

int taa_gl_get_error()
{
    return 0;
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
