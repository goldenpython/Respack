/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#include "StringUtil.h"

char *RemoveRemarks(char *szLine) {
	char *p = strchr(szLine, CHAR_REMARK);
	if (p) {
		*p = '\0';
		for (char *ps = szLine; *ps; ps++)
			if (!strchr(STRING_SEPARATOR, *ps)) {
				*p = CHAR_REMARK;
				return szLine;
			}
	}
	return szLine;
}

enum LINE_TYPE GetLineType(char *szLine) {
	switch (*szLine) {
		case CHAR_PROPERTY:
			return LINE_TYPE_PROPERTY;

		case CHAR_FILE:
			return LINE_TYPE_FILE;
	}

	return LINE_TYPE_BLANK;
}

enum PROPERTIES GetLinePropertyType(int iLineNo, char *szLine) {
	char buffer[MAX_LINE_LEN];
	strcpy(buffer, szLine);

	char *p = strtok(buffer, STRING_SEPARATOR);

	if (p) 
		if (!strcmp(p, STRING_PROPERTY_FORMAT)) {
			return PROPERTY_FORMAT;
		} else if (!strcmp(p, STRING_PROPERTY_OUTPUT_FILE)) {
			return PROPERTY_OUTPUT_FILE;
		} else if (!strcmp(p, STRING_PROPERTY_HEADER_FILE)) {
			return PROPERTY_HEADER_FILE;
		} else if (!strcmp(p, STRING_PROPERTY_HEADER_FILE_FORMAT)) {
			return PROPERTY_HEADER_FILE_FORMAT;
		}

	return PROPERTY_ERROR;
};

char *GetLinePropertyValue(int iLineNo, char *szLine) {
	char buffer[MAX_LINE_LEN];
	strcpy(buffer, szLine);

	char *p = strtok(buffer, STRING_SEPARATOR);
	if (!p) {
		sprintf(buffer, STRING_INVALID_LINE, iLineNo);
		ErrorAndExit(buffer);
	}

	p = strtok(NULL, STRING_SEPARATOR);
	if (!p) {
		sprintf(buffer, STRING_INVALID_LINE, iLineNo);
		ErrorAndExit(buffer);
	}

	return strdup(p);
}

enum HEADER_FILE_FORMAT GetHeaderFileFormat(int iLineNo, char *szLine) {
	if (!strcmp(szLine, STRING_HEADER_FILE_FORMAT_JAVA)) 
		return FILE_JAVA;
	else if (!strcmp(szLine, STRING_HEADER_FILE_FORMAT_CPP)) 
		return FILE_CPP;

	char buffer[MAX_LINE_LEN];
	sprintf(buffer, STRING_INVALID_HEADER_FILE_FORMAT, iLineNo);
	ErrorAndExit(buffer);

	return FILE_NO_FORMAT;
}

char *ProcessStringWithWildmarks(char *szText) {
	if (!szText || !*szText)
		return NULL;

	int len = 0;
	for (char *p = szText; *p; p++)
		if (*p == '\\' && *(p + 1) == 'n') {
			len++;
			p++;
		} else
			len++;

	char *aux = (char *)malloc(len + 1);
	char *paux = aux;

	for (char *p = szText; *p; p++)
		if (*p == '\\' && *(p + 1) == 'n') {
			*paux++ = '\n';
			p++;
		} else
			*paux++ = *p;

	*paux = '\0';

	return aux;
}

