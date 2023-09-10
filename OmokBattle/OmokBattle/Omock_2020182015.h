#pragma once
#include <stdio.h>

#define Board_SIZE 19
#define BLACK -1
#define WHITE 1

int board_2020182015[Board_SIZE][Board_SIZE] = {0, };
int x_2020182015, y_2020182015;
typedef struct Stone_2020182015
{
	int start_x = -1; // 연속된 돌 시작위치
	int start_y = -1;

	int space_x = -1; // 빈 돌 위치
	int space_y = -1;

	int end_x = -1; // 연속된 돌 끝 위치
	int end_y = -1;

	int num; // 연속된 돌 개수
}Stone_2020182015;

bool Black_Stone_Twin(int type)
{
	int count = 0;
	if (type == 0) // 쌍삼 삼사 가로 검사
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
	if (type == 0) // 가로 검사
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
	else if (type == 1) // 세로 검사
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
	else if (type == 2) // 대각 검사
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
bool Stone_Board_Check(int stone, int num) // 가로 세로 대각 검사
{
	Stone_2020182015 Stone_Width[Board_SIZE][Board_SIZE]; // 기로로 연속된 돌 개수를 저장해줄 변수
	int Stone_Line = 0; // Stone_Width에 사용될 변수
	int Stone_count = 0; // Stone_Width에 사용될 변수

	for (int y = 0; y < Board_SIZE; y++)
	{
		int Num_Stone_count = 0; // 연속 개수 체크
		for (int x = 0; x < Board_SIZE + 1; x++) // 1을 추가한 이유는 마지막 위치에 돌이 놓여있을경우 오류 처리때문에
		{
			if (board_2020182015[y][x] == stone)
			{
				Num_Stone_count++;
			}
			else if(Num_Stone_count != 0)
			{
				if (board_2020182015[y][x] == 0 && board_2020182015[y][x + 1] == stone && Stone_Width[Stone_Line][Stone_count].space_x == -1)
				{
					// Stone_Width.space에 값이 없으면 수행, 값이 있으면 수행 안함
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
				printf("시작 위치 %d,%d / 끝 위치 %d,%d / 빈 위치 %d, %d / num : %d\n",
					Stone_Width[i][j].start_x, Stone_Width[i][j].start_y, Stone_Width[i][j].end_x, Stone_Width[i][j].end_y, Stone_Width[i][j].space_x, Stone_Width[i][j].space_y, Stone_Width[i][j].num);
			}*/
		}
	}


	Stone_2020182015 Stone_Height[Board_SIZE][Board_SIZE]; // 세로로 연속된 돌 개수를 저장해줄 변수
	Stone_Line = 0; // Stone_Height에 사용될 변수
	Stone_count = 0; // Stone_Height에 사용될 변수

	for (int x = 0; x < Board_SIZE; x++)
	{
		int Num_Stone_count = 0; // 연속 개수 체크
		for (int y = 0; y < Board_SIZE + 1; y++) // 1을 추가한 이유는 마지막 위치에 돌이 놓여있을경우 오류 처리때문에
		{
			if (board_2020182015[y][x] == stone)
			{
				Num_Stone_count++;
			}
			else if (Num_Stone_count != 0)
			{
				if (board_2020182015[y][x] == 0 && board_2020182015[y][x + 1] == stone && Stone_Height[Stone_Line][Stone_count].space_x == -1)
				{
					// Stone_Height.space에 값이 없으면 수행, 값이 있으면 수행 안함
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

	Stone_2020182015 Srone_Diagonal[Board_SIZE * 2][Board_SIZE * 2]; // 사선으로  연속된 돌 개수를 저장해줄 변수
	Stone_Line = 0; // Srone_Diagonal에 사용될 변수
	Stone_count = 0; // Srone_Diagonal에 사용될 변수

	for (int i = 0; i < Board_SIZE * 2 - 1; i++)
	{ 
		int Num_Stone_count = 0; // 연속 개수 체크
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
void FindStone(int stone1, int stone2) // 무슨 돌이 연속으로 몇개 놓여있는지
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