#pragma once
#include <atlstr.h>
#include <graphics.h>
#include <string>

// ����
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
// �Թ�����
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
// ��ɫ�鼯��
struct BlueAssemble {
	int num;
	MazeSquare* blue_squares;
};

