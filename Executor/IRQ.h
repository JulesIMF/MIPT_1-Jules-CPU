/*
Copyright (c) 2020  MIPT
Module Name:
    IRQ.h
Abstract:
    ��������� ���������� ����������
Author:
    JulesIMF
Last Edit:
    16.10.2020 11:29
Edit Notes:

*/

#ifndef _JCPU_IRQ
#define _JCPU_IRQ
#include "Core.h"


void IRQ_StackError(Core* core);         //0
void IRQ_DivideByZero(Core* core);       //1
void IRQ_InvalidCommand(Core* core);     //2
void IRQ_InvalidParameters(Core* core);  //3
void IRQ_InvalidIRQ(Core* core);         //4


#endif // !_JCPU_IRQ
