#include <stdio.h>
#include <windows.h>

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
}UnitInfo;

//맵
char board[UPDOWN][SIDE];
//유닛
UnitInfo unitList[UPDOWN * SIDE + 1];


//유닛 생성 수
int unitCount = 0;
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

//유닛 정보
void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);

//유닛 초기 배치
void MakeUL();
void ShowUL();

void ShowUL_R(int i);
void Select_UL_R(int x, int y, int i);
void Destroy_UL_R(int x, int y, int i);
void DisplayMap_UL();

void Destroy(int i);

int main()
{
	int x, y;


	MakeUL();
	while (1)
	{
		int order;
		DisplayMap_UL();
		printf("명령어 // 1 : ShowUL // 2 : Select_UL_R (x,y) // 3 : Destroy_UL_R (x,y) ");
		scanf_s("%d", &order);
		system("cls");
		switch (order)
		{
		case 1:
			ShowUL();
			break;
		case 2:
			scanf_s("%d %d", &x, &y);
			Select_UL_R(x, y, unitCount);
			break;
		case 3:
			scanf_s("%d %d", &x, &y);
			Destroy_UL_R(x, y, unitCount);
			break;
		default:
			break;
		}

	}
}


void ShowUL()
{
	for (int i = 0; i < unitCount; i++)
	{
		printf("name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // unitID : %c%04d\n"
		,unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID);
	}
}

void ShowUL_R(int i)
{
	--i;
	if (i < 0)
	{
		return;
	}
	printf("name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // unitID : %c%04d // unitCount : %d\n"
	,unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID, i);
	
	return ShowUL_R(i);
}

void Select_UL_R(int x, int y, int i)
{
	--i;
	if (i < 0)
	{
		printf("해당 유닛이 존재하지 않습니다.\n");
		return;
	}
	
	if (x == unitList[i].x && y == unitList[i].y)
	{
		printf("name : %c // HP : %d // MP : %d // 좌표 : (%d,%d) // unitID : %c%04d // unitCount : %d\n"
			, unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID, i);
	}
	else
		return Select_UL_R(x, y, i);
}

void Destroy_UL_R(int x, int y, int i)
{
	--i;
	if (i < 0)
	{
		printf("해당 위치에 유닛이 존재하지 않습니다.\n");
		return;
	}

	if (x == unitList[i].x && y == unitList[i].y)
	{
		unitCount--;
		Destroy(i);
		printf("%d %d 좌표의 유닛 제거\n", x, y);
		return;
	}
	else
		return Destroy_UL_R(x, y, i);
}

void Destroy(int i)
{
	if (i < 0 || i > unitCount)
	{
		return;
	}

	unitList[i] = unitList[i + 1];
	return Destroy(++i);
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

void MakeUL()
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

void Unit_H(int x, int y)
{
	unitList[unitCount].name = 'H';
	unitList[unitCount].HP = 50;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].tribeID = HydraID;
	unitList[unitCount].unitID = HydraCount++;
	unitList[unitCount++].team = Zerg;

}

void Unit_Q(int x, int y)
{
	unitList[unitCount].name = 'Q';
	unitList[unitCount].HP = 70;
	unitList[unitCount].MP = 150;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].tribeID = QueenID;
	unitList[unitCount].unitID = QueenCount++;
	unitList[unitCount++].team = Zerg;

}

void Unit_D(int x, int y)
{
	unitList[unitCount].name = 'D';
	unitList[unitCount].HP = 60;
	unitList[unitCount].MP = 200;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].tribeID = DefilerID;
	unitList[unitCount].unitID = DefilerCount++;
	unitList[unitCount++].team = Zerg;

}

void Unit_M(int x, int y)
{
	unitList[unitCount].name = 'M';
	unitList[unitCount].HP = 30;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].tribeID = MarineID;
	unitList[unitCount].unitID = MarineCount++;
	unitList[unitCount++].team = Terran;

}

void Unit_T(int x, int y)
{
	unitList[unitCount].name = 'T';
	unitList[unitCount].HP = 120;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].tribeID = TankID;
	unitList[unitCount].unitID = TankCount++;
	unitList[unitCount++].team = Terran;

}

void Unit_V(int x, int y)
{
	unitList[unitCount].name = 'V';
	unitList[unitCount].HP = 80;
	unitList[unitCount].MP = 140;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount].tribeID = VesselID;
	unitList[unitCount].unitID = VesselCount++;
	unitList[unitCount++].team = Terran;

}
