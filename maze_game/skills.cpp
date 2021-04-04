#include "skills.h"

extern MazeSquare** squares;
extern int gMazeEndX;
extern MazeSquare** closeList;
extern int gMazeEndY;
extern int closeNum;
extern Person person;
extern int sillLeftTime0;
extern int sillLeftTime1;
extern int sillLeftTime2;
extern int sillLeftTime3;

void useSkill(int skillNum) {
	if (skillNum == 0) { //无技能
		return;
	}
	if (skillNum == 1) { // 寻路
		if (sillLeftTime1 <= 0)
			return;
		//setfillcolor(BLACK);
		//fillrectangle(300, 100, 400, 200);
		//FlushBatchDraw();
		mciSendString(_T("seek 寻路 to start"), NULL, 0, NULL);
		mciSendString(_T("play 寻路"), NULL, 0, NULL);
		getThroughPath(&squares[person.y][person.x],
			&squares[gMazeEndY][gMazeEndX]);

		squares[closeList[1]->x][closeList[1]->y].special = true;
		sillLeftTime1--;
		//setfillcolor(YELLOW);
		//fillrectangle(300, 100, 400, 200);
		//FlushBatchDraw();
	}

	if (skillNum == 2) { // 飞跃
		if (sillLeftTime2 <= 0)
			return;
		char input = _getch();
		if (input == 'a' && squares[person.y][person.x-2].color == red) {
			mciSendString(_T("seek 飞跃 to start"), NULL, 0, NULL);
			mciSendString(_T("play 飞跃"), NULL, 0, NULL);
			person.x -=2;
			sillLeftTime2--;
		}
		if (input == 's' && squares[person.y + 2][person.x].color == red) {
			mciSendString(_T("seek 飞跃 to start"), NULL, 0, NULL);
			mciSendString(_T("play 飞跃"), NULL, 0, NULL);
			person.y+=2;
			sillLeftTime2--;
		}
		if (input == 'd'&&squares[person.y][person.x+2].color == red) {
			mciSendString(_T("seek 飞跃 to start"), NULL, 0, NULL);
			mciSendString(_T("play 飞跃"), NULL, 0, NULL);
			person.x+=2;
			sillLeftTime2--;
		}
		if (input == 'w'&&squares[person.y - 2][person.x].color == red) {
			mciSendString(_T("seek 飞跃 to start"), NULL, 0, NULL);
			mciSendString(_T("play 飞跃"), NULL, 0, NULL);
			person.y-=2;
			sillLeftTime2--;
		}
	}

	if (skillNum == 3) { //破坏
		if (sillLeftTime3 <= 0)
			return;
		char input = _getch();
		if (input == 'a' &&squares[person.y][person.x - 1].color == grey) {
			mciSendString(_T("seek 连通 to start"), NULL, 0, NULL);
			mciSendString(_T("play 连通"), NULL, 0, NULL);
			squares[person.y][person.x - 1].color = red;
			sillLeftTime3--;
		}
		else if (input == 's'&&squares[person.y+1][person.x].color == grey) {
			mciSendString(_T("seek 连通 to start"), NULL, 0, NULL);
			mciSendString(_T("play 连通"), NULL, 0, NULL);
			squares[person.y+1][person.x].color = red;
			sillLeftTime3--;
		}
		else if (input == 'd'&&squares[person.y][person.x + 1].color == grey) {
			mciSendString(_T("seek 连通 to start"), NULL, 0, NULL);
			mciSendString(_T("play 连通"), NULL, 0, NULL);
			squares[person.y][person.x + 1].color = red;
			sillLeftTime3--;
		}
		else if (input == 'w'&&squares[person.y - 1][person.x].color == grey) {
			mciSendString(_T("seek 连通 to start"), NULL, 0, NULL);
			mciSendString(_T("play 连通"), NULL, 0, NULL);
			squares[person.y-1 ][person.x].color = red;
			sillLeftTime3--;
		}
	}
}