#pragma once
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include "global_constant.h"
#include "struct.h"
extern int gMazeHeight;
extern int gMazeWidth;
/************************************/

// 以下是外部文件可能需要调用的函数
// 生成迷宫, return一个迷宫矩阵
extern void CreateMaze();
// 设置出发点
extern void SetPointRand();
extern void SetStartPoint(int x = 1, int y = 1);
extern void SetEndPoint(int x = gMazeHeight, int y = gMazeWidth);


/************************************/
// 生成迷宫矩阵
void CreateMatrix();

void InitSquare();
void UpdateMatrix();
void InitMatrix();

void InitBlueAssemble();
// 输入number，number号迷宫格去掉，后面依次进一，数量减一
void ResetBlueAssemble(int number);
void AddBlueAssemble(MazeSquare square);
void FinishMaze();
bool CheckFinal(int choice);
void Clean();
