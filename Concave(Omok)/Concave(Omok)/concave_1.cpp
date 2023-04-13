//바두간 그리기 -> 좌표 입력받기 -> 중복 확인 -> 돌 넣기 -> 돌의 개수 출력
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

//열 행
#define ROW 19	// 열 세로
#define COL 19	// 행 가로

int Stone[COL][ROW] = { 0 };	// 
int turn = 0;					// 0턴 초기화

int inputX, inputY;

void PrintStone(int printStone);	// 돌 출력
void PrintBoard();					// 보드판 출력
void CountStone();					// 검돌, 흰돌 몇개인지 세기
void ScanStone();					// 입력 받기
bool IsSamePos();					// 중복 입력 받기
void InputStone(int inputX, int inputY);					// 돌 추가


int main()
{
	while (TRUE)
	{
		PrintBoard();	//바둑판 그리기

		ScanStone();	//스캔
		system("cls");

		if (IsSamePos() == TRUE)	//중복 확인 중복이면 while 다시 시작
			continue;

		InputStone(inputX, inputY);	//돌 출력

		turn++;			//1턴 증가
	}

}

void PrintStone(int printStone)
{
	if (printStone == BLANK)
		printf("* ");
	if (printStone == BLACK)
		printf("○");
	if (printStone == WHITE)
		printf("●");
}

void PrintBoard()
{
	CountStone();
	for (int UpDown = 0; UpDown < COL; UpDown++)
	{//상하 for문
		for (int Side = 0; Side < ROW; Side++)
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
	for (int UpDown = 0; UpDown < COL; UpDown++)
	{
		for (int Side = 0; Side < ROW; Side++)
		{
			if (Stone[UpDown][Side] == BLACK)
				BlackStone++;
			if (Stone[UpDown][Side] == WHITE)
				WhiteStone++;
		}
	}
	printf("검은 돌 : %d 흰 돌 : %d\n", BlackStone, WhiteStone);
}

void ScanStone()
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
	scanf("%d %d", &inputX, &inputY);
}


void InputStone(int InputX, int InputY)
{
	if (turn % 2 == 0)	//흑돌 턴일 때
		Stone[inputY][inputX] = BLACK;
	else
		Stone[inputY][inputX] = WHITE;
}