#define _CRT_SECURE_NO_WARNINGS

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

typedef struct {
	int s;//������ ����
	int e;//������ ��
	int max;//���� Ƚ��
}checkline;

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

int main()
{
	char order;
	while (TRUE)
	{

		PrintBoard();	//�ٵ��� �׸���
		ScanTurn();	//��ĵ

		printf("��ɾ� : 1. �� ����(x,y) 5. �ߺ� �� �˻� : ");
		scanf_s(" %c", &order, 1);
		switch (order)
		{
		case '1':
		{
			scanf_s("%d %d", &inputX, &inputY);
			system("cls");

			if (inputX<0 || inputX > SIZE || inputY < 0 || inputY > SIZE)
			{
				printf("�߸��� ���Դϴ� �ٽ� �Է��� �ּ���.\n");
				continue;
			}
			if (IsSamePos() == TRUE)	//�ߺ� Ȯ�� �ߺ��̸� while �ٽ� ����
				break;
			InputStone(inputX, inputY);	//�� ���
			break;
		}
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
void InputStone(int x, int y)
{
	if (turn % 2 == 0)	//�浹 ���� ��
		Stone[y][x] = BLACK;
	else
		Stone[y][x] = WHITE;
	turn++;			//1�� ����
}
void ScanSide()
{
	checkline lineb[SIZE][SIZE];
	checkline linew[SIZE][SIZE];
	int linebc = 0, linewc = 0;//�ش� �ٿ� ���° ������

	//�ʱ�ȭ
	//for (int i = 0; i < SIZE; i++)
	//{
	//	lineb[i] = 0;
	//	linew[i] = 0;
	//}
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (Stone[y][x] == BLACK)
			{//3~5��° ���̸� s=3 e=5
				lineb[y][linebc].s = x;
				while (1)
				{
					lineb[y][linebc].e = x++;
					lineb[y][linebc].max++;
					if (Stone[y][x] != BLACK) {
						linebc++;
						break;
					}
				}
			}
		}

		int linemax[SIZE] = 0;
		for (int y = 0; y < SIZE; y++){
			for (int i = 0; i < linebc - 1; i++){
				if (linemax[y] < lineb[y][i].max + lineb[y][i + 1].max)
					linemax[y] = lineb[y][i].max + lineb[y][i + 1].max;
			}
		}

		printf("%d��° ������ BLACK : ", y);
		for (int i = 0; i < lineb[y]; i++)
			printf("(%d,%d)", y, tempb[y][i]);

		/*if (lineb[y] == 0 && linew[y] == 0)
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
		printf("\n");*/
	}
}