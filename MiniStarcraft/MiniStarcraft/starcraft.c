#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>

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
#define MaxUnitCount 10000

//������ ũ��
#define SIDE 40	
#define UPDOWN 20
board[UPDOWN][SIDE] = { BLANK, };

void PrintUnit(int unitboard);	//��ġ�� ���� ���� �ϳ��� ���� ��ġ�� �׸�.
void Display();		//PrintUnit�� �����Ͽ� ���� ������ ��ġ ��ȫ�� �׸���.
void Produce();		//���ο� ������ ������ ��ġ�� ���� �� �� ���ο� ������ ������ �Է¹޴´�
//void Select();		//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ������ ������ ����Ѵ�.
//void SelectAll();	//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ��� ������ ������ ����Ѵ�.

//typedef struct UnitInform;	//���� ���� ����ü
void UnitInformation();

//�Է�
int inputX, inputY;
char inputC;


int main()
{
	while (TRUE)
	{
		system("cls");
		Display();

		UnitInformation();

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

typedef struct 
{
	//�̸�, ��ġ
	char unitName[30];
	int unitX;
	int unitY;
	//����
	int MaxHP;
	int MaxMP;
	int Speed;
	//ID
	int tribeID;//���� ID
	int unitID;	//���� ID	
} UnitInform;

void GeneratedUnit()
{
	//����� �Ҵ�
	UnitInform Hydra[MaxUnitCount] = { 0 };

	//����� for������ �ʱ�ȭ
	for (int i = 0; i < MaxUnitCount; i++)
	{
		strcpy(Hydra[i].unitName, "Hydra");
		//Hydra[i].unitX = 0;
		//Hydra[i].unitY = 0;
		Hydra[i].MaxHP = 100;
		Hydra[i].MaxMP = 50;
		Hydra[i].Speed = 3;
		Hydra[i].tribeID = HydraID;	//���߿� ID�� ���� ���ڷ� ���
		Hydra[i].unitID = MaxUnitCount + i;
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
		Hydra[HydraNum]
		Hydra


		printf("����󸮽�ũ�� �����ϼ̽��ϴ�.\n");
		
	}
	}
}


