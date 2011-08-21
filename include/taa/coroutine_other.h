/**
 * @brief     coroutine managment header for platforms without fiber support
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_COROUTINE_OTHER_H_
#define TAA_COROUTINE_OTHER_H_

struct taa_coroutine_s
{
    void* other;
};

#endif // TAA_COROUTINE_OTHER_H_
