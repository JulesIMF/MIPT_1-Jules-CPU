/*
Copyright (c) 2020  MIPT
Module Name:
    Handlers.h
Abstract:
    Описывает хендлеры
Author:
    JulesIMF
Last Edit:
    16.10.2020 10:08
Edit Notes:

*/

#ifndef _JCPU_HANDLERS
#define _JCPU_HANDLERS
#include "Core.h"

//Arithmetic
void hnd_add(Core* core);
void hnd_sub(Core* core);
void hnd_mul(Core* core);
void hnd_div(Core* core);
void hnd_sin(Core* core);
void hnd_cos(Core* core);
void hnd_sqrt(Core* core);
void hnd_inc(Core* core);
void hnd_dec(Core* core);
void hnd_neg(Core* core);
void hnd_fadd(Core* core);
void hnd_fsub(Core* core);
void hnd_fmul(Core* core);
void hnd_fdiv(Core* core);


//Control
void hnd_jmp(Core* core);
void hnd_call(Core* core);
void hnd_ret(Core* core);
void hnd_int(Core* core);
void hnd_iret(Core* core);


//Logic
void hnd_and(Core* core);
void hnd_xor(Core* core);
void hnd_or(Core* core);
void hnd_test(Core* core);
void hnd_cmp(Core* core);
void hnd_shl(Core* core);
void hnd_shr(Core* core);
void hnd_sti(Core* core);
void hnd_cli(Core* core);
void hnd_not(Core* core);


//Stack
void hnd_mov(Core* core);
void hnd_push(Core* core);
void hnd_pop(Core* core);
void hnd_pusha(Core* core);
void hnd_pushf(Core* core);
void hnd_popa(Core* core);
void hnd_popf(Core* core);


//System
void hnd_out(Core* core);
void hnd_hlt(Core* core);
void hnd_in(Core* core);
void hnd_dump(Core* core);
void hnd_crack(Core* core);
void hnd_nop(Core* core);

#endif // !_JCPU_HANDLERS
