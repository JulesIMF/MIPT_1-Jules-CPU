/*
Copyright (c) 2020  MIPT

Module Name:
    System

Abstract:

Author:
    JulesIMF

Last Edit:
    18.10.2020 0:15

Edit Notes:

*/

#define _CRT_SECURE_NO_WARNINGS
#include "Core.h"
#include "Execution.h"
#include "IRQ.h"
#include "../Common.h"



//System
void hnd_out(Core* core)
{
    assert(core);
    long long value = 0;

    if (stackTop(core->coreStack, &value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }

    byte secondByte = getSecondByte(core);
    if (secondByte == WRONG_SECOND_BYTE)
    {
        IRQ_InvalidParameters(core);
        return;
    }
    SetColor(LightCyan);
    str_printf(core->outputStream, "\t");
    switch (secondByte)
    {
    case OUTF_016LLX:
        str_printf(core->outputStream, "%016llx\n", value);
        return;
    case OUTF_LF:
        str_printf(core->outputStream, "%lf\n", value);
        return;
    case OUTF_LLD:
        str_printf(core->outputStream, "%lld\n", value);
        return;
    }
    SetColor(White);
    
}

void hnd_hlt(Core* core)
{
    assert(core);
    core->isWorking = 0;
}

void hnd_in(Core* core)
{
    assert(core);
    long long value = -1ll;
    int procN = 0;
    static char buffer[256];
    SetColor(Yellow);
    str_printf(core->outputStream, "Enter value: ");
    SetColor(White);

    str_scanf(core->inputStream, "%255s", buffer);

    if (sscanf(buffer, "%lld%n", &value, &procN) > 0 && (!buffer[procN])) goto PUSH;
    if (sscanf(buffer, "%llx%n", &value, &procN) > 0 && (!buffer[procN])) goto PUSH;
    if (sscanf(buffer, "%lf%n",  &value, &procN) > 0 && (!buffer[procN])) goto PUSH;
    SetColor(LightRed);
    str_printf(core->outputStream, "Unknown format. -1 will be pushed into stack.\n");
    SetColor(White);

PUSH:
    if(stackPush(core->coreStack, value) != STACK_OK)
    {
        IRQ_StackError(core);
        return;
    }
}

void hnd_dump(Core* core)
{
    assert(core);
    
    str_printf(core->outputStream,
        "\n-----CORE DUMP BEGIN-----\n"
        "[RAX]          \t%lld\n"
        "[RBX]          \t%lld\n"
        "[RCX]          \t%lld\n"
        "[RDX]          \t%lld\n"
        "[RIP]          \t%d\n"
        "[isWorking]    \t%d\n"
        "[INT]          \t%d\n"
        "[programm.size]\t%d\n"
        "[capacity]     \t%d\n"
        "[size]         \t%d\n\n",
        core->rx[0], core->rx[1],
        core->rx[2], core->rx[3],
        core->rip, core->isWorking,
        core->interruption,
        core->program.size,
        core->coreStack->capacity,
        core->coreStack->size);
 
    str_printf(core->outputStream,
        "[CF]           \t%d\n"
        "[PF]           \t%d\n"
        "[AF]           \t%d\n"
        "[ZF]           \t%d\n"
        "[SF]           \t%d\n"
        "[TF]           \t%d\n"
        "[IF]           \t%d\n"
        "[DF]           \t%d\n"
        "[OF]           \t%d\n"
        "[NT]           \t%d\n"
        "------CORE DUMP END------\n\n",
        !!(core->flags & FLAG_CF),
        !!(core->flags & FLAG_PF),
        !!(core->flags & FLAG_AF),
        !!(core->flags & FLAG_ZF),
        !!(core->flags & FLAG_SF),
        !!(core->flags & FLAG_TF),
        !!(core->flags & FLAG_IF),
        !!(core->flags & FLAG_DF),
        !!(core->flags & FLAG_OF),
        !!(core->flags & FLAG_NT)
    );
}
void hnd_crack(Core* core)
{
    assert(core);
}
void hnd_nop(Core* core)
{
    assert(core);
}

///**
// * UNWRAP_CMD(jle,          TwoParameters, GET_CMD(jle)      , { int newRIP = 0; \
//    if (isTapeEnd(core, sizeof(int))\
//        || \
//        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
//    {\
//        IRQ_InvalidParameters(core); \
//        return; \
//    }\
//        \
//    if((core->flags & FLAG_ZF) || (core->flags & FLAG_SF)) core->rip = newRIP; }, Z_NO_VALUE).
// */
//
//void hnd_jle(Core* core)
//{
//    assert(core);
//    int newRIP = 0; 
//        if (isTapeEnd(core, sizeof(int))
//            || 
//            (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))
//        {
//            IRQ_InvalidParameters(core); 
//            return; 
//        }
//            
//            if ((core->flags & FLAG_ZF) || (core->flags & FLAG_SF)) core->rip = newRIP;
//}
//



