#pragma once
#include "Line.h"
/**
 * \brief ��������� ���� � RAM � ��������� 0 ����� ����, ��� ���� ����� 0 ���� ��� ���� ��������� ����.
 *
 * \param fileName ����������� ����
 * \param fileSize ��������� �� ����������, � ������� ����� ������� ������ �����
 * \param nStrings ��������� �� ����������, � ������� ����� �������� ���������� �����
 * \return ��������� �� ������� ������, � ������� �������� ����, 0 � ������ ������
 */
void* translateFileIntoRam(char const* fileName, int* pFileSize);


/**
 * \brief ������� ������ ����� � ����.
 * \param fileName ������ � ������ ����� ("?" ��� stdout)
 * \param strings ������ �����
 * \param nStrings ��������� ����� � �������
 * \param mode ����� �������� �����
 * \return 0 � ������ ��������� ����������, 1 � ������ ������ �������� �����
 */
int write(char const* fileName, Line* strings, int nStrings, char const* mode);


/**
 * \brief ���������� ������ �����
 * \param file ����������� ����
 * \return ������ ����� � ������.
 */
int getFileSize(FILE* file);


/**
 * \brief ��������� source �� ������ � destination.
 * \param source ��������� �� ��������������� ����
 * \param fileSize ������ ���������������� �����
 * \param destination ��������� �� ������ �� ��������
 * \param nStrings ���������� �����
 * \warning source �� ��������������!!
 * \warning ������ *stringsLengths ��������������!!
 * \return 0 � ������ ��������� ����������, 1 ���� �������� �������������� ���������, 2 ���� ���� ������ ������� 100
 */
int separateStrings(void* source, int fileSize, Line* destination, int nStrings);


/**
 * �������� ������ ������������� ������ �������� ������, ���� ������� ����, �����.
 * \param line ������
 */
void replaceNewLine(char* line);
