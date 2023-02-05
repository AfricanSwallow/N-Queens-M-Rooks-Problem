#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
int N, M, total;
int *diff;
int *sum;
bool *visit_col, *isQueen;
int sol_cnt = 0, put_cnt = 0, N_cnt, M_cnt;

void Visit(int row);
bool valid(int row, int column, bool IsQueen);
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
        Visit(0);
        printf("%d\n", sol_cnt);
        free(diff);
        free(sum);
        free(visit_col);
        free(isQueen);
    }
    
    
}

void Visit(int row) {
    if(row == total) {
        sol_cnt++;
        // printf("Found\n");
        return;
    }

    for(int j = 0; j < 2; j++) {
        for(int i = 0; i < total; i++) {
            if(valid(row, i, j)) {
                visit_col[i] = true;
                diff[put_cnt] = row - i;
                sum[put_cnt] = row + i;
                if(j == 0) {
                    // printf("Rook visit (%d, %d)\n", row, i);
                    M_cnt--;
                }
                else {
                    // printf("Queen visit (%d, %d)\n", row, i);
                    isQueen[put_cnt] = true;
                    N_cnt--;
                }
                put_cnt++;
                
                Visit(row+1);

                //Restore tracking
                visit_col[i] = false;
                put_cnt--;
                diff[put_cnt] = INT_MAX;
                sum[put_cnt] = INT_MAX;
                if(j == 0)
                    M_cnt++;
                else {
                    isQueen[put_cnt] = false;
                    N_cnt++;
                }
            }
        }
    }

    
}

bool valid(int row, int column, bool ThisIsQueen) {
    int difference = row - column;
    int summation = row + column;
    //See if there are enough queens or rooks
    if(ThisIsQueen) {
        if(N_cnt == 0)
            return false;
    }else
        if(M_cnt == 0)
            return false;

    if(visit_col[column] == false) {
        for(int i = 0; i < put_cnt; i++) {
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
    put_cnt = 0;
}