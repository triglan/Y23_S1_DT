#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

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
	int max;//연속 횟수
}checkline;

int Stone[SIZE][SIZE] = { 0 };


int turn = 0;					// 0턴 초기화
int inputX, inputY;

void StartStone();					// 초기값, 테스트 용
void PrintStone(int printStone);	// 돌 출력
void PrintBoard();					// 보드판 출력
void CountStone();					// 검돌, 흰돌 몇개인지 세기
void ScanTurn();					// 입력 받기
bool IsSamePos();					// 중복 입력 받기
void InputStone(int inputX, int inputY);// 돌 추가

void ScanSide();

int main()
{
	char order;
	while (TRUE)
	{

		PrintBoard();	//바둑판 그리기
		ScanTurn();	//스캔

		printf("명령어 : 1. 돌 놓기(x,y) 5. 중복 돌 검사 : ");
		scanf_s(" %c", &order, 1);
		switch (order)
		{
		case '1':
		{
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
			break;
		}
		case '5':
		{
			ScanSide();
			printf("\n");
			ScanLine();
			printf("\n");
			ScanRightUp();
			printf("\n");
			ScanRightDown();
			printf("\n");
			ScanCount();
			printf("\n\n");
		}
		break;
		default:
			break;
		}

	}
}

void StartStone()
{
	Stone[1][1] = BLACK;
	Stone[1][2] = BLACK;
	Stone[1][3] = BLACK;
	Stone[1][4] = BLACK;

	Stone[0][1] = WHITE;
	Stone[0][2] = WHITE;
	Stone[0][3] = WHITE;
	Stone[0][4] = WHITE;

	Stone[0][7] = BLACK;
	Stone[0][8] = BLACK;
	Stone[0][9] = BLACK;
	Stone[0][10] = BLACK;
	Stone[0][11] = BLACK;
	Stone[0][12] = BLACK;
	Stone[0][13] = BLACK;

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
void PrintStone(int printStone)
{
	if (printStone == BLANK)
		printf("■");
	if (printStone == BLACK)
		printf("○");
	if (printStone == WHITE)
		printf("●");
}
void PrintBoard()
{
	CountStone();
	for (int UpDown = 0; UpDown < SIZE; UpDown++)
	{//상하 for문
		for (int Side = 0; Side < SIZE; Side++)
		{//좌우 for문
			PrintStone(Stone[UpDown][Side]);
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
	checkline lineb[SIZE][SIZE];
	checkline linew[SIZE][SIZE];
	int linebc = 0, linewc = 0;//해당 줄에 몇번째 줄인지

	//초기화
	//for (int i = 0; i < SIZE; i++)
	//{
	//	lineb[i] = 0;
	//	linew[i] = 0;
	//}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (Stone[y][x] == BLACK)
			{//3~5번째 줄이면 s=3 e=5
				lineb[y][linebc].s = x;
				while (1)
				{
					lineb[y][linebc].e = x++;
					lineb[y][linebc].max++;
					if (Stone[y][x] != BLACK) {
						linebc++;
						break;
					}
				}
			}
		}

		int linemax[SIZE] = 0;
		for (int y = 0; y < SIZE; y++){
			for (int i = 0; i < linebc - 1; i++){
				if (linemax[y] < lineb[y][i].max + lineb[y][i + 1].max)
					linemax[y] = lineb[y][i].max + lineb[y][i + 1].max;
			}
		}

		printf("%d번째 가로줄 BLACK : ", y);
		for (int i = 0; i < lineb[y]; i++)
			printf("(%d,%d)", y, tempb[y][i]);

		/*if (lineb[y] == 0 && linew[y] == 0)
			printf("EMPTY\n");
		else if (lineb[y] > linew[y])
		{
			printf("%d번째 가로줄 BLACK : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempb[y][i]);
		}
		else if (lineb[y] == linew[y])
		{
			printf("%d번째 가로줄 BLACK : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempb[y][i]);

			printf("%d번째 가로줄 WHITE : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempw[y][i]);
		}
		else
		{
			printf("%d번째 가로줄 WHITE : ", y);
			for (int i = 0; i < linew[y]; i++)
				printf("(%d,%d)", y, tempw[y][i]);
		}
		printf("\n");*/
	}
}