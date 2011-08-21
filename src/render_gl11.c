/**
 * @brief     rendering implementation for OpenGL 1.1
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
// only compile when included by render.c
#ifdef TAA_RENDER_C_

taa_THREADLOCAL taa_indexbuffer taa_tlg_indexbuf;
taa_THREADLOCAL taa_vertexbuffer taa_tlg_vertexbuf;

#endif // TAA_RENDER_C_
