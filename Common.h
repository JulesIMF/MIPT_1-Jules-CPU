/*
Copyright (c) 2020  MIPT
Module Name:
    Common.c
Abstract:
    ����� �����������
Author:
    JulesIMF
Last Edit:
    17.10.2020 0:26
Edit Notes:

*/

#ifndef _JCPU_COMMON
#define _JCPU_COMMON

typedef enum
{
    //Arithmetic
    cmd_add	    = 0x00,
    cmd_sub	    = 0x01,
    cmd_mul	    = 0x02,
    cmd_div	    = 0x03,
    cmd_sin	    = 0x04,
    cmd_cos	    = 0x05,
    cmd_sqrt	= 0x06,
    cmd_inc	    = 0x07,
    cmd_dec	    = 0x08,
    cmd_neg	    = 0x09,
    cmd_fadd	= 0x0A,
    cmd_fsub	= 0x0B,
    cmd_fmul	= 0x0C,
    cmd_fdiv	= 0x0D,

    //Control
    cmd_jmp	    = 0x10,
    cmd_call	= 0x11,
    cmd_ret	    = 0x12,
    cmd_int	    = 0x13,
    cmd_iret	= 0x14,

    //Logic
    cmd_and     = 0x20,
    cmd_xor     = 0x21,
    cmd_or      = 0x22,
    cmd_test	= 0x23,
    cmd_cmp	    = 0x24,
    cmd_shl	    = 0x25,
    cmd_shr	    = 0x26,
    cmd_sti	    = 0x27,
    cmd_cli	    = 0x28,
    cmd_not     = 0x29,

    //Stack
    cmd_mov	    = 0x30,
    cmd_push	= 0x31,
    cmd_pop	    = 0x32,
    cmd_pusha	= 0x33,
    cmd_pushf	= 0x34,
    cmd_popa	= 0x35,
    cmd_popf	= 0x36,

    //System
    cmd_out	    = 0x40,
    cmd_hlt	    = 0x41,
    cmd_in	    = 0x42,
    cmd_dump	= 0x43,
    cmd_crack	= 0x44,
    cmd_nop	    = 0x45,
    
} Cmd;

typedef struct
{
    unsigned signaure;
    unsigned asmVersion;
    long long checksum;
    long long stackSize;
    unsigned INT[8];
} jbcSignature;


typedef enum { AST_RAX = 0, AST_RBX, AST_RCX, AST_RDX, AST_STACKTOP, AST_CONST } AST;

#endif // !_JCPU_COMMON
