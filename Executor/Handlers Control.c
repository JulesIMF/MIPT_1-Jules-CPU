/*
Copyright (c) 2020  MIPT
Module Name:
    Control
Abstract:

Author:
    JulesIMF
Last Edit:
    18.10.2020 18:57
Edit Notes:

*/

#include "Core.h"
#include "Execution.h"
#include "IRQ.h"


//Control
void hnd_jmp(Core* core)
{
    assert(core);
    int newRIP = 0;
    if (isTapeEnd(core, sizeof(int))
        ||
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))
    {
        IRQ_InvalidParameters(core);
        return;
    }

    core->rip = newRIP;
}

void hnd_call(Core* core)
{
    assert(core);
    if (isTapeEnd(core, sizeof(int)))
    {
        IRQ_InvalidParameters(core);
        return;
    }
    
}

void hnd_ret(Core* core)
{
    assert(core);
}

void hnd_int(Core* core)
{
    assert(core);
}

void hnd_iret(Core* core)
{
    assert(core);
}
