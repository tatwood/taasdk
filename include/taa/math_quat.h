/**
 * @brief     header for inlined quaternion functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_QUAT_H_
#define TAA_MATH_QUAT_H_

#include <assert.h>

//****************************************************************************
taa_INLINE static void taa_quat_add(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* qout)
{
    qout->x = a->x + b->x;
    qout->y = a->y + b->y;
    qout->z = a->z + b->z;
    qout->w = a->w + b->w;
}

//****************************************************************************
taa_INLINE static void taa_quat_conjugate(
    const taa_quat* a,
    taa_quat* qout)
{
    qout->x = -a->x;
    qout->y = -a->y;
    qout->z = -a->z;
    qout->w =  a->w;
}

//****************************************************************************
taa_INLINE static void taa_quat_from_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_quat* qout)
{
    float a = rad * 0.5f;
    float s = sinf(a);
    qout->x = axis->x * s;
    qout->y = axis->y * s;
    qout->z = axis->z * s;
    qout->w = cosf(a);
}

//****************************************************************************
taa_INLINE static void taa_quat_from_mat33(
    const taa_mat33* m,
    taa_quat* qout)
{
    float trace = m->x.x + m->y.y + m->z.z;
    if (trace >= 0.0f)
    {
        float s = sqrtf(trace + 1.0f) * 0.5f;
        float t = 0.25f/s;
        qout->x = (m->y.z - m->z.y) * t;
        qout->y = (m->z.x - m->x.z) * t;
        qout->z = (m->x.y - m->y.x) * t;
        qout->w = s;
    }
    else if((m->x.x > m->y.y) && (m->x.x > m->z.z))
    {
        // s=4*x
        float s = sqrtf(1.0f+m->x.x-m->y.y-m->z.z) * 0.5f;
        float t = 0.25f/s;
        qout->x = s;
        qout->y = (m->y.x + m->x.y) * t;
        qout->z = (m->x.z + m->z.x) * t;
        qout->w = (m->y.z - m->z.y) * t;
    }
    else if(m->y.y > m->z.z)
    {
        // s=4*y
        float s = sqrtf(1.0f+m->y.y-m->x.x-m->z.z) * 0.5f;
        float t = 0.25f/s;
        qout->x = (m->y.x + m->x.y) * t;
        qout->y = s;
        qout->z = (m->z.y + m->y.z) * t;
        qout->w = (m->z.x - m->x.z) * t;
    }
    else
    {
        // s=4*z
        float s = sqrtf(1.0f+m->z.z-m->x.x-m->y.y) * 0.5f;
        float t = 0.25f/s;
        qout->x = (m->z.x + m->x.z) * t;
        qout->y = (m->z.y + m->y.z) * t;
        qout->z = s;
        qout->w = (m->x.y - m->y.x) * t;
    }
}

//****************************************************************************
taa_INLINE static void taa_quat_from_mat44(
    const taa_mat44* m,
    taa_quat* qout)
{
    float trace = m->x.x + m->y.y + m->z.z;
    if (trace >= 0.0f)
    {
        float s = sqrtf(trace + 1.0f) * 0.5f;
        float t = 0.25f/s;
        qout->x = (m->y.z - m->z.y) * t;
        qout->y = (m->z.x - m->x.z) * t;
        qout->z = (m->x.y - m->y.x) * t;
        qout->w = s;
    }
    else if((m->x.x > m->y.y) && (m->x.x > m->z.z))
    {
        // s=4*x
        float s = sqrtf(1.0f+m->x.x-m->y.y-m->z.z) * 0.5f;
        float t = 0.25f/s;
        qout->x = s;
        qout->y = (m->y.x + m->x.y) * t;
        qout->z = (m->x.z + m->z.x) * t;
        qout->w = (m->y.z - m->z.y) * t;
    }
    else if(m->y.y > m->z.z)
    {
        // s=4*y
        float s = sqrtf(1.0f+m->y.y-m->x.x-m->z.z) * 0.5f;
        float t = 0.25f/s;
        qout->x = (m->y.x + m->x.y) * t;
        qout->y = s;
        qout->z = (m->z.y + m->y.z) * t;
        qout->w = (m->z.x - m->x.z) * t;
    }
    else
    {
        // s=4*z
        float s = sqrtf(1.0f+m->z.z-m->x.x-m->y.y) * 0.5f;
        float t = 0.25f/s;
        qout->x = (m->z.x + m->x.z) * t;
        qout->y = (m->z.y + m->y.z) * t;
        qout->z = s;
        qout->w = (m->x.y - m->y.x) * t;
    }
}

//****************************************************************************
taa_INLINE static void taa_quat_identity(
    taa_quat* qout)
{
    qout->x = 0.0f;
    qout->y = 0.0f;
    qout->z = 0.0f;
    qout->w = 1.0f;
}

//****************************************************************************
taa_INLINE static void taa_quat_multiply(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* qout)
{
    assert(a != qout);
    assert(b != qout);
    qout->x = a->y*b->z - a->z*b->y + a->w*b->x + a->x*b->w;
    qout->y = a->z*b->x - a->x*b->z + a->w*b->y + a->y*b->w;
    qout->z = a->x*b->y - a->y*b->x + a->w*b->z + a->z*b->w;
    qout->w = a->w*b->w - a->x*b->x - a->y*b->y - a->z*b->z;
}

//****************************************************************************
taa_INLINE static void taa_quat_multiply_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_quat* qout)
{
    assert(a != qout);
    qout->x = a->w * b->x + a->y * b->z - a->z * b->y;
    qout->y = a->w * b->y + a->z * b->x - a->x * b->z;
    qout->z = a->w * b->z + a->x * b->y - a->y * b->x;
    qout->w =-a->x * b->x - a->y * b->y - a->z * b->z;
}

//****************************************************************************
taa_INLINE static void taa_quat_normalize(
    const taa_quat* a,
    taa_quat* qout)
{
    float len = sqrtf(a->x*a->x+a->y*a->y+a->z*a->z+a->w*a->w);
    taa_quat_scale(a, 1.0f/len, qout);
}

//****************************************************************************
taa_INLINE static void taa_quat_transform_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_vec3* vout)
{
    // v' = 2 * cross(q.xyz, (cross(q.xyz, v) + v*q.w)) + v
    const taa_vec3* q = (const taa_vec3*) a;
    taa_vec3 qxv;
    assert(b != vout);
    taa_vec3_cross(q, b, &qxv);
    taa_vec3_scale(b, a->w, vout);
    taa_vec3_add(&qxv, vout, vout);
    taa_vec3_cross(q, vout, &qxv);
    taa_vec3_scale(&qxv, 2.0f, vout);
    taa_vec3_add(vout, b, vout);
}

//****************************************************************************
taa_INLINE static void taa_quat_transform_vec4(
    const taa_quat* a,
    const taa_vec4* b,
    taa_vec4* vout)
{
    // v' = 2 * cross(q.xyz, (cross(q.xyz, v) + v*q.w)) + v
    const taa_vec4* q = (const taa_vec4*) a;
    taa_vec4 qxv;
    assert(b != vout);
    taa_vec4_cross3(q, b, &qxv);
    taa_vec4_scale(b, a->w, vout);
    taa_vec4_add(&qxv, vout, vout);
    taa_vec4_cross3(q, vout, &qxv);
    taa_vec4_scale(&qxv, 2.0f, vout);
    taa_vec4_add(vout, b, vout);
}

//****************************************************************************
taa_INLINE static void taa_quat_scale(
    const taa_quat* a,
    float x,
    taa_quat* qout)
{
    qout->x = a->x * x;
    qout->y = a->y * x;
    qout->z = a->z * x;
    qout->w = a->w * x;
}

#endif // TAA_MATH_QUAT_H_
