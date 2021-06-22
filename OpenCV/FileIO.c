#include <stdlib.h>
#include <string.h>
#include "FileIO.h"

#pragma warning (disable:4996)

char* GetPureFileName(char* strFileName)
{
	char* pToken[10];
	int iIndex = 0;

	pToken[iIndex++] = strtok(strFileName, "\\");
	while (pToken[iIndex - 1] != NULL)
	{
		pToken[iIndex++] = strtok(NULL, "\\");
	}
	return pToken[iIndex - 2];
}

void ByRuvendisOpenFile(FILE** ppFile, char* strFileName, const char* pMode)
{
	*ppFile = fopen(strFileName, pMode);
	if (*ppFile == NULL)
	{
		perror("���� ��Ʈ�� ���� ����!");
		exit(EXIT_FAILURE);
	}
}

void ByRuvendixCloseFile(FILE* pFile)
{
	if (fclose(pFile) == EOF)
	{
		perror("���� ��Ʈ�� ���� ����!");
		exit(EXIT_FAILURE);
	}
}


