/**
 * @brief     header for inlined scalar functions
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MATH_SCALAR_H_
#define TAA_MATH_SCALAR_H_

taa_INLINE float taa_clamp(
    float x,
    float min,
    float max)
{
    return (x > min) ? ((x < max) ? x : max) : min;
}

taa_INLINE int32_t taa_clampi(
    int32_t x,
    int32_t min,
    int32_t max)
{
    return (x > min) ? ((x < max) ? x : max) : min;
}

taa_INLINE float taa_degrees(
    float radians)
{
    return radians * (180.0f/taa_PI);
}

taa_INLINE float taa_max(
    float a,
    float b)
{
    return (a > b) ? a : b;
}

taa_INLINE int32_t taa_maxi(
    int32_t a,
    int32_t b)
{
    return (a > b) ? a : b;
}


taa_INLINE float taa_min(
    float a,
    float b)
{
    return (a < b) ? a : b;
}

taa_INLINE int32_t taa_mini(
    int32_t a,
    int32_t b)
{
    return (a < b) ? a : b;
}

taa_INLINE float taa_mix(
    float x,
    float y,
    float a)
{
    return x*(1.0f - a) + y*a;
}

taa_INLINE float taa_radians(
    float degrees)
{
    return degrees * (taa_PI/180.0f);
}

#endif // TAA_MATH_SCALAR_H_
