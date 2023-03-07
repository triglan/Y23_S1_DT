#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

//������ ũ��
#define SIDE 40	
#define UPDOWN 20
board[UPDOWN][SIDE] = { 0 };

//bool
#define BOOL int
#define TRUE 1
#define FALSE 0

#define BLANK 0
#define HydraID 1
#define QueenID 2
#define UltraID 3
#define MarineID 4
#define GhostID 5
#define TankID 6
#define MaxUnitCount 1000


void PrintUnit(int unitboard);	//��ġ�� ���� ���� �ϳ��� ���� ��ġ�� �׸�.
void Display();		//PrintUnit�� �����Ͽ� ���� ������ ��ġ ��ȫ�� �׸���.
void Produce();		//���ο� ������ ������ ��ġ�� ���� �� �� ���ο� ������ ������ �Է¹޴´�
void Select();		//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ������ ������ ����Ѵ�.
void SelectAll();	//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ��� ������ ������ ����Ѵ�.

struct UnitInform;	//���� ���� ����ü
void UnitInformation();


int inputX, inputY;
char inputC;

int* NewHydra[500];
int HydraCount = 0;

int main()
{
	while (TRUE)
	{
		Display();
	}
}

void PrintUnit(int unitboard)
{
	if (board == BLANK)
		printf("+");
	if(board == HydraID)
		printf("H");
	if(board == QueenID)
		printf("Q");
	if(board == UltraID)
		printf("U");
	if(board == MarineID)
		printf("M");
	if(board == GhostID)
		printf("G");
	if(board == TankID)
		printf("T");
}

void Display()
{
	for (int updown = 0; updown < UPDOWN; updown++)
	{
		for (int side = 0; side < SIDE; side++)
		{
			PrintUnit(board[updown][side]);
		}
	}
}

struct UnitInform Hydra = { .unitName = "Hydra", .unitX = 0, .unitY = 0, .MaxHP = 100, .MaxMP = 50, .Speed = 3, .UnitID = 1 };

void Produce()
{
	printf("������ ������ �ּ��� (x��ǥ, y��ǥ, ���� ����");
	scanf("%d %d %c", &inputX, &inputY, &inputC);

	switch (inputC)
	{
	case 'H':
	{
		printf("����󸮽�ũ�� �����ϼ̽��ϴ�.\n");
		NewHydra[HydraCount] = (int*)malloc(sizeof(int));	//�� ����� �����
		HydraCount++;										//����� ī��Ʈ+1
		struct UnitInform Hydra = {.unitX = inputX, .unitY = inputY, .UnitID = HydraID };

	}
	case 'Q':

	}
}

void UnitInformation()
{
	//struct UnitInform Hydra = { .unitName = "Hydra", .unitX = 0, .unitY = 0, .MaxHP = 100, .MaxMP = 50, .Speed = 3, .UnitID = 1};
	

}

struct UnitInform
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
	int UnitID;
	int UnitOwnID;
};


//tempword