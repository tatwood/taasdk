/**
 * @brief     simple state machine implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/statemachine.h>
#include <assert.h>
#include <stdlib.h>

typedef struct taa_statemachine_state_s taa_statemachine_state;

struct taa_statemachine_state_s
{
    taa_statemachine_enter_func enter;
    taa_statemachine_update_func update;
    taa_statemachine_exit_func exit;
    void* userdata;
};

struct taa_statemachine_s
{
    taa_statemachine_state* states;
    taa_statemachine_state* current;
    taa_statemachine_state* next;
    uint32_t numstates;
};

//****************************************************************************
void taa_statemachine_create(
    uint32_t numstates,
    taa_statemachine* sm_out)
{
    taa_statemachine sm;
    taa_statemachine_state* states;
    ptrdiff_t off;
    off = 0;
    // calculate buffer size and pointer offsets
    sm = (taa_statemachine) off;
    off = (ptrdiff_t) (sm + 1);
    states = (taa_statemachine_state*) taa_ALIGN_PTR(off, 8);
    off = (ptrdiff_t) (states + numstates);
    // allocate buffer and set pointers
    off = (ptrdiff_t) calloc(1, off);
    sm = (taa_statemachine) (((ptrdiff_t) sm) + off);
    states = (taa_statemachine_state*) (((ptrdiff_t) states) + off);
    // init struct
    sm->states = states;
    sm->current = NULL;
    sm->next = NULL;
    sm->numstates = numstates;
    // set out param
    *sm_out = sm;
}

//****************************************************************************
void taa_statemachine_destroy(
    taa_statemachine sm)
{
    free(sm);
}

//****************************************************************************
void taa_statemachine_register_state(
    taa_statemachine sm,
    uint32_t stateid,
    void* userdata,
    taa_statemachine_enter_func enter_func,
    taa_statemachine_update_func update_func,
    taa_statemachine_exit_func exit_func)
{
    assert(stateid < sm->numstates);
    if(stateid < sm->numstates)
    {
        taa_statemachine_state* state = sm->states + stateid;
        assert(state->update == NULL);
        assert(update_func != NULL);
        state->userdata = userdata;
        state->enter = enter_func;
        state->update = update_func;
        state->exit = exit_func;
    }
}

//****************************************************************************
void taa_statemachine_transition(
    taa_statemachine sm,
    uint32_t stateid)
{
    assert(stateid < sm->numstates);
    if(stateid < sm->numstates)
    {
        sm->next = sm->states + stateid;
    }
}

//****************************************************************************
void taa_statemachine_update(
    taa_statemachine sm)
{
    taa_statemachine_state* current;
    if(sm->next != NULL)
    {
        taa_statemachine_state* prev = sm->current;
        taa_statemachine_state* next = sm->next;
        sm->current = next;
        sm->next = NULL;
        if(prev != NULL && prev->exit != NULL)
        {
            prev->exit(prev->userdata);
        }
        if(next->enter != NULL)
        {
            int previd = -1;
            if(prev != NULL)
            {
                previd = (int) ((ptrdiff_t) (prev - sm->states));
            }
            next->enter(next->userdata, previd);
        }
    }
    current = sm->current;
    assert(current == NULL || current->update != NULL);
    if(current != NULL && current->update != NULL)
    {
        current->update(sm, current->userdata);
    }
}

//****************************************************************************
void* taa_statemachine_unregister_state(
    taa_statemachine sm,
    uint32_t stateid)
{
    void* userdata = NULL;
    assert(stateid < sm->numstates);
    if(stateid < sm->numstates)
    {
        taa_statemachine_state* state = sm->states + stateid;
        userdata = state->userdata;
        state->userdata = NULL;
        state->enter = NULL;
        state->update = NULL;
        state->exit = NULL;
    }
    return userdata;
}
