/**
 * @brief     linear algbera header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_H_
#define TAA_MATH_H_

#include "system.h"
#include <math.h>

#define taa_PI (3.14159265f)

typedef struct taa_mat33_s taa_mat33;
typedef struct taa_mat44_s taa_mat44;
typedef struct taa_vec4_s taa_quat;
typedef struct taa_vec2_s taa_vec2;
typedef struct taa_vec3_s taa_vec3;
typedef struct taa_vec4_s taa_vec4;

struct taa_vec2_s
{
    float x, y;
};

struct taa_vec3_s
{
    float x, y, z;
};

struct taa_vec4_s
{
    float x, y, z, w;
};

/**
 * A 3x3 matrix in column major format.
 * <p>Elements are layed out in memory in the following order:</p>
 * <pre>
 * |  0  3  6  |
 * |  1  4  7  |
 * |  2  5  8  |
 * </pre>
 */
struct taa_mat33_s
{
    taa_vec3 x;
    taa_vec3 y;
    taa_vec3 z;
};

/**
 * A 4x4 matrix in column major format.
 * <p>Elements are layed out in memory in the following order:</p>
 * <pre>
 * |  0  4   8  12  |
 * |  1  5   9  13  |
 * |  2  6  10  14  |
 * |  3  7  11  15  |
 * </pre>
 */
struct taa_mat44_s
{
    taa_vec4 x;
    taa_vec4 y;
    taa_vec4 z;
    taa_vec4 w;
};


//****************************************************************************
// mat33 functions

taa_INLINE static void taa_mat33_add(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* mout);

taa_INLINE static float taa_mat33_determinant(
    const taa_mat33* m);

taa_INLINE static void taa_mat33_from_axisangle(
    float rad, 
    const taa_vec3* axis,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_from_mat44(
    const taa_mat44* a,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_from_pitch(
    float pitch,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_from_quat(
    const taa_quat* q,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_from_roll(
    float roll,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_from_scale(
    const taa_vec3* scale,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_from_yaw(
    float yaw,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_identity(
    taa_mat33* mout);

taa_INLINE static void taa_mat33_inverse(
    const taa_mat33* a,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_multiply(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_orthonormalize(
    const taa_mat33* a,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_scale(
    const taa_mat33* a,
    float x,
    taa_mat33* mout);

taa_INLINE static void taa_mat33_subtract(
    const taa_mat33* a,
    const taa_mat33* b,
    taa_mat33* mout);

/** Multiplies a matrix by a column vector
 */
taa_INLINE static void taa_mat33_transform_vec3(
    const taa_mat33* a,
    const taa_vec3* b,
    taa_vec3* vout);

taa_INLINE static void taa_mat33_transpose(
    const taa_mat33* a,
    taa_mat33* mout);

//****************************************************************************
// mat44 functions

taa_INLINE static void taa_mat44_add(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* vout);

taa_INLINE static float taa_mat44_determinant(
    const taa_mat44* a);

taa_INLINE static void taa_mat44_from_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_from_mat33(
    const taa_mat33* a,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_from_pitch(
    float pitch,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_from_quat(
    const taa_quat* q,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_from_roll(
    float roll,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_from_scale(
    const taa_vec4 *scale,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_from_translate(
    const taa_vec4* v,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_from_yaw(
    float yaw,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_identity(
    taa_mat44* mout);

taa_INLINE static void taa_mat44_inverse(
    const taa_mat44* a,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_lookat(
    const taa_vec4* eye,
    const taa_vec4* target,
    const taa_vec4* up,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_multiply(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_orthonormalize(
    const taa_mat44* a,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_perspective(
    float fovy,
    float aspect,
    float znear,
    float zfar,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_scale(
    const taa_mat44* a,
    float x,
    taa_mat44* mout);

taa_INLINE static void taa_mat44_subtract(
    const taa_mat44* a,
    const taa_mat44* b,
    taa_mat44* mout);

/** Multiplies a matrix by a column vector
 *<p>Discards w component</p>
 */
taa_INLINE static void taa_mat44_transform_vec3(
    const taa_mat44* a,
    const taa_vec3* b,
    taa_vec3* vout);

/** Multiplies a matrix by a column vector
 */
taa_INLINE static void taa_mat44_transform_vec4(
    const taa_mat44* a,
    const taa_vec4* b,
    taa_vec4* vout);

taa_INLINE static void taa_mat44_transpose(
    const taa_mat44* a,
    taa_mat44* mout);

//****************************************************************************
// quat functions

taa_INLINE static void taa_quat_add(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* qout);

taa_INLINE static void taa_quat_conjugate(
    const taa_quat* a,
    taa_quat* qout);

taa_INLINE static void taa_quat_from_axisangle(
    float rad,
    const taa_vec4* axis,
    taa_quat* qout);

taa_INLINE static void taa_quat_from_mat33(
    const taa_mat33* m,
    taa_quat* qout);

taa_INLINE static void taa_quat_from_mat44(
    const taa_mat44* m,
    taa_quat* qout);

taa_INLINE static void taa_quat_identity(
    taa_quat* qout);

taa_INLINE static void taa_quat_multiply(
    const taa_quat* a,
    const taa_quat* b,
    taa_quat* qout);

taa_INLINE static void taa_quat_multiply_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_quat* qout);

taa_INLINE static void taa_quat_normalize(
    const taa_quat* a,
    taa_quat* qout);

taa_INLINE static void taa_quat_transform_vec3(
    const taa_quat* a,
    const taa_vec3* b,
    taa_vec3* vout);

taa_INLINE static void taa_quat_transform_vec4(
    const taa_quat* a,
    const taa_vec4* b,
    taa_vec4* vout);

taa_INLINE static void taa_quat_scale(
    const taa_quat* a,
    float x,
    taa_quat* qout);

//****************************************************************************
// scalar functions

taa_INLINE static float taa_clamp(
    float x,
    float min,
    float max);

taa_INLINE static int32_t taa_clampi(
    int32_t x,
    int32_t min,
    int32_t max);

taa_INLINE static float taa_degrees(
    float radians);

taa_INLINE static float taa_max(
    float a,
    float b);

taa_INLINE static int32_t taa_maxi(
    int32_t a,
    int32_t b);

taa_INLINE static float taa_min(
    float a,
    float b);

taa_INLINE static int32_t taa_mini(
    int32_t a,
    int32_t b);

taa_INLINE static float taa_mix(
    float x,
    float y,
    float a);

taa_INLINE static float taa_radians(
    float degrees);

//****************************************************************************
// vec2 functions

taa_INLINE static void taa_vec2_add(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout);

taa_INLINE static float taa_vec2_cross(
    const taa_vec2* a,
    const taa_vec2* b);

taa_INLINE static void taa_vec2_divide(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout);

taa_INLINE static float taa_vec2_dot(
    const taa_vec2* a,
    const taa_vec2* b);

taa_INLINE static float taa_vec2_length(
    const taa_vec2* a);

taa_INLINE static void taa_vec2_mix(
    const taa_vec2* a,
    const taa_vec2* b,
    float x,
    taa_vec2* vout);

taa_INLINE static void taa_vec2_multiply(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout);

taa_INLINE static void taa_vec2_negate(
    const taa_vec2* a,
    taa_vec2* vout);

taa_INLINE static void taa_vec2_normalize(
    const taa_vec2* a,
    taa_vec2* vout);

taa_INLINE static void taa_vec2_scale(
    const taa_vec2* a,
    float x,
    taa_vec2* vout);

taa_INLINE static void taa_vec2_set(
    float x,
    float y,
    taa_vec2* vout);

taa_INLINE static void taa_vec2_subtract(
    const taa_vec2* a,
    const taa_vec2* b,
    taa_vec2* vout);

//****************************************************************************
// vec3 functions

taa_INLINE static void taa_vec3_add(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout);

taa_INLINE static void taa_vec3_cross(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout);

taa_INLINE static void taa_vec3_divide(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout);

taa_INLINE static float taa_vec3_dot(
    const taa_vec3* a,
    const taa_vec3* b);

taa_INLINE static void taa_vec3_from_mat33_scale(
    const taa_mat33* a,
    taa_vec3* vout);

taa_INLINE static float taa_vec3_length(
    const taa_vec3* a);

taa_INLINE static void taa_vec3_mix(
    const taa_vec3* a,
    const taa_vec3* b,
    float x,
    taa_vec3* vout);

taa_INLINE static void taa_vec3_multiply(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout);

taa_INLINE static void taa_vec3_negate(
    const taa_vec3* a,
    taa_vec3* vout);

taa_INLINE static void taa_vec3_normalize(
    const taa_vec3* a,
    taa_vec3* vout);

taa_INLINE static void taa_vec3_scale(
    const taa_vec3* a,
    float x,
    taa_vec3* vout);

taa_INLINE static void taa_vec3_set(
    float x, 
    float y, 
    float z, 
    taa_vec3* vout);

taa_INLINE static void taa_vec3_subtract(
    const taa_vec3* a,
    const taa_vec3* b,
    taa_vec3* vout);


//****************************************************************************
// vec4 functions

taa_INLINE static void taa_vec4_add(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_cross3(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_divide(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout);

taa_INLINE static float taa_vec4_dot(
    const taa_vec4* a,
    const taa_vec4* b);

taa_INLINE static void taa_vec4_from_mat44_scale(
    const taa_mat44* a,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_from_mat44_translate(
    const taa_mat44* a,
    taa_vec4* vout);

taa_INLINE static float taa_vec4_length(
    const taa_vec4* a);

taa_INLINE static void taa_vec4_mix(
    const taa_vec4* a,
    const taa_vec4* b,
    float x,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_multiply(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_negate(
    const taa_vec4* a,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_normalize(
    const taa_vec4* a,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_scale(
    const taa_vec4* a,
    float x,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_set(
    float x,
    float y,
    float z,
    float w,
    taa_vec4* vout);

taa_INLINE static void taa_vec4_subtract(
    const taa_vec4* a,
    const taa_vec4* b,
    taa_vec4* vout);

#include "math_mat33.h"
#include "math_mat44.h"
#include "math_quat.h"
#include "math_scalar.h"
#include "math_vec2.h"
#include "math_vec3.h"
#include "math_vec4.h"

#endif // TAA_MATH_H_
