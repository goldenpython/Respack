/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#include "FileUtil.h"

BOOLEAN FileExists(char *szFileName) {
	FILE *f = fopen(szFileName, "rb");
	if (!f)
		return FALSE;

	fclose(f);

	return TRUE;
}

int GetFileSize(char *szFileName) {
	FILE *f = fopen(szFileName, "rb");

	if (!f)
		return -1;

	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fclose(f);

	return len;
}

