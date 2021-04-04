#include "game_page.h"
//extern int fog_range;
extern int gMazeHeight;
extern int gMazeWidth;
extern int gMazeSquareLength; // 每个方格的边长（像素）
extern int gMazeGapBetween; // 每两个方格之间的边长空隙
extern int gMazeStartX;
extern int gMazeStartY;
extern int gMazeEndX;
extern int gMazeEndY;
extern int gGameScreenChangeSpeed;
extern int closeNum;
extern int currTheme;
extern int gSquareColor;
extern int gScene;
extern bool if_back = false;
extern int sillLeftTime0;
extern int sillLeftTime1;
extern int sillLeftTime2;
extern int sillLeftTime3;
extern int gPrize;

extern int gCurrentPerson;
extern MazeSquare** closeList;
extern CString gPersonName;
static IMAGE themes[6];

static int gameCornerX;
static int gameCornerY;
static int personImgWidth = 4 * gMazeSquareLength / 5;
static bool return_show = false;
static clock_t game_start;
static clock_t game_now;
static int used_step;
static bool if_succeed;
static int game_times = 0;
static bool go_ahead = false;
static int init_speed;
static int musicStart;

Person person;

extern MazeSquare** squares;
void GamePage() {
	InitAllGameSettings();
	
	while (1) {
		MoveFirst();
		DrawPersonFirst();
		HideOverFlow();
		DrawGameRightPart();
		FlushBatchDraw();
		Sleep(1);
		if (go_ahead) {
			break;
		}
	}
	while (1) {
		// draw
		playBackMusic();
		DrawMaze();
		DrawPerson();
		HideOverFlow();
		DrawGameRightPart();
		FlushBatchDraw();
		CheckSucceed();
		CheckFailed();
		if (if_back) {
			EndBatchDraw();
			mciSendString(_T("close game_start"), NULL, 0, NULL);
			mciSendString(_T("close 连通"), NULL, 0, NULL);
			mciSendString(_T("close 飞跃"), NULL, 0, NULL);
			mciSendString(_T("close 寻路"), NULL, 0, NULL);
			mciSendString(_T("close 游戏成功"), NULL, 0, NULL);
			mciSendString(_T("close 游戏失败"), NULL, 0, NULL);

			mciSendString(_T("close 海浪声"), NULL, 0, NULL);
			mciSendString(_T("close 牛"), NULL, 0, NULL);
			mciSendString(_T("close 羊"), NULL, 0, NULL);
			mciSendString(_T("close 岩浆"), NULL, 0, NULL);

			if (squares != NULL) {
				for (int i = 0; i < (gMazeHeight + 2); i++) {
					delete[]squares[i];
				}
				delete[]squares;
			}
			return;
		}
		Sleep(1);
		GetInput();
		GetMouseInput();
	}
}
void InitAllGameSettings() {
	return_show = 0;
	go_ahead = false;
	game_times = 0;
	if_succeed = false;
	used_step = 0;
	game_start = clock();
	musicStart = clock();
	if_back = false;
	InitPerson();
	CreateMaze();
	BeginBatchDraw();
	InitPage();
	InitCorner();
	mciSendString(_T("open ../sources/music/game_start.mp3 alias game_start"), NULL, 0, NULL);
	mciSendString(_T("play game_start"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/连通.mp3 alias 连通"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/按钮2.mp3 alias 飞跃"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/按钮2.mp3 alias 飞跃"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/神圣的光感.mp3 alias 寻路"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/游戏成功.mp3 alias 游戏成功"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/游戏失败.mp3 alias 游戏失败"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/海浪声.mp3 alias 海浪声"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/岩浆.wav alias 岩浆"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/牛.wav alias 牛"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/羊.wav alias 羊"), NULL, 0, NULL);

	int length = gMazeSquareLength + gMazeGapBetween;
	int width = length * (gMazeWidth + 2);
	int height = length * (gMazeHeight + 2);
	int max = width > height ? width : height;
	if (currTheme == 5) {
		init_speed = max / 35;
	}
	if (currTheme == 4) {
		init_speed = max / 65;
	}
	if (currTheme == 3) {
		init_speed = max / 120;
	}
	if (currTheme == 2) {
		init_speed = max / 130;
	}
	if (currTheme == 1) {
		init_speed = max / 160;
	}
	if (currTheme == 0) {
		init_speed = max / 210;
	}
	
}
void InitPage() {
	sillLeftTime0 = kSkillTimes[0];
	sillLeftTime1 = kSkillTimes[1];
	sillLeftTime2 = kSkillTimes[2];
	sillLeftTime3 = kSkillTimes[3];
	setfillcolor(WHITE);
	setcolor(GREEN);
	fillrectangle(kGameSideSpace, kGameSideSpace, kGameSideSpace
		+ kGameWindowWidth, kGameSideSpace + kGameWindowHeight);
	int imgWidth = 250;
	int imgHeight = 150;
	loadimage(&themes[0], _T("../sources/pic/主题/海洋.jpg"), imgWidth, imgHeight, true);
	loadimage(&themes[1], _T("../sources/pic/主题/火山.jpg"), imgWidth, imgHeight, true);
	loadimage(&themes[2], _T("../sources/pic/主题/草原.jpg"), imgWidth, imgHeight, true);
	loadimage(&themes[3], _T("../sources/pic/主题/海洋.jpg"), imgWidth, imgHeight, true);
	loadimage(&themes[4], _T("../sources/pic/主题/火山.jpg"), imgWidth, imgHeight, true);
	loadimage(&themes[5], _T("../sources/pic/主题/草原.jpg"), imgWidth, imgHeight, true);
}
void InitCorner() {
	gameCornerX = 0;
	gameCornerY = 0;
}
void MoveFirst() {
	int length = gMazeSquareLength + gMazeGapBetween;
	static int last_game_corner_x = gMazeWidth;
	static int last_game_corner_y = gMazeHeight;
	static int count_x = 0;
	static int count_y = 0;
	if (game_times == 0) {
		last_game_corner_x = gMazeWidth;
		last_game_corner_y = gMazeHeight;
		count_x = 0;
		count_y = 0;
		game_times += 1;
	}
	if (gameCornerX - last_game_corner_x != 0) {
		int temp = (gameCornerX - last_game_corner_x);
		count_x += temp / abs(temp) * init_speed;
		if (abs(count_x) >= abs(temp * length)) {
			count_x = 0;
			last_game_corner_x = gameCornerX;
		}
	}
	if (gameCornerY - last_game_corner_y != 0) {
		int temp = (gameCornerY - last_game_corner_y);
		count_y += temp / abs(temp) * init_speed;
		if (abs(count_y) >= abs(temp * length)) {
			count_y = 0;
			last_game_corner_y = gameCornerY;
		}
	}
	if (gameCornerY - last_game_corner_y == 0 &&
		gameCornerX - last_game_corner_x == 0) {
		go_ahead = true;
	}
	CString backGroundImgStr;
	TCHAR backStr[6][20] = { _T("海洋"),_T("火山"),_T("草原"),_T("海洋"),_T("火山"),_T("草原") };
	backGroundImgStr.Format(_T("%s%s%s"),
		_T("../sources/pic/主题/"),
		backStr[currTheme], _T(".jpg"));
	int SquareClors[6] = { RGB(0,191,255),RGB(139,0,0),RGB(0,255,127),RGB(0,191,255),RGB(139,0,0),RGB(0,255,127) };
	gSquareColor = SquareClors[currTheme];
	//画背景图片
	setfillcolor(TRANSPARENT);
	cleardevice();
	IMAGE backGroundImg;
	loadimage(&backGroundImg, backGroundImgStr, kScreenWidth, kScreenHeight, true);
	putimage(0, 0, &backGroundImg);

	//画方块
	for (int i = -gameCornerY; i < gMazeHeight + 2 - gameCornerY; i++) {
		for (int j = -gameCornerX; j < gMazeWidth + 2 - gameCornerX; j++) {
			if (squares[i + gameCornerY][j + gameCornerX].color == grey) {
				setcolor(BLACK);
			}
			else {
				if (i == gMazeEndY - gameCornerY && j == gMazeEndX - gameCornerX) {
					setfillcolor(RGB(255, 165, 0));
				}
				else if (i == gMazeStartY - gameCornerY && j == gMazeStartX - gameCornerX) {
					setfillcolor(RGB(255, 182, 193));
				}
				else if (squares[i + gameCornerY][j + gameCornerX].special) {
					setfillcolor(WHITE);
				}
				else {
					setfillcolor(gSquareColor);
				}
				setcolor(BLACK);
				int temp_x = (gameCornerX - last_game_corner_x);
				int temp_y = (gameCornerY - last_game_corner_y);
				fillrectangle(kGameSideSpace + j * length + temp_x * length - count_x,
					kGameSideSpace + i * length + temp_y * length - count_y,
					kGameSideSpace + j * length + gMazeSquareLength + temp_x * length - count_x,
					kGameSideSpace + i * length + gMazeSquareLength + temp_y * length - count_y);
			}

		}
	}
}
void DrawMaze() {
	int length = gMazeSquareLength + gMazeGapBetween;
	static int last_game_corner_x = gameCornerX;
	static int last_game_corner_y = gameCornerY;
	static int count_x = 0;
	static int count_y = 0;
	if (game_times == 2) {
		last_game_corner_x = gameCornerX;
		last_game_corner_y = gameCornerY;
		count_x = 0;
		count_y = 0;
		game_times += 1;
	}

	if (gameCornerX - last_game_corner_x != 0) {
		int temp = (gameCornerX - last_game_corner_x);
		count_x += temp / abs(temp) * gGameScreenChangeSpeed;
		if (abs(count_x) >= abs(temp * length)) {
			count_x = 0;
			last_game_corner_x = gameCornerX;
		}
	}
	if (gameCornerY - last_game_corner_y != 0) {
		int temp = (gameCornerY - last_game_corner_y);
		count_y += temp / abs(temp) * gGameScreenChangeSpeed;
		if (abs(count_y) >= abs(temp * length)) {
			count_y = 0;
			last_game_corner_y = gameCornerY;
		}
	}
	//根据主题判定参数
	CString backGroundImgStr;
	TCHAR backStr[6][20] = { _T("海洋"),_T("火山"),_T("草原"),_T("海洋"),_T("火山"),_T("草原") };
	backGroundImgStr.Format(_T("%s%s%s"),
		_T("../sources/pic/主题/"),
		backStr[currTheme], _T(".jpg"));
	int SquareClors[6] = { RGB(0,191,255),RGB(139,0,0),RGB(0,255,127),RGB(0,191,255),RGB(139,0,0),RGB(0,255,127) };
	gSquareColor = SquareClors[currTheme];
	//画背景图片
	setfillcolor(TRANSPARENT);
	cleardevice();
	IMAGE backGroundImg;
	loadimage(&backGroundImg, backGroundImgStr, kScreenWidth, kScreenHeight, true);
	putimage(0, 0, &backGroundImg);

	//画方块
	for (int i = -gameCornerY; i < gMazeHeight + 2 - gameCornerY; i++) {
		for (int j = -gameCornerX; j < gMazeWidth + 2 - gameCornerX; j++) {
			/*if (fog[currTheme]) {
				if (abs(j + gameCornerX - person.x) +
					abs(i + gameCornerY - person.y) > fog_range) {
					setcolor(BLACK);
					continue;
				}
			}*/
			if (squares[i + gameCornerY][j + gameCornerX].color == grey) {
				setcolor(BLACK);
			}
			else {
				if (i == gMazeEndY - gameCornerY && j ==  gMazeEndX - gameCornerX) {
					setfillcolor(RGB(255, 165, 0));
				}
				else if (i == gMazeStartY - gameCornerY && j == gMazeStartX - gameCornerX) {
					setfillcolor(RGB(255, 182, 193));
				} 
				else if (squares[i + gameCornerY][j + gameCornerX].special) {
					setfillcolor(WHITE);
				}
				else {
					setfillcolor(gSquareColor);
				}	
				setcolor(BLACK);
				int temp_x = (gameCornerX - last_game_corner_x);
				int temp_y = (gameCornerY - last_game_corner_y);
				fillrectangle(kGameSideSpace + j * length + temp_x * length - count_x,
					kGameSideSpace + i * length + temp_y * length - count_y,
					kGameSideSpace + j * length + gMazeSquareLength + temp_x * length - count_x,
					kGameSideSpace + i * length + gMazeSquareLength + temp_y * length - count_y);
			}

		}
	}
}
void HideOverFlow() {
	if (fog[currTheme] && go_ahead) {
		setfillcolor(WHITE);
		setcolor(BLACK);
		rectangle(0, 0, kGameWindowWidth + kGameSideSpace - 1,
			kScreenHeight - 1);
		int length = gMazeSquareLength + gMazeGapBetween;
		int true_x = person.x * length + gMazeSquareLength / 2 -
			gameCornerX * length + kGameSideSpace;
		int true_y = person.y * length + gMazeSquareLength / 2
			- gameCornerY * length + kGameSideSpace;
		setcolor(WHITE);
		circle(true_x,
			true_y, fog_range[currTheme] * length);
		int out_x;
		int out_y;
		int x1 = 1;
		int y1 = 1;
		int x2 = kGameWindowWidth + kGameSideSpace - 2;
		int y2 = kScreenHeight - 2;
		int x3 = 1;
		int y3 = kScreenHeight - 2;
		int x4 = kGameWindowWidth + kGameSideSpace - 2;
		int y4 = 1;
		int len1 = pow(abs(true_x - x1)
			, 2) + pow(abs(true_y - y1)
			, 2);
		int len2 = pow(abs(true_x - x2)
			, 2) + pow(abs(true_y - y2)
				, 2);
		int len3 = pow(abs(true_x - x3)
			, 2) + pow(abs(true_y - y3)
				, 2);
		int len4 = pow(abs(true_x - x4)
			, 2) + pow(abs(true_y - y4)
				, 2);
		int len = pow(fog_range[currTheme] * length, 2);
		if (len1 > len) {
			floodfill(x1, y1, WHITE);
		}
		if (len2 > len) {
			floodfill(x2, y2, WHITE);
		}
		if (len3 > len) {
			floodfill(x3, y3, WHITE);
		}
		if (len4 > len) {
			floodfill(x4, y4, WHITE);
		}
		/*int x1 = person.x * length + fog_range * length + gMazeSquareLength / 2 + 10;
		int x2 = person.x * length - fog_range * length + gMazeSquareLength / 2 - 10;
		out_y = person.y * length + gMazeSquareLength / 2;
		if (x1 > 0 && x1 < kGameWindowWidth - 1) {
			out_x = x1;
		}
		else if (x2 > 0 && x1 < kGameWindowWidth - 1) {
			out_x = x2;
		}*/
		
	}
	

	setfillcolor(BLACK);
	setcolor(BLACK);
	fillrectangle(kGameSideSpace + kGameWindowWidth, 0,
		kScreenWidth - 1, kScreenHeight - 1);
	fillrectangle(0, kScreenHeight - kGameSideSpace,
		kGameWindowWidth + kGameSideSpace, kScreenHeight - 1);
}
void InitPerson() {
	// 生成名字
	person.name = gPersonName;
	// 生成路径
	CString full_src1;
	CString full_src2;
	full_src1.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
		gPersonName, _T(".jpg"));
	full_src2.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
		gPersonName, _T("black.jpg"));

	person.x = gMazeStartY;
	person.y = gMazeStartX;
	person.is_move = false;
	loadimage(&person.img, full_src1,
		0, 0, true);
	int current_width = person.img.getwidth();
	int current_height = person.img.getheight();
	int new_width = personImgWidth;
	int new_height = (int)
		(current_height * double(new_width) / current_width);
	Resize(&person.img, new_width, new_height);
	loadimage(&person.img, full_src1,
		new_width, new_height, true);
	loadimage(&person.img_black, full_src2,
		new_width, new_height, true);
}
void DrawPersonFirst() {
	
	int length = gMazeSquareLength + gMazeGapBetween;
	static int last_game_corner_x = gMazeWidth;
	static int last_game_corner_y = gMazeHeight;
	static int count_x = 0;
	static int count_y = 0;
	if (game_times == 1) {
		last_game_corner_x = gMazeWidth;
		last_game_corner_y = gMazeHeight;
		count_x = 0;
		count_y = 0;
		game_times += 1;
	}
	if (gameCornerX - last_game_corner_x != 0) {
		int temp = (gameCornerX - last_game_corner_x);
		count_x += temp / abs(temp) * init_speed;
		if (abs(count_x) >= abs(temp * length)) {
			count_x = 0;
			last_game_corner_x = gameCornerX;
		}
	}
	if (gameCornerY - last_game_corner_y != 0) {
		int temp = (gameCornerY - last_game_corner_y);
		count_y += temp / abs(temp) * init_speed;
		if (abs(count_y) >= abs(temp * length)) {
			count_y = 0;
			last_game_corner_y = gameCornerY;
		}
	}

	int temp_x = (gameCornerX - last_game_corner_x);
	int temp_y = (gameCornerY - last_game_corner_y);
	int x_position = kGameSideSpace + person.x * length + gMazeSquareLength / 10 -
		gameCornerX * length + temp_x * length - count_x;
	int y_position = kGameSideSpace + person.y * length -
		gameCornerY * length + temp_y * length - count_y;
	putimage(x_position, y_position, &person.img_black, NOTSRCERASE);
	putimage(x_position, y_position, &person.img, SRCINVERT);
}
void DrawPerson() {
	int length = gMazeSquareLength + gMazeGapBetween;
	static int last_game_corner_x = gameCornerX;
	static int last_game_corner_y = gameCornerY;
	static int count_x = 0;
	static int count_y = 0;
	if (game_times == 3) {
		last_game_corner_x = gameCornerX;
		last_game_corner_y = gameCornerY;
		count_x = 0;
		count_y = 0;
		game_times += 1;
	}
	if (gameCornerX - last_game_corner_x != 0) {
		int temp = (gameCornerX - last_game_corner_x);
		count_x += temp / abs(temp) * gGameScreenChangeSpeed;
		if (abs(count_x) >= abs(temp * length)) {
			count_x = 0;
			last_game_corner_x = gameCornerX;
		}
	}
	if (gameCornerY - last_game_corner_y != 0) {
		int temp = (gameCornerY - last_game_corner_y);
		count_y += temp / abs(temp) * gGameScreenChangeSpeed;
		if (abs(count_y) >= abs(temp * length)) {
			count_y = 0;
			last_game_corner_y = gameCornerY;
		}
	}

	int temp_x = (gameCornerX - last_game_corner_x);
	int temp_y = (gameCornerY - last_game_corner_y);
	int x_position = kGameSideSpace + person.x * length + gMazeSquareLength / 10 -
		gameCornerX * length + temp_x * length - count_x;
	int y_position = kGameSideSpace + person.y * length -
		gameCornerY * length + temp_y * length - count_y;
	putimage(x_position, y_position, &person.img_black, NOTSRCERASE);
	putimage(x_position, y_position, &person.img, SRCINVERT);
}
void DrawGameRightPart() {
	setcolor(RGB(54, 54, 54));
	setfillcolor(RGB(40, 40, 40));
	fillrectangle(kChoosePersonWidth, 0,
		kScreenWidth, kScreenHeight);
	DrawGameSkills(gCurrentPerson);
	DrawGameRightTitle();
	DrawGameReturnLast();
	CheckTime();
	CheckRemainTime();
	CheckStep();
	DrawRightPic();
}
void DrawGameReturnLast() {
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
void DrawGameRightTitle() {
	settextcolor(YELLOW);
	settextstyle(30, 0, _T("黑体"));
	outtextxy(kChoosePersonWidth + 10, 220, _T("技能描述"));
	settextstyle(15, 0, _T("楷体"));
	settextcolor(WHITE);
	outtextxy(kChoosePersonWidth + 160, 220, _T("'J'发动一技能"));
	outtextxy(kChoosePersonWidth + 160, 235, _T("'K'发动二技能"));
}
void DrawGameSkills(int person_num) {
	int skill_1 = kSkills[person_num][0];
	int skill_2 = kSkills[person_num][1];
	int temp1 = -20;
	int temp2 = 50;
	if (skill_1 == 0) {
		setfillcolor(BLACK);
		fillrectangle(kChoosePersonWidth + 20, 250 - temp1,
			kChoosePersonWidth + 100, 330 - temp1);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 330 - temp1, skill0_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 270 - temp1,
			kScreenWidth - 10, 610 };
		drawtext(skill0_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime0;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 350);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
	if (skill_1 == 1) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/寻路.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 250 - temp1, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 330 - temp1, skill1_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 270 - temp1,
			kScreenWidth - 10, 610 };
		drawtext(skill1_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime1;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 350);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
	if (skill_1 == 2) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/飞跃.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 250 - temp1, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 330 - temp1, skill2_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 270 - temp1,
			kScreenWidth - 10, 610 };
		drawtext(skill2_description, &r, DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime2;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 350);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
	if (skill_1 == 3) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/破坏.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 270 - temp1, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 330 - temp1, skill3_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 270 - temp1,
			kScreenWidth - 10, 610 };
		drawtext(skill3_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime3;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 350);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
	if (skill_2 == 0) {
		setfillcolor(BLACK);
		fillrectangle(kChoosePersonWidth + 20, 350 + temp2,
			kChoosePersonWidth + 100, 430 + temp2);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430 + temp2, skill0_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370 + temp2,
			kScreenWidth - 10, 760 };
		drawtext(skill0_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime0;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 480);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
	if (skill_2 == 1) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/寻路.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350 + temp2, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430 + temp2, skill1_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370 + temp2,
			kScreenWidth - 10, 760 };
		drawtext(skill1_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime1;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 480);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
	if (skill_2 == 2) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/飞跃.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350 + temp2, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430 + temp2, skill2_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370 + temp2,
			kScreenWidth - 10, 760 };
		drawtext(skill2_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime2;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 480);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
	if (skill_2 == 3) {
		IMAGE img;
		loadimage(&img, _T("../sources/pic/技能/破坏.jpg"), 80, 80);
		putimage(kChoosePersonWidth + 20, 350 + temp2, &img);
		settextcolor(WHITE);
		settextstyle(20, 0, _T("宋体"));
		outtextxy(kChoosePersonWidth + 40, 430 + temp2, skill3_name);
		settextstyle(17, 0, _T("宋体"));
		RECT r = { kChoosePersonWidth + 110, 370 + temp2,
			kScreenWidth - 10, 760 };
		drawtext(skill3_description, &r,
			DT_LEFT | DT_WORDBREAK | DT_EXTERNALLEADING);
		int num = sillLeftTime3;
		char s[12];
		sprintf_s(s, "%d", num);
		int i;
		moveto(kChoosePersonWidth + 120, 480);
		if (num == 0) {
			settextcolor(RED);
		}
		else {
			settextcolor(GREEN);
		}
		settextstyle(20, 0, _T("黑体"));
		outtext(_T("剩余使用次数："));
		for (i = 0; i < 12; i++) {
			if (s[i] == '\0') {
				break;
			}
			outtext(s[i]);
		}
	}
}
void GetInput() {
	if (!_kbhit()) {
		person.is_move = false;
		return;
	}
	char input = _getch();
	int length = gMazeSquareLength + gMazeGapBetween;
	int max_y = kGameWindowHeight / length;
	int max_x = kGameWindowWidth / length;
	if (input == 'w') {
		person.y -= 1;
		if (!CheckHit()) {
			person.y += 1;
			person.is_move = false;
		}
		else {
			person.is_move = true;
			used_step++;
		}
		if (person.is_move) {
			if (person.y - gameCornerY <= 1 / 3.0 * max_y) {
				if (gameCornerY > 0) {
					gameCornerY--;
				}
			}
		}
	}
	else if (input == 'a') {
		person.x -= 1;
		if (!CheckHit()) {
			person.x += 1;
			person.is_move = false;
		}
		else {
			person.is_move = true;
			used_step++;
		}
		if (person.is_move) {
			if (person.x - gameCornerX <= 1 / 3.0 * max_x) {
				if (gameCornerX > 0) {
					gameCornerX--;
				}
			}
		}
	}
	else if (input == 's') {
		person.y += 1;
		if (!CheckHit()) {
			person.y -= 1;
			person.is_move = false;
		}
		else {
			person.is_move = true;
			used_step++;
		}
		if (person.is_move) {
			if (person.y - gameCornerY >= 2 / 3.0 * max_y) {
				if (gameCornerY < gMazeHeight - max_y + 1) {
					gameCornerY++;
				}
			}
		}
	}
	else if (input == 'd') {
		person.x += 1;
		if (!CheckHit()) {
			person.x -= 1;
			person.is_move = false;
		}
		else {
			person.is_move = true;
			used_step++;
		}
		if (person.is_move) {
			if (person.x - gameCornerX >= 2 / 3.0 * max_x) {
				if (gameCornerX < gMazeWidth - max_x + 1) {
					gameCornerX++;
				}
			}
		}
	}
	else if (input == 'j') {
		useSkill(kSkills[gCurrentPerson][0]);
	}
	else if (input == 'k') {
		useSkill(kSkills[gCurrentPerson][1]);
	}
	else if (input == 27) {
		return_show = 2;
		setlinestyle(PS_SOLID, 5);
		setcolor(RGB(255, 215, 0));
		setfillcolor(RGB(20, 20, 20));
		int width = kGameWindowWidth / 2;
		int height = kGameWindowHeight / 2;
		int bar_width = 600;
		int bar_height = 300;
		fillrectangle(width - bar_width / 2, height - bar_height / 2,
			width + bar_width / 2, height + bar_height / 2);
		DrawBoard();
		FlushBatchDraw();
		Sleep(2000);
		_getch();
		gScene = BeginPage;
		if_back = true;
	}
}
bool CheckHit() {
	if (squares[person.y][person.x].color == grey) {
		return false;
	}
	else {
		return true;
	}
}
void GetMouseInput() {
	if (!MouseHit()) {
		return;
	}
	MOUSEMSG msg = GetMouseMsg();
	int x = msg.x;
	int y = msg.y;
	if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <=
		40) {
		if (msg.mkLButton) {
			return_show = 2;
			setlinestyle(PS_SOLID, 5);
			setcolor(RGB(255, 215, 0));
			setfillcolor(RGB(20, 20, 20));
			int width = kGameWindowWidth / 2;
			int height = kGameWindowHeight / 2;
			int bar_width = 600;
			int bar_height = 300;
			fillrectangle(width - bar_width / 2, height - bar_height / 2,
				width + bar_width / 2, height + bar_height / 2);
			DrawBoard();
			FlushBatchDraw();
			Sleep(2000);
			_getch();
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
void CheckSucceed() {
	if (person.x == gMazeEndX && person.y == gMazeEndY) {
		if_succeed = true;
		setlinestyle(PS_SOLID, 5);
		setcolor(RGB(255, 215, 0));
		setfillcolor(RGB(20, 20, 20));
		int width = kGameWindowWidth /2;
		int height = kGameWindowHeight /2;
		int bar_width = 600;
		int bar_height = 300;
		fillrectangle(width-bar_width/2, height-bar_height/2, 
			width + bar_width / 2, height + bar_height / 2);
		DrawBoard();
		FlushBatchDraw();
		ChangeMoney(gPrize);
		Sleep(1000);
		_getch();
		gScene = BeginPage;
		if_back = true;
	}
}
void CheckFailed() {
	game_now = clock();
	int temp = Time[currTheme] - (game_now - game_start) / 1000;
	if (temp <= 0) {
		setlinestyle(PS_SOLID, 5);
		setcolor(RGB(255, 215, 0));
		setfillcolor(RGB(20, 20, 20));
		int width = kGameWindowWidth / 2;
		int height = kGameWindowHeight / 2;
		int bar_width = 600;
		int bar_height = 300;
		fillrectangle(width - bar_width / 2, height - bar_height / 2,
			width + bar_width / 2, height + bar_height / 2);
		DrawBoard();
		FlushBatchDraw();
		Sleep(2000);
		_getch();
		gScene = BeginPage;
		if_back = true;
	}
}
void CheckTime() {
	game_now = clock();
	int temp = (game_now - game_start) / 1000;
	int hour = temp / 3600;
	int minute = temp % 3600 / 60;
	int second = temp % 3600 % 60;
	char s1[12];
	sprintf_s(s1, "%d", hour);
	char s2[12];
	sprintf_s(s2, "%d", minute);
	char s3[12];
	sprintf_s(s3, "%d", second);
	int i;
	moveto(kGameWindowWidth + 150, 120);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("黑体"));
	outtext(_T("已用时："));
	for (i = 0; i < 12; i++) {
		if (s1[i] == '\0') {
			break;
		}
		outtext(s1[i]);
	}
	outtext(_T(":"));
	for (i = 0; i < 12; i++) {
		if (s2[i] == '\0') {
			break;
		}
		outtext(s2[i]);
	}
	outtext(_T(":"));
	for (i = 0; i < 12; i++) {
		if (s3[i] == '\0') {
			break;
		}
		outtext(s3[i]);
	}
}
void CheckRemainTime() {
	game_now = clock();
	int temp = Time[currTheme] - (game_now - game_start) / 1000;
	int hour = temp / 3600;
	int minute = temp % 3600 / 60;
	int second = temp % 3600 % 60;
	char s1[12];
	sprintf_s(s1, "%d", hour);
	char s2[12];
	sprintf_s(s2, "%d", minute);
	char s3[12];
	sprintf_s(s3, "%d", second);
	int i;
	moveto(kGameWindowWidth + 150, 150);
	settextcolor(RGB(255, 69, 0));
	settextstyle(20, 0, _T("黑体"));
	outtext(_T("剩余时间："));
	for (i = 0; i < 12; i++) {
		if (s1[i] == '\0') {
			break;
		}
		outtext(s1[i]);
	}
	outtext(_T(":"));
	for (i = 0; i < 12; i++) {
		if (s2[i] == '\0') {
			break;
		}
		outtext(s2[i]);
	}
	outtext(_T(":"));
	for (i = 0; i < 12; i++) {
		if (s3[i] == '\0') {
			break;
		}
		outtext(s3[i]);
	}
}
void CheckStep() {
	char s1[12];
	sprintf_s(s1, "%d", used_step);
	int i;
	moveto(kGameWindowWidth + 150, 90);
	settextcolor(WHITE);
	settextstyle(15, 0, _T("黑体"));
	outtext(_T("已用步数："));
	for (i = 0; i < 12; i++) {
		if (s1[i] == '\0') {
			break;
		}
		outtext(s1[i]);
	}
}
void DrawBoard() {
	int width = kGameWindowWidth / 2;
	int height = kGameWindowHeight / 2;
	int bar_width = 600;
	int bar_height = 300;
	RECT r = { width-bar_width/2, height-bar_height/2,
		width + bar_width / 2, height-50 };
	settextcolor(WHITE);
	settextstyle(70, 0, _T("黑体"));
	if (if_succeed) {
		mciSendString(_T("play 游戏成功"), NULL, 0, NULL);
		drawtext(_T("通关成功"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		mciSendString(_T("play 游戏失败"), NULL, 0, NULL);
		drawtext(_T("通关失败"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
		
	setcolor(WHITE);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);
	line(width - bar_width / 2 + 40, height - 50,
		width + bar_width / 2 - 40, height - 50);

	game_now = clock();
	int temp = (game_now - game_start) / 1000;
	int hour = temp / 3600;
	int minute = temp % 3600 / 60;
	int second = temp % 3600 % 60;
	char s1[12];
	sprintf_s(s1, "%d", hour);
	char s2[12];
	sprintf_s(s2, "%d", minute);
	char s3[12];
	sprintf_s(s3, "%d", second);
	int i;
	moveto(width - bar_width / 2 + 40, height - 10);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("黑体"));
	if (if_succeed) {
		outtext(_T("通关用时："));
	}
	else {
		outtext(_T("总共用时："));
	}
	
	for (i = 0; i < 12; i++) {
		if (s1[i] == '\0') {
			break;
		}
		outtext(s1[i]);
	}
	outtext(_T(":"));
	for (i = 0; i < 12; i++) {
		if (s2[i] == '\0') {
			break;
		}
		outtext(s2[i]);
	}
	outtext(_T(":"));
	for (i = 0; i < 12; i++) {
		if (s3[i] == '\0') {
			break;
		}
		outtext(s3[i]);
	}
	//setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 10);


	char s4[12];
	sprintf_s(s4, "%d", used_step);
	moveto(width - bar_width / 2 + 40, height + 30);
	outtext(_T("已用步数："));
	for (i = 0; i < 12; i++) {
		if (s4[i] == '\0') {
			break;
		}
		outtext(s4[i]);
	}
	if (if_succeed) {
		char s5[12];
		sprintf_s(s4, "%d", gPrize);
		moveto(width - bar_width / 2 + 40, height + 70);
		outtext(_T("获得金钱："));
		for (i = 0; i < 12; i++) {
			if (s4[i] == '\0') {
				break;
			}
			outtext(s4[i]);
		}
	}
	

	// 生成路径
	CString full_src1;
	CString full_src2;
	full_src1.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
		gPersonName, _T(".jpg"));
	full_src2.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
		gPersonName, _T("black.jpg"));

	loadimage(&person.img, full_src1,
		0, 0, true);
	int current_width = person.img.getwidth();
	int current_height = person.img.getheight();
	int new_width = 60;
	int new_height = (int)
		(current_height * double(new_width) / current_width);
	Resize(&person.img, new_width, new_height);
	loadimage(&person.img, full_src1,
		new_width, new_height, true);
	loadimage(&person.img_black, full_src2,
		new_width, new_height, true);

	int x_position = width + bar_width / 2 - 130;
	int y_position = height - bar_height / 2 + 30;
	putimage(x_position, y_position, &person.img_black, NOTSRCERASE);
	putimage(x_position, y_position, &person.img, SRCINVERT);
	
	putimage(x_position - 160, y_position + 100, &themes[currTheme]);
	setcolor(RGB(192, 192, 192));
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 3);
	rectangle(x_position - 160, y_position + 100, x_position + 90,
		y_position + 250);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, 1);


	RECT r2 = { width - bar_width / 2, height + bar_height / 2 - 50,
		width, height + bar_height / 2  };
	settextcolor(RGB(211, 211, 211));
	settextstyle(15, 0, _T("黑体"));
	drawtext(_T("按任意键以继续..."), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
}
void DrawRightPic() {
	int x_position = 730;
	int y_position = 70;



	IMAGE temp, temp_black;

	// 生成路径
	CString full_src1;
	CString full_src2;
	full_src1.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
		gPersonName, _T(".jpg"));
	full_src2.Format(_T("%s%s%s"),
		_T("../sources/pic/人物/"),
		gPersonName, _T("black.jpg"));

	loadimage(&temp, full_src1,
		0, 0, true);
	int current_width = temp.getwidth();
	int current_height = temp.getheight();
	int new_width = 100;
	int new_height = (int)
		(current_height * double(new_width) / current_width);

	setcolor(RGB(255, 215, 0));
	setfillcolor(WHITE);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 7);
	fillrectangle(x_position - 10, y_position - 10, 
		x_position + new_width + 10,
		y_position + new_height + 10);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, 1);




	loadimage(&temp, full_src1,
		new_width, new_height, true);
	loadimage(&temp_black, full_src2,
		new_width, new_height, true);
	putimage(x_position, y_position, &temp_black, NOTSRCERASE);
	putimage(x_position, y_position, &temp, SRCINVERT);

	
}
void playBackMusic() {
	int musicCheck = clock();
	if (currTheme == 0 || currTheme == 3) { //海洋
		mciSendString(_T("play 海浪声 repeat"), NULL, 0, NULL);
	}
	if (currTheme == 1 || currTheme == 4) {// 火山
		if ((musicCheck - musicStart) >= 5000 && musicCheck % 400 == 0) {
			mciSendString(_T("seek 岩浆 to start"), NULL, 0, NULL);
			mciSendString(_T("play 岩浆"), NULL, 0, NULL);
			musicStart = musicCheck;
		}
	}

	if (currTheme == 2 || currTheme == 5) {// 草原
		if ((musicCheck - musicStart) / 1000 >= 5) {
			if (musicCheck % 3 == 1) {
				mciSendString(_T("seek 牛 to start"), NULL, 0, NULL);
				mciSendString(_T("play 牛"), NULL, 0, NULL);
			}
			else if (musicCheck % 6 == 2) {
				mciSendString(_T("seek 羊 to start"), NULL, 0, NULL);
				mciSendString(_T("play 羊"), NULL, 0, NULL);
			}
			musicStart = musicCheck;
		}
	}

}