#include "choose_maze.h"
#include<stdlib.h>
//#include"global_variables.h"

extern int gScene;
extern int gPrize;
extern int currTheme;
extern int gMazeHeight;
extern int gMazeWidth;
const int themeNum = 6;     //主题数量
static int gMazeSizes[themeNum][2];   //迷宫大小
static char sizes[themeNum][2][25];
static int prizes[themeNum];   //奖励
char prize[themeNum][25];
//bool fog[themeNum];
static IMAGE Themes[themeNum];
static int x[themeNum];
static int y[themeNum];
static int hangNum = 2;
static int startX, startY;
static int imgWidth = 200, imgHeight = 100;
static int interSpaceHeng = 40;
static int interSpaceZong = 90;
static int rightSideWidth = 250;
static int titleHeight = 10;
static int colors = RGB(186, 206, 195);
static bool if_back = false;
static int return_show;
static int current_stay;
static TCHAR s[themeNum][20] = { _T("海洋"),_T("火山"),_T("草原"),_T("海洋"),_T("火山"),_T("草原") };
static TCHAR sizeInfo[themeNum][20] = {};
static TCHAR story[themeNum][300] = { _T("  海洋（SEA）是地球上最广阔的水体的总称，海洋的中心部分称作洋，边缘部分称作海，彼此沟通组成统一的水体。"),
						  _T("  火山是一种常见的地貌形态，由地下熔融物质及其携带的固体碎屑冲出地表后堆积形成的山体。地壳之下100-150千米处，有一个全是岩浆“液态区”。"),
						  _T("  草原是地球生态系统的一种，分为热带草原、温带草原等多种类型，是地球上分布最广的植被类型。"),
						  _T("  海洋（SEA）是地球上最广阔的水体的总称，海洋的中心部分称作洋，边缘部分称作海，彼此沟通组成统一的水体。"),
						  _T("  火山是一种常见的地貌形态，由地下熔融物质及其携带的固体碎屑冲出地表后堆积形成的山体。地壳之下100-150千米处，有一个全是岩浆“液态区”。"),
						  _T("  草原是地球生态系统的一种，分为热带草原、温带草原等多种类型，是地球上分布最广的植被类型。") };


void initAll() {
	loadimage(&Themes[0], _T("../sources/pic/主题/海洋.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[1], _T("../sources/pic/主题/火山.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[2], _T("../sources/pic/主题/草原.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[3], _T("../sources/pic/主题/海洋.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[4], _T("../sources/pic/主题/火山.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[5], _T("../sources/pic/主题/草原.jpg"), imgWidth, imgHeight, true);




	for (int i = 0; i < themeNum / 2; i++) {  //迷宫大小和迷雾
		gMazeSizes[i][0] = 20 * (i + 1);
		gMazeSizes[i][1] = 15 * (i + 1);
		/*fog[i] = false;*/
	}
	for (int i = themeNum / 2; i < themeNum; i++) {
		gMazeSizes[i][0] = 35 * (i - 3 + 1);
		gMazeSizes[i][1] = 35 * (i - 3 + 1);
		/*fog[i] = true;*/
	}
	for (int j = 0; j < themeNum; j++) {
		_itoa_s(gMazeSizes[j][0], sizes[j][0], 10);
		_itoa_s(gMazeSizes[j][1], sizes[j][1], 10);
	}

	for (int i = 0; i < themeNum / 2; i++) {  //奖励
		prizes[i] = 100 * (i + 1);
		prizes[i] = 100 * (i + 1);
	}
	for (int i = themeNum / 2; i < themeNum; i++) {
		prizes[i] = 300 * (i - 3 + 1);
		prizes[i] = 300 * (i - 3 + 1);
	}
	for (int j = 0; j < themeNum; j++) {
		_itoa_s(prizes[j], prize[j], 10);
		_itoa_s(prizes[j], prize[j], 10);
	}

}
void drawTheme() {
	int k = 0;
	for (int i = 0; i < 3; i++) { //第一行图片
		x[i] = startX + k * imgWidth + k * interSpaceHeng;
		y[i] = startY;
		setbkcolor(RGB(58, 59, 79));
		clearroundrect(x[i] - 15, y[i] - 18, x[i] + imgWidth + 15, y[i] + imgHeight + 35, 10, 10); //边框颜色
		putimage(x[i], y[i], &Themes[i]);
		settextcolor(colors);
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
		outtextxy(x[i] + imgWidth / 2 - textwidth(s[i]) / 2, y[i] + imgHeight + 5, s[i]);
		setlinecolor(RGB(128, 128, 105));
		rectangle(x[i], y[i], x[i] + imgWidth, y[i] + imgHeight);

		k++;
	}
	k = 0;
	for (int i = 3; i < themeNum; i++) { //第二行图片
		x[i] = startX + k * imgWidth + k * interSpaceHeng;
		y[i] = startY + imgHeight + interSpaceZong;
		setbkcolor(RGB(58, 59, 79));
		clearroundrect(x[i] - 15, y[i] - 18, x[i] + imgWidth + 15, y[i] + imgHeight + 35, 10, 10);
		putimage(x[i], y[i], &Themes[i]);
		settextcolor(colors);
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
		outtextxy(x[i] + imgWidth / 2 - textwidth(s[i]) / 2, y[i] + imgHeight + 5, s[i]);
		setlinecolor(RGB(128, 128, 105));
		rectangle(x[i], y[i], x[i] + imgWidth, y[i] + imgHeight);

		k++;
	}
}
void drawTitle() {
	TCHAR s[] = _T("主题选择");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("宋体"), 0, 0, 700, false, false, false);
	outtextxy(startX, 30, s);
}
void showInfo(int i) {
	setfillcolor(RGB(41, 36, 33));
	fillrectangle(kScreenWidth - rightSideWidth, 0, kScreenWidth, kScreenHeight);
	//显示题目
	settextcolor(RGB(200, 205, 210));
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("宋体"), 0, 0, 700, false, false, false);
	outtextxy(kScreenWidth - rightSideWidth + 5, 30, s[i]);


	//显示故事
	settextcolor(RGB(200, 205, 210));
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("宋体"), 0, 0, 700, false, false, false);
	outtextxy(kScreenWidth - rightSideWidth + 5, 100, _T("简介："));

	settextcolor(RGB(200, 205, 210));
	setbkmode(TRANSPARENT);
	settextstyle(18, 0, _T("宋体"), 0, 0, 700, false, false, false);
	RECT r = { kScreenWidth - rightSideWidth + 5, 140, kScreenWidth, kScreenHeight };
	drawtext(story[i], &r, DT_WORDBREAK | DT_EXTERNALLEADING);


	//显示迷宫大小
	CString sizeSrc;
	CString str_1 = sizes[i][0];
	CString str_2 = sizes[i][1];
	sizeSrc.Format(_T("%s%s%s%s"),
		_T("迷宫大小："),
		str_1, _T("*"), str_2);
	settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
	int sizePosy = 320;
	outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy, sizeSrc);


	//显示模式
	settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
	if (fog[i] == true) {
		outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy + 50, _T("模式：迷雾"));
	}
	else {
		outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy + 50, _T("模式：普通"));
	}



	//显示奖励
	CString prizeSrc;
	CString str = prize[i];
	prizeSrc.Format(_T("%s%s"),
		_T("奖励："),
		str);
	settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
	outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy + 100, prizeSrc);

	//显示剩余时间
	int hour = Time[i] / 3600;
	int minute = Time[i] % 3600 / 60;
	int second = Time[i] % 3600 % 60;
	char s1[12];
	sprintf_s(s1, "%d", hour);
	char s2[12];
	sprintf_s(s2, "%d", minute);
	char s3[12];
	sprintf_s(s3, "%d", second);
	moveto(kScreenWidth - rightSideWidth + 5, sizePosy + 150);
	settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
	outtext(_T("限制用时："));
	for (i = 0; i < 12; i++) {
		if (s1[i] == '\0') {
			break;
		}
		outtext(s1[i]);
	}
	outtext(_T("时"));
	for (i = 0; i < 12; i++) {
		if (s2[i] == '\0') {
			break;
		}
		outtext(s2[i]);
	}
	outtext(_T("分"));
	for (i = 0; i < 12; i++) {
		if (s3[i] == '\0') {
			break;
		}
		outtext(s3[i]);
	}
	outtext(_T("秒"));



}
void drawChooseMaze() {
	return_show = 0;
	mciSendString(_T("open ../sources/music/change_scene.mp3 alias change_scene"), NULL, 0, NULL);
	current_stay = 100;
	if_back = false;
	initAll();
	setbkcolor(RGB(48, 48, 48));
	cleardevice(); //左上颜色

	startX = (kScreenWidth - rightSideWidth - imgWidth * (themeNum / hangNum) - interSpaceHeng * (themeNum / hangNum)) / 2;
	startY = titleHeight + (kScreenHeight - imgHeight * hangNum - interSpaceZong * (hangNum - 1)) / 2;
	setbkcolor(BLACK);
	clearrectangle(0, startY - 40, kScreenWidth - rightSideWidth, kScreenHeight); //左下颜色
	setbkcolor(RGB(41, 36, 33));
	clearrectangle(kScreenWidth - rightSideWidth, 0, kScreenWidth, kScreenHeight); //右边颜色
	setlinecolor(WHITE);
	line(0, startY - 40, kScreenWidth - rightSideWidth, startY - 40);
	line(kScreenWidth - rightSideWidth, 0, kScreenWidth - rightSideWidth, kScreenHeight);

	drawTitle();
	drawTheme();
	BeginBatchDraw();
	while (1) {
		if (MouseHit() == true) {
			MOUSEMSG mes = GetMouseMsg();
			Sleep(5);
			DrawSceneReturnLast();
			FlushBatchDraw();
			if (mes.x >= kScreenWidth - 100 && mes.x <= kScreenWidth &&
				mes.y >= 15 && mes.y <=
				40) {
				if (mes.mkLButton) {
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
			int i;
			for (i = 0; i < themeNum; i++) {
				if (mes.x >= x[i] && mes.x <= x[i] + imgWidth && mes.y >= y[i] && mes.y <= y[i] + imgHeight) {
					setfillcolor(RGB(139, 69, 19));
					fillroundrect(x[i] - 15, y[i] - 18, x[i] + imgWidth + 15, y[i] + imgHeight + 35, 10, 10); //边框颜色
					putimage(x[i], y[i], &Themes[i]);
					settextcolor(colors);
					setbkmode(TRANSPARENT);
					settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
					outtextxy(x[i] + imgWidth / 2 - textwidth(s[i]) / 2, y[i] + imgHeight + 5, s[i]);
					setlinecolor(RGB(128, 128, 105));
					rectangle(x[i], y[i], x[i] + imgWidth, y[i] + imgHeight);
					showInfo(i);

					if (current_stay != i) {
						current_stay = i;
						mciSendString(_T("seek change_scene to start"), 0, 0, 0);
						mciSendString(_T("play change_scene"), NULL, 0, NULL);

					}


					if (mes.mkLButton) {
						currTheme = i;
						gMazeWidth = gMazeSizes[i][0];
						gMazeHeight = gMazeSizes[i][1];
						gPrize = prizes[i];
						gScene = PersonPage;
						if_back = true;
					}
				}
				else {
					setbkcolor(RGB(58, 59, 79));
					clearroundrect(x[i] - 15, y[i] - 18, x[i] + imgWidth + 15, y[i] + imgHeight + 35, 10, 10);
					putimage(x[i], y[i], &Themes[i]);
					settextcolor(colors);
					setbkmode(TRANSPARENT);
					settextstyle(20, 0, _T("宋体"), 0, 0, 700, false, false, false);
					outtextxy(x[i] + imgWidth / 2 - textwidth(s[i]) / 2, y[i] + imgHeight + 5, s[i]);
					setlinecolor(RGB(128, 128, 105));
					rectangle(x[i], y[i], x[i] + imgWidth, y[i] + imgHeight);
				}
			}
		}
		
		if (if_back) {
			mciSendString(_T("close change_scene"), NULL, 0, NULL);
			EndBatchDraw();
			return;
		}
		CheckKeyboardInput();
	}
}
void DrawSceneReturnLast() {
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
static void CheckKeyboardInput() {
	if (!_kbhit()) {
		return;
	}
	char input = _getch();
	if (input == 27) {
		return_show = 2;
		gScene = BeginPage;
		if_back = true;
	}
}
