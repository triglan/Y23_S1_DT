#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

#define FALSE 0
#define TRUE 1

#define HydraID 1
#define QueenID 2
#define DefilerID 3
#define MarineID 4
#define TankID 5
#define VesselID 6

#define UPDOWN 20
#define SIDE 40

#define Zerg 1
#define Terran 2

int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

typedef struct
{
	char name;
	int HP;
	int MP;

	int x;
	int y;

	int life;
	int tribeID;
	int unitID;
	int team;
}UnitInfo;

UnitInfo board[UPDOWN][SIDE];


void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);

void FirstBoard();

void Display();
void Produce(int x, int y, char c);
void Select(int x, int y);
void SelectAll(int x1, int y1, int x2, int y2);

void Destroy(int x, int y);
void FindTarget(int x1, int y1);
int Distance(int x1, int y1, int x2, int y2);
void SortByID();

int main()
{
	char select;
	char order;

	int inputX, inputY;
	int inputX1, inputY1;
	int inputX2, inputY2;

	FirstBoard();

	while (TRUE)
	{
		Display();

		printf("명령어 : ");
		scanf(" %c", &select);

		switch (select)
		{
		case'p':
			if (scanf("%d %d %c", &inputX, &inputY, &order) != 1)
			{
				system("cls");
				printf("잘못된 값");
				break;
			}
			system("cls");

			Produce(inputX, inputY, order);
			break;
		case's':
			scanf("%d %d", &inputX, &inputY);
			
			system("cls");

			Select(inputX, inputY);
			break;
		case 'S':
			scanf("%d %d %d %d", &inputX1, &inputY1, &inputX2, &inputY2);
			system("cls");

			SelectAll(inputX1, inputY1, inputX2, inputY2);
			break;

		case 'd':
			scanf("%d %d", &inputX, &inputY);
			system("cls");

			Destroy(inputX, inputY);
			break;
			
		case 'f':
			scanf("%d %d", &inputX, &inputY);
			system("cls");

			FindTarget(inputX, inputY);
			break;

		case 'a':
			system("cls");

			SortByID();
			break;

		default:
			system("cls");
			printf("잘못된 값\n");

			break;
		}
	}
	
}

void FirstBoard()
{
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

	Unit_H(39, 19);
	Unit_H(39, 18);
	Unit_H(37, 17);
	Unit_H(38, 16);
	Unit_H(39, 15);
	Unit_H(39, 14);

	Unit_Q(39, 17);
	Unit_Q(38, 17);

	Unit_D(39, 16);
	Unit_D(39, 15);
}

void Display()
{
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{
			if (board[y][x].life != 0)
				printf("%c", board[y][x].name);
			else
				printf("+");
		}
		printf("\n");
	}
}

void Produce(int x, int y, char c)
{
	if (c == 'h')
	{
		Unit_H(x, y);
		Select(x, y);
	}
	else if (c == 'q')
	{
		Unit_Q(x, y);
		Select(x, y);
	}
	else if (c == 'd')
	{
		Unit_D(x, y);
		Select(x, y);
	}
	else if (c == 'm')
	{
		Unit_M(x, y);
		Select(x, y);
	}
	else if (c == 't')
	{
		Unit_T(x, y);
		Select(x, y);
	}
	else if (c == 'v')
	{
		Unit_V(x, y);
		Select(x, y);
	}
	else
		printf("잘못된 값\n");
}

void Select(int x, int y)
{
	if (board[y][x].tribeID != 0)
	{
		printf("UNIT ID : %c%04d // HP : %d // MP : %d // 좌표 : (%d,%d)",
			board[y][x].name, board[y][x].unitID, board[y][x].HP, board[y][x].MP, board[y][x].x, board[y][x].y);

		printf("\n\n");
	}

}


void SelectAll(int x1, int y1, int x2, int y2)//1 1 3 3
{
	for (int y = y1; y <= y2; y++)
	{
		for (int x = x1; x <= x2; x++)
		{
			Select(x, y);
		}
	}
}
  
void Destroy(int x, int y)
{
	board[y][x].life = FALSE;
}

void FindTarget(int x1, int y1)
{
	int min = 1000000000;
	int minX[100] = { 0 };
	int minY[100] = { 0 };
	int minCount = 0;

	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{
			if (board[y2][x2].team != board[y1][x1].team && board[y2][x2].tribeID != 0 && Distance(x1, y1, x2, y2) < min)//팀다르고 공백아니고 최소값보다 작을 떄
			{
				for (int i = 0; i < minCount; i++)
				{
					minX[i] = 0;
					minY[i] = 0;
				}
				minCount = 0;

				min = Distance(x1, y1, x2, y2);
				minX[0] = board[y2][x2].x;
				minY[0] = board[y2][x2].y;
				minCount++;
			}
			else if(board[y2][x2].team != board[y1][x1].team && board[y2][x2].tribeID != 0 && Distance(x1, y1, x2, y2) == min)
			{
				minX[minCount] = board[y2][x2].x;
				minY[minCount] = board[y2][x2].y;
				minCount++;
			}
		}
	}

	for (int i = 0; i < minCount; i++)
	{
		Select(minX[i], minY[i]);
	}
}

int Distance(int x1, int y1, int x2, int y2)
{
	int unitDistance = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	return unitDistance;
}

void SortByID()
{
	for (int i = 0; i < DefilerCount; i++)
	{
		for (int y = 0; y <= UPDOWN; y++)
		{
			for (int x = 0; x <= SIDE; x++)
			{
				if (board[y][x].tribeID == DefilerID && board[y][x].unitID == i)
				{
					Select(x, y);
				}

			}
		}
	}

}

void Unit_H(int x, int y)
{
	board[y][x].name = 'H';
	board[y][x].HP = 50;
	board[y][x].MP = 0;

	board[y][x].x = x;
	board[y][x].y = y;

	board[y][x].life = TRUE;
	board[y][x].tribeID = HydraID;
	board[y][x].unitID = HydraCount;
	board[y][x].team = Zerg;

	HydraCount++;
}

void Unit_Q(int x, int y)
{
	board[y][x].name = 'Q';
	board[y][x].HP = 70;
	board[y][x].MP = 150;

	board[y][x].x = x;
	board[y][x].y = y;

	board[y][x].tribeID = QueenID;
	board[y][x].unitID = QueenCount;
	board[y][x].life = TRUE;
	board[y][x].team = Zerg;

	QueenCount++;
}

void Unit_D(int x, int y)
{
	board[y][x].name = 'D';
	board[y][x].HP = 60;
	board[y][x].MP = 200;

	board[y][x].x = x;
	board[y][x].y = y;

	board[y][x].tribeID = DefilerID;
	board[y][x].unitID = DefilerCount;
	board[y][x].life = TRUE;
	board[y][x].team = Zerg;

	DefilerCount++;
}

void Unit_M(int x, int y)
{
	board[y][x].name = 'M';
	board[y][x].HP = 30;
	board[y][x].MP = 0;

	board[y][x].x = x;
	board[y][x].y = y;

	board[y][x].tribeID = MarineID;
	board[y][x].unitID = MarineCount;
	board[y][x].life = TRUE;
	board[y][x].team = Terran;

	MarineCount++;
}

void Unit_T(int x, int y)
{
	board[y][x].name = 'T';
	board[y][x].HP = 120;
	board[y][x].MP = 0;

	board[y][x].x = x;
	board[y][x].y = y;

	board[y][x].tribeID = TankID;
	board[y][x].unitID = TankCount;
	board[y][x].life = TRUE;
	board[y][x].team = Terran;

	TankCount++;
}

void Unit_V(int x, int y)
{
	board[y][x].name = 'V';
	board[y][x].HP = 80;
	board[y][x].MP = 140;

	board[y][x].x = x;
	board[y][x].y = y;

	board[y][x].tribeID = VesselID;
	board[y][x].unitID = VesselCount;
	board[y][x].life = TRUE;
	board[y][x].team = Terran;

	VesselCount++;
}
