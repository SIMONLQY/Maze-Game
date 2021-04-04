#pragma once
#include <atlstr.h>
#include <graphics.h>
#include <string>

// 人物
struct Person {
	CString name;
	int x;;
	int y;
	bool is_move;

	IMAGE img;
	IMAGE img_black;
	int img_width;
	int img_height;

	int skill1;
	int skill2;
};
// 迷宫矩阵
struct MazeSquare {
	int x;
	int y;
	int color;
	int g;
	int h;
	bool isInClose;
	bool isInOpen;
	bool special;
	MazeSquare* parent;
};
// 蓝色块集合
struct BlueAssemble {
	int num;
	MazeSquare* blue_squares;
};

