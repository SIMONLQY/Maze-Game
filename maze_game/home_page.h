#pragma once
#include <graphics.h>
#include <conio.h>
#include "global_constant.h"
#include<stdlib.h>
#include <math.h>
#include <atlstr.h>
#include "struct.h"
#include "time.h"
#pragma comment(lib,"Winmm.lib") // 引用 Windows Multimedia API
// 进入初始界面，该函数为入口函数，调用此函数即可进入主页面
extern void ShowHomePage();

void startup();
void showWelcome();
void showStart();
void click();