#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT 25
#define WIDTH 80

int priorites(int token);
int *read_tokens(char *input, int *amount_tokens);
int shunting_yard(char *input, struct stack *result);
void free_matrix(int **matrix);
struct stack *init(double data);
struct stack *push(struct stack *root, double data);
struct stack *pop(struct stack *root);
void free_stack(struct stack *root);

int main() {
    int flag = 1;
    



    return 0;
}

int input(char **t) {
    int size;
    size = 0;
    int flag;
    *t = malloc(sizeof(char));
    if ( t == NULL)
        flag = 0;
    while(1) {
        int s;
        s = getchar();
        if (s < '0' || s > '9') {
            if ( strchr())
        }
    }
}
