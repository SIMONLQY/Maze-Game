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

// �������ⲿ�ļ�������Ҫ���õĺ���
// �����Թ�, returnһ���Թ�����
extern void CreateMaze();
// ���ó�����
extern void SetPointRand();
extern void SetStartPoint(int x = 1, int y = 1);
extern void SetEndPoint(int x = gMazeHeight, int y = gMazeWidth);


/************************************/
// �����Թ�����
void CreateMatrix();

void InitSquare();
void UpdateMatrix();
void InitMatrix();

void InitBlueAssemble();
// ����number��number���Թ���ȥ�����������ν�һ��������һ
void ResetBlueAssemble(int number);
void AddBlueAssemble(MazeSquare square);
void FinishMaze();
bool CheckFinal(int choice);
void Clean();
