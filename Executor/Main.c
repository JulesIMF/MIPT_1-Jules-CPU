/*
Copyright (c) 2020  MIPT

Module Name:
    Main.c

Abstract:
    �������� ����

Author:
    JulesIMF

Last Edit:
    19.10.2020 1:51

Edit Notes:

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Core.h"
#include "../Common.h"
#include "Files.h"
#include "Execution.h"

static size_t STACK_CAPACITY = 10000;

int main(int argc, char const** argv)
{
    SetColor(White);

    if (argc == 1)
    {
        SetColor(LightRed);
        printf("No *.jbc file specified. Stop.\n");
        SetColor(LightGray);
        //return 0;



        
        //DEBUG
        SetColor(White);
        argv[1] = "../pgmcmn/fib.jbc";
    }
    Core* core = newCore(STACK_CAPACITY);
    int fileSize = 0;
    byte* file = (byte*)translateFileIntoRam(argv[1], &fileSize);
    if (file == NULL)
    {
        SetColor(LightRed);
        printf("Can`t open file \"%s\". Stop.\n", argv[1]); 
        SetColor(LightGray);
        return 0;
    }
    if (runProgram(core, file, fileSize))
        return 0;

    //printf("Program runned\n\n\n");
    while (executeNextCommand(core) != -1)
        ;

    //printf("\n\nProgram ended\n");
    deleteCore(core);
    free(file);
    SetColor(LightGray);
    return 0;
}
