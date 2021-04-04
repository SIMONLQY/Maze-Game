#pragma once
#include <graphics.h>
// 全局常量命名时，以 k 开头，小驼峰命名
// 整体窗口布局
const int kScreenWidth = 1024; // 游戏窗口宽度
const int kScreenHeight = 540; // 游戏窗口高度
// 游戏界面游戏小窗口布局
const int kGameSideSpace = 5; // 窗口距离游戏主窗口距离
const int kGameWindowWidth = 700;
const int kGameWindowHeight = kScreenHeight - 2 * kGameSideSpace;
// 选择人物界面
const int kChoosePersonWidth = 700;
const int kChoosePersonHeight = kScreenHeight;
const int kChoosePersonSideBarWidth = kScreenWidth - kChoosePersonWidth;
const int kChoosePersonSideBarHeight = kScreenHeight;
const int kPersonWidth = 130;
const int kButtonWidth = 200;
const int kButtonHeight = 50;

// 一些颜色
const int red = 1;
const int blue = 2;
const int white = 3;
const int grey = 4;
const int yellow = 5;

// 主题
// 0：开始页面，1：场景界面，2：人物选择，3：游戏主页面，4：商店, 
// 5:设置界面
const int BeginPage = 0;
const int ScenePage = 1;
const int PersonPage = 2;
const int PlayPage = 3;
const int StorePage = 4;
const int SettingPage = 5;
const int FirstPage = 6;

// 技能使用次数
const int kSkillTimes[4] = { 0, 3, 6, 3 };

// 人物技能
const int kSkills[7][2] = {
	{0, 0}, {1, 0}, {2, 0}, {3, 0}, {1, 2}, {2, 3}, {3, 1}
};
// 技能描述
const TCHAR skill0_name[] = _T("无技能");
const TCHAR skill0_description[] = _T("无描述");
const TCHAR skill1_name[] = _T("寻路");
const TCHAR skill1_description[] = _T("发动此技能，你将会得到下一步前进的方向");
const TCHAR skill2_name[] = _T("飞跃");
const TCHAR skill2_description[] = _T("发动此技能，你将可以越过一个障碍跳到另一格中");
const TCHAR skill3_name[] = _T("连通");
const TCHAR skill3_description[] = _T("发动此技能，你将可以在你的面前新建一条道路");

const bool fog[6] = {
	false, false, false, true, true, true
};
const int fog_range[6] = {
	0, 0, 0, 9, 8, 7
};

const TCHAR kPersonMoney[8][15] = {
	_T("$0"), _T("$1000"), _T("$1500"), _T("$1200"), _T("$5000"),
	_T("$6000"), _T("$7000"), _T("已拥有")
};
// 关卡限制用时
const int Time[6] = { 1 * 60,
	2 * 60,
	2 * 60 + 30,
	3 * 60,
	4 * 60,
	5 * 60
};