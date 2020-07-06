#include <stdio.h>
#include <string.h>

#include "caballo.h"

int main()
{
    int N = 5;
    int board[N][N];
    memset(board, -1, N*N*sizeof(int));
    board[0][0] = 0;

    solve_knight_tour(0, 0, 1, N, board);

    print_board(N, board);

    return 0;
}

void print_board(int N, int board[N][N])
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf(" %02d ", board[i][j]);
        }
        printf("\n");
    }
}

int is_safe(int x, int y, int N, int board[N][N])
{
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

int solve_knight_tour(int x, int y, int num_mov, int N, int board[N][N])
{
    if (num_mov == N * N)
        return 1;

    // posibles movimientos de el caballo en cualquier posicion (x, y)
    // tomando esa posicion como el origen
    int x_moves[8] = {2, 1, -1, -2, -2, -1,  1,  2};
    int y_moves[8] = {1, 2,  2,  1, -1, -2, -2, -1};

    int new_x, new_y;

    for (int i = 0; i < 8; ++i) {
        new_x = x + x_moves[i];
        new_y = y + y_moves[i];

        if (is_safe(new_x, new_y, N, board)) {
            board[new_x][new_y] = num_mov;
            if (solve_knight_tour(new_x, new_y, num_mov + 1, N, board)) {
                return 1;
            } else {
                board[new_x][new_y] = -1;
            }
        }
    }

    return 0;
}