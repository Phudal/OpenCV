#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <Windows.h>
#include "FileIO.h"

#pragma warning (disable:4996)

typedef enum _State
{
	PLAY, STOP
}STATE;

double CheckTime(LARGE_INTEGER* pLastTime, LARGE_INTEGER* pNowTime, LARGE_INTEGER* pFrequency)
{
	double dTimeInterval;

	QueryPerformanceCounter(pNowTime);

	dTimeInterval =
		((double)(pNowTime->QuadPart - pLastTime->QuadPart) / (double)pFrequency->QuadPart);
	pLastTime->QuadPart = pNowTime->QuadPart;

	return dTimeInterval;
}

int main(int argc, char* argv[])
{
	char Buffer[500];
	char cLF;
	char FindPath[100];
	int iResult = 0;
	double dResult = 0.0;
	STATE eState = PLAY;
	FILE* pASCIIART = NULL;
	intptr_t FileHandle;
	LARGE_INTEGER LastTime, NowTime, Frequency;
	COORD CursorPos = { 0,0 };
	struct _finddata_t FindASCIIArt;

	QueryPerformanceFrequency(&Frequency);

	QueryPerformanceCounter(&LastTime);

	while (true)
	{
		strcpy(FindPath, argv[1]);
		strcat(FindPath, "\\*.txt");

		FileHandle = _findfirst(FindPath, &FindASCIIArt);

		if (FileHandle == -1)
		{
			perror("파일 핸들 가져오기 실패");
			return 0;
		}

		iResult = 0;

		while (iResult != -1)
		{
			if (eState == PLAY)
			{
				strcpy(FindPath, argv[1]);
				strcat(FindPath, "\\");
				strcat(FindPath, FindASCIIArt.name);

				ByRuvendisOpenFile(&pASCIIART, FindPath, "rt");

				while (feof(pASCIIART) == 0)
				{
					fscanf(pASCIIART, "%[^\n]s", Buffer);
					fscanf(pASCIIART, "%c", &cLF);
					puts(Buffer);
				}
				ByRuvendixCloseFile(pASCIIART);
				eState = STOP;
			}

			dResult += CheckTime(&LastTime, &NowTime, &Frequency);

			if (dResult >= 1.0 / 14.0)
			{
				dResult = 0.0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPos);

				iResult = _findnext(FileHandle, &FindASCIIArt);

				eState = PLAY;
			}
		}
		_findclose(FileHandle);
	}
	return 0;
}