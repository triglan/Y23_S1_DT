#define _CRT_SECURE_NO_WARNINGS
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
#define SIZE 19// 가로 세로
#define DIAG 37// 대각선 개수
int Stone[SIZE][SIZE] = { 0 };	
int linecountb[SIZE];
int linecountw[SIZE];

int lengthcountb[37];
int lengthcountw[37];

int turn = 0;					// 0턴 초기화
int inputX, inputY;

void StartStone();
void PrintStone(int printStone);	// 돌 출력
void PrintBoard();					// 보드판 출력
void CountStone();					// 검돌, 흰돌 몇개인지 세기
void ScanTurn();					// 입력 받기
bool IsSamePos();					// 중복 입력 받기
void InputStone(int inputX, int inputY);					// 돌 추가
void ScanLine();
void ScanLength();
void ScanDiag();
void DownDirect();
int main()
{
	StartStone();
	while (TRUE)
	{
		ScanLine();
		printf("\n");
		ScanLength();
		printf("\n");
		ScanDiag();

		PrintBoard();	//바둑판 그리기
		DownDirect();

		ScanTurn();	//스캔



		scanf("%d %d", &inputX, &inputY);
		system("cls");
		if (inputX<0 || inputX > SIZE || inputY < 0 || inputY > SIZE)
		{
			printf("잘못된 값입니다 다시 입력해 주세요.\n");
			continue;
		}
		if (IsSamePos() == TRUE)	//중복 확인 중복이면 while 다시 시작
			continue;
		InputStone(inputX, inputY);	//돌 출력

		turn++;			//1턴 증가
	}
}

void StartStone()
{
	Stone[1][1] = BLACK;
	Stone[1][2] = BLACK;
	Stone[1][3] = BLACK;
	Stone[1][4] = BLACK;

	Stone[1][9] = BLACK;
	Stone[1][10] = BLACK;
	Stone[1][11] = BLACK;
	Stone[1][14] = BLACK;
	Stone[1][15] = BLACK;
	Stone[1][16] = BLACK;
	Stone[1][17] = BLACK;
	Stone[1][18] = BLACK;

	Stone[2][1] = BLACK;
	Stone[2][2] = BLACK;
	Stone[2][3] = BLACK;
	Stone[2][4] = BLACK;
	Stone[3][3] = BLACK;
	Stone[4][3] = BLACK;
	Stone[4][4] = BLACK;

	Stone[2][8] = WHITE;
	Stone[2][9] = WHITE;
	Stone[2][10] = WHITE;
	Stone[2][11] = WHITE;
	Stone[2][12] = WHITE;
	Stone[2][13] = WHITE;
	Stone[2][14] = WHITE;

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
void InputStone(int InputX, int InputY)
{
	if (turn % 2 == 0)	//흑돌 턴일 때
		Stone[inputY][inputX] = BLACK;
	else
		Stone[inputY][inputX] = WHITE;
}
void ScanLine()
{
	int tempblack = 0;
	int tempwhite = 0;
	for (int i = 0; i < SIZE; i++)
	{
		linecountb[i] = 0;
		linecountw[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			tempblack = 0;
			tempwhite = 0;
			if (Stone[y][x] == BLACK)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (x < SIZE)
				{
					tempblack++;
					x++;
					if (Stone[y][x] != BLACK)
						break;
				}
				if (tempblack > linecountb[y])//최대값이면 넣어
					linecountb[y] = tempblack;
			}
			if (Stone[y][x] == WHITE)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (x < SIZE)
				{
					tempwhite++;
					x++;
					if (Stone[y][x] != WHITE)
						break;
				}
				if (tempwhite > linecountw[y])//최대값이면 넣어
					linecountw[y] = tempwhite;
			}
		}
		{
			if (linecountb[y] > linecountw[y])
				printf("%d번째 가로 줄 가장 연속된 돌 Black : %d\n", y, linecountb[y]);
			else if (linecountb[y] == linecountw[y])
				printf("%d번째 가로 줄 가장 연속된 돌 Black : %d, White : %d\n", y, linecountb[y], linecountw[y]);
			else
				printf("%d번째 가로 줄 가장 연속된 돌 White : %d\n", y, linecountw[y]);

			tempblack = 0;
			tempwhite = 0;
		}
	}
}
void ScanLength()
{
	int tempblack = 0;
	int tempwhite = 0;
	for (int i = 0; i < SIZE; i++)
	{
		lengthcountb[i] = 0;
		lengthcountw[i] = 0;
	}
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			tempblack = 0;
			tempwhite = 0;
			if (Stone[y][x] == BLACK)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (y < SIZE)
				{
					tempblack++;
					y++;
					if (Stone[y][x] != BLACK)
						break;
				}
				if (tempblack > lengthcountb[x])//최대값이면 넣어
					lengthcountb[x] = tempblack;
			}
			if (Stone[y][x] == WHITE)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (y < SIZE)
				{
					tempwhite++;
					y++;
					if (Stone[y][x] != WHITE)
						break;
				}
				if (tempwhite > lengthcountw[x])//최대값이면 넣어
					lengthcountw[x] = tempwhite;
			}
		}

		if (lengthcountb[x] > lengthcountw[x])
			printf("%d번째 세로 줄 가장 연속된 돌 Black : %d\n", x, lengthcountb[x]);
		else if (lengthcountb[x] == lengthcountw[x])
			printf("%d번째 세로 줄 가장 연속된 돌 Black : %d, White : %d\n", x, lengthcountb[x], lengthcountw[x]);
		else
			printf("%d번째 세로 줄 가장 연속된 돌 White : %d\n", x, lengthcountw[x]);

		tempblack = 0;
		tempwhite = 0;
	}
}

void ScanDiag()
{
	for (int i = 0; i < 37; i++)
	{
		linecountb[i] = 0;
		linecountw[i] = 0;
	}
	int Diagcountb[SIZE], Diagcountw[SIZE], tempblack = 0, tempwhite = 0;
	for (int i = 0; i < DIAG; i++)
	{
		//if (i < DIAG / 2 + 1)//37 / 2 = 18
		//{
		for (int j = 0; j <= i; j++)
		{
			if (j < SIZE && i - j < SIZE)
			{
				if (Stone[j][i - j] == BLACK)
				{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
					while (j <= i)
					{
						tempblack++;
						j++;
						if (Stone[j][i - j] != BLACK)
							break;
					}
					if (tempblack > linecountb[i])//최대값이면 넣어
						linecountb[i] = tempblack;
				}
				if (Stone[j][i - j] == WHITE)
				{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
					while (j <= i)
					{
						tempwhite++;
						j++;
						if (Stone[j][i - j] != WHITE)
							break;
					}
					if (tempwhite > linecountw[i])//최대값이면 넣어
						linecountw[i] = tempwhite;
				}
			}
		}
		{
			if (linecountb[i] > linecountw[i])
				printf("%d번째 대각선 줄 가장 연속된 돌 Black : %d\n", i, linecountb[i]);
			else if (linecountb[i] == linecountw[i])
				printf("%d번째 대각선 줄 가장 연속된 돌 Black : %d, White : %d\n", i, linecountb[i], linecountw[i]);
			else
				printf("%d번째 대각선 줄 가장 연속된 돌 White : %d\n", i, linecountw[i]);

			tempblack = 0;
			tempwhite = 0;
		}
	}
}
//우하향 대각선
void DownDirect()
{
	for (int i = 0; i < 37; i++)
	{
		linecountb[i] = 0;
		linecountw[i] = 0;
	}
	int Diagcountb[SIZE], Diagcountw[SIZE], tempblack = 0, tempwhite = 0;
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE - x; y++)
		{
			if (Stone[y][x + y] == BLACK)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (y <= SIZE - x)
				{
					tempblack++;
					y++;
					if (Stone[y][x + y] != BLACK)
						break;
				}
				if (tempblack > linecountb[x])//최대값이면 넣어
					linecountb[x] = tempblack;
			}
			if (Stone[y][x + y] == WHITE)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (y <= SIZE - x)
				{
					tempwhite++;
					y++;
					if (Stone[y][x + y] != WHITE)
						break;
				}
				if (tempwhite > linecountw[x])//최대값이면 넣어
					linecountw[x] = tempwhite;
			}
		}
		{
			if (linecountb[x] > linecountw[x])
				printf("x%d번째 대각선 줄 가장 연속된 돌 Black : %d\n", x, linecountb[x]);
			else if (linecountb[x] == linecountw[x])
				printf("x%d번째 대각선 줄 가장 연속된 돌 Black : %d, White : %d\n", x, linecountb[x], linecountw[x]);
			else
				printf("x%d번째 대각선 줄 가장 연속된 돌 White : %d\n", x, linecountw[x]);

			tempblack = 0;
			tempwhite = 0;
		}
	}

	for (int i = 0; i < 37; i++)
	{
		linecountb[i] = 0;
		linecountw[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE - y; x++)
		{
			if (Stone[x + y][x] == BLACK)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (x <= SIZE - y)
				{
					tempblack++;
					x++;
					if (Stone[x + y][x] != BLACK)
						break;
				}
				if (tempblack > linecountb[y])//최대값이면 넣어
					linecountb[y] = tempblack;
			}
			if (Stone[x + y][x] == WHITE)
			{//줄마다 검사 검은돌이면 검은돌 아닐 때 까지 더하고 검은돌이면 멈추고 기존 가장 연속수보다 크면 대입 not 탈출
				while (x <= SIZE - y)
				{
					tempwhite++;
					x++;
					if (Stone[x + y][x] != WHITE)
						break;
				}
				if (tempwhite > linecountw[y])//최대값이면 넣어
					linecountw[y] = tempwhite;
			}
		}
		{
			if (linecountb[y] > linecountw[y])
				printf("y%d번째 대각선 줄 가장 연속된 돌 Black : %d\n", y, linecountb[y]);
			else if (linecountb[y] == linecountw[y])
				printf("y%d번째 대각선 줄 가장 연속된 돌 Black : %d, White : %d\n", y, linecountb[y], linecountw[y]);
			else
				printf("y%d번째 대각선 줄 가장 연속된 돌 White : %d\n", y, linecountw[y]);

			tempblack = 0;
			tempwhite = 0;
		}
	}
}