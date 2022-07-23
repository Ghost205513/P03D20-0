#include <stdio.h>
#define columns 25
#define rows 80

void func_print(int *matrix[columns][rows]);

int main() {
    int matrix[columns][rows];
    func_print(matrix[columns][rows]);

return 0;
}

void func_print(int *matrix[columns][rows]) {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
