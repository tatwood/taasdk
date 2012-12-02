#ifndef taa_LOG_H_
#define taa_LOG_H_

#include "system.h"
#include <stdarg.h>

//****************************************************************************
// macros

#ifndef NDEBUG
#define taa_LOG_DEBUG(format_, ...) \
    taa_log_print( \
        __FILE__, \
        __LINE__, \
        taa_LOG_LEVEL_DEBUG, \
        format_, \
        ##__VA_ARGS__);
#else
#define taa_LOG_DEBUG(format_, ...)
#endif

#define taa_LOG_INFO(format_, ...) \
    taa_log_print( \
        __FILE__, \
        __LINE__, \
        taa_LOG_LEVEL_INFO, \
        format_, \
        ##__VA_ARGS__);

#define taa_LOG_ERROR(format_, ...) \
    taa_log_print( \
        __FILE__, \
        __LINE__, \
        taa_LOG_LEVEL_ERROR, \
        format_, \
        ##__VA_ARGS__);

#define taa_LOG_WARN(format_, ...) \
    taa_log_print( \
        __FILE__, \
        __LINE__, \
        taa_LOG_LEVEL_WARN, \
        format_, \
        ##__VA_ARGS__);

//****************************************************************************
// enums

enum taa_log_level_e
{
    taa_LOG_LEVEL_DEBUG,
    taa_LOG_LEVEL_INFO,
    taa_LOG_LEVEL_WARN,
    taa_LOG_LEVEL_ERROR
};

//****************************************************************************
// typedefs

typedef enum taa_log_level_e taa_log_level;

typedef void (*taa_log_func)(
    const char* file,
    int32_t line,
    taa_log_level level,
    const char * format,
    va_list arg);

//****************************************************************************
// functions

/**
 * default log functionality
 * prints log message to std_out. if log level is error, it raises an assert
 */
taa_SDK_LINKAGE void taa_log_default_func(
    const char* file,
    int32_t line,
    taa_log_level level,
    const char * format,
    va_list arg);

taa_SDK_LINKAGE void taa_log_print(
    const char* file,
    int32_t line,
    taa_log_level level,
    const char* format,
    ...);

taa_SDK_LINKAGE void taa_log_set_func(
    taa_log_func func);


#endif // taa_LOG_H_
