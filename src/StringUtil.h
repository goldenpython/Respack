/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#ifndef __STRINGUTIL__H__
#define __STRINGUTIL__H__

#include <string.h>
#include "constants.h"
#include "defines.h"
#include "error.h"

char *RemoveRemarks(char *szLine);
enum LINE_TYPE GetLineType(char *szLine);
enum PROPERTIES GetLinePropertyType(int iLineNo, char *szLine);
char *GetLinePropertyValue(int iLineNo, char *szLine);
enum HEADER_FILE_FORMAT GetHeaderFileFormat(int iLineNo, char *szLine);
char *ProcessStringWithWildmarks(char *szText);

#endif //__STRINGUTIL__H__
