/*
Copyright (c) 2020  MIPT

Module Name:
    Execution.h

Abstract:
    ��������� ��������� ��������� ���������

Author:
    JulesIMF

Last Edit:
    16.10.2020 11:29

Edit Notes:

*/

#ifndef _JCPU_EXECUTION
#define _JCPU_EXECUTION
#include "Core.h"
#include "IRQ.h"

#define GET_ARGUMENT(CORE, TYPE) ((CORE->rip += sizeof(TYPE)),  *( TYPE*)( (CORE)->program.tape + CORE->rip - sizeof(TYPE) ) )
#define WRONG_SECOND_BYTE ( (byte)255 )


/**
 * ���������, �������� �� �������� �������� ���������������� �������.
 * 
 * \param core
 * \param size
 * \return 0 ���� �������� (�� ����� �����), 1 �����
 */
int isTapeEnd(Core* core, size_t size);


//���� isValidParameters == 0, ��������� ���� ����� ���� ������ ������
typedef struct
{
    int isValidParameters;
    long long first;
    long long second;
} Parameters;

/**
 * .
 * 
 * \param byteCode ��������������� � ������ ����-���
 * \return -1 ���� ��������� �����������, �������� ���� ��������� ���������
 */
int programShift(byte* byteCode);

Program getProgram(byte* byteCode, size_t byteCodeSize);

byte getSecondByte(Core* core);


/*
static void IRQ_StackError(Core* core);         //0
static void IRQ_DivideByZero(Core* core);       //1
static void IRQ_InvalidCommand(Core* core);     //2
static void IRQ_InvalidParameters(Core* core);  //3
static void IRQ_InvalidIRQ(Core* core);         //4
*/
void proceedInterruption(Core* core);

Parameters getTwoParameters(Core* core);
Parameters getOneParameter(Core* core);
Parameters getNoParameters(Core* core);


/**
 * ��������� ���������. ����� �������� ��������� �� �������
 *
 * \param core
 * \param translatedFile
 * \param fileSize
 * \return 0 ���� ��������� �������� ��� ������, 1 �����
 */
int runProgram(Core* core, byte* translatedFile, int fileSize);

/**
 * .
 *
 * \param core
 * \return 0 ���� ��������� ������ �� ����� �����������, 1 �����
 */
int executeNextCommand(Core* core);

#endif // !_JCPU_EXECUTION
