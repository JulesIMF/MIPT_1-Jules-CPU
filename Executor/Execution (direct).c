/*
Copyright (c) 2020  MIPT

Module Name:
    Execution (direct).с

Abstract:
    Реализует непосредственный интерфейс исполнения

Author:
    JulesIMF

Last Edit:
    19.10.2020 0:14

Edit Notes:
    
*/

#include "Execution.h"
#include "..\Common.h"
#include "Handlers.h"

/**
 * Запускает программу. Может выводить сообщения об ошибках
 * 
 * \param core 
 * \param translatedFile
 * \param fileSize
 * \return 0 если программа запущена без ошибок, 1 иначе
 */
int runProgram(Core* core, byte* translatedFile, int fileSize)
{
    assert(core);
    assert(translatedFile);
    Program program = getProgram(translatedFile, fileSize);

    if (program.tape == NULL)
    {
        printf("Failed to execute: the program is damaged or has too old version\n");
        return 1;
    }

    core->program = program;
    core->rip = 0;
    core->interruption = -1;
    //TODO: intTable
    core->rx[0] = core->rx[1] = core->rx[2] = core->rx[3] = 0ll;
    core->flags = FLAG_IF;
    return 0;
}



/**
 * .
 * 
 * \param core
 * \return 0 если программа больше не может исполняться, 1 иначе
 */
int executeNextCommand(Core* core)
{
    if (core->rip >= core->program.size
        ||
        core->isWorking == 0)
    {
        return 0;
    }

    switch (GET_ARGUMENT(core, byte))
    {

        //
        //Эти строки закомментированы, а не удалены, с целью иметь возможность просто к ним вернуться
        //


    /*case cmd_add:
        hnd_add(core);
        return 1;

    case cmd_sub:
        hnd_sub(core);
        return 1;

    case cmd_mul:
        hnd_mul(core);
        return 1;

    case cmd_div:
        hnd_div(core);
        return 1;

    case cmd_sin:
        hnd_sin(core);
        return 1;

    case cmd_cos:
        hnd_cos(core);
        return 1;

    case cmd_sqrt:
        hnd_sqrt(core);
        return 1;

    case cmd_inc:
        hnd_inc(core);
        return 1;

    case cmd_dec:
        hnd_dec(core);
        return 1;

    case cmd_neg:
        hnd_neg(core);
        return 1;

    case cmd_fadd:
        hnd_fadd(core);
        return 1;

    case cmd_fsub:
        hnd_fsub(core);
        return 1;

    case cmd_fmul:
        hnd_fmul(core);
        return 1;

    case cmd_fdiv:
        hnd_fdiv(core);
        return 1;

    case cmd_jmp:
        hnd_jmp(core);
        return 1;

    case cmd_call:
        hnd_call(core);
        return 1;

    case cmd_ret:
        hnd_ret(core);
        return 1;

    case cmd_int:
        hnd_int(core);
        return 1;

    case cmd_iret:
        hnd_iret(core);
        return 1;

    case cmd_and:
        hnd_and(core);
        return 1;

    case cmd_xor:
        hnd_xor(core);
        return 1;

    case cmd_or:
        hnd_or(core);
        return 1;

    case cmd_test:
        hnd_test(core);
        return 1;

    case cmd_cmp:
        hnd_cmp(core);
        return 1;

    case cmd_shl:
        hnd_shl(core);
        return 1;

    case cmd_shr:
        hnd_shr(core);
        return 1;

    case cmd_sti:
        hnd_sti(core);
        return 1;

    case cmd_cli:
        hnd_cli(core);
        return 1;

    case cmd_not:
        hnd_not(core);
        return 1;

    case cmd_mov:
        hnd_mov(core);
        return 1;*/

//
//**********************************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************************
//**********************************************************************************************************************************************************************************
//


        //
        //Дорогой потомок, если ты сейчас читаешь это, знай - это сделано в учебных целях,
        //и без острой нужды НИКОГДА так не делай. Злоупотребление макросами - это преступление,
        //потому что читать такой код жутко сложно. Простите.
        //




#define UNWRAP_CMD(NAME, ARGS, CMD_CODE, CMD_BODY, PUSHED_VALUE_TYPE) case CMD_CODE : hnd_##NAME (core); return 1;
#include "../Commands includes.h"
#undef UNWRAP_CMD

    case cmd_push:
        hnd_push(core);
        return 1;

    case cmd_pop:
        hnd_pop(core);
        return 1;

    case cmd_pusha:
        hnd_pusha(core);
        return 1;

    case cmd_pushf:
        hnd_pushf(core);
        return 1;

    case cmd_popa:
        hnd_popa(core);
        return 1;

    case cmd_popf:
        hnd_popf(core);
        return 1;

    case cmd_out:
        hnd_out(core);
        return 1;

    case cmd_hlt:
        hnd_hlt(core);
        return 1;

    case cmd_in:
        hnd_in(core);
        return 1;

    case cmd_dump:
        hnd_dump(core);
        return 1;

    case cmd_nop:
        hnd_nop(core);
        return 1;

    case cmd_mov:
        hnd_mov(core);
        return 1;

    default:
        IRQ_InvalidCommand(core);
        return 0;
    }
}
