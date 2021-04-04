#include "choose_person.h"
extern CString gPersonName;
extern int gScreenScrollSpeed;
extern int* gPersonHave;
extern int gScene;
static bool is_have = 0;
static int current_person = 0;
static bool if_back = false;
extern int gCurrentPerson;

static int scroll_times = 0;
static int button_show = 0; // 0�ޣ�1hover��2click
static int return_show = 0; // 0�ޣ�1hover��2click

void ChoosePerson() {
	button_show = 0;
	return_show = 0;
	scroll_times = 0;
	mciSendString(_T("open ../sources/music/��ť1.mp3 alias ����"), NULL, 0, NULL);
	mciSendString(_T("close ����"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/��������.mp3 alias ����"), NULL, 0, NULL);
	if_back = false;
	BeginBatchDraw();
	
	while (1) {
		FlushMouseMsgBuffer();
		DrawLeftPart();
		DrawPersonWhileChoose();
		DrawMiddleCircle();
		DrawMiddleCross();
		DrawName();
		DrawTitle();
		DrawGoButton();
		DrawRightPart();
		FlushBatchDraw();
		Wait(10000);
		CheckScrollInput();
		//CheckHoverInput();
		ChooseCheckIfHave();
		CheckKeyboardInput();
		if (if_back) {
			mciSendString(_T("close ����"), NULL, 0, NULL);
			mciSendString(_T("pause ѡ������"), NULL, 0, NULL);
			EndBatchDraw();
			return;
		}
	}
}
void Wait(int num) {
	for (int i = 0; i < num; i++);
}
void DrawLeftPart() {
	setcolor(RGB(48, 48, 48));
	setfillcolor(RGB(48, 48, 48));
	fillrectangle(0, 0, kChoosePersonWidth, 
		kScreenHeight/4);
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillrectangle(0, kScreenHeight / 4, kChoosePersonWidth,
		3*kScreenHeight / 4);
	setcolor(RGB(48, 48, 48));
	setfillcolor(RGB(48, 48, 48));
	fillrectangle(0, 3*kScreenHeight / 4, kChoosePersonWidth,
		kScreenHeight);
}
void DrawRightPart() {
	setcolor(RGB(54, 54, 54));
	setfillcolor(RGB(40, 40, 40));
	fillrectangle(kChoosePersonWidth, 0, 
		kScreenWidth, kScreenHeight);
	DrawSkills(current_person);
	DrawRightTitle();
	DrawReturnLast();
}
void DrawPersonWhileChoose() {
	const char* names[7] = { "��ʿ" , "��ʦ", "�̿�" , "ʥ��ʿ",
		"��Ѫ��", "����", "����"};
	static int deviation = 0;
	int length = 2 * kChoosePersonWidth / 5;
	if (scroll_times != 0) {
		deviation += scroll_times / abs(scroll_times) * gScreenScrollSpeed;
		if (abs(deviation) >= abs(length)) {
			deviation = 0;
			current_person += scroll_times / abs(scroll_times);
			if (scroll_times > 0) {
				scroll_times -= 1;
			}
			else if (scroll_times < 0) {
				scroll_times += 1;
			}
			if (current_person == 7) {
				current_person = 0;
			}
			else if (current_person == -1) {
				current_person = 6;
			}
		}
		if (scroll_times == 0) {
			mciSendString(_T("seek ���� to start"), 0, 0, 0);
			mciSendString(_T("play ����"), NULL, 0, NULL);
		}
	}
	int current_middle = current_person;
	int current_left = chooseLeft(current_middle);
	int current_right = chooseRight(current_middle);
	int middle_x = kChoosePersonWidth / 2;
	DrawOnePerson(current_middle, deviation, middle_x);
	int left_x = kChoosePersonWidth / 10;
	DrawOnePerson(current_left, deviation, left_x);
	int right_x = 9*kChoosePersonWidth / 10;
	DrawOnePerson(current_right, deviation, right_x);
	int right2_x = right_x + length;
	int right2_person = chooseRight(current_right);
	DrawOnePerson(right2_person, deviation, right2_x);
	int left2_x = left_x - length;
	int left2_person = chooseLeft(current_left);
	DrawOnePerson(left2_person, deviation, left2_x);

}
void DrawOnePerson(int number,  int deviation, int x_position) {
	IMAGE img1;
	IMAGE img2;
	const char* names[7] = { "��ʿ" , "��ʦ", "�̿�" , "ʥ��ʿ",
		"��Ѫ��", "����", "����" };
	CString full_src1;
	CString full_src2;
	CString str_l = names[number];
	full_src1.Format(_T("%s%s%s"),
		_T("../sources/pic/����/"),
		str_l, _T(".jpg"));
	full_src2.Format(_T("%s%s%s"),
		_T("../sources/pic/����/"),
		str_l, _T("black.jpg"));
	IMAGE temp1;
	loadimage(&temp1, full_src1);
	int height1 = temp1.getheight();
	int width1 = temp1.getwidth();
	int new_width1 = kPersonWidth;
	int new_height1 = (int)(height1 * (double)kPersonWidth / width1);
	loadimage(&img1, full_src1, new_width1, new_height1);
	loadimage(&img2, full_src2, new_width1, new_height1);

	int put_x = x_position - new_width1 / 2;
	int put_y = kChoosePersonHeight / 2 - new_height1 / 2;
	putimage(put_x + deviation, put_y, &img2, NOTSRCERASE);
	putimage(put_x + deviation, put_y, &img1, SRCINVERT);

}
int chooseLeft(int num) {
	int left;
	if (num == 6) {
		left = 0;
	}
	else {
		left = num + 1;
	}
	return left;
}
int chooseRight(int num) {
	int right;
	if (num == 0) {
		right = 6;
	}
	else {
		right = num - 1;
	}
	return right;
}

void DrawMiddleCircle() {
	int center_x = kChoosePersonWidth / 2;
	int center_y = kChoosePersonHeight / 2;
	setcolor(BLACK);
	circle(center_x, center_y, 105);
	circle(center_x, center_y, 125);
	floodfill(center_x + 115, center_y, BLACK);

}
void DrawMiddleCross() {
	int center_x = kChoosePersonWidth / 2;
	int center_y = kChoosePersonHeight / 2;
	setcolor(BLACK);
	line(center_x - 105, center_y, center_x + 105, center_y);
	line(center_x, center_y - 105, center_x, center_y + 105);
	circle(center_x, center_y, 35);
}
void CheckScrollInput() {
	if (!MouseHit()) {
		return;
	} 
	MOUSEMSG msg = GetMouseMsg();
	int wheel_run = msg.wheel / 120;
	scroll_times += wheel_run;
	if (abs(scroll_times) >= 3) {
		if (scroll_times > 0)
			scroll_times = 3;
		else if (scroll_times < 0)
			scroll_times = -3;
	}




	int x = msg.x;
	int y = msg.y;
	int x_position = kChoosePersonWidth / 2 - kButtonWidth / 2;
	int y_position = 7 * kChoosePersonHeight / 8 - kButtonHeight / 2;
	if (x >= x_position && x <= x_position + kButtonWidth && y >= y_position
		&& y <= y_position + kButtonHeight && is_have && msg.mkLButton) {
		mciSendString(_T("pause ѡ������"), NULL, 0, NULL);
		mciSendString(_T("play ����"), NULL, 0, NULL);
		Sleep(4000);
		button_show = 2;
		gScene = PlayPage;
		if (current_person == 0) {
			gPersonName = _T("��ʿ");
		}
		if (current_person == 1) {
			gPersonName = _T("��ʦ");
		}
		if (current_person == 2) {
			gPersonName = _T("�̿�");
		}
		if (current_person == 3) {
			gPersonName = _T("ʥ��ʿ");
		}
		if (current_person == 4) {
			gPersonName = _T("��Ѫ��");
		}
		if (current_person == 5) {
			gPersonName = _T("����");
		}
		if (current_person == 6) {
			gPersonName = _T("����");
		}
		gCurrentPerson = current_person;
		if_back = true;
	}
	else if (x >= x_position && x <= x_position + kButtonWidth && y >= y_position
		&& y <= y_position + kButtonHeight && is_have) {
		button_show = 1;
	}
	else {
		button_show = 0;
	}
	if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <=
		40 && msg.mkLButton) {
		return_show = 2;
		gScene = ScenePage;
		if_back = true;
	}
	else if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <= 40) {
		return_show = 1;
	}
	else {
		return_show = 0;
	}
}
void CheckHoverInput() {
	if (!MouseHit()) {
		return;
	}
	MOUSEMSG msg = GetMouseMsg();
	int x = msg.x;
	int y = msg.y;
	int x_position = kChoosePersonWidth / 2 - kButtonWidth / 2;
	int y_position = 7 * kChoosePersonHeight / 8 - kButtonHeight / 2;
	if (x >= x_position && x <= x_position + kButtonWidth && y >= y_position
		&& y <= y_position + kButtonHeight && is_have && msg.mkLButton) {
		mciSendString(_T("pause ѡ������"), NULL, 0, NULL);
		mciSendString(_T("play ����"), NULL, 0, NULL);
		Sleep(4000);
		button_show = 2;
		gScene = PlayPage;
		if (current_person == 0) {
			gPersonName = _T("��ʿ");
		}
		if (current_person == 1) {
			gPersonName = _T("��ʦ");
		}
		if (current_person == 2) {
			gPersonName = _T("�̿�");
		}
		if (current_person == 3) {
			gPersonName = _T("ʥ��ʿ");
		}
		if (current_person == 4) {
			gPersonName = _T("��Ѫ��");
		}
		if (current_person == 5) {
			gPersonName = _T("����");
		}
		if (current_person == 6) {
			gPersonName = _T("����");
		}
		gCurrentPerson = current_person;
		if_back = true;
	}
	else if (x >= x_position && x <= x_position + kButtonWidth && y >= y_position
		&& y <= y_position + kButtonHeight && is_have) {
		button_show = 1;
	}
	else {
		button_show = 0;
	}
	if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <=
		40 && msg.mkLButton) {
		return_show = 2;
		gScene = ScenePage;
		if_back = true;
	}
	else if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <= 40) {
		return_show = 1;
	}
	else {
		return_show = 0;
	}
}
void DrawName() {
	TCHAR names[7][20] = { _T("��ʿ") , _T("��ʦ"), _T("�̿�") ,
		_T("ʥ��ʿ"), _T("��Ѫ��"), _T("����"), _T("����") };
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("����"));
	RECT r = { 0, 0, kChoosePersonWidth, kChoosePersonHeight/5};
	drawtext(names[current_person], &r, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	
}
void DrawTitle() {
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("����"));
	outtextxy(5, 20, _T("����ѡ��"));
}
void DrawGoButton() {
	int temp_width = kButtonWidth;
	int temp_height = kButtonHeight;
	int font_size = 40;
	if (is_have == 0) {
		setfillcolor(RGB(189, 183, 107));
	}
	else {
		setfillcolor(RGB(50, 205, 50));
	}
	
	if (button_show != 0) {
		temp_width += 10;
		temp_height += 10;
		font_size += 10;
	}
	if (button_show == 2) {
		setfillcolor(RGB(109, 103, 27));
	}
	int x_position = kChoosePersonWidth / 2 - temp_width / 2;
	int y_position = 7*kChoosePersonHeight/8 - temp_height / 2;
	POINT pts[] = { {x_position, y_position}, {x_position+ temp_width,
		y_position}, {x_position + temp_width +20, 7 * kChoosePersonHeight / 8},
	{x_position + temp_width, y_position + temp_height},
	{x_position, y_position + temp_height},
	{x_position - 20, 7 * kChoosePersonHeight / 8} };
	setcolor(RGB(211, 211, 211));
	
	
	fillpolygon(pts, 6);
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(font_size, 0, _T("����"));
	RECT r = { x_position, y_position, x_position+ temp_width,
		y_position+ temp_height };
	if (is_have == 0) {
		drawtext(_T("δӵ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		drawtext(_T("GO!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	}
}
void DrawSkills(int person_num) {
	int skill_1 = kSkills[person_num][0];
	int skill_2 = kSkills[person_num][1];
	if (skill_1 == 0) {
		setfillcolor(BLACK);
		fillrectangle(kChoosePersonWidth + 20, 200,
			kChoosePersonWidth + 100, 280);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 280, skill0_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth + 110, 220,
			kScreenWidth - 10, 610 };
		drawtext(skill0_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_1 == 1) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/����/Ѱ·.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 200, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 280, skill1_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth + 110, 220,
			kScreenWidth - 10, 610 };
		drawtext(skill1_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_1 == 2) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/����/��Ծ.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 200, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 280, skill2_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth + 110, 220,
			kScreenWidth - 10, 610 };
		drawtext(skill2_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_1 == 3) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/����/�ƻ�.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 200, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 280, skill3_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth+110, 220, 
			kScreenWidth - 10, 610 };
		drawtext(skill3_description, &r, 
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 0) {
		setfillcolor(BLACK);
		fillrectangle(kChoosePersonWidth + 20, 350,
			kChoosePersonWidth + 100, 430);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 430, skill0_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill0_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 1) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/����/Ѱ·.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 430, skill1_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill1_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 2) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/����/��Ծ.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 430, skill2_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill2_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 3) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/����/�ƻ�.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("����"));
		outtextxy(kChoosePersonWidth + 40, 430, skill3_name);
		settextstyle(17, 0, _T("����"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill3_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
}
void DrawRightTitle() {
	settextcolor(YELLOW);
	settextstyle(30, 0, _T("����"));
	outtextxy(kChoosePersonWidth + 10, 120, _T("��������"));
}
void DrawReturnLast() {
	COLORREF color;
	if (return_show != 0) {
		color = BLUE;
	}
	else {
		color = RGB(176, 196, 222);
	}
	int font_size = 25;
	settextcolor(color);
	settextstyle(25, 0, _T("����"), 0, 0, FW_SEMIBOLD,
		false, true, false);
	outtextxy(kScreenWidth - 100, 15, _T("Return"));
	settextstyle(25, 0, _T("����"), 0, 0, 0,
		false, false, false);
}
void ChooseCheckIfHave() {
	if (gPersonHave[current_person] == 1) {
		is_have = 1;
	}
	else {
		is_have = 0;
	}
}
void CheckKeyboardInput() {
	if (!_kbhit()) {
		return;
	}
	char input = _getch();
	if (input == 13 && is_have) {
		mciSendString(_T("pause ѡ������"), NULL, 0, NULL);
		mciSendString(_T("play ����"), NULL, 0, NULL);
		Sleep(4000);
		button_show = 2;
		gScene = PlayPage;
		if (current_person == 0) {
			gPersonName = _T("��ʿ");
		}
		if (current_person == 1) {
			gPersonName = _T("��ʦ");
		}
		if (current_person == 2) {
			gPersonName = _T("�̿�");
		}
		if (current_person == 3) {
			gPersonName = _T("ʥ��ʿ");
		}
		if (current_person == 4) {
			gPersonName = _T("��Ѫ��");
		}
		if (current_person == 5) {
			gPersonName = _T("����");
		}
		if (current_person == 6) {
			gPersonName = _T("����");
		}
		gCurrentPerson = current_person;
		if_back = true;
	}
	if (input == 27) {
		return_show = 2;
		gScene = ScenePage;
		if_back = true;
	}
}