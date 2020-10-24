/*
Copyright (c) 2020  MIPT

Module Name:
    Parsing.h

Abstract:


Author:
    JulesIMF

Last Edit:
    22.10.2020

Edit Notes:

*/

#ifndef _JCPU_PARSING
#define _JCPU_PARSING

typedef struct
{
    char const* label;
    int address;
} Label;

typedef struct
{
    size_t nLabels;
    Label *labels;
    long long stackSize;
    long long programSize;
    int IRQ[8];
} ProgramParameters;

typedef struct
{
    size_t length;

    char code[20];

    //
    //����� ���������, ��� ��� �� �������, ����� � ��� ���������,
    //������ ����� length... ��� ������ ��� �� ���������, ��� ��������� �����
    //����� � ������� + ����������, � ����� � ��� ��� ������ �� ������� code.
    //20 ���� ������ �������
    //
} Instruction;


/**
 * ����� ������ � ��������� ������ ��������� � ������ �������.
 * ���� ��������� �����������, ���� programSize ��������� �������� -1.
 */
ProgramParameters   getProgramParameters(Line* lines, size_t nLines);
Instruction         getInstruction(Line line, size_t lineN, Label* labels, size_t nLabels);

unsigned long long   isStackSet(Line line);
char const*          isLabel(Line line);
long long            isIntSet(Line line);
#endif // !_JCPU_PARSING
