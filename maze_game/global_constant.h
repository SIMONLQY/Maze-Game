#pragma once
#include <graphics.h>
// ȫ�ֳ�������ʱ���� k ��ͷ��С�շ�����
// ���崰�ڲ���
const int kScreenWidth = 1024; // ��Ϸ���ڿ��
const int kScreenHeight = 540; // ��Ϸ���ڸ߶�
// ��Ϸ������ϷС���ڲ���
const int kGameSideSpace = 5; // ���ھ�����Ϸ�����ھ���
const int kGameWindowWidth = 700;
const int kGameWindowHeight = kScreenHeight - 2 * kGameSideSpace;
// ѡ���������
const int kChoosePersonWidth = 700;
const int kChoosePersonHeight = kScreenHeight;
const int kChoosePersonSideBarWidth = kScreenWidth - kChoosePersonWidth;
const int kChoosePersonSideBarHeight = kScreenHeight;
const int kPersonWidth = 130;
const int kButtonWidth = 200;
const int kButtonHeight = 50;

// һЩ��ɫ
const int red = 1;
const int blue = 2;
const int white = 3;
const int grey = 4;
const int yellow = 5;

// ����
// 0����ʼҳ�棬1���������棬2������ѡ��3����Ϸ��ҳ�棬4���̵�, 
// 5:���ý���
const int BeginPage = 0;
const int ScenePage = 1;
const int PersonPage = 2;
const int PlayPage = 3;
const int StorePage = 4;
const int SettingPage = 5;
const int FirstPage = 6;

// ����ʹ�ô���
const int kSkillTimes[4] = { 0, 3, 6, 3 };

// ���＼��
const int kSkills[7][2] = {
	{0, 0}, {1, 0}, {2, 0}, {3, 0}, {1, 2}, {2, 3}, {3, 1}
};
// ��������
const TCHAR skill0_name[] = _T("�޼���");
const TCHAR skill0_description[] = _T("������");
const TCHAR skill1_name[] = _T("Ѱ·");
const TCHAR skill1_description[] = _T("�����˼��ܣ��㽫��õ���һ��ǰ���ķ���");
const TCHAR skill2_name[] = _T("��Ծ");
const TCHAR skill2_description[] = _T("�����˼��ܣ��㽫����Խ��һ���ϰ�������һ����");
const TCHAR skill3_name[] = _T("��ͨ");
const TCHAR skill3_description[] = _T("�����˼��ܣ��㽫�����������ǰ�½�һ����·");

const bool fog[6] = {
	false, false, false, true, true, true
};
const int fog_range[6] = {
	0, 0, 0, 9, 8, 7
};

const TCHAR kPersonMoney[8][15] = {
	_T("$0"), _T("$1000"), _T("$1500"), _T("$1200"), _T("$5000"),
	_T("$6000"), _T("$7000"), _T("��ӵ��")
};
// �ؿ�������ʱ
const int Time[6] = { 1 * 60,
	2 * 60,
	2 * 60 + 30,
	3 * 60,
	4 * 60,
	5 * 60
};