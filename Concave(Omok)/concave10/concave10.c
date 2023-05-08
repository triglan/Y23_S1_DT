#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

/*
	README : 2번 문제에서 3~4개짜리 돌만 방어하기로 하는데
	이 때 3 3 돌은 6개짜리 돌로 취급해 모양이 바뀌지 않습니다.
*/

//bool 타입
#define bool int
#define TRUE 1
#define FALSE 0
//플레이어
#define BLANK 0
#define BLACK 1
#define WHITE 2
//바둑판 크기
#define SIZE 19
#define LINE 37

typedef struct {
	int s;//연속의 시작
	int e;//연속의 끝
	int line;
	int blank;//사이 빈칸
	int max;//연속 횟수
	int down;//아래줄 위줄
}checkline;

int Stone[SIZE][SIZE] = { 0 };
int defStone[SIZE][SIZE] = { 0 };

int turn = 0;					// 0턴 초기화
int inputX, inputY;

void StartStone();					// 초기값, 테스트 용
void PrintStone(int stone, int def);	// 돌 출력
void PrintBoard();					// 보드판 출력
void CountStone();					// 검돌, 흰돌 몇개인지 세기
void ScanTurn();					// 입력 받기
bool IsSamePos();					// 중복 입력 받기
void InputStone(int inputX, int inputY);// 돌 추가

void ScanSide();
void ScanLine();
void ScanRightUp();
void ScanRightDown();

int main()
{
	char order;

	StartStone();
	while (TRUE)
	{
		for (int y = 0; y < SIZE; y++)
		{
			for (int x = 0; x < SIZE; x++)
			{
				defStone[y][x] = 0;
			}
		}
		ScanSide();
		printf("\n");
		ScanLine();
		printf("\n");
		ScanRightUp();
		printf("\n");
		ScanRightDown();
		printf("\n");

		PrintBoard();	//바둑판 그리기
		ScanTurn();	//스캔

		printf("명령어 : 돌 놓기(x,y) : ");
		scanf_s("%d %d", &inputX, &inputY);
		system("cls");

		if (inputX<0 || inputX > SIZE || inputY < 0 || inputY > SIZE)
		{
			printf("잘못된 값입니다 다시 입력해 주세요.\n");
			continue;
		}
		if (IsSamePos() == TRUE)	//중복 확인 중복이면 while 다시 시작
			break;
		InputStone(inputX, inputY);	//돌 출력

	}
}
void StartStone()
{
	Stone[1][1] = BLACK;
	Stone[1][2] = BLACK;
	
	Stone[1][4] = BLACK;
	Stone[1][5] = BLACK;
	Stone[1][6] = BLACK;

	Stone[1][8] = BLACK;
	Stone[1][9] = BLACK;
	Stone[1][10] = BLACK;
	Stone[1][11] = BLACK;
	Stone[1][12] = BLACK;

	Stone[0][1] = WHITE;
	Stone[0][2] = WHITE;
	Stone[0][3] = WHITE;
	Stone[0][4] = WHITE;

	Stone[0][8] = BLACK;
	Stone[0][9] = BLACK;
	Stone[0][10] = BLACK;

	Stone[0][12] = BLACK;
	Stone[0][13] = BLACK;
	Stone[0][14] = BLACK;

	Stone[2][3] = WHITE;
	Stone[3][4] = WHITE;
	Stone[4][5] = WHITE;
	Stone[5][6] = WHITE;
	Stone[6][6] = WHITE;
	Stone[7][8] = WHITE;
	Stone[8][9] = WHITE;

	Stone[12][8] = WHITE;
	Stone[11][9] = WHITE;
	Stone[10][10] = WHITE;
	Stone[10][11] = WHITE;
	Stone[9][11] = WHITE;
	Stone[8][12] = WHITE;

	Stone[12][9] = WHITE;
	Stone[12][10] = WHITE;
	Stone[13][11] = WHITE;
	Stone[14][12] = WHITE;
	Stone[15][13] = WHITE;
	Stone[16][14] = WHITE;
	Stone[12][11] = WHITE;
	Stone[12][12] = WHITE;
	Stone[12][13] = WHITE;
	Stone[12][14] = WHITE;
}
void PrintStone(int stone, int def)
{
	if (stone == BLANK)
		printf("■");
	else if (stone == BLACK)
		if(def == 1)
			printf("☆");
		else
			printf("○");
	else if (stone == WHITE)
		if (def == 1)
			printf("★");
		else
			printf("●");

}
void PrintBoard()
{
	CountStone();
	for (int y = 0; y < SIZE; y++)
	{//상하 for문
		for (int x = 0; x < SIZE; x++)
		{//좌우 for문

			PrintStone(Stone[y][x], defStone[y][x]);
		}
		printf("\n");
	}
}
bool IsSamePos()
{
	if (Stone[inputY][inputX] != BLANK)	// 공백칸이 아니라면
	{
		printf("이미 돌이 놓여 있습니다.\n");
		return TRUE;
	}
	else
		return FALSE;
}
void CountStone()
{
	int BlackStone = 0;
	int WhiteStone = 0;
	for (int UpDown = 0; UpDown < SIZE; UpDown++)
	{
		for (int Side = 0; Side < SIZE; Side++)
		{
			if (Stone[UpDown][Side] == BLACK)
				BlackStone++;
			if (Stone[UpDown][Side] == WHITE)
				WhiteStone++;
		}
	}
	printf("검은 돌 : %d 흰 돌 : %d\n", BlackStone, WhiteStone);
}
void ScanTurn()
{
	if (turn % 2 == 0)	//홀수, 흑돌 턴일 때
	{
		printf("흑돌");
	}
	else				//짝수, 백돌 턴일 때
	{
		printf("백돌");
	}
	printf(" 턴입니다. 수를 놓아 주십시오 가로[0~18] 세로[0~18] : ");

}
void InputStone(int x, int y)
{
	if (turn % 2 == 0)	//흑돌 턴일 때
		Stone[y][x] = BLACK;
	else
		Stone[y][x] = WHITE;
	turn++;			//1턴 증가
}
void ScanSide()
{
	checkline lineb[SIZE][SIZE] = { 0 };
	checkline linew[SIZE][SIZE] = { 0 };
	checkline linebmax[SIZE] = { 0 };
	checkline linewmax[SIZE] = { 0 };
	int linebc = 0, linewc = 0;//해당 줄에 몇번째 줄인지

	for (int y = 0; y < SIZE; y++)
	{
		linebc = 0, linewc = 0;
		
		for (int x = 0; x < SIZE; x++)
		{
			//검은돌 가로줄 넣기
			if (Stone[y][x] == BLACK)
			{//3~5번째 줄이면 s=3 e=5
				lineb[y][linebc].s = x;
				while (1)
				{
					lineb[y][linebc].e = x++;
					lineb[y][linebc].max++;
					if (Stone[y][x] != BLACK) {
							x--;
						linebc++;
						break;
					}
				}
			}

			//흰돌 가로줄 넣기
			if (Stone[y][x] == WHITE)
			{//3~5번째 줄이면 s=3 e=5
				linew[y][linewc].s = x;
				while (1)
				{
					linew[y][linewc].e = x++;
					linew[y][linewc].max++;
					if (Stone[y][x] != WHITE) {
						x--;
						linewc++;
						break;
					}
				}
			}
		}

		//최종에 돌 집어넣기
		if (linebc < 1) {
			linebmax[y].max = lineb[y][0].max;
			linebmax[y].s = lineb[y][0].s;
			linebmax[y].e = lineb[y][0].e;
			linebmax[y].line = y;
			linebmax[y].blank = -1;

			if (lineb[y][0].max == 3 || lineb[y][0].max == 4) {
				for (int k = lineb[y][0].s; k <= lineb[y][0].e; k++) {
					if (k != lineb[y][0].e + 1)//공백 칸이 아니면
						defStone[y][k] = 1;
				}
			}
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linebc; i++) {
				if (lineb[y][i].e == lineb[y][i + 1].s - 2) {
					if (linebmax[y].max < lineb[y][i].max + lineb[y][i + 1].max) {//두 단어 칸이 더 크면
						linebmax[y].s = lineb[y][i].s;
						linebmax[y].e = lineb[y][i + 1].e;
						linebmax[y].line = y;
						linebmax[y].blank = lineb[y][i].e + 1;
						linebmax[y].max = lineb[y][i].max + lineb[y][i + 1].max - 1;

						if ((lineb[y][i].max + lineb[y][i + 1].max - 1) == 3 || (lineb[y][i].max + lineb[y][i + 1].max - 1) == 4) {
							for (int k = lineb[y][i].s; k <= lineb[y][i + 1].e; k++){
								if (k != lineb[y][i].e + 1)//공백 칸이 아니면
									defStone[y][k] = 1;
							}
						}
					}
				}
				else if (linebmax[y].max < lineb[y][i].max) {
					linebmax[y].s = lineb[y][i].s;
					linebmax[y].e = lineb[y][i].e;
					linebmax[y].line = y;
					linebmax[y].blank = -1;
					linebmax[y].max = lineb[y][i].max;

					if (lineb[y][i].max == 3 || lineb[y][i].max == 4) {
						for (int k = lineb[y][i].s; k <= lineb[y][i].e; k++) {
							if (k != lineb[y][i].e + 1)//공백 칸이 아니면
								defStone[y][k] = 1;
						}
					}
				}
			}
		}
		//최종에 흰돌 집어넣기
		if (linewc < 2) {
			linewmax[y].max = linew[y][0].max;
			linewmax[y].s = linew[y][0].s;
			linewmax[y].e = linew[y][0].e;
			linewmax[y].line = y;
			linewmax[y].blank = -1;

			if (linew[y][0].max == 3 || linew[y][0].max == 4) {
				for (int k = linew[y][0].s; k <= linew[y][0].e; k++) {
					if (k != linew[y][0].e + 1)//공백 칸이 아니면
						defStone[y][k] = 1;
				}
			}
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linewc; i++) {
				if (linew[y][i].e == linew[y][i + 1].s - 2) {
					if (linewmax[y].max < linew[y][i].max + linew[y][i + 1].max) {//두 단어 칸이 더 크면
						linewmax[y].s = linew[y][i].s;
						linewmax[y].e = linew[y][i + 1].e;
						linewmax[y].line = y;
						linewmax[y].blank = linew[y][i].e + 1;
						linewmax[y].max = linew[y][i].max + linew[y][i + 1].max - 1;

						if ((linew[y][i].max + linew[y][i + 1].max - 1) == 3 || (linew[y][i].max + linew[y][i + 1].max - 1) == 4) {
							for (int k = linew[y][i].s; k <= linew[y][i + 1].e; k++) {
								if (k != linew[y][i].e + 1)//공백 칸이 아니면
									defStone[y][k] = 1;
							}
						}
					}
				}
				else if (linewmax[y].max < linew[y][i].max) {
					linewmax[y].s = linew[y][i].s;
					linewmax[y].e = linew[y][i].e;
					linewmax[y].line = y;
					linewmax[y].blank = -1;
					linewmax[y].max = linew[y][i].max;

					if (linew[y][i].max == 3 || linew[y][i].max == 4) {
						for (int k = linew[y][i].s; k <= linew[y][i].e; k++) {
							if (k != linew[y][i].e + 1)//공백 칸이 아니면
								defStone[y][k] = 1;
						}
					}
				}
			}
		}
		
	}
	//전체에서 가장 긴 줄
	{
		checkline realbmax = { 0 };
		for (int i = 0; i < SIZE; i++){
			if (realbmax.max < linebmax[i].max) {
				realbmax = linebmax[i];
			}
		}
		checkline realwmax = { 0 };
		for (int i = 0; i < SIZE; i++){
			if (realwmax.max < linewmax[i].max) {
				realwmax = linewmax[i];
			}
		}

		if (realwmax.max < realbmax.max) {
			printf("가로줄 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					printf("(%d,%d)", i, realbmax.line);
		}
		else if (realwmax.max == realbmax.max) {
			printf("가로줄 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					printf("(%d,%d)", i, realbmax.line);
			printf("\n");
			printf("가로줄 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					printf("(%d,%d)", i, realwmax.line);
		}
		else {
			printf("가로줄 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					printf("(%d,%d)", i, realwmax.line);
		}
		printf("\n");
	}
}
void ScanLine()
{
	checkline lineb[SIZE][SIZE] = { 0 };
	checkline linew[SIZE][SIZE] = { 0 };
	checkline linebmax[SIZE] = { 0 };
	checkline linewmax[SIZE] = { 0 };
	int linebc = 0, linewc = 0;//해당 줄에 몇번째 줄인지

	for (int x = 0; x < SIZE; x++)
	{
		linebc = 0, linewc = 0;

		for (int y = 0; y < SIZE; y++)
		{
			//검은돌 가로줄 넣기
			if (Stone[y][x] == BLACK)
			{//3~5번째 줄이면 s=3 e=5
				lineb[x][linebc].s = y;
				while (1)
				{
					lineb[x][linebc].e = y++;
					lineb[x][linebc].max++;
					if (Stone[y][x] != BLACK) {
						y--;
						linebc++;
						break;
					}
				}
			}

			//흰돌 가로줄 넣기
			if (Stone[y][x] == WHITE)
			{//3~5번째 줄이면 s=3 e=5
				linew[x][linewc].s = y;
				while (1)
				{
					linew[x][linewc].e = y++;
					linew[x][linewc].max++;
					if (Stone[y][x] != WHITE) {
						y--;
						linewc++;
						break;
					}
				}
			}
		}

		//최종에 흰돌 집어넣기
		if (linebc < 1) {
			linebmax[x].max = lineb[x][0].max;
			linebmax[x].s = lineb[x][0].s;
			linebmax[x].e = lineb[x][0].e;
			linebmax[x].line = x;
			linebmax[x].blank = -1;

			if (lineb[x][0].max == 3 || lineb[x][0].max == 4){
				for (int k = lineb[x][0].s; k <= lineb[x][0].e; k++) {
					if (k != lineb[x][0].e + 1)//공백 칸이 아니면
						defStone[k][x] = 1;
				}
			}
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linebc; i++) {
				if (lineb[x][i].e == lineb[x][i + 1].s - 2) {
					if (linebmax[x].max < lineb[x][i].max + lineb[x][i + 1].max) {//두 단어 칸이 더 크면
						linebmax[x].s = lineb[x][i].s;
						linebmax[x].e = lineb[x][i + 1].e;
						linebmax[x].line = x;
						linebmax[x].blank = lineb[x][i].e + 1;
						linebmax[x].max = lineb[x][i].max + lineb[x][i + 1].max - 1;

						if ((lineb[x][i].max + lineb[x][i + 1].max - 1) == 3 || (lineb[x][i].max + lineb[x][i + 1].max - 1) == 4) {
							for (int k = lineb[x][i].s; k <= lineb[x][i].e; k++) {
								if (k != lineb[x][i].e + 1)//공백 칸이 아니면
									defStone[k][x] = 1;
							}
						}
					}
				}
				else if (linebmax[x].max < lineb[x][i].max) {
					linebmax[x].s = lineb[x][i].s;
					linebmax[x].e = lineb[x][i].e;
					linebmax[x].line = x;
					linebmax[x].blank = -1;
					linebmax[x].max = lineb[x][i].max;

					if ((lineb[x][i].max + lineb[x][i + 1].max - 1) == 3 || (lineb[x][i].max + lineb[x][i + 1].max - 1) == 4) {
						for (int k = lineb[x][i].s; k <= lineb[x][i + 1].e; k++) {
							if (k != lineb[x][i].e + 1)//공백 칸이 아니면
								defStone[k][x] = 1;
						}
					}
				}
			}
		}
		//최종에 흰돌 집어넣기
		if (linewc < 2) {
			linewmax[x].max = linew[x][0].max;
			linewmax[x].s = linew[x][0].s;
			linewmax[x].e = linew[x][0].e;
			linewmax[x].line = x;
			linewmax[x].blank = -1;

			if (linew[x][0].max == 3 || linew[x][0].max == 4) {
				for (int k = linew[x][0].s; k <= linew[x][0].e; k++) {
					if (k != linew[x][0].e + 1)//공백 칸이 아니면
						defStone[k][x] = 1;
				}
			}
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linewc; i++) {
				if (linew[x][i].e == linew[x][i + 1].s - 2) {
					if (linewmax[x].max < linew[x][i].max + linew[x][i + 1].max) {//두 단어 칸이 더 크면
						linewmax[x].s = linew[x][i].s;
						linewmax[x].e = linew[x][i + 1].e;
						linewmax[x].line = x;
						linewmax[x].blank = linew[x][i].e + 1;
						linewmax[x].max = linew[x][i].max + linew[x][i + 1].max - 1;

						if ((linew[x][i].max + linew[x][i + 1].max - 1) == 3 || (linew[x][i].max + linew[x][i + 1].max - 1) == 4) {
							for (int k = linew[x][i].s; k <= linew[x][i].e; k++) {
								if (k != linew[x][i].e + 1)//공백 칸이 아니면
									defStone[k][x] = 1;
							}
						}
					}
				}
				else if (linewmax[x].max < linew[x][i].max) {
					linewmax[x].s = linew[x][i].s;
					linewmax[x].e = linew[x][i].e;
					linewmax[x].line = x;
					linewmax[x].blank = -1;
					linewmax[x].max = linew[x][i].max;

					if ((linew[x][i].max + linew[x][i + 1].max - 1) == 3 || (linew[x][i].max + linew[x][i + 1].max - 1) == 4) {
						for (int k = linew[x][i].s; k <= linew[x][i].e; k++) {
							if (k != linew[x][i + 1].e + 1)//공백 칸이 아니면
								defStone[k][x] = 1;
						}
					}
				}
			}
		}

	}
	//전체에서 가장 긴 줄
	{
		checkline realbmax = { 0 };
		for (int i = 0; i < SIZE; i++) {
			if (realbmax.max < linebmax[i].max) {
				realbmax = linebmax[i];
			}
		}
		checkline realwmax = { 0 };
		for (int i = 0; i < SIZE; i++) {
			if (realwmax.max < linewmax[i].max) {
				realwmax = linewmax[i];
			}
		}

		if (realwmax.max < realbmax.max) {
			printf("세로줄 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					printf("(%d,%d)", realbmax.line, i);
		}
		else if (realwmax.max == realbmax.max) {
			printf("세로줄 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					printf("(%d,%d)", realbmax.line, i);
			printf("\n");
			printf("세로줄 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					printf("(%d,%d)", realwmax.line, i);
		}
		else {
			printf("세로줄 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					printf("(%d,%d)", realwmax.line, i);
		}
		printf("\n");
	}
}
void ScanRightUp()
{
	checkline lineb[LINE][LINE] = { 0 };
	checkline linew[LINE][LINE] = { 0 };
	checkline linebmax[LINE] = { 0 };
	checkline linewmax[LINE] = { 0 };
	int linebc[LINE] = { 0 }, linewc[LINE] = { 0 };//해당 줄에 몇번째 줄인지
	int linecount = 0;
	for (int y = 0; y < SIZE; y++)
	{
		linebc[y] = 0, linewc[y] = 0;
		for (int x = 0; x <= y; x++)
		{
			//검은돌
			if (Stone[y - x][x] == BLACK)
			{
				lineb[linecount][linebc[y]].s = x;
				while (1)
				{
					lineb[linecount][linebc[y]].e = x++;
					lineb[linecount][linebc[y]].max++;
					if (Stone[y - x][x] != BLACK) {
						x--;
						linebc[y]++;
						break;
					}
				}
			}
			//흰돌
			if (Stone[y - x][x] == WHITE)
			{
				linew[linecount][linewc[y]].s = x;
				while (1)
				{
					linew[linecount][linewc[y]].e = x++;
					linew[linecount][linewc[y]].max++;
					if (Stone[y - x][x] != WHITE) {
						x--;
						linewc[y]++;
						break;
					}
				}
			}
		}
		linecount++;
	}
	for (int x = 1; x < SIZE; x++)
	{
		linebc[x] = 0, linewc[x] = 0;
		for (int y = x; y <= SIZE; y++)
		{
			//검은돌
			if (Stone[y][x - y] == BLACK)
			{
				lineb[linecount][linebc[y]].s = y;
				while (1)
				{
					lineb[linecount][linebc[x]].e = y++;
					lineb[linecount][linebc[x]].max++;
					if (Stone[y][x - y] != BLACK) {
						y--;
						linebc[y]++;
						break;
					}
				}
			}
			//흰돌
			if (Stone[y][x - y] == WHITE)
			{
				linew[linecount][linewc[x]].s = y;
				while (1)
				{
					linew[linecount][linewc[x]].e = y++;
					linew[linecount][linewc[x]].max++;
					if (Stone[y][x - y] != WHITE) {
						y--;
						linewc[y]++;
						break;
					}
				}
			}
		}
		linecount++;
	}
	//라인
	for (int y = 0; y < LINE; y++)
	{
		//최종에 검돌 집어넣기
		if (linebc[y] < 2) {
			linebmax[y].max = lineb[y][0].max;
			linebmax[y].s = lineb[y][0].s;
			linebmax[y].e = lineb[y][0].e;
			linebmax[y].line = y;
			linebmax[y].blank = -1;

			if (lineb[y][0].max == 3 || lineb[y][0].max == 4) {
				for (int k = linew[y][0].s; k <= linew[y][0].e; k++) {
					if (k != linew[y][0].e + 1)//공백 칸이 아니면
						defStone[y - k][k] = 1;
				}
			}
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linebc[y]; i++) {
				if (lineb[y][i].e == lineb[y][i + 1].s - 2) {
					if (linebmax[y].max < lineb[y][i].max + lineb[y][i + 1].max) {//두 단어 칸이 더 크면
						linebmax[y].s = lineb[y][i].s;
						linebmax[y].e = lineb[y][i + 1].e;
						linebmax[y].line = y;
						linebmax[y].blank = lineb[y][i].e + 1;
						linebmax[y].max = lineb[y][i].max + lineb[y][i + 1].max - 1;

						if (lineb[y][i].max == 3 || lineb[y][i].max == 4) {
							for (int k = linew[y][i].s; k <= linew[y][i].e; k++) {
								if (k != linew[y][i].e + 1)//공백 칸이 아니면
									defStone[y - k][k] = 1;
							}
						}
					}
				}
				else if (linebmax[y].max < lineb[y][i].max) {
					linebmax[y].s = lineb[y][i].s;
					linebmax[y].e = lineb[y][i].e;
					linebmax[y].line = y;
					linebmax[y].blank = -1;
					linebmax[y].max = lineb[y][i].max;

					if (lineb[y][i].max == 3 || lineb[y][i].max == 4) {
						for (int k = linew[y][i].s; k <= linew[y][i].e; k++) {
							if (k != linew[y][i].e + 1)//공백 칸이 아니면
								defStone[y - k][k] = 1;
						}
					}
				}
			}
		}
		//최종에 흰돌 집어넣기
		if (linewc[y] < 2) {
			linewmax[y].max = linew[y][0].max;
			linewmax[y].s = linew[y][0].s;
			linewmax[y].e = linew[y][0].e;
			linewmax[y].line = y;
			linewmax[y].blank = -1;
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linewc[y]; i++) {
				if (linew[y][i].e == linew[y][i + 1].s - 2) {
					if (linewmax[y].max < linew[y][i].max + linew[y][i + 1].max) {//두 단어 칸이 더 크면
						linewmax[y].s = linew[y][i].s;
						linewmax[y].e = linew[y][i + 1].e;
						linewmax[y].line = y;
						linewmax[y].blank = linew[y][i].e + 1;
						linewmax[y].max = linew[y][i].max + linew[y][i + 1].max - 1;
					}
				}
				else if (linewmax[y].max < linew[y][i].max) {
					linewmax[y].s = linew[y][i].s;
					linewmax[y].e = linew[y][i].e;
					linewmax[y].line = y;
					linewmax[y].blank = -1;
					linewmax[y].max = linew[y][i].max;
				}
			}
		}
	}
	

	//전체에서 가장 긴 줄
	{
		checkline realbmax = { 0 };
		for (int i = 0; i < LINE; i++) {
			if (realbmax.max < linebmax[i].max) {
				realbmax = linebmax[i];
			}
		}
		checkline realwmax = { 0 };
		for (int i = 0; i < LINE; i++) {
			if (realwmax.max < linewmax[i].max) {
				realwmax = linewmax[i];
			}
		}

		if (realwmax.max < realbmax.max) {
			printf("우상향 대각선 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					printf("(%d,%d)", i, realbmax.line - i);
		}
		else if (realwmax.max == realbmax.max) {
			printf("우상향 대각선 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					printf("(%d,%d)", i, realbmax.line - i);
			printf("\n");
			printf("우상향 대각선 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					printf("(%d,%d)", i, realwmax.line - i);
		}
		else {
			printf("우상향 대각선 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					printf("(%d,%d)", i, realwmax.line - i);
		}
		printf("\n");
	}
}
void ScanRightDown()
{
	checkline lineb[LINE][LINE] = { 0 };
	checkline linew[LINE][LINE] = { 0 };
	checkline linebmax[LINE] = { 0 };
	checkline linewmax[LINE] = { 0 };
	int linebc[LINE] = { 0 }, linewc[LINE] = { 0 };//해당 줄에 몇번째 줄인지
	int linecount = 0;
	for (int y = 0; y < SIZE; y++)
	{
		linebc[linecount] = 0, linewc[linecount] = 0;
		for (int x = 0; x < SIZE - y; x++)
		{
			//검은돌
			if (Stone[y + x][x] == BLACK)
			{
				lineb[linecount][linebc[linecount]].s = x;
				lineb[linecount][linebc[linecount]].line = y;
				while (1)
				{
					lineb[linecount][linebc[linecount]].e = x++;
					lineb[linecount][linebc[linecount]].max++;
					if (Stone[y + x][x] != BLACK) {
						x--;
						linebc[linecount]++;
						break;
					}
				}
			}
			//흰돌
			if (Stone[y + x][x] == WHITE)
			{
				linew[linecount][linewc[linecount]].s = x;
				linew[linecount][linebc[linecount]].line = y;
				while (1)
				{
					linew[linecount][linewc[linecount]].e = x++;
					linew[linecount][linewc[linecount]].max++;
					if (Stone[y + x][x] != WHITE) {
						x--;
						linewc[linecount]++;
						break;
					}
				}
			}
		}
		linecount++;
	}

	for (int x = 1; x < SIZE; x++)
	{
		linebc[linecount] = 0, linewc[linecount] = 0;
		for (int y = 0; y < SIZE - x; y++)
		{
			//검은돌
			if (Stone[y][x + y] == BLACK)
			{
				lineb[linecount][linebc[linecount]].s = y;
				lineb[linecount][linebc[linecount]].line = x;
				while (1)
				{
					lineb[linecount][linebc[linecount]].e = y++;
					lineb[linecount][linebc[linecount]].max++;
					if (Stone[y][x + y] != BLACK) {
						y--;
						linebc[linecount]++;
						break;
					}
				}
			}
			//흰돌
			if (Stone[y][x + y] == WHITE)
			{
				linew[linecount][linewc[linecount]].s = y;
				linew[linecount][linebc[linecount]].line = x;
				while (1)
				{
					linew[linecount][linewc[linecount]].e = y++;
					linew[linecount][linewc[linecount]].max++;
					if (Stone[y][x + y] != WHITE) {
						y--;
						linewc[linecount]++;
						break;
					}
				}
			}
		}
		linecount++;
	}
	//라인

	for (int y = 0; y < LINE; y++)
	{
		//최종에 검돌 집어넣기
		if (linebc[y] < 2) {
			linebmax[y].max = lineb[y][0].max;
			linebmax[y].s = lineb[y][0].s;
			linebmax[y].e = lineb[y][0].e;
			linebmax[y].line = lineb[y][0].line;
			linebmax[y].blank = -1;
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linebc[y]; i++) {
				if (lineb[y][i].e == lineb[y][i + 1].s - 2) {
					if (linebmax[y].max < lineb[y][i].max + lineb[y][i + 1].max) {//두 단어 칸이 더 크면
						linebmax[y].s = lineb[y][i].s;
						linebmax[y].e = lineb[y][i + 1].e;
						linebmax[y].line = lineb[y][i].line;
						linebmax[y].blank = lineb[y][i].e + 1;
						linebmax[y].max = lineb[y][i].max + lineb[y][i + 1].max - 1;
					}
				}
				else if (linebmax[y].max < lineb[y][i].max) {
					linebmax[y].s = lineb[y][i].s;
					linebmax[y].e = lineb[y][i].e;
					linebmax[y].line = lineb[y][i].line;
					linebmax[y].blank = -1;
					linebmax[y].max = lineb[y][i].max;
				}
			}
		}
		//최종에 흰돌 집어넣기
		if (linewc[y] < 2) {
			linewmax[y].max = linew[y][0].max;
			linewmax[y].s = linew[y][0].s;
			linewmax[y].e = linew[y][0].e;
			linewmax[y].line = linew[y][0].line;
			linewmax[y].blank = -1;
		}
		else {
			//한 곳에 두개 이상일 때
			for (int i = 0; i < linewc[y]; i++) {
				if (linew[y][i].e == linew[y][i + 1].s - 2) {
					if (linewmax[y].max < linew[y][i].max + linew[y][i + 1].max) {//두 단어 칸이 더 크면
						linewmax[y].s = linew[y][i].s;
						linewmax[y].e = linew[y][i + 1].e;
						linewmax[y].line = linew[y][i].line;
						linewmax[y].blank = linew[y][i].e + 1;
						linewmax[y].max = linew[y][i].max + linew[y][i + 1].max - 1;
					}
				}
				else if (linewmax[y].max < linew[y][i].max) {
					linewmax[y].s = linew[y][i].s;
					linewmax[y].e = linew[y][i].e;
					linewmax[y].line = linew[y][i].line;
					linewmax[y].blank = -1;
					linewmax[y].max = linew[y][i].max;
				}
			}
		}
	}
	

	//전체에서 가장 긴 줄
	{
		//아래 쪽 대각선이면 x, x+y 위면 x+y, y
		checkline realbmax = { 0 };
		for (int i = 0; i < LINE; i++) {
			if (realbmax.max < linebmax[i].max) {
				realbmax = linebmax[i];
				if (i < SIZE)
					realbmax.down = TRUE;
				else
					realbmax.down = FALSE;
			}
		}
		checkline realwmax = { 0 };
		for (int i = 0; i < LINE; i++) {
			if (realwmax.max < linewmax[i].max) {
				realwmax = linewmax[i];
				if (i < SIZE)
					realwmax.down = TRUE;
				else
					realwmax.down = FALSE;
			}
		}

		if (realwmax.max < realbmax.max) {
			printf("우하향 대각선 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					if(realbmax.down ==TRUE)
						printf("(%d,%d)", i, i + realbmax.line);
					else
						printf("(%d,%d)", i + realbmax.line, i);
		}
		else if (realwmax.max == realbmax.max) {
			printf("우하향 대각선 최대 BLACK : ");
			for (int i = realbmax.s; i <= realbmax.e; i++)
				if (realbmax.blank != i)
					if (realbmax.down == TRUE)
						printf("(%d,%d)", i, i + realbmax.line);
					else
						printf("(%d,%d)", i + realbmax.line, i);

			printf("\n");
			printf("우하향 대각선 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					if (realwmax.down == TRUE)
						printf("(%d,%d)", i, i + realwmax.line);
					else
						printf("(%d,%d)", i + realwmax.line, i);
		}
		else {
			printf("우하향 대각선 최대 WHITE : ");
			for (int i = realwmax.s; i <= realwmax.e; i++)
				if (realwmax.blank != i)
					if (realwmax.down == TRUE)
						printf("(%d,%d)", i, i + realwmax.line);
					else
						printf("(%d,%d)", i + realwmax.line, i);
		}
		printf("\n");
	}
}