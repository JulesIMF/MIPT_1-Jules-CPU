/*
Copyright (c) 2020  MIPT

Module Name:
    Handlers
Abstract:
    Реализует хендлеры, не требующие специального написания

Author:
    JulesIMF
Last Edit:
    18.10.2020 18:57
Edit Notes:

*/

#include <math.h>
#include "Core.h"
#include "Execution.h"
#include "IRQ.h"


//
//Дорогой потомок, если ты сейчас читаешь это, знай - это сделано в учебных целях,
//и без острой нужды НИКОГДА так не делай. Злоупотребление макросами - это преступление,
//потому что читать такой код жутко сложно. Простите.
//



#define UNWRAP_CMD(NAME, ARGS, CMD_CODE, CMD_BODY, PUSHED_VALUE_TYPE)   \
void hnd_ ##NAME(Core* core)                                            \
{                                                                       \
    assert(core);                                                       \
    Parameters parameters = get##ARGS(core);                            \
    if(!parameters.isValidParameters) return;                           \
    PUSHED_VALUE_TYPE value = (PUSHED_VALUE_TYPE)0;                     \
    {CMD_BODY;}                                                         \
    if(*(#PUSHED_VALUE_TYPE) != 'Z')                                    \
    {                                                                   \
        if(stackPush(core->coreStack,*(long long*)(&value)) != STACK_OK)\
        {                                                               \
            IRQ_StackError(core);                                       \
            return;                                                     \
        }                                                               \
    }                                                                   \
}

#include "../Commands includes.h"

//#undef UNWRAP_CMD