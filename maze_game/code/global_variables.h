#pragma once
#include <atlstr.h>
#include "global_constant.h"
// 全局变量前面加g
int gMazeWidth = 15; // 宽度方向有几格,由于生成方法问题，因此只能为
                     // 2n + 1个。长度方向同
int gMazeHeight = 15; // 长度方向有几格
int gMazeSquareLength = 40; // 每个方格的边长（像素）
int gMazeGapBetween = 3; // 每两个方格之间的边长空隙
int gGameScreenChangeSpeed = 20;
int gScreenScrollSpeed = 20;
int gScene = BeginPage;
//int fog_range = 8;
CString gPersonName;



// 一些中间全局变量，无需操作
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


