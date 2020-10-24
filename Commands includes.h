/*
Copyright (c) 2020  MIPT

Module Name:
    Handlers
Abstract:
    Описывает хендлеры, не требующие специального написания

Author:
    JulesIMF
Last Edit:
    20.10.2020 19:57
Edit Notes:

*/

#include "Common.h"

#define GET_CMD(NAME) cmd_##NAME

typedef long long Z_NO_VALUE;
enum FLAGS_UPDATE{FLAGS_NO_UPDATE, FLAGS_UPDATE};

UNWRAP_CMD(add, TwoParameters, GET_CMD(add), { value = parameters.first + parameters.second; }, long long)
UNWRAP_CMD(sub, TwoParameters, GET_CMD(sub), { value = parameters.first - parameters.second; }, long long)
UNWRAP_CMD(mul, TwoParameters, GET_CMD(mul), { value = parameters.first * parameters.second; }, long long)
UNWRAP_CMD(div, TwoParameters, GET_CMD(div), { value = parameters.first / parameters.second; }, long long)
UNWRAP_CMD(sin,  OneParameter, GET_CMD(sin), { value = sin(*(double*)(&parameters.first)); }, double)
UNWRAP_CMD(cos,  OneParameter, GET_CMD(cos), { value = cos(*(double*)(&parameters.first)); }, double)
UNWRAP_CMD(sqrt, OneParameter, GET_CMD(sqrt), { value = sqrt(*(double*)(&parameters.first)); }, double)
UNWRAP_CMD(inc,  NoParameters, GET_CMD(inc), { if (isTapeEnd(core, 1)) return; int rxIndex = (GET_ARGUMENT(core, byte) & 3); core->rx[rxIndex]++; }, Z_NO_VALUE)
UNWRAP_CMD(dec,  NoParameters, GET_CMD(dec), { if (isTapeEnd(core, 1)) return; int rxIndex = (GET_ARGUMENT(core, byte) & 3); core->rx[rxIndex]--; }, Z_NO_VALUE)
UNWRAP_CMD(neg,  OneParameter, GET_CMD(neg), { value = -parameters.first; }, long long)
UNWRAP_CMD(fadd, TwoParameters, GET_CMD(fadd), { value = (*(double*)(&parameters.first) + *(double*)(&parameters.second)); }, double)
UNWRAP_CMD(fsub, TwoParameters, GET_CMD(fsub), { value = (*(double*)(&parameters.first) - *(double*)(&parameters.second)); }, double)
UNWRAP_CMD(fmul, TwoParameters, GET_CMD(fmul), { value = (*(double*)(&parameters.first) * *(double*)(&parameters.second)); }, double)
UNWRAP_CMD(fdiv, TwoParameters, GET_CMD(fdiv), { value = (*(double*)(&parameters.first) / *(double*)(&parameters.second)); }, double)




UNWRAP_CMD(iret, NoParameters, GET_CMD(iret), {}, Z_NO_VALUE)
UNWRAP_CMD(int, NoParameters, GET_CMD(int), {}, Z_NO_VALUE)


#ifndef _JCPU_NOJMP
UNWRAP_CMD(jmp, NoParameters, GET_CMD(jmp), { int newRIP = 0; \
    if (isTapeEnd(core, sizeof(int))\
        || \
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
        \
    core->rip = newRIP; }, Z_NO_VALUE)

    UNWRAP_CMD(call, NoParameters, GET_CMD(call), { int newRIP = 0; \
        if (isTapeEnd(core, sizeof(int))\
            || \
            (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
        {\
            IRQ_InvalidParameters(core); \
            return; \
        }\
            \
            if (stackPush(core->coreStack, core->rip) != STACK_OK)\
            {\
                IRQ_StackError(core); \
                return; \
            } core->rip = newRIP; }, Z_NO_VALUE)


        UNWRAP_CMD(ret, NoParameters, GET_CMD(ret), { long long retPoint = 0; if (stackTop(core->coreStack, &retPoint) != STACK_OK || stackPop(core->coreStack) != STACK_OK)\
                {\
           IRQ_StackError(core); \
           return; \
       } core->rip = retPoint;\
        }, Z_NO_VALUE)

UNWRAP_CMD(je, NoParameters, GET_CMD(je)      , { int newRIP = 0; \
    if (isTapeEnd(core, sizeof(int))\
        || \
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
        \
    if(core->flags & FLAG_ZF) core->rip = newRIP; }, Z_NO_VALUE)

UNWRAP_CMD(jne, NoParameters, GET_CMD(jne)      , { int newRIP = 0; \
    if (isTapeEnd(core, sizeof(int))\
        || \
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
        \
    if(!(core->flags & FLAG_ZF)) core->rip = newRIP; }, Z_NO_VALUE)

UNWRAP_CMD(jl, NoParameters, GET_CMD(jl)      , { int newRIP = 0; \
    if (isTapeEnd(core, sizeof(int))\
        || \
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
        \
    if(core->flags & FLAG_SF) core->rip = newRIP; }, Z_NO_VALUE)

UNWRAP_CMD(jle, NoParameters, GET_CMD(jle)      , { int newRIP = 0; \
    if (isTapeEnd(core, sizeof(int))\
        || \
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
        \
    if((core->flags & FLAG_ZF) || (core->flags & FLAG_SF)) core->rip = newRIP; }, Z_NO_VALUE)

UNWRAP_CMD(jg, NoParameters, GET_CMD(jg)      , { int newRIP = 0; \
    if (isTapeEnd(core, sizeof(int))\
        || \
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
        \
    if(!(core->flags & FLAG_SF)) core->rip = newRIP; }, Z_NO_VALUE)

UNWRAP_CMD(jge, NoParameters, GET_CMD(jge)      , { int newRIP = 0; \
    if (isTapeEnd(core, sizeof(int))\
        || \
        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
        \
    if((core->flags & FLAG_ZF) || !(core->flags & FLAG_SF)) core->rip = newRIP; }, Z_NO_VALUE)

//UNWRAP_CMD(jm, NoParameters, GET_CMD(jm)      , { int newRIP = 0; \
//    if (isTapeEnd(core, sizeof(int))\
//        || \
//        (newRIP = GET_ARGUMENT(core, int), newRIP >= core->program.size))\
//    {\
//        IRQ_InvalidParameters(core); \
//        return; \
//    }\
//    time_t currentTime = 0; struct tm *currentDate; t = time(0); currentDate = localtime(&t);\
//    if((core->flags & FLAG_ZF) || !(core->flags & FLAG_SF)) core->rip = newRIP; }, Z_NO_VALUE)

#endif

UNWRAP_CMD(and,         TwoParameters, GET_CMD(and)     , { value = parameters.first & parameters.second; }, long long)
UNWRAP_CMD(xor,         TwoParameters, GET_CMD(xor)     , { value = parameters.first ^ parameters.second; }, long long)
UNWRAP_CMD(or,          TwoParameters, GET_CMD(or)      , { value = parameters.first | parameters.second; }, long long)
UNWRAP_CMD(test,        TwoParameters, GET_CMD(test)    , { value = parameters.first & parameters.second; \
if(!value) core->flags &= (~(FLAG_ZF));\
else core->flags |= ((FLAG_ZF));\
if (value >= 0) core->flags &= (~(FLAG_SF)); \
else core->flags |= ((FLAG_SF)); \
    }, Z_NO_VALUE)

UNWRAP_CMD(cmp,        TwoParameters, GET_CMD(cmp)    , { value = parameters.first - parameters.second; \
if(!value) core->flags |= ((FLAG_ZF));\
else core->flags &= (~(FLAG_ZF)); \
if (value >= 0) core->flags &= (~(FLAG_SF)); \
else core->flags |= ((FLAG_SF)); \
    }, Z_NO_VALUE)

UNWRAP_CMD(fcmp,        TwoParameters, GET_CMD(fcmp)    , { double dvalue = *(double*)(&parameters.first) - *(double*)(&parameters.second); \
if(dvalue == 0.0) core->flags |= ((FLAG_ZF));\
else core->flags &= (~(FLAG_ZF)); \
if (dvalue >= 0.0) core->flags &= (~(FLAG_SF)); \
else core->flags |= ((FLAG_SF)); \
    }, Z_NO_VALUE)

UNWRAP_CMD(shl,         TwoParameters, GET_CMD(shl)     , { if (parameters.second < 0 || parameters.second > 64)\
    {\
        IRQ_InvalidParameters(core);\
        return;\
    }\
    \
    value = parameters.first << parameters.second; }, long long)
UNWRAP_CMD(shr,         TwoParameters, GET_CMD(shr)     , { if (parameters.second < 0 || parameters.second > 64)\
    {\
        IRQ_InvalidParameters(core); \
        return; \
    }\
    \
    value = parameters.first >> parameters.second; }, long long)
UNWRAP_CMD(sti,         NoParameters, GET_CMD(sti)     , { core->flags &= (~(FLAG_IF)); }, Z_NO_VALUE)
UNWRAP_CMD(cli,         NoParameters, GET_CMD(cli)     , { core->flags |= ((FLAG_IF)); }, Z_NO_VALUE)
UNWRAP_CMD(not,         OneParameter, GET_CMD(not)     , { value = ~parameters.first; }, long long)
