//보드판 출력 -> 플레이어 입력 -> 중복확인 continue -> 최종적으로 바꿔주기 -> turn++

#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

//bool타입 정의
#define bool int
#define FALSE 0
#define TRUE 1
//공백 0 검돌1 흰돌2
#define BLANK 0
#define BLACK 1
#define WHITE 2
//행열
#define ROW 19	// 행 가로
#define COL 19	// 열 세로
//오목 돌
int Stone[COL][ROW];
//입력받는 돌 숫자
int InputX, InputY;
//턴
int turn = 0;


void PrintStone(int printStone);	// 오목 모양 출력
void PrintBoard();					// 오목판 출력
void ScanStone();					// 플레이어 확인 후 입력
void InputStone(int PlayerInputX, int PlayerInputY);					// 
bool IsSamePos(int PlayerInputX, int PlayerInputY);					// 중복 확인

int main()
{
	while (TRUE)
	{
		printf("검은 돌 : %d 흰 돌 : %d\n", turn / 2 + turn % 2, turn / 2);
		PrintBoard();				//오목판 출력

		ScanStone();	//오목돌 스캔
		system("cls");

		if (IsSamePos(InputX, InputY))			//중복 확인
			continue;

		InputStone(InputX, InputY);				//오목돌 놓기
		turn++;									//턴+1
	}

}

void PrintStone(int printStone)
{
	if (printStone == BLANK)
		printf("+ ");
	if (printStone == BLACK)
		printf("●");
	if (printStone == WHITE)
		printf("○");
}

void PrintBoard()
{
	for (int UpDown = 0; UpDown < COL; UpDown++)
	{
		for (int Side = 0; Side < ROW; Side++)
		{
			PrintStone(Stone[UpDown][Side]);
		}
		printf("\n");
	}
}


void ScanStone()
{
	int player = 0;
	if (turn % 2 == 0)	//짝수는 흑돌
	{
		player = BLACK;
		printf("흑돌");
	}
	else
	{
		player = WHITE;
		printf("백돌");
	}
	printf(" 플레이어의 턴입니다. 행[0~18] 열[0~18] 에 맞춰 입력해주세요 : ");

	scanf("%d %d", &InputX, &InputY);
	
}

void InputStone(int PlayerInputX, int PlayerInputY)
{
	if (turn % 2 == 0)	//짝수는 흑돌
	{
		Stone[PlayerInputY][PlayerInputX] = BLACK;
	}
	else			//홀수는 백돌
	{
		Stone[PlayerInputY][PlayerInputX] = WHITE;
	}
	
}

bool IsSamePos(int PlayerInputX, int PlayerInputY)
{
	if (Stone[PlayerInputY][PlayerInputX] != 0)
	{
		printf("이미 돌이 놓여 있습니다.\n\n");
		return TRUE;
	}
	return FALSE;
}