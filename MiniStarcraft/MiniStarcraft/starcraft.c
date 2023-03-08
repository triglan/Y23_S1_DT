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
#define DefilerID 3
#define MarineID 4
#define TankID 5
#define VesselID 6
#define MaxUnitCount 1000

//���� ��
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

//������ ũ��
#define SIDE 40	
#define UPDOWN 20

//���� ����
typedef struct
{
	//�̸�, ��ġ
	char unitName;
	int unitX;
	int unitY;
	//����
	int MaxHP;
	int MaxMP;
	int Speed;
	int ATK;
	int Range;
	int Splash;
	int SkillMP;
	int team;
	int produce;
	//ID
	int tribeID;//���� ID
	int unitID;	//���� ID	
} boardInform;

char c = '1';
boardInform board[UPDOWN][SIDE];

//���� ���� �ο�
void SelectMenu(char order);		//��� ���� �Լ�
void PrintUnit(int unitboard);	//��ġ�� ���� ���� �ϳ��� ���� ��ġ�� �׸�.
void Display();		//PrintUnit�� �����Ͽ� ���� ������ ��ġ ��ȫ�� �׸���.
void Produce(int x, int y, char c);		//���ο� ������ ������ ��ġ�� ���� �� �� ���ο� ������ ������ �Է¹޴´�
void Select(int x, int y);		//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ������ ������ ����Ѵ�.
void SelectAll(int x1, int y1, int x2, int y2);	//�־��� ��ǥ�� ��ġ�ϰ� �ִ� ��� ������ ������ ����Ѵ�.

//Destroy();
//FindTarget();
//SortByID();

//���� ���� ���
void PrintUnitInfo(int x, int y);
void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);

//�ʱ�ȭ
void Clear(int x, int y);
void FirstBoard();

int inputX, inputY;
int inputX1, inputY1;
int inputX2, inputY2;
char inputC;
char selectC;

int main()
{
	PrintUnitInfo(1, 1);

	FirstBoard();
	Display(); 
	printf("\n");
	while (TRUE)
	{
		selectC = 0;
		inputC = 0;
		//TODO : �߸��� �� ������ �ٽ�
		printf("��ɾ�(�ѹ��� �Է� ����) (p : ����, s : ���� ���� ��ȸ, S : ���� ) : ");
		scanf(" %c", &selectC);

		SelectMenu(selectC);

		Display();
		printf("\n");
		
	}

	return 0;
}

void FirstBoard()	//�ʱ� ��ġ
{
	for (int i = 0; i < UPDOWN * SIDE - 1; i++)
	{
		Clear(i / SIDE, i % SIDE);
	}//������ �ʱ�ȭ

	Unit_M(0, 0);
	Unit_M(0, 1);
	Unit_M(0, 2);
	Unit_M(1, 3);
	Unit_M(1, 4);
	Unit_M(0, 5);

	Unit_T(0, 3);
	Unit_T(0, 4);
	
	Unit_V(1, 2);
	Unit_V(2, 2);


	Unit_V(39, 20);
	Unit_V(39, 19);
	Unit_V(37, 17);
	Unit_V(39, 14);

	Unit_D(39, 16);
	Unit_D(39, 15);

	Unit_Q(39, 17);
	Unit_Q(38, 17);
}

void SelectMenu(char order)
{
	if (selectC == 'p')
	{//����
		printf("��ɾ�(x��ǥ, y��ǥ, ���� ����(h) : ");
		scanf("%d %d %c", &inputX, &inputY, &inputC);
		system("cls");

		Produce(inputX, inputY, inputC);
		printf("\n");
	}

	if (selectC == 's')
	{//���� ��ȸ
		printf("��ɾ�(x��ǥ, y��ǥ) : ");
		scanf("%d %d", &inputX, &inputY);
		system("cls");

		printf("(%d, %d) ��ġ�� ���� ��ȸ\n", inputX, inputY);
		Select(inputX, inputY);
		printf("\n");
	}

	if (selectC == 'S')
	{//���� ���� ��ȸ
		printf("��ɾ�(x1��ǥ, y1��ǥ, x2��ǥ, y2��ǥ) : ");
		scanf("%d %d %d %d", &inputX1, &inputY1, &inputX2, &inputY2);
		system("cls");

		printf("(%d, %d) (%d, %d) ������ ���� ��ȸ\n", inputX1, inputY1, inputX2, inputY2);
		SelectAll(inputX1, inputY1, inputX2, inputY2);
		printf("\n");
	}
}

void PrintUnit(int unitboard)
{
	if (unitboard == BLANK)
		printf("+");
	else if (unitboard == HydraID)
		printf("H");
	else if (unitboard == QueenID)
		printf("Q");
	else if (unitboard == DefilerID)
		printf("D");
	else if (unitboard == MarineID)
		printf("M");
	else if (unitboard == VesselID)
		printf("V");
	else if (unitboard == TankID)
		printf("T");
	else
		printf("?");
}

//p
//5 10 D

void Display()
{
	for (int updown = 0; updown < UPDOWN; updown++)
	{
		for (int side = 0; side < SIDE; side++)
		{
			PrintUnit(board[updown][side].tribeID);
		}
		printf("\n");
	}
}

void Produce(int x, int y, char c)
{
	if (c == 'h' || c == 'H')
	{
		Unit_H(x, y);
		PrintUnitInfo(x, y);
	}
}

void Select(int x, int y)
{
	PrintUnitInfo(x, y);
}

void SelectAll(int x1, int y1, int x2, int y2)//1,1 3,3 
{
	for (int x = x1; x <= x2; x++)	//x1~x2
	{
		for (int y = y1; y <= y2; y++)//y1~y2
		{
			if (board[y][x].tribeID != BLANK)
			{
				PrintUnitInfo(x, y);
				printf("\n");
			}
		}
	}
}

//Destroy();
//FindTarget();
//SortByID();

void PrintUnitInfo(int x, int y)
{
		printf("UnitInfo : Unit name: %c, ��ǥ(%d,%d) MaxHP: %d, MaxMP: %d, Speed: %d, \nATK: %d, Range: %d, Splash: %d, SkillMP: %d, team: %d, tribeID: %d, unitID: %c%04d\n",
			board[y][x].unitName, board[y][x].unitX, board[y][x].unitY, board[y][x].MaxHP, board[y][x].MaxMP, board[y][x].Speed, board[y][x].ATK,
			board[y][x].Range, board[y][x].Splash, board[y][x].SkillMP, board[y][x].team, board[y][x].tribeID,
			board[y][x].unitName, board[y][x].unitID);
		//04d �ϸ� 4��° �ڸ����� ���
}

void Unit_H(int x, int y)
{
	board[y][x].unitName = 'H';
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].MaxHP = 100;
	board[y][x].MaxMP = 0;
	board[y][x].Speed = 3;
	board[y][x].Range = 5;
	board[y][x].ATK = 25;
	board[y][x].SkillMP = 0;
	board[y][x].Splash = 1;
	board[y][x].produce = 1;

	board[y][x].team = 0;
	board[y][x].tribeID = HydraID;
	board[y][x].unitID = HydraCount;	//��� unitID : unitName + 00 + unitID

	HydraCount++;
}

void Unit_Q(int x, int y)
{
	board[y][x].unitName = 'Q';
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].MaxHP = 70;
	board[y][x].MaxMP = 150;
	board[y][x].Speed = 6;
	board[y][x].Range = 15;
	board[y][x].ATK = 1000;
	board[y][x].SkillMP = 45;
	board[y][x].Splash = 1;
	board[y][x].produce = 2;

	board[y][x].team = 0;
	board[y][x].tribeID = QueenID;
	board[y][x].unitID = QueenCount;	//��� unitID : unitName + 00 + unitID

	QueenCount++;
}

void Unit_D(int x, int y)
{
	board[y][x].unitName = 'D';
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].MaxHP = 60;
	board[y][x].MaxMP = 200;
	board[y][x].Speed = 2;
	board[y][x].Range = 4;
	board[y][x].ATK = 20;
	board[y][x].SkillMP = 60;
	board[y][x].Splash = 5 * 5;
	board[y][x].produce = 2;

	board[y][x].team = 0;
	board[y][x].tribeID = DefilerID;
	board[y][x].unitID = DefilerCount;	//��� unitID : unitName + 00 + unitID

	DefilerCount++;
}

void Unit_M(int x, int y)
{
	board[y][x].unitName = 'M';
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].MaxHP = 30;
	board[y][x].MaxMP = 0;
	board[y][x].Speed = 3;
	board[y][x].Range = 4;
	board[y][x].ATK = 20;
	board[y][x].SkillMP = 0;
	board[y][x].Splash = 1;
	board[y][x].produce = 1;

	board[y][x].team = 0;
	board[y][x].tribeID = MarineID;
	board[y][x].unitID = MarineCount;	//��� unitID : unitName + 00 + unitID

	MarineCount++;
}

void Unit_T(int x, int y)
{
	board[y][x].unitName = 'T';
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].MaxHP = 120;
	board[y][x].MaxMP = 0;
	board[y][x].Speed = 4;
	board[y][x].Range = 17;
	board[y][x].ATK = 40;
	board[y][x].SkillMP = 0;
	board[y][x].Splash = 1;
	board[y][x].produce = 2;

	board[y][x].team = 0;
	board[y][x].tribeID = TankID;
	board[y][x].unitID = TankCount;	//��� unitID : unitName + 00 + unitID

	TankCount++;
}

void Unit_V(int x, int y)
{
	board[y][x].unitName = 'V';
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].MaxHP = 80;
	board[y][x].MaxMP = 140;
	board[y][x].Speed = 5;
	board[y][x].Range = 12;
	board[y][x].ATK = 50;
	board[y][x].SkillMP = 35;
	board[y][x].Splash = 3 * 3;
	board[y][x].produce = 2;

	board[y][x].team = 0;
	board[y][x].tribeID = VesselID;
	board[y][x].unitID = VesselCount;	//��� unitID : unitName + 00 + unitID

	VesselCount++;
}

void Clear(int y, int x)
{
	board[y][x].unitName = BLANK;
	board[y][x].unitX = BLANK;
	board[y][x].unitY = BLANK;

	board[y][x].MaxHP = BLANK;
	board[y][x].MaxMP = BLANK;
	board[y][x].Speed = BLANK;
	board[y][x].Range = BLANK;
	board[y][x].ATK = BLANK;
	board[y][x].SkillMP = BLANK;
	board[y][x].Splash = BLANK;
	board[y][x].produce = BLANK;

	board[y][x].team = BLANK;
	board[y][x].tribeID = BLANK;
	board[y][x].unitID = BLANK;	//��� unitID : unitName + BLANKBLANK + unitID

}