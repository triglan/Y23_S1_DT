#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

//������
#define HydraID 1
#define QueenID 2
#define DefilerID 3
#define MarineID 4 
#define TankID 5 
#define VesselID 6 

//������ ũ��
#define SIDE 40
#define UPDOWN 20

//���� ��
#define Zerg 1
#define Terran 2

//bool ��
#define TRUE 1
#define FALSE 0

//�� ����ü
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

//��
UnitInfo board[UPDOWN][SIDE];

//���� ���� ��
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

//���� �ʱ� ��ġ
void StartBoard();
int Distance(int x1, int y1, int x2, int y2);

void Display();
void Produce(int x, int y, char unit);
void Select(int x, int y);
void SelectAll(int x1, int y1, int x2, int y2);
void Destroy(int x, int y);
void FindTarget(int x1, int y1);
void SortByID();



int main()
{
	int x;
	int y;
	int x1;
	int y1;
	int x2;
	int y2;

	char order;
	char unit;

	StartBoard();

	while (1)
	{
		x = 0;
		y = 0;
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;

		order = 0;
		unit = 0;

		Display();
		printf("����(x,y,unit) : p // ���� ����(x,y) : s // ���� ������ ����(x1,y1,x2,y2) : S // ����(x,y) : d\n����� ��(x,y) : f // ��� ���� ��� : e // ���� ������ : q\nex) (1,2)��ǥ�� ����� ���� : p 1 2 h\n��ɾ �ʿ� �̻��� ���� �� ��� ȭ���� �Ⱥ��� �� �ֽ��ϴ� �� ���, �߰����� ��ɾ �Է��ϴٺ��� �ٽ� ���ƿɴϴ�.\n");
		printf("��ɾ� : ");
		scanf_s(" %c", &order);
		system("cls");


		switch (order)
		{
		case 'p':
			scanf_s("%d %d %c", &x, &y, &unit);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��\n");
				break;
			}
			if (unit == 'h' || unit == 'q' || unit == 'd' || unit == 'm' || unit == 't' || unit == 'v')
			{
				Produce(x, y, unit);
				break;
			}
			else
				printf("�߸��� ��\n");
			break;

		case's':
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��\n");
				break;
			}
			if (board[y][x].life == 0)
			{
				printf("�� ��\n");
				break;
			}
			Select(x, y);
			break;

		case 'S':
			scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (x1 < 0 || x1 >= SIDE || y1 < 0 || y1 >= UPDOWN || x2 < 0 || x2 >= SIDE || y2 < 0 || y2 >= UPDOWN)
			{
				printf("�߸��� ��\n");
				break;
			}
			SelectAll(x1, y1, x2, y2);
			break;

		case 'd':
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��\n");
				break;
			}

			Destroy(x, y);
			break;

		case 'f':
			scanf_s("%d %d", &x, &y);
			if (x < 0 || x >= SIDE || y < 0 || y >= UPDOWN)
			{
				printf("�߸��� ��\n");
				break;
			}

			FindTarget(x, y);
			break;

		case 'e':
			SortByID();
			break;

		case 'q':
			return 0;

		default:
			printf("�߸��� ��\n");
			break;

		}
	}

	return 0;
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

void Produce(int x, int y, char unit)
{
	if (board[y][x].life != 0)
	{
		printf("�̹� ������ ������.\n");
		return;
	}

	if (unit == 'h')
	{
		Unit_H(x, y);
		Select(x, y);
	}
	else if (unit == 'q')
	{
		Unit_Q(x, y);
		Select(x, y);
	}
	else if (unit == 'd')
	{
		Unit_D(x, y);
		Select(x, y);
	}
	else if (unit == 'm')
	{
		Unit_M(x, y);
		Select(x, y);
	}
	else if (unit == 't')
	{
		Unit_T(x, y);
		Select(x, y);
	}
	else if (unit == 'v')
	{
		Unit_V(x, y);
		Select(x, y);
	}
}

void Select(int x, int y)
{
	if (board[y][x].life == 0)
		return;

	printf("name : %c HP : %d MP : %d ��ǥ : (%d,%d) ID : %c%04d",
		board[y][x].name, board[y][x].HP, board[y][x].MP, board[y][x].x, board[y][x].y, board[y][x].name, board[y][x].unitID);
	printf("\n\n");
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
	if (board[y][x].life == 0)
	{
		printf("�� ��\n");
		return;
	}
	printf("(%d,%d) ��ǥ�� ������ �����߽��ϴ�.\n", x, y);

	board[y][x].life = 0;
}

void FindTarget(int x1, int y1)
{
	if (board[y1][x1].life == 0)
	{
		printf("�� ��\n");
		return;
	}

	int min = 10000000;
	int minX = 0;
	int minY = 0;
	for (int y2 = 0; y2 < UPDOWN; y2++)
	{
		for (int x2 = 0; x2 < SIDE; x2++)
		{//���̸鼭 ���� �ƴϸ鼭 �ּҰ����� ������
			if (board[y1][x1].team != board[y2][x2].team && board[y2][x2].life != 0 && Distance(x1, y1, x2, y2) < min)
			{
				min = Distance(x1, y1, x2, y2);
				minX = x2;
				minY = y2;
			}
		}
	}

	Select(minX, minY);
}

void SortByID()
{//D H M Q T V
	for (int i = 0; i < DefilerCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{//�����Ϸ��� �������� �����鼭 ���̵� == ī��Ʈ
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
			{//�����Ϸ��� �������� �����鼭 ���̵� == ī��Ʈ
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
			{//�����Ϸ��� �������� �����鼭 ���̵� == ī��Ʈ
				if (board[y][x].tribeID == MarineID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}
	for (int i = 0; i < QueenCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{//�����Ϸ��� �������� �����鼭 ���̵� == ī��Ʈ
				if (board[y][x].tribeID == QueenID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}
	for (int i = 0; i < TankCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{//�����Ϸ��� �������� �����鼭 ���̵� == ī��Ʈ
				if (board[y][x].tribeID == TankID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}
	for (int i = 0; i < VesselCount; i++)
	{
		for (int y = 0; y < UPDOWN; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{//�����Ϸ��� �������� �����鼭 ���̵� == ī��Ʈ
				if (board[y][x].tribeID == VesselID && board[y][x].unitID == i)
					Select(x, y);
			}
		}
	}


}

int Distance(int x1, int y1, int x2, int y2)
{
	int distance = (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1);
	return distance;
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
