#include <stdio.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

#define FALSE 0
#define TRUE 1

#define BLANK 0
#define WHITE 1
#define BLACK 2

typedef int bool;

#define ROW 19	//행 가로 + 1
#define COL 19	//열 세로 + 1

int inputX = 0, inputY = 0;	//입력받기
int turn = 0;		//흑 백돌 순서, 0은 흑돌 먼저ㅇ

void PrintStone(int printStone);	//0 : *, 1 : 흑 : ●, 백 : ○
void PrintBoard();					//바둑판 출력
void addStone();			//플레이어 턴 구분해서 한 수 두기
void InputStone();
bool isSamePos(int, int);

int Stone[COL][ROW] = { 0 };	//돌 초기화



int main()
{

	while (TRUE)
	{
		PrintBoard();	//보드판 출력
		printf("%d번 뒀습니다.\n\n", turn);
		InputStone();	//scanf로 플레이어 스톤 입력
		system("cls");

		//중복체크 함수 호출해서 중복이면 continue 아니면 그대로가서
		if (isSamePos(inputX, inputY))
			continue;

		//addStone으로 추가
		addStone();

		turn++;			//1턴 경과


		//AI~~
	}
}



void PrintStone(int printStone)
{
	if (printStone == 0)
		printf("* ");
	else if (printStone == BLACK)
		printf("●");
	else if (printStone == WHITE)
		printf("○");
}

void PrintBoard()
{
	for (int UpDown = 0; UpDown < COL; UpDown++)	//무슨 돌인지 체크 후 출력
	{
		for (int Side = 0; Side < ROW; Side++)
		{
			PrintStone(Stone[UpDown][Side]); //공백, 흑, 백인지 확인 후 출력
		}//행
		printf("\n");
	}//열
}



void addStone()	//간택당한 돌을 해당 돌로 바꿔주는 함수
{
	int player = 0;	//흑돌 플레이어 턴인지 아닌지

	if (turn % 2 == 0)	//짝수 턴일 때 흑돌
	{
		player = BLACK;
	}
	else			//홀수 턴일 때 백돌
	{
		player = WHITE;
	}

	Stone[inputY][inputX] = player;
}

void InputStone()	//해당 플레이어를 확인하고 scanf
{
	if (turn % 2 == 0)	//짝수 턴일 때 흑돌
	{
		printf("흑돌");
	}
	else			//홀수 턴일 때 백돌
	{
		printf("백돌");
	}
	printf("차례입니다. [열] (0~18) [행] (0~18) 순서로 입력해 주세요 : ");
	scanf_s("%d %d", &inputX, &inputY);
}

bool isSamePos(int x, int y)	//중복확인
{
	if (Stone[y][x] != 0)
	{
		printf("이미 돌이 놓여 있습니다\n\n");
		return TRUE;		//공백이면 trues
	}
	return FALSE;	//공백이 아니면 false
}
