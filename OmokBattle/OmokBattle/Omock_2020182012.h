#include <stdlib.h>
#include <time.h>

#pragma once
int board_2020182012[19][19];

//Èòµ¹		1
//°ËÀºµ¹	-1
#define BLACK -1
#define WHITE 1

int w = 0;
int b = 0;

void WhiteAttack_2020182012(int* x, int* y)
{
    srand(time(NULL));

    if (w == 0) {
        *x = rand() % 19;
        *y = rand() % 19;
        w++;
        while (board_2020182012[*y][*x] == WHITE || board_2020182012[*y][*x] == BLACK) {
            *x = rand() % 19;
            *y = rand() % 19;
        }
    }
    else {
        (*x)++;

        if (*x >= 19 || board_2020182012[*y][*x] == WHITE || board_2020182012[*y][*x] == BLACK) {
            *x = rand() % 19;
            *y = rand() % 19;

            while (board_2020182012[*y][*x] == WHITE || board_2020182012[*y][*x] == BLACK) {
                *x = rand() % 19;
                *y = rand() % 19;
            }
        }

    }

    board_2020182012[*y][*x] = WHITE;
}
void WhiteDefence_2020182012(int x, int y)
{
    board_2020182012[y][x] = BLACK;

    x++;
    y++;

}
void BlackAttack_2020182012(int* x, int* y){

    if (b == 0) {
        *x = rand() % 19;
        *y = rand() % 19;
        b++;
        while (board_2020182012[*y][*x] == WHITE || board_2020182012[*y][*x] == BLACK) {
            *x = rand() % 19;
            *y = rand() % 19;
        }
    }
    else {
        (*y)++;

        if (*y >= 19 || board_2020182012[*y][*x] == WHITE || board_2020182012[*y][*x] == BLACK) {
            *x = rand() % 19;
            *y = rand() % 19;

            while (board_2020182012[*y][*x] == WHITE || board_2020182012[*y][*x] == BLACK) {
                *x = rand() % 19;
                *y = rand() % 19;
            }
        }

    }

	board_2020182012[*y][*x] = BLACK;
}
void BlackDefence_2020182012(int x, int y)
{
	board_2020182012[y][x] = WHITE;
}