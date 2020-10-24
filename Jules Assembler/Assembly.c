/*
Copyright (c) 2020  MIPT

Module Name:
    Assembly.c

Abstract:


Author:
    JulesIMF

Last Edit:
    22.10.2020

Edit Notes:

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Assembly.h"
#include "Parsing.h"
#include "../Common.h"
#include "../Hash.h"    

void writeSignature(ByteCode* bytecode, ProgramParameters parameters)
{
    jbcSignature signature;
    signature.signature = 'EXEJ';
    signature.stackSize = parameters.stackSize;
    for (int i = 0; i != 8; i++)
        signature.INT[i] = parameters.IRQ[i];
    
    signature.asmVersion = _JCPU_ASM_VERSION;
    signature.checksum = getHash(bytecode->code + _JCPU_SIGNATURE_SIZE, bytecode->programSize - _JCPU_SIGNATURE_SIZE);
    assert(bytecode->code);
    *(jbcSignature*)(bytecode->code) = signature;
}

static void putToListing(FILE* file, int realRip, Instruction instruction, Line line)
{
    fprintf(file, "0x%08X  (0x%08X)\t%-20s\t", realRip, (int)(realRip - _JCPU_SIGNATURE_SIZE), line.string);
    for (int i = 0; i != instruction.length; i++)
    {
        fprintf(file, "%02X ", instruction.code[i] & 255);
    }

    fprintf(file, "\n");
}


static FILE* initListing(char const* asmName, ProgramParameters parameters)
{
    int asmName_size = strlen(asmName);
    char const* addName = " - listing.txt";
    char* listingName = (char*)calloc(asmName_size + 17, sizeof(char));
    strcpy(listingName, asmName);
    strcat(listingName, addName);
    FILE* file = fopen(listingName, "w");
    fprintf(file, "Listing file for \"%s\" assembly\n\n", asmName);
    
    fprintf(file, "Program size = %lld\nStack size   = %lld\n", parameters.programSize, parameters.stackSize);
    fprintf(file,
        "\n\n\n--------------------------------------------------------------------------------------------------------------\n"
        "real RIP    virtual RIP         mnemonics               byte code\n"
        "--------------------------------------------------------------------------------------------------------------\n");

    return file;
}

ByteCode getByteCode(Line* lines, size_t nLines, char const* asmName)
{
    ByteCode byteCode = {NULL, 0};
    ProgramParameters parameters = getProgramParameters(lines, nLines);
    if (parameters.programSize == -1)
        return byteCode;

    byteCode.programSize = _JCPU_SIGNATURE_SIZE + parameters.programSize;
    byteCode.code = (byte*)calloc(byteCode.programSize, sizeof(byte));
    FILE* listingFile = initListing(asmName, parameters);
    int realRip = _JCPU_SIGNATURE_SIZE;

    for (int i = 0; i != nLines; i++)
    {
        if (isLabel(lines[i]))
        {
            fprintf(listingFile, "%s\n", lines[i].string);
            continue;
        }
        if (
            !lines[i].size ||
            isIntSet(lines[i]) ||
            isStackSet(lines[i])
            )
        {
            continue;
        }

        Instruction instruction = getInstruction(lines[i], i + 1, parameters.labels, parameters.nLabels);
        if (!instruction.length)
        {
            byteCode.programSize = 0;
            return byteCode;
        }
        
        putToListing(listingFile, realRip, instruction, lines[i]);
        for (int i = 0; i != instruction.length; i++)
        {
            assert(realRip < byteCode.programSize);
            byteCode.code[realRip++] = instruction.code[i];
        }
    }

    writeSignature(&byteCode, parameters);
    return byteCode;
}
