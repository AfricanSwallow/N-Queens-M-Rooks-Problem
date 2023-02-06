#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
int N, M, total;
bool *visit_col;
int sol_cnt = 0;
typedef struct _piece {
    int diff;
    int sum;
    bool isQueen;
}Piece;
Piece *piece;


void Visit(int row, int numQueens, int numRooks);
bool valid(int row, int column, bool IsQueen, int numQueens, int numRooks);
void Reset(int total);

int main(void) {
    while(scanf("%d%d", &N, &M) == 2) {
        total = N + M;
        visit_col = (bool*) malloc(sizeof(bool)*total);
        piece = (Piece*) malloc(sizeof(Piece)*total);
        Reset(total);
        Visit(0, N, M);
        printf("%d\n", sol_cnt);
        free(visit_col);
        free(piece);
    }
}

void Visit(int row, int numQueens, int numRooks) {
    if(row == total) {
        sol_cnt++;
        // printf("Found\n");
        return;
    }

    for(int j = 0; j < 2; j++) {
        for(int i = 0; i < total; i++) {
            if(valid(row, i, j, numQueens, numRooks)) {
                visit_col[i] = true;
                piece[row].diff = row - i;
                piece[row].sum = row + i;
                if(j == 0) {
                    // printf("Rook visit (%d, %d)\n", row, i);
                    Visit(row+1, numQueens, numRooks-1);
                }
                else {
                    // printf("Queen visit (%d, %d)\n", row, i);
                    piece[row].isQueen = true;
                    Visit(row+1, numQueens-1, numRooks);
                }
                

                //Restore tracking
                visit_col[i] = false;
                piece[row].diff = INT_MAX;
                piece[row].sum = INT_MAX;
                piece[row].isQueen = false;
            }
        }
    }

    
}

bool valid(int row, int column, bool ThisIsQueen, int numQueens, int numRooks) {
    int difference = row - column;
    int summation = row + column;
    //See if there are enough queens or rooks
    if(ThisIsQueen) {
        if(numQueens == 0)
            return false;
    }else
        if(numRooks == 0)
            return false;

    if(visit_col[column] == false) {
        for(int i = 0; i < row; i++) {
            if(ThisIsQueen) {
                if(difference == piece[i].diff || summation == piece[i].sum)
                    return false;
            }else {
                if((difference == piece[i].diff || summation == piece[i].sum) && piece[i].isQueen) 
                    return false;
            }
        }
        return true;
    }else 
        return false;
}

void Reset(int total) {
    memset(visit_col, false, sizeof(bool)*total);
    for(int i = 0; i < total; i++) {
        piece[i].diff = INT_MAX;
        piece[i].sum = INT_MAX;
        piece[i].isQueen = false;
    }
    sol_cnt = 0;
}