#define _CRT_SECURE_NO_WARNINGS
//바두간 그리기 -> 좌표 입력받기 -> 중복 확인 -> 돌 넣기 -> 돌의 개수 출력
#include <stdio.h>
#include <Windows.h>
//ScanUp 0~37번째 줄 한번에 계산
//ScanDown scanUp이랑 연계되게
//for문에서 x++를 쓰지 말고 써서 if else 에서 쓰게끔
//PrintSide에서 b, w 구분해서 만들어
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

int Stone[SIZE][SIZE] = { 0 };

int turn = 0;					// 0턴 초기화
int inputX, inputY;

void StartStone();					// 초기값, 테스트 용
void StartStone();
void PrintStone(int printStone);	// 돌 출력
void PrintBoard();					// 보드판 출력
void CountStone();					// 검돌, 흰돌 몇개인지 세기
void ScanTurn();					// 입력 받기
bool IsSamePos();					// 중복 입력 받기
void InputStone(int inputX, int inputY);// 돌 추가
void ScanSide();
void ScanLeng();
void ScanDown();
void ScanUP();
void PrintSide();
int main()
{
	StartStone();
	while (TRUE)
	{
		PrintBoard();	//바둑판 그리기
		//ScanSide();
		//ScanLeng();
		//ScanDown();
		//ScanUP();
		PrintSide();
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
int maxb[SIZE] = {0}, maxw[SIZE], tempb = 0, tempw = 0;

void ScanSide()//가로줄 검사
{
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					tempb++;
					x++;
					if (Stone[y][x] != BLACK)
						break;
				}
				if (tempb > maxb[y])
					maxb[y] = tempb;
			}
			if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					tempw++;
					x++;
					if (Stone[y][x] != WHITE)
						break;
				}
				if (tempw > maxw[y])
					maxw[y] = tempw;
			}
			tempb = 0;
			tempw = 0;
		}
		if (maxb[y] > maxw[y])
			printf("%d번째 가로줄 가장 연속된 돌 BLACK : %d\n", y, maxb[y]);
		else if (maxb[y] == maxw[y])
			printf("%d번째 가로줄 가장 연속된 돌 BLACK : %d WHITE : %d\n", y, maxb[y], maxw[y]);
		else
			printf("%d번째 가로줄 가장 연속된 돌 WHITE : %d\n", y, maxw[y]);
	}
}
void ScanLeng()
{
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					tempb++;
					y++;
					if (Stone[y][x] != BLACK)
						break;
				}
				if (tempb > maxb[x])
					maxb[x] = tempb;
			}
			if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					tempw++;
					y++;

					if (Stone[y][x] != WHITE)
						break;
				}
				if (tempw > maxw[x])
					maxw[x] = tempw;
			}
			tempb = 0;
			tempw = 0;
		}
		if (maxb[x] > maxw[x])
			printf("%d번째 세로줄 가장 연속된 돌 BLACK : %d\n", x, maxb[x]);
		else if (maxb[x] == maxw[x])
			printf("%d번째 세로줄 가장 연속된 돌 BLACK : %d WHITE : %d\n", x, maxb[x], maxw[x]);
		else
			printf("%d번째 세로줄 가장 연속된 돌 WHITE : %d\n", x, maxw[x]);
	}
}
void ScanDown()
{
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	//우하향 그래프 x 0 ~ 18
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE - x; y++)
		{
			if (Stone[y][x + y] == BLACK)
			{
				while (1)
				{
					tempb++;
					y++;
					if (Stone[y][x + y] != BLACK)
						break;
				}
				if (tempb > maxb[x])
					maxb[x] = tempb;
			}
			if (Stone[y][x + y] == WHITE)
			{
				while (1)
				{
					tempw++;
					y++;
					if (Stone[y][x + y] != WHITE)
						break;
				}
				if (tempw > maxw[x])
					maxw[x] = tempw;
			}
			tempb = 0;
			tempw = 0;
		}
		if (maxb[x] > maxw[x])
			printf("우하향 대각선 x%d번째 가로줄 가장 연속된 돌 BLACK : %d\n", x, maxb[x]);
		else if (maxb[x] == maxw[x])
			printf("우하향 대각선 x%d번째 가로줄 가장 연속된 돌 BLACK : %d WHITE : %d\n", x, maxb[x], maxw[x]);
		else
			printf("우하향 대각선 x%d번째 가로줄 가장 연속된 돌 WHITE : %d\n", x, maxw[x]);
	}
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	//y 1 ~ 18
	for (int y = 1; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE - y; x++)
		{
			if (Stone[x + y][x] == BLACK)
			{
				while (1)
				{
					tempb++;
					x++;
					if (Stone[x + y][x] != BLACK)
						break;
				}
				if (tempb > maxb[y])
					maxb[y] = tempb;
			}
			if (Stone[x + y][x] == WHITE)
			{
				while (1)
				{
					tempw++;
					x++;
					if (Stone[x + y][x] != WHITE)
						break;
				}
				if (tempw > maxw[y])
					maxw[y] = tempw;
			}
			tempb = 0;
			tempw = 0;
		}
		if (maxb[y] > maxw[y])
			printf("y%d번째 우하향 대각선 가장 연속된 돌 BLACK : %d\n", y, maxb[y]);
		else if (maxb[y] == maxw[y])
			printf("y%d번째 우하향 대각선 가장 연속된 돌 BLACK : %d WHITE : %d\n", y, maxb[y], maxw[y]);
		else
			printf("y%d번째 우하향 대각선 가장 연속된 돌 WHITE : %d\n", y, maxw[y]);
	}


}
void ScanUP()
{
	
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	//우상향 그래프 y 0 ~ 18
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x <= y; x)
		{
			if (Stone[y - x][x] == BLACK)
			{
				while (1)
				{
					if (Stone[y - x][x] != BLACK)
						break;
					tempb++;
					x++;

				}
				if (tempb > maxb[y])
					maxb[y] = tempb;
			}
			else if (Stone[y - x][x] == WHITE)
			{
				while (1)
				{
					if (Stone[y - x][x] != WHITE)
						break;
					tempw++;
					x++;

				}
				if (tempw > maxw[y])
					maxw[y] = tempw;
			}
			else
				x++;
			tempb = 0;
			tempw = 0;
		}
		if (maxb[y] > maxw[y])
			printf("y%d번째 우상향 대각선 가장 연속된 돌 BLACK : %d\n", y, maxb[y]);
		else if (maxb[y] == maxw[y])
			printf("y%d번째 우상향 대각선 가장 연속된 돌 BLACK : %d WHITE : %d\n", y, maxb[y], maxw[y]);
		else
			printf("y%d번째 우상향 대각선 가장 연속된 돌 WHITE : %d\n", y, maxw[y]);
	}
	//우상향 그래프 x 1 ~ 18
	for (int x = 1; x < SIZE; x++)
	{
		for (int y = SIZE; y >= x; y)
		{
			if (Stone[y][y - x] == BLACK)
			{
				while (1)
				{
					if (Stone[y - x][x] != BLACK)
						break;
					tempb++;
					x++;

				}
				if (tempb > maxb[y])
					maxb[y] = tempb;
			}
			else if (Stone[y - x][x] == WHITE)
			{
				while (1)
				{
					if (Stone[y - x][x] != WHITE)
						break;
					tempw++;
					x++;

				}
				if (tempw > maxw[y])
					maxw[y] = tempw;
			}
			else
				x++;
			tempb = 0;
			tempw = 0;
		}
		if (maxb[x] > maxw[x])
			printf("x%d번째 우상향 대각선 가장 연속된 돌 BLACK : %d\n", x, maxb[x]);
		else if (maxb[x] == maxw[x])
			printf("x%d번째 우상향 대각선 가장 연속된 돌 BLACK : %d WHITE : %d\n", x, maxb[x], maxw[x]);
		else
			printf("x%d번째 우상향 대각선 가장 연속된 돌 WHITE : %d\n", x, maxw[x]);
	}
}
void PrintSide()
{
	int max[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					tempb++;
					x++;
					if (Stone[y][x] != BLACK)
						break;
				}
				if (tempb > maxb[y])
				{
					maxb[y] = tempb;
					for (int i = 0; i < tempb; i++)
					{
						max[y][i] = y * SIZE + (x - i - 1);
					}
					
				}
			}
			else if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					tempw++;
					x++;
					if (Stone[y][x] != WHITE)
						break;
				}
				if (tempw > maxw[y])
					maxw[y] = tempw;
			}
			else
				x++;
			tempb = 0;
			tempw = 0;
		}

		if (maxb[y] > maxw[y])
			for (int i = 0; i < maxb[y]; i++)
				printf("B(%d, %d)", max[y][i] / SIZE, max[y][i] % SIZE);
		else if (maxb[y] == maxw[y])
			for (int i = 0; i < maxb[y]; i++)
				printf("W(%d, %d)", max[y][i] / SIZE, max[y][i] % SIZE);
		else
			printf("%d번째 가로줄 가장 연속된 돌 WHITE : %d\n", y, maxw[y]);
		printf("\n");
	}
}