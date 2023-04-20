#define _CRT_SECURE_NO_WARNINGS
//�ٵΰ� �׸��� -> ��ǥ �Է¹ޱ� -> �ߺ� Ȯ�� -> �� �ֱ� -> ���� ���� ���
#include <stdio.h>
#include <Windows.h>
//ScanUp 0~37��° �� �ѹ��� ���
//ScanDown scanUp�̶� ����ǰ�
//for������ x++�� ���� ���� �Ἥ if else ���� ���Բ�
//PrintSide���� b, w �����ؼ� �����
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

int Stone[SIZE][SIZE] = { 0 };

int turn = 0;					// 0�� �ʱ�ȭ
int inputX, inputY;

void StartStone();					// �ʱⰪ, �׽�Ʈ ��
void StartStone();
void PrintStone(int printStone);	// �� ���
void PrintBoard();					// ������ ���
void CountStone();					// �˵�, �� ����� ����
void ScanTurn();					// �Է� �ޱ�
bool IsSamePos();					// �ߺ� �Է� �ޱ�
void InputStone(int inputX, int inputY);// �� �߰�
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
		PrintBoard();	//�ٵ��� �׸���
		//ScanSide();
		//ScanLeng();
		//ScanDown();
		//ScanUP();
		PrintSide();
		ScanTurn();	//��ĵ

		scanf("%d %d", &inputX, &inputY);
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
int maxb[SIZE] = {0}, maxw[SIZE], tempb = 0, tempw = 0;

void ScanSide()//������ �˻�
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
			printf("%d��° ������ ���� ���ӵ� �� BLACK : %d\n", y, maxb[y]);
		else if (maxb[y] == maxw[y])
			printf("%d��° ������ ���� ���ӵ� �� BLACK : %d WHITE : %d\n", y, maxb[y], maxw[y]);
		else
			printf("%d��° ������ ���� ���ӵ� �� WHITE : %d\n", y, maxw[y]);
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
			printf("%d��° ������ ���� ���ӵ� �� BLACK : %d\n", x, maxb[x]);
		else if (maxb[x] == maxw[x])
			printf("%d��° ������ ���� ���ӵ� �� BLACK : %d WHITE : %d\n", x, maxb[x], maxw[x]);
		else
			printf("%d��° ������ ���� ���ӵ� �� WHITE : %d\n", x, maxw[x]);
	}
}
void ScanDown()
{
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	//������ �׷��� x 0 ~ 18
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
			printf("������ �밢�� x%d��° ������ ���� ���ӵ� �� BLACK : %d\n", x, maxb[x]);
		else if (maxb[x] == maxw[x])
			printf("������ �밢�� x%d��° ������ ���� ���ӵ� �� BLACK : %d WHITE : %d\n", x, maxb[x], maxw[x]);
		else
			printf("������ �밢�� x%d��° ������ ���� ���ӵ� �� WHITE : %d\n", x, maxw[x]);
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
			printf("y%d��° ������ �밢�� ���� ���ӵ� �� BLACK : %d\n", y, maxb[y]);
		else if (maxb[y] == maxw[y])
			printf("y%d��° ������ �밢�� ���� ���ӵ� �� BLACK : %d WHITE : %d\n", y, maxb[y], maxw[y]);
		else
			printf("y%d��° ������ �밢�� ���� ���ӵ� �� WHITE : %d\n", y, maxw[y]);
	}


}
void ScanUP()
{
	
	for (int i = 0; i < SIZE; i++)
	{
		maxb[i] = 0;
		maxw[i] = 0;
	}
	//����� �׷��� y 0 ~ 18
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
			printf("y%d��° ����� �밢�� ���� ���ӵ� �� BLACK : %d\n", y, maxb[y]);
		else if (maxb[y] == maxw[y])
			printf("y%d��° ����� �밢�� ���� ���ӵ� �� BLACK : %d WHITE : %d\n", y, maxb[y], maxw[y]);
		else
			printf("y%d��° ����� �밢�� ���� ���ӵ� �� WHITE : %d\n", y, maxw[y]);
	}
	//����� �׷��� x 1 ~ 18
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
			printf("x%d��° ����� �밢�� ���� ���ӵ� �� BLACK : %d\n", x, maxb[x]);
		else if (maxb[x] == maxw[x])
			printf("x%d��° ����� �밢�� ���� ���ӵ� �� BLACK : %d WHITE : %d\n", x, maxb[x], maxw[x]);
		else
			printf("x%d��° ����� �밢�� ���� ���ӵ� �� WHITE : %d\n", x, maxw[x]);
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
			printf("%d��° ������ ���� ���ӵ� �� WHITE : %d\n", y, maxw[y]);
		printf("\n");
	}
}