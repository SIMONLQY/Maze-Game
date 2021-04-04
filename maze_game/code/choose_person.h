#pragma once
#include "global_constant.h"
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <atlstr.h>
#include "struct.h"
#include "global_constant.h"
#include "math.h"
#pragma comment(lib,"Winmm.lib") // ÒýÓÃ Windows Multimedia API


extern void ChoosePerson();

void DrawLeftPart();
void DrawRightPart();
void DrawPersonWhileChoose();
void DrawMiddleCircle();
void CheckHoverInput();
void DrawMiddleCross();
void CheckScrollInput();
void DrawOnePerson(int number, int deviation,
	int x_position);
int chooseLeft(int num);
int chooseRight(int num);
void DrawName();
void DrawTitle();
void DrawGoButton();
void DrawSkills(int person_num);
void DrawRightTitle();
void Wait(int num);
void DrawReturnLast();
void ChooseCheckIfHave();
static void CheckKeyboardInput();