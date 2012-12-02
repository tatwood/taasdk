/**
 * @brief     simple state machine header
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#ifndef taa_STATEMACHINE_H_
#define taa_STATEMACHINE_H_

#include "system.h"

//****************************************************************************
// typedefs

typedef struct taa_statemachine_s* taa_statemachine;

typedef void (*taa_statemachine_enter_func)(
    void* userdata,
    int prevstate);

typedef void (*taa_statemachine_exit_func)(
    void* userdata);

typedef void (*taa_statemachine_update_func)(
    taa_statemachine sm,
    void* userdata);

//****************************************************************************
// functions

taa_SDK_LINKAGE void taa_statemachine_create(
    uint32_t numstates,
    taa_statemachine* sm_out);

taa_SDK_LINKAGE void taa_statemachine_destroy(
    taa_statemachine sm);

/**
 * @param sm handle to state machine
 * @param stateid an index into the state array; must be < number of states
 * @param userdata client specified data that will be provided to state funcs
 * @param enter_func called once each time the state is activated
 * @param update_func called each update frame while state is active
 * @param exit_func called once each time the state is deactivated
 */
taa_SDK_LINKAGE void taa_statemachine_register_state(
    taa_statemachine sm,
    uint32_t stateid,
    void* userdata,
    taa_statemachine_enter_func enter_func,
    taa_statemachine_update_func update_func,
    taa_statemachine_exit_func exit_func);

taa_SDK_LINKAGE void taa_statemachine_transition(
    taa_statemachine sm,
    uint32_t stateid);

taa_SDK_LINKAGE void taa_statemachine_update(
    taa_statemachine sm);

/**
 * @return the userdata pointer associated with the specified state id
 */
taa_SDK_LINKAGE void* taa_statemachine_unregister_state(
    taa_statemachine sm,
    uint32_t stateid);

#endif // taa_STATEMACHINE_H_
