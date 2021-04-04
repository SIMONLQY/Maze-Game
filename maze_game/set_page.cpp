#include "set_page.h"
extern int gScene;

static IMAGE img_bk;//背景图
static MOUSEMSG m;
static bool gmusic = true;//声音开关
static int gmusic_playing;//音乐选择
static int gdistance;
static UINT chan;


//与音量设置有关
static IAudioEndpointVolume* m_pEndptVolCtrl;
static IMMDeviceEnumerator* m_pEnumerator;
static IMMDevice* m_pDevice;
static HRESULT hr = S_OK;
static float vol;
static float vol1;
static float vol2;
static bool if_back;
static bool return_show;


void set() {
	start_up();
	while (1)
	{
		Sleep(5);
		showset();
		SetDrawReturnLast();
		FlushBatchDraw();
		set_music();
		//SetCheckHoverInput();
		if (if_back) {
			EndBatchDraw();
			return;
		}
	}
}



void start_up()
{
	if_back = false;
	return_show = false;
	loadimage(&img_bk, _T("../sources/pic/背景/Bk.jpg"));
	BeginBatchDraw();
	mciSendString(_T("open bkmusic1.mp3 alias bkmusic_one"), NULL, 0, NULL);//打开背景音乐
	mciSendString(_T("play bkmusic_one repeat"), NULL, 0, NULL);//循环播放
}

void showset()
{
	//固定内容
	setbkcolor(WHITE);
	cleardevice();
	putimage(0, 0, &img_bk);
	setfillcolor(RGB(128, 128, 128));//灰色区域
	solidrectangle(100, 50, 924, 490);
	setfillcolor(RGB(50, 50, 50));//黑色区域
	solidrectangle(110, 60, 914, 480);
	//汉字部分
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30, 0, _T("楷体"));
	//outtextxy(900, 0, _T("Return"));
	RECT r = { 0, 70, 1024, 100 };
	drawtext(_T("设置"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setlinecolor(WHITE);
	line(200, 115, 824, 115);
	settextstyle(20, 0, _T("楷体"));
	outtextxy(200, 130, _T("声音："));
	outtextxy(200, 160, _T("音量："));
	/*outtextxy(200, 190, _T("音乐："));
	outtextxy(200, 340, _T("迷宫格之间的距离："));*/
	//绘图部分
	setfillcolor(RGB(128, 128, 128));
	solidcircle(270, 140, 6);//声音开关
		//音量
	fillrectangle(260, 168, 270, 178);
	fillrectangle(270, 168, 280, 178);
	fillrectangle(280, 168, 290, 178);
	fillrectangle(290, 168, 300, 178);
	fillrectangle(300, 168, 310, 178);
	fillrectangle(310, 168, 320, 178);
	fillrectangle(320, 168, 330, 178);
	fillrectangle(330, 168, 340, 178);
	fillrectangle(340, 168, 350, 178);
	fillrectangle(350, 168, 360, 178);

	/*settextstyle(18, 0, _T("楷体"));
	outtextxy(270, 190, _T("music1"));
	outtextxy(270, 220, _T("music2"));
	outtextxy(270, 250, _T("music3"));
	outtextxy(270, 280, _T("music4"));
	outtextxy(270, 310, _T("music5"));
	solidcircle(350, 200, 6);
	solidcircle(350, 230, 6);
	solidcircle(350, 260, 6);
	solidcircle(350, 290, 6);
	solidcircle(350, 320, 6);
	outtextxy(400, 340, _T("1"));
	solidcircle(420, 348, 6);
	outtextxy(450, 340, _T("3"));
	solidcircle(470, 348, 6);
	outtextxy(500, 340, _T("5"));
	solidcircle(520, 348, 6);*/

	//更新的内容
	setfillcolor(RGB(0, 128, 0));
	if (gmusic == true)
	{
		solidcircle(270, 140 * gmusic, 4);//声音
		solidcircle(350, gmusic_playing * 30 + 170, 4);//音乐

		//音量
		int i;
		for (i = 0; i < vol / 0.1; i++)
			fillrectangle(260 + i * 10, 168, 270 + i * 10, 178);
	}
	//solidcircle(50 * (gdistance / 2) + 420, 348, 4);//距离
}

void set_music()
{
	if (MouseHit())
	{
		m = GetMouseMsg();


		int x = m.x;
		int y = m.y;
		if (x >= kScreenWidth - 100 && x <= kScreenWidth && y >= 15 && y <=
			40) {
			if (m.mkLButton) {
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





		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > 900 && m.y > 0 && m.x < 1000 && m.y < 100)//return
			{

			}
			if (m.x > 270 - 6 && m.y > 140 - 6 && m.x < 270 + 6 && m.y < 140 + 6)//声音开关 
			{
				//准备设备数据
				hr = CoInitialize(NULL);
				// Create instance for MMDevices...  
				hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)& m_pEnumerator);
				// Get default Andio Endpoint  
				hr = m_pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &m_pDevice);
				// Activate devices...  
				hr = m_pDevice->Activate(__uuidof(IAudioEndpointVolume),
					CLSCTX_ALL, NULL,
					(void**)& m_pEndptVolCtrl);
				hr = m_pEndptVolCtrl->GetChannelCount(&chan);



				if (gmusic == true) {
					gmusic = false;
					vol = 0;
					vol1 = 0;
					vol2 = 0;
				}
				else {
					gmusic = true;
					vol = 0.25;
					vol1 = 0.25;
					vol2 = 0.25;
				}



				//设置音量
				hr = m_pEndptVolCtrl->SetMute(0, &GUID_NULL);
				hr = m_pEndptVolCtrl->SetMasterVolumeLevelScalar(vol, &GUID_NULL);
				hr = m_pEndptVolCtrl->SetChannelVolumeLevelScalar(0, vol1, &GUID_NULL);
				hr = m_pEndptVolCtrl->SetChannelVolumeLevelScalar(1, vol2, &GUID_NULL);

				hr = m_pEndptVolCtrl->GetMasterVolumeLevelScalar(&vol);
				hr = m_pEndptVolCtrl->GetChannelVolumeLevelScalar(0, &vol1);
				hr = m_pEndptVolCtrl->GetChannelVolumeLevelScalar(1, &vol2);
				CoUninitialize();
			}
			if (m.y > 168 && m.y < 178 && m.x>260 && m.x < 360)//控制音量
			{


				//准备设备数据
				hr = CoInitialize(NULL);
				// Create instance for MMDevices...  
				hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)& m_pEnumerator);
				// Get default Andio Endpoint  
				hr = m_pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &m_pDevice);
				// Activate devices...  
				hr = m_pDevice->Activate(__uuidof(IAudioEndpointVolume),
					CLSCTX_ALL, NULL,
					(void**)& m_pEndptVolCtrl);
				hr = m_pEndptVolCtrl->GetChannelCount(&chan);

				vol = (m.x - 260) * 0.01;
				vol1 = vol;
				vol2 = vol;

				//设置音量部分

				hr = m_pEndptVolCtrl->SetMute(0, &GUID_NULL);

				hr = m_pEndptVolCtrl->SetMasterVolumeLevelScalar(vol, &GUID_NULL);
				hr = m_pEndptVolCtrl->SetChannelVolumeLevelScalar(0, vol1, &GUID_NULL);
				hr = m_pEndptVolCtrl->SetChannelVolumeLevelScalar(1, vol2, &GUID_NULL);

				hr = m_pEndptVolCtrl->GetMasterVolumeLevelScalar(&vol);
				hr = m_pEndptVolCtrl->GetChannelVolumeLevelScalar(0, &vol1);
				hr = m_pEndptVolCtrl->GetChannelVolumeLevelScalar(1, &vol2);
				CoUninitialize();
			}

			//if (m.y > 348 - 6 && m.y < 348 + 6 && ((m.x > 420 - 6 && m.x < 420 + 6) || (m.x > 470 - 6 && m.x < 470 + 6) || (m.x > 520 - 6 && m.x < 520 + 6)))//距离
			//	gdistance = (m.x - 420 + 6) / 50 * 2 + 1;

			//if (m.x > 350 - 6 && m.x < 350 + 6 && ((m.y > 200 - 6 && m.y < 200 + 6) || (m.y > 230 - 6 && m.y < 230 + 6) || (m.y > 260 - 6 && m.y < 260 + 6) || (m.y > 290 - 6 && m.y < 290 + 6) || (m.y > 320 - 6 && m.y < 320 + 6)) && gmusic == true)
			//{
			//	//选择音乐 
			//	switch (gmusic_playing)//关闭之前的音乐
			//	{
			//	case 1:
			//		mciSendString(_T("close bkmusic_one"), NULL, 0, NULL);
			//	case 2:
			//		mciSendString(_T("close bkmusic_two"), NULL, 0, NULL);
			//	case 3:
			//		mciSendString(_T("close bkmusic_three"), NULL, 0, NULL);
			//	case 4:
			//		mciSendString(_T("close bkmusic_four"), NULL, 0, NULL);
			//	case 5:
			//		mciSendString(_T("close bkmusic_five"), NULL, 0, NULL);
			//	}
			//	gmusic_playing = (m.y - 200 + 6) / 30 + 1;
			//	switch (gmusic_playing)//播放新的音乐
			//	{
			//	case 1:
			//		mciSendString(_T("open bkmusic1.mp3 alias bkmusic_one"), NULL, 0, NULL);
			//		mciSendString(_T("play bkmusic_one repeat"), NULL, 0, NULL);
			//	case 2:
			//		mciSendString(_T("open bkmusic2.mp3 alias bkmusic_two"), NULL, 0, NULL);
			//		mciSendString(_T("play bkmusic_two repeat"), NULL, 0, NULL);
			//	case 3:
			//		mciSendString(_T("open bkmusic3.mp3 alias bkmusic_three"), NULL, 0, NULL);
			//		mciSendString(_T("play bkmusic_three repeat"), NULL, 0, NULL);
			//	case 4:
			//		mciSendString(_T("open bkmusic4.mp3 alias bkmusic_four"), NULL, 0, NULL);
			//		mciSendString(_T("play bkmusic_four repeat"), NULL, 0, NULL);
			//	case 5:
			//		mciSendString(_T("open bkmusic5.mp3 alias bkmusic_five"), NULL, 0, NULL);
			//		mciSendString(_T("play bkmusic_five repeat"), NULL, 0, NULL);
			//	}
			//}
		}
	}
}


void SetDrawReturnLast() {
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

void SetCheckHoverInput() {
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