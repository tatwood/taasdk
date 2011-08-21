/**
 * @brief     target agnostic header for handling mouse input
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_MOUSE_H_
#define TAA_MOUSE_H_

#include "stdint.h"

typedef struct taa_mouse_state_s taa_mouse_state;

struct taa_mouse_state_s
{
    int32_t cursorx;
    int32_t cursory;
    /// left button
    int16_t button1;
    /// middle button
    int16_t button2;
    /// right button
    int16_t button3;
    int16_t padding;
};

#endif // TAA_MOUSE_H_
