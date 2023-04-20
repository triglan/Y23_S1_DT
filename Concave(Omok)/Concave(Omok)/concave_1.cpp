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
#define ROW 19	// �� ����
#define COL 19	// �� ����

int Stone[COL][ROW] = { 0 };	// 
int turn = 0;					// 0�� �ʱ�ȭ

int inputX, inputY;

void PrintStone(int printStone);	// �� ���
void PrintBoard();					// ������ ���
void CountStone();					// �˵�, �� ����� ����
void ScanStone();					// �Է� �ޱ�
bool IsSamePos();					// �ߺ� �Է� �ޱ�
void InputStone(int inputX, int inputY);					// �� �߰�


int main()
{
	while (TRUE)
	{
		PrintBoard();	//�ٵ��� �׸���

		ScanStone();	//��ĵ
		system("cls");

		if (IsSamePos() == TRUE)	//�ߺ� Ȯ�� �ߺ��̸� while �ٽ� ����
			continue;

		InputStone(inputX, inputY);	//�� ���

		turn++;			//1�� ����
	}

}

void PrintStone(int printStone)
{
	if (printStone == BLANK)
		printf("* ");
	if (printStone == BLACK)
		printf("��");
	if (printStone == WHITE)
		printf("��");
}

void PrintBoard()
{
	CountStone();
	for (int UpDown = 0; UpDown < COL; UpDown++)
	{//���� for��
		for (int Side = 0; Side < ROW; Side++)
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
	for (int UpDown = 0; UpDown < COL; UpDown++)
	{
		for (int Side = 0; Side < ROW; Side++)
		{
			if (Stone[UpDown][Side] == BLACK)
				BlackStone++;
			if (Stone[UpDown][Side] == WHITE)
				WhiteStone++;
		}
	}
	printf("���� �� : %d �� �� : %d\n", BlackStone, WhiteStone);
}

void ScanStone()
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
	scanf("%d %d", &inputX, &inputY);
}


void InputStone(int InputX, int InputY)
{
	if (turn % 2 == 0)	//�浹 ���� ��
		Stone[inputY][inputX] = BLACK;
	else
		Stone[inputY][inputX] = WHITE;
}