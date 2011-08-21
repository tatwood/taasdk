/**
 * @brief     rendering header for OpenGL on win32
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_RENDER_WIN32_H_
#define TAA_RENDER_WIN32_H_

typedef struct taa_rendercontext_win32_s taa_rendercontext_win32;

struct taa_rendercontext_win32_s
{
    HWND hwnd;
    HDC hdc;
    HGLRC hglrc;
};

struct taa_rendercontext_s
{
    taa_rendercontext_win32 win32;
};

#endif // TAA_RENDER_WIN32_H_
