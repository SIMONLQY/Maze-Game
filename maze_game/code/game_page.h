#pragma once
#include "create_maze.h"
#include "global_constant.h"
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <atlstr.h>
#include "struct.h"
//#include "get_through_path.h"
#include "skills.h"
#include "time.h"
#include "money.h"
#pragma comment(lib,"Winmm.lib") // ÒýÓÃ Windows Multimedia API

extern void GamePage();

void InitPage();
void DrawMaze();
void HideOverFlow();


void DrawPerson();
void InitPerson();
void GetInput();
bool CheckHit();
void InitCorner();
void DrawGameRightPart();
void CheckSucceed();

void DrawGameSkills(int person_num);
void DrawGameRightTitle();
void DrawGameReturnLast();
void GetMouseInput();
void CheckTime();
void CheckRemainTime();
void CheckStep();
void DrawBoard();
void CheckFailed();
void DrawRightPic();
void InitAllGameSettings();
void MoveFirst();
void DrawPersonFirst();
void playBackMusic();