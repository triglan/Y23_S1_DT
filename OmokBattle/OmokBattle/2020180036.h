#pragma once
#include <stdlib.h>
#include <stdio.h>

int board_2020180036[19][19];


#define BLACK 1
#define WHITE 2
#define SIZE 19
#define PLAYER1 'O'
#define PLAYER2 'X'

void random_AI(int *x, int *y);
int FindBest();
int minimax(int depth, int maximizing);


void WhiteAttack_2020180036(int* x, int* y)
{
	// 직접 구현하신 돌 놓기 로직을 넣어주세요
    int best_move = FindBest();
    int row, col;
    row = best_move / SIZE;
    col = best_move % SIZE;
    *x = row;
    *y = col;
	board_2020180036[*y][*x] = WHITE;
}
void WhiteDefence_2020180036(int x, int y)
{
	// 상대가 놓은 돌의 위치를 전달받아서 저장합니다
	board_2020180036[y][x] = BLACK;
}
void BlackAttack_2020180036(int* x, int* y)
{
	// 직접 구현하신 돌 놓기 로직을 넣어주세요
    int best_move = FindBest();
    int row, col;
    row = best_move / SIZE;
    col = best_move % SIZE;
    *x = row;
    *y = col;
    board_2020180036[*y][*x] = WHITE;

}
void BlackDefence_2020180036(int x, int y)
{
	// 상대가 놓은 돌의 위치를 전달받아서 저장합니다
	board_2020180036[y][x] = WHITE;
}


void random_AI(int *x, int *y)
{
	srand((unsigned int)time(NULL));
	do
	{
		*x = rand() % 19;
		*y = rand() % 19;

	} while (board_2020180036[*y][*x] == BLACK || board_2020180036[*y][*x] == WHITE);

}


int minimax(int depth, int maximizing) {
    if (maximizing) {
        int max_eval = INT_MIN;
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board_2020180036[i][j] == 0) {
                    board_2020180036[i][j] = PLAYER1;
                    int eval = minimax(depth - 1, 0);
                    board_2020180036[i][j] = 0;
                    if (eval > max_eval) {
                        max_eval = eval;
                    }
                }
            }
        }
        return max_eval;
    }
    else {
        int min_eval = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board_2020180036[i][j] == 0) {
                    board_2020180036[i][j] = PLAYER2;
                    int eval = minimax(depth - 1, 1);
                    board_2020180036[i][j] = 0;
                    if (eval < min_eval) {
                        min_eval = eval;
                    }
                }
            }
        }
        return min_eval;
    }
}

// 최적의 수 선택
int FindBest() {
    int best_move;
    int best_eval = INT_MIN;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <SIZE; j++) {
            if (board_2020180036[i][j] == 0) {
                board_2020180036[i][j] = PLAYER1;
                int eval = minimax(3, 0);  // 깊이 설정
                board_2020180036[i][j] = 0;
                if (eval > best_eval) {
                    best_eval = eval;
                    best_move = i * SIZE + j;  // 1차원 인덱스로 변환
                }
            }
        }
    }
    return best_move;
}