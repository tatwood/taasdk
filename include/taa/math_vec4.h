/**
 * @brief     header for inlined 4 dimensional vector functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_VEC4_H_
#define TAA_MATH_VEC4_H_

#include <assert.h>

//****************************************************************************
taa_INLINE static void taa_vec4_add(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout)
{
    vout->x = a->x + b->x;
    vout->y = a->y + b->y;
    vout->z = a->z + b->z;
    vout->w = a->w + b->w;
}

//****************************************************************************
taa_INLINE static void taa_vec4_cross3(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout)
{
    assert(a != vout);
    assert(b != vout);
    vout->x = a->y*b->z-a->z*b->y;
    vout->y = a->z*b->x-a->x*b->z;
    vout->z = a->x*b->y-a->y*b->x;
    vout->w = 0.0f;
}

//****************************************************************************
taa_INLINE static void taa_vec4_divide(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout)
{
    vout->x = a->x / b->x;
    vout->y = a->y / b->y;
    vout->z = a->z / b->z;
    vout->w = a->w / b->w;
}

//****************************************************************************
taa_INLINE static float taa_vec4_dot(
    const taa_vec4* a,
    const taa_vec4* b)
{
    return a->x*b->x + a->y*b->y + a->z*b->z + a->w*b->w;
}

//****************************************************************************
taa_INLINE static void taa_vec4_from_mat44_scale(
    const taa_mat44* a,
    taa_vec4* vout)
{
    vout->x = taa_vec4_length(&a->x);
    vout->y = taa_vec4_length(&a->y);
    vout->z = taa_vec4_length(&a->z);
    vout->w = 1.0f;
}

//****************************************************************************
taa_INLINE static void taa_vec4_from_mat44_translate(
    const taa_mat44* a,
    taa_vec4* vout)
{
    *vout = a->w;
    vout->w = 0.0f;
}

//****************************************************************************
taa_INLINE static float taa_vec4_length(
    const taa_vec4* a)
{
    return sqrtf(a->x*a->x + a->y*a->y + a->z*a->z + a->w*a->w);
}

//****************************************************************************
taa_INLINE static void taa_vec4_mix(
    const taa_vec4* a,
    const taa_vec4* b,
    float x,
    taa_vec4* vout)
{
    vout->x = a->x*(1.0f-x) + b->x*x;
    vout->y = a->y*(1.0f-x) + b->y*x;
    vout->z = a->z*(1.0f-x) + b->z*x;
    vout->w = a->w*(1.0f-x) + b->w*x;
}

//****************************************************************************
taa_INLINE static void taa_vec4_multiply(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout)
{
    vout->x = a->x * b->x;
    vout->y = a->y * b->y;
    vout->z = a->z * b->z;
    vout->w = a->w * b->w;
}

//****************************************************************************
taa_INLINE static void taa_vec4_negate(
    const taa_vec4* a,
    taa_vec4* vout)
{
    vout->x = -a->x;
    vout->y = -a->y;
    vout->z = -a->z;
    vout->w = -a->w;
}

//****************************************************************************
taa_INLINE static void taa_vec4_normalize(
    const taa_vec4* a,
    taa_vec4* vout)
{
    taa_vec4_scale(a, 1.0f/taa_vec4_length(a), vout);
}

//****************************************************************************
taa_INLINE static void taa_vec4_scale(
    const taa_vec4* a,
    float x,
    taa_vec4* vout)
{
    vout->x = a->x * x;
    vout->y = a->y * x;
    vout->z = a->z * x;
    vout->w = a->w * x;
}

//****************************************************************************
taa_INLINE static void taa_vec4_set(
    float x,
    float y,
    float z,
    float w,
    taa_vec4* vout)
{
    vout->x = x;
    vout->y = y;
    vout->z = z;
    vout->w = w;
}

//****************************************************************************
taa_INLINE static void taa_vec4_subtract(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout)
{
    vout->x = a->x - b->x;
    vout->y = a->y - b->y;
    vout->z = a->z - b->z;
    vout->w = a->w - b->w;
}

#endif // TAA_MATH_VEC4_H_
