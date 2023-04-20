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
//�� ��
#define SIZE 19// ���� ����
#define DIAG 37// �밢�� ����
int Stone[SIZE][SIZE] = { 0 };	
int linecountb[SIZE];
int linecountw[SIZE];

int lengthcountb[37];
int lengthcountw[37];

int turn = 0;					// 0�� �ʱ�ȭ
int inputX, inputY;

void StartStone();
void PrintStone(int printStone);	// �� ���
void PrintBoard();					// ������ ���
void CountStone();					// �˵�, �� ����� ����
void ScanTurn();					// �Է� �ޱ�
bool IsSamePos();					// �ߺ� �Է� �ޱ�
void InputStone(int inputX, int inputY);					// �� �߰�
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

		PrintBoard();	//�ٵ��� �׸���
		DownDirect();

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
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (x < SIZE)
				{
					tempblack++;
					x++;
					if (Stone[y][x] != BLACK)
						break;
				}
				if (tempblack > linecountb[y])//�ִ밪�̸� �־�
					linecountb[y] = tempblack;
			}
			if (Stone[y][x] == WHITE)
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (x < SIZE)
				{
					tempwhite++;
					x++;
					if (Stone[y][x] != WHITE)
						break;
				}
				if (tempwhite > linecountw[y])//�ִ밪�̸� �־�
					linecountw[y] = tempwhite;
			}
		}
		{
			if (linecountb[y] > linecountw[y])
				printf("%d��° ���� �� ���� ���ӵ� �� Black : %d\n", y, linecountb[y]);
			else if (linecountb[y] == linecountw[y])
				printf("%d��° ���� �� ���� ���ӵ� �� Black : %d, White : %d\n", y, linecountb[y], linecountw[y]);
			else
				printf("%d��° ���� �� ���� ���ӵ� �� White : %d\n", y, linecountw[y]);

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
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (y < SIZE)
				{
					tempblack++;
					y++;
					if (Stone[y][x] != BLACK)
						break;
				}
				if (tempblack > lengthcountb[x])//�ִ밪�̸� �־�
					lengthcountb[x] = tempblack;
			}
			if (Stone[y][x] == WHITE)
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (y < SIZE)
				{
					tempwhite++;
					y++;
					if (Stone[y][x] != WHITE)
						break;
				}
				if (tempwhite > lengthcountw[x])//�ִ밪�̸� �־�
					lengthcountw[x] = tempwhite;
			}
		}

		if (lengthcountb[x] > lengthcountw[x])
			printf("%d��° ���� �� ���� ���ӵ� �� Black : %d\n", x, lengthcountb[x]);
		else if (lengthcountb[x] == lengthcountw[x])
			printf("%d��° ���� �� ���� ���ӵ� �� Black : %d, White : %d\n", x, lengthcountb[x], lengthcountw[x]);
		else
			printf("%d��° ���� �� ���� ���ӵ� �� White : %d\n", x, lengthcountw[x]);

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
				{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
					while (j <= i)
					{
						tempblack++;
						j++;
						if (Stone[j][i - j] != BLACK)
							break;
					}
					if (tempblack > linecountb[i])//�ִ밪�̸� �־�
						linecountb[i] = tempblack;
				}
				if (Stone[j][i - j] == WHITE)
				{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
					while (j <= i)
					{
						tempwhite++;
						j++;
						if (Stone[j][i - j] != WHITE)
							break;
					}
					if (tempwhite > linecountw[i])//�ִ밪�̸� �־�
						linecountw[i] = tempwhite;
				}
			}
		}
		{
			if (linecountb[i] > linecountw[i])
				printf("%d��° �밢�� �� ���� ���ӵ� �� Black : %d\n", i, linecountb[i]);
			else if (linecountb[i] == linecountw[i])
				printf("%d��° �밢�� �� ���� ���ӵ� �� Black : %d, White : %d\n", i, linecountb[i], linecountw[i]);
			else
				printf("%d��° �밢�� �� ���� ���ӵ� �� White : %d\n", i, linecountw[i]);

			tempblack = 0;
			tempwhite = 0;
		}
	}
}
//������ �밢��
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
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (y <= SIZE - x)
				{
					tempblack++;
					y++;
					if (Stone[y][x + y] != BLACK)
						break;
				}
				if (tempblack > linecountb[x])//�ִ밪�̸� �־�
					linecountb[x] = tempblack;
			}
			if (Stone[y][x + y] == WHITE)
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (y <= SIZE - x)
				{
					tempwhite++;
					y++;
					if (Stone[y][x + y] != WHITE)
						break;
				}
				if (tempwhite > linecountw[x])//�ִ밪�̸� �־�
					linecountw[x] = tempwhite;
			}
		}
		{
			if (linecountb[x] > linecountw[x])
				printf("x%d��° �밢�� �� ���� ���ӵ� �� Black : %d\n", x, linecountb[x]);
			else if (linecountb[x] == linecountw[x])
				printf("x%d��° �밢�� �� ���� ���ӵ� �� Black : %d, White : %d\n", x, linecountb[x], linecountw[x]);
			else
				printf("x%d��° �밢�� �� ���� ���ӵ� �� White : %d\n", x, linecountw[x]);

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
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (x <= SIZE - y)
				{
					tempblack++;
					x++;
					if (Stone[x + y][x] != BLACK)
						break;
				}
				if (tempblack > linecountb[y])//�ִ밪�̸� �־�
					linecountb[y] = tempblack;
			}
			if (Stone[x + y][x] == WHITE)
			{//�ٸ��� �˻� �������̸� ������ �ƴ� �� ���� ���ϰ� �������̸� ���߰� ���� ���� ���Ӽ����� ũ�� ���� not Ż��
				while (x <= SIZE - y)
				{
					tempwhite++;
					x++;
					if (Stone[x + y][x] != WHITE)
						break;
				}
				if (tempwhite > linecountw[y])//�ִ밪�̸� �־�
					linecountw[y] = tempwhite;
			}
		}
		{
			if (linecountb[y] > linecountw[y])
				printf("y%d��° �밢�� �� ���� ���ӵ� �� Black : %d\n", y, linecountb[y]);
			else if (linecountb[y] == linecountw[y])
				printf("y%d��° �밢�� �� ���� ���ӵ� �� Black : %d, White : %d\n", y, linecountb[y], linecountw[y]);
			else
				printf("y%d��° �밢�� �� ���� ���ӵ� �� White : %d\n", y, linecountw[y]);

			tempblack = 0;
			tempwhite = 0;
		}
	}
}