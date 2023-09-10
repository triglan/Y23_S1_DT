#pragma once
#include <stdio.h>

#define Board_SIZE 19
#define BLACK -1
#define WHITE 1

int board_2020182015[Board_SIZE][Board_SIZE] = {0, };
int x_2020182015, y_2020182015;
typedef struct Stone_2020182015
{
	int start_x = -1; // ���ӵ� �� ������ġ
	int start_y = -1;

	int space_x = -1; // �� �� ��ġ
	int space_y = -1;

	int end_x = -1; // ���ӵ� �� �� ��ġ
	int end_y = -1;

	int num; // ���ӵ� �� ����
}Stone_2020182015;

bool Black_Stone_Twin(int type)
{
	int count = 0;
	if (type == 0) // �ֻ� ��� ���� �˻�
	{
		if (board_2020182015[y_2020182015][x_2020182015 + 1] == BLACK && board_2020182015[y_2020182015][x_2020182015 - 1] == BLACK)
		{
			return true;
		}
		for (int i = 1; i <= 3; i++)
		{
			if (board_2020182015[y_2020182015][x_2020182015 + i] == BLACK)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		if (count >= 2)
		{
			return true;
		}

		count = 0;
		for (int i = 1; i <= 3; i++)
		{
			if (board_2020182015[y_2020182015][x_2020182015 - i] == BLACK)
			{
				count++;
			}
			else
			{
				break;
			}
		}
		if (count >= 2)
		{
			return true;
		}
	}
	return false;
}
bool Stone_check(int type, Stone_2020182015 Stone)
{
	if (type == 0) // ���� �˻�
	{
		if (Stone.space_x != -1 && Stone.num >= 4)
		{
			x_2020182015 = Stone.space_x;
			y_2020182015 = Stone.space_y;
			return true;
		}
		else if ((Stone.start_x - 1) >= 0 && board_2020182015[Stone.start_y][Stone.start_x - 1] == 0)
		{
			x_2020182015 = Stone.start_x - 1;
			y_2020182015 = Stone.start_y;
			return true;
		}
		else if (Stone.end_x + 1 < Board_SIZE && board_2020182015[Stone.end_y][Stone.end_x + 1] == 0)
		{
			x_2020182015 = Stone.end_x + 1;
			y_2020182015 = Stone.end_y;
			return true;
		}
		return false;
	}
	else if (type == 1) // ���� �˻�
	{
		if (Stone.space_y != -1 && Stone.num >= 4)
		{
			x_2020182015 = Stone.space_x;
			y_2020182015 = Stone.space_y;
			return true;
		}
		else if ((Stone.start_y - 1) >= 0 && board_2020182015[Stone.start_y - 1][Stone.start_x] == 0)
		{
			x_2020182015 = Stone.start_x;
			y_2020182015 = Stone.start_y - 1;
			return true;
		}
		else if (Stone.end_y + 1 < Board_SIZE && board_2020182015[Stone.end_y + 1][Stone.end_x] == 0)
		{
			x_2020182015 = Stone.end_x;
			y_2020182015 = Stone.end_y + 1;
			return true;
		}
		return false;
	}
	else if (type == 2) // �밢 �˻�
	{
		if (Stone.space_y != -1 && Stone.num >= 4)
		{
			x_2020182015 = Stone.space_x;
			y_2020182015 = Stone.space_y;
			return true;
		}
		else if ((Stone.start_y - 1) >= 0 && board_2020182015[Stone.start_y - 1][Stone.start_x + 1] == 0)
		{
			x_2020182015 = Stone.start_x + 1;
			y_2020182015 = Stone.start_y - 1;
			return true;
		}
		else if (Stone.end_y + 1 < Board_SIZE && board_2020182015[Stone.end_y + 1][Stone.end_x - 1] == 0)
		{
			x_2020182015 = Stone.end_x - 1;
			y_2020182015 = Stone.end_y + 1;
			return true;
		}
		return false;
	}
}
bool Stone_Board_Check(int stone, int num) // ���� ���� �밢 �˻�
{
	Stone_2020182015 Stone_Width[Board_SIZE][Board_SIZE]; // ��η� ���ӵ� �� ������ �������� ����
	int Stone_Line = 0; // Stone_Width�� ���� ����
	int Stone_count = 0; // Stone_Width�� ���� ����

	for (int y = 0; y < Board_SIZE; y++)
	{
		int Num_Stone_count = 0; // ���� ���� üũ
		for (int x = 0; x < Board_SIZE + 1; x++) // 1�� �߰��� ������ ������ ��ġ�� ���� ����������� ���� ó��������
		{
			if (board_2020182015[y][x] == stone)
			{
				Num_Stone_count++;
			}
			else if(Num_Stone_count != 0)
			{
				if (board_2020182015[y][x] == 0 && board_2020182015[y][x + 1] == stone && Stone_Width[Stone_Line][Stone_count].space_x == -1)
				{
					// Stone_Width.space�� ���� ������ ����, ���� ������ ���� ����
					Stone_Width[Stone_Line][Stone_count].space_x = x;
					Stone_Width[Stone_Line][Stone_count].space_y = y;
					Num_Stone_count++;
					continue;
				}
				Stone_Width[Stone_Line][Stone_count].num = Num_Stone_count;
				Stone_Width[Stone_Line][Stone_count].end_x = x - 1;
				Stone_Width[Stone_Line][Stone_count].end_y = y;
				Stone_Width[Stone_Line][Stone_count].start_x = x - Num_Stone_count;
				Stone_Width[Stone_Line][Stone_count].start_y = y;
				if (Stone_Width[Stone_Line][Stone_count].space_x != -1)
				{
					x = Stone_Width[Stone_Line][Stone_count].space_x;
					y = Stone_Width[Stone_Line][Stone_count].space_y;
				}
				

				Stone_count++;
				Num_Stone_count = 0;
			}
			
		}
		Stone_count = 0;
		Stone_Line++;
	}
	for (int i = 0; i < Board_SIZE; i++)
	{
		for (int j = 0; j < Board_SIZE; j++)
		{
			if (Stone_Width[i][j].num == num)
			{
				if (Stone_check(0, Stone_Width[i][j]))
				{
					return true;
				}
			}
			/*if (Stone_Width[i][j].start_x != -1)
			{
				printf("���� ��ġ %d,%d / �� ��ġ %d,%d / �� ��ġ %d, %d / num : %d\n",
					Stone_Width[i][j].start_x, Stone_Width[i][j].start_y, Stone_Width[i][j].end_x, Stone_Width[i][j].end_y, Stone_Width[i][j].space_x, Stone_Width[i][j].space_y, Stone_Width[i][j].num);
			}*/
		}
	}


	Stone_2020182015 Stone_Height[Board_SIZE][Board_SIZE]; // ���η� ���ӵ� �� ������ �������� ����
	Stone_Line = 0; // Stone_Height�� ���� ����
	Stone_count = 0; // Stone_Height�� ���� ����

	for (int x = 0; x < Board_SIZE; x++)
	{
		int Num_Stone_count = 0; // ���� ���� üũ
		for (int y = 0; y < Board_SIZE + 1; y++) // 1�� �߰��� ������ ������ ��ġ�� ���� ����������� ���� ó��������
		{
			if (board_2020182015[y][x] == stone)
			{
				Num_Stone_count++;
			}
			else if (Num_Stone_count != 0)
			{
				if (board_2020182015[y][x] == 0 && board_2020182015[y][x + 1] == stone && Stone_Height[Stone_Line][Stone_count].space_x == -1)
				{
					// Stone_Height.space�� ���� ������ ����, ���� ������ ���� ����
					Stone_Height[Stone_Line][Stone_count].space_x = x;
					Stone_Height[Stone_Line][Stone_count].space_y = y;
					Num_Stone_count++;
					continue;
				}
				Stone_Height[Stone_Line][Stone_count].num = Num_Stone_count;
				Stone_Height[Stone_Line][Stone_count].end_x = x;
				Stone_Height[Stone_Line][Stone_count].end_y = y - 1;
				Stone_Height[Stone_Line][Stone_count].start_x = x;
				Stone_Height[Stone_Line][Stone_count].start_y = y - Num_Stone_count;
				if (Stone_Height[Stone_Line][Stone_count].space_y != -1)
				{
					x = Stone_Height[Stone_Line][Stone_count].space_x;
					y = Stone_Height[Stone_Line][Stone_count].space_y;
				}


				Stone_count++;
				Num_Stone_count = 0;
			}

		}
		Stone_count = 0;
		Stone_Line++;
	}
	for (int i = 0; i < Board_SIZE; i++)
	{
		for (int j = 0; j < Board_SIZE; j++)
		{
			if (Stone_Height[i][j].num == num)
			{
				if (Stone_check(1, Stone_Height[i][j]))
				{
					return true;
				}
			}
		}
	}

	Stone_2020182015 Srone_Diagonal[Board_SIZE * 2][Board_SIZE * 2]; // �缱����  ���ӵ� �� ������ �������� ����
	Stone_Line = 0; // Srone_Diagonal�� ���� ����
	Stone_count = 0; // Srone_Diagonal�� ���� ����

	for (int i = 0; i < Board_SIZE * 2 - 1; i++)
	{ 
		int Num_Stone_count = 0; // ���� ���� üũ
		for (int j = 0; j < (Board_SIZE * 2 - 1) / 2; j++)
		{
			int t = i - j;
			if (t >= 0 && t < Board_SIZE)
			{
				if (board_2020182015[j][t] == stone)
				{
					Num_Stone_count++;
				}
				else if (Num_Stone_count != 0)
				{
					Srone_Diagonal[Stone_Line][Stone_count].num = Num_Stone_count;
					Srone_Diagonal[Stone_Line][Stone_count].end_x = t + 1;
					Srone_Diagonal[Stone_Line][Stone_count].end_y = j - 1;
					Srone_Diagonal[Stone_Line][Stone_count].start_x = t + Num_Stone_count;
					Srone_Diagonal[Stone_Line][Stone_count].start_y = j - Num_Stone_count;
					if (Srone_Diagonal[Stone_Line][Stone_count].space_y != -1)
					{
						j = Srone_Diagonal[Stone_Line][Stone_count].space_x;
						i = Srone_Diagonal[Stone_Line][Stone_count].space_y;
					}
					Stone_count++;
					Num_Stone_count = 0;
				}
			}

		}
	}
	for (int i = 0; i < Board_SIZE; i++)
	{
		for (int j = 0; j < Board_SIZE; j++)
		{
			if (Srone_Diagonal[i][j].num == num)
			{
				if (Stone_check(2, Srone_Diagonal[i][j]))
				{
					return true;
				}
			}
		}
	}
	return false;
}
void FindStone(int stone1, int stone2) // ���� ���� �������� � �����ִ���
{
	if (Stone_Board_Check(stone2, 5)) return;
	if (Stone_Board_Check(stone1, 5)) return;
	else if (Stone_Board_Check(stone2, 5)) return;
	else if (Stone_Board_Check(stone1, 4)) return;
	else if (Stone_Board_Check(stone2, 4)) return;
	else if (Stone_Board_Check(stone1, 3)) return;
	else if (Stone_Board_Check(stone2, 3)) return;
	else if (Stone_Board_Check(stone1, 2)) return;
	else if (Stone_Board_Check(stone1, 1)) return;
	else if (Stone_Board_Check(stone2, 2)) return;
	else if (Stone_Board_Check(stone2, 1)) return;
	else
	{
		x_2020182015 = Board_SIZE / 2;
		y_2020182015 = Board_SIZE / 2;
	}
}

void BlackAttack_2020182015(int* x, int* y)
{
	FindStone(BLACK, WHITE);
	*x = x_2020182015;
	*y = y_2020182015;
	board_2020182015[*y][*x] = BLACK;
}
void  BlackDefence_2020182015(int x, int y)
{
	board_2020182015[y][x] = WHITE;
}

void WhiteAttack_2020182015(int* x, int* y)
{
	FindStone(WHITE, BLACK);
	*x = x_2020182015;
	*y = y_2020182015;
	board_2020182015[*y][*x] = WHITE;
	
}

void WhiteDefence_2020182015(int x, int y)
{
	board_2020182015[y][x] = BLACK;
}