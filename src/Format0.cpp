/*******************************************************************************
*    Cristian Alexandrescu                                                     *
*    2163013577ba2bc237f22b3f4d006856                                          *
*    11a4bb2c77aca6a9927b85f259d9af10db791ce5cf884bb31e7f7a889d4fb385          *
*    bc9a53289baf23d369484f5343ed5d6c                                          *
*******************************************************************************/


#include "Format0.h"

void BuildRespackFile0(struct RESPACK_FILE_PROPERTIES prop, struct FILE_LIST_ELEMENT *FileList, int iNoFiles) {
	FILE *f = fopen(prop.szOutputFile, "wb");

	printf("Creating file %s\n", prop.szOutputFile);

	int size;
	fwrite(&size, sizeof(size), 1, f);

	fwrite(&prop.format, sizeof(prop.format), 1, f);
	fwrite(&iNoFiles, sizeof(iNoFiles), 1, f);

	int *offsets = new int[iNoFiles + 1];

	fwrite(offsets, sizeof(int) * (iNoFiles + 1), 1, f);

	offsets[0] = sizeof(int) * 3 + sizeof(int) * (iNoFiles + 1);
	for (int i = 0; i < iNoFiles; i++) {
		if (FileList[i].bText) {
			AddString(f, FileList[i].szFileName, &offsets[i + 1]);
			printf("\tAddind string \"%s\"\n", FileList[i].szFileName);
		} else {
			AddFile(f, FileList[i].szFileName, &offsets[i + 1]);
			printf("\tAddind file %s\n", FileList[i].szFileName);
		}

		offsets[i + 1] += offsets[i];
	}

	fseek(f, 0, SEEK_SET);
	fwrite(&offsets[iNoFiles], sizeof(int), 1, f);

	fseek(f, sizeof(int) * 3, SEEK_SET);
	fwrite(offsets, sizeof(int) * (iNoFiles + 1), 1, f);

	fclose(f);

	printf("\tGenerating %s file\n", prop.szHeaderFile);
	GenerateHeaderFile(prop.szHeaderFile, prop.HeaderFormat, FileList, iNoFiles);

	printf("DONE\n");

	delete []offsets;
}