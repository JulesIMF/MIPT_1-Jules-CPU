/*
Copyright (c) 2020  MIPT

Module Name:
    Parsing.c

Abstract:
    ��������� ������� ��������

Author:
    JulesIMF

Last Edit:
    22.10.2020 1:42

Edit Notes:

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "Files.h"
#include "Routine.h"
#include "Assembly.h"
#include "../Common.h"
void SetColor(int text)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)(text));
}


int main(int argc, char const** argv)
{
    SetColor(LightRed);
    if (argc == 1)
    {
        printf("No *.asm file specified. Stop\n");

        //return 0;
        SetColor(LightGray);
        //DEBUG
        argv[1] = "../pgmcmn/equation.asm";
    }

    int fileSize = 0, nStrings = 0;
    byte* asmFile   = (byte*)translateFileIntoRam(argv[1], &fileSize, &nStrings);
    if (asmFile == NULL)
    {
        printf("Can`t open file \"%s\". Stop.\n", argv[1]);
        SetColor(LightGray);
        return 0;
    }

    Line* lines = (Line*)calloc(nStrings, sizeof(Line));

    if (separateStrings(asmFile, fileSize, lines, nStrings))
    {
        printf("Something went wrong... Stop.\n");
        SetColor(LightGray);
        return 0;
    }

    //
    //���������� �������
    //


    //��� �� ������� ����������� � ���������� �������
    for (size_t i = 0; i != nStrings; i++)
        replaceSemicolon(lines + i);

    eraseLeadingSpaces(lines, nStrings);


    //
    //���������������
    //
    ByteCode code = getByteCode(lines, nStrings, argv[1]);
           
    if (code.programSize) 
    {

        //
        //������� ���� ��� ���������...
        //
        char* programFileName = getProgramFileName(argv[1]);
        if (programFileName == NULL)
        {
            printf("Unknown error.\n");
            SetColor(LightGray);
            return 0;
        }

        FILE* program = fopen(programFileName, "wb");

        if (program == NULL)
        {
            printf("Can`t open file \"%s\" for write. Stop.\n", programFileName);
            SetColor(LightGray);
            return 0;
        }

        fwrite(code.code, sizeof(byte), code.programSize, program);
        fclose(program);
        free(programFileName);
    }
    free(asmFile);
    free(lines);   
}
