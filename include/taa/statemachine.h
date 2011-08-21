/**
 * @brief     simple state machine header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef TAA_STATEMACHINE_H_
#define TAA_STATEMACHINE_H_

#include "system.h"

typedef struct taa_statemachine_state_s taa_statemachine_state;
typedef struct taa_statemachine_s taa_statemachine;

typedef void (*taa_statemachine_enterfunc)(
    void* userdata);

typedef void (*taa_statemachine_exitfunc)(
    void* userdata);

typedef void (*taa_statemachine_updatefunc)(
    taa_statemachine* sm,
    void* userdata);

struct taa_statemachine_state_s
{
    taa_statemachine_enterfunc enter;
    taa_statemachine_updatefunc update;
    taa_statemachine_exitfunc exit;
    void* userdata;
};

struct taa_statemachine_s
{
    taa_statemachine_state* states;
    taa_statemachine_state* current;
    taa_statemachine_state* next;
    uint32_t numstates;
};

taa_EXTERN_C void taa_statemachine_create(
    uint32_t numstates,
    taa_statemachine* smout);

taa_EXTERN_C void taa_statemachine_destroy(
    taa_statemachine* sm);

taa_EXTERN_C void taa_statemachine_transition(
    taa_statemachine* sm,
    uint32_t stateid);

taa_EXTERN_C void taa_statemachine_update(
    taa_statemachine* sm);

#endif // TAA_STATEMACHINE_H_
