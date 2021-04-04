#pragma once
#include "global_constant.h"
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <atlstr.h>
#include "struct.h"
#include "global_constant.h"
#include "math.h"
#include "money.h"
#include "person.h"
#pragma comment(lib,"Winmm.lib") // ÒýÓÃ Windows Multimedia API

extern void ShowStore();

void StoreDrawLeftPart();
void StoreDrawRightPart();
void StoreDrawPersonWhileChoose();
void StoreDrawMiddleCircle();
void StoreCheckHoverInput();
void StoreDrawMiddleCross();
void StoreCheckScrollInput();
void StoreDrawOnePerson(int number, int deviation,
	int x_position);
int StorechooseLeft(int num);
int StorechooseRight(int num);
void StoreDrawName();
void StoreDrawTitle();
void StoreDrawGoButton();
void StoreDrawSkills(int person_num);
void StoreDrawRightTitle();
void StoreWait(int num);
void StoreDrawReturnLast();
void StoreDrawMoney();
int GetNumLen(int num);
void StoreDrawPersonMoney();
void CheckIfHave();
static void CheckKeyboardInput();