/**
 * @brief     linear algbera header for inlined 4x4 matrix functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_MAT44_H_
#define TAA_MATH_MAT44_H_

#include <assert.h>

//****************************************************************************
taa_INLINE static void taa_mat44_add(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* mout)
{
    taa_vec4_add(&a->x, &b->x, &mout->x);
    taa_vec4_add(&a->y, &b->y, &mout->y);
    taa_vec4_add(&a->z, &b->z, &mout->z);
    taa_vec4_add(&a->w, &b->w, &mout->w);
}

//****************************************************************************
taa_INLINE static float taa_mat44_determinant(
    const taa_mat44* a)
{
    return  a->w.x * a->z.y * a->y.z * a->x.w
           -a->z.x * a->w.y * a->y.z * a->x.w
           -a->w.x * a->y.y * a->z.z * a->x.w
           +a->y.x * a->w.y * a->z.z * a->x.w
           +a->z.x * a->y.y * a->w.z * a->x.w
           -a->y.x * a->z.y * a->w.z * a->x.w
           -a->w.x * a->z.y * a->x.z * a->y.w
           +a->z.x * a->w.y * a->x.z * a->y.w
           +a->w.x * a->x.y * a->z.z * a->y.w
           -a->x.x * a->w.y * a->z.z * a->y.w
           -a->z.x * a->x.y * a->w.z * a->y.w
           +a->x.x * a->z.y * a->w.z * a->y.w
           +a->w.x * a->y.y * a->x.z * a->z.w
           -a->y.x * a->w.y * a->x.z * a->z.w
           -a->w.x * a->x.y * a->y.z * a->z.w
           +a->x.x * a->w.y * a->y.z * a->z.w
           +a->y.x * a->x.y * a->w.z * a->z.w
           -a->x.x * a->y.y * a->w.z * a->z.w
           -a->z.x * a->y.y * a->x.z * a->w.w
           +a->y.x * a->z.y * a->x.z * a->w.w
           +a->z.x * a->x.y * a->y.z * a->w.w
           -a->x.x * a->z.y * a->y.z * a->w.w
           -a->y.x * a->x.y * a->z.z * a->w.w
           +a->x.x * a->y.y * a->z.z * a->w.w;
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_mat44* mout)
{
    float c = cosf(rad);
    float s = sinf(rad);
    mout->x.x = axis->x*axis->x*(1.0f-c) + c;
    mout->x.y = axis->y*axis->x*(1.0f-c) + axis->z*s;
    mout->x.z = axis->x*axis->z*(1.0f-c) - axis->y*s;
    mout->x.w = 0.0f;
    mout->y.x = axis->x*axis->y*(1.0f-c) - axis->z*s;
    mout->y.y = axis->y*axis->y*(1.0f-c) + c;
    mout->y.z = axis->y*axis->z*(1.0f-c) + axis->x*s;
    mout->y.w = 0.0f;
    mout->z.x = axis->x*axis->z*(1.0f-c) + axis->y*s;
    mout->z.y = axis->y*axis->z*(1.0f-c) - axis->x*s;
    mout->z.z = axis->z*axis->z*(1.0f-c) + c;
    mout->z.w = 0.0f;
    mout->w.x = 0.0f;
    mout->w.y = 0.0f;
    mout->w.z = 0.0f;
    mout->w.w = 1.0f;
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_mat33(
    const taa_mat33* a,
    taa_mat44* mout)
{
    taa_vec4_set(a->x.x, a->x.y, a->x.z, 0.0f, &mout->x);
    taa_vec4_set(a->y.x, a->y.y, a->y.z, 0.0f, &mout->y);
    taa_vec4_set(a->z.x, a->z.y, a->z.z, 0.0f, &mout->z);
    taa_vec4_set(  0.0f,   0.0f,   0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_pitch(
    float pitch,
    taa_mat44* mout)
{
    /*  1  0  0  0
     *  0  c -s  0
     *  0  s  c  0
     *  0  0  0  1
     */
    float c = cosf(pitch);
    float s = sinf(pitch);
    // columns
    taa_vec4_set(1.0f, 0.0f, 0.0f, 0.0f, &mout->x);
    taa_vec4_set(0.0f,    c,    s, 0.0f, &mout->y);
    taa_vec4_set(0.0f,   -s,    c, 0.0f, &mout->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_quat(
    const taa_quat* q,
    taa_mat44* mout)
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
    taa_vec4_set(1.0f-(yy+zz),        xy+wz,        xz-wy, 0.0f, &mout->x);
    taa_vec4_set(       xy-wz, 1.0f-(xx+zz),        yz+wx, 0.0f, &mout->y);
    taa_vec4_set(       xz+wy,        yz-wx, 1.0f-(xx+yy), 0.0f, &mout->z);
    taa_vec4_set(        0.0f,         0.0f,         0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_roll(
    float roll,
    taa_mat44* mout)
{
    /*  c -s  0  0
     *  s  c  0  0
     *  0  0  1  0
     *  0  0  0  1
     */
    float c = cosf(roll);
    float s = sinf(roll);
    // columns
    taa_vec4_set(   c,    s, 0.0f, 0.0f, &mout->x);
    taa_vec4_set(  -s,    c, 0.0f, 0.0f, &mout->y);
    taa_vec4_set(0.0f, 0.0f, 1.0f, 0.0f, &mout->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_scale(
    const taa_vec4 *scale,
    taa_mat44* mout)
{
    // columns
    taa_vec4_set(scale->x,    0.0f,     0.0f, 0.0f, &mout->x);
    taa_vec4_set(   0.0f, scale->y,     0.0f, 0.0f, &mout->y);
    taa_vec4_set(   0.0f,     0.0f, scale->z, 0.0f, &mout->z);
    taa_vec4_set(   0.0f,     0.0f,     0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_translate(
    const taa_vec4* v,
    taa_mat44* mout)
{
    // columns
    taa_vec4_set( 1.0f, 0.0f, 0.0f, 0.0f, &mout->x);
    taa_vec4_set( 0.0f, 1.0f, 0.0f, 0.0f, &mout->y);
    taa_vec4_set( 0.0f, 0.0f, 1.0f, 0.0f, &mout->z);
    taa_vec4_set( v->x, v->y, v->z, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_from_yaw(
    float yaw,
    taa_mat44* mout)
{
    /*  c  0  s  0
     *  0  1  0  0
     * -s  0  c  0
     *  0  0  0  1
     */
    float c = cosf(yaw);
    float s = sinf(yaw);
    // columns
    taa_vec4_set(    c, 0.0f,   -s, 0.0f, &mout->x);
    taa_vec4_set( 0.0f, 1.0f, 0.0f, 0.0f, &mout->y);
    taa_vec4_set(    s, 0.0f,    c, 0.0f, &mout->z);
    taa_vec4_set( 0.0f, 0.0f, 0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_identity(
    taa_mat44* mout)
{
    // columns
    taa_vec4_set(1.0f, 0.0f, 0.0f, 0.0f, &mout->x);
    taa_vec4_set(0.0f, 1.0f, 0.0f, 0.0f, &mout->y);
    taa_vec4_set(0.0f, 0.0f, 1.0f, 0.0f, &mout->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_inverse(
    const taa_mat44* a,
    taa_mat44* mout)
{
    float d = 1.0f/taa_mat44_determinant(a);
    assert(a != mout);
    mout->x.x = d *
        (a->z.y*a->w.z*a->y.w - a->w.y*a->z.z*a->y.w +
         a->w.y*a->y.z*a->z.w - a->y.y*a->w.z*a->z.w -
         a->z.y*a->y.z*a->w.w + a->y.y*a->z.z*a->w.w);
    mout->x.y = d *
        (a->w.y*a->z.z*a->x.w - a->z.y*a->w.z*a->x.w -
         a->w.y*a->x.z*a->z.w + a->x.y*a->w.z*a->z.w +
         a->z.y*a->x.z*a->w.w - a->x.y*a->z.z*a->w.w);
    mout->x.z = d *
        (a->y.y*a->w.z*a->x.w - a->w.y*a->y.z*a->x.w +
         a->w.y*a->x.z*a->y.w - a->x.y*a->w.z*a->y.w -
         a->y.y*a->x.z*a->w.w + a->x.y*a->y.z*a->w.w);
    mout->x.w = d *
        (a->z.y*a->y.z*a->x.w - a->y.y*a->z.z*a->x.w -
         a->z.y*a->x.z*a->y.w + a->x.y*a->z.z*a->y.w +
         a->y.y*a->x.z*a->z.w - a->x.y*a->y.z*a->z.w);

    mout->y.x = d *
        (a->w.x*a->z.z*a->y.w - a->z.x*a->w.z*a->y.w -
         a->w.x*a->y.z*a->z.w + a->y.x*a->w.z*a->z.w +
         a->z.x*a->y.z*a->w.w - a->y.x*a->z.z*a->w.w);
    mout->y.y = d *
        (a->z.x*a->w.z*a->x.w - a->w.x*a->z.z*a->x.w +
         a->w.x*a->x.z*a->z.w - a->x.x*a->w.z*a->z.w -
         a->z.x*a->x.z*a->w.w + a->x.x*a->z.z*a->w.w);
    mout->y.z =  d *
        (a->w.x*a->y.z*a->x.w - a->y.x*a->w.z*a->x.w -
         a->w.x*a->x.z*a->y.w + a->x.x*a->w.z*a->y.w +
         a->y.x*a->x.z*a->w.w - a->x.x*a->y.z*a->w.w);
    mout->y.w = d *
        (a->y.x*a->z.z*a->x.w - a->z.x*a->y.z*a->x.w +
         a->z.x*a->x.z*a->y.w - a->x.x*a->z.z*a->y.w -
         a->y.x*a->x.z*a->z.w + a->x.x*a->y.z*a->z.w);

    mout->z.x = d *
        (a->z.x*a->w.y*a->y.w - a->w.x*a->z.y*a->y.w +
         a->w.x*a->y.y*a->z.w - a->y.x*a->w.y*a->z.w -
         a->z.x*a->y.y*a->w.w + a->y.x*a->z.y*a->w.w);
    mout->z.y = d *
        (a->w.x*a->z.y*a->x.w - a->z.x*a->w.y*a->x.w -
         a->w.x*a->x.y*a->z.w + a->x.x*a->w.y*a->z.w +
         a->z.x*a->x.y*a->w.w - a->x.x*a->z.y*a->w.w);
    mout->z.z = d *
        (a->y.x*a->w.y*a->x.w - a->w.x*a->y.y*a->x.w +
         a->w.x*a->x.y*a->y.w - a->x.x*a->w.y*a->y.w -
         a->y.x*a->x.y*a->w.w + a->x.x*a->y.y*a->w.w);
    mout->z.w = d *
        (a->z.x*a->y.y*a->x.w - a->y.x*a->z.y*a->x.w -
         a->z.x*a->x.y*a->y.w + a->x.x*a->z.y*a->y.w +
         a->y.x*a->x.y*a->z.w - a->x.x*a->y.y*a->z.w);

    mout->w.x = d *
        (a->w.x*a->z.y*a->y.z - a->z.x*a->w.y*a->y.z -
         a->w.x*a->y.y*a->z.z + a->y.x*a->w.y*a->z.z +
         a->z.x*a->y.y*a->w.z - a->y.x*a->z.y*a->w.z);
    mout->w.y = d *
        (a->z.x*a->w.y*a->x.z - a->w.x*a->z.y*a->x.z +
         a->w.x*a->x.y*a->z.z - a->x.x*a->w.y*a->z.z -
         a->z.x*a->x.y*a->w.z + a->x.x*a->z.y*a->w.z);
    mout->w.z = d *
        (a->w.x*a->y.y*a->x.z - a->y.x*a->w.y*a->x.z -
         a->w.x*a->x.y*a->y.z + a->x.x*a->w.y*a->y.z +
         a->y.x*a->x.y*a->w.z - a->x.x*a->y.y*a->w.z);
    mout->w.w = d *
        (a->y.x*a->z.y*a->x.z - a->z.x*a->y.y*a->x.z +
         a->z.x*a->x.y*a->y.z - a->x.x*a->z.y*a->y.z -
         a->y.x*a->x.y*a->z.z + a->x.x*a->y.y*a->z.z);
}

//****************************************************************************
taa_INLINE static void taa_mat44_lookat(
    const taa_vec4* eye,
    const taa_vec4* target,
    const taa_vec4* up,
    taa_mat44* mout)
{
    taa_vec4 f;
    taa_vec4 s;
    taa_vec4 u;
    // calculate rotation
    taa_vec4_subtract(target, eye, &f);
    f.w = 0.0f;
    taa_vec4_normalize(&f, &f);
    taa_vec4_cross3(&f, up, &s);
    taa_vec4_normalize(&s, &s);
    taa_vec4_cross3(&s, &f, &u);
    taa_vec4_normalize(&u, &u);
    // columns
    taa_vec4_set(s.x,   u.x, -f.x, 0.0f, &mout->x);
    taa_vec4_set(s.y,   u.y, -f.y, 0.0f, &mout->y);
    taa_vec4_set(s.z,   u.z, -f.z, 0.0f, &mout->z);
    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &mout->w);
    // calculate translation
    taa_vec4_set(-eye->x, -eye->y, -eye->z, 1.0f, &f);
    taa_mat44_transform_vec4(mout, &f, &s);
    mout->w = s;
}

//****************************************************************************
taa_INLINE static void taa_mat44_multiply(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* mout)
{
    assert(a != mout);
    assert(b != mout);
    mout->x.x = a->x.x*b->x.x +
                a->y.x*b->x.y +
                a->z.x*b->x.z +
                a->w.x*b->x.w;
    mout->x.y = a->x.y*b->x.x +
                a->y.y*b->x.y +
                a->z.y*b->x.z +
                a->w.y*b->x.w;
    mout->x.z = a->x.z*b->x.x +
                a->y.z*b->x.y +
                a->z.z*b->x.z +
                a->w.z*b->x.w;
    mout->x.w = a->x.w*b->x.x +
                a->y.w*b->x.y +
                a->z.w*b->x.z +
                a->w.w*b->x.w;
    mout->y.x = a->x.x*b->y.x +
                a->y.x*b->y.y +
                a->z.x*b->y.z +
                a->w.x*b->y.w;
    mout->y.y = a->x.y*b->y.x +
                a->y.y*b->y.y +
                a->z.y*b->y.z +
                a->w.y*b->y.w;
    mout->y.z = a->x.z*b->y.x +
                a->y.z*b->y.y +
                a->z.z*b->y.z +
                a->w.z*b->y.w;
    mout->y.w = a->x.w*b->y.x +
                a->y.w*b->y.y +
                a->z.w*b->y.z +
                a->w.w*b->y.w;
    mout->z.x = a->x.x*b->z.x +
                a->y.x*b->z.y +
                a->z.x*b->z.z +
                a->w.x*b->z.w;
    mout->z.y = a->x.y*b->z.x +
                a->y.y*b->z.y +
                a->z.y*b->z.z +
                a->w.y*b->z.w;
    mout->z.z = a->x.z*b->z.x +
                a->y.z*b->z.y +
                a->z.z*b->z.z +
                a->w.z*b->z.w;
    mout->z.w = a->x.w*b->z.x +
                a->y.w*b->z.y +
                a->z.w*b->z.z +
                a->w.w*b->z.w;
    mout->w.x = a->x.x*b->w.x +
                a->y.x*b->w.y +
                a->z.x*b->w.z +
                a->w.x*b->w.w;
    mout->w.y = a->x.y*b->w.x +
                a->y.y*b->w.y +
                a->z.y*b->w.z +
                a->w.y*b->w.w;
    mout->w.z = a->x.z*b->w.x +
                a->y.z*b->w.y +
                a->z.z*b->w.z +
                a->w.z*b->w.w;
    mout->w.w = a->x.w*b->w.x +
                a->y.w*b->w.y +
                a->z.w*b->w.z +
                a->w.w*b->w.w;
}

//****************************************************************************
taa_INLINE static void taa_mat44_orthonormalize(
    const taa_mat44* a,
    taa_mat44* mout)
{
    // col0' = |col0|
    // col1' = |col1 - dot(col0', col1) col0'|
    // col2' = |col2 - dot(col0', col2) col0' - dot(col1', col2) col1'|
    taa_vec4 t;
    taa_vec4 u;
    taa_vec4 v;

    t = a->x;
    t.w = 0.0f;
    taa_vec4_normalize(&t, &mout->x);

    t = a->y;
    t.w = 0.0f;
    taa_vec4_scale(&mout->x, taa_vec4_dot(&mout->x, &t), &v);
    taa_vec4_subtract(&t, &v, &mout->y);
    taa_vec4_normalize(&mout->y, &mout->y);

    t = a->z;
    t.w = 0.0f;
    taa_vec4_scale(&mout->x, taa_vec4_dot(&mout->x, &t), &u);
    taa_vec4_scale(&mout->y, taa_vec4_dot(&mout->y, &t), &v);
    taa_vec4_subtract(&t, &u, &mout->z);
    taa_vec4_subtract(&mout->z, &v, &mout->z);
    taa_vec4_normalize(&mout->z, &mout->z);

    taa_vec4_set(0.0f, 0.0f, 0.0f, 1.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_perspective(
    float fovy,
    float aspect,
    float znear,
    float zfar,
    taa_mat44* mout)
{
    float rad = fovy * 0.5f;
    float cotan = cosf(rad) / sinf(rad);
    float dz = 1.0f/(znear - zfar);
    // columns
    taa_vec4_set(cotan/aspect,  0.0f,               0.0f,  0.0f, &mout->x);
    taa_vec4_set(        0.0f, cotan,               0.0f,  0.0f, &mout->y);
    taa_vec4_set(        0.0f,  0.0f,    (zfar+znear)*dz, -1.0f, &mout->z);
    taa_vec4_set(        0.0f,  0.0f, 2.0f*znear*zfar*dz,  0.0f, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_scale(
    const taa_mat44* a,
    float x,
    taa_mat44* mout)
{
    taa_vec4_scale(&a->x, x, &mout->x);
    taa_vec4_scale(&a->y, x, &mout->y);
    taa_vec4_scale(&a->z, x, &mout->z);
    taa_vec4_scale(&a->w, x, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_subtract(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* mout)
{
    taa_vec4_subtract(&a->x, &b->x, &mout->x);
    taa_vec4_subtract(&a->y, &b->y, &mout->y);
    taa_vec4_subtract(&a->z, &b->z, &mout->z);
    taa_vec4_subtract(&a->w, &b->w, &mout->w);
}

//****************************************************************************
taa_INLINE static void taa_mat44_transform_vec3(
    const taa_mat44* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    assert(((taa_vec3*) &a->x) > vout || ((taa_vec3*) &a->w) < vout);
    assert(b != vout);
    vout->x = a->x.x*b->x + a->y.x*b->y + a->z.x*b->z + a->w.x;
    vout->y = a->x.y*b->x + a->y.y*b->y + a->z.y*b->z + a->w.y;
    vout->z = a->x.z*b->x + a->y.z*b->y + a->z.z*b->z + a->w.z;
}

//****************************************************************************
taa_INLINE static void taa_mat44_transform_vec4(
    const taa_mat44* a,
    const taa_vec4* b,
    taa_vec4* vout)
{
    assert(&a->x > vout || &a->w < vout);
    assert(b != vout);
    vout->x = a->x.x*b->x + a->y.x*b->y + a->z.x*b->z + a->w.x*b->w;
    vout->y = a->x.y*b->x + a->y.y*b->y + a->z.y*b->z + a->w.y*b->w;
    vout->z = a->x.z*b->x + a->y.z*b->y + a->z.z*b->z + a->w.z*b->w;
    vout->w = a->x.w*b->x + a->y.w*b->y + a->z.w*b->z + a->w.w*b->w;
}

//****************************************************************************
taa_INLINE static void taa_mat44_transpose(
    const taa_mat44* a,
    taa_mat44* mout)
{
    assert(a != mout);
    taa_vec4_set(a->x.x, a->y.x, a->z.x, a->w.x, &mout->x);
    taa_vec4_set(a->x.y, a->y.y, a->z.y, a->w.y, &mout->y);
    taa_vec4_set(a->x.z, a->y.z, a->z.z, a->w.z, &mout->z);
    taa_vec4_set(a->x.w, a->y.w, a->z.w, a->w.w, &mout->w);
}

#endif // TAA_MATH_MAT44_H_
