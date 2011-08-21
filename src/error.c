/**
 * @brief     error handling implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/error.h>

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static taa_error_callback taa_g_error_callback;

//****************************************************************************
 void taa_error_report(
     const char* file,
     int32_t line,
     const char* format,
     ...)
{
    static char msg[128];
    va_list ap;
    va_start(ap, format);
#ifdef _MSC_FULL_VER
    _vsnprintf(msg, sizeof(msg), format, ap);
#else
    vsnprintf(msg, sizeof(msg), format, ap);
#endif
    va_end(ap);
    msg[sizeof(msg)-1] = '\0';
    if(taa_g_error_callback)
    {
        taa_g_error_callback(file, line, msg);
    }
    else
    {
        printf("%s, line %i: %s", file, line, msg);
        printf("\n");
        assert(0);
        abort();
    }
}

//****************************************************************************
void taa_error_setcallback(
    taa_error_callback cb)
{
    taa_g_error_callback = cb;
}
