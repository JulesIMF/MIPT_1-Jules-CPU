/*
Copyright (c) 2020  MIPT

Module Name:
    Arithmetics

Abstract:
    
Author:
    JulesIMF

Last Edit:
    18.10.2020 22:20

Edit Notes:

*/

#include "Core.h"
#include "Execution.h"
#include "IRQ.h"
#include <math.h>

//Arithmetic
void hnd_add(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    long long value = parameters.first + parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_sub(Core* core)
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

void hnd_mul(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    long long value = parameters.first * parameters.second;
    //TODO: flags

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_div(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    if (parameters.second == 0)
    {
        IRQ_DivideByZero(core);
        return;
    }

    long long mod = parameters.first % (unsigned long long)parameters.second;

    if (stackPush(core->coreStack, mod) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }

    long long div = parameters.first / parameters.second;

    if (stackPush(core->coreStack, div) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }

    //TODO: flags
}

void hnd_sin(Core* core)
{
    assert(core);
    

    Parameters parameter = getOneParameter(core);
    if (!parameter.isValidParameters)
        return;
    //TODO: flags

    double first = *(double*)(&parameter.first);

    double value = sin(first);

    if (stackPush(core->coreStack, *(long long*)(&value)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_cos(Core* core)
{
    assert(core);


    Parameters parameter = getOneParameter(core);
    if (!parameter.isValidParameters)
        return;
    //TODO: flags

    double first = *(double*)(&parameter.first);

    double value = cos(first);

    if (stackPush(core->coreStack, *(long long*)(&value)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_sqrt(Core* core)
{
    assert(core);


    Parameters parameter = getOneParameter(core);
    if (!parameter.isValidParameters)
        return;
    //TODO: flags

    double first = *(double*)(&parameter.first);

    double value = sqrt(first);

    if (stackPush(core->coreStack, *(long long*)(&value)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_inc(Core* core)
{
    assert(core);
    if (isTapeEnd(core, 1))
        return;

    //Выделяем индекс из второго байта
    int rxIndex = (GET_ARGUMENT(core, byte) & (3<<1)) >> 1;
    core->rx[rxIndex]++;
}

void hnd_dec(Core* core)
{
    assert(core);
    if (isTapeEnd(core, 1))
        return;

    //Выделяем индекс из второго байта
    int rxIndex = (GET_ARGUMENT(core, byte) & (3 << 1)) >> 1;
    core->rx[rxIndex]++;

}

void hnd_neg(Core* core)
{
    assert(core);


    Parameters parameter = getOneParameter(core);
    if (!parameter.isValidParameters)
        return;
    //TODO: flags

    long long value = -parameter.first;

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_fadd(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    double first  = *(double*)(&parameters.first);
    double second = *(double*)(&parameters.second);

    double value = first + second;

    if (stackPush(core->coreStack, *(long long*)(&value)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_fsub(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    double first = *(double*)(&parameters.first);
    double second = *(double*)(&parameters.second);

    double value = first - second;

    if (stackPush(core->coreStack, *(long long*)(&value)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}
void hnd_fmul(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    double first = *(double*)(&parameters.first);
    double second = *(double*)(&parameters.second);

    double value = first * second;

    if (stackPush(core->coreStack, *(long long*)(&value)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_fdiv(Core* core)
{
    assert(core);
    Parameters parameters = getTwoParameters(core);
    if (!parameters.isValidParameters)
        return;

    double first  = *(double*)(&parameters.first);
    double second = *(double*)(&parameters.second);

    double value = first / second;

    if (stackPush(core->coreStack, *(long long*)(&value)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}
