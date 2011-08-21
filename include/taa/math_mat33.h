/**
 * @brief     linear algbera header for inlined 3x3 matrix functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_MAT33_H_
#define TAA_MATH_MAT33_H_

#include <assert.h>

//****************************************************************************
taa_INLINE void taa_mat33_add(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* mout)
{
    taa_vec3_add(&a->x, &b->x, &mout->x);
    taa_vec3_add(&a->y, &b->y, &mout->y);
    taa_vec3_add(&a->z, &b->z, &mout->z);
}

//****************************************************************************
taa_INLINE float taa_mat33_determinant(
    const taa_mat33* m)
{
    return   m->x.x * m->y.y * m->z.z
           + m->y.x * m->z.y * m->x.z
           + m->z.x * m->x.y * m->y.z
           - m->x.x * m->z.y * m->y.z
           - m->y.x * m->x.y * m->z.z
           - m->z.x * m->y.y * m->x.z;
}

//****************************************************************************
taa_INLINE void taa_mat33_from_axisangle(
    float rad, 
    const taa_vec3* axis,
    taa_mat33* mout)
{
    float c = cosf(rad);
    float s = sinf(rad);
    mout->x.x = axis->x*axis->x*(1.0f-c) + c;
    mout->x.y = axis->y*axis->x*(1.0f-c) + axis->z*s;
    mout->x.z = axis->x*axis->z*(1.0f-c) - axis->y*s;

    mout->y.x = axis->x*axis->y*(1.0f-c) - axis->z*s;
    mout->y.y = axis->y*axis->y*(1.0f-c) + c;
    mout->y.z = axis->y*axis->z*(1.0f-c) + axis->x*s;

    mout->z.x = axis->x*axis->z*(1.0f-c) + axis->y*s;
    mout->z.y = axis->y*axis->z*(1.0f-c) - axis->x*s;
    mout->z.z = axis->z*axis->z*(1.0f-c) + c;
}

//****************************************************************************
taa_INLINE void taa_mat33_from_mat44(
    const taa_mat44* a,
    taa_mat33* mout)
{
    taa_vec3_set(a->x.x, a->x.y, a->x.z, &mout->x);
    taa_vec3_set(a->y.x, a->y.y, a->y.z, &mout->y);
    taa_vec3_set(a->z.x, a->z.y, a->z.z, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_from_pitch(
    float pitch,
    taa_mat33* mout)
{
    /*  1  0  0
     *  0  c -s
     *  0  s  c
     */
    float c = cosf(pitch);
    float s = sinf(pitch);
    // columns
    taa_vec3_set(1.0f, 0.0f, 0.0f, &mout->x);
    taa_vec3_set(0.0f,    c,    s, &mout->y);
    taa_vec3_set(0.0f,   -s,    c, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_from_quat(
    const taa_quat* q,
    taa_mat33* mout)
{
    float xx = 2.0f * q->x * q->x;
    float xy = 2.0f * q->y * q->x;
    float xz = 2.0f * q->z * q->x;
    float yy = 2.0f * q->y * q->y;
    float yz = 2.0f * q->z * q->y;
    float zz = 2.0f * q->z * q->z;
    float wx = 2.0f * q->x * q->w;
    float wy = 2.0f * q->y * q->w;
    float wz = 2.0f * q->z * q->w;
    // columns
    taa_vec3_set(1.0f - (yy+zz),          xy+wz,          xz-wy, &mout->x);
    taa_vec3_set(         xy-wz, 1.0f - (xx+zz),          yz+wx, &mout->y);
    taa_vec3_set(         xz+wy,          yz-wx, 1.0f - (xx+yy), &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_from_roll(
    float roll,
    taa_mat33* mout)
{
    /*  c -s  0
     *  s  c  0
     *  0  0  1
     */
    float c = cosf(roll);
    float s = sinf(roll);
    // columns    
    taa_vec3_set(    c,    s, 0.0f, &mout->x);
    taa_vec3_set(   -s,    c, 0.0f, &mout->y);
    taa_vec3_set( 0.0f, 0.0f, 1.0f, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_from_scale(
    const taa_vec3* scale,
    taa_mat33* mout)
{
    // columns
    taa_vec3_set(scale->x,     0.0f,     0.0f, &mout->x);
    taa_vec3_set(    0.0f, scale->y,     0.0f, &mout->y);
    taa_vec3_set(    0.0f,     0.0f, scale->z, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_from_yaw(
    float yaw,
    taa_mat33* mout)
{
    /*  c  0  s
     *  0  1  0
     * -s  0  c
     */
    float c = cosf(yaw);
    float s = sinf(yaw);
    // columns    
    taa_vec3_set(   c, 0.0f,   -s, &mout->x);
    taa_vec3_set(0.0f, 1.0f, 0.0f, &mout->y);
    taa_vec3_set(   s, 0.0f,    c, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_identity(
    taa_mat33* mout)
{
    // columns
    taa_vec3_set(1.0f, 0.0f, 0.0f, &mout->x);
    taa_vec3_set(0.0f, 1.0f, 0.0f, &mout->y);
    taa_vec3_set(0.0f, 0.0f, 1.0f, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_inverse(
    const taa_mat33* a,
    taa_mat33* mout)
{
    float d = 1.0f/taa_mat33_determinant(a);
    assert(a != mout);
    mout->x.x = (a->y.y*a->z.z - a->y.z*a->z.y)*d;
    mout->x.y = (a->x.z*a->z.y - a->x.y*a->z.z)*d;
    mout->x.z = (a->x.y*a->y.z - a->x.z*a->y.y)*d;
    mout->y.x = (a->y.z*a->z.x - a->y.x*a->z.z)*d;
    mout->y.y = (a->x.x*a->z.z - a->x.z*a->z.x)*d;
    mout->y.z = (a->x.z*a->y.x - a->x.x*a->y.z)*d;
    mout->z.x = (a->y.x*a->z.y - a->y.y*a->z.x)*d;
    mout->z.y = (a->x.y*a->z.x - a->x.x*a->z.y)*d;
    mout->z.z = (a->x.x*a->y.y - a->x.y*a->y.x)*d;
}

//****************************************************************************
taa_INLINE void taa_mat33_multiply(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* mout)
{
    assert(a != mout);
    assert(b != mout);
    mout->x.x = a->x.x*b->x.x + a->y.x*b->x.y + a->z.x*b->x.z;
    mout->x.y = a->x.y*b->x.x + a->y.y*b->x.y + a->z.y*b->x.z;
    mout->x.z = a->x.z*b->x.x + a->y.z*b->x.y + a->z.z*b->x.z;
    mout->y.x = a->x.x*b->y.x + a->y.x*b->y.y + a->z.x*b->y.z;
    mout->y.y = a->x.y*b->y.x + a->y.y*b->y.y + a->z.y*b->y.z;
    mout->y.z = a->x.z*b->y.x + a->y.z*b->y.y + a->z.z*b->y.z;
    mout->z.x = a->x.x*b->z.x + a->y.x*b->z.y + a->z.x*b->z.z;
    mout->z.y = a->x.y*b->z.x + a->y.y*b->z.y + a->z.y*b->z.z;
    mout->z.z = a->x.z*b->z.x + a->y.z*b->z.y + a->z.z*b->z.z;
}

//****************************************************************************
taa_INLINE void taa_mat33_orthonormalize(
    const taa_mat33* a,
    taa_mat33* mout)
{
    // col0' = |col0|
    // col1' = |col1 - dot(col0', col1) col0'|
    // col2' = |col2 - dot(col0', col2) col0' - dot(col1', col2) col1'|
    taa_vec3 u;
    taa_vec3 v;

    taa_vec3_normalize(&a->x, &mout->x);

    taa_vec3_scale(&mout->x, taa_vec3_dot(&mout->x, &a->y), &v);
    taa_vec3_subtract(&a->y, &v, &mout->y);
    taa_vec3_normalize(&mout->y, &mout->y);

    taa_vec3_scale(&mout->x, taa_vec3_dot(&mout->x, &a->z), &u);
    taa_vec3_scale(&mout->y, taa_vec3_dot(&mout->y, &a->z), &v);
    taa_vec3_subtract(&a->z, &u, &mout->z);
    taa_vec3_subtract(&mout->z, &v, &mout->z);
    taa_vec3_normalize(&mout->z, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_scale(
    const taa_mat33* a,
    float x,
    taa_mat33* mout)
{
    taa_vec3_scale(&a->x, x, &mout->x);
    taa_vec3_scale(&a->y, x, &mout->y);
    taa_vec3_scale(&a->z, x, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_subtract(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* mout)
{
    taa_vec3_subtract(&a->x, &b->x, &mout->x);
    taa_vec3_subtract(&a->y, &b->y, &mout->y);
    taa_vec3_subtract(&a->z, &b->z, &mout->z);
}

//****************************************************************************
taa_INLINE void taa_mat33_transform_vec3(
    const taa_mat33* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    assert(&a->x > vout || &a->z < vout);
    assert(b != vout);
    vout->x = a->x.x*b->x + a->y.x*b->y + a->z.x*b->z;
    vout->y = a->x.y*b->x + a->y.y*b->y + a->z.y*b->z;
    vout->z = a->x.z*b->x + a->y.z*b->y + a->z.z*b->z;
}

//****************************************************************************
taa_INLINE void taa_mat33_transpose(
    const taa_mat33* a,
    taa_mat33* mout)
{
    assert(a != mout);
    taa_vec3_set(a->x.x, a->y.x, a->z.x, &mout->x);
    taa_vec3_set(a->x.y, a->y.y, a->z.y, &mout->y);
    taa_vec3_set(a->x.z, a->y.z, a->z.z, &mout->z);
}

#endif // TAA_MATH_MAT33_H_
