/*
Copyright (c) 2020  MIPT

Module Name:
    Main.c

Abstract:
    Основной файл

Author:
    JulesIMF

Last Edit:
    19.10.2020 1:51

Edit Notes:

*/

#include <stdio.h>
#include <stdlib.h>
#include "../Common.h"
#include "Includes.h"
#include "../Executor/Files.h"

int main(int argc, char const** argv)
{
    SetColor(LightRed);

    if (argc == 1)
    {
        printf("No *.jbc file specified. Stop.\n");
        SetColor(LightGray);
        return 0;




        //DEBUG
        argv[1] = "../pgmcmn/fib.jbc";
    }
    int fileSize = 0;
    byte* file = (byte*)translateFileIntoRam(argv[1], &fileSize);
    if (file == NULL)
    {
        printf("Can`t open file \"%s\". Stop.\n", argv[1]);
        SetColor(LightGray);
        return 0;
    }

    disassembly(file, fileSize, argv[1]);

        
}