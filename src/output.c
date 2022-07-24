#include <stdio.h>
#define HEIGHT 25
#define WEIGHT 80

void func_print(int matrix);

int main() {
    int matrix[HEIGHT][WEIGHT];
    func_print(matrix[HEIGHT][WEIGHT]);

return 0;
}

void func_print(int matrix) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WEIGHT; j++) {
            if (matrix[i][j])
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}
