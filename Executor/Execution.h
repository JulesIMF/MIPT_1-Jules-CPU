/*
Copyright (c) 2020  MIPT

Module Name:
    Execution.h

Abstract:
    Описывает интерфейс обработки программы

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
 * Проверяет, возможно ли получить аргумент соответствующего размера.
 * 
 * \param core
 * \param size
 * \return 0 если возможно (не конец ленты), 1 иначе
 */
int isTapeEnd(Core* core, size_t size);


//Если isValidParameters == 0, остальные поля могут быть какими угодно
typedef struct
{
    int isValidParameters;
    long long first;
    long long second;
} Parameters;

/**
 * .
 * 
 * \param byteCode транслированный в память байт-код
 * \return -1 если программа некорректна, смещение если программа корректна
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
 * Запускает программу. Может выводить сообщения об ошибках
 *
 * \param core
 * \param translatedFile
 * \param fileSize
 * \return 0 если программа запущена без ошибок, 1 иначе
 */
int runProgram(Core* core, byte* translatedFile, int fileSize);

/**
 * .
 *
 * \param core
 * \return 0 если программа больше не может исполняться, 1 иначе
 */
int executeNextCommand(Core* core);

#endif // !_JCPU_EXECUTION
