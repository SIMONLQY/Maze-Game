#pragma once
#include <atlstr.h>
#include "global_constant.h"
// ȫ�ֱ���ǰ���g
int gMazeWidth = 15; // ��ȷ����м���,�������ɷ������⣬���ֻ��Ϊ
                     // 2n + 1�������ȷ���ͬ
int gMazeHeight = 15; // ���ȷ����м���
int gMazeSquareLength = 40; // ÿ������ı߳������أ�
int gMazeGapBetween = 3; // ÿ��������֮��ı߳���϶
int gGameScreenChangeSpeed = 20;
int gScreenScrollSpeed = 20;
int gScene = BeginPage;
//int fog_range = 8;
CString gPersonName;



// һЩ�м�ȫ�ֱ������������
int gCurrentPerson;
int gSquareColor;
int gPrize;
int gMazeStartX;
int gMazeStartY;
int gMazeEndX;
int gMazeEndY;
int currTheme;
bool is_reach;
int closeNum;
int* gPersonHave;
int* gPersonMoney;
int sillLeftTime0;
int sillLeftTime1;
int sillLeftTime2;
int sillLeftTime3;


