/*
Copyright (c) 2020  MIPT

Module Name:
    Disassembling.c

Abstract:
    Разбирает программу

Author:
    JulesIMF

Last Edit:
    26.10.2020

Edit Notes:

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Includes.h"
#include "../Common.h"

//typedef struct
//{
//    int  nLabels;
//    int* labels;
//    int  nCommands;
//} DisassemblyParameters;

#define UNWRAP_SIMPLE(name) case cmd_ ## name: rip++;    continue;\

#define UNWRAP_JMP(name) case cmd_ ## name: rip += 5; parameters.nLabels++; continue;\

#define UNWRAP_ALU(name, operands) case cmd_ ## name: rip += 2 + 8 * (operands); continue;\


int cmp(void const* first, void const* second)
{
    return *(int*)first - *(int*)second;
}


DisassemblyParameters getParameters(byte* byteCode, size_t size)
{
    DisassemblyParameters parameters = { 0, (int*)NULL, 0 };
    int rip = 0;



    while (rip < size)
    {
        parameters.nCommands++;
        switch (byteCode[rip])
        {
        case cmd_inc:
        case cmd_dec:
        case cmd_int:
        case cmd_out:
            rip += 2;
            continue;

        #include "../Jules Assembler/Instructions include.h"
        
        default:
            parameters.nCommands = -1;
            printf("Error: unknown instruction. Byte 0x%08llX. Stop.\n", rip + _JCPU_SIGNATURE_SIZE);
            return parameters;
        #undef UNWRAP_JMP       
        }
    }

    if (rip != size)
    {
        parameters.nCommands = -1;
        printf("Error: unexpected end of file. Stop.\n");
        return parameters;
    }

    parameters.labels = (int*)calloc(parameters.nLabels, sizeof(int));
    rip = 0;
    int labelsIndex = 0;
#define UNWRAP_JMP(name) 0;
    while (rip != size && labelsIndex != parameters.nLabels)
    {
        switch (byteCode[rip])
        {
        case cmd_inc:
        case cmd_dec:
        case cmd_int:
        case cmd_out:
            rip += 2;
            continue;

        #include "../Jules Assembler/Instructions include.h"
        default:
            rip++;
            parameters.labels[labelsIndex++] = *(int*)(byteCode + rip);
            rip += 4;
        }
    }

    qsort(parameters.labels, parameters.nLabels, sizeof(int), cmp);

    return parameters;    
}

void writeAlu(FILE* file, byte* code, int operands)
{
    byte secondByte = *(code++);

    int isPtr_1 = secondByte & 1,
        isPtr_2 = secondByte & (1 << 4),
        AST_1 = secondByte & (7 << 1),
        AST_2 = secondByte & (7 << 5);

    AST_1 >>= 1, AST_2 >>= 5;

    long long firstParameter = *(long long*)code;
    code += sizeof(long long);
     
    
    if (isPtr_1)
    {
        if (firstParameter)
            fprintf(file, " ps");
        else
            fprintf(file, " p");
    }

    if (AST_1 < 4)
        fprintf(file, " r%cx", 'a' + AST_1);

    if (AST_1 == 4)
        fprintf(file, " rsp");
    if (AST_1 == 5 || (AST_1 < 5 && isPtr_1 && firstParameter))
        fprintf(file, " 0x%llX", firstParameter);

    if (AST_1 > 5)
        fprintf(file, " AST%d 0x%llX", AST_1, firstParameter);

    if (operands == 1)
    {
        fprintf(file, "\n");
        return;
    }

    long long secondParameter = *(long long*)code;
    code += sizeof(long long);


    if (isPtr_2)
    {
        if (secondParameter)
            fprintf(file, " ps");
        else
            fprintf(file, " p");
    }

    if (AST_2 < 4)
        fprintf(file, " r%cx", 'a' + AST_2);

    if (AST_2 == 4)
        fprintf(file, " rsp");
    if (AST_2 == 5 || (AST_2 < 5 && isPtr_2 && secondParameter))
        fprintf(file, " 0x%llX", secondParameter);

    if (AST_2 > 5)
        fprintf(file, " AST%d 0x%llX", AST_2, secondParameter);

    fprintf(file, "\n");
}

#undef UNWRAP_SIMPLE
#undef UNWRAP_ALU


void disassembly(byte* byteCode, size_t size, char const* fileName)
{
    //Проверка на корректность
    long long stackSize = isCorrect(byteCode, size);

    if (!stackSize)
    {
        printf("Program is damaged or has too old version. Stop.\n");
        return;
    }

    //Параметры
    DisassemblyParameters parameters = getParameters(byteCode + _JCPU_SIGNATURE_SIZE, size - _JCPU_SIGNATURE_SIZE);
    if (parameters.nCommands == -1)
    {
        return;
    }

    //Программа корректна


    int asmName_size = strlen(fileName);
    char const* addName = " - disassembler.asm";
    char* asmName = (char*)calloc(asmName_size + 21, sizeof(char));
    strcpy(asmName, fileName);
    strcat(asmName, addName);
    //printf("DEBUG: %s", asmName);
    FILE* file = fopen(asmName, "w");
    if (file == NULL)
    {
        printf("Failed to open output file. Stop.\n");
        return;
    }

    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fprintf(file, 
        ";\n;JulesIMF disassemler, ver. %d\n;\n"
        ";Created:\t%s"
        ";Binary: \t\"%s\"\n;\n"
        ";Set stack size\n",
        _JCPU_ASM_VERSION, 
        asctime(timeinfo),
        fileName);

    fprintf(file, "@%lld\n\n\n", stackSize);

    //Давайте выводить


#define UNWRAP_SIMPLE(name) case cmd_ ## name: rip++; fprintf(file, "%s\n", #name);   continue;\

#define UNWRAP_JMP(name) case cmd_ ## name: rip++; fprintf(file, "%s LABEL_0x%X\n", #name, *(int*)(byteCode + rip)); rip += 4; continue;\

#define UNWRAP_ALU(name, operands) case cmd_ ## name: rip++; fprintf(file, "%s", #name); writeAlu(file, byteCode + rip, operands); rip += 1 + 8 * (operands); continue;\


    int rip = 0;
    int nextLabel = 0;
    byteCode += _JCPU_SIGNATURE_SIZE;
    size -= _JCPU_SIGNATURE_SIZE;
    if (parameters.nLabels)
        fprintf(file, "ENTRY_POINT:\n");

    while (rip < size)
    {
        //Пилим метки
        if (nextLabel < parameters.nLabels &&
            rip == parameters.labels[nextLabel])
        {
            fprintf(file, "\nLABEL_0x%X:\n", rip);
            nextLabel++;
            while (nextLabel != parameters.nLabels &&
                   parameters.labels[nextLabel] == parameters.labels[nextLabel - 1]) nextLabel++;
        }


        //Команды
        if (parameters.nLabels)
            fprintf(file, "\t");

        switch (byteCode[rip])
        {
        case cmd_inc:
            rip++;
            fprintf(file, "inc r%cx\n", 'a' + (byteCode[rip++] & 3));
            continue;

        case cmd_dec:
            rip++;
            fprintf(file, "dec r%cx\n", 'a' + (byteCode[rip++] & 3));
            continue;

        case cmd_int:
            rip++;
            fprintf(file, "int %d\n", (char)byteCode[rip++]);
            continue;

        case cmd_out:
            rip++;
            fprintf(file, "out");
            if (byteCode[rip] == OUTF_016LLX)
            {
                fprintf(file, " llx\n");
                rip++;
                continue;
            }

            if (byteCode[rip] == OUTF_LF)
            {
                fprintf(file, " lf\n");
                rip++;
                continue;
            }

            fprintf(file, "\n");
            rip++;
            continue;

        #include "../Jules Assembler/Instructions include.h"
        }
    }

}