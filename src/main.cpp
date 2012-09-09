/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "defines.h"

#include "FileUtil.h"
#include "StringUtil.h"
#include "BuildResPack.h"

void ParseArguments(char *szFileName, int argc, char **argv) {
	if (argc < 2) {
		ErrorAndExit(STRING_SINTAX);
	}

	strcpy(szFileName, argv[1]);
}

BOOLEAN IsFormatValid(int format) {
	if (format != 0)
		return FALSE;
	else
		return TRUE;
}

void ParsePropertyLine(int iLineNo, char *szLine, struct RESPACK_FILE_PROPERTIES *ResProp) {
	enum PROPERTIES prop = GetLinePropertyType(iLineNo, szLine);
	char *p;

	switch (prop) {
		case PROPERTY_FORMAT:
			p = GetLinePropertyValue(iLineNo, szLine);
			if (sscanf(p, "%d", &ResProp->format) != 1) {
				ErrorAndExit(STRING_NO_FORMAT_SPECIFIED);

				if (!IsFormatValid(ResProp->format))
					ErrorAndExit(STRING_INVALID_OUTPUT_FORMAT);
			}

			delete(p);

			break;

		case PROPERTY_OUTPUT_FILE:
			ResProp->szOutputFile = GetLinePropertyValue(iLineNo, szLine);
			break;

		case PROPERTY_HEADER_FILE:
			ResProp->szHeaderFile = GetLinePropertyValue(iLineNo, szLine);
			break;

		case PROPERTY_HEADER_FILE_FORMAT:
			ResProp->HeaderFormat = GetHeaderFileFormat(iLineNo, GetLinePropertyValue(iLineNo, szLine));
			break;

		case PROPERTY_ERROR:
			char buffer[MAX_LINE_LEN];
			sprintf(buffer, STRING_PROPERTY_ERROR, iLineNo);
			ErrorAndExit(buffer);
			break;
	}
}

void ParseFileLine(int iLineNo, char *szLine, struct FILE_LIST_ELEMENT **FileList, int *iNoFiles, int *iCapacity) {
	char buffer[MAX_LINE_LEN];

	szLine++;

	enum BOOLEAN bString = FALSE;
	char *pFirstQuote, *pLastQuote;

	if (pFirstQuote = strchr(szLine, '"')) {
		bString = TRUE;


		char *aux;
		for (pLastQuote = pFirstQuote; aux = strchr(pLastQuote + 1, '"'); pLastQuote = aux)
			;

		if (pLastQuote == pFirstQuote) {
			sprintf(buffer, STRING_MISSING_APOSTROPHE, iLineNo);
			ErrorAndExit(buffer);
		}
	}

	char *p;
	
	if (!bString) {
		p = strtok(szLine, STRING_SEPARATOR);

		if (!p) {
			sprintf(buffer, STRING_NO_FILE_SPECIFIED, iLineNo);
			ErrorAndExit(buffer);
		}

		if (!FileExists(p)) {
			sprintf(buffer, STRING_FILE_DOES_NOT_EXISTS, p, iLineNo);
			ErrorAndExit(buffer);
		}
	}

	if (*iNoFiles == *iCapacity) {
		*iCapacity += 10;
		*FileList = (struct FILE_LIST_ELEMENT *)realloc(*FileList, sizeof(struct FILE_LIST_ELEMENT) * (*iCapacity));
	}

	memset(&(*FileList)[*iNoFiles], 0, sizeof(FILE_LIST_ELEMENT));

	if (!bString)
		(*FileList)[*iNoFiles].szFileName = strdup(p);


	if (!bString)
		p = strtok(NULL, STRING_SEPARATOR);
	else
		p = strtok(pLastQuote + 1, STRING_SEPARATOR);

	if (!p) {
		sprintf(buffer, STRING_NO_SECTION_NAME, (*FileList)[*iNoFiles].szFileName, iLineNo);
		ErrorAndExit(buffer);
	}

	if (bString) {
		(*FileList)[*iNoFiles].bText = TRUE;
		*pLastQuote = '\0';
		//ca (*FileList)[*iNoFiles].szFileName = strdup(pFirstQuote + 1);
		(*FileList)[*iNoFiles].szFileName = ProcessStringWithWildmarks(pFirstQuote + 1);
	}

	(*FileList)[*iNoFiles].szSectionName = strdup(p);
	(*iNoFiles)++;
}

BOOLEAN CheckFormat0(struct RESPACK_FILE_PROPERTIES prop) {
	if (!prop.szHeaderFile)
		ErrorAndExit(STRING_NO_HEADER_FILE_SPECIFIED);

	if (prop.HeaderFormat == FILE_NO_FORMAT)
		ErrorAndExit(STRING_NO_HEADER_FILE_FORMAT_SPECIFIED); 

	return TRUE;
}

BOOLEAN CheckFileValidity(struct RESPACK_FILE_PROPERTIES prop) {
	switch (prop.format) {
		case 0:
			return CheckFormat0(prop);
			break;
	}

	return FALSE;
}

void ProcessFile(char *szFileName) {
	if (!FileExists(szFileName)) {
		char sz_buf[MAX_ERROR_MESSAGE_LEN];
		sprintf(sz_buf, STRING_COULD_NOT_FIND_FILE, szFileName);
		ErrorAndExit(sz_buf);
	}

	FILE *f = fopen(szFileName, "rt");

	char szLine[MAX_LINE_LEN];
	int iLineNo = 0;
	struct RESPACK_FILE_PROPERTIES prop = {-1, NULL, NULL, FILE_NO_FORMAT};

	struct FILE_LIST_ELEMENT *FileList = (struct FILE_LIST_ELEMENT *)malloc(sizeof(struct FILE_LIST_ELEMENT) * FILE_LIST_INITIAL_LEN);
	int iNoFiles = 0;
	int iCapacity = FILE_LIST_INITIAL_LEN;

	while (iLineNo++, fgets(szLine, MAX_LINE_LEN, f)) {
		RemoveRemarks(szLine);

		enum LINE_TYPE type = GetLineType(szLine);

		switch (type) {
			case LINE_TYPE_PROPERTY:
				ParsePropertyLine(iLineNo, szLine, &prop);
				break;

			case LINE_TYPE_FILE:
				ParseFileLine(iLineNo, szLine, &FileList, &iNoFiles, &iCapacity);
				break;

			case LINE_TYPE_BLANK:
				break;
		}
	}

	fclose(f);

	CheckFileValidity(prop);

	BuildRespackFile(prop, FileList, iNoFiles);

	free(FileList);
}

int main(int argc, char **argv) {
	char szFileName[MAX_FILE_NAME_LEN];

	ParseArguments(szFileName, argc, argv);

	ProcessFile(szFileName);
}