/*
Copyright (c) 2020  MIPT

Module Name:
    Parsing.c

Abstract:
    Реализует функции парсинга

Author:
    JulesIMF

Last Edit:
    23.10.2020 1:03

Edit Notes:

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "Line.h"
#include "Parsing.h"
#include "Routine.h"
#include "../Common.h"

//****************************************************************
//* Символы метки, установки прерывания, установки размера стека *
//****************************************************************

#define LABEL_SYMBOL     ':'
#define STACKSET_SYMBOL  '@'
#define INTSET_SYMBOL    '#'

#define STACK_SIZE 2000

static void printError(char const* error, int lineN)
{
    printf("Error: %s. Line %d. Stop.\n", error, lineN);
}

char const* isLabel(Line line)
{
    if (line.size > 1 && line.string[line.size - 1] == LABEL_SYMBOL)
        return line.string;

    else
        return NULL;
}

int isSameLabel(char const* label, char const* candidate)
{
    while (*label == *candidate && *label && *candidate)
        label++, candidate++;

    return (*label == '\0') && (*candidate == LABEL_SYMBOL);
}

unsigned long long isStackSet(Line line)
{
    if (*(line.string) == STACKSET_SYMBOL && *(line.string + 1))
    {
        unsigned long long newStackSize = 0;
        sscanf(line.string + 1, "%lld", &newStackSize);
        return newStackSize;
    }

    return 0;
}

long long isIntSet(Line line)
{
    long long returned = 0;
    int nInt = 0, address = 0;
    if (*(line.string) == INTSET_SYMBOL && *(line.string + 1))
    {
        sscanf(line.string + 1, "%d %d", &nInt, &address);
        returned = nInt;
        returned <<= 32;
        returned += address;
    }

    return returned;
}


typedef struct
{
    byte secondByte;
    long long arg1, arg2;
    int success;
} StdInstructionArgs;

static StdInstructionArgs parseStdInstructionArgs(char const* string, int isTwoParam, size_t lineN)
{
    byte secondByte = 0;
    StdInstructionArgs stdInstructionArgs;
    stdInstructionArgs.success = 0;
    long long arg1 = 0, arg2 = 0;
    int arg1_set = 0, arg2_set = 0;
    int arg1_ps = 0, arg2_ps = 0;
    static char buffer[20] = "";
    int procN = 0;
GET_ARG1:
    sscanf(string, "%20s%n", buffer, &procN);

    if (!procN)
        goto GET_ARG1_ERROR;

    //isPointer
    if (!strcmp("p", buffer))
    {
        secondByte |= 1;
        string += procN;
        sscanf(string, "%20s%n", buffer, &procN);
    }

    //isPointer + sum
    if (!strcmp("ps", buffer))
    {
        secondByte |= 1;
        string += procN;
        sscanf(string, "%20s%n", buffer, &procN);
        arg1_ps = 1;
    }

    if (!procN)
        goto OUT;

    //Registers
    if (!strcmp("rax", buffer))
    {
        secondByte |= 0 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

    if (!strcmp("rbx", buffer))
    {
        secondByte |= 1 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

    if (!strcmp("rcx", buffer))
    {
        secondByte |= 2 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

    if (!strcmp("rdx", buffer))
    {
        secondByte |= 3 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

    if (!strcmp("rsp", buffer))
    {
        secondByte |= 4 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

    //Const

    //Decimal
    if (sscanf(string, "%lld%n", &arg1, &procN) > 0 && (isspace(string[procN]) || !string[procN]))
    {
        secondByte |= 5 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

    //HEX
    if (sscanf(string, "%llx%n", &arg1, &procN) > 0 && (isspace(string[procN]) || !string[procN]))
    {
        secondByte |= 5 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

    //Double
    if (sscanf(string, "%lf%n", &arg1, &procN) > 0 && (isspace(string[procN]) || !string[procN]))
    {
        secondByte |= 5 << 1;
        arg1_set = 1;
        goto GET_ARG2;
    }

GET_ARG1_ERROR:
    printError("can`t recognize first parameter", lineN);
    return stdInstructionArgs;


GET_ARG2:
    if (!isTwoParam)
        goto OUT;
    string += procN;

    sscanf(string, "%20s%n", buffer, &procN);

    if (!procN)
        goto GET_ARG2_ERROR;

    //isPointer
    if (!strcmp("p", buffer))
    {
        secondByte |= 1 << 4;
        string += procN;
        sscanf(string, "%20s%n", buffer, &procN);
    }

    //isPointer + sum
    if (!strcmp("ps", buffer))
    {
        secondByte |= 1 << 4;
        string += procN;
        sscanf(string, "%20s%n", buffer, &procN);
        arg2_ps = 1;
    }

    if (!procN)
        goto OUT;

    //Registers
    if (!strcmp("rax", buffer))
    {
        secondByte |= 0 << 5;
        arg1_set = 1;
        goto OUT;
    }

    if (!strcmp("rbx", buffer))
    {
        secondByte |= 1 << 5;
        arg1_set = 1;
        goto OUT;
    }

    if (!strcmp("rcx", buffer))
    {
        secondByte |= 2 << 5;
        arg1_set = 1;
        goto OUT;
    }

    if (!strcmp("rdx", buffer))
    {
        secondByte |= 3 << 5;
        arg1_set = 1;
        goto OUT;
    }

    if (!strcmp("rsp", buffer))
    {
        secondByte |= 4 << 5;
        arg1_set = 1;
        goto OUT;
    }

    //Const

    //Decimal
    if (sscanf(string, "%lld%n", &arg2, &procN) > 0 && (!string[procN]))
    {
        secondByte |= 5 << 5;
        arg1_set = 1;
        goto OUT;
    }

    //HEX
    if (sscanf(string, "%llx%n", &arg2, &procN) > 0 && (!string[procN]))
    {
        secondByte |= 5 << 5;
        arg1_set = 1;
        goto OUT;
    }

    //Double
    if (sscanf(string, "%lf%n", &arg2, &procN) > 0 && (!string[procN]))
    {
        secondByte |= 5 << 5;
        arg1_set = 1;
        goto OUT;
    }

GET_ARG2_ERROR:
    printError("can`t recognize second parameter", lineN);
    return stdInstructionArgs;

OUT:
    stdInstructionArgs.arg1 = arg1;
    stdInstructionArgs.arg2 = arg2;
    stdInstructionArgs.secondByte = secondByte;
    stdInstructionArgs.success = 1;
    return stdInstructionArgs;
}

Instruction getInstruction(Line line, size_t lineN, Label* labels, size_t nLabels)
{
    static char mnemonic[10] = "";
    Instruction instruction = { 0, { 0 } };
    if (isLabel(line))
        return instruction;

    int shift = 0;
    sscanf(line.string, "%10s%n", mnemonic, &shift);

    

    //
    //***********************************************************
    //*************************SPECIALS**************************
    //***********************************************************
    //


    //out
    if (!strcmp("out", mnemonic))
    {
        instruction.code[instruction.length++] = cmd_out;
        char mode[5] = {0,0,0,0,0};
        sscanf(line.string + shift + 1, "%3s", mode);
        byte secondByte = OUTF_LLD;
        if (!strcmp("llx", mode))
            secondByte = OUTF_016LLX;

        if (!strcmp("lf", mode))
            secondByte = OUTF_LF;

        instruction.code[instruction.length++] = secondByte;
        return instruction;
    }

    //int
    if (!strcmp("int", mnemonic))
    {
        instruction.code[instruction.length++] = cmd_int;
        int irqCode = 0;
        if (!sscanf(line.string + 1 + shift, "%d", &irqCode) || !(8 <= irqCode && irqCode < 16))
        {
            printError("no such interruption handler", lineN);
            instruction.length = 0;
            return instruction;
        }
        *(char*)(&instruction.code[instruction.length]) = (char)irqCode;
        instruction.length++;
        return instruction;
    }

    if (!strcmp("inc", mnemonic) || !strcmp("dec", mnemonic))
    {
        if (!strcmp("inc", mnemonic))
            instruction.code[instruction.length++] = cmd_inc;
        else
            instruction.code[instruction.length++] = cmd_dec;

        char reg[4] = "";
        if (!sscanf(line.string + 1 + shift, "%3s", reg))
        {
            printError("no such interruption handler", lineN);
            instruction.length = 0;
            return instruction;
        }

        if (!strcmp("rax", reg))
        {
            instruction.code[instruction.length++] = 0;
            return instruction;
        }
        if (!strcmp("rbx", reg))
        {
            instruction.code[instruction.length++] = 1;
            return instruction;
        }
        if (!strcmp("rcx", reg))
        {
            instruction.code[instruction.length++] = 2;
            return instruction;
        }
        if (!strcmp("rdx", reg))
        {
            instruction.code[instruction.length++] = 3;
            return instruction;
        }
        
        printError("unknown mnemonic", lineN);

        instruction.length = 0;
        return instruction;
    }

   

    //***********************************************************
    //*************************DEFINES***************************
    //***********************************************************

#undef UNWRAP_JMP
#undef UNWRAP_SIMPLE
#undef UNWRAP_ALU

#define UNWRAP_JMP(jmpname) \
    if (!strcmp(#jmpname, mnemonic))\
    {\
        instruction.code[instruction.length++] = cmd_##jmpname;\
        char labelname[20] = "";\
        sscanf(line.string + shift + 1, "%20s", labelname);\
        for(int i = 0; i != nLabels; i++)\
        {\
            if(isSameLabel(labelname, labels[i].label))\
            {\
                *(int*)(&instruction.code[instruction.length]) = labels[i].address; instruction.length += 4;\
                return instruction;\
            }\
        } printError("no such label", lineN);\
    instruction.length = 0; return instruction; \
    }\

#define UNWRAP_SIMPLE(name) if (!strcmp(#name, mnemonic))\
{\
    instruction.code[instruction.length++] = cmd_##name;\
    return instruction;\
}\

#define UNWRAP_ALU(name, param) if (!strcmp(#name, mnemonic))\
{\
    instruction.code[instruction.length++] = cmd_##name;\
    StdInstructionArgs args = parseStdInstructionArgs(line.string + shift + 1, param - 1, lineN);\
    if (!args.success)\
    {\
        instruction.length = 0;\
        return instruction;\
    }\
    instruction.code[instruction.length++] = args.secondByte;\
    *(long long*)(&instruction.code[instruction.length]) = args.arg1;\
    instruction.length += 8;\
    if(param == 2){\
    *(long long*)(&instruction.code[instruction.length]) = args.arg2;\
    instruction.length += 8;\
    }\
    return instruction;\
}\

#include "Instructions include.h"

    return instruction;
}

ProgramParameters getProgramParameters(Line* lines, size_t nLines)
{
    assert(lines);
    ProgramParameters programParameters;

    //
    //Инициализация
    //
    programParameters.stackSize = STACK_SIZE;
    programParameters.nLabels = 0;
    for (int i = 0; i != 8; i++)
        programParameters.IRQ[i] = -1;



    for (int i = 0; i != nLines; i++)
        programParameters.nLabels += !!isLabel(lines[i]);

    programParameters.labels = (Label*)calloc(programParameters.nLabels, sizeof(Label));

    //Запихаем имена меток в массив
    {
        size_t labelsPtr = 0;
        for (int i = 0; i != nLines; i++)
        {
            char const* label = isLabel(lines[i]);
            if (label)
            {
                programParameters.labels[labelsPtr].label = label;
                programParameters.labels[labelsPtr].address = -1;
                labelsPtr++;
            }
        }
    }


    int rip = 0;
    int labelsPtr = 0;
    char* newLabel = NULL;
    long long newStackSize = 0;
    long long newIrq = 0;
    for (int i = 0; i != nLines; i++)
    {
        if (!lines[i].size)
            continue;

        if (newLabel = isLabel(lines[i]))
        {
            programParameters.labels[labelsPtr++].address = rip;
            continue;
        }

        if (newIrq = isIntSet(lines[i]))
        {
            int address = newIrq & (~0);
            newIrq >>= 32;
            if ((8 <= newIrq && newIrq < 16))
                programParameters.IRQ[newIrq - 8] = address;

            continue;
        }

        if (newStackSize = isStackSet(lines[i]))
        {
            programParameters.stackSize = newStackSize;
            continue;
        }

        Instruction instruction = getInstruction(lines[i], i + 1, programParameters.labels, programParameters.nLabels);
        if (!instruction.length)
        {
            free(programParameters.labels);
            programParameters.labels = NULL;
            programParameters.programSize = -1; //Программа некорректна
            return programParameters;
        }

        rip += instruction.length;
    }

    programParameters.programSize = rip;
    return programParameters;
}
