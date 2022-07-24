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

char *readline_() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;

    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = (int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}
