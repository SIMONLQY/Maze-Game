#include "create_maze.h"
extern int gMazeHeight;
extern int gMazeWidth;

extern bool is_reach;

extern int gMazeStartX;
extern int gMazeStartY;
extern int gMazeEndX;
extern int gMazeEndY;

MazeSquare** squares;
BlueAssemble blue_assemble;

void CreateMaze() {
	is_reach = false;
	CreateMatrix();
	InitMatrix();
	while (blue_assemble.num != 0) {
		UpdateMatrix();
	}
	FinishMaze();
	Clean();
	is_reach = false;
}

void CreateMatrix() {
	// ÉêÇë¾ØÕóÄÚ´æ
	squares = new MazeSquare*[(gMazeHeight+2)];
	for (int i = 0; i < (gMazeHeight+2); i++) {
		squares[i] = new MazeSquare[(gMazeWidth+2)];
	}
	InitSquare();
	InitBlueAssemble();
}
void InitSquare() {
	
	for (int i = 0; i < (gMazeHeight + 2); i++) {
		for (int j = 0; j < (gMazeWidth + 2); j++) {
			squares[i][j].x = i;
			squares[i][j].y = j;
			if (i == 0 || i == (gMazeHeight + 2) - 1 || j == 0 || j == (gMazeWidth + 2) - 1) {
				squares[i][j].color = grey;
			}
			else if (i % 2 == 1 && j % 2 == 1) {
				squares[i][j].color = yellow;
			}
			else {
				squares[i][j].color = white;
			}
			squares[i][j].g = 0;
			squares[i][j].h = 0;
			squares[i][j].isInClose = false;
			squares[i][j].isInOpen = false;
			squares[i][j].special = false;
		}
	}
}

void InitBlueAssemble() {
	blue_assemble.num = 0;
	blue_assemble.blue_squares = 
		new MazeSquare[gMazeHeight * gMazeWidth];
}
void ResetBlueAssemble(int number) {
	for (int i = number; i < blue_assemble.num - 1; i++) {
		blue_assemble.blue_squares[i] 
			= blue_assemble.blue_squares[i + 1];
	}
	blue_assemble.num--;
}
void AddBlueAssemble(MazeSquare square) {
	int x = square.x;
	int y = square.y;
	if (squares[x + 1][y].color == white) {
		squares[x + 1][y].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[x + 1][y];
		blue_assemble.num++;
	}
	if (squares[x - 1][y].color == white) {
		squares[x - 1][y].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[x - 1][y];
		blue_assemble.num++;
	}
	if (squares[x][y+1].color == white) {
		squares[x][y+1].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[x][y+1];
		blue_assemble.num++;
	}
	if (squares[x][y-1].color == white) {
		squares[x][y-1].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[x][y-1];
		blue_assemble.num++;
	}
}
void InitMatrix() {
	squares[gMazeStartY][gMazeStartX].color = red;
	squares[gMazeEndY][gMazeEndX].color = red;
	if (squares[gMazeStartY][gMazeStartX + 1].color != grey) {
		squares[gMazeStartY][gMazeStartX + 1].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[gMazeStartY][gMazeStartX + 1];
		blue_assemble.num++;
		
	}	
	if (squares[gMazeStartY][gMazeStartX - 1].color != grey) {
		squares[gMazeStartY][gMazeStartX - 1].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[gMazeStartY][gMazeStartX - 1];
		blue_assemble.num++;
	}	
	if (squares[gMazeStartY + 1][gMazeStartX].color != grey) {
		squares[gMazeStartY + 1][gMazeStartX].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[gMazeStartY + 1][gMazeStartX];
		blue_assemble.num++;
	}
	if (squares[gMazeStartY - 1][gMazeStartX].color != grey) {
		squares[gMazeStartY - 1][gMazeStartX].color = blue;
		blue_assemble.blue_squares[blue_assemble.num]
			= squares[gMazeStartY - 1][gMazeStartX];
		blue_assemble.num++;
	}
	srand(time(0));
}
void UpdateMatrix() {
	int choice = rand() % blue_assemble.num;
	int x = blue_assemble.blue_squares[choice].x;
	int y = blue_assemble.blue_squares[choice].y;
	if (squares[x + 1][y].color == yellow) {
		squares[x + 1][y].color = red;
		AddBlueAssemble(squares[x + 1][y]);
		squares[x][y].color = red;
	}
	else if (squares[x - 1][y].color == yellow) {
		squares[x - 1][y].color = red;
		AddBlueAssemble(squares[x - 1][y]);
		squares[x][y].color = red;
	}
	else if (squares[x][y+1].color == yellow) {
		squares[x][y+1].color = red;
		AddBlueAssemble(squares[x][y+1]);
		squares[x][y].color = red;
	}
	else if (squares[x][y - 1].color == yellow) {
		squares[x][y - 1].color = red;
		AddBlueAssemble(squares[x][y - 1]);
		squares[x][y].color = red;
	}
	else {
		if (is_reach == false) {
			if (!CheckFinal(choice))
				squares[x][y].color = grey;
		}
		else {
			squares[x][y].color = grey;
		}
	}
	ResetBlueAssemble(choice);
}
void FinishMaze() {
	for (int i = 0; i < (gMazeHeight+2); i++) {
		for (int j = 0; j < (gMazeWidth+2); j++) {
			if (squares[i][j].color == white) {
				squares[i][j].color = grey;
			}
		}
	}
}
void SetEndPoint(int x, int y) {
	gMazeEndX = x;
	gMazeEndY = y;
}
void SetStartPoint(int x, int y) {
	gMazeStartX = x;
	gMazeStartY = y;
}
void SetPointRand() {
	srand(time(0));
	int start_x = 1;
	int start_y = 1;
	int end_x = 1;
	int end_y = 1;
	while (abs(end_x - start_x) + abs(end_y - start_y) <= gMazeHeight / 2 + gMazeWidth / 2) {
		int x2 = rand() % ((gMazeWidth + 1) / 2);
		end_x = 2 * x2 + 1;
		int y2 = rand() % ((gMazeHeight + 1) / 2);
		end_y = 2 * y2 + 1;
	}
	SetStartPoint(start_x, start_y);
	SetEndPoint(end_x, end_y);
}
bool CheckFinal(int choice) {
	int x = blue_assemble.blue_squares[choice].x;
	int y = blue_assemble.blue_squares[choice].y;
	if (x + 1 == gMazeEndY && y == gMazeEndX) {
		squares[x][y].color = red;
		is_reach = true;
		return true;
	}
	if (x - 1 == gMazeEndY && y == gMazeEndX) {
		squares[x][y].color = red;
		is_reach = true;
		return true;
	}
	if (x == gMazeEndY && y + 1 == gMazeEndX) {
		squares[x][y].color = red;
		is_reach = true;
		return true;
	}
	if (x == gMazeEndY && y - 1 == gMazeEndX) {
		squares[x][y].color = red;
		is_reach = true;
		return true;
	}
	return false;
}
void Clean() {
	/*for (int i = 0; i < blue_assemble.num; i++) {
		delete
	}*/
	delete[]blue_assemble.blue_squares;
}