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

int turn = 0;					// 0�� �ʱ�ȭ
int inputX, inputY;

void StartStone();					// �ʱⰪ, �׽�Ʈ ��
void PrintStone(int printStone);	// �� ���
void PrintBoard();					// ������ ���
void CountStone();					// �˵�, �� ����� ����
void ScanTurn();					// �Է� �ޱ�
bool IsSamePos();					// �ߺ� �Է� �ޱ�
void InputStone(int inputX, int inputY);// �� �߰�
void ScanSide();
void ScanDown();
void ScanRightDown();
void ScanRightUp();
void ScanCount();

int main()
{
	char order;
	StartStone();
	while (TRUE)
	{
		PrintBoard();	//�ٵ��� �׸���
		ScanTurn();	//��ĵ

		scanf_s(" %c", &order, 1);
		system("cls");

		switch (order)
		{
		case '1':
			ScanSide();
			break;
		case '2':
			ScanDown();
			break;
		case '3':
			ScanRightDown();
			break;
		case '4':
			ScanRightUp();
			break;
		case '5':
			ScanCount();
			break;
		case 'p':
			scanf("%c %d %d", &order, &inputX, &inputY);
			if (inputX<0 || inputX > SIZE || inputY < 0 || inputY > SIZE)
			{
				printf("�߸��� ���Դϴ� �ٽ� �Է��� �ּ���.\n");
				continue;
			}
			if (IsSamePos() == TRUE)	//�ߺ� Ȯ�� �ߺ��̸� while �ٽ� ����
				continue;
			InputStone(inputX, inputY);	//�� �Է�
		default:
			break;
		}


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
				BlackStone++;
			if (Stone[UpDown][Side] == WHITE)
				WhiteStone++;
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
int lineb[LINE] = { 0 }, maxb = 0, linew[LINE] = { 0 }, maxw = 0, tempb[LINE], tempw[LINE];
void ScanSide()
{
	for (int i = 0; i < LINE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
		tempb[i] = 0;
		tempw[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (Stone[y][x] == BLACK)
			{
				while (1)
				{
					maxb++;
					x++;
					if (Stone[y][x] != BLACK)
					{
						if (lineb[y] < maxb)
						{
							lineb[y] = maxb;
							for (int i = 0; i < maxb; i++)
								tempb[i] = x - i - 1;
						}
						x--;
						break;
					}
				}
			}
			if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					maxw++;
					x++;
					if (Stone[y][x] != WHITE)
					{
						if (linew[y] < maxw)
						{
							linew[y] = maxw;
							for (int i = 0; i < maxw; i++)
								tempw[i] = x - i - 1;
						}
						x--;
						break;
					}
				}
				
			}
			maxb = 0;
			maxw = 0;
		}
		if (lineb[y] == 0 && linew[y] == 0)
			printf("EMPTY");
		else if (lineb[y] > linew[y])
		{
			printf("%d��° ������ BLACK : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d) ", y, tempb[i]);
		}
		else if (lineb[y] == linew[y])
		{
			printf("%d��° ������ BLACK : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d) ", y, tempb[i]);

			printf("WHITE : ", y, linew[y]);
			for (int i = 0; i < linew[y]; i++)
				printf("(%d,%d) ", y, tempw[i]);
		}
		else
		{
			printf("%d��° ������ WHITE : ", y);
			for (int i = 0; i < linew[y]; i++)
				printf("(%d,%d) ", y, tempw[i]);
		}
		printf("\n");
	}
}
void ScanDown()
{
	for (int i = 0; i < LINE; i++)
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
					maxb++;
					y++;
					if (Stone[y][x] != BLACK)
					{
						if (lineb[x] < maxb)
							lineb[x] = maxb;
						y--;
						break;
					}
				}
			}
			if (Stone[y][x] == WHITE)
			{
				while (1)
				{
					maxw++;
					y++;
					if (Stone[y][x] != WHITE)
					{
						if (linew[x] < maxw)
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
			printf("%d��° ������ BLACK : %d\n", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("%d��° ������ BLACK : %d WHITE : %d\n", x, lineb[x], linew[x]);
		else
			printf("%d��° ������ WHITE : %d\n", x, linew[x]);
	}
}
void ScanRightDown()//������
{//19,0 20, 1
	for (int i = 0; i < LINE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE - y; x++)
		{
			if (Stone[x + y][x] == BLACK)
			{
				while (1)
				{
					maxb++;
					x++;
					if (Stone[x + y][x] != BLACK)
					{
						if (lineb[y] < maxb)
							lineb[y] = maxb;
						x--;
						break;
					}
				}
			}
			if (Stone[x + y][x] == WHITE)
			{
				while (1)
				{
					maxw++;
					x++;
					if (Stone[x + y][x] != WHITE)
					{
						if (linew[y] < maxw)
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
			printf("y%d��° ������ �밢�� BLACK : %d\n", y, lineb[y]);
		else if (lineb[y] == linew[y])
			printf("y%d��° ������ �밢�� BLACK : %d WHITE : %d\n", y, lineb[y], linew[y]);
		else
			printf("y%d��° ������ �밢�� WHITE : %d\n", y, linew[y]);
	}
	for (int i = 0; i < LINE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int x = 1; x < SIZE; x++)
	{//19,0 20,1
		for (int y = 0; y < SIZE - x; y++)
		{
			if (Stone[y][x + y] == BLACK)
			{
				while (1)
				{
					maxb++;
					y++;
					if (Stone[y][x + y] != BLACK)
					{
						if (lineb[x] < maxb)
							lineb[x] = maxb;
						y--;
						break;
					}
				}
			}
			if (Stone[y][x + y] == WHITE)
			{
				while (1)
				{
					maxw++;
					y++;
					if (Stone[y][x + y] != WHITE)
					{
						if (linew[x] < maxw)
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
			printf("x%d��° ������ �밢�� BLACK : %d\n", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("x%d��° ������ �밢�� BLACK : %d WHITE : %d\n", x, lineb[x], linew[x]);
		else
			printf("x%d��° ������ �밢�� WHITE : %d\n", x, linew[x]);
	}


}
void ScanRightUp()//�����
{//3,0 0,3
	for (int i = 0; i < LINE; i++)
	{
		lineb[i] = 0;
		linew[i] = 0;
	}
	for (int y = 0; y < LINE; y++)
	{
		for (int x = 0; x < LINE; x++)
		{
			if (x >= 0 && x < SIZE && y - x >= 0 && y - x < SIZE)
			{
				if (Stone[y - x][x] == BLACK)
				{
					while (1)
					{
						maxb++;
						x++;
						if (Stone[y - x][x] != BLACK)
						{
							if (lineb[y] < maxb)
								lineb[y] = maxb;
							x--;
							break;
						}
					}
				}
				if (Stone[y - x][x] == WHITE)
				{
					while (1)
					{
						maxw++;
						x++;
						if (Stone[y - x][x] != WHITE)
						{
							if (linew[y] < maxw)
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
		if (y < SIZE)
		{
			if (lineb[y] > linew[y])
				printf("y%d��° ����� �밢�� BLACK : %d\n", y, lineb[y]);
			else if (lineb[y] == linew[y])
				printf("y%d��° ����� �밢�� BLACK : %d WHITE : %d\n", y, lineb[y], linew[y]);
			else
				printf("y%d��° ����� �밢�� WHITE : %d\n", y, linew[y]);
		}
		else
		{
			if (lineb[y] > linew[y])
				printf("x%d��° ����� �밢�� BLACK : %d\n", y - SIZE + 1, lineb[y]);
			else if (lineb[y] == linew[y])
				printf("x%d��° ����� �밢�� BLACK : %d WHITE : %d\n", y - SIZE + 1, lineb[y], linew[y]);
			else
				printf("x%d��° ����� �밢�� WHITE : %d\n", y - SIZE + 1, linew[y]);
		}
	}
}
void ScanCount()
{
	for (int i = 0; i < LINE; i++)
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
			if (Stone[y][x] == WHITE)
				linew[y]++;
		}
		printf("%d��° �� ���� �� : %d �� �� : %d\n", y, lineb[y], linew[y]);
	}
}