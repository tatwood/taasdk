/**
 * @brief     hash function header 
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_HASH_H_
#define taa_HASH_H_

#include "system.h"

// TODO: should this really be inlined?
taa_INLINE static uint32_t taa_hash_pjw(const char* s)
{
    // Based on HashPJW
    // http://www.ddj.com/documents/s=962/ddj9604b/
    enum
    {
        BYTE           = 8,
        NIBBLE         = 4,
        TOTAL_BITS     = ( sizeof(uint32_t) * BYTE ),
        THREE_QUARTERS = ((uint32_t) ((TOTAL_BITS * 3) / 4)),
        HIGH_BITS      = (~((uint32_t)(~0) >> NIBBLE ))
    };

    uint32_t i;
    uint32_t h = 0;
    while(*s != '\0')
    {
        if ((i = (h & HIGH_BITS)) != 0)
        {
            h = (h ^ (i >> THREE_QUARTERS)) & ~HIGH_BITS;
        }
        // Moved this line below the high bit test so
        // that all 32 bits can be utilized in the final hash
        h = (h << NIBBLE) + *s++; 
    }
    return h;
}

#endif // taa_HASH_H_
