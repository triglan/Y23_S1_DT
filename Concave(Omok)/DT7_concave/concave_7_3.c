#define _CRT_SECURE_NO_WARNINGS
//�ٵΰ� �׸��� -> ��ǥ �Է¹ޱ� -> �ߺ� Ȯ�� -> �� �ֱ� -> ���� ���� ���
#include <stdio.h>
#include <Windows.h>

//bool Ÿ��
#define bool int
#define TRUE 1
#define FALSE 0
//�÷��̾�
#define BLANK 0
#define BLACK 1
#define WHITE 2
//�ٵ��� ũ��
#define SIZE 19
#define LINE 37

int Stone[SIZE][SIZE] = { 0 };
int tempStoneb[SIZE][SIZE * 2];
int tempStonew[SIZE][SIZE * 2];

int bline[SIZE] = { 0 };
int wline[SIZE] = { 0 };

int turn = 0;					// 0�� �ʱ�ȭ
int inputX, inputY;

int maxb = 0, maxw = 0, lineb[LINE] = { 0 }, linew[LINE] = { 0 };


void StartStone();					// �ʱⰪ, �׽�Ʈ ��
void PrintStone(int printStone);	// �� ���
void PrintBoard();					// ������ ���
void CountStone();					// �˵�, �� ����� ����
void ScanTurn();					// �Է� �ޱ�
bool IsSamePos();					// �ߺ� �Է� �ޱ�
void InputStone(int inputX, int inputY);// �� �߰�

void ScanSide();
void ScanLine();
void RightUp();
void RightDown();
void printLine();

int main()
{
	char order;
	StartStone();
	while (TRUE)
	{
		printLine();
		printf("\n\n");
		ScanSide();
		printf("\n\n");

		ScanLine();
		printf("\n\n");
		RightUp();
		printf("\n\n");
		RightDown();
		printf("\n\n");

		PrintBoard();	//�ٵ��� �׸���
		ScanTurn();	//��ĵ

		scanf_s("%d %d", &inputX, &inputY);
		system("cls");

		if (inputX<0 || inputX > SIZE || inputY < 0 || inputY > SIZE)
		{
			printf("�߸��� ���Դϴ� �ٽ� �Է��� �ּ���.\n");
			continue;
		}
		if (IsSamePos() == TRUE)	//�ߺ� Ȯ�� �ߺ��̸� while �ٽ� ����
			continue;


		InputStone(inputX, inputY);	//�� ���
		turn++;			//1�� ����
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
		printf("��");
	if (printStone == BLACK)
		printf("��");
	if (printStone == WHITE)
		printf("��");
}
void PrintBoard()
{
	CountStone();
	for (int UpDown = 0; UpDown < SIZE; UpDown++)
	{//���� for��
		for (int Side = 0; Side < SIZE; Side++)
		{//�¿� for��
			PrintStone(Stone[UpDown][Side]);
		}
		printf("\n");
	}
}
bool IsSamePos()
{
	if (Stone[inputY][inputX] != BLANK)	// ����ĭ�� �ƴ϶��
	{
		printf("�̹� ���� ���� �ֽ��ϴ�.\n");
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
			{
				BlackStone++;
			}
			if (Stone[UpDown][Side] == WHITE)
			{
				WhiteStone++;
			}
		}
	}
	printf("���� �� : %d �� �� : %d\n", BlackStone, WhiteStone);
}
void ScanTurn()
{
	if (turn % 2 == 0)	//Ȧ��, �浹 ���� ��
	{
		printf("�浹");
	}
	else				//¦��, �鵹 ���� ��
	{
		printf("�鵹");
	}
	printf(" ���Դϴ�. ���� ���� �ֽʽÿ� ����[0~18] ����[0~18] : ");

}
void InputStone(int InputX, int InputY)
{
	if (turn % 2 == 0)	//�浹 ���� ��
		Stone[inputY][inputX] = BLACK;
	else
		Stone[inputY][inputX] = WHITE;
}

void printLine()
{
	for (int i = 0; i < SIZE; i++)
	{
		bline[i] = 0;
		wline[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (Stone[y][x] == BLACK)
				bline[y]++;
			if (Stone[y][x] == WHITE)
				wline[y]++;
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d�� BLACK : %d // WHITE : %d\n", i, bline[i], wline[i]);
	}		
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
		for (int x = 0; x < SIZE; x)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					x++;
					maxb++;
					if (Stone[y][x] != BLACK)
					{
						if (maxb > lineb[y])
						{
							lineb[y] = maxb;
							for (int i = 0; i < maxb; i++)
							{
								tempStoneb[y][i] = x - i;
							}
						}
						break;
					}
				}
				
			}
			else if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					x++;
					maxw++;
					if (Stone[y][x] != WHITE)
					{
						if (maxw > linew[y])
						{
							linew[y] = maxw;
							for (int i = 0; i < maxw; i++)
							{
								tempStonew[y][i] = x - i;
							}
						}
						break;
					}
				}
			}
			else
				x++;
			maxb = 0;
			maxw = 0;
		}
		if (lineb[y] == 0 && linew[y] == 0)
		{
			printf("EMPTY\n");
		}
		else if (lineb[y] > linew[y])
		{
			printf("%d��° ������ BLACK : [", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempStoneb[y][i]);
			printf("]\n");
		}
		else if (lineb[y] == linew[y])
		{
			printf("%d��° ������ BLACK : [", y, lineb[y], linew[y]);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempStoneb[y][i]);
			printf("] WHITE : [");
			for (int i = 0; i < linew[y]; i++)
				printf("(%d,%d)", y, tempStonew[y][i]);
			printf("]\n");
		}
		else
		{
			printf("%d��° ������ WHITE : [", y);
			for (int i = 0; i < linew[y]; i++)
				printf("(%d,%d)", y, tempStonew[y][i]);
			printf("]\n");
		}
	}
}
void ScanLine()//������
{
	for (int i = 0; i < SIZE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int x = 0; x < SIZE; x++)
	{
		for (int y = 0; y < SIZE; y)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					y++;
					maxb++;
					if (Stone[y][x] != BLACK)
					{
						if (maxb > lineb[x])
							lineb[x] = maxb;
						break;
					}
				}

			}
			else if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					y++;
					maxw++;
					if (Stone[y][x] != WHITE)
					{
						if (maxw > linew[x])
							linew[x] = maxw;
						break;
					}
				}
			}
			else
				y++;
			maxb = 0;
			maxw = 0;
		}
		if (lineb[x] > linew[x])
			printf("%d��° ������ [BLACK : %d]\n", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("%d��° ������ [BLACK : %d] [WHITE : %d]\n", x, lineb[x], linew[x]);
		else
			printf("%d��° ������[WHITE:% d]\n", x, linew[x]);
	}
}
void RightUp()//����� �׷���
{
	for (int i = 0; i < LINE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 0; y < LINE; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			if (x < SIZE && y - x < SIZE)
			{
				if (Stone[y - x][x] == BLACK)
				{
					while (1)
					{
						x++;
						maxb++;
						if (Stone[y - x][x] != BLACK)
						{
							if (maxb > lineb[y])
								lineb[y] = maxb;
							x--;
							break;
						}
					}

				}
				else if (Stone[y - x][x] == WHITE)
				{
					while (1)
					{
						x++;
						maxw++;
						if (Stone[y - x][x] != WHITE)
						{
							if (maxw > linew[y])
								linew[y] = maxw;
							x--;
							break;
						}
					}
				}
			}

			maxb = 0;
			maxw = 0;
		}
		if (lineb[y] > linew[y])
			printf("%d��° ����� �밢�� [BLACK : %d]\n", y, lineb[y]);
		else if (lineb[y] == linew[y])
			printf("%d��° ����� �밢�� [BLACK : %d] [WHITE : %d]\n", y, lineb[y], linew[y]);
		else
			printf("%d��° ����� �밢�� [WHITE:% d]\n", y, linew[y]);
	}
}
void RightDown()//������ �׷���
{
	for (int i = 0; i < LINE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int x = SIZE - 1; x >= 0; x--)
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
						if (maxb > lineb[x])
							lineb[x] = maxb;
						y--;
						break;
					}
				}

			}
			else if (Stone[y][x + y] == WHITE)
			{
				while (1)
				{
					y++;
					maxw++;
					if (Stone[y][x + y] != WHITE)
					{
						if (maxw > linew[x])
							linew[x] = maxw;
						y--;
						break;
					}
				}
			}
			maxb = 0;
			maxw = 0;
		}
		if (lineb[x] > linew[x])
			printf("x%d��° ������ �밢�� [BLACK : %d]\n", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("x%d��° ������ �밢�� [BLACK : %d] [WHITE : %d]\n", x, lineb[x], linew[x]);
		else
			printf("x%d��° ������ �밢��[WHITE:% d]\n", x, linew[x]);
	}

	for (int i = 0; i < LINE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 1; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE - y; x++)
		{
			if (Stone[x + y][x] == BLACK)
			{
				while (1)
				{
					x++;
					maxb++;
					if (Stone[x + y][x] != BLACK)
					{
						if (maxb > lineb[y])
							lineb[y] = maxb;
						x--;
						break;
					}
				}

			}
			else if (Stone[x + y][x] == WHITE)
			{
				while (1)
				{
					x++;
					maxw++;
					if (Stone[x + y][x] != WHITE)
					{
						if (maxw > linew[y])
							linew[y] = maxw;
						x--;
						break;
					}
				}
			}
			maxb = 0;
			maxw = 0;
		}
		if (lineb[y] > linew[y])
			printf("y%d��° ������ �밢�� [BLACK : %d]\n", y, lineb[y]);
		else if (lineb[y] == linew[y])
			printf("y%d��° ������ �밢�� [BLACK : %d] [WHITE : %d]\n", y, lineb[y], linew[y]);
		else
			printf("y%d��° ������ �밢��[WHITE:% d]\n", y, linew[y]);
	}
}
