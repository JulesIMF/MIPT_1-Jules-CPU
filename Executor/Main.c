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
    if (argc == 1)
    {
        printf("No *.jbc file specified. Stop.\n");
        //return 0;
        argv[1] = "../pgmcmn/equation.jbc";
    }
    Core* core = newCore(STACK_CAPACITY);
    int fileSize = 0;
    byte* file = (byte*)translateFileIntoRam(argv[1], &fileSize);
    if (file == NULL)
    {
        printf("Can`t open file \"%s\"\n", argv[1]);
    }
    if (runProgram(core, file, fileSize))
        return 0;

    //printf("Program runned\n\n\n");
    while (executeNextCommand(core))
        ;

    //printf("\n\nProgram ended\n");
    deleteCore(core);
    free(file);
    return 0;
}

void foo()
{
    int x = 0;
    
label:
    x++;
    if (x != 10)
        goto label;


}