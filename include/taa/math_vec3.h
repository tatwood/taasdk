/**
 * @brief     header for inlined 3 dimensional vector functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_VEC3_H_
#define TAA_MATH_VEC3_H_

#include <assert.h>

//****************************************************************************
taa_INLINE void taa_vec3_add(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    vout->x = a->x + b->x;
    vout->y = a->y + b->y;
    vout->z = a->z + b->z;
}

//****************************************************************************
taa_INLINE void taa_vec3_cross(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    assert(a != vout);
    assert(b != vout);
    vout->x = a->y*b->z-a->z*b->y;
    vout->y = a->z*b->x-a->x*b->z;
    vout->z = a->x*b->y-a->y*b->x;
}

//****************************************************************************
taa_INLINE void taa_vec3_divide(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    vout->x = a->x / b->x;
    vout->y = a->y / b->y;
    vout->z = a->z / b->z;
}

//****************************************************************************
taa_INLINE float taa_vec3_dot(
    const taa_vec3* a,
    const taa_vec3* b)
{
    return a->x*b->x + a->y*b->y + a->z*b->z;
}

//****************************************************************************
taa_INLINE void taa_vec3_from_mat33_scale(
    const taa_mat33* a,
    taa_vec3* vout)
{
    vout->x = taa_vec3_length(&a->x);
    vout->y = taa_vec3_length(&a->y);
    vout->z = taa_vec3_length(&a->z);
}

//****************************************************************************
taa_INLINE float taa_vec3_length(
    const taa_vec3* a)
{
    return sqrtf(a->x*a->x + a->y*a->y + a->z*a->z);
}

//****************************************************************************
taa_INLINE void taa_vec3_mix(
    const taa_vec3* a,
    const taa_vec3* b,
    float x,
    taa_vec3* vout)
{
    vout->x = a->x*(1.0f-x) + b->x*x;
    vout->y = a->y*(1.0f-x) + b->y*x;
    vout->z = a->z*(1.0f-x) + b->z*x;
}

//****************************************************************************
taa_INLINE void taa_vec3_multiply(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    vout->x = a->x * b->x;
    vout->y = a->y * b->y;
    vout->z = a->z * b->z;
}

//****************************************************************************
taa_INLINE void taa_vec3_negate(
    const taa_vec3* a,
    taa_vec3* vout)
{
    vout->x = -a->x;
    vout->y = -a->y;
    vout->z = -a->z;
}

//****************************************************************************
taa_INLINE void taa_vec3_normalize(
    const taa_vec3* a,
    taa_vec3* vout)
{
    taa_vec3_scale(a, 1.0f/taa_vec3_length(a), vout);
}

//****************************************************************************
taa_INLINE void taa_vec3_scale(
    const taa_vec3* a,
    float x,
    taa_vec3* vout)
{
    vout->x = a->x * x;
    vout->y = a->y * x;
    vout->z = a->z * x;
}

//****************************************************************************
taa_INLINE void taa_vec3_set(
    float x, 
    float y, 
    float z, 
    taa_vec3* vout)
{
    vout->x = x;
    vout->y = y;
    vout->z = z;
}

//****************************************************************************
taa_INLINE void taa_vec3_subtract(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    vout->x = a->x - b->x;
    vout->y = a->y - b->y;
    vout->z = a->z - b->z;
}

#endif // TAA_MATH_VEC3_H_
