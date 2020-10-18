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

#include "Core.h"
#include "Execution.h"
#include "IRQ.h"

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

    str_printf(core->outputStream, "%016llx\n", value);
}

void hnd_hlt(Core* core)
{
    assert(core);
    core->isWorking = 0;
}

void hnd_in(Core* core)
{
    assert(core);
    long long value = 0;
    str_printf(core->outputStream, "Enter value: ");
    str_scanf(core->inputStream, "%lld", &value);
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
void hnd_crack(Core* core);
void hnd_nop(Core* core)
{
    assert(core);
}
