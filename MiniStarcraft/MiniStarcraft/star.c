#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

//bool
#define BOOL int
#define TRUE 1
#define FALSE 0

//unit
#define BLANK 0
#define HydraID 1
#define QueenID 2
#define UltraID 3
#define MarineID 4
#define TankID 5
#define VultureID 6
#define MaxUnitCount 1000

//������ ũ��
#define SIDE 40	
#define UPDOWN 20
board[UPDOWN][SIDE] = { BLANK };

void PrintUnit(int unitboard);	//��ġ�� ���� ���� �ϳ��� ���� ��ġ�� �׸�.
void Display();		//PrintUnit�� �����Ͽ� ���� ������ ��ġ ��ȫ�� �׸���.
void Produce();		//���ο� ������ ������ ��ġ�� ���� �� �� ���ο� ������ ������ �Է¹޴´�
//void Select();		//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ������ ������ ����Ѵ�.
//void SelectAll();	//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ��� ������ ������ ����Ѵ�.

int inputX, inputY;
char inputC;


int main()
{
	while (TRUE)
	{
		system("cls");
		Display();

		board[1][1] = HydraID;

		Sleep(300);
	}

	return 0;
}

void PrintUnit(int unitboard)
{
	if (unitboard == BLANK)
		printf("+");
	else if (unitboard == HydraID)
		printf("H");
	else if (unitboard == QueenID)
		printf("Q");
	else if (unitboard == UltraID)
		printf("U");
	else if (unitboard == MarineID)
		printf("M");
	else if (unitboard == VultureID)
		printf("G");
	else if (unitboard == TankID)
		printf("T");
	else
		printf("?");
}

void Display()
{
	for (int updown = 0; updown < UPDOWN; updown++)
	{
		for (int side = 0; side < SIDE; side++)
		{
			PrintUnit(board[updown][side]);
		}
		printf("\n");
	}
}

void Produce()
{
	printf("������ ������ �ּ��� (x��ǥ, y��ǥ, ���� ����");
	scanf("%d %d %c", &inputX, &inputY, &inputC);

	switch (inputC)
	{
	case 'H':
	{
		Hydra[]

		printf("����󸮽�ũ�� �����ϼ̽��ϴ�.\n");

	}

	}
}

//struct UnitInform
//{
//	//�̸�, ��ġ
//	char unitName[30];
//	int unitX;
//	int unitY;
//	//����
//	int MaxHP;
//	int MaxMP;
//	int Speed;
//	//ID
//	int UnitID;
//	int UnitOwnID;
//};

