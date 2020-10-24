/*
Copyright (c) 2020  MIPT

Module Name:
    Streams.h

Abstract:
    Описывает потоки ввода/вывода

Author:
    JulesIMF

Last Edit:
    15.10.2020 20:15

Edit Notes:

*/

#include <stdio.h>

#ifndef _JCPU_STREAMS
#define _JCPU_STREAMS

typedef struct
{
    FILE* stream;
} InputStream;

typedef struct
{
    FILE* stream;
} OutputStream;

int str_printf(OutputStream* stream, char const* ptr, ...);
int str_scanf(InputStream*   stream, char const* ptr, ...);

InputStream*    newInputStream();
OutputStream*   newOutputStream();
void            deleteInputStream (InputStream*  stream);
void            deleteOutputStream(OutputStream* stream);

#endif // !_JCPU_STREAMS
