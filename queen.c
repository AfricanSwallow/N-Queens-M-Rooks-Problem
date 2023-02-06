#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
int N, M, total;
int *diff;
int *sum;
bool *visit_col, *isQueen;
int sol_cnt = 0, N_cnt, M_cnt;
typedef struct _piece {
    int diff;
    int sum;
    bool isQueen;
}Piece;


void Visit(int row, int numQueens, int numRooks);
bool valid(int row, int column, bool IsQueen, int numQueens, int numRooks);
void Reset(void);

int main(void) {
    while(scanf("%d%d", &N, &M) == 2) {
        total = N + M;
        N_cnt = N;
        M_cnt = M;
        diff = (int*) malloc(sizeof(int)*total);
        sum = (int*) malloc(sizeof(int)*total);
        visit_col = (bool*) malloc(sizeof(bool)*total);
        isQueen = (bool*) malloc(sizeof(bool)*total);
        Reset();
        Visit(0, N, M);
        printf("%d\n", sol_cnt);
        free(diff);
        free(sum);
        free(visit_col);
        free(isQueen);
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
                diff[row] = row - i;
                sum[row] = row + i;
                if(j == 0) {
                    // printf("Rook visit (%d, %d)\n", row, i);
                    Visit(row+1, numQueens, numRooks-1);
                }
                else {
                    // printf("Queen visit (%d, %d)\n", row, i);
                    isQueen[row] = true;
                    Visit(row+1, numQueens-1, numRooks);
                }
                

                //Restore tracking
                visit_col[i] = false;
                diff[row] = INT_MAX;
                sum[row] = INT_MAX;
                if(j == 1)
                    isQueen[row] = false;
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
                if(difference == diff[i] || summation == sum[i])
                    return false;
            }else {
                if((difference == diff[i] || summation == sum[i]) && isQueen[i]) 
                    return false;
            }
        }
        return true;
    }else 
        return false;
}

void Reset(void) {
    memset(diff, INT_MAX, sizeof(int)*total);
    memset(sum, INT_MAX, sizeof(int)*total);
    memset(visit_col, false, sizeof(bool)*total);
    memset(isQueen, false, sizeof(bool)*total);
    sol_cnt = 0;
}