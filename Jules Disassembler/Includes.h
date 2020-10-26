/*
Copyright (c) 2020  MIPT

Module Name:
    Includes.h

Abstract:
    ����� ������� ��� �����������

Author:
    JulesIMF

Last Edit:
    26.10.2020

Edit Notes:

*/

typedef struct
{
    int  nLabels;
    int* labels;
    int  nCommands;
} DisassemblyParameters;

typedef char byte;

long long isCorrect(byte* byteCode, size_t byteCodeSize);
void disassembly(byte* byteCode, size_t size, char const* fileName);
