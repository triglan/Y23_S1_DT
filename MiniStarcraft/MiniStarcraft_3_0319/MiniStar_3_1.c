#define _CRT_SECURE_NO_WARNINGS
//scanf 검사시 이상한 수 들어가면 ERROR
//ShowOrderList()에 30개 이상 들어가면 교환 혹은 금지

#include <stdio.h>
#include <Windows.h>
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
	int distance;
}UnitInfo;

typedef struct
{
	char order;
	char unit;

	int x;
	int x1;
	int x2;

	int y;
	int y1;
	int y2;
}OrderStruct;

//맵
UnitInfo board[UPDOWN][SIDE];
//명령어 리스트
OrderStruct orderL[30];
int orderCount = 0;


//유닛 생성 수
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;


int continueGame = 0;

int inputX = 0;
int inputY = 0;
int inputX1 = 0;
int inputY1 = 0;
int inputX2 = 0;
int inputY2 = 0;
char inputUnit = 0;

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
void ShowOrderList();
void GetDistance(int x1, int y1, int x2, int y2);
void FindWeakEnemy(int x1, int y1, int surroundDistance);
void SortByDistance(int x1, int y1);

//s 2 3 

int main()
{
	continueGame = 1;
	StartBoard();

	char command = 0;
	
	int x;
	int y;

	int x1, y1;
	int x2, y2;

	int surroundDistance;
	while (continueGame)
	{

		//if잘못된값 == true print 잘못된값
		Display();
		printf("명령어 (order(m,a,s,S,p), f, r, d, D) : ");
		scanf_s(" %c", &command);
		system("cls");
		switch (command)
		{
		case 'm':
		case 'a':
		case 's':
		case 'S':
		case 'p':
			Order(command);
			break;

		case 'D':
			scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 < 0 || x1>SIDE || y1 < 0 || y1 > UPDOWN || x2 < 0 || x2>SIDE || y2 < 0 || y2 > UPDOWN)
			{
				printf("잘못된 입력 값입니다.\n");
				break;
			}

			DestroyAll(x1, y1, x2, y2);
			break;
		case 'd':
			scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 < 0 || x1>SIDE || y1 < 0 || y1 > UPDOWN || x2 < 0 || x2>SIDE || y2 < 0 || y2 > UPDOWN)
			{
				printf("잘못된 입력 값입니다.\n");
				break;
			}

			GetDistance(x1, y1, x2, y2);
			break;

		case 'f':
			scanf_s("%d %d %d", &x, &y, &surroundDistance);
			if (x < 0 || x>SIDE || y<0 || y>UPDOWN || surroundDistance<0)
			{
				printf("잘못된 입력 값입니다.\n");
				break;
			}

			FindWeakEnemy(x, y, surroundDistance);
			break;

		case 'r':
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x>SIDE || y < 0 || y > UPDOWN)
			{
				printf("잘못된 입력 값입니다.\n");
				break;
			}

			SortByDistance(x, y);
			break;

		case 'g':
			ShowOrderList();

			break;
		default:
			printf("잘못된 입력 값입니다.D\n");
			break;
		}
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

void ShowOrderList()
{
	int i = 0;
	while (orderL[i].order != 0 && i < 30)
	{
		switch (orderL[i].order)
		{
		case 'p':
			printf("/ %c %d %d %c /", orderL[i].order, orderL[i].x, orderL[i].y, orderL[i].unit);
			break;
		case 's':
			printf("/ %c %d %d /", orderL[i].order, orderL[i].x, orderL[i].y);
			break;
		case 'S':
			printf("/ %c %d %d %d %d /", orderL[i].order, orderL[i].x1, orderL[i].y1, orderL[i].x2, orderL[i].y2);
			break;
		case 'a':
			printf("/ %c %d %d /", orderL[i].order, orderL[i].x, orderL[i].y);
			break;
		case 'm':
			printf("/ %c %d %d /", orderL[i].order, orderL[i].x, orderL[i].y);
			break;

		default:
			break;
		}
		if (i % 10 == 9)
			printf("\n");
		i++;
	}
	printf("\n");

}

void Order(char command)
{


	inputX = 0;
	inputY = 0;
	inputX1 = 0;
	inputY1 = 0;
	inputX2 = 0;
	inputY2 = 0;
	inputUnit = 0;

	switch (command)
	{
	case'p':
		scanf_s("%d %d %c", &inputX, &inputY, &inputUnit, 1);
		if (inputX < 0 || inputX>SIDE || inputY < 0 || inputY > UPDOWN)
		{
			printf("잘못된 입력 값입니다.\n");
			break;
		}
		if (inputUnit == 'h' || inputUnit == 'q' || inputUnit == 'd' || inputUnit == 'm' || inputUnit == 't' || inputUnit == 'v')
		{
			printf("잘못된 입력 값입니다.\n");
			break;
		}
		if (orderCount >= 30)
		{
			printf("Order가 30개를 넘었습니다.\n");//TODO : 왜 프린트가 안되지?
			return;
		}
		orderL[orderCount].order = 'p';

		orderL[orderCount].x = inputX;
		orderL[orderCount].y = inputY;
		orderL[orderCount].unit = inputUnit;

		break;   

	case 's':
		scanf_s("%d %d", &inputX, &inputY);
		if (inputX < 0 || inputX>SIDE || inputY < 0 || inputY > UPDOWN)
		{
			printf("잘못된 입력 값입니다.\n");
			break;
		}
		if (orderCount >= 30)
		{
			printf("Order가 30개를 넘었습니다.\n");//TODO : 왜 프린트가 안되지?
			return;
		}

		orderL[orderCount].order = 's';

		orderL[orderCount].x = inputX;
		orderL[orderCount].y = inputY;

		break;

	case 'S':
		scanf_s("%d %d %d %d", &inputX1, &inputY1, &inputX2, &inputY2);
		if (inputX1 < 0 || inputX1>SIDE || inputY1 < 0 || inputY1 > UPDOWN || inputX2 < 0 || inputX2>SIDE || inputY2 < 0 || inputY2 > UPDOWN)
		{
			printf("잘못된 입력 값입니다.\n");
			break;
		}
		if (orderCount >= 30)
		{
			printf("Order가 30개를 넘었습니다.\n");//TODO : 왜 프린트가 안되지?
			return;
		}
		orderL[orderCount].order = 'S';

		orderL[orderCount].x1 = inputX1;
		orderL[orderCount].y1 = inputY1;
		orderL[orderCount].x2 = inputX2;
		orderL[orderCount].y2 = inputY2;

		break;

	case 'm':
		scanf_s("%d %d", &inputX, &inputY);
		if (inputX < 0 || inputX>SIDE || inputY < 0 || inputY > UPDOWN)
		{
			printf("잘못된 입력 값입니다.\n");
			break;
		}
		if (orderCount >= 30)
		{
			printf("Order가 30개를 넘었습니다.\n");//TODO : 왜 프린트가 안되지?
			return;
		}
		orderL[orderCount].order = 'm';

		orderL[orderCount].x = inputX;
		orderL[orderCount].y = inputY;

		break;

	case 'a':
		scanf_s("%d %d", &inputX, &inputY);
		if (inputX < 0 || inputX>SIDE || inputY < 0 || inputY > UPDOWN)
		{
			printf("잘못된 입력 값입니다.\n");
			break;
		}
		if (orderCount >= 30)
		{
			printf("Order가 30개를 넘었습니다.\n");//TODO : 왜 프린트가 안되지?
			return;
		}
		orderL[orderCount].order = 'a';

		orderL[orderCount].x = inputX;
		orderL[orderCount].y = inputY;

		break;
	case 'e':
		scanf_s("%d %d %d %d", &inputX1, &inputY1, &inputX2, &inputY2);
		if (inputX1 < 0 || inputX1>SIDE || inputY1 < 0 || inputY1 > UPDOWN || inputX2 < 0 || inputX2>SIDE || inputY2 < 0 || inputY2 > UPDOWN)
		{
			printf("잘못된 입력 값입니다.\n");
			break;
		}
		if (orderCount >= 30)
		{
			printf("Order가 30개를 넘었습니다.\n");//TODO : 왜 프린트가 안되지?
			return;
		}
		orderL[orderCount].order = 'e';

		orderL[orderCount].x1 = inputX1;
		orderL[orderCount].y1 = inputY1;
		orderL[orderCount].x2 = inputX2;
		orderL[orderCount].y2 = inputY2;

		GetDistance(inputX1, inputY1, inputX2, inputY2);

		break;

	case'q':

		continueGame = 0;
		break;

	default:
		break;
	}

	orderCount++;
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
	int a = abs(x2 - x1);
	int b = abs(y2 - y1);
	int distance = 0;
	if (a > b)
		distance = a;
	else
		distance = b;

	return distance;
}

void GetDistance(int x1, int y1, int x2, int y2)
{
	int distance = Distance(x1, y1, x2, y2);
	printf("%d\n", distance);
}

void FindWeakEnemy(int x1, int y1, int surroundDistance)
{
	int minHP = 100000000;
	UnitInfo Enemy[100];

	int minCount = 0;

	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{//적이면서 빈땅이 아니면서 거리내에 있으면서 체력이 적어야됌
			if (board[y2][x2].team != board[y1][x1].team &&
				board[y2][x2].life != 0 &&
				Distance(x1, y1, x2, y2) < surroundDistance)
			{
				if (board[y2][x2].HP < minHP)
				{
					for (int i = 0; i < minCount; i++)
					{
						Enemy[i].x = 0;
						Enemy[i].y = 0;
					}
					minHP = board[y2][x2].HP;
					Enemy[0] = board[y2][x2];
					Enemy[0].distance = Distance(x1, y1, x2, y2);
					minCount = 1;
				}
				else if (board[y2][x2].HP == minHP)
				{
					Enemy[minCount] = board[y2][x2];
					Enemy[minCount].distance = Distance(x1, y1, x2, y2);
					minCount++;
				}
			}
		}
	}

	if (minCount != 0)
	{	
		for (int i = 0; i < minCount; i++)
		{
			printf("name : %c HP : %d MP : %d 좌표 : (%d,%d) ID : %c%04d 거리 : %d\n",
				Enemy[i].name, Enemy[i].HP, Enemy[i].MP,
				Enemy[i].x, Enemy[i].y, Enemy[i].name, Enemy[i].unitID, Enemy[i].distance);
		}
	}
	else
		printf("주어진 범위 내에 적이 없음");
		
}


void SortByDistance(int x1, int y1)
{
	UnitInfo sortUnit[UPDOWN * SIDE] = { 0 };
 	int unitCount = 0;
	//가까우면서 거리가 같으면 ID순으로 출력
	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{
			if (board[y2][x2].life != 0 && board[y2][x2].x != x1 && board[y2][x2].y != y1)//유닛이면 거리 저장
			{
				sortUnit[unitCount] = board[y2][x2];
				sortUnit[unitCount].distance = Distance(x1, y1, x2, y2);
				unitCount++;
			}
		}
	}

	//거리 Sort
	for (int i = 0; i < unitCount; i++)
	{
		for (int j = 0; j < unitCount; j++)
		{
			if (sortUnit[i].distance < sortUnit[j].distance)
			{
				UnitInfo temp = sortUnit[i];
				sortUnit[i] = sortUnit[j];
				sortUnit[j] = temp;
			}
			else if (sortUnit[i].distance == sortUnit[j].distance)
			{//거리가 같으면 종족이름 먼저 비교 같으면 ID 비교
				if (sortUnit[i].name < sortUnit[j].name)
				{
					UnitInfo temp = sortUnit[i];
					sortUnit[i] = sortUnit[j];
					sortUnit[j] = temp;
				}
				else if (sortUnit[i].name == sortUnit[j].name
					&& sortUnit[i].unitID < sortUnit[j].unitID)
				{
					UnitInfo temp = sortUnit[i];
					sortUnit[i] = sortUnit[j];
					sortUnit[j] = temp;
				}
			}
		}
	}

	for (int i = 0; i < unitCount; i++)
	{
		printf("name : %c HP : %d MP : %d 좌표 : (%d,%d) ID : %c%04d 거리 : %d\n",
			sortUnit[i].name, sortUnit[i].HP, sortUnit[i].MP,
			sortUnit[i].x, sortUnit[i].y, sortUnit[i].name, sortUnit[i].unitID, sortUnit[i].distance);
		
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
