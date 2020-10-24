/*
Copyright (c) 2020  MIPT

Module Name:
    Streams.h

Abstract:
    Реализует потоки ввода/вывода

Author:
    JulesIMF

Last Edit:
    16.10.2020 10:08

Edit Notes:

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Streams.h"

#ifndef _MSC_VER
#define __crt_va_start va_start
#define __crt_va_end va_end
#define __crt_va_arg va_arg
#endif // !_MSC_VER

void SetColor(int text)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)(text));
}

int str_printf(OutputStream* stream, char const* format, ...)
{
    va_list list;
    __crt_va_start(list, format);
    int ret = vfprintf(stream->stream, format, list);
    __crt_va_end(list);
    return ret;
}   

int str_scanf(InputStream* stream, char const* format, ...)
{
    va_list list;
    __crt_va_start(list, format);
    int ret = vfscanf(stream->stream, format, list);
    __crt_va_end(list);
    return ret;
}

InputStream*    newInputStream()
{
    InputStream* stream = (InputStream*)calloc(1, sizeof(InputStream));
    stream->stream = stdin;
    return stream;
}

OutputStream* newOutputStream()
{
    OutputStream* stream = (OutputStream*)calloc(1, sizeof(OutputStream));
    stream->stream = stdout;
    return stream;
}

void            deleteInputStream(InputStream* stream)
{
    free(stream);
}

void            deleteOutputStream(OutputStream* stream) 
{
    free(stream);
}
