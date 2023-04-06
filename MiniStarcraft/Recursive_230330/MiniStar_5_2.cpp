#include <stdio.h>
#include <windows.h>

//������ ũ��
#define SIDE 40
#define UPDOWN 20


//�� ����ü
typedef struct
{//hp mp x,y unitID
	char name;
	int HP;
	int MP;

	int x;
	int y;

	int unitID;
}UnitInfo;

//����
UnitInfo unitList[UPDOWN * SIDE + 1];
char board[UPDOWN][SIDE];

//���� ���� ��
int unitCount = 0;
int HydraCount = 0;
int QueenCount = 0;
int DefilerCount = 0;
int MarineCount = 0;
int TankCount = 0;
int VesselCount = 0;

//���� ����
void Unit_H(int x, int y);
void Unit_Q(int x, int y);
void Unit_D(int x, int y);
void Unit_M(int x, int y);
void Unit_T(int x, int y);
void Unit_V(int x, int y);

void MakeUL();

void Destroy(int x, int y, int i);

void ShowUL();
void ShowUL_R(int i);

void Select_UL(int x, int y);
void Select_UL_R(int x, int y, int i);

void Destroy_UL(int x, int y);
void Destroy_UL_R(int x, int y, int i);

void DisplayMap_UL();

int main()
{
	int order;
	int x, y;
	MakeUL();
	while (1)
	{
		DisplayMap_UL();
		printf("��ɾ� 1 : ShowUL_R // ��ɾ� 2 : Select_UL_R(x,y) // ��ɾ� 3 : Destroy_UL_R(x,y) : ");
		scanf_s("%d", &order);
		system("cls");

		switch (order)
		{
		case 1:
			ShowUL_R(unitCount);
			break;
		case 2:
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��.\n");
				break;
			}
			Select_UL_R(x, y, unitCount);
			break;
		case 3:
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��.\n");
				break;
			}
			Destroy_UL_R(x, y, unitCount);
			break;
		case 4:
			ShowUL();
			break;
		case 5:
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��.\n");
				break;
			}
			Select_UL(x, y);
			break;
		case 6:
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��.\n");
				break;
			}
			Destroy_UL(x, y);
			break;
		default:
			printf("�߸��� ��.\n");
			break;
		}
	}

}

void ShowUL()
{
	for (int i = unitCount - 1; i >= 0; i--)
	{
		printf("name : %c // HP : %d // MP : %d // ��ǥ : (%d,%d) // ID : %c%04d // ���� �� : %d\n",
			unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID, i);
	}
}

void ShowUL_R(int i)
{
	i--;
	if (i < 0)
		return;

	printf("name : %c // HP : %d // MP : %d // ��ǥ : (%d,%d) // ID : %c%04d // ���� �� : %d\n",
		unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID, i);

	return ShowUL_R(i);
}

void Select_UL(int x, int y)
{
	for (int i = 0; i < unitCount; i++)
	{
		if (unitList[i].x == x && unitList[i].y == y)
		{
			printf("name : %c // HP : %d // MP : %d // ��ǥ : (%d,%d) // ID : %c%04d // ���� �� : %d\n",
				unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID, i);
			return;
		}
	}
	printf("�ش� ��ǥ�� ������ ����\n");
	return;
}

void Select_UL_R(int x, int y, int i)
{
	i--;

	if (i < 0 || i>unitCount)
	{
		printf("�ش� ��ǥ�� ������ ����\n");
		return;
	}

	if (unitList[i].x == x && unitList[i].y == y)
	{
		printf("name : %c // HP : %d // MP : %d // ��ǥ : (%d,%d) // ID : %c%04d // ���� �� : %d\n",
			unitList[i].name, unitList[i].HP, unitList[i].MP, unitList[i].x, unitList[i].y, unitList[i].name, unitList[i].unitID, i);
		return;
	}
	return Select_UL_R(x, y, i);

}

void Destroy_UL(int x, int y)
{
	for (int i = 0; i < unitCount; i++)
	{
		if (unitList[i].x == x && unitList[i].y == y)
		{
			unitCount--;
			Destroy(x, y, i);
			printf("%d %d ��ǥ�� ���� ����\n", x, y);
			return;
		}
	}
	printf("�ش� ��ǥ�� ������ ����\n");
	return;
}

void Destroy_UL_R(int x, int y, int i)
{
	i--;

	if (i < 0 || i>unitCount)
	{
		printf("�ش� ��ǥ�� ������ ����\n");
		return;
	}

	if (unitList[i].x == x && unitList[i].y == y)
	{//
		unitCount--;
		Destroy(x, y, i);
		printf("%d %d ��ǥ�� ���� ����\n", x, y);
		return;
	}
	return Destroy_UL_R(x, y, i);
}

void Destroy(int x, int y, int i)
{
	if (i<0 || i>unitCount)
		return;

	unitList[i] = unitList[i + 1];
	return Destroy(x, y, ++i);
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

	unitList[unitCount++].unitID = HydraCount++;
}

void Unit_Q(int x, int y)
{
	unitList[unitCount].name = 'Q';
	unitList[unitCount].HP = 70;
	unitList[unitCount].MP = 150;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount++].unitID = QueenCount++;
}

void Unit_D(int x, int y)
{
	unitList[unitCount].name = 'D';
	unitList[unitCount].HP = 60;
	unitList[unitCount].MP = 200;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount++].unitID = DefilerCount++;

}

void Unit_M(int x, int y)
{
	unitList[unitCount].name = 'M';
	unitList[unitCount].HP = 30;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount++].unitID = MarineCount++;

}

void Unit_T(int x, int y)
{
	unitList[unitCount].name = 'T';
	unitList[unitCount].HP = 120;
	unitList[unitCount].MP = 0;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount++].unitID = TankCount++;

}

void Unit_V(int x, int y)
{
	unitList[unitCount].name = 'V';
	unitList[unitCount].HP = 80;
	unitList[unitCount].MP = 140;

	unitList[unitCount].x = x;
	unitList[unitCount].y = y;

	unitList[unitCount++].unitID = VesselCount++;
}
