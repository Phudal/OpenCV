#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <stdio.h>

char* GetPureFileName(char* strFileName);
void ByRuvendisOpenFile(FILE** ppFile, char* strFileName, const char* pMode);
void ByRuvendixCloseFile(FILE* pFile);

#endif