/**
 * @brief     header for inlined 2 dimensional vector functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_VEC2_H_
#define TAA_MATH_VEC2_H_

//****************************************************************************
taa_INLINE static void taa_vec2_add(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout)
{
    vout->x = a->x + b->x;
    vout->y = a->y + b->y;
}

//****************************************************************************
taa_INLINE static float taa_vec2_cross(
    const taa_vec2* a,
    const taa_vec2* b)
{
    return a->x*b->y - a->y*b->x;
}

//****************************************************************************
taa_INLINE static void taa_vec2_divide(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout)
{
    vout->x = a->x / b->x;
    vout->y = a->y / b->y;
}

//****************************************************************************
taa_INLINE static float taa_vec2_dot(
    const taa_vec2* a,
    const taa_vec2* b)
{
    return a->x*b->x + a->y*b->y;
}

//****************************************************************************
taa_INLINE static float taa_vec2_length(
    const taa_vec2* a)
{
    return sqrtf(a->x*a->x + a->y*a->y);
}

//****************************************************************************
taa_INLINE static void taa_vec2_mix(
    const taa_vec2* a,
    const taa_vec2* b,
    float x,
    taa_vec2* vout)
{
    vout->x = a->x*(1.0f-x) + b->x*x;
    vout->y = a->y*(1.0f-x) + b->y*x;
}

//****************************************************************************
taa_INLINE static void taa_vec2_multiply(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout)
{
    vout->x = a->x * b->x;
    vout->y = a->y * b->y;
}

//****************************************************************************
taa_INLINE static void taa_vec2_negate(
    const taa_vec2* a,
    taa_vec2* vout)
{
    vout->x = -a->x;
    vout->y = -a->y;
}

//****************************************************************************
taa_INLINE static void taa_vec2_normalize(
    const taa_vec2* a,
    taa_vec2* vout)
{
    taa_vec2_scale(a, 1.0f/taa_vec2_length(a), vout);
}

//****************************************************************************
taa_INLINE static void taa_vec2_scale(
    const taa_vec2* a,
    float x,
    taa_vec2* vout)
{
    vout->x = a->x * x;
    vout->y = a->y * x;
}

//****************************************************************************
taa_INLINE static void taa_vec2_set(
    float x,
    float y,
    taa_vec2* vout)
{
    vout->x = x;
    vout->y = y;
}

//****************************************************************************
taa_INLINE static void taa_vec2_subtract(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout)
{
    vout->x = a->x - b->x;
    vout->y = a->y - b->y;
}

#endif // TAA_MATH_VEC2_H_
