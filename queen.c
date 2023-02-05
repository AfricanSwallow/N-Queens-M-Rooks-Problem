//Only rooks
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool visited_column[4] = {0};
int dif[4] = {0};
int count = 0;
void f(int row);

int main(void) {
    f(0);
    printf("count = %d\n", count);
}

void f(int row) {
    //Basis Step
    if(row == 3) {
        count++;
        return;
    }

    //Recursive Step
    for(int i = 0; i < 4; i++) {
        if(visited_column[i] == false) {
            visited_column[i] = true;
            f(row+1);
            visited_column[i] = false;
        }
    }

}