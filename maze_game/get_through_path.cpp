#include "get_through_path.h"
extern int closeNum;
extern int gMazeHeight;
extern int gMazeWidth;
extern Person person;
extern MazeSquare** squares;
static int openNum;

static MazeSquare** openList; //open列表 

MazeSquare** closeList;

void sort(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j > i; j--) {
			int k1 = 0, k2 = 0;
			for (k1 = 0; k1 < closeNum; k1++) { //找到j和j-1的父亲 父亲后加入closeList 表示自己后加入openList 
				if (openList[j]->parent->x == closeList[k1]->x && openList[j]->parent->y == closeList[k1]->y) {
					break;
				}
			}
			for (k2 = 0; k2 < closeNum; k2++) {
				if (openList[j - 1]->parent->x == closeList[k2]->x && openList[j - 1]->parent->y == closeList[k2]->y) {
					break;
				}
			}
			if (((openList[j]->g + openList[j]->h) <= (openList[j - 1]->g + openList[j - 1]->h)) && k1 > k2) {  //如果F相同 后加入openList的排前面 
				MazeSquare* temp;
				temp = openList[j];
				openList[j] = openList[j - 1];
				openList[j - 1] = temp;
			}
		}
	}
}
static void finalClose(MazeSquare* startSquare) {  //最后复查closeList如果存在之前加进去但不是路径的就删除
	int k = closeNum - 1;
	while (k > 0) {
		if (closeList[k - 1] != closeList[k]->parent) {
			for (int j = k - 1; j < closeNum - 1; j++) {
				closeList[j] = closeList[j + 1];
			}
			closeNum--;
		}
		k--;
	}
}
static void changeNeighbours(MazeSquare* neighbour, MazeSquare* currNode, MazeSquare* endSquare) {
	if (neighbour->color != grey && neighbour->isInClose == false) {
		if (neighbour->isInOpen == false) { //不在open列表中 
			neighbour->g = currNode->g + 1;
			neighbour->h = abs(endSquare->x - neighbour->x) + abs(endSquare->y - neighbour->y);
			neighbour->parent = currNode;
			neighbour->isInOpen = true;
			openList[openNum++] = neighbour;
			sort(openNum);
		}
		else {
			// 判断选择走当前路线到这个neighbour是否更优
			if ((neighbour->g) > (currNode->g + 1)) {
				for (int i = 0; i < openNum; i++) {
					if (openList[i]->x == neighbour->x && openList[i]->y == neighbour->y) {
						openList[i]->g = currNode->g + 1;
						openList[i]->parent = currNode;
						break;
					}
				}
				sort(openNum);
			}
		}
	}
}

void getThroughPath(MazeSquare* startSquare, MazeSquare* endSquare) {
	for (int i = 0; i <= gMazeHeight; i++) {
		for (int j = 0; j <= gMazeWidth; j++) {
			squares[i][j].g = 0;
			squares[i][j].h = 0;
			squares[i][j].parent = NULL;
			squares[i][j].isInClose = false;
			squares[i][j].isInOpen = false;
		}
	}
	if (closeList != NULL) {
		delete[]closeList;
	}
	if (openList != NULL) {
		delete[]openList;
	}
	openList = new MazeSquare * [gMazeHeight * gMazeWidth];
	closeList = new MazeSquare * [gMazeHeight * gMazeWidth];
	closeNum = 0;
	openNum = 0;
	MazeSquare* currNode;
	bool isFound;

	openList[openNum++] = startSquare;
	startSquare->isInOpen = true;
	startSquare->h = abs(endSquare->x - startSquare->x) + abs(endSquare->y - startSquare->y);
	isFound = false;
	while (1) {
		MazeSquare* a = openList[1];/////
		MazeSquare* b = &squares[3][1];
		MazeSquare* c = &squares[3][2];
		currNode = openList[0];
		openList[0] = openList[--openNum];
		sort(openNum);
		closeList[closeNum++] = currNode;

		currNode->isInClose = true;
		currNode->isInOpen = false;
		if (currNode->x == endSquare->x && currNode->y == endSquare->y) {
			isFound = true;
			finalClose(startSquare);
			break;
		}
		if (currNode->x + 1 <= gMazeHeight) {
			changeNeighbours(&squares[currNode->x + 1][currNode->y], currNode, endSquare);
		}
		if (currNode->y + 1 <= gMazeWidth) {
			changeNeighbours(&squares[currNode->x][currNode->y + 1], currNode, endSquare);
		}
		if (currNode->x - 1 > 0) {
			changeNeighbours(&squares[currNode->x - 1][currNode->y], currNode, endSquare);
		}
		if (currNode->y - 1 > 0) {
			changeNeighbours(&squares[currNode->x][currNode->y - 1], currNode, endSquare);
		}
	}

}

