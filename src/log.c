#include <taa/log.h>
#include <taa/atomic.h>
#include <taa/spinlock.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static taa_log_func taa_g_log_func;

//****************************************************************************
void taa_log_default_func(
    const char* file,
    int32_t line,
    taa_log_level level,
    const char * format,
    va_list arg)
{
    static int lock = 0;
    const char* lvlstr = "";
    const char* slash;
    // convert level to string
    switch(level)
    {
    case taa_LOG_LEVEL_DEBUG: lvlstr = "DBG"; break;
    case taa_LOG_LEVEL_INFO : lvlstr = "INF"; break;
    case taa_LOG_LEVEL_WARN : lvlstr = "WRN"; break;
    case taa_LOG_LEVEL_ERROR: lvlstr = "ERR"; break;
    }
    // strip dir names off file
    slash = strrchr(file, '/');
    if(slash != NULL)
    {
        file = slash + 1;
    }
    slash = strrchr(file, '\\');
    if(slash != NULL)
    {
        file = slash + 1;
    }
    // primitive lock
    taa_SPINLOCK_LOCK(&lock);
    // print message
    printf("%s,%i %s: ", file, line, lvlstr);
    vprintf(format, arg);
    puts(""); // add newline
    taa_SPINLOCK_UNLOCK(&lock);
    // assert on error
    assert(level != taa_LOG_LEVEL_ERROR);
}

//****************************************************************************
 void taa_log_print(
    const char* file,
    int32_t line,
    taa_log_level level,
    const char* format,
    ...)
{
    va_list arg;
    va_start(arg, format);
    if(taa_g_log_func != NULL)
    {
        // user defined behavior
        taa_g_log_func(file, line, level, format, arg);
    }
    else
    {
        // default behavior
        taa_log_default_func(file, line, level, format, arg);
    }
    va_end(arg);
}

//****************************************************************************
void taa_log_set_func(
    taa_log_func func)
{
    taa_g_log_func = func;
}
