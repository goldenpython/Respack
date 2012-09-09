/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#ifndef __CONSTANTS__H__
#define __CONSTANTS__H__

#define STRING_SINTAX					"Invalid sintax. Sintax is:\n\trespack.exe resfile" 
#define STRING_COULD_NOT_FIND_FILE		"Could not find file: %s"
#define STRING_NO_FORMAT_SPECIFIED		"No output format specified"
#define STRING_INVALID_OUTPUT_FORMAT	"Invalid output format"

#define CHAR_REMARK		'#'
#define CHAR_PROPERTY	'-'
#define CHAR_FILE		'+'

#define STRING_SEPARATOR					"- \t=\n"
#define STRING_SEPARATOR_1					"\""
#define STRING_PROPERTY_FORMAT				"FORMAT"
#define STRING_PROPERTY_OUTPUT_FILE			"OUTPUT"
#define STRING_PROPERTY_HEADER_FILE			"HEADER_FILE"
#define STRING_PROPERTY_HEADER_FILE_FORMAT	"HEADER_FILE_FORMAT"

#define STRING_HEADER_FILE_FORMAT_CPP					"C"
#define STRING_HEADER_FILE_FORMAT_JAVA					"JAVA"

#define STRING_PROPERTY_ERROR				"Invalid property at line %d"
#define STRING_NO_FILE_SPECIFIED			"No file specified at line %d"
#define STRING_FILE_DOES_NOT_EXISTS			"The file %s specified at line %d does not exist"
#define STRING_NO_SECTION_NAME				"No section name specified for file %s at line %d"
#define STRING_INVALID_HEADER_FILE_FORMAT	"Invalid header file format specified at line %d"

#define STRING_MISSING_APOSTROPHE			"Missing '\"' for end of string at line %d"

#define STRING_NO_HEADER_FILE_SPECIFIED			"No header file specified"
#define STRING_NO_HEADER_FILE_FORMAT_SPECIFIED	"No header file format specified"

#define STRING_INVALID_LINE					"Error at line %d"

#define STRING_DESCRIPTION					"Respack Version 0.0.1"

#endif //__CONSTANTS__H__
