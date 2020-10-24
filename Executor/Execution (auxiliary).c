/*
Copyright (c) 2020  MIPT

Module Name:
    Execution (auxiliary).с

Abstract:
    Реализует вспомогательный интерфейс исполнения

Author:
    JulesIMF

Last Edit:
    19.10.2020 0:14

Edit Notes:

*/

#include "Execution.h"
#include "../Common.h"

Parameters getTwoParameters(Core* core)
{
    assert(core);
    proceedInterruption(core);
    Parameters parameters;
    parameters.isValidParameters = parameters.first = parameters.second = 0;
    
    byte secondByte = getSecondByte(core);
    if (secondByte == WRONG_SECOND_BYTE)
        return parameters;
    /*
        Argument signature:
            0:      isPtr_1
            1 2 3:  AST_1
            4:      isPtr_2
            5 6 7:  AST_2


        isPtr   - флаг, показывающий, необходимо ли разыменовывать указатель
        AST     - Argument signature type

        Для их получения воспользуемся побитовыми операциями
    */
    int isPtr_1 = secondByte & (1 << 0);
    int isPtr_2 = secondByte & (1 << 4);
    int AST_1 = (secondByte & (7 << 1)) >> 1;
    int AST_2 = (secondByte & (7 << 5)) >> 5;


    /*
        Argument signature type:
            0: rax
            1: rbx
            2: rcx
            3: rdx
            4: stackTop
            5: const
            6:
            7:
    */

    if (AST_1 > 5 || AST_2 > 5)
    {
        IRQ_InvalidCommand(core);
        return parameters;
    }

    switch (AST_1)
    {
    case AST_RAX:
    case AST_RBX:
    case AST_RCX:
    case AST_RDX:
        parameters.first = core->rx[AST_1];
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.first += GET_ARGUMENT(core, long long);
        break;


    case AST_STACKTOP:
        if (stackTop(core->coreStack, &parameters.first) != STACK_OK)
        {
            IRQ_StackError(core);
            return parameters;
        }
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.first += GET_ARGUMENT(core, long long);
        break;


    case AST_CONST:
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return parameters;
        }
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.first += GET_ARGUMENT(core, long long);
        break;
    default:
        IRQ_InvalidCommand(core);
        return parameters;
    }


    switch (AST_2)
    {
    case AST_RAX:
    case AST_RBX:
    case AST_RCX:
    case AST_RDX:
        parameters.second = core->rx[AST_2];
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.second += GET_ARGUMENT(core, long long);
        break;


    case AST_STACKTOP:
        if (stackTop(core->coreStack, &parameters.second) != STACK_OK)
        {
            IRQ_StackError(core);
            return parameters;
        }
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.second += GET_ARGUMENT(core, long long);
        break;


    case AST_CONST:
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return parameters;
        }
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.second += GET_ARGUMENT(core, long long);
        break;
    default:
        IRQ_InvalidCommand(core);
        return parameters;
    }


    if (AST_1 == 4 && AST_2 == 4)
    {
        long long tmp = parameters.first;
        parameters.first = parameters.second;
        parameters.second = tmp;
    }

    if (isPtr_1)
    {
        if (parameters.first >= core->capacity * sizeof(long long))
        {
            IRQ_InvalidCommand(core);
            return parameters;
        }
        parameters.first = core->ram[parameters.first];
    }

    if (isPtr_2)
    {
        if (parameters.second >= core->capacity * sizeof(long long))
        {
            IRQ_InvalidCommand(core);
            return parameters;
        }
        parameters.second = core->ram[parameters.second];
    }

    parameters.isValidParameters = 1;
    return parameters;
}

Parameters getOneParameter(Core* core)
{
    assert(core);
    proceedInterruption(core);
    Parameters parameters;
    parameters.isValidParameters = parameters.first = parameters.second = 0;

    byte secondByte = getSecondByte(core);
    if (secondByte == WRONG_SECOND_BYTE)
        return parameters;
    /*
        Argument signature:
            0:      isPtr_1
            1 2 3:  AST_1
            4:      isPtr_2
            5 6 7:  AST_2


        isPtr   - флаг, показывающий, необходимо ли разыменовывать указатель
        AST     - Argument signature type

        Для их получения воспользуемся побитовыми операциями
    */
    int isPtr_1 = secondByte & (1 << 0);
    int AST_1 = (secondByte & (7 << 1)) >> 1;

    //Пока оперативки нет, никаких указателей
    

    /*
        Argument signature type:
            0: rax
            1: rbx
            2: rcx
            3: rdx
            4: stackTop
            5: const
            6:
            7:
    */

    if (AST_1 > 5)
    {
        IRQ_InvalidCommand(core);
        return parameters;
    }

    switch (AST_1)
    {
    case AST_RAX:
    case AST_RBX:
    case AST_RCX:
    case AST_RDX:
        parameters.first = core->rx[AST_1];
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.first += GET_ARGUMENT(core, long long);
        break;


    case AST_STACKTOP:
        if (stackTop(core->coreStack, &parameters.first) != STACK_OK)
        {
            IRQ_StackError(core);
            return parameters;
        }
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return;
        }
        parameters.first += GET_ARGUMENT(core, long long);
        break;


    case AST_CONST:
        if (isTapeEnd(core, sizeof(long long)))
        {
            IRQ_StackError(core);
            return parameters;
        }
        parameters.first = GET_ARGUMENT(core, long long);
        break;
    default:
        IRQ_InvalidCommand(core);
        return parameters;
    }

    if (isPtr_1)
    {
        if (parameters.first >= core->capacity * sizeof(long long))
        {
            IRQ_InvalidCommand(core);
            return parameters;
        }
        parameters.first = core->ram[parameters.first];
    }
    parameters.isValidParameters = 1;
    return parameters;
}

Parameters getNoParameters(Core* core)
{
    assert(core);
    proceedInterruption(core);
    Parameters parameters;
    parameters.isValidParameters = 1, parameters.first = parameters.second = 0;
    return parameters;
}

int isTapeEnd(Core* core, size_t size)
{
    assert(core);
    return core->rip + size > core->program.size;
}

int programShift(byte* byteCode, size_t byteCodeSize)
{
    //TODO: сейчас тут цирк, потом будет нормальная проверка сигнатуры
    if (byteCodeSize < sizeof(jbcSignature))
        return -1;
    return sizeof(jbcSignature);
}

Program getProgram(byte* byteCode, size_t byteCodeSize)
{
    assert(byteCode);
    int shift = programShift(byteCode, byteCodeSize);
    Program program;
    if (shift == -1)
        program.tape = NULL, program.size = 0;
    else
        program.tape = byteCode + shift, program.size = byteCodeSize - shift;
    
    return program;
}

/*
static void IRQ_StackError(Core* core);         //0
static void IRQ_DivideByZero(Core* core);       //1
static void IRQ_InvalidCommand(Core* core);     //2
static void IRQ_InvalidParameters(Core* core);  //3
static void IRQ_InvalidIRQ(Core* core);         //4
*/
void proceedInterruption(Core* core)
{
    assert(core);
}

byte getSecondByte(Core* core)
{
    assert(core);
    if (isTapeEnd(core, 1))
    {
        {
            IRQ_InvalidParameters(core);
            return WRONG_SECOND_BYTE;
        }
    }

    return GET_ARGUMENT(core, byte);
}
