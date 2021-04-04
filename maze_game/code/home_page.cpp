#include "home_page.h"
static int welcome_time = 0;
extern int gScene;
static IMAGE img_bk, img_mark, img_start;
const int scollImageNum = 6;
static IMAGE scollImages[scollImageNum];
static bool if_back = false;
static int sc = 0; ////����չʾ����ͼƬ

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
		mciSendString(_T("open ../sources/music/���¿�ʼ.mp3 alias ���¿�ʼ"), NULL, 0, NULL);
		showWelcome();
		welcome_time += 1;
	}
	mciSendString(_T("seek ��ҳ to start"), NULL, 0, NULL);
	mciSendString(_T("play ��ҳ"), NULL, 0, NULL);
	mciSendString(_T("seek ��ʼҳ��1 to start"), NULL, 0, NULL);
	mciSendString(_T("play ��ʼҳ��1 repeat"), NULL, 0, NULL);
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
	loadimage(&img_bk, _T("../sources/pic/����/2.jpg"), kScreenWidth, kScreenHeight, true);
	loadimage(&img_mark, _T("../sources/pic/����/mark.jpg"));
	loadimage(&img_start, _T("../sources/pic/����/start.jpg"));
	char scollBackNames[scollImageNum][5] = { "1","2","3","4","5","6" };
	CString picName;
	for (int i = 0; i < scollImageNum; i++) {
		CString p = scollBackNames[i];
		picName.Format(_T("%s%s%s"),
			_T("../sources/pic/����/scollBack"),
			p, _T(".jpg"));
		loadimage(&scollImages[i], picName, 600, 400, true);
	}
	BeginBatchDraw();
}

void showWelcome()
{
	mciSendString(_T("play ���¿�ʼ repeat"), NULL, 0, NULL);
	setbkcolor(WHITE);
	cleardevice();
	putimage(0, 0, &img_bk);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(0, 255, 255));
	settextstyle(100, 0, _T("����"));
	outtextxy(350, 200, _T("������"));
	settextcolor(RGB(211, 211, 211));
	settextstyle(25, 0, _T("����"));
	outtextxy(400, 500, _T("�������������Ϸ"));
	FlushBatchDraw();
	_getch();
	mciSendString(_T("close ���¿�ʼ"), NULL, 0, NULL);
}


void showStart()
{

	putimage(0, 0, &img_bk);
	putimage(250, 30, &img_start);
	//putimage(40, 30, &img_mark);
	setfillcolor(RGB(77, 77, 77)); //����ͼƬ�ı߿�
	fillroundrect(scollImageX - 4, 36, scollImageX + scollImages[sc].getwidth() + 4, 40 + scollImages[sc].getheight() + 4, 10, 10);
	putimage(scollImageX, 40, &scollImages[sc]);

	setfillcolor(RGB(77, 77, 77));     //�̵� ���� ��ʼ��Ϸ������ʽ
	satrtButtonX = scollImageX + scollImages[sc].getwidth() + 50;
	sheZhiY = startButtonY + scollImages[sc].getheight() - 70;
	storeY = startButtonY + scollImages[sc].getheight() / 2 - 70 / 2;
	solidroundrect(satrtButtonX, startButtonY, satrtButtonX + 230, startButtonY + 70, 10, 10);     //��ʼ��Ϸ
	solidroundrect(satrtButtonX, storeY, satrtButtonX + 230, storeY + 70, 10, 10);     //�̵�
	solidroundrect(satrtButtonX, sheZhiY, satrtButtonX + 230, sheZhiY + 70, 10, 10);       //����


	setbkmode(TRANSPARENT);   //�̵� ���� ��ʼ��Ϸ������ʽ
	settextcolor(RGB(237, 237, 237));
	settextstyle(30, 0, _T("����"));
	RECT r1 = { satrtButtonX, startButtonY, satrtButtonX + 220, startButtonY + 70 };
	drawtext(_T("��ʼ��Ϸ"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r2 = { satrtButtonX, storeY, satrtButtonX + 220, storeY + 70 };
	drawtext(_T("�̵�"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { satrtButtonX, sheZhiY, satrtButtonX + 220, sheZhiY + 70 };
	drawtext(_T("����"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
			// ��ʼ��Ϸ
			if (m.y > startButtonY && m.y < startButtonY + 70) {
				gScene = ScenePage;
				EndBatchDraw();
				if_back = true;
			}
			// �̵�
			else if (m.y > storeY && m.y < storeY + 70) {
				gScene = StorePage;
				EndBatchDraw();
				if_back = true;
			}
			// ����
			else if (m.y > sheZhiY && m.y < sheZhiY + 70) {
				gScene = SettingPage;
				EndBatchDraw();
				if_back = true;
			}
			;
			//// ѫ��ǽ
			//else if (m.x > 10 && m.y > 200 && m.x < 100 && m.y < 270)
			//	;
		}
	}
}



