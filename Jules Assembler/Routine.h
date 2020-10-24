/*
Copyright (c) 2020  MIPT

Module Name:
    Routine.h

Abstract:
    ��������� ������ �������

Author:
    JulesIMF

Last Edit:
    22.10.2020 1:42

Edit Notes:

*/

#ifndef _JCPU_ROUTINE
#define _JCPU_ROUTINE

typedef char byte;

/**
 * ���������� ��� ��������� ����� - *.jbc ���� asmFileName *.jsm, ����� Program.h
 * \param asmFileName ��� �����
 */
char const* getProgramFileName(char const* asmFileName);

/**
 * ������� ������� �������.
 */
void eraseLeadingSpaces(Line* lines, size_t nLines);

#endif // !_JCPU_ROUTINE
