#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
int n;
int *diff;
int *sum;
bool *visit_col;
int sol_cnt = 0, diff_cnt = 0;

void Visit(int row);
bool valid(int row, int column);
void Reset(void);

int main(void) {
    scanf("%d", &n);
    diff = (int*) malloc(sizeof(int)*n);
    sum = (int*) malloc(sizeof(int)*n);
    visit_col = (bool*) malloc(sizeof(bool)*n);
    Reset();
    Visit(0);
    printf("%d solution\n", sol_cnt);

    free(diff);
    free(sum);
    free(visit_col);
}

void Visit(int row) {
    if(row == n) {
        sol_cnt++;
        printf("Found\n");
        return;
    }


    for(int i = 0; i < n; i++) {
        if(valid(row, i)) {
            visit_col[i] = true;
            diff[diff_cnt] = row - i;
            sum[diff_cnt++] = row + i;
            printf("visit (%d, %d)\n", row, i);
            Visit(row+1);
            visit_col[i] = false;
            diff[--diff_cnt] = INT_MAX;
            sum[diff_cnt] = INT_MAX;
        }
    }
}

bool valid(int row, int column) {
    int difference = row - column;
    int summation = row + column;
    if(visit_col[column] == false) {
        for(int i = 0; i < diff_cnt; i++) {
            if(difference == diff[i] || summation == sum[i]) {
                return false;
            }
        }
        return true;
    }else 
        return false;
}

void Reset(void) {
    memset(diff, INT_MAX, sizeof(int)*n);
    memset(sum, INT_MAX, sizeof(int)*n);
    memset(visit_col, false, sizeof(bool)*n);
}