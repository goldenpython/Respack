/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#include "BuildResPack.h"

void AddFile(FILE *fileResPack, char *szFileName, int *iFileSize) {
	char buffer[BUFFER_SIZE];
	int BytesRead;

	*iFileSize = 0;

	FILE *f = fopen(szFileName, "rb");

	do {
		BytesRead = (int)fread(buffer, sizeof(char), BUFFER_SIZE, f);
		fwrite(buffer, sizeof(char), BytesRead, fileResPack);
		*iFileSize += BytesRead;
	} while (BytesRead == BUFFER_SIZE);

	fclose(f);
}

void AddString(FILE *fileResPack, char *szString, int *iStringSize) {
	fwrite(szString, *iStringSize = (int)strlen(szString), 1, fileResPack);
}



void BuildRespackFile(struct RESPACK_FILE_PROPERTIES prop, struct FILE_LIST_ELEMENT *FileList, int iNoFiles) {
	switch (prop.format) {
		case 0:
			BuildRespackFile0(prop, FileList, iNoFiles);
			break;
	}
}

char *GetDefineName(char *dest, char *src) {
	sprintf(dest, "__%s__", src);
	for (char *p = dest; *dest; dest++)
		if (*dest == '.')
			*dest = '_';

	return dest;
}

void WriteCommentSection(FILE *f) {
	char buffer[MAX_LINE_LEN];

	sprintf(buffer, "**** Generated by %s ****", STRING_DESCRIPTION);
	int len = (int)strlen(buffer);

	*buffer = '/';
	memset(buffer + 1, '*', len - 1);
	buffer[len] = '\0';
	fprintf(f, buffer);
	fprintf(f, "\n");

	sprintf(buffer, "**** Generated by %s ****", STRING_DESCRIPTION);
	fprintf(f, buffer);
	fprintf(f, "\n");

	memset(buffer, '*', len - 1);
	buffer[len - 1] = '/';
	buffer[len] = '\0';
	fprintf(f, buffer);
	fprintf(f, "\n\n");
}

void GenerateHeaderFileCPP(char *szFileName, struct FILE_LIST_ELEMENT *FileList, int iNoFiles) {
	char buffer[MAX_LINE_LEN];
	char szDefineName[MAX_LINE_LEN];

	GetDefineName(szDefineName, szFileName);

	FILE *f = fopen(szFileName, "wt");

	WriteCommentSection(f);

	sprintf(buffer, "#ifndef %s\n", szDefineName);
	fprintf(f, buffer);
	sprintf(buffer, "#define %s\n\n", szDefineName);
	fprintf(f, buffer);

	for (int i = 0; i < iNoFiles; i++) {
		sprintf(buffer, "#define\t\t%s\t\t\t%d\n", FileList[i].szSectionName, i);
		fprintf(f, buffer);
	}

	sprintf(buffer, "\n\n#endif //%s", szDefineName);
	fprintf(f, buffer);

	fclose(f);
}

char *GetFileName(char *szPath) {
	char *szFileName = szPath + strlen(szPath) - 1;

	while (szFileName > szPath) {
		if (*szFileName == '\\' || *szFileName == '/')
			return szFileName + 1;

		szFileName--;
	}

	return szFileName;
}
void GenerateHeaderFileJAVA(char *szFileName, struct FILE_LIST_ELEMENT *FileList, int iNoFiles) {
	char buffer[MAX_LINE_LEN];
	char szClassName[MAX_LINE_LEN];

	strcpy(szClassName, GetFileName(szFileName));
	char *p = strchr(szClassName, '.');
	if (*p)
		*p = '\0';

	FILE *f = fopen(szFileName, "wt");

	WriteCommentSection(f);

	sprintf(buffer, "public class %s\n{\n", szClassName);
	fprintf(f, buffer);
	for (int i = 0; i < iNoFiles; i++) {
		sprintf(buffer, "\tpublic final static int %s = %d;\n", FileList[i].szSectionName, i);
		fprintf(f, buffer);
	}

	fprintf(f, "}\n");

	fclose(f);
}

void GenerateHeaderFile(char *szFileName, enum HEADER_FILE_FORMAT format, struct FILE_LIST_ELEMENT *FileList, int iNoFiles) {
	switch (format) {
		case FILE_CPP:
			GenerateHeaderFileCPP(szFileName, FileList, iNoFiles);
			break;
		case FILE_JAVA:
			GenerateHeaderFileJAVA(szFileName, FileList, iNoFiles);
			break;				
	}
}