#include <stdio.h>
#include <windows.h>
#include <math.h>

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
	int distance;
}UnitInfo;

typedef struct
{
	char order;
	char unit;

	int x;
	int y;

	int x1;
	int y1;
	int x2;
	int y2;
}UnitOrder;
//맵
UnitInfo board[UPDOWN][SIDE];
UnitOrder OrderL[30];

//유닛 생성 수
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

int orderCount = 0;
//유닛 정보
void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);

//유닛 초기 배치
void StartBoard();

//scanf 조건검사 걸어줘 2~5번
void Order(char command);
void ShowOrderList();
void Display();
void DestroyAll(int x1, int y1, int x2, int y2);
int Distance(int x1, int y1, int x2, int y2);
void GetDistance(int x1, int y1, int x2, int y2);
void FindWeakEnemy(int x1, int y1, int distance);
void SortByDistance(int x1, int y1);


int main()
{
	int x1, y1;
	int x2, y2;
	int distance;
	char command;

	StartBoard();
	while (1)
	{
		Display();
		printf("명령어 : Order : p,m,a,s,S // 1 : ShowOrderList // 2 : DestroyAll(x1,y1,x2,y2) // 3 : GetDistance(x1,y1,x2,y2)\n4 : FindWeakEnemy(x1,y1,distance) // 5 : SortByDistance(x1,y1) : ");
		scanf_s(" %c", &command, 1);
		system("cls");
		switch (command)
		{
		case 'a':
		case 'm':
		case 's':
		case 'S':
		case 'p':
			Order(command);
			break;
		case '1':
			ShowOrderList();
			break;
		case '2':
			scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 < 0 || x1 >= SIDE || y1 < 0 || y1 >= UPDOWN || x2 < 0 || x2 >= SIDE || y2 < 0 || y2 >= UPDOWN)
			{
				printf("잘못된 값.\n");
				break;
			}
			DestroyAll(x1, y1, x2, y2);
			break;

		case '3':
			scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 < 0 || x1 >= SIDE || y1 < 0 || y1 >= UPDOWN || x2 < 0 || x2 >= SIDE || y2 < 0 || y2 >= UPDOWN)
			{
				printf("잘못된 값.\n");
				break;
			}
			GetDistance(x1, y1, x2, y2);
			break;

		case '4':
			scanf_s("%d %d %d", &x1, &y1, &distance);
			if (x1 < 0 || x1 >= SIDE || y1 < 0 || y1 >= UPDOWN || distance < 0)
			{
				printf("잘못된 값.\n");
				break;
			}
			if (board[y1][x1].life == 0)
			{
				printf("해당 위치에 유닛이 없음.\n");
				break;
			}
			FindWeakEnemy(x1, y1, distance);
			break;
		case '5':
			scanf_s("%d %d", &x1, &y1);
			if (x1 < 0 || x1 >= SIDE || y1 < 0 || y1 >= UPDOWN)
			{
				printf("잘못된 값.\n");
				break;
			}
			SortByDistance(x1, y1);
			break;

		case 'q':
			return 0;
		default:
			printf("잘못된 값D\n");
			break;
		}
	}
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

void Order(char command)
{
	int x, y;
	int x1, y1;
	int x2, y2;
	char unit;
	switch (command)
	{
	case 'p':
		scanf_s("%d %d %c", &x, &y, &unit);
		if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
		{
			printf("잘못된 값 p\n");
			return;
		}
		if (orderCount >= 30)
		{
			printf("OrderCount가 30개를 넘음\n");
			return;
		}
		else if (unit == 'h' || unit == 'q' || unit == 'd' || unit == 'm' || unit == 't' || unit == 'v')
		{
			OrderL[orderCount].order = 'p';
			OrderL[orderCount].unit = unit;
			OrderL[orderCount].x = x;
			OrderL[orderCount].y = y;
		}
		else
		{
			printf("잘못된 값 p\n");
			return;
		}
		break;
	case 'm':
	case 'a':
	case 's':
		scanf_s("%d %d", &x, &y);
		if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
		{
			printf("잘못된 값 p\n");
			return;
		}
		if (orderCount >= 30)
		{
			printf("OrderCount가 30개를 넘음\n");
			return;
		}
		OrderL[orderCount].order = command;//TODO : 맞음?
		OrderL[orderCount].x = x;
		OrderL[orderCount].y = y;
		break;
	case 'S':
		scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
		if (x1 < 0 || x1 >= SIDE || y1 < 0 || y1 >= UPDOWN || x2 < 0 || x2 >= SIDE || y2 < 0 || y2 >= UPDOWN)
		{
			printf("잘못된 값 p\n");
			return;
		}
		if (orderCount >= 30)
		{
			printf("OrderCount가 30개를 넘음\n");
			return;
		}
		OrderL[orderCount].order = command;//TODO : 맞음?
		OrderL[orderCount].x1 = x1;
		OrderL[orderCount].y1 = y1;
		OrderL[orderCount].x2 = x2;
		OrderL[orderCount].y2 = y2;
		break;
	default:
		break;
	}

	orderCount++;
}

void ShowOrderList()
{
	for (int i = 0; i < orderCount; i++)
	{
		switch (OrderL[i].order)
		{
		case 'p':
			printf("/ %c %d %d %c /", OrderL[i].order, OrderL[i].x, OrderL[i].y, OrderL[i].unit);
			break;
		case 'a':
		case 'm':
		case 's':
			printf("/ %c %d %d /", OrderL[i].order, OrderL[i].x, OrderL[i].y);
			break;
		case 'S':
			printf("/ %c %d %d %d %d /", OrderL[i].order, OrderL[i].x1, OrderL[i].y1, OrderL[i].x2, OrderL[i].y2);
			break;
		default:
			break;
		}
		if (i % 10 == 9)
			printf("\n");
	}
	printf("\n");

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

void DestroyAll(int x1, int y1, int x2, int y2)
{
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
	int a = abs(y2 - y1);
	int b = abs(x2 - x1);
	if (a > b)
		return a;
	else
		return b;
}

void GetDistance(int x1, int y1, int x2, int y2)
{
	int distance = Distance(x1, y1, x2, y2);
	printf("거리 : %d", distance);
}

void FindWeakEnemy(int x1, int y1, int distance)
{
	UnitInfo Enemy[100];
	int minHP = 100000000000;
	int minCount = 0;
	//거리내에 있으면서 적이면서 빈땅아님
	//HP < 최소값 새로 넣기 HP == 최소값 하나 더 넣기

	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{
			if (board[y2][x2].life != 0 && board[y2][x2].team != board[y1][x1].team
				&& Distance(x1, y1, x2, y2) < distance)
			{
				if (board[y2][x2].HP < minHP)
				{
					minHP = board[y2][x2].HP;
					Enemy[0] = board[y2][x2];
					minCount = 1;
				}
				else if (board[y2][x2].HP == minHP)
				{
					Enemy[minCount] = board[y2][x2];
					minCount++;
				}
			}
		}
	}


	for (int i = 0; i < minCount; i++)
	{
		printf("name : %c // HP : %d // MP %d // ID : %c%04d\n",
			Enemy[i].name, Enemy[i].HP, Enemy[i].MP, Enemy[i].name, Enemy[i].unitID);
	}
}

void SortByDistance(int x1, int y1)
{
	UnitInfo Sort[SIDE * UPDOWN];
	int count = 0;
	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{
			if (board[y2][x2].life != 0)
			{
				Sort[count] = board[y2][x2];
				Sort[count].distance = Distance(x1, y1, x2, y2);
				count++;
			}
		}
	}
	//거리가 가까우면
	//거리가 같으면 이름 먼저 그다음 ID
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (Sort[i].distance < Sort[j].distance)
			{
				UnitInfo temp = Sort[i];
				Sort[i] = Sort[j];
				Sort[j] = temp;
			}
			else if (Sort[i].distance == Sort[j].distance)
			{
				if (Sort[i].name < Sort[j].name)
				{
					UnitInfo temp = Sort[i];
					Sort[i] = Sort[j];
					Sort[j] = temp;
				}
				else if (Sort[i].name == Sort[j].name
					&& Sort[i].unitID < Sort[j].unitID)
				{
					UnitInfo temp = Sort[i];
					Sort[i] = Sort[j];
					Sort[j] = temp;
				}
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		printf("name : %c // HP : %d // MP %d // ID : %c%04d // 거리 : %d\n",
			Sort[i].name, Sort[i].HP, Sort[i].MP, Sort[i].name, Sort[i].unitID, Sort[i].distance);
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
