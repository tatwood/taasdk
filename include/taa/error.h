/**
 * @brief     error handling header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_ERROR_H_
#define TAA_ERROR_H_

#include "system.h"

//****************************************************************************
// macros

#define taa_CHECK_ERROR(cond, msg) \
    if(!(cond)) \
    { \
        taa_error_report(__FILE__, __LINE__, msg); \
    }

#define taa_CHECK_ERROR1(cond, msg, arg) \
    if(!(cond)) \
    { \
        taa_error_report(__FILE__, __LINE__, msg, arg); \
    }

#define taa_CHECK_ERROR2(cond, msg, arg0, arg1) \
    if(!(cond)) \
    { \
        taa_error_report(__FILE__, __LINE__, msg, arg0, arg1); \
    }

//****************************************************************************
// typedefs

typedef void (*taa_error_callback)(
    const char* file,
    int32_t line,
    const char* msg);

//****************************************************************************
// functions

taa_EXTERN_C void taa_error_report(
    const char* file,
    int32_t line,
    const char* format,
    ...);

taa_EXTERN_C void taa_error_setcallback(
    taa_error_callback cb);

#endif // TAA_ERROR_H_
