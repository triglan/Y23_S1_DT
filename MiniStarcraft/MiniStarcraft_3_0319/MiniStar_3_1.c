#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

//종족값
#define HydraID 1
#define QueenID 2
#define DefilerID 3
#define MarineID 4 
#define TankID 5 
#define VesselID 6 

//보드판 크기
#define SIDE 40
#define UPDOWN 20

//종족 팀
#define Zerg 1
#define Terran 2

//bool 값
#define TRUE 1
#define FALSE 0

//맵 구조체
typedef struct
{//hp mp x,y unitID
	char name;
	int HP;
	int MP;

	int x;
	int y;

	int tribeID;
	int unitID;
	int team;
	int life;
}UnitInfo;

//맵
UnitInfo board[UPDOWN][SIDE];

//유닛 생성 수
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

int inputX = 0;
int inputY = 0;
int inputX1 = 0;
int inputY1 = 0;
int inputX2 = 0;
int inputY2 = 0;

char inputUnit = 0;

char orderList[30];
int orderCount = 0;

int continueGame = 0;
//유닛 정보
void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);

//유닛 초기 배치
void StartBoard();
int Distance(int x1, int y1, int x2, int y2);

void Display();
void DestroyAll(int x1, int y1, int x2, int y2);
void Order(char command);
void ShowOrderList(char order);
void GetDistance(int x1, int y1, int x2, int y2);
void FindWeakEnemy(int x1, int y1);


int main()
{
	continueGame = 1;
	StartBoard();

	char command = 0;
	while (continueGame)
	{
		Display();
		scanf_s(" %c", &command);
		system("cls");

		Order(command);
	}


	return 0;
}

void StartBoard()
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
	Unit_H(38, 15);
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

void ShowOrderList(char order)
{
	int i = 0;
	while (orderList[i] == 0)
	{
		printf("%c ", orderList[i]);
		if (i % 10 == 9)
			printf("\n");
		i++;
	}
}

void Order(char command)
{


	switch (command)
	{
	case'p':
		scanf_s("%d %d %c", &inputX, &inputY, &inputUnit);

		orderList[orderCount] = 'p';
		orderCount++;
		break;

	case 's':

	case 'S':

	case 'm':

	case 'a':

	case 'e':
		scanf_s("%d %d %d %d", &inputX1, &inputY1, &inputX2, &inputY2);

		GetDistance(inputX1, inputY1, inputX2, inputY2);
		break;
	case'q':
		continueGame = 0;
		break;
	default:
		break;
	}
}

void DestroyAll(int x1, int y1, int x2, int y2)
{//왼쪽 위부터 아래쪽 아래로만 해야 드래그가 됌
	for (int y = y1; y <= y2; y++)
	{
		for (int x = x1; x <= x2; x++)
		{
			board[y][x].life = 0;
		}
	}
}

int Distance(int x1, int y1, int x2, int y2)
{
	int a = x2 - x1;
	int b = y2 - y1;
	int distance = sqrt((a * a) + (b * b));

	return distance;
}

void GetDistance(int x1, int y1, int x2, int y2)
{
	int distance = Distance(x1, y1, x2, y2);
	printf("%d", distance);
}

void FindWeakEnemy(int x1, int y1)
{
	int min = 100000000;
	int minX = 0;
	int minY = 0;

	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{//적이면서 빈땅이 아니면서 최소값보다 작아야 됌
			if (board[y2][x2].team != board[y1][x1].team &&
				board[y2][x2].life != 0 &&
				Distance(x1, y1, x2, y2) < min)
			{
				min = Distance(x1, y1, x2, y2);
				minX = x2;
				minY = y2;
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

	board[y][x].tribeID = HydraID;
	board[y][x].unitID = HydraCount;
	board[y][x].team = Zerg;
	board[y][x].life = 1;

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
	board[y][x].team = Zerg;
	board[y][x].life = 1;

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
	board[y][x].team = Zerg;
	board[y][x].life = 1;

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
	board[y][x].team = Terran;
	board[y][x].life = 1;

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
	board[y][x].team = Terran;
	board[y][x].life = 1;

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
	board[y][x].team = Terran;
	board[y][x].life = 1;

	VesselCount++;
}
