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
#define UltraID 3
#define MarineID 4
#define TankID 5
#define VultureID 6
#define MaxUnitCount 1000

//보드판 크기
#define SIDE 40	
#define UPDOWN 20
board[UPDOWN][SIDE] = { BLANK };

void PrintUnit(int unitboard);	//위치에 따라 유닛 하나의 각각 위치를 그림.
void Display();		//PrintUnit과 연계하여 현재 유닛의 배치 상홍을 그린다.
void Produce();		//새로운 유닛을 지정된 위치에 생성 이 때 새로운 유닛의 정보는 입력받는다
//void Select();		//주어진 좌표에 위치하고 있는 유닛의 정보를 출력한다.
//void SelectAll();	//주어진 좌표에 위치하고 있는 모든 유닛의 정보를 출력한다.

int inputX, inputY;
char inputC;


int main()
{
	while (TRUE)
	{
		system("cls");
		Display();

		board[1][1] = HydraID;

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

void Produce()
{
	printf("유닛을 생산해 주세요 (x좌표, y좌표, 생산 유닛");
	scanf("%d %d %c", &inputX, &inputY, &inputC);

	switch (inputC)
	{
	case 'H':
	{
		Hydra[]

		printf("히드라리스크를 생산하셨습니다.\n");

	}

	}
}

//struct UnitInform
//{
//	//이름, 위치
//	char unitName[30];
//	int unitX;
//	int unitY;
//	//스텟
//	int MaxHP;
//	int MaxMP;
//	int Speed;
//	//ID
//	int UnitID;
//	int UnitOwnID;
//};

