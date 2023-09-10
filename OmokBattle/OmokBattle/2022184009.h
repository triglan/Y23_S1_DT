#pragma once

#include<stdio.h>
int board_2022184009[19][19];
int Blackpriorities_2022184009[19][19]{};
int Whitepriorities_2022184009[19][19]{};

//흰돌		1
//검은돌	-1
#define BLACK -1
#define WHITE 1

void Bstd_giving_priority_BLACK_2022184009(int* x, int* y);
void Bstd_giving_priority_WHITE_2022184009(int* x, int* y);
void ToBlockWhite3Line_2022184009(int* x, int* y);
void Make3BlackLine_2022184009(int* x, int* y);
void Make4BlackLine_2022184009(int* x, int* y);
void priority_check_BLACK_2022184009(int* x, int* y);
void priority_check_WHITE_2022184009(int* x, int* y);
void TranPri_2022184009(int* x, int* y);
void WhiteMidBlock_2022184009(int* x, int* y);
void White33Block_2022184009(int* x, int* y);
void BlackRealDefence_2022184009(int* x, int* y);
void BlackCanWin_2022184009(int* x, int* y);
void NewCheck_2022184009();
void Check33_2022184009();

//=================백
void Wstd_giving_priority_BLACK_2022184009(int* x, int* y);
void Wstd_giving_priority_WHITE_2022184009(int* x, int* y);
void ToBlockBlack3Line_2022184009(int* x, int* y);
void Make3WhiteLine_2022184009(int* x, int* y);
void Make4WhiteLine_2022184009(int* x, int* y);
void BlackMidBlock_2022184009(int* x, int* y);
void White33Atack_2022184009(int* x, int* y);
void WhiteRealDefence_2022184009(int* x, int* y);
void WhiteCanWin_2022184009(int* x, int* y);


//================
void BlackAttack_2022184009(int* x, int* y)
{
    Bstd_giving_priority_BLACK_2022184009(x, y);
    Bstd_giving_priority_WHITE_2022184009(x, y);
    ToBlockWhite3Line_2022184009(x, y);        //막아야 할 곳 가중치 주기
    Make3BlackLine_2022184009(x, y);
    Make4BlackLine_2022184009(x, y);
    White33Block_2022184009(x, y);
    WhiteMidBlock_2022184009(x, y);
    TranPri_2022184009(x, y);      //돌이 있는 곳에 가중치 10000
    Check33_2022184009();
    priority_check_BLACK_2022184009(x, y);      //가중치 높은 곳에 돌 놓기
    BlackRealDefence_2022184009(x, y);
    BlackCanWin_2022184009(x, y);        //무조건 이기는 곳에 돌 놓기
	board_2022184009[*y][*x] = BLACK;
    for (int i = 0; i < 19; ++i)
        for (int j = 0; j < 19; ++j)
            Blackpriorities_2022184009[i][j] = 0;
}

void BlackDefence_2022184009(int x, int y)
{
	board_2022184009[y][x] = WHITE;
}

void WhiteAttack_2022184009(int* x, int* y)
{
    Wstd_giving_priority_BLACK_2022184009(x, y);
    Wstd_giving_priority_WHITE_2022184009(x, y);
    ToBlockBlack3Line_2022184009(x, y);        //막아야 할 곳 가중치 주기
    Make3WhiteLine_2022184009(x, y);
    Make4WhiteLine_2022184009(x, y);
    White33Atack_2022184009(x, y);
    BlackMidBlock_2022184009(x, y);
    TranPri_2022184009(x, y);      //돌이 있는 곳에 가중치 10000
    priority_check_WHITE_2022184009(x, y);      //가중치 높은 곳에 돌 놓기
    WhiteRealDefence_2022184009(x, y);
    WhiteCanWin_2022184009(x, y);        //무조건 이기는 곳에 돌 놓기
    board_2022184009[*y][*x] = WHITE;
    for (int i = 0; i < 19; ++i)
        for (int j = 0; j < 19; ++j)
            Whitepriorities_2022184009[i][j] = 0;

}
void WhiteDefence_2022184009(int x, int y)
{
	board_2022184009[y][x] = BLACK;
}

void Bstd_giving_priority_BLACK_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK) {
                if(i - 1 >= 0 && j - 1 >= 0)
                    ++Blackpriorities_2022184009[i - 1][j - 1];
                if (i - 1 >= 0) {
                    ++Blackpriorities_2022184009[i - 1][j];
                    if(j + 1 <= 18)
                        ++Blackpriorities_2022184009[i - 1][j + 1];
                }

                if(j - 1 >= 0)
                    ++Blackpriorities_2022184009[i][j - 1];
                if(j + 1 <= 18)
                    ++Blackpriorities_2022184009[i][j + 1];

                if (i + 1 <= 18 && j - 1 >= 0)
                    ++Blackpriorities_2022184009[i + 1][j - 1];

                if (i + 1 <= 18) {
                    ++Blackpriorities_2022184009[i + 1][j];
                    if (j + 1 <= 18)
                         ++Blackpriorities_2022184009[i + 1][j + 1];
                }
            }
        }
    }
}
void Bstd_giving_priority_WHITE_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE) {
                if (i - 1 >= 0 && j - 1 >= 0)
                    --Blackpriorities_2022184009[i - 1][j - 1];

                if (i - 1 >= 0) {
                    --Blackpriorities_2022184009[i - 1][j];
                    if (j + 1 <= 18)
                        --Blackpriorities_2022184009[i - 1][j + 1];
                }

                if (j - 1 >= 0)
                    --Blackpriorities_2022184009[i][j - 1];
                if (j + 1 <= 18)
                    --Blackpriorities_2022184009[i][j + 1];

                if (i + 1 <= 18 && j - 1 >= 0)
                    --Blackpriorities_2022184009[i + 1][j - 1];

                if (i + 1 <= 18) {
                    --Blackpriorities_2022184009[i + 1][j];
                    if (j + 1 <= 18)
                        --Blackpriorities_2022184009[i + 1][j + 1];
                }
            }
        }
    }
}
void priority_check_BLACK_2022184009(int* x, int* y)
{
    int max = -9999;
    int max_x = 0, max_y = 0;
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            if (Blackpriorities_2022184009[i][j] >= 9000) continue;
            if (board_2022184009[i][j] == BLACK || board_2022184009[i][j] == WHITE) continue;

            if (Blackpriorities_2022184009[i][j] > max) {
                max = Blackpriorities_2022184009[i][j];
                max_x = j;
                max_y = i;
            }
        }
    }
    *x = max_x;
    *y = max_y;
    
    if (max == 0) {
        *x = 9;
        *y = 9;
    }
}
void priority_check_WHITE_2022184009(int* x, int* y)
{
    int Wcnt = 0;
    int max = -9999;
    int max_x = 0, max_y = 0;
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            if (board_2022184009[i][j] == WHITE) ++Wcnt;
            if (Whitepriorities_2022184009[i][j] >= 9000) continue;
            if (board_2022184009[i][j] == BLACK || board_2022184009[i][j] == WHITE) continue;

            if (Whitepriorities_2022184009[i][j] > max) {
                max = Whitepriorities_2022184009[i][j];
                max_x = j;
                max_y = i;
            }
        }
    }
    *x = max_x;
    *y = max_y;
    if (Wcnt == 0) {
        for (int i = 0; i < 19; ++i) {
            for (int j = 0; j < 19; ++j) {
                if (board_2022184009[i][j] == BLACK) {
                    if (i == 0 && j == 0) {
                        *x = 1;
                        *y = 1;
                    }
                    else if (i == 0 && j == 18) {
                        *x = 17;
                        *y = 1;
                    }
                    else if (i == 18 && j == 0) {
                        *x = 1;
                        *y = 17;
                    }
                    else if (i == 18 && j == 18) {
                        *x = 17;
                        *y = 17;
                    }
                    else if(i == 0) {
                        *x = j;
                        *y = i + 1;
                    }
                    else if (i == 18) {
                        *x = j;
                        *y = i - 1;
                    }
                    else if (j == 0) {
                        *x = j + 1;
                        *y = i;
                    }
                    else if (j == 18) {
                        *x = j - 1;
                        *y = i;
                    }
                    else {
                        *x = j - 1;
                        *y = i - 1;
                    }
                }
            }
        }
    }

}
void Make3BlackLine_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == 0 ) {
                if (j - 1 >= 0) {
                    Blackpriorities_2022184009[i][j - 1] += 10;
                    if (board_2022184009[i][j - 1] == BLACK || board_2022184009[i][j - 1] == WHITE)
                        Blackpriorities_2022184009[i][j - 1] = 10000;
                }
                if (j + 2 <= 18) {
                    Blackpriorities_2022184009[i][j + 2] += 10;
                    if (board_2022184009[i][j + 2] == BLACK || board_2022184009[i][j + 2] == WHITE)
                        Blackpriorities_2022184009[i][j + 2] = 10000;
                }
            }
        }
    }

    // 세로 방향 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == 0) {
                if (i - 1 >= 0) {
                    Blackpriorities_2022184009[i - 1][j] += 10;
                    if (board_2022184009[i - 1][j] == BLACK || board_2022184009[i - 1][j] == WHITE)
                        Blackpriorities_2022184009[i - 1][j] = 10000;
                }

                if (i + 2 <= 18) {
                    Blackpriorities_2022184009[i + 2][j] += 10;
                    if (board_2022184009[i + 2][j] == BLACK || board_2022184009[i + 2][j] == WHITE)
                        Blackpriorities_2022184009[i + 2][j] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == 0) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Blackpriorities_2022184009[i - 1][j - 1] += 10;
                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j - 1] = 10000;
                }

                if (i + 2 <= 18 && j + 2 <= 18) {
                    Blackpriorities_2022184009[i + 2][j + 2] += 10;
                    if (board_2022184009[i + 2][j + 2] == BLACK || board_2022184009[i + 2][j + 2] == WHITE)
                        Blackpriorities_2022184009[i + 2][j + 2] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 4; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == 0) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Blackpriorities_2022184009[i - 1][j + 1] += 10;
                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j + 1] = 10000;
                }

                if (i + 2 <= 18 && j - 2 <= 18) {
                    Blackpriorities_2022184009[i + 2][j - 2] += 10;
                    if (board_2022184009[i + 2][j - 2] == BLACK || board_2022184009[i + 2][j - 2] == WHITE)
                        Blackpriorities_2022184009[i + 2][j - 2] = 10000;
                }
            }
        }
    }
}
void Make4BlackLine_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == 0 && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK && board_2022184009[i][j + 4] == 0 && (board_2022184009[i][j + 5] == 0 || board_2022184009[i][j - 1] == 0)) {
                if (j - 1 >= 0) {
                    Blackpriorities_2022184009[i][j] += 70;
                   
                }
                if (j + 4 <= 18) {
                    Blackpriorities_2022184009[i][j + 3] += 70;
                }
            }
        }
    }

    // 세로 방향 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == 0 && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == 0 && (board_2022184009[i + 5][j] == 0 || board_2022184009[i - 1][j] == 0)) {
                if (i - 1 >= 0) {
                    Blackpriorities_2022184009[i][j] += 70;
                }

                if (i + 4 <= 18) {
                    Blackpriorities_2022184009[i + 3][j] += 70;
                }
            }

        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == 0) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Blackpriorities_2022184009[i - 1][j - 1] += 70;
                   
                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j - 1] = 10000;
                }

                if (i + 4 <= 18 && j + 4 <= 18) {
                    Blackpriorities_2022184009[i + 3][j + 3] += 70;
                   
                    if (board_2022184009[i + 3][j + 3] == BLACK || board_2022184009[i + 3][j + 3] == WHITE)
                        Blackpriorities_2022184009[i + 3][j + 3] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 4; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == 0) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Blackpriorities_2022184009[i - 1][j + 1] += 70;
                   
                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j + 1] = 10000;
                }

                if (i + 3 <= 18 && j - 3 <= 18) {
                    Blackpriorities_2022184009[i + 3][j - 3] += 70;
                   
                    if (board_2022184009[i + 3][j - 3] == BLACK || board_2022184009[i + 3][j - 3] == WHITE)
                        Blackpriorities_2022184009[i + 3][j - 3] = 10000;
                }
            }
        }
    }
}
void ToBlockWhite3Line_2022184009(int* x, int* y)
{
    //가로 막기
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE ) {
                if (j - 1 >= 0) {
                    
                     Blackpriorities_2022184009[i][j - 1] += 70;
                 
                    if (board_2022184009[i][j - 1] == BLACK || board_2022184009[i][j - 1] == WHITE)
                        Blackpriorities_2022184009[i][j - 1] = 10000;
                }
                if (j + 3 <= 18) {
                    Blackpriorities_2022184009[i][j + 3] += 70;
                   
                    if (board_2022184009[i][j + 3] == BLACK || board_2022184009[i][j + 3] == WHITE)
                        Blackpriorities_2022184009[i][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i][j - 1] == BLACK && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == 0) {
                if (j + 3 <= 18) {
                    Blackpriorities_2022184009[i][j + 3] -= 30;
                    if (j + 4 <= 18 && board_2022184009[i][j + 4] == WHITE)
                        Blackpriorities_2022184009[i][j + 3] += 300;

                    if (board_2022184009[i][j + 3] == BLACK || board_2022184009[i][j + 3] == WHITE)
                        Blackpriorities_2022184009[i][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == BLACK) {
                if (j - 1 >= 0) {
                    if(j - 2 >= 0 && board_2022184009[i][j - 2] == WHITE)
                         Blackpriorities_2022184009[i][j - 1] -= 30;
                    if (j - 2 >= 0 && board_2022184009[i][j - 2] == WHITE)
                        Blackpriorities_2022184009[i][j - 1] += 300;

                    if (board_2022184009[i][j - 1] == BLACK || board_2022184009[i][j - 1] == WHITE)
                        Blackpriorities_2022184009[i][j - 1] = 10000;
                }
            }
            else if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == 0 &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE) {
                Blackpriorities_2022184009[i][j + 1] += 320;
            }
            else if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == 0 && board_2022184009[i][j + 3] == WHITE) {
                Blackpriorities_2022184009[i][j + 2] += 320;
            }
        }
    }
    // 세로 방향 체크
    for (int i = 1; i < 16; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == 0) {
                if (i - 1 >= 0) {
                    Blackpriorities_2022184009[i - 1][j] += 70;
                  
                    if (board_2022184009[i - 1][j] == BLACK || board_2022184009[i - 1][j] == WHITE)
                        Blackpriorities_2022184009[i - 1][j] = 10000;
                }

                if (i + 3 <= 18) {
                    Blackpriorities_2022184009[i + 3][j] += 70;
                 
                    if (board_2022184009[i + 3][j] == BLACK || board_2022184009[i][j] == WHITE)
                        Blackpriorities_2022184009[i + 3][j] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j] == BLACK && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == 0) {
                if (i + 3 <= 18) {
                    Blackpriorities_2022184009[i + 3][j] -= 30;
                    if(i + 4 <= 18 && board_2022184009[i + 4][j] == WHITE)
                        Blackpriorities_2022184009[i + 3][j] += 300;

                    if (board_2022184009[i + 3][j] == BLACK || board_2022184009[i + 3][j] == WHITE)
                        Blackpriorities_2022184009[i + 3][j] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == BLACK) {
                if (i - 1 >= 0) {
                    Blackpriorities_2022184009[i - 1][j] -= 30;
                    if (i - 2 >= 0 && board_2022184009[i - 2][j] == WHITE)
                        Blackpriorities_2022184009[i - 1][j] += 300;

                    if (board_2022184009[i - 1][j] == BLACK || board_2022184009[i - 1][j] == WHITE)
                        Blackpriorities_2022184009[i - 1][j] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == 0 &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE) {
                Blackpriorities_2022184009[i + 1][j] += 320;
            }
            else if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == 0 && board_2022184009[i + 3][j] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 320;
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == 0) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Blackpriorities_2022184009[i - 1][j - 1] += 70;
                 
                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j - 1] = 10000;
                }

                if (i + 3 <= 18 && j + 3 <= 18) {
                    Blackpriorities_2022184009[i + 3][j + 3] += 70;
                  
                    if (board_2022184009[i + 3][j + 3] == BLACK || board_2022184009[i + 3][j + 3] == WHITE)
                        Blackpriorities_2022184009[i + 3][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j - 1] == BLACK && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == 0) {
                if (i + 3 <= 18 && j + 3 <= 18) {
                    Blackpriorities_2022184009[i + 3][j + 3] -= 30;
                    if(i + 4 <= 18 && j + 4 <= 18 && board_2022184009[i + 4][j + 4] == WHITE)
                        Blackpriorities_2022184009[i + 3][j + 3] += 300;

                    if (board_2022184009[i + 3][j + 3] == BLACK || board_2022184009[i + 3][j + 3] == WHITE)
                        Blackpriorities_2022184009[i + 3][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == BLACK) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Blackpriorities_2022184009[i - 1][j - 1] -= 30;
                    if(i - 2 >= 0 && j - 2 >= 0 && board_2022184009[i - 2][j - 2] == WHITE)
                        Blackpriorities_2022184009[i - 1][j - 1] += 300;

                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j - 1] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 4; j < 18; j++) {
            if (board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == 0) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Blackpriorities_2022184009[i - 1][j + 1] += 70;
               
                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j + 1] = 10000;
                }
                if (i + 4 <= 18 && j - 4 <= 18) {
                    Blackpriorities_2022184009[i + 3][j - 3] += 70;
              
                    if (board_2022184009[i + 3][j - 3] == BLACK || board_2022184009[i + 3][j - 3] == WHITE)
                        Blackpriorities_2022184009[i + 3][j - 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j + 1] == BLACK && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == 0) {
                if (i + 4 <= 18 && j - 4 <= 18) {
                    Blackpriorities_2022184009[i + 3][j - 3] -= 30;
                    if(i + 4 <= 18 && j - 4 >= 0 && board_2022184009[i + 4][j - 4] == WHITE)
                        Blackpriorities_2022184009[i + 3][j - 3] += 300;

                    if (board_2022184009[i + 3][j - 3] == BLACK || board_2022184009[i + 3][j - 3] == WHITE)
                        Blackpriorities_2022184009[i + 3][j - 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == BLACK) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Blackpriorities_2022184009[i - 1][j + 1] -= 30;
                    if(i - 2 >= 0 && j + 2 <= 18)
                        Blackpriorities_2022184009[i - 1][j + 1] += 300;

                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Blackpriorities_2022184009[i - 1][j + 1] = 10000;
                }
            }
        }
    }
}
void BlackRealDefence_2022184009(int* x, int* y)
{
    //가로 가운데 무조건 막기
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE && board_2022184009[i][j + 2] == 0 &&
                board_2022184009[i][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                *x = j + 2;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == 0 && board_2022184009[i][j + 2] == WHITE &&
                board_2022184009[i][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                *x = j + 1;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE && board_2022184009[i][j + 2] == WHITE &&
                board_2022184009[i][j + 3] == 0 && board_2022184009[i][j + 4] == WHITE) {
                *x = j + 3;
                *y = i;
                return;
            }
        }
    }
    
    //세로 가운데 무조건 막기
    for (int i = 0; i < 15; i++) {
        for (int j = 1; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == 0 && board_2022184009[i + 2][j] == WHITE &&
                board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                *x = j;
                *y = i + 1;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE && board_2022184009[i + 2][j] == 0 &&
                board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                *x = j;
                *y = i + 2;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE && board_2022184009[i + 2][j] == WHITE &&
                board_2022184009[i + 3][j] == 0 && board_2022184009[i + 4][j] == WHITE) {
                *x = j;
                *y = i + 3;
                return;
            }
        }
    }

    //대각선 오른쪽 아래로 가는 가운데 무조건 막기
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == WHITE && 
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == WHITE && board_2022184009[i + 5][j + 5] == 0) {
                *x = j + 5;
                *y = i + 5;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == 0 &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == WHITE) {
                *x = j + 1;
                *y = i + 1;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == 0 && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == WHITE) {
                *x = j + 2;
                *y = i + 2;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == 0 && board_2022184009[i + 4][j + 4] == WHITE) {
                *x = j + 3;
                *y = i + 3;
                return;
            }
            else if (board_2022184009[i][j] == 0 && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == BLACK) {
                *x = j;
                *y = i;
                return;
            }
        }
    }
    //대각선 왼쪽 아래로가는 가운데...
    for (int i = 0; i < 14; i++) {
        for (int j = 4; j < 18; j++) {
            if (board_2022184009[i][j] == 0 && board_2022184009[i + 1][j - 1] == WHITE && board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == WHITE &&
                board_2022184009[i + 4][j - 4] == WHITE && board_2022184009[i + 5][j - 5] == BLACK) {
                *x = j;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == WHITE && board_2022184009[i + 2][j - 2] == WHITE &&
                board_2022184009[i + 3][j - 3] == WHITE && board_2022184009[i + 4][j - 4] == WHITE && board_2022184009[i + 5][j - 5] == 0) {
                *x = j - 5;
                *y = i + 5;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == 0 && board_2022184009[i + 2][j - 2] == WHITE &&
                board_2022184009[i + 3][j - 3] == WHITE && board_2022184009[i + 4][j - 4] == WHITE) {
                *x = j - 1;
                *y = i + 1;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE && board_2022184009[i + 2][j - 2] == WHITE &&
                board_2022184009[i + 3][j - 3] == 0 && board_2022184009[i + 4][j - 4] == WHITE) {
                *x = j - 3;
                *y = i + 3;
                return;
            }
        }
    }


    //가로 무조건 막기
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE && board_2022184009[i][j + 4] != 0) {
                *x = j - 1;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j - 1] != 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE && board_2022184009[i][j + 4] == 0) {
                *x = j + 4;
                *y = i;
                return;
            }
        }
    }
    

    // 세로 방향 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] != 0) {
                *x = j;
                *y = i - 1;
                return;
            }
            else if (board_2022184009[i - 1][j] != 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == 0) {
                *x = j;
                *y = i + 4;
                return;
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] != 0) {
                *x = j - 1;
                *y = i - 1;
                return;
            }
            else if (board_2022184009[i - 1][j - 1] != 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == 0) {
                *x = j + 4;
                *y = i + 4;
                return;
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 4; j < 17; j++) {
            if (board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == 0 && board_2022184009[i + 4][j - 4] == BLACK) {
                *x = j + 1;
                *y = i - 1;
                return;
            }
            else if (board_2022184009[i - 1][j + 1] == BLACK && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == WHITE && board_2022184009[i + 4][j - 4] == 0) {
                *x = j - 4;
                *y = i + 4;
                return;
            }
        }
    }
}
void WhiteMidBlock_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == 0 &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE ) {
                Blackpriorities_2022184009[i][j + 1] += 300;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == 0 && board_2022184009[i][j + 3] == WHITE) {
                Blackpriorities_2022184009[i][j + 2] += 300;
            }
        }
    }


    // 세로 방향 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == 0 &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE) {
                Blackpriorities_2022184009[i + 1][j] += 300;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == 0 && board_2022184009[i + 3][j] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 300;
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == 0 &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE) {
                Blackpriorities_2022184009[i + 1][j + 1] += 300;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == 0 && board_2022184009[i + 3][j + 3] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 300;
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 4; j < 18; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == 0 &&
                board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == WHITE) {
                Blackpriorities_2022184009[i - 1][j + 1] += 300;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == 0 && board_2022184009[i + 3][j - 3] == WHITE) {
                Blackpriorities_2022184009[i + 2][j - 2] += 300;
            }
        }
    }
}
void BlackCanWin_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK &&
                board_2022184009[i][j + 4] == 0) {
                *x = j + 4;
                *y = i;
                return;
            }
            else if (j - 1 >= 0 && board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK) {
                *x = j - 1;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == 0 &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK &&
                board_2022184009[i][j + 4] == BLACK) {
                *x = j + 1;
                *y = i;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == 0 && board_2022184009[i][j + 3] == BLACK &&
                board_2022184009[i][j + 4] == BLACK) {
                *x = j + 2;
                *y = i;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == 0 &&
                board_2022184009[i][j + 4] == BLACK) {
                *x = j + 3;
                *y = i;
            }
        }

        // 세로 방향 체크
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 19; j++) {
                if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                    board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == 0) {
                    *x = j;
                    *y = i + 4;
                    return;
                }
                else if (i - 1 >= 0 && board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                    board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK) {
                    *x = j;
                    *y = i - 1;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == 0 &&
                    board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == BLACK) {
                    *x = j;
                    *y = i + 1;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                    board_2022184009[i + 2][j] == 0 && board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == BLACK) {
                    *x = j;
                    *y = i + 2;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                    board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == 0 && board_2022184009[i + 4][j] == BLACK) {
                    *x = j;
                    *y = i + 3;
                    return;
                }
            }
        }

        // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                    board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == 0) {
                    *x = j + 4;
                    *y = i + 4;
                    return;
                }
                else if (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                    board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK) {
                    *x = j - 1;
                    *y = i - 1;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == 0 &&
                    board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == BLACK) {
                    *x = j + 1;
                    *y = i + 1;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                    board_2022184009[i + 2][j + 2] == 0 && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == BLACK) {
                    *x = j + 2;
                    *y = i + 2;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                    board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == 0 && board_2022184009[i + 4][j + 4] == BLACK) {
                    *x = j + 3;
                    *y = i + 3;
                    return;
                }
            }
        }

        // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
        for (int i = 0; i < 15; i++) {
            for (int j = 4; j < 19; j++) {
                if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                    board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == BLACK &&
                    board_2022184009[i + 4][j - 4] == 0) {
                    *x = j - 4;
                    *y = i + 4;
                    return;
                }
                else if (i - 1 >= 0 && j + 1 <= 18 && board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                    board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == BLACK) {
                    *x = j + 1;
                    *y = i - 1;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == 0 &&
                    board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == BLACK && board_2022184009[i + 4][j - 4] == BLACK) {
                    *x = j - 1;
                    *y = i + 1;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                    board_2022184009[i + 2][j - 2] == 0 && board_2022184009[i + 3][j - 3] == BLACK && board_2022184009[i + 4][j - 4] == BLACK) {
                    *x = j - 2;
                    *y = i + 2;
                    return;
                }
                else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                    board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == 0 && board_2022184009[i + 4][j - 4] == BLACK) {
                    *x = j - 2;
                    *y = i + 2;
                    return;
                }
            }
        }
    }
}




void TranPri_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; ++i) 
        for (int j = 0; j < 19; ++j) {
            if (board_2022184009[i][j] == BLACK || board_2022184009[i][j] == WHITE)
                Blackpriorities_2022184009[i][j] = 10000;
        }
}
void White33Block_2022184009(int* x, int* y)
{
    //오른쪽으로 가다가 아래 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                    Blackpriorities_2022184009[i][j + 2] += 250;
            }
            else if (j - 1 >= 0 && board_2022184009[i][j - 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                Blackpriorities_2022184009[i][j + 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == 0 && j + 5 <= 18 && board_2022184009[i + 2][j + 5] == WHITE) {
                Blackpriorities_2022184009[i][j + 2] += 250;
            }
        }
    }

    //왼쪽으로 가다가 아래 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE 
                && board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                     Blackpriorities_2022184009[i + 2][j + 2] += 300;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j + 1] == WHITE
                && board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE
                && board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == 0 && j + 5 <= 18 && board_2022184009[i + 2][j + 5] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
        }
    }

    //오른쪽으로 가다가 위 대각선
    for (int i = 2; i < 19; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i - 2][j + 4] == WHITE) {
                Blackpriorities_2022184009[i - 1][j + 2] += 250;
            }
            else if (j - 1 >= 0 && board_2022184009[i][j - 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i - 2][j + 4] == WHITE) {
                Blackpriorities_2022184009[i - 1][j + 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i - 2][j + 4] == 0 && j + 5 <= 18 && board_2022184009[i - 2][j + 5] == WHITE) {
                Blackpriorities_2022184009[i - 1][j + 2] += 250;
            }
        }
    }

    //왼쪽으로 가다가 위 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == 0 && j + 5 <= 18 && board_2022184009[i + 2][j + 5] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
        }
    }

    //v자
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i][j + 4] == 0 && i - 1 >= 0 && j + 5 <= 18 && board_2022184009[i - 1][j + 5] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
        }
    }

    //v자 거꾸로
    for (int i = 2; i < 19; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i - 1][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Blackpriorities_2022184009[i - 2][j + 2] += 250;
            }
            else if (i + 1 <= 18 && j + 1 <= 18 && board_2022184009[i + 1][j + 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i - 1][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Blackpriorities_2022184009[i - 2][j + 2] += 250;
            }
            else if (i + 1 <= 18 && j + 1 <= 18 && board_2022184009[i + 1][j + 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i - 1][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Blackpriorities_2022184009[i - 2][j + 2] += 250;
            }
        }
    }


    //<자
    for (int i = 0; i < 15; i++) {
        for (int j = 2; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Blackpriorities_2022184009[i + 2][j - 2] += 250;
            }
            else if (i - 1 >= 0 && j + 1 <= 18 && board_2022184009[i - 1][j + 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Blackpriorities_2022184009[i + 2][j - 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j] == 0 && i + 5 <= 18 && j + 1 <= 18 && board_2022184009[i + 5][j + 1] == WHITE) {
                Blackpriorities_2022184009[i + 2][j - 2] += 250;
            }
        }
    }

    //>자 
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j] == 0 && i + 5 <= 18 && j - 1 >= 0 && board_2022184009[i + 5][j - 1] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
        }
    }

    //오른쪽 아래 대각선으로 가다가 아래로
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 2] == WHITE && board_2022184009[i + 4][j + 2] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 2] == WHITE && board_2022184009[i + 4][j + 2] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 2] == WHITE && board_2022184009[i + 4][j + 2] == 0 && i + 5 <= 18 && j + 3 <= 18 && board_2022184009[i + 5][j + 3] == WHITE) {
                Blackpriorities_2022184009[i + 2][j + 2] += 250;
            }
        }
    }

    //왼쪽 아래 대각선으로 가다가 아래로
    for (int i = 4; i < 19; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i - 1][j] == WHITE &&
                board_2022184009[i - 3][j + 1] == WHITE && board_2022184009[i - 4][j + 2] == WHITE) {
                Blackpriorities_2022184009[i - 2][j] += 250;
            }
            else if (i - 1 >= 0 && board_2022184009[i - 1][j] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i - 1][j] == WHITE &&
                board_2022184009[i - 3][j + 1] == WHITE && board_2022184009[i - 4][j + 2] == WHITE) {
                Blackpriorities_2022184009[i - 2][j] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i - 1][j] == WHITE &&
                board_2022184009[i - 3][j + 1] == WHITE && board_2022184009[i - 4][j + 2] == WHITE && i - 5 >= 0 && j + 3 <= 18 && board_2022184009[i - 5][j + 3] == WHITE) {
                Blackpriorities_2022184009[i - 2][j] += 250;
            }
        }
    }

    //오른쪽 위 대각선으로 가다가 위로
    for (int i = 0; i < 14; i++) {
        for (int j = 2; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j - 2] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 250;
            }
            else if (i - 1 >= 0 && board_2022184009[i - 1][j] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j - 2] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j - 2] == 0 && i + 5 <= 18 && j - 3 >= 0 && board_2022184009[i + 5][j - 3] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 250;
            }
        }
    }

    //왼쪽 위 대각선으로 가다가 위로
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j + 2] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 250;
            }
            else if (i - 1 >= 0 && board_2022184009[i - 1][j] == WHITE && board_2022184009[i][j] == 0 && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j + 2] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 250;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j + 2] == 0 && i + 5 <= 18 && j + 3 <= 18 && board_2022184009[i + 5][j + 3] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 250;
            }
        }
    }

    //가로 -자
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Blackpriorities_2022184009[i][j + 2] += 250;
            }
        }
    }
    //가로 1자
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Blackpriorities_2022184009[i + 2][j] += 250;
            }
        }
    }
}





void ToBlockBlack3Line_2022184009(int* x, int* y)
{
    //가로 막기
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK) {
                if (j - 1 >= 0) {

                    Whitepriorities_2022184009[i][j - 1] += 70;

                    if (board_2022184009[i][j - 1] == BLACK || board_2022184009[i][j - 1] == WHITE)
                        Whitepriorities_2022184009[i][j - 1] = 10000;
                }
                if (j + 3 <= 18) {
                    Whitepriorities_2022184009[i][j + 3] += 70;

                    if (board_2022184009[i][j + 3] == BLACK || board_2022184009[i][j + 3] == WHITE)
                        Whitepriorities_2022184009[i][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i][j - 1] == WHITE && board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == 0) {
                if (j + 3 <= 18) {
                    Whitepriorities_2022184009[i][j + 3] -= 30;
                    if (j + 4 <= 18 && board_2022184009[i][j + 4] == BLACK)
                        Whitepriorities_2022184009[i][j + 3] += 300;

                    if (board_2022184009[i][j + 3] == BLACK || board_2022184009[i][j + 3] == WHITE)
                        Whitepriorities_2022184009[i][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == BLACK) {
                if (j - 1 >= 0) {
                    if (j - 2 >= 0 && board_2022184009[i][j - 2] == BLACK)
                        Whitepriorities_2022184009[i][j - 1] -= 30;
                    if (j - 2 >= 0 && board_2022184009[i][j - 2] == BLACK)
                        Whitepriorities_2022184009[i][j - 1] += 300;

                    if (board_2022184009[i][j - 1] == BLACK || board_2022184009[i][j - 1] == WHITE)
                        Whitepriorities_2022184009[i][j - 1] = 10000;
                }
            }
            else if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == 0 &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK) {
                Whitepriorities_2022184009[i][j + 1] += 320;
            }
            else if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                Whitepriorities_2022184009[i][j + 2] == 0 && board_2022184009[i][j + 3] == BLACK) {
                Blackpriorities_2022184009[i][j + 2] += 320;
            }
        }
    }
    // 세로 방향 체크
    for (int i = 1; i < 16; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == 0) {
                if (i - 1 >= 0) {
                    Whitepriorities_2022184009[i - 1][j] += 70;

                    if (board_2022184009[i - 1][j] == BLACK || board_2022184009[i - 1][j] == WHITE)
                        Whitepriorities_2022184009[i - 1][j] = 10000;
                }

                if (i + 3 <= 18) {
                    Whitepriorities_2022184009[i + 3][j] += 70;

                    if (board_2022184009[i + 3][j] == BLACK || board_2022184009[i][j] == WHITE)
                        Whitepriorities_2022184009[i + 3][j] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j] == WHITE && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == 0) {
                if (i + 3 <= 18) {
                    Whitepriorities_2022184009[i + 3][j] -= 30;
                    if (i + 4 <= 18 && board_2022184009[i + 4][j] == BLACK)
                        Whitepriorities_2022184009[i + 3][j] += 300;

                    if (board_2022184009[i + 3][j] == BLACK || board_2022184009[i + 3][j] == WHITE)
                        Whitepriorities_2022184009[i + 3][j] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == WHITE) {
                if (i - 1 >= 0) {
                    Whitepriorities_2022184009[i - 1][j] -= 30;
                    if (i - 2 >= 0 && board_2022184009[i - 2][j] == BLACK)
                        Whitepriorities_2022184009[i - 1][j] += 300;

                    if (board_2022184009[i - 1][j] == BLACK || board_2022184009[i - 1][j] == WHITE)
                        Whitepriorities_2022184009[i - 1][j] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == 0 &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK) {
                Whitepriorities_2022184009[i + 1][j] += 320;
            }
            else if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == 0 && board_2022184009[i + 3][j] == BLACK) {
                Whitepriorities_2022184009[i + 2][j] += 320;
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == 0) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Whitepriorities_2022184009[i - 1][j - 1] += 70;

                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j - 1] = 10000;
                }

                if (i + 3 <= 18 && j + 3 <= 18) {
                    Whitepriorities_2022184009[i + 3][j + 3] += 70;

                    if (board_2022184009[i + 3][j + 3] == BLACK || board_2022184009[i + 3][j + 3] == WHITE)
                        Whitepriorities_2022184009[i + 3][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j - 1] == WHITE && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == 0) {
                if (i + 3 <= 18 && j + 3 <= 18) {
                    Whitepriorities_2022184009[i + 3][j + 3] -= 30;
                    if (i + 4 <= 18 && j + 4 <= 18 && board_2022184009[i + 4][j + 4] == BLACK)
                        Whitepriorities_2022184009[i + 3][j + 3] += 300;

                    if (board_2022184009[i + 3][j + 3] == BLACK || board_2022184009[i + 3][j + 3] == WHITE)
                        Whitepriorities_2022184009[i + 3][j + 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == WHITE) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Whitepriorities_2022184009[i - 1][j - 1] -= 30;
                    if (i - 2 >= 0 && j - 2 >= 0 && board_2022184009[i - 2][j - 2] == BLACK)
                        Whitepriorities_2022184009[i - 1][j - 1] += 300;

                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j - 1] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 4; j < 18; j++) {
            if (board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == 0) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Whitepriorities_2022184009[i - 1][j + 1] += 70;

                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j + 1] = 10000;
                }
                if (i + 4 <= 18 && j - 4 <= 18) {
                    Whitepriorities_2022184009[i + 3][j - 3] += 70;

                    if (board_2022184009[i + 3][j - 3] == BLACK || board_2022184009[i + 3][j - 3] == WHITE)
                        Whitepriorities_2022184009[i + 3][j - 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j + 1] == WHITE && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == 0) {
                if (i + 4 <= 18 && j - 4 <= 18) {
                    Whitepriorities_2022184009[i + 3][j - 3] -= 30;
                    if (i + 4 <= 18 && j - 4 >= 0 && board_2022184009[i + 4][j - 4] == BLACK)
                        Whitepriorities_2022184009[i + 3][j - 3] += 300;

                    if (board_2022184009[i + 3][j - 3] == BLACK || board_2022184009[i + 3][j - 3] == BLACK)
                        Whitepriorities_2022184009[i + 3][j - 3] = 10000;
                }
            }
            else if (board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == WHITE) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Whitepriorities_2022184009[i - 1][j + 1] -= 30;
                    if (i - 2 >= 0 && j + 2 <= 18)
                        Whitepriorities_2022184009[i - 1][j + 1] += 300;

                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j + 1] = 10000;
                }
            }
        }
    }
}
void Make3WhiteLine_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == 0) {
                if (j - 1 >= 0) {
                    Whitepriorities_2022184009[i][j - 1] += 10;
                    if (board_2022184009[i][j - 1] == BLACK || board_2022184009[i][j - 1] == WHITE)
                        Whitepriorities_2022184009[i][j - 1] = 10000;
                }
                if (j + 2 <= 18) {
                    Whitepriorities_2022184009[i][j + 2] += 10;
                    if (board_2022184009[i][j + 2] == BLACK || board_2022184009[i][j + 2] == WHITE)
                        Whitepriorities_2022184009[i][j + 2] = 10000;
                }
            }
        }
    }

    // 세로 방향 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == 0) {
                if (i - 1 >= 0) {
                    Whitepriorities_2022184009[i - 1][j] += 10;
                    if (board_2022184009[i - 1][j] == BLACK || board_2022184009[i - 1][j] == WHITE)
                        Whitepriorities_2022184009[i - 1][j] = 10000;
                }

                if (i + 2 <= 18) {
                    Whitepriorities_2022184009[i + 2][j] += 10;
                    if (board_2022184009[i + 2][j] == BLACK || board_2022184009[i + 2][j] == WHITE)
                        Whitepriorities_2022184009[i + 2][j] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == 0) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Whitepriorities_2022184009[i - 1][j - 1] += 10;
                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j - 1] = 10000;
                }

                if (i + 2 <= 18 && j + 2 <= 18) {
                    Whitepriorities_2022184009[i + 2][j + 2] += 10;
                    if (board_2022184009[i + 2][j + 2] == BLACK || board_2022184009[i + 2][j + 2] == WHITE)
                        Whitepriorities_2022184009[i + 2][j + 2] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 4; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == 0) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Whitepriorities_2022184009[i - 1][j + 1] += 10;
                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j + 1] = 10000;
                }

                if (i + 2 <= 18 && j - 2 <= 18) {
                    Whitepriorities_2022184009[i + 2][j - 2] += 10;
                    if (board_2022184009[i + 2][j - 2] == BLACK || board_2022184009[i + 2][j - 2] == WHITE)
                        Whitepriorities_2022184009[i + 2][j - 2] = 10000;
                }
            }
        }
    }
}
void Make4WhiteLine_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == 0 && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE && board_2022184009[i][j + 4] == 0 && (board_2022184009[i][j + 5] == 0 || board_2022184009[i][j - 1] == 0)) {
                if (j - 1 >= 0) {
                    Whitepriorities_2022184009[i][j] += 70;

                }
                if (j + 4 <= 18) {
                    Whitepriorities_2022184009[i][j + 3] += 70;
                }
            }
        }
    }

    // 세로 방향 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == 0 && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == 0 && (board_2022184009[i + 5][j] == 0 || board_2022184009[i - 1][j] == 0)) {
                if (i - 1 >= 0) {
                    Whitepriorities_2022184009[i][j] += 70;
                }

                if (i + 4 <= 18) {
                    Whitepriorities_2022184009[i + 3][j] += 70;
                }
            }

        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == 0) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    Whitepriorities_2022184009[i - 1][j - 1] += 70;

                    if (board_2022184009[i - 1][j - 1] == BLACK || board_2022184009[i - 1][j - 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j - 1] = 10000;
                }

                if (i + 4 <= 18 && j + 4 <= 18) {
                    Whitepriorities_2022184009[i + 3][j + 3] += 70;

                    if (board_2022184009[i + 3][j + 3] == BLACK || board_2022184009[i + 3][j + 3] == WHITE)
                        Whitepriorities_2022184009[i + 3][j + 3] = 10000;
                }
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 4; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == 0) {
                if (i - 1 >= 0 && j + 1 <= 18) {
                    Whitepriorities_2022184009[i - 1][j + 1] += 70;

                    if (board_2022184009[i - 1][j + 1] == BLACK || board_2022184009[i - 1][j + 1] == WHITE)
                        Whitepriorities_2022184009[i - 1][j + 1] = 10000;
                }

                if (i + 3 <= 18 && j - 3 <= 18) {
                    Whitepriorities_2022184009[i + 3][j - 3] += 70;

                    if (board_2022184009[i + 3][j - 3] == BLACK || board_2022184009[i + 3][j - 3] == WHITE)
                        Whitepriorities_2022184009[i + 3][j - 3] = 10000;
                }
            }
        }
    }
}
void BlackMidBlock_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == 0 &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK) {
                Whitepriorities_2022184009[i][j + 1] += 300;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == 0 && board_2022184009[i][j + 3] == BLACK) {
                Whitepriorities_2022184009[i][j + 2] += 300;
            }
        }
    }


    // 세로 방향 체크
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == 0 &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK) {
                Whitepriorities_2022184009[i + 1][j] += 300;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == 0 && board_2022184009[i + 3][j] == BLACK) {
                Whitepriorities_2022184009[i + 2][j] += 300;
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == 0 &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK) {
                Whitepriorities_2022184009[i + 1][j + 1] += 300;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == 0 && board_2022184009[i + 3][j + 3] == BLACK) {
                Whitepriorities_2022184009[i + 2][j + 2] += 300;
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 4; j < 18; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == 0 &&
                board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == BLACK) {
                Whitepriorities_2022184009[i - 1][j + 1] += 300;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == 0 && board_2022184009[i + 3][j - 3] == BLACK) {
                Whitepriorities_2022184009[i + 2][j - 2] += 300;
            }
        }
    }
}
void White33Atack_2022184009(int* x, int* y)
{
    //오른쪽으로 가다가 아래 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                Whitepriorities_2022184009[i][j + 2] += 300;
            }
        }
    }

    //왼쪽으로 가다가 아래 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE
                && board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4]) {
                Whitepriorities_2022184009[i + 2][j + 2] += 300;
            }
        }
    }

    //오른쪽으로 가다가 위 대각선
    for (int i = 2; i < 19; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i - 2][j + 4] == WHITE) {
                Whitepriorities_2022184009[i - 1][j + 2] += 300;
            }
        }
    }

    //왼쪽으로 가다가 위 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 2][j + 3] == WHITE && board_2022184009[i + 2][j + 4] == WHITE) {
                Whitepriorities_2022184009[i + 2][j + 2] += 300;
            }
        }
    }

    //v자
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 1][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Whitepriorities_2022184009[i + 2][j + 2] += 300;
            }
        }
    }

    //v자 거꾸로
    for (int i = 2; i < 19; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i - 1][j + 1] == WHITE &&
                board_2022184009[i - 1][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Whitepriorities_2022184009[i - 2][j + 2] += 300;
            }
        }
    }


    //<자
    for (int i = 0; i < 15; i++) {
        for (int j = 2; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Whitepriorities_2022184009[i + 2][j - 2] += 300;
            }
        }
    }

    //>자 
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Whitepriorities_2022184009[i + 2][j + 2] += 300;
            }
        }
    }

    //오른쪽 아래 대각선으로 가다가 아래로
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                board_2022184009[i + 3][j + 2] == WHITE && board_2022184009[i + 4][j + 2] == WHITE) {
                Whitepriorities_2022184009[i + 2][j + 2] += 300;
            }
        }
    }

    //왼쪽 아래 대각선으로 가다가 아래로
    for (int i = 4; i < 19; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i - 1][j] == WHITE &&
                board_2022184009[i - 3][j + 1] == WHITE && board_2022184009[i - 4][j + 2] == WHITE) {
                Whitepriorities_2022184009[i - 2][j] += 300;
            }
        }
    }

    //오른쪽 위 대각선으로 가다가 위로
    for (int i = 0; i < 14; i++) {
        for (int j = 2; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j - 1] == WHITE && board_2022184009[i + 4][j - 2] == WHITE) {
                Whitepriorities_2022184009[i + 2][j] += 300;
            }
        }
    }

    //왼쪽 위 대각선으로 가다가 위로
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j + 1] == WHITE && board_2022184009[i + 4][j + 2] == WHITE) {
                Whitepriorities_2022184009[i + 2][j] += 300;
            }
        }
    }

    //가로 -자
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 3] == WHITE && board_2022184009[i][j + 4] == WHITE) {
                Whitepriorities_2022184009[i][j + 2] += 300;
            }
        }
    }
    //가로 1자
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                Whitepriorities_2022184009[i + 2][j] += 300;
            }
        }
    }
}
void WhiteRealDefence_2022184009(int* x, int* y)
{
    //가로 가운데 무조건 막기
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK && board_2022184009[i][j + 2] == 0 &&
                board_2022184009[i][j + 3] == BLACK && board_2022184009[i][j + 4] == BLACK) {
                *x = j + 2;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == 0 && board_2022184009[i][j + 2] == BLACK &&
                board_2022184009[i][j + 3] == BLACK && board_2022184009[i][j + 4] == BLACK) {
                *x = j + 1;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK && board_2022184009[i][j + 2] == BLACK &&
                board_2022184009[i][j + 3] == 0 && board_2022184009[i][j + 4] == BLACK) {
                *x = j + 3;
                *y = i;
                return;
            }
        }
    }

    //세로 가운데 무조건 막기
    for (int i = 0; i < 15; i++) {
        for (int j = 1; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == 0 && board_2022184009[i + 2][j] == BLACK &&
                board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == BLACK) {
                *x = j;
                *y = i + 1;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK && board_2022184009[i + 2][j] == 0 &&
                board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == BLACK) {
                *x = j;
                *y = i + 2;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK && board_2022184009[i + 2][j] == BLACK &&
                board_2022184009[i + 3][j] == 0 && board_2022184009[i + 4][j] == BLACK) {
                *x = j;
                *y = i + 3;
                return;
            }
            else if (board_2022184009[i][j] == 0 && board_2022184009[i + 1][j] == BLACK && board_2022184009[i + 2][j] == BLACK &&
                board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == BLACK) {
                *x = j;
                *y = i;
                return;
            }
        }
    }

    //대각선 오른쪽 아래로 가는 가운데 무조건 막기
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == BLACK && board_2022184009[i + 5][j + 5] == 0) {
                *x = j + 5;
                *y = i + 5;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == 0 &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == BLACK) {
                *x = j + 1;
                *y = i + 1;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == 0 && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == BLACK) {
                *x = j + 2;
                *y = i + 2;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == 0 && board_2022184009[i + 4][j + 4] == BLACK) {
                *x = j + 3;
                *y = i + 3;
                return;
            }
            else if (board_2022184009[i][j] == 0 && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == WHITE) {
                *x = j;
                *y = i;
                return;
            }
        }
    }
    //대각선 왼쪽 아래로가는 가운데...
    for (int i = 0; i < 14; i++) {
        for (int j = 4; j < 18; j++) {
            if (board_2022184009[i][j] == 0 && board_2022184009[i + 1][j - 1] == BLACK && board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == BLACK &&
                board_2022184009[i + 4][j - 4] == BLACK && board_2022184009[i + 5][j - 5] == WHITE) {
                *x = j;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == BLACK && board_2022184009[i + 2][j - 2] == BLACK &&
                board_2022184009[i + 3][j - 3] == BLACK && board_2022184009[i + 4][j - 4] == BLACK && board_2022184009[i + 5][j - 5] == 0) {
                *x = j - 5;
                *y = i + 5;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == 0 && board_2022184009[i + 2][j - 2] == BLACK &&
                board_2022184009[i + 3][j - 3] == BLACK && board_2022184009[i + 4][j - 4] == BLACK) {
                *x = j - 1;
                *y = i + 1;
                return;
            }
            else if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK && board_2022184009[i + 2][j - 2] == BLACK &&
                board_2022184009[i + 3][j - 3] == 0 && board_2022184009[i + 4][j - 4] == BLACK) {
                *x = j - 3;
                *y = i + 3;
                return;
            }
        }
    }


    //가로 무조건 막기
    for (int i = 0; i < 19; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK && (board_2022184009[i][j + 4] != 0 || j + 4 == 19)) {
                *x = j - 1;
                *y = i;
                return;
            }
            else if ((board_2022184009[i][j - 1] == WHITE || j - 1 == -1 ) && board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i][j + 2] == BLACK && board_2022184009[i][j + 3] == BLACK && board_2022184009[i][j + 4] == 0) {
                *x = j + 4;
                *y = i;
                return;
            }
        }
    }


    // 세로 방향 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] != 0) {
                *x = j;
                *y = i - 1;
                return;
            }
            else if (board_2022184009[i - 1][j] != 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 2][j] == BLACK && board_2022184009[i + 3][j] == BLACK && board_2022184009[i + 4][j] == 0) {
                *x = j;
                *y = i + 4;
                return;
            }
        }
    }

    // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 1; j < 15; j++) {
            if (board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] != 0) {
                *x = j - 1;
                *y = i - 1;
                return;
            }
            else if (board_2022184009[i - 1][j - 1] != 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 2] == BLACK && board_2022184009[i + 3][j + 3] == BLACK && board_2022184009[i + 4][j + 4] == 0) {
                *x = j + 4;
                *y = i + 4;
                return;
            }
        }
    }

    // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
    for (int i = 1; i < 15; i++) {
        for (int j = 4; j < 17; j++) {
            if (board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == 0 && board_2022184009[i + 4][j - 4] == WHITE) {
                *x = j + 1;
                *y = i - 1;
                return;
            }
            else if (board_2022184009[i - 1][j + 1] == WHITE && board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 2][j - 2] == BLACK && board_2022184009[i + 3][j - 3] == BLACK && board_2022184009[i + 4][j - 4] == 0) {
                *x = j - 4;
                *y = i + 4;
                return;
            }
        }
    }
}
void WhiteCanWin_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE &&
                board_2022184009[i][j + 4] == 0) {
                *x = j + 4;
                *y = i;
                return;
            }
            else if (j - 1 >= 0 && board_2022184009[i][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE) {
                *x = j - 1;
                *y = i;
                return;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == 0 &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == WHITE &&
                board_2022184009[i][j + 4] == WHITE) {
                *x = j + 1;
                *y = i;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == 0 && board_2022184009[i][j + 3] == WHITE &&
                board_2022184009[i][j + 4] == WHITE) {
                *x = j + 2;
                *y = i;
            }
            else if (board_2022184009[i][j] == WHITE && board_2022184009[i][j + 1] == WHITE &&
                board_2022184009[i][j + 2] == WHITE && board_2022184009[i][j + 3] == 0 &&
                board_2022184009[i][j + 4] == WHITE) {
                *x = j + 3;
                *y = i;
            }
        }

        // 세로 방향 체크
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 19; j++) {
                if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                    board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == 0) {
                    *x = j;
                    *y = i + 4;
                    return;
                }
                else if (i - 1 >= 0 && board_2022184009[i - 1][j] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                    board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE) {
                    *x = j;
                    *y = i - 1;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == 0 &&
                    board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                    *x = j;
                    *y = i + 1;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                    board_2022184009[i + 2][j] == 0 && board_2022184009[i + 3][j] == WHITE && board_2022184009[i + 4][j] == WHITE) {
                    *x = j;
                    *y = i + 2;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j] == WHITE &&
                    board_2022184009[i + 2][j] == WHITE && board_2022184009[i + 3][j] == 0 && board_2022184009[i + 4][j] == WHITE) {
                    *x = j;
                    *y = i + 3;
                    return;
                }
            }
        }

        // 대각선 방향 (왼쪽 위에서 오른쪽 아래로) 체크
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 15; j++) {
                if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                    board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == 0) {
                    *x = j + 4;
                    *y = i + 4;
                    return;
                }
                else if (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                    board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE) {
                    *x = j - 1;
                    *y = i - 1;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == 0 &&
                    board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == WHITE) {
                    *x = j + 1;
                    *y = i + 1;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                    board_2022184009[i + 2][j + 2] == 0 && board_2022184009[i + 3][j + 3] == WHITE && board_2022184009[i + 4][j + 4] == WHITE) {
                    *x = j + 2;
                    *y = i + 2;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j + 1] == WHITE &&
                    board_2022184009[i + 2][j + 2] == WHITE && board_2022184009[i + 3][j + 3] == 0 && board_2022184009[i + 4][j + 4] == WHITE) {
                    *x = j + 3;
                    *y = i + 3;
                    return;
                }
            }
        }

        // 대각선 방향 (오른쪽 위에서 왼쪽 아래로) 체크
        for (int i = 0; i < 15; i++) {
            for (int j = 4; j < 19; j++) {
                if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                    board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == WHITE &&
                    board_2022184009[i + 4][j - 4] == 0) {
                    *x = j - 4;
                    *y = i + 4;
                    return;
                }
                else if (i - 1 >= 0 && j + 1 <= 18 && board_2022184009[i - 1][j + 1] == 0 && board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                    board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == WHITE) {
                    *x = j + 1;
                    *y = i - 1;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == 0 &&
                    board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == WHITE && board_2022184009[i + 4][j - 4] == WHITE) {
                    *x = j - 1;
                    *y = i + 1;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                    board_2022184009[i + 2][j - 2] == 0 && board_2022184009[i + 3][j - 3] == WHITE && board_2022184009[i + 4][j - 4] == WHITE) {
                    *x = j - 2;
                    *y = i + 2;
                    return;
                }
                else if (board_2022184009[i][j] == WHITE && board_2022184009[i + 1][j - 1] == WHITE &&
                    board_2022184009[i + 2][j - 2] == WHITE && board_2022184009[i + 3][j - 3] == 0 && board_2022184009[i + 4][j - 4] == WHITE) {
                    *x = j - 2;
                    *y = i + 2;
                    return;
                }
            }
        }
    }
}
void Wstd_giving_priority_BLACK_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK) {
                if (i - 1 >= 0 && j - 1 >= 0)
                    --Blackpriorities_2022184009[i - 1][j - 1];
                if (i - 1 >= 0) {
                    --Blackpriorities_2022184009[i - 1][j];
                    if (j + 1 <= 18)
                        ++Blackpriorities_2022184009[i - 1][j + 1];
                }

                if (j - 1 >= 0)
                    --Blackpriorities_2022184009[i][j - 1];
                if (j + 1 <= 18)
                    --Blackpriorities_2022184009[i][j + 1];

                if (i + 1 <= 18 && j - 1 >= 0)
                    --Blackpriorities_2022184009[i + 1][j - 1];

                if (i + 1 <= 18) {
                    --Blackpriorities_2022184009[i + 1][j];
                    if (j + 1 <= 18)
                        --Blackpriorities_2022184009[i + 1][j + 1];
                }
            }
        }
    }
}
void Wstd_giving_priority_WHITE_2022184009(int* x, int* y)
{
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 19; j++) {
            if (board_2022184009[i][j] == WHITE) {
                if (i - 1 >= 0 && j - 1 >= 0)
                    ++Blackpriorities_2022184009[i - 1][j - 1];

                if (i - 1 >= 0) {
                    ++Blackpriorities_2022184009[i - 1][j];
                    if (j + 1 <= 18)
                        ++Blackpriorities_2022184009[i - 1][j + 1];
                }

                if (j - 1 >= 0)
                    ++Blackpriorities_2022184009[i][j - 1];
                if (j + 1 <= 18)
                    ++Blackpriorities_2022184009[i][j + 1];

                if (i + 1 <= 18 && j - 1 >= 0)
                    ++Blackpriorities_2022184009[i + 1][j - 1];

                if (i + 1 <= 18) {
                    ++Blackpriorities_2022184009[i + 1][j];
                    if (j + 1 <= 18)
                        ++Blackpriorities_2022184009[i + 1][j + 1];
                }
            }
        }
    }
}

void NewCheck_2022184009()
{
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {

        }
    }
}

void Check33_2022184009()
{
    //오른쪽으로 가다가 아래 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i + 1][j + 3] == BLACK && board_2022184009[i + 2][j + 4] == BLACK) {
                if((j - 1 >= 18 && board_2022184009[i][j - 1] != WHITE )||( i + 3 <= 18 && j + 5 <= 18 && board_2022184009[i + 3][j + 5] != WHITE))
                    Blackpriorities_2022184009[i][j + 2] += 10000;
            }
        }
    }

    //왼쪽으로 가다가 아래 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK
                && board_2022184009[i + 2][j + 3] == BLACK && board_2022184009[i + 2][j + 4]) {
                if ((i - 1 >= 0 && j - 1 >= 18 && board_2022184009[i - 1][j - 1] != WHITE) || (i + 3 <= 18 && j + 5 <= 18 && board_2022184009[i + 3][j + 5] != WHITE))
                    Blackpriorities_2022184009[i + 2][j + 2] += 10000;
            }
        }
    }

    //오른쪽으로 가다가 위 대각선
    for (int i = 2; i < 19; i++) {
        for (int j = 0; j < 15; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i][j + 1] == BLACK &&
                board_2022184009[i - 1][j + 3] == BLACK && board_2022184009[i - 2][j + 4] == BLACK) {
                if ((j - 1 >= 18 && board_2022184009[i][j - 1] != WHITE) || (i - 3 >= 0 && j + 5 <= 18 && board_2022184009[i - 3][j + 5] != WHITE))
                    Blackpriorities_2022184009[i - 1][j + 2] += 10000;
            }
        }
    }

    //왼쪽으로 가다가 위 대각선
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 2][j + 3] == BLACK && board_2022184009[i + 2][j + 4] == BLACK) {
                if ((i - 1 >= 18 && j - 1 >= 18 && board_2022184009[i - 1][j - 1] != WHITE) || (i + 3 <= 18 && j + 5 <= 18 && board_2022184009[i + 3][j + 5] != WHITE))
                    Blackpriorities_2022184009[i + 2][j + 2] += 10000;
            }
        }
    }

    //v자
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 1][j + 3] == BLACK && board_2022184009[i][j + 4] == BLACK) {
                if ((i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] != WHITE) || (i - 1 >= 0 && j + 5 <= 18 && board_2022184009[i - 1][j + 5] != WHITE))
                    Blackpriorities_2022184009[i + 2][j + 2] += 10000;
            }
        }
    }

    //v자 거꾸로
    for (int i = 2; i < 19; i++) {
        for (int j = 0; j < 14; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i - 1][j + 1] == BLACK &&
                board_2022184009[i - 1][j + 3] == BLACK && board_2022184009[i][j + 4] == BLACK) {
                if ((i + 1 <= 18 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] != WHITE) || (i - 1 >= 0 && j + 5 <= 18 && board_2022184009[i - 1][j + 5] != WHITE))
                    Blackpriorities_2022184009[i - 2][j + 2] += 10000;
            }
        }
    }


    //<자
    for (int i = 0; i < 15; i++) {
        for (int j = 2; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j - 1] == BLACK &&
                board_2022184009[i + 3][j - 1] == BLACK && board_2022184009[i + 4][j] == BLACK) {
                if ((i - 1 >= 0 && j + 1 <= 18 && board_2022184009[i - 1][j - 1] != WHITE) || (i - 1 >= 0 && j + 1 <= 18 && board_2022184009[i - 1][j + 1] != WHITE))
                    Blackpriorities_2022184009[i + 2][j - 2] += 10000;
            }
        }
    }

    //>자 
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 3][j + 1] == BLACK && board_2022184009[i + 4][j] == BLACK) {
                if ((i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] != WHITE) || (i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i + 5][j - 1] != WHITE))
                    Blackpriorities_2022184009[i + 2][j + 2] += 10000;
            }
        }
    }

    //오른쪽 아래 대각선으로 가다가 아래로
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j + 1] == BLACK &&
                board_2022184009[i + 3][j + 2] == BLACK && board_2022184009[i + 4][j + 2] == BLACK) {
                if ((i - 1 >= 0 && j - 1 >= 0 && board_2022184009[i - 1][j - 1] != WHITE) || (i + 5 <= 18 && j+3 <= 18 && board_2022184009[i + 5][j + 3] != WHITE))
                    Blackpriorities_2022184009[i + 2][j + 2] += 10000;
            }
        }
    }

    //왼쪽 아래 대각선으로 가다가 아래로
    for (int i = 4; i < 19; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i - 1][j] == BLACK &&
                board_2022184009[i - 3][j + 1] == BLACK && board_2022184009[i - 4][j + 2] == BLACK) {
                if ((i + 1 <= 18 && board_2022184009[i - 1][j] != WHITE) || (i - 5 >= 0 && j + 3 <= 18 && board_2022184009[i - 5][j + 3] != WHITE))
                    Blackpriorities_2022184009[i - 2][j] += 10000;
            }
        }
    }

    //오른쪽 위 대각선으로 가다가 위로
    for (int i = 0; i < 14; i++) {
        for (int j = 2; j < 19; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 3][j - 1] == BLACK && board_2022184009[i + 4][j - 2] == BLACK) {
                if ((i - 1 >= 0 && board_2022184009[i - 1][j] != WHITE) || (i + 5 <= 18 && j - 3 >= 0 && board_2022184009[i + 5][j - 3] != WHITE))
                    Blackpriorities_2022184009[i + 2][j] += 10000;
            }
        }
    }

    //왼쪽 위 대각선으로 가다가 위로
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 17; j++) {
            if (board_2022184009[i][j] == BLACK && board_2022184009[i + 1][j] == BLACK &&
                board_2022184009[i + 3][j + 1] == BLACK && board_2022184009[i + 4][j + 2] == BLACK) {
                if ((i - 1 >= 0 && board_2022184009[i - 1][j] != WHITE) || (i + 5 <= 18 && j + 3 <= 18 && board_2022184009[i + 5][j + 3] != WHITE))
                    Blackpriorities_2022184009[i + 2][j] += 10000;
            }
        }
    }
}