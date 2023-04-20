#include <stdio.h>
#include <windows.h>
//보드판 크기
#define SIDE 40
#define UPDOWN 20

#define TERRAN 1
#define ZERG 2

//맵 구조체
typedef struct
{//hp mp x,y unitID
	char name;
	int HP;
	int MP;

	int x;
	int y;

	int unitID;
	int team;
}UnitInfo;

//유닛
UnitInfo unitList[UPDOWN * SIDE + 1];
int board[UPDOWN][SIDE];
//유닛 생성 수
int unitCount = 0;

int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

//유닛 정보
void Unit(char unit, int hp, int mp, int x, int y, int i);
void MakeUL();
void printlist(int i);
int scanteam(int x, int y);
int Distance(int x, int y, int distance);

void DisplayMap_UL();
void Show_UL_R(int i);
void Produce_UL_R(char unit, int x, int y, int hp, int mp, int i);
void SelectAll_UL_R(int x1, int y1, int x2, int y2, int i);
void Destroy_UL_R(int x, int y, int i);
void FindWeakEnemy(int x, int y, int distance, int team, int i);

int main()
{
	MakeUL();
	char order;
	char unit;
	int x, y, hp, mp, distance;
	int x1, y1, x2, y2;
	while (1)
	{
		DisplayMap_UL();
		printf("명령어 Show : 1 // produce : 2 (unit,x,y,hp,mp) // SelectAll : 3 (x1,y1,x2,y2)\nDestroy : 4 (x,y) // FindWeakEnemy : 5(x,y,distance) : ");
		scanf_s(" %c", &order, 1);
		system("cls");
		switch (order)
		{
		case '1':
			Show_UL_R(unitCount);
			break;
		case '2':
			scanf_s(" %c %d %d %d %d", &unit, 1, &x, &y, &hp, &mp);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN || hp < 0 || mp < 0)
			{
				printf("잘못된 값\n");
				break;
			}
			if (board[y][x] != '+')
			{
				printf("해당 위치에 이미 유닛이 있음\n");
				break;
			}
			if (unit == 'h' || unit == 'q' || unit == 'd' || unit == 'm' || unit == 't' || unit == 'v')
			{
				Produce_UL_R(unit, x, y, hp, mp, 0);
				break;
			}

			printf("잘못된 값\n");
			break;
		case '3':
			scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 < 0 || x1 >= SIDE || y1 < 0 || y1 >= UPDOWN ||
				x2 < 0 || x2 >= SIDE || y2 < 0 || y2 >= UPDOWN)
			{
				printf("잘못된 값\n");
				break;
			}
			SelectAll_UL_R(x1, y1, x2, y2, unitCount);
			break;

		case '4':
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("잘못된 값\n");
				break;
			}
			Destroy_UL_R(x, y, unitCount);
			break;

		case '5':
			scanf_s("%d %d %d", &x, &y, &distance);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN || distance < 0)
			{
				printf("잘못된 값\n");
				break;
			}
			FindWeakEnemy(x, y, distance, scanteam(x, y), unitCount);
			break;
		default:
			break;
		}
	}
}

void DisplayMap_UL()
{
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{
			board[y][x] = '+';
		}
	}
	for (int i = 0; i < unitCount; i++)
	{
		if (unitList[i].name != 0)
			board[unitList[i].y][unitList[i].x] = unitList[i].name;
	}
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{
			printf("%c", board[y][x]);
		}
		printf("\n");
	}
}
void Show_UL_R(int i)
{
	i--;
	if (i < 0)
	{
		return;
	}
	if (unitList[i].name != 0)
		printlist(i);
	else
		printf("EMPTY\n");
	return Show_UL_R(i);
}
void Produce_UL_R(char unit, int x, int y, int hp, int mp, int i)
{
	if (unitList[i].name == 0)
	{
		Unit(unit, x, y, hp, mp, i);
		printlist(i);
		return;
	}

	return Produce_UL_R(unit, x, y, hp, mp, ++i);
}
void SelectAll_UL_R(int x1, int y1, int x2, int y2, int i)
{
	i--;
	if (i < 0)
		return;
	if (x1 <= unitList[i].x && unitList[i].x <= x2 &&
		y1 <= unitList[i].y && unitList[i].y <= y2 &&
		unitList[i].name != 0)
	{
		printlist(i);
	}
	return SelectAll_UL_R(x1, y1, x2, y2, i);
}
void Destroy_UL_R(int x, int y, int i)
{
	i--;
	if (board[y][x] == 0 || i < 0)
	{
		printf("해당 위치에 유닛이 없음\n");
		return;
	}

	if (unitList[i].x == x && unitList[i].y == y && unitList[i].name != 0)
	{
		unitList[i].HP = 0;
		unitList[i].MP = 0;
		unitList[i].name = 0;
		unitList[i].team = 0;
		unitList[i].unitID = 0;
		unitList[i].x = 0;
		unitList[i].y = 0;
		printf("(%d,%d) 좌표의 유닛 제거\n", x, y);
		return;
	}
	return Destroy_UL_R(x, y, i);
}

int minHP = 10000000;
int minCount = 0;
int enemy[100];

void FindWeakEnemy(int x, int y, int distance, int team, int i)
{
	i--;

	if (i < 0)
	{
		for (int i = 0; i < minCount; i++)
		{
			printlist(enemy[i]);
		}
		minHP = 10000000;
		minCount = 0;
		for (int i = 0; i < 10; i++)
		{
			enemy[i] = 0;
		}
		return;
	}

	//거리가 더 작으면서 적이면서 빈땅이 아니면서
	//HP가 더 적은
	if (Distance(x, y, i) <= distance && unitList[i].team != team && unitList[i].name != 0)
	{
		if (unitList[i].HP < minHP)
		{
			minHP = unitList[i].HP;
			minCount = 0;
			enemy[minCount++] = i;
		}
		else if (unitList[i].HP == minHP)
			enemy[minCount++] = i;
	}
	return FindWeakEnemy(x, y, distance, team, i);
}
int Distance(int x, int y, int i)
{
	int a = abs(x - unitList[i].x);
	int b = abs(y - unitList[i].y);
	if (a > b)
		return a;
	else
		return b;
}
int scanteam(int x, int y)
{
	for (int i = 0; i < unitCount; i++)
	{
		if (x == unitList[i].x && y == unitList[i].y)
			return unitList[i].team;
	}
	return 0;
}


void printlist(int i)
{
	printf("name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // ID : %c%03d // UC : %d\n",
		unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID, i);
}

void MakeUL()
{
	Unit('m', 0, 0, 25, 0, unitCount);
	Unit('m', 0, 1, 20, 0, unitCount);
	Unit('m', 0, 2, 30, 0, unitCount);
	Unit('m', 1, 3, 15, 0, unitCount);
	Unit('m', 1, 4, 30, 0, unitCount);
	Unit('m', 0, 5, 27, 0, unitCount);

	Unit('t', 0, 3, 120, 0, unitCount);
	Unit('t', 0, 4, 50, 0, unitCount);

	Unit('v', 1, 2, 80, 0, unitCount);
	Unit('v', 2, 2, 75, 0, unitCount);

	Unit('h', 39, 19, 37, 0, unitCount);
	Unit('h', 39, 18, 47, 0, unitCount);
	Unit('h', 37, 17, 30, 0, unitCount);
	Unit('h', 38, 16, 20, 0, unitCount);
	Unit('h', 38, 15, 45, 0, unitCount);
	Unit('h', 39, 14, 50, 0, unitCount);

	Unit('q', 39, 17, 35, 0, unitCount);
	Unit('q', 38, 17, 70, 0, unitCount);

	Unit('d', 39, 16, 15, 0, unitCount);
	Unit('d', 39, 15, 40, 0, unitCount);

}
void Unit(char unit, int x, int y, int hp, int mp, int i)
{
	if (unit == 'h') {
		unitList[i].name = 'H';
		unitList[i].unitID = HydraCount++;
		unitList[i].team = ZERG;
	}
	else if (unit == 'q')
	{
		unitList[i].name = 'Q';
		unitList[i].unitID = QueenCount++;
		unitList[i].team = ZERG;
	}
	else if (unit == 'd')
	{
		unitList[i].name = 'D';
		unitList[i].unitID = DefilerCount++;
		unitList[i].team = ZERG;
	}
	else if (unit == 'm')
	{
		unitList[i].name = 'M';
		unitList[i].unitID = MarineCount++;
		unitList[i].team = TERRAN;
	}
	else if (unit == 't')
	{
		unitList[i].name = 'T';
		unitList[i].unitID = TankCount++;
		unitList[i].team = TERRAN;
	}
	else if (unit == 'v')
	{
		unitList[i].name = 'V';
		unitList[i].unitID = VesselCount++;
		unitList[i].team = TERRAN;
	}
	else
		return;
	unitList[i].HP = hp;
	unitList[i].MP = mp;

	unitList[i].x = x;
	unitList[i].y = y;
	if (i >= unitCount)
		unitCount++;
}