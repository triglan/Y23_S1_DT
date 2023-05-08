#include <stdio.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS

#define FALSE 0
#define TRUE 1

#define BLANK 0
#define WHITE 1
#define BLACK 2

typedef int bool;

#define ROW 19	//�� ���� + 1
#define COL 19	//�� ���� + 1

int inputX = 0, inputY = 0;	//�Է¹ޱ�
int turn = 0;		//�� �鵹 ����, 0�� �浹 ������

void PrintStone(int printStone);	//0 : *, 1 : �� : ��, �� : ��
void PrintBoard();					//�ٵ��� ���
void addStone();			//�÷��̾� �� �����ؼ� �� �� �α�
void InputStone();
bool isSamePos(int, int);

int Stone[COL][ROW] = { 0 };	//�� �ʱ�ȭ



int main()
{

	while (TRUE)
	{
		PrintBoard();	//������ ���
		printf("%d�� �׽��ϴ�.\n\n", turn);
		InputStone();	//scanf�� �÷��̾� ���� �Է�
		system("cls");

		//�ߺ�üũ �Լ� ȣ���ؼ� �ߺ��̸� continue �ƴϸ� �״�ΰ���
		if (isSamePos(inputX, inputY))
			continue;

		//addStone���� �߰�
		addStone();

		turn++;			//1�� ���


		//AI~~
	}
}



void PrintStone(int printStone)
{
	if (printStone == 0)
		printf("* ");
	else if (printStone == BLACK)
		printf("��");
	else if (printStone == WHITE)
		printf("��");
}

void PrintBoard()
{
	for (int UpDown = 0; UpDown < COL; UpDown++)	//���� ������ üũ �� ���
	{
		for (int Side = 0; Side < ROW; Side++)
		{
			PrintStone(Stone[UpDown][Side]); //����, ��, ������ Ȯ�� �� ���
		}//��
		printf("\n");
	}//��
}



void addStone()	//���ô��� ���� �ش� ���� �ٲ��ִ� �Լ�
{
	int player = 0;	//�浹 �÷��̾� ������ �ƴ���

	if (turn % 2 == 0)	//¦�� ���� �� �浹
	{
		player = BLACK;
	}
	else			//Ȧ�� ���� �� �鵹
	{
		player = WHITE;
	}

	Stone[inputY][inputX] = player;
}

void InputStone()	//�ش� �÷��̾ Ȯ���ϰ� scanf
{
	if (turn % 2 == 0)	//¦�� ���� �� �浹
	{
		printf("�浹");
	}
	else			//Ȧ�� ���� �� �鵹
	{
		printf("�鵹");
	}
	printf("�����Դϴ�. [��] (0~18) [��] (0~18) ������ �Է��� �ּ��� : ");
	scanf_s("%d %d", &inputX, &inputY);
}

bool isSamePos(int x, int y)	//�ߺ�Ȯ��
{
	if (Stone[y][x] != 0)
	{
		printf("�̹� ���� ���� �ֽ��ϴ�\n\n");
		return TRUE;		//�����̸� trues
	}
	return FALSE;	//������ �ƴϸ� false
}
