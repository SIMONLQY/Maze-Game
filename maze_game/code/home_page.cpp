#include "home_page.h"
static int welcome_time = 0;
extern int gScene;
static IMAGE img_bk, img_mark, img_start;
const int scollImageNum = 6;
static IMAGE scollImages[scollImageNum];
static bool if_back = false;
static int sc = 0; ////决定展示那张图片

static int scollImageX = 60;
static int satrtButtonX;
static int startButtonY = 40;
static int sheZhiY;
static int storeY;

extern void ShowHomePage()
{

	if_back = false;
	startup();
	if (welcome_time == 0) {
		mciSendString(_T("open ../sources/music/故事开始.mp3 alias 故事开始"), NULL, 0, NULL);
		showWelcome();
		welcome_time += 1;
	}
	mciSendString(_T("seek 翻页 to start"), NULL, 0, NULL);
	mciSendString(_T("play 翻页"), NULL, 0, NULL);
	mciSendString(_T("seek 开始页面1 to start"), NULL, 0, NULL);
	mciSendString(_T("play 开始页面1 repeat"), NULL, 0, NULL);
	int time1 = clock();
	int time2 = clock();
	while (1) {
		showStart();
		FlushBatchDraw();
		Sleep(5);
		click();
		if (if_back == true) {
			return;
		}
		time2 = clock();
		if ((time2 - time1) / 1000 == 2) {
			time1 = time2;
			int temp = sc;
			sc++;
			if (sc == 6) {
				sc = 0;
			}
		}
	}
}

void startup()
{
	loadimage(&img_bk, _T("../sources/pic/背景/2.jpg"), kScreenWidth, kScreenHeight, true);
	loadimage(&img_mark, _T("../sources/pic/背景/mark.jpg"));
	loadimage(&img_start, _T("../sources/pic/背景/start.jpg"));
	char scollBackNames[scollImageNum][5] = { "1","2","3","4","5","6" };
	CString picName;
	for (int i = 0; i < scollImageNum; i++) {
		CString p = scollBackNames[i];
		picName.Format(_T("%s%s%s"),
			_T("../sources/pic/背景/scollBack"),
			p, _T(".jpg"));
		loadimage(&scollImages[i], picName, 600, 400, true);
	}
	BeginBatchDraw();
}

void showWelcome()
{
	mciSendString(_T("play 故事开始 repeat"), NULL, 0, NULL);
	setbkcolor(WHITE);
	cleardevice();
	putimage(0, 0, &img_bk);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(0, 255, 255));
	settextstyle(100, 0, _T("楷体"));
	outtextxy(350, 200, _T("旅行者"));
	settextcolor(RGB(211, 211, 211));
	settextstyle(25, 0, _T("楷体"));
	outtextxy(400, 500, _T("按任意键进入游戏"));
	FlushBatchDraw();
	_getch();
	mciSendString(_T("close 故事开始"), NULL, 0, NULL);
}


void showStart()
{

	putimage(0, 0, &img_bk);
	putimage(250, 30, &img_start);
	//putimage(40, 30, &img_mark);
	setfillcolor(RGB(77, 77, 77)); //滚动图片的边框
	fillroundrect(scollImageX - 4, 36, scollImageX + scollImages[sc].getwidth() + 4, 40 + scollImages[sc].getheight() + 4, 10, 10);
	putimage(scollImageX, 40, &scollImages[sc]);

	setfillcolor(RGB(77, 77, 77));     //商店 设置 开始游戏按键样式
	satrtButtonX = scollImageX + scollImages[sc].getwidth() + 50;
	sheZhiY = startButtonY + scollImages[sc].getheight() - 70;
	storeY = startButtonY + scollImages[sc].getheight() / 2 - 70 / 2;
	solidroundrect(satrtButtonX, startButtonY, satrtButtonX + 230, startButtonY + 70, 10, 10);     //开始游戏
	solidroundrect(satrtButtonX, storeY, satrtButtonX + 230, storeY + 70, 10, 10);     //商店
	solidroundrect(satrtButtonX, sheZhiY, satrtButtonX + 230, sheZhiY + 70, 10, 10);       //设置


	setbkmode(TRANSPARENT);   //商店 设置 开始游戏字体样式
	settextcolor(RGB(237, 237, 237));
	settextstyle(30, 0, _T("楷体"));
	RECT r1 = { satrtButtonX, startButtonY, satrtButtonX + 220, startButtonY + 70 };
	drawtext(_T("开始游戏"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r2 = { satrtButtonX, storeY, satrtButtonX + 220, storeY + 70 };
	drawtext(_T("商店"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { satrtButtonX, sheZhiY, satrtButtonX + 220, sheZhiY + 70 };
	drawtext(_T("设置"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();

}

void click()
{
	if (MouseHit())
	{
		MOUSEMSG m;
		m = GetMouseMsg();
		if (m.mkLButton && m.x > satrtButtonX && m.x < satrtButtonX + 220)
		{
			// 开始游戏
			if (m.y > startButtonY && m.y < startButtonY + 70) {
				gScene = ScenePage;
				EndBatchDraw();
				if_back = true;
			}
			// 商店
			else if (m.y > storeY && m.y < storeY + 70) {
				gScene = StorePage;
				EndBatchDraw();
				if_back = true;
			}
			// 设置
			else if (m.y > sheZhiY && m.y < sheZhiY + 70) {
				gScene = SettingPage;
				EndBatchDraw();
				if_back = true;
			}
			;
			//// 勋章墙
			//else if (m.x > 10 && m.y > 200 && m.x < 100 && m.y < 270)
			//	;
		}
	}
}



