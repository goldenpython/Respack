/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#ifndef __DEFINES__H__
#define __DEFINES__H__

enum BOOLEAN {
	FALSE = 0,
	TRUE = 1
};

enum LINE_TYPE {
	LINE_TYPE_FILE = 0,
	LINE_TYPE_PROPERTY = 1,
	LINE_TYPE_BLANK = 2
};

enum PROPERTIES {
	PROPERTY_OUTPUT_FILE = 0,
	PROPERTY_FORMAT = 1,
	PROPERTY_HEADER_FILE = 2,
	PROPERTY_HEADER_FILE_FORMAT = 3,
	PROPERTY_ERROR = 101
};

enum HEADER_FILE_FORMAT {
	FILE_NO_FORMAT = 0,
	FILE_CPP = 1,
	FILE_JAVA = 2
};

struct RESPACK_FILE_PROPERTIES {
	int format;
	char *szOutputFile;
	char *szHeaderFile;
	enum HEADER_FILE_FORMAT HeaderFormat;
};

struct FILE_LIST_ELEMENT {
	char *szFileName;
	char *szSectionName;
	enum BOOLEAN bText;
};

#define MAX_FILE_NAME_LEN				255
#define MAX_ERROR_MESSAGE_LEN			255
#define MAX_LINE_LEN					1024

#define FILE_LIST_INITIAL_LEN			10
#define FILE_LIST_INCREMENT_SIZE		5

#endif //__DEFINES__H__
