#include "choose_maze.h"
#include<stdlib.h>
//#include"global_variables.h"

extern int gScene;
extern int gPrize;
extern int currTheme;
extern int gMazeHeight;
extern int gMazeWidth;
const int themeNum = 6;     //��������
static int gMazeSizes[themeNum][2];   //�Թ���С
static char sizes[themeNum][2][25];
static int prizes[themeNum];   //����
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
static TCHAR s[themeNum][20] = { _T("����"),_T("��ɽ"),_T("��ԭ"),_T("����"),_T("��ɽ"),_T("��ԭ") };
static TCHAR sizeInfo[themeNum][20] = {};
static TCHAR story[themeNum][300] = { _T("  ����SEA���ǵ������������ˮ����ܳƣ���������Ĳ��ֳ����󣬱�Ե���ֳ��������˴˹�ͨ���ͳһ��ˮ�塣"),
						  _T("  ��ɽ��һ�ֳ����ĵ�ò��̬���ɵ����������ʼ���Я���Ĺ�����м����ر��ѻ��γɵ�ɽ�塣�ؿ�֮��100-150ǧ�״�����һ��ȫ���ҽ���Һ̬������"),
						  _T("  ��ԭ�ǵ�����̬ϵͳ��һ�֣���Ϊ�ȴ���ԭ���´���ԭ�ȶ������ͣ��ǵ����Ϸֲ�����ֲ�����͡�"),
						  _T("  ����SEA���ǵ������������ˮ����ܳƣ���������Ĳ��ֳ����󣬱�Ե���ֳ��������˴˹�ͨ���ͳһ��ˮ�塣"),
						  _T("  ��ɽ��һ�ֳ����ĵ�ò��̬���ɵ����������ʼ���Я���Ĺ�����м����ر��ѻ��γɵ�ɽ�塣�ؿ�֮��100-150ǧ�״�����һ��ȫ���ҽ���Һ̬������"),
						  _T("  ��ԭ�ǵ�����̬ϵͳ��һ�֣���Ϊ�ȴ���ԭ���´���ԭ�ȶ������ͣ��ǵ����Ϸֲ�����ֲ�����͡�") };


void initAll() {
	loadimage(&Themes[0], _T("../sources/pic/����/����.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[1], _T("../sources/pic/����/��ɽ.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[2], _T("../sources/pic/����/��ԭ.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[3], _T("../sources/pic/����/����.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[4], _T("../sources/pic/����/��ɽ.jpg"), imgWidth, imgHeight, true);
	loadimage(&Themes[5], _T("../sources/pic/����/��ԭ.jpg"), imgWidth, imgHeight, true);




	for (int i = 0; i < themeNum / 2; i++) {  //�Թ���С������
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

	for (int i = 0; i < themeNum / 2; i++) {  //����
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
	for (int i = 0; i < 3; i++) { //��һ��ͼƬ
		x[i] = startX + k * imgWidth + k * interSpaceHeng;
		y[i] = startY;
		setbkcolor(RGB(58, 59, 79));
		clearroundrect(x[i] - 15, y[i] - 18, x[i] + imgWidth + 15, y[i] + imgHeight + 35, 10, 10); //�߿���ɫ
		putimage(x[i], y[i], &Themes[i]);
		settextcolor(colors);
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
		outtextxy(x[i] + imgWidth / 2 - textwidth(s[i]) / 2, y[i] + imgHeight + 5, s[i]);
		setlinecolor(RGB(128, 128, 105));
		rectangle(x[i], y[i], x[i] + imgWidth, y[i] + imgHeight);

		k++;
	}
	k = 0;
	for (int i = 3; i < themeNum; i++) { //�ڶ���ͼƬ
		x[i] = startX + k * imgWidth + k * interSpaceHeng;
		y[i] = startY + imgHeight + interSpaceZong;
		setbkcolor(RGB(58, 59, 79));
		clearroundrect(x[i] - 15, y[i] - 18, x[i] + imgWidth + 15, y[i] + imgHeight + 35, 10, 10);
		putimage(x[i], y[i], &Themes[i]);
		settextcolor(colors);
		setbkmode(TRANSPARENT);
		settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
		outtextxy(x[i] + imgWidth / 2 - textwidth(s[i]) / 2, y[i] + imgHeight + 5, s[i]);
		setlinecolor(RGB(128, 128, 105));
		rectangle(x[i], y[i], x[i] + imgWidth, y[i] + imgHeight);

		k++;
	}
}
void drawTitle() {
	TCHAR s[] = _T("����ѡ��");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("����"), 0, 0, 700, false, false, false);
	outtextxy(startX, 30, s);
}
void showInfo(int i) {
	setfillcolor(RGB(41, 36, 33));
	fillrectangle(kScreenWidth - rightSideWidth, 0, kScreenWidth, kScreenHeight);
	//��ʾ��Ŀ
	settextcolor(RGB(200, 205, 210));
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("����"), 0, 0, 700, false, false, false);
	outtextxy(kScreenWidth - rightSideWidth + 5, 30, s[i]);


	//��ʾ����
	settextcolor(RGB(200, 205, 210));
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, _T("����"), 0, 0, 700, false, false, false);
	outtextxy(kScreenWidth - rightSideWidth + 5, 100, _T("��飺"));

	settextcolor(RGB(200, 205, 210));
	setbkmode(TRANSPARENT);
	settextstyle(18, 0, _T("����"), 0, 0, 700, false, false, false);
	RECT r = { kScreenWidth - rightSideWidth + 5, 140, kScreenWidth, kScreenHeight };
	drawtext(story[i], &r, DT_WORDBREAK | DT_EXTERNALLEADING);


	//��ʾ�Թ���С
	CString sizeSrc;
	CString str_1 = sizes[i][0];
	CString str_2 = sizes[i][1];
	sizeSrc.Format(_T("%s%s%s%s"),
		_T("�Թ���С��"),
		str_1, _T("*"), str_2);
	settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
	int sizePosy = 320;
	outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy, sizeSrc);


	//��ʾģʽ
	settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
	if (fog[i] == true) {
		outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy + 50, _T("ģʽ������"));
	}
	else {
		outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy + 50, _T("ģʽ����ͨ"));
	}



	//��ʾ����
	CString prizeSrc;
	CString str = prize[i];
	prizeSrc.Format(_T("%s%s"),
		_T("������"),
		str);
	settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
	outtextxy(kScreenWidth - rightSideWidth + 5, sizePosy + 100, prizeSrc);

	//��ʾʣ��ʱ��
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
	settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
	outtext(_T("������ʱ��"));
	for (i = 0; i < 12; i++) {
		if (s1[i] == '\0') {
			break;
		}
		outtext(s1[i]);
	}
	outtext(_T("ʱ"));
	for (i = 0; i < 12; i++) {
		if (s2[i] == '\0') {
			break;
		}
		outtext(s2[i]);
	}
	outtext(_T("��"));
	for (i = 0; i < 12; i++) {
		if (s3[i] == '\0') {
			break;
		}
		outtext(s3[i]);
	}
	outtext(_T("��"));



}
void drawChooseMaze() {
	return_show = 0;
	mciSendString(_T("open ../sources/music/change_scene.mp3 alias change_scene"), NULL, 0, NULL);
	current_stay = 100;
	if_back = false;
	initAll();
	setbkcolor(RGB(48, 48, 48));
	cleardevice(); //������ɫ

	startX = (kScreenWidth - rightSideWidth - imgWidth * (themeNum / hangNum) - interSpaceHeng * (themeNum / hangNum)) / 2;
	startY = titleHeight + (kScreenHeight - imgHeight * hangNum - interSpaceZong * (hangNum - 1)) / 2;
	setbkcolor(BLACK);
	clearrectangle(0, startY - 40, kScreenWidth - rightSideWidth, kScreenHeight); //������ɫ
	setbkcolor(RGB(41, 36, 33));
	clearrectangle(kScreenWidth - rightSideWidth, 0, kScreenWidth, kScreenHeight); //�ұ���ɫ
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
					fillroundrect(x[i] - 15, y[i] - 18, x[i] + imgWidth + 15, y[i] + imgHeight + 35, 10, 10); //�߿���ɫ
					putimage(x[i], y[i], &Themes[i]);
					settextcolor(colors);
					setbkmode(TRANSPARENT);
					settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
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
					settextstyle(20, 0, _T("����"), 0, 0, 700, false, false, false);
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
	settextstyle(25, 0, _T("����"), 0, 0, FW_SEMIBOLD,
		false, true, false);
	outtextxy(kScreenWidth - 100, 15, _T("Return"));
	settextstyle(25, 0, _T("����"), 0, 0, 0,
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
