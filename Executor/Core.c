/*
Copyright (c) 2020  MIPT

Module Name:
    Core.h

Abstract:
    Реализует класс ядра процессора

Author:
    JulesIMF

Last Edit:
    16.10.2020 10:08

Edit Notes:

*/

#include "Core.h"


Core* newCore(size_t capacity)
{
    Core* core = (Core*)calloc(1, sizeof(Core));
    assert(core);
    core->flags = FLAG_IF;
    core->isWorking = 1;
    core->rip = 0;
    core->interruption = -1;
    core->inputStream  = newInputStream();
    core->outputStream = newOutputStream();
    //core->coreStack = stackNew(capacity);
    //core->ram = (long long*)calloc(capacity, sizeof(long long));
    //core->capacity = capacity;
    return core;
}

void  deleteCore(Core* core)
{
    if (core == NULL)
        return;
    stackDelete(core->coreStack);
    deleteInputStream(core->inputStream);
    deleteOutputStream(core->outputStream);
    free(core->ram);
    free(core);
}

int setProgram(Core* core, Program program)
{
    assert(core);
    core->program = program;
    return program.tape == NULL;
}
