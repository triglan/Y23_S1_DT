#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

//보드판 크기
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


void PrintUnit(int unitboard);	//위치에 따라 유닛 하나의 각각 위치를 그림.
void Display();		//PrintUnit과 연계하여 현재 유닛의 배치 상홍을 그린다.
void Produce();		//새로운 유닛을 지정된 위치에 생성 이 때 새로운 유닛의 정보는 입력받는다
void Select();		//주어진 좌표에 위치하고 있는 유닛의 정보를 출력한다.
void SelectAll();	//주어진 좌표에 위치하고 있는 모든 유닛의 정보를 출력한다.

struct UnitInform;	//유닛 정보 구조체
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
	printf("유닛을 생산해 주세요 (x좌표, y좌표, 생산 유닛");
	scanf("%d %d %c", &inputX, &inputY, &inputC);

	switch (inputC)
	{
	case 'H':
	{
		printf("히드라리스크를 생산하셨습니다.\n");
		NewHydra[HydraCount] = (int*)malloc(sizeof(int));	//새 히드라 만들기
		HydraCount++;										//히드라 카운트+1
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
	//이름, 위치
	char unitName[30];
	int unitX;
	int unitY;
	//스텟
	int MaxHP;
	int MaxMP;
	int Speed;
	//ID
	int UnitID;
	int UnitOwnID;
};


//tempword