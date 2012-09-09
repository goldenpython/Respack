/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/

#ifndef __BUILD_RESPACK__H__
#define __BUILD_RESPACK__H__

#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "constants.h"
#include "Format0.h"

#define BUFFER_SIZE		1024

void BuildRespackFile(struct RESPACK_FILE_PROPERTIES prop, struct FILE_LIST_ELEMENT *FileList, int iNoFiles);
void AddFile(FILE *fileResPack, char *szFileName, int *iFileSize);
void AddString(FILE *fileResPack, char *szString, int *iStringSize);
void GenerateHeaderFile(char *szFileName, enum HEADER_FILE_FORMAT format, struct FILE_LIST_ELEMENT *FileList, int iNoFiles);

#endif __BUILD_RESPACK__H__
