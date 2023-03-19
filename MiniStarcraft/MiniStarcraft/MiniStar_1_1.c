#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>

//보드 열행 크기
#define UPDOWN 20
#define SIDE 40

#define TRUE 1
#define FALSE 0

//종족 아이디
#define HydraID 1
#define QueenID 2
#define DefilerID 3
#define MarineID 4
#define TankID 5
#define VesselID 6

//팀
#define ZERG 1
#define TERRAN 2

//유닛 수 초기화
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

typedef struct
{
	char unitName;
	//스텟
	int HP;
	int MP;

	BOOL life;
	//좌표
	int unitX;
	int unitY;
	//ID
	int tribeID;
	int unitID;
	int team;

}UnitInfo;

UnitInfo board[UPDOWN][SIDE];

void Display();
void Produce(int x, int y, char c);
void Select(int x, int y);
void SelectAll(inputX1, inputY1, inputX2, inputY2);

void Destroy(int x, int y);
void FindTarget(int x1, int y1);
void SortByID();

int Distance(int x1, int y1, int x2, int y2);

void ClearBoard();
void FirstBoard();

void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);

void Unit_Clear(int x, int y);

int main()
{
	char selectOrder = 0;
	char selectUnit = 0;

	int inputX1 = 0;
	int inputX2 = 0;
	int inputY1 = 0;
	int inputY2 = 0;

	FirstBoard();
	while (TRUE)
	{
		Display();
		printf("명령어\n p : 생산 // s : 유닛 정보 출력 // S : 모든 유닛 정보 출력 // D : 해당 유닛 삭제\n // f : 가장 가까운 적 유닛 정보 출력  // a : 모든 유닛 ID 출력 : ");
		scanf(" %c", &selectOrder);

		switch (selectOrder)
		{
		case 'p':
			printf("유닛 생산(x,y,Unit) : ");
			scanf("%d %d %c", &inputX1, &inputY1, &selectUnit);
			system("cls");

			Produce(inputX1, inputY1, selectUnit);


			break;
		case 's':
			scanf("%d %d", &inputX1, &inputY1);
			system("cls");

			Select(inputX1, inputY1);


			break;
		case 'S':
			scanf("%d %d %d %d", &inputX1, &inputY1, &inputX2, &inputY2);
			system("cls");

			SelectAll(inputX1, inputY1, inputX2, inputY2);

			break;

		case 'd':
			scanf("%d %d", &inputX1, &inputY1);
			system("cls");

			Destroy(inputX1, inputY1);

			break;

		case 'f':
			printf("(x,y)좌표에서 가장 가까운 유닛 정보 출력\n");
			scanf("%d %d", &inputX1, &inputY1);
			system("cls");

			FindTarget(inputX1, inputY1);

			break;

		case 'a':
			system("cls");
			SortByID();

			break;
		default:
			system("cls");
			printf("잘못된 명령어 입니다. 다시 입력하세요.\n");
			break;
		}
	}
}

void ClearBoard()
{
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{

			Unit_Clear(x, y);
		}
	}
}

void FirstBoard()
{
	ClearBoard();

	Unit_M(0, 0);
	Unit_M(0, 1);
	Unit_M(0, 2);
	Unit_M(1, 3);
	Unit_M(1, 4);
	Unit_M(0, 5);

	Unit_V(1, 2);
	Unit_V(2, 2);

	Unit_T(0, 3);
	Unit_T(0, 4);

	Unit_H(39, 19);
	Unit_H(39, 18);
	Unit_H(37, 17);
	Unit_H(38, 16);
	Unit_H(38, 15);
	Unit_H(39, 14);

	Unit_Q(39, 17);
	Unit_Q(38, 17);

	Unit_D(39, 15);
	Unit_D(39, 16);
}

void Display()
{
	for (int y = 0; y < UPDOWN; y++)
	{
		for (int x = 0; x < SIDE; x++)
		{
			if (board[y][x].life == TRUE)
				printf("%c", board[y][x].unitName);
			else
				printf("+");
		}
		printf("\n");
	}

}


void Produce(int x, int y, char c)	//유닛 생성
{
	//유닛 생성
	//유닛 정보 출력 select
	if (c == 'h' || c == 'H')
	{
		Unit_H(x, y);
		Select(x, y);
	}
	else if (c == 'q' || c == 'Q')
	{
		Unit_Q(x, y);
		Select(x, y);
	}
	else if (c == 'd' || c == 'D')
	{
		Unit_D(x, y);
		Select(x, y);
	}
	else if (c == 'm' || c == 'M')
	{
		Unit_M(x, y);
		Select(x, y);
	}
	else if (c == 't' || c == 'T')
	{
		Unit_T(x, y);
		Select(x, y);
	}
	else if (c == 'v' || c == 'V')
	{
		Unit_V(x, y);
		Select(x, y);
	}


}

void Select(int x, int y)
{
	if (board[y][x].tribeID != 0)//공백이면 출력 안함
	{
		printf("ID : %c%04d // HP : %d // MP : %d // 좌표 : (%d,%d)",
			board[y][x].unitName, board[y][x].unitID, board[y][x].HP, board[y][x].MP, board[y][x].unitX, board[y][x].unitY
		);
		printf("\n\n");
	}
}

void SelectAll(int x1, int y1, int x2, int y2)
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
	//최소값
	int min = 10000000;
	int minUnitIDX[1000] = { 0 };
	int minUnitIDY[1000] = { 0 };
	int minIDCount = 0;
	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{
			if (board[y2][x2].team != board[y1][x1].team && board[y2][x2].tribeID != FALSE && Distance(x1, y1, x2, y2) < min)	//서로 팀이 같지 않고, 공백이 아니고, 기존 최소보다 더 작을  때
			{
				min = Distance(x1, y1, x2, y2);
				for (int i = 0; i < minIDCount; i++)
				{//초기화
					minUnitIDX[i] = 0;
					minUnitIDY[i] = 0;
				}
				minIDCount = 0;
				minUnitIDX[0] = board[y2][x2].unitX;
				minUnitIDY[0] = board[y2][x2].unitY;
				minIDCount++;
			}
			else if (board[y2][x2].team != board[y1][x1].team && board[y2][x2].tribeID != FALSE && Distance(x1, y1, x2, y2) == min)
			{
				minUnitIDX[minIDCount] = board[y2][x2].unitX;
				minUnitIDY[minIDCount] = board[y2][x2].unitY;
				minIDCount++;
			}
		}
	}

	printf("가장 가까운 적 : ");
	for (int i = 0; i < minIDCount; i++)
	{
		Select(minUnitIDX[i], minUnitIDY[i]);
	}
}

void SortByID()
{//D H M Q T V
	//모든 디파일러 출력
	for (int i = 0; i < DefilerCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{
				if (i == board[y][x].unitID && DefilerID == board[y][x].tribeID)//i번째 디파일러면 정보 출력
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
				if (i == board[y][x].unitID && HydraID == board[y][x].tribeID)//i번째 디파일러면 정보 출력
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
				if (i == board[y][x].unitID && MarineID == board[y][x].tribeID)//i번째 디파일러면 정보 출력
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
				if (i == board[y][x].unitID && QueenID == board[y][x].tribeID)//i번째 디파일러면 정보 출력
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
				if (i == board[y][x].unitID && TankID == board[y][x].tribeID)//i번째 디파일러면 정보 출력
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
				if (i == board[y][x].unitID && VesselID == board[y][x].tribeID)//i번째 디파일러면 정보 출력
					Select(x, y);
			}
		}
	}

}

int Distance(int x1, int y1, int x2, int y2)
{
	int unitDistance = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
	return unitDistance;
}



void Unit_H(int x, int y)
{
	board[y][x].unitName = 'H';
	board[y][x].HP = 50;
	board[y][x].MP = 0;

	board[y][x].life = TRUE;
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = HydraID;
	board[y][x].unitID = HydraCount;
	board[y][x].team = ZERG;

	HydraCount++;
}

void Unit_Q(int x, int y)
{
	board[y][x].unitName = 'Q';
	board[y][x].HP = 70;
	board[y][x].MP = 150;

	board[y][x].life = TRUE;
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = QueenID;
	board[y][x].unitID = QueenCount;
	board[y][x].team = ZERG;

	HydraCount++;
}

void Unit_D(int x, int y)
{
	board[y][x].unitName = 'D';
	board[y][x].HP = 60;
	board[y][x].MP = 200;

	board[y][x].life = TRUE;
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = DefilerID;
	board[y][x].unitID = DefilerCount;
	board[y][x].team = ZERG;

	DefilerCount++;
}

void Unit_M(int x, int y)
{
	board[y][x].unitName = 'M';
	board[y][x].HP = 30;
	board[y][x].MP = 0;

	board[y][x].life = TRUE;
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = MarineID;
	board[y][x].unitID = MarineCount;
	board[y][x].team = TERRAN;

	MarineCount++;
}

void Unit_T(int x, int y)
{
	board[y][x].unitName = 'T';
	board[y][x].HP = 120;
	board[y][x].MP = 0;

	board[y][x].life = TRUE;
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = TankID;
	board[y][x].unitID = TankCount;
	board[y][x].team = TERRAN;

	TankCount++;
}

void Unit_V(int x, int y)
{
	board[y][x].unitName = 'V';
	board[y][x].HP = 80;
	board[y][x].MP = 140;

	board[y][x].life = TRUE;
	board[y][x].unitX = x;
	board[y][x].unitY = y;

	board[y][x].tribeID = VesselID;
	board[y][x].unitID = VesselCount;
	board[y][x].team = TERRAN;

	VesselCount++;
}

void Unit_Clear(int x, int y)
{
	board[y][x].unitName = 0;
	board[y][x].HP = 0;
	board[y][x].MP = 0;

	board[y][x].life = FALSE;
	board[y][x].unitX = 0;
	board[y][x].unitY = 0;

	board[y][x].tribeID = FALSE;
	board[y][x].unitID = FALSE;
	board[y][x].team = FALSE;

	HydraCount = 0;
	QueenCount = 0;
	DefilerCount = 0;
	MarineCount = 0;
	TankCount = 0;
	VesselCount = 0;

}