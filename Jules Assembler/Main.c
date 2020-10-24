/*
Copyright (c) 2020  MIPT

Module Name:
    Parsing.c

Abstract:
    Реализует функции парсинга

Author:
    JulesIMF

Last Edit:
    22.10.2020 1:42

Edit Notes:

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "Files.h"
#include "Routine.h"
#include "Assembly.h"


int main(int argc, char const** argv)
{
    if (argc == 1)
    {
        printf("No *.asm file specified. Stop\n");

        return 0;

        //DEBUG
        argv[1] = "../pgmcmn/equation.asm";
    }

    int fileSize = 0, nStrings = 0;
    byte* asmFile   = (byte*)translateFileIntoRam(argv[1], &fileSize, &nStrings);
    if (asmFile == NULL)
    {
        printf("Can`t open file \"%s\". Stop.\n", argv[1]);
        return 0;
    }

    Line* lines = (Line*)calloc(nStrings, sizeof(Line));

    if (separateStrings(asmFile, fileSize, lines, nStrings))
    {
        printf("Something went wrong... Stop.\n");
        return 0;
    }

    //
    //Собственно поехали
    //


    //Это мы убираем комментарии и пробельные символы
    for (size_t i = 0; i != nStrings; i++)
        replaceSemicolon(lines + i);

    eraseLeadingSpaces(lines, nStrings);

    //
    //Ассемблирование
    //
    ByteCode code = getByteCode(lines, nStrings);
           
    if (code.programSize) 
    {

        //
        //Запилим файл для программы...
        //
        char* programFileName = getProgramFileName(argv[1]);
        if (programFileName == NULL)
        {
            printf("Unknown error.\n");
            return 0;
        }

        FILE* program = fopen(programFileName, "wb");

        if (program == NULL)
        {
            printf("Can`t open file \"%s\" for write. Stop.\n", programFileName);
            return 0;
        }

        fwrite(code.code, sizeof(byte), code.programSize, program);
        fclose(program);
        free(programFileName);
    }
    free(asmFile);
    free(lines);   
}
