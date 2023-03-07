//������ ��� -> �÷��̾� �Է� -> �ߺ�Ȯ�� continue -> ���������� �ٲ��ֱ� -> turn++

#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

//boolŸ�� ����
#define bool int
#define FALSE 0
#define TRUE 1
//���� 0 �˵�1 ��2
#define BLANK 0
#define BLACK 1
#define WHITE 2
//�࿭
#define ROW 19	// �� ����
#define COL 19	// �� ����
//���� ��
int Stone[COL][ROW];
//�Է¹޴� �� ����
int InputX, InputY;
//��
int turn = 0;


void PrintStone(int printStone);	// ���� ��� ���
void PrintBoard();					// ������ ���
void ScanStone();					// �÷��̾� Ȯ�� �� �Է�
void InputStone(int PlayerInputX, int PlayerInputY);					// 
bool IsSamePos(int PlayerInputX, int PlayerInputY);					// �ߺ� Ȯ��

int main()
{
	while (TRUE)
	{
		printf("���� �� : %d �� �� : %d\n", turn / 2 + turn % 2, turn / 2);
		PrintBoard();				//������ ���

		ScanStone();	//���� ��ĵ
		system("cls");

		if (IsSamePos(InputX, InputY))			//�ߺ� Ȯ��
			continue;

		InputStone(InputX, InputY);				//���� ����
		turn++;									//��+1
	}

}

void PrintStone(int printStone)
{
	if (printStone == BLANK)
		printf("+ ");
	if (printStone == BLACK)
		printf("��");
	if (printStone == WHITE)
		printf("��");
}

void PrintBoard()
{
	for (int UpDown = 0; UpDown < COL; UpDown++)
	{
		for (int Side = 0; Side < ROW; Side++)
		{
			PrintStone(Stone[UpDown][Side]);
		}
		printf("\n");
	}
}


void ScanStone()
{
	int player = 0;
	if (turn % 2 == 0)	//¦���� �浹
	{
		player = BLACK;
		printf("�浹");
	}
	else
	{
		player = WHITE;
		printf("�鵹");
	}
	printf(" �÷��̾��� ���Դϴ�. ��[0~18] ��[0~18] �� ���� �Է����ּ��� : ");

	scanf("%d %d", &InputX, &InputY);
	
}

void InputStone(int PlayerInputX, int PlayerInputY)
{
	if (turn % 2 == 0)	//¦���� �浹
	{
		Stone[PlayerInputY][PlayerInputX] = BLACK;
	}
	else			//Ȧ���� �鵹
	{
		Stone[PlayerInputY][PlayerInputX] = WHITE;
	}
	
}

bool IsSamePos(int PlayerInputX, int PlayerInputY)
{
	if (Stone[PlayerInputY][PlayerInputX] != 0)
	{
		printf("�̹� ���� ���� �ֽ��ϴ�.\n\n");
		return TRUE;
	}
	return FALSE;
}