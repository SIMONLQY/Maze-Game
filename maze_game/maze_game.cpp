#include "global_variables.h"
#include "global_constant.h"
#include "start.h"
#include "home_page.h"
#include "create_maze.h"
#include "game_page.h"
#include "choose_person.h"
#include "choose_maze.h"
#include "store.h"
#include "set_page.h"
#pragma comment(lib,"Winmm.lib") // 引用 Windows Multimedia API

static bool if_set = false;
extern int gScene;

int main()
{
	Start();
	mciSendString(_T("open ../sources/music/选择人物.mp3 alias 选择人物"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/商店.mp3 alias 商店"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/选择地图.mp3 alias 选择地图"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/翻页声.mp3 alias 翻页"), NULL, 0, NULL);
	mciSendString(_T("open ../sources/music/wellcome.mp3 alias wellcome"), NULL, 0, NULL);
	ShowHomePage();
	mciSendString(_T("pause wellcome"), NULL, 0, NULL);
	while (1) {
		

		if (gScene == BeginPage) {
			mciSendString(_T("seek 翻页 to start"), NULL, 0, NULL);
			mciSendString(_T("play 翻页"), NULL, 0, NULL);
			if (!if_set) {
				mciSendString(_T("seek wellcome to start"), NULL, 0, NULL);
			}
			
			ShowHomePage();
			mciSendString(_T("pause wellcome"), NULL, 0, NULL);
			if_set = false;
			continue;
		}
		if (gScene == ScenePage) {
			mciSendString(_T("seek 翻页 to start"), NULL, 0, NULL);
			mciSendString(_T("play 翻页"), NULL, 0, NULL);
			mciSendString(_T("seek 选择地图 to start"), NULL, 0, NULL);
			mciSendString(_T("play 选择地图 repeat"), NULL, 0, NULL);
			drawChooseMaze();
			if_set = false;
			mciSendString(_T("pause 选择地图"), NULL, 0, NULL);
			continue;
		}
		if (gScene == PersonPage) {
			mciSendString(_T("seek 翻页 to start"), NULL, 0, NULL);
			mciSendString(_T("play 翻页"), NULL, 0, NULL);
			if_set = false;
			mciSendString(_T("seek 选择人物 to start"), NULL, 0, NULL);
			mciSendString(_T("play 选择人物 repeat"), NULL, 0, NULL);
			ChoosePerson();
			continue;
		}
		if (gScene == PlayPage) {
			SetPointRand();
			if_set = false;
			GamePage();

			continue;
		}
		if (gScene == StorePage) {
			mciSendString(_T("seek 翻页 to start"), NULL, 0, NULL);
			mciSendString(_T("play 翻页"), NULL, 0, NULL);
			mciSendString(_T("seek 商店 to start"), NULL, 0, NULL);
			mciSendString(_T("play 商店 repeat"), NULL, 0, NULL);
			if_set = false;
			ShowStore();
			mciSendString(_T("pause 商店"), NULL, 0, NULL);
			continue;
		}
		if (gScene == SettingPage) {
			mciSendString(_T("seek 翻页 to start"), NULL, 0, NULL);
			mciSendString(_T("play 翻页"), NULL, 0, NULL);
			mciSendString(_T("play wellcome"), NULL, 0, NULL);
			set();
			if_set = true;
			mciSendString(_T("pause wellcome"), NULL, 0, NULL);
			continue;
		}
	}
	mciSendString(_T("close 翻页"), NULL, 0, NULL);
	mciSendString(_T("close 选择人物"), NULL, 0, NULL);
	mciSendString(_T("close 选择地图"), NULL, 0, NULL);
	mciSendString(_T("close 商店"), NULL, 0, NULL);
	mciSendString(_T("close wellcome"), NULL, 0, NULL);
}
