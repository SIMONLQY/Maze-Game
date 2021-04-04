#pragma once
#include <Windows.h>  
#include <Endpointvolume.h>  
#include <Mmdeviceapi.h> 
#include <graphics.h>
#include <conio.h>
#include "global_constant.h"

//ÒýÓÃWindows Multimedia API
#pragma comment(lib, "Winmm.lib")


extern void set();
void start_up();
void showset();
void set_music();
void SetDrawReturnLast();
void SetCheckHoverInput();

