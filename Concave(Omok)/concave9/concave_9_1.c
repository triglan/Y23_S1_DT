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
int lineb[SIZE] = { 0 }, linew[SIZE] = { 0 }, maxb = 0, maxw = 0, tempb[SIZE][SIZE * 2], tempw[SIZE][SIZE * 2];

int turn = 0;					// 0�� �ʱ�ȭ
int inputX, inputY;

FILE* fp;

void InputFile();
void OutputFile();

void StartStone();					// �ʱⰪ, �׽�Ʈ ��
void PrintStone(int printStone);	// �� ���
void PrintBoard();					// ������ ���
void CountStone();					// �˵�, �� ����� ����
void ScanTurn();					// �Է� �ޱ�
bool IsSamePos();					// �ߺ� �Է� �ޱ�
void InputStone(int inputX, int inputY);// �� �߰�

void ScanSide();
void ScanLine();
void ScanRightUp();
void ScanRightDown();
void ScanCount();

int main()
{
	StartStone();
	while (TRUE)
	{
		//InputFile();
		OutputFile();//���� ��� �׽�Ʈ
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
			PrintBoard();	//�ٵ��� �׸���
		}
		


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

void InputFile()//���Ͽ� �Է�
{
	fp = fopen("test.txt", "w"); //test������ w(����) ���� ����

	for (int y = 0; y < SIZE; y++)
	{//���� for��
		for (int x = 0; x < SIZE; x++)
		{//�¿� for��
			fprintf(fp, "%d", Stone[y][x]);
		}
		
	}
	fclose(fp);
}

void OutputFile()
{
	char str[100];
	fp = fopen("test.txt", "r");
	int c;
	while ((c = fgetc(fp)) != EOF) {
		putchar(c);
	}
	//for (int y = 0; y < SIZE; y++)
	//{//���� for��
	//	for (int x = 0; x < SIZE; x++)
	//	{//�¿� for��
	//		Stone[y][x] = fgets(str, 1, fp);
	//	}
	//}
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
			printf("%d��° ������ BLACK : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempb[y][i]);
		}
		else if (lineb[y] == linew[y])
		{
			printf("%d��° ������ BLACK : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempb[y][i]);

			printf("%d��° ������ WHITE : ", y);
			for (int i = 0; i < lineb[y]; i++)
				printf("(%d,%d)", y, tempw[y][i]);
		}
		else
		{
			printf("%d��° ������ WHITE : ", y);
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
			printf("%d��° ������ BLACK : %d", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("%d��° ������ BLACK : %d WHITE : %d", x, lineb[x], linew[x]);
		else
			printf("%d��° ������ WHITE : %d", x, linew[x]);
		printf("\n");
	}
}
void ScanRightDown()
{//������ 2,0 20, 18 // 0,2 18,20 
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
			printf("y%d��° ������ �밢�� BLACK : %d", y, lineb[y]);
		else if (lineb[y] == linew[y])
			printf("y%d��° ������ �밢�� BLACK : %d WHITE : %d", y, lineb[y], linew[y]);
		else
			printf("y%d��° ������ �밢�� WHITE : %d", y, linew[y]);
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
			printf("x%d��° ������ �밢�� BLACK : %d", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("x%d��° ������ �밢�� BLACK : %d WHITE : %d", x, lineb[x], linew[x]);
		else
			printf("x%d��° ������ �밢�� WHITE : %d", x, linew[x]);
		printf("\n");
	}
}
void ScanRightUp()
{
	//����� 3,0 0,3
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
			printf("y%d��° ����� �밢�� BLACK : %d", y, lineb[y]);
		else if (lineb[y] == linew[y])
			printf("y%d��° ����� �밢�� BLACK : %d WHITE : %d", y, lineb[y], linew[y]);
		else
			printf("y%d��° ����� �밢�� WHITE : %d", y, linew[y]);
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
			printf("x%d��° ����� �밢�� BLACK : %d", x, lineb[x]);
		else if (lineb[x] == linew[x])
			printf("x%d��° ����� �밢�� BLACK : %d WHITE : %d", x, lineb[x], linew[x]);
		else
			printf("x%d��° ����� �밢�� WHITE : %d", x, linew[x]);
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
		printf("%d��° �� ���� �� : %d �� �� : %d\n", y, lineb[y], linew[y]);
	}
}