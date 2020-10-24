/*
Copyright (c) 2020  MIPT

Module Name:
    Stack
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
#include "../Common.h"

//Stack
void hnd_mov(Core* core)
{
    assert(core);
    long long value = 0;
    byte secondByte = getSecondByte(core);
    if (secondByte == WRONG_SECOND_BYTE)
        return;

    //Получим isPtr и AST
    int isPtr_1 = secondByte & (1 << 0);
    int isPtr_2 = (secondByte & (1 << 4)) >> 4;
    int AST_1 = (secondByte & (7 << 1)) >> 1;
    int AST_2 = (secondByte & (7 << 5)) >> 5;

    switch (AST_1)
    {
    case AST_RAX:
    case AST_RBX:
    case AST_RCX:
    case AST_RDX:
        value = core->rx[AST_1];
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        value += GET_ARGUMENT(core, long long);
        if (isPtr_1)
        {
            if (value >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            value = core->ram[value];
        }
        break;


        //Команда "push" без аргумента просто пихает в стек еще одно значение как на вершине
    case AST_STACKTOP:
        if (stackTop(core->coreStack, &value) != STACK_OK)
        {
            IRQ_StackError(core);
            return;
        }
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        value += GET_ARGUMENT(core, long long);

        if (isPtr_1)
        {
            if (value >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            value = core->ram[value];
        }

        break;


    case AST_CONST:
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        value = GET_ARGUMENT(core, long long);
        if (isPtr_1)
        {
            if (value >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            value = core->ram[value];
        }
        break;


    default:
        IRQ_InvalidCommand(core);
        return;
    }

    AST_1 = AST_2;
    isPtr_1 = isPtr_2;

    int addition = 0;

    switch (AST_1)
    {
    case AST_RAX:
    case AST_RBX:
    case AST_RCX:
    case AST_RDX:
        addition += GET_ARGUMENT(core, long long);
        if (isPtr_1)
        {
            if (core->rx[AST_1] + addition >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            core->ram[core->rx[AST_1] + addition] = value;
            return;
        }
        core->rx[AST_1] = value;
        break;



    case AST_STACKTOP:
        if (isPtr_1)
        {
            if (stackTop(core->coreStack, &addition) != STACK_OK)
            {
                IRQ_StackError(core);
                return;
            }
            addition += GET_ARGUMENT(core, long long);
            if(addition >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidParameters(core);
                return;
            }
            core->ram[addition] = value;
            break;
        }

        addition = GET_ARGUMENT(core, long long);
        if (stackPush(core->coreStack, value) != STACK_OK)
        {
            IRQ_StackError(core);
            return;
        }
        
        break;


    case AST_CONST:
        if (isPtr_1)
        {
            addition = GET_ARGUMENT(core, long long);
            if (addition >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            core->ram[addition] = value;
            break;
        }

    default:
        IRQ_InvalidParameters(core);
        return;
    }
}

void hnd_push(Core* core)
{
    assert(core);
    long long value = 0;
    byte secondByte = getSecondByte(core);
    if (secondByte == WRONG_SECOND_BYTE)
        return;

    //Получим isPtr и AST
    int isPtr_1 =  secondByte & (1 << 0);
    int AST_1   = (secondByte & (7 << 1)) >> 1;

    switch (AST_1)
    {
    case AST_RAX:
    case AST_RBX:
    case AST_RCX:
    case AST_RDX:
        value = core->rx[AST_1];
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        value += GET_ARGUMENT(core, long long);
        if (isPtr_1)
        {
            if (value >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            value = core->ram[value];
            return;
        }
        break;


    //Команда "push" без аргумента просто пихает в стек еще одно значение как на вершине
    case AST_STACKTOP:
        if (stackTop(core->coreStack, &value) != STACK_OK)
        {
            IRQ_StackError(core);
            return;
        }
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        value += GET_ARGUMENT(core, long long);

        if (isPtr_1)
        {
            if (value >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            value = core->ram[value];
            return;
        }

        break;


    case AST_CONST:
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        value = GET_ARGUMENT(core, long long);
        break;


    default:
        IRQ_InvalidCommand(core);
        return;
    }

    if (stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_pop(Core* core)
{
    assert(core);
    long long value = 0;
    if (stackTop(core->coreStack, &value) != STACK_OK 
        ||
        stackPop(core->coreStack) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }

    byte secondByte = getSecondByte(core);
    if (secondByte == WRONG_SECOND_BYTE)
        return;

    //Получим isPtr и AST
    int isPtr_1 = secondByte & (1 << 0);
    int AST_1 = (secondByte & (7 << 1)) >> 1;
    if (isTapeEnd(core, sizeof(long long)))
    {
        IRQ_StackError(core);
        return;
    }
    value += GET_ARGUMENT(core, long long);
    switch (AST_1)
    {
    case AST_RAX:
    case AST_RBX:
    case AST_RCX:
    case AST_RDX:

        if (isPtr_1)
        {
            if (core->rx[AST_1] >= core->capacity * sizeof(long long))
            {
                IRQ_InvalidCommand(core);
                return;
            }
            core->ram[core->rx[AST_1]] = value;
            return;
        }
        core->rx[AST_1] = value;
        break;


        
    case AST_STACKTOP:
        break;


    case AST_CONST:
    default:
        IRQ_InvalidCommand(core);
        return;
    }
}

void hnd_pusha(Core* core)
{
    assert(core);
    for (int i = 0; i != 4; i++)
    {
        if (stackPush(core->coreStack, core->rx[i]) != STACK_OK)
        {
            IRQ_StackError(core);
            return;
        }
    }
}

void hnd_pushf(Core* core)
{
    assert(core);
    if (stackPush(core->coreStack, *(long long*)(&core->flags)) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_popa(Core* core)
{
    assert(core);
    for (int i = 0; i != 4; i++)
    {
        if (stackTop(core->coreStack, &core->rx[i]) != STACK_OK 
            ||
            stackPop(core->coreStack) != STACK_OK)
        {
            IRQ_StackError(core);
            return;
        }
    }
}

void hnd_popf(Core* core)
{
    assert(core);
    long long llFlags = 0;
    if (stackTop(core->coreStack, &llFlags) != STACK_OK
        ||
        stackPop(core->coreStack) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
    core->flags = *(short*)(&llFlags);
}
