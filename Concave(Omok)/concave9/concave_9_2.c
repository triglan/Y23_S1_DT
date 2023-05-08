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

FILE* fp, * tfp;
int Stack[1000], top = -1;
int tStack[1000], ttop = -1;

int Stone[SIZE][SIZE] = { 0 };
int lineb[SIZE] = { 0 }, linew[SIZE] = { 0 }, maxb = 0, maxw = 0, tempb[SIZE][SIZE * 2], tempw[SIZE][SIZE * 2];

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
void ScanLine();
void ScanRightUp();
void ScanRightDown();
void ScanCount();

void SaveGame();
void LoadGame();

void BackSpace();
void BackBackSpace();

int main()
{
	char order;
	while (TRUE)
	{
		printf("top : %d, ttop : %d\n", top, ttop);
		PrintBoard();	//바둑판 그리기
		ScanTurn();	//스캔

		printf("\n명령어 : 1. 수 놓기(x,y) 5. 중복 돌 검사 : ");
		scanf_s(" %c", &order, 1);
		system("cls");
		
		switch (order)
		{
		case '1':
		{
			scanf_s("%d %d", &inputX, &inputY);
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
		case '2':
			SaveGame();
			break;
		case '3':
			LoadGame();
			break;
		case 'u':
			if (top <= -1)
			{
				printf("ㄴㄴ");
				break;
			}
			BackSpace();
			break;
		case 'r':
			if (ttop <= -1)
			{
				printf("ㄴㄴ");
				break;
			}
			BackBackSpace();
			break;
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
void SaveGame()
{
	fp = fopen("savegame.txt", "w");
	for (int i = 0; i <= top; i++)
		fprintf(fp, "%d\n", Stack[i]);

	tfp = fopen("tempgame.txt", "w");
	for (int i = 0; i <= ttop; i++)
		fprintf(tfp, "%d\n", tStack[i]);

	fclose(fp);
	fclose(tfp);
}
void LoadGame()
{
	turn = 0;
	top = -1, ttop = -1;
	for (int y = 0; y < SIZE; y++) 
	{
		for (int x = 0; x < SIZE; x++)
		{
			Stone[y][x] = 0;
		}
	}
	int value = 0, count = 0, x = 0, y = 0;
	fp = fopen("savegame.txt", "r");
	tfp = fopen("tempgame.txt", "r");
	while (fscanf(fp, "%d\n", &value) != EOF) {
		if (count % 2 == 0) {
			x = value;
			count++;
		}
		else {
			y = value;
			InputStone(x, y);
			count++;
		}
	}

	while (fscanf(tfp, "%d\n", &value) != EOF) {
		tStack[++ttop] = value;
	}
}
void BackSpace(){
	int x, y;
	y = Stack[top--];
	x = Stack[top--];
	Stone[y][x] = 0;
	tStack[++ttop] = x;
	tStack[++ttop] = y;
	turn--;
}
void BackBackSpace(){
	int x, y;
	y = tStack[ttop--];
	x = tStack[ttop--];
	InputStone(x, y);
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
	printf(" 턴입니다. 수를 놓아 주십시오 가로[0~18] 세로[0~18]");

}
void InputStone(int x, int y)
{
	if (turn % 2 == 0)	//흑돌 턴일 때
		Stone[y][x] = BLACK;
	else
		Stone[y][x] = WHITE;
	Stack[++top] = x;
	Stack[++top] = y;

	turn++;			//1턴 증가
}
void ScanSide()
{
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					x++;
					maxb++;
					if (Stone[y][x] != BLACK)
					{
						x--;
						if (maxb > lineb[y])
						{
							lineb[y] = maxb;
							for (int i = 0; i < maxb; i++)
							{
								tempb[y][i] = x - i;
							}
						}
						break;
					}
				}
			}
			if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					x++;
					maxw++;
					if (Stone[y][x] != WHITE)
					{
						x--;
						if (maxw > linew[y])
						{
							linew[y] = maxw;
							for (int i = 0; i < maxw; i++)
							{
								tempw[y][i] = x - i;
							}
						}
						break;
					}
				}

			}
			maxw = 0;
			maxb = 0;
		}
		if (lineb[y] == 0 && linew[y] == 0)
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
		printf("\n");
	}
}
void ScanLine()
{
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y++)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					y++;
					maxb++;
					if (Stone[y][x] != BLACK)
					{
						y--;
						if (maxb > lineb[x])
							lineb[x] = maxb;
						break;
					}
				}
			}
			if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					y++;
					maxw++;
					if (Stone[y][x] != WHITE)
					{
						y--;
						if (maxw > linew[x])
							linew[x] = maxw;
						break;
					}
				}

			}
			maxw = 0;
			maxb = 0;
		}
		if (lineb[x] > linew[x])
			printf("%d번째 세로줄 BLACK : %d", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("%d번째 세로줄 BLACK : %d WHITE : %d", x, lineb[x], linew[x]);
		else
			printf("%d번째 세로줄 WHITE : %d", x, linew[x]);
		printf("\n");
	}
}
void ScanRightDown()
{//우하향 2,0 20, 18 // 0,2 18,20 
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE - y; x++)
		{
			if (Stone[y + x][x] == BLACK)
			{
				while (1)
				{
					x++;
					maxb++;
					if (Stone[y + x][x] != BLACK)
					{
						x--;
						if (maxb > lineb[y])
							lineb[y] = maxb;
						break;
					}
				}
			}
			if (Stone[y + x][x] == WHITE)
			{
				while (1)
				{
					x++;
					maxw++;
					if (Stone[y + x][x] != WHITE)
					{
						x--;
						if (maxw > linew[y])
							linew[y] = maxw;
						break;
					}
				}

			}
			maxw = 0;
			maxb = 0;
		}
		if (lineb[y] > linew[y])
			printf("y%d번째 우하향 대각선 BLACK : %d", y, lineb[y]);
		else if (lineb[y] == linew[y])
			printf("y%d번째 우하향 대각선 BLACK : %d WHITE : %d", y, lineb[y], linew[y]);
		else
			printf("y%d번째 우하향 대각선 WHITE : %d", y, linew[y]);
		printf("\n");
	}
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int x = 1; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE - x; y++)
		{
			if (Stone[y][x + y] == BLACK)
			{
				while (1)
				{
					y++;
					maxb++;
					if (Stone[y][x + y] != BLACK)
					{
						y--;
						if (maxb > lineb[x])
							lineb[x] = maxb;
						break;
					}
				}
			}
			if (Stone[y][x + y] == WHITE)
			{
				while (1)
				{
					y++;
					maxw++;
					if (Stone[y][x + y] != WHITE)
					{
						y--;
						if (maxw > linew[x])
							linew[x] = maxw;
						break;
					}
				}

			}
			maxw = 0;
			maxb = 0;
		}
		if (lineb[x] > linew[x])
			printf("x%d번째 우하향 대각선 BLACK : %d", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("x%d번째 우하향 대각선 BLACK : %d WHITE : %d", x, lineb[x], linew[x]);
		else
			printf("x%d번째 우하향 대각선 WHITE : %d", x, linew[x]);
		printf("\n");
	}
}
void ScanRightUp()
{
	//우상향 3,0 0,3
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			if (Stone[y - x][x] == BLACK)
			{
				while (1)
				{
					x++;
					maxb++;
					if (Stone[y - x][x] != BLACK)
					{
						x--;
						if (maxb > lineb[y])
							lineb[y] = maxb;
						break;
					}
				}
			}
			if (Stone[y - x][x] == WHITE)
			{
				while (1)
				{
					x++;
					maxw++;
					if (Stone[y - x][x] != WHITE)
					{
						x--;
						if (maxw > linew[y])
							linew[y] = maxw;
						break;
					}
				}

			}
			maxw = 0;
			maxb = 0;
		}
		if (lineb[y] > linew[y])
			printf("y%d번째 우상향 대각선 BLACK : %d", y, lineb[y]);
		else if (lineb[y] == linew[y])
			printf("y%d번째 우상향 대각선 BLACK : %d WHITE : %d", y, lineb[y], linew[y]);
		else
			printf("y%d번째 우상향 대각선 WHITE : %d", y, linew[y]);
		printf("\n");
	}
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int x = 1; x < SIZE; x++)
	{//3,20 20,3
		for (int y = x; y <= SIZE; y++)
		{
			if (Stone[y][x - y] == BLACK)
			{
				while (1)
				{
					y++;
					maxb++;
					if (Stone[y][x - y] != BLACK)
					{
						y--;
						if (maxb > lineb[x])
							lineb[x] = maxb;
						break;
					}
				}
			}
			if (Stone[y][x - y] == WHITE)
			{
				while (1)
				{
					y++;
					maxw++;
					if (Stone[y][x - y] != WHITE)
					{
						y--;
						if (maxw > linew[x])
							linew[x] = maxw;
						break;
					}
				}
			}
			maxw = 0;
			maxb = 0;
		}
		if (lineb[x] > linew[x])
			printf("x%d번째 우상향 대각선 BLACK : %d", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("x%d번째 우상향 대각선 BLACK : %d WHITE : %d", x, lineb[x], linew[x]);
		else
			printf("x%d번째 우상향 대각선 WHITE : %d", x, linew[x]);
		printf("\n");
	}
}
void ScanCount()
{
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (Stone[y][x] == BLACK)
				lineb[y]++;
			else if (Stone[y][x] == WHITE)
				linew[y]++;
		}
		printf("%d번째 줄 검은 돌 : %d 흰 돌 : %d\n", y, lineb[y], linew[y]);
	}
}