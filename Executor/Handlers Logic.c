/*
Copyright (c) 2020  MIPT
Module Name:
    Logic
Abstract:

Author:
    JulesIMF
Last Edit:
    18.10.2020 0:14
Edit Notes:

*/

#include "Core.h"
#include "Execution.h"
#include "IRQ.h"


//Logic
void hnd_and(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    long long value = parameters.first & parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_xor(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    long long value = parameters.first ^ parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_or(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    long long value = parameters.first | parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_test(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    long long value = parameters.first & parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_cmp(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    long long value = parameters.first - parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_shl(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    
    if(parameters.second < 0 || parameters.second > 64)
    {
        IRQ_InvalidParameters(core);
        return WRONG_SECOND_BYTE;
    }

    long long value = parameters.first << parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_shr(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    if (parameters.second < 0 || parameters.second > 64)
    {
        IRQ_InvalidParameters(core);
        return WRONG_SECOND_BYTE;
    }

    long long value = parameters.first >> parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_sti(Core* core)
{
    assert(core);
    core->flags &= (~(FLAG_IF));
}

void hnd_cli(Core* core)
{
    assert(core);
    core->flags |= FLAG_IF;
}

void hnd_neg(Core* core)
{
    assert(core);


    Parameters parameter = getOneParameter(core);
    if (!parameter.isValidParameters)
        return;
    //TODO: flags

    long long value = ~parameter.first;

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}
