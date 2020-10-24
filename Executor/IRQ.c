/*
Copyright (c) 2020  MIPT

Module Name:
    IRQ.c

Abstract:
    Реализует синхронные прерывания

Author:
    JulesIMF

Last Edit:
    16.10.2020 11:45

Edit Notes:

*/
#include "IRQ.h"
#include "Streams.h"
#include "../Common.h"

void IRQ_StackError(Core* core)
{
    assert(core);
    SetColor(LightRed);
    str_printf(core->outputStream, "Interruption: %s. Stop.\n", __FUNCTION__);
    SetColor(White);
    core->isWorking = 0;
}

void IRQ_DivideByZero(Core* core)
{
    assert(core);
    SetColor(LightRed);
    str_printf(core->outputStream, "Interruption: %s. Stop.\n", __FUNCTION__);
    SetColor(White);
    core->isWorking = 0;
}

void IRQ_InvalidCommand(Core* core)
{
    assert(core);
    SetColor(LightRed);
    str_printf(core->outputStream, "Interruption: %s. Stop.\n", __FUNCTION__);
    SetColor(White);
    core->isWorking = 0;
}

void IRQ_InvalidParameters(Core* core)
{
    assert(core);
    SetColor(LightRed);
    str_printf(core->outputStream, "Interruption: %s. Stop.\n", __FUNCTION__);
    SetColor(White);
    core->isWorking = 0;
}

void IRQ_HeapOverflow(Core* core)
{
    assert(core);
    SetColor(LightRed);
    str_printf(core->outputStream, "Interruption: %s. Stop.\n", __FUNCTION__);
    SetColor(White);
    core->isWorking = 0;
}

void IRQ_InvalidIRQ(Core* core)
{
    assert(core);
    SetColor(LightRed);
    str_printf(core->outputStream, "Interruption: %s. Stop.\n", __FUNCTION__);
    SetColor(White);
    core->isWorking = 0;
}
