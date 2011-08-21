/**
 * @brief     simple state machine implementation
 * @author    Thomas Atwood (tatwood.net)
 * @date      2011
 * @copyright unlicense / public domain
 ****************************************************************************/
#include <taa/statemachine.h>
#include <taa/error.h>
#include <stdlib.h>

void taa_statemachine_create(
    uint32_t numstates,
    taa_statemachine* smout)
{
    void* buf = calloc(numstates, sizeof(*smout->states));
    smout->states = (taa_statemachine_state*) buf;
    smout->current = NULL;
    smout->next = NULL;
    smout->numstates = numstates;
}

void taa_statemachine_destroy(
    taa_statemachine* sm)
{
    free(sm->states);
}

void taa_statemachine_transition(
    taa_statemachine* sm,
    uint32_t stateid)
{
    taa_CHECK_ERROR1(stateid < sm->numstates, "Invalid state id %u", stateid);
    sm->next = sm->states + stateid;
}

void taa_statemachine_update(
    taa_statemachine* sm)
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
            next->enter(next->userdata);
        }
    }
    current = sm->current;
    if(current != NULL && current->update != NULL)
    {
        current->update(sm, current->userdata);
    }
}
