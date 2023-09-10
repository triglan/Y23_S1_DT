#pragma once
#include <stdbool.h>
#include<stdlib.h>

int board_2021180004[19][19];
bool turn = true;

//검은돌	-1
//흰돌 1
#define BLACK -1
#define WHITE 1

int X, Y;
int peach = 0;

void WhiteAttack_2021180004(int* x, int* y)
{
	*x = peach;
		*y = 0;
	if (board_2021180004[0][peach] != 0) {
		++peach;
	}

	board_2021180004[0][peach] = -1;
	++peach;

	board_2021180004[*y][*x] = WHITE;
}
void WhiteDefence_2021180004(int x, int y)
{
	// 상대가 놓은 돌의 위치를 전달받아서 저장합니다
	board_2021180004[y][x] = BLACK;
}
void BlackAttack_2021180004(int* x, int* y)
{
	*x = peach;
	*y = 0;

	if (board_2021180004[0][peach] != 0) {
		++peach;
	}

	board_2021180004[0][peach] = 1;
	++peach;

	board_2021180004[*y][*x] = BLACK;
}
void BlackDefence_2021180004(int x, int y)
{
	// 상대가 놓은 돌의 위치를 전달받아서 저장합니다
	board_2021180004[y][x] = WHITE;
}