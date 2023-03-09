#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

#define TRUE 1
#define FALSE 0

#define UPDOWN 20
#define SIDE 40

#define HydraID 1
#define QueenID 2
#define DefilerID 3
#define MarineID 4
#define TankID 5
#define VesselID 6

#define Zerg 1 
#define Terran 2

typedef struct
{
	char unitName;
	int HP;
	int MP;

	int unitX;
	int unitY;

	int tribeID;
	int unitID;
	int team;
	int life;
}UnitInfo;

int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;


void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);


void Display();
void Produce(int x, int y, char c);
void Select(int x, int y);
void SelectAll(int x1, int y1, int x2, int y2);

void Destroy(int x, int y);
void FindTarget(int x1, int y1);
void SortByID();

void FirstBoard();

UnitInfo board[UPDOWN][SIDE];


int main()
{
	int inputX = 0, inputY = 0;
	int inputX1 = 0, inputY1 = 0;
	int inputX2 = 0, inputY2 = 0;

	char select = 0;
	char unitOrder = 0;

	FirstBoard();
	while (TRUE)
	{
		Display();
		printf("명령어 : p 생산 s 정보 S 전체 정보 d 삭제 f 가까운 적 찾기 a 모든 유닛 출력 : ");
		scanf(" %c", &select);

		switch (select)
		{
		case 'p':
			scanf("%d %d %c", &inputX, &inputY, &unitOrder);
			system("cls");

			Produce(inputX, inputY, unitOrder);

			break;
		case 's':
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
			printf("잘못된 값");
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
			if (board[y][x].life != FALSE)
				printf("%c", board[y][x].unitName);
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


}

void Select(int x, int y)
{
	if (board[y][x].tribeID != 0)
	{
		printf("UNIT ID : %c%04d // HP : %d // MP : %d // 좌표 : (%d,%d)",
			board[y][x].unitName, board[y][x].unitID, board[y][x].HP, board[y][x].MP, board[y][x].unitX, board[y][x].unitY);

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
	int min = 10000000;
	int minIDX[100] = { 0 };
	int minIDY[100] = { 0 };
	int minCount = 0;

	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{
			if (board[y2][x2].team != board[y1][x1].team && board[y2][x2].tribeID != 0 && Distance(x1, y1, x2, y2) < min)//팀이 같으면 안되고 빈땅이면 안되고 최소값보다 작아야함
			{
				for (int i = 0; i < minCount; i++)
				{
					minIDX[minCount] = 0;
					minIDY[minCount] = 0;
				}//초기화
				minCount = 0;

				min = Distance(x1, y1, x2, y2);	//최소거리 값 넣기
				minIDX[0] = board[y2][x2].unitX;
				minIDY[0] = board[y2][x2].unitY;
				minCount++;
			}
			else if (board[y2][x2].team != board[y1][x1].team && board[y2][x2].tribeID != 0 && Distance(x1, y1, x2, y2) < min)//최소값이랑 같을 때 중복 출력
			{
				minIDX[minCount] = board[y2][x2].unitX;
				minIDY[minCount] = board[y2][x2].unitY;
				minCount++;

			}
		}
	}
	
	for (int i = 0; i < minCount; i++)
	{
		Select(minIDX[i], minIDY[i]);
	}
}

int Distance(int x1, int y1, int x2, int y2)
{
	int unitDistance = ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return unitDistance;
}

void SortByID()
{
	for (int i = 0; i < DefilerCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)//20
		{
			for (int x = 0; x < SIDE; x++)//40
			{
				if (board[y][x].tribeID == DefilerID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}

	for (int i = 0; i < HydraCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{
				if (board[y][x].tribeID == HydraID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}

	for (int i = 0; i < MarineCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{
				if (board[y][x].tribeID == MarineID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}

	for (int i = 0; i < TankCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{
				if (board[y][x].tribeID == TankID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}

	for (int i = 0; i < QueenCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{
				if (board[y][x].tribeID == QueenID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}

	for (int i = 0; i < VesselCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{
				if (board[y][x].tribeID == VesselID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}
}

void Unit_H(int x, int y)
{
	board[y][x].unitName = 'H';
	board[y][x].HP = 50;
	board[y][x].MP = 0;

	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = HydraID;
	board[y][x].unitID = HydraCount;
	board[y][x].life = TRUE;
	board[y][x].team = Zerg;

	HydraCount++;
}

void Unit_Q(int x, int y)
{
	board[y][x].unitName = 'Q';
	board[y][x].HP = 70;
	board[y][x].MP = 150;

	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = QueenID;
	board[y][x].unitID = QueenCount;
	board[y][x].life = TRUE;
	board[y][x].team = Zerg;

	QueenCount++;
}

void Unit_D(int x, int y)
{
	board[y][x].unitName = 'D';
	board[y][x].HP = 60;
	board[y][x].MP = 200;

	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = DefilerID;
	board[y][x].unitID = DefilerCount;
	board[y][x].life = TRUE;
	board[y][x].team = Zerg;

	DefilerCount++;
}

void Unit_M(int x, int y)
{
	board[y][x].unitName = 'M';
	board[y][x].HP = 30;
	board[y][x].MP = 0;

	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = MarineID;
	board[y][x].unitID = MarineCount;
	board[y][x].life = TRUE;
	board[y][x].team = Terran;

	MarineCount++;
}

void Unit_T(int x, int y)
{
	board[y][x].unitName = 'T';
	board[y][x].HP = 120;
	board[y][x].MP = 0;

	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = TankID;
	board[y][x].unitID = TankCount;
	board[y][x].life = TRUE;
	board[y][x].team = Terran;

	TankCount++;
}

void Unit_V(int x, int y)
{
	board[y][x].unitName = 'V';
	board[y][x].HP = 80;
	board[y][x].MP = 140;

	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = VesselID;
	board[y][x].unitID = VesselCount;
	board[y][x].life = TRUE;
	board[y][x].team = Terran;

	VesselCount++;
}
