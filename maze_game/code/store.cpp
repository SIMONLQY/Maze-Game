#include "store.h"

extern int gScreenScrollSpeed;
extern int* gPersonMoney;
extern int* gPersonHave;
extern int gScene;
static int current_person = 6;
static bool is_have;
static bool if_back = false;

static int scroll_times = 0;
static int button_show = 0; // 0无，1hover，2click
static int return_show = 0; // 0无，1hover，2click
void ShowStore() {
	button_show = 0;
	return_show = 0;
	scroll_times = 0;
	mciSendString(_T("open ../sources/music/按钮1.mp3 alias 火焰"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/金币.mp3 alias 金币"), NULL, 0, NULL);
	if_back = false;
	BeginBatchDraw();
	while (1) {
		StoreDrawLeftPart();
		StoreDrawPersonWhileChoose();
		StoreDrawMiddleCircle();
		StoreDrawMiddleCross();
		StoreDrawName();
		StoreDrawTitle();
		StoreDrawGoButton();
		StoreDrawPersonMoney();
		StoreDrawRightPart();
		StoreDrawMoney();
		FlushBatchDraw();
		StoreWait(10000);
		StoreCheckScrollInput();
		//StoreCheckHoverInput();
		CheckKeyboardInput();
		CheckIfHave();
		if (if_back == true) {
			mciSendString(_T("close 火焰"), NULL, 0, NULL);
			mciSendString(_T("close 金币"), NULL, 0, NULL);
			EndBatchDraw();
			return;
		}
	}
}


void StoreWait(int num) {
	for (int i = 0; i < num; i++);
}
void StoreDrawLeftPart() {
	setcolor(RGB(48, 48, 48));
	setfillcolor(RGB(48, 48, 48));
	fillrectangle(0, 0, kChoosePersonWidth,
		kScreenHeight / 4);
	setcolor(WHITE);
	setfillcolor(WHITE);
	fillrectangle(0, kScreenHeight / 4, kChoosePersonWidth,
		3 * kScreenHeight / 4);
	setcolor(RGB(48, 48, 48));
	setfillcolor(RGB(48, 48, 48));
	fillrectangle(0, 3 * kScreenHeight / 4, kChoosePersonWidth,
		kScreenHeight);
}
void StoreDrawRightPart() {
	setcolor(RGB(54, 54, 54));
	setfillcolor(RGB(40, 40, 40));
	fillrectangle(kChoosePersonWidth, 0,
		kScreenWidth, kScreenHeight);
	StoreDrawSkills(current_person);
	StoreDrawRightTitle();
	StoreDrawReturnLast();
}
void StoreDrawPersonWhileChoose() {
	const char* names[7] = { "骑士" , "法师", "刺客" , "圣骑士",
		"吸血鬼", "狼人", "游侠" };
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
			mciSendString(_T("seek 火焰 to start"), 0, 0, 0);
			mciSendString(_T("play 火焰"), NULL, 0, NULL);
		}
	}
	int current_middle = current_person;
	int current_left = StorechooseLeft(current_middle);
	int current_right = StorechooseRight(current_middle);
	int middle_x = kChoosePersonWidth / 2;
	StoreDrawOnePerson(current_middle, deviation, middle_x);
	int left_x = kChoosePersonWidth / 10;
	StoreDrawOnePerson(current_left, deviation, left_x);
	int right_x = 9 * kChoosePersonWidth / 10;
	StoreDrawOnePerson(current_right, deviation, right_x);
	int right2_x = right_x + length;
	int right2_person = StorechooseRight(current_right);
	StoreDrawOnePerson(right2_person, deviation, right2_x);
	int left2_x = left_x - length;
	int left2_person = StorechooseLeft(current_left);
	StoreDrawOnePerson(left2_person, deviation, left2_x);

}
void StoreDrawOnePerson(int number, int deviation, int x_position) {
	IMAGE img1;
	IMAGE img2;
	const char* names[7] = { "骑士" , "法师", "刺客" , "圣骑士",
		"吸血鬼", "狼人", "游侠" };
	CString full_src1;
	CString full_src2;
	CString str_l = names[number];
	full_src1.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
		str_l, _T(".jpg"));
	full_src2.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
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
int StorechooseLeft(int num) {
	int left;
	if (num == 6) {
		left = 0;
	}
	else {
		left = num + 1;
	}
	return left;
}
int StorechooseRight(int num) {
	int right;
	if (num == 0) {
		right = 6;
	}
	else {
		right = num - 1;
	}
	return right;
}

void StoreDrawMiddleCircle() {
	int center_x = kChoosePersonWidth / 2;
	int center_y = kChoosePersonHeight / 2;
	setcolor(BLACK);
	circle(center_x, center_y, 105);
	circle(center_x, center_y, 125);
	floodfill(center_x + 115, center_y, BLACK);

}
void StoreDrawMiddleCross() {
	int center_x = kChoosePersonWidth / 2;
	int center_y = kChoosePersonHeight / 2;
	setcolor(BLACK);
	line(center_x - 105, center_y, center_x + 105, center_y);
	line(center_x, center_y - 105, center_x, center_y + 105);
	circle(center_x, center_y, 35);
}
void StoreCheckScrollInput() {
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
		&& y <= y_position + kButtonHeight && !is_have) {
		if (msg.uMsg == WM_LBUTTONDOWN || msg.uMsg == WM_LBUTTONUP || msg.mkLButton) {
			button_show = 2;
			int money = gPersonMoney[current_person];
			if (money <= GetMoney()) {
				mciSendString(_T("seek 金币 to start"), 0, 0, 0);
				mciSendString(_T("play 金币"), NULL, 0, NULL);
				BuyPerson(current_person);
				ChangeMoney(-money);
			}
		}
		else {
			button_show = 1;
		}
	}
	else {
		button_show = 0;
	}
	if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <=
		40) {
		if (msg.mkLButton) {
			return_show = 2;
			gScene = BeginPage;
			if_back = true;
		}
		else {
			return_show = 1;
		}
	}
	else {
		return_show = 0;
	}



}
//void StoreCheckHoverInput() {
//	if (!MouseHit()) {
//		return;
//	}
//	MOUSEMSG msg = GetMouseMsg();
//	int x = msg.x;
//	int y = msg.y;
//	int x_position = kChoosePersonWidth / 2 - kButtonWidth / 2;
//	int y_position = 7 * kChoosePersonHeight / 8 - kButtonHeight / 2;
//	if (x >= x_position && x <= x_position + kButtonWidth && y >= y_position
//		&& y <= y_position + kButtonHeight && !is_have) {
//		if (msg.uMsg == WM_LBUTTONDOWN || msg.uMsg == WM_LBUTTONUP || msg.mkLButton) {
//			button_show = 2;
//			int money = gPersonMoney[current_person];
//			if (money <= GetMoney()) {
//				mciSendString(_T("seek 金币 to start"), 0, 0, 0);
//				mciSendString(_T("play 金币"), NULL, 0, NULL);
//				BuyPerson(current_person);
//				ChangeMoney(-money);
//			}
//		}
//		else {
//			button_show = 1;
//		}
//	}
//	else {
//		button_show = 0;
//	}
//	if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <=
//		40) {
//		if (msg.mkLButton) {
//			return_show = 2;
//			gScene = BeginPage;
//			if_back = true;
//		}
//		else {
//			return_show = 1;
//		}
//	}
//	else {
//		return_show = 0;
//	}
//}
void StoreDrawName() {
	TCHAR names[7][20] = { _T("骑士") , _T("法师"), _T("刺客") ,
		_T("圣骑士"), _T("吸血鬼"), _T("狼人"), _T("游侠") };
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("黑体"));
	RECT r = { 0, 0, kChoosePersonWidth, kChoosePersonHeight / 7 };
	drawtext(names[current_person], &r, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);

}
void StoreDrawTitle() {
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(5, 20, _T("商店"));
}
void StoreDrawGoButton() {
	int temp_width = kButtonWidth;
	int temp_height = kButtonHeight;
	int font_size = 40;
	setfillcolor(RGB(189, 183, 107));
	if (button_show != 0) {
		temp_width += 10;
		temp_height += 10;
		font_size += 10;
	}
	if (button_show == 2) {
		setfillcolor(RGB(109, 103, 27));
	}
	int x_position = kChoosePersonWidth / 2 - temp_width / 2;
	int y_position = 7 * kChoosePersonHeight / 8 - temp_height / 2;
	POINT pts[] = { {x_position, y_position}, {x_position + temp_width,
		y_position}, {x_position + temp_width + 20, 7 * kChoosePersonHeight / 8},
	{x_position + temp_width, y_position + temp_height},
	{x_position, y_position + temp_height},
	{x_position - 20, 7 * kChoosePersonHeight / 8} };
	setcolor(RGB(211, 211, 211));

	fillpolygon(pts, 6);
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(font_size, 0, _T("黑体"));
	RECT r = { x_position, y_position, x_position + temp_width,
		y_position + temp_height };
	if (is_have == 0) {
		drawtext(_T("Got him!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		drawtext(_T("已拥有"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	}
}
void StoreDrawSkills(int person_num) {
	int skill_1 = kSkills[person_num][0];
	int skill_2 = kSkills[person_num][1];
	if (skill_1 == 0) {
		setfillcolor(BLACK);
		fillrectangle(kChoosePersonWidth + 20, 200,
			kChoosePersonWidth + 100, 280);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 280, skill0_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 220,
			kScreenWidth - 10, 610 };
		drawtext(skill0_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_1 == 1) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/寻路.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 200, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 280, skill1_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 220,
			kScreenWidth - 10, 610 };
		drawtext(skill1_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_1 == 2) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/飞跃.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 200, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 280, skill2_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 220,
			kScreenWidth - 10, 610 };
		drawtext(skill2_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_1 == 3) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/破坏.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 200, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 280, skill3_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 220,
			kScreenWidth - 10, 610 };
		drawtext(skill3_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 0) {
		setfillcolor(BLACK);
		fillrectangle(kChoosePersonWidth + 20, 350,
			kChoosePersonWidth + 100, 430);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430, skill0_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill0_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 1) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/寻路.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430, skill1_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill1_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 2) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/飞跃.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430, skill2_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill2_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}
	if (skill_2 == 3) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/破坏.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430, skill3_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370,
			kScreenWidth - 10, 760 };
		drawtext(skill3_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
	}

}
void StoreDrawRightTitle() {
	settextcolor(YELLOW);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(kChoosePersonWidth + 10, 120, _T("技能描述"));
}
void StoreDrawReturnLast() {
	COLORREF color;
	if (return_show != 0) {
		color = BLUE;
	}
	else {
		color = RGB(176, 196, 222);
	}
	int font_size = 25;
	settextcolor(color);
	settextstyle(25, 0, _T("黑体"), 0, 0, FW_SEMIBOLD,
		false, true, false);
	outtextxy(kScreenWidth - 100, 15, _T("Return"));
	settextstyle(25, 0, _T("黑体"), 0, 0, 0,
		false, false, false);
}
int GetNumLen(int num) {
	int i = 0;
	while (num > 0) {
		num /= 10;
		i += 1;
	}
	return i;
}
void StoreDrawMoney() {
	int num = GetMoney();
	char s[12];
	sprintf_s(s, "%d", num);
	int i;
	moveto(kChoosePersonWidth-200, 10);
	settextcolor(GREEN);
	settextstyle(20, 0, _T("黑体"));
	outtext(_T("我的财富：$"));
	for (i = 0; i < 12; i++) {
		if (s[i] == '\0') {
			break;
		}
		outtext(s[i]);
	}
}
void StoreDrawPersonMoney() {
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	fillrectangle(250, 85, 450, 125);
	settextstyle(30, 0, _T("黑体"));
	RECT r = { 250, 85, 450, 125 };
	if (is_have == 0) {
		settextcolor(GREEN);
		drawtext(kPersonMoney[current_person], &r,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		settextcolor(RGB(112, 128, 144));
		drawtext(kPersonMoney[7], &r,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
}
void CheckIfHave() {
	if (gPersonHave[current_person] == 1) {
		is_have = 1;
	}
	else {
		is_have = 0;
	}
	
}
static void CheckKeyboardInput() {
	if (!_kbhit()) {
		return;
	}
	char input = _getch();
	if (input == 13 && !is_have) {
		button_show = 2;
		int money = gPersonMoney[current_person];
		if (money <= GetMoney()) {
			mciSendString(_T("seek 金币 to start"), 0, 0, 0);
			mciSendString(_T("play 金币"), NULL, 0, NULL);
			BuyPerson(current_person);
			ChangeMoney(-money);
		}
	}
	if (input == 27) {
		return_show = 2;
		gScene = BeginPage;
		if_back = true;
	}
}