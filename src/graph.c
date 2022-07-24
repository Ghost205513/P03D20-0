#include <string.h>
#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "queue.h"

#define WIDHT 80
#define HEIGHT 25
#define is_operator(x) (-5 <= x && x <= -1)
#define is_operator_c(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
#define is_function(x) (-13 <= x && x <= -8)

char *readline_();
int priority(int token);
int associativity(int token);
void print(int **matrix);
int *read_tokens(char *input, int *amount_tokens);
struct queue *shunting_yard(char *input, int *flag);
int **function2matrix(struct queue *result);
void free_matrix(int **matrix);

int main() {
    int flag;
    char *input = readline_();
    struct queue *result = NULL;
    result = shunting_yard(input, &flag);

    if (flag) {
        printf("n/a\n");
    } else {
        int **matrix = function2matrix(result);
        print(matrix);
        free_matrix(matrix);
    }

    free(input);
    free_queue(result);

    return 0;
}

char *readline_() {
    char buf[81] = {0};
    char *res = NULL, *tmp;
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
            tokens = realloc(res, str_len + 1);
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

int priority(int token) {
    int ans;

    switch (token) {
        case -2:
            ans = 3;
            break;
        case -4:
        case -5:
            ans = 2;
            break;
        case -1:
        case -3:
            ans = 1;
            break;
    }

    return ans;
}

int associativity(int token) {
    int ans;

    switch (token) {
        case -1:
        case -3:
        case -4:
        case -5:
            ans = 0;
            break;
        case -2:
            ans = 1;
            break;
    }

    return ans;
}

void print(int **matrix) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDHT; j++) {
            if (matrix[i][j])
                printf("*");
            else
                printf(".");
        }

        printf("\n");
    }
}

int *read_tokens(char *input, int *amount_tokens) {
    int len = (int) strlen(input), flag = 0;
    int *tokens = NULL, *tmp;

    *amount_tokens = 0;

    for (int i = 0; i < len; ) {
         if (len - i >= 1 && is_operator_c(input[i])) {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));

            switch (input[i]) {
                case '+':
                    tokens[*amount_tokens] = -1;
                    break;
                case '-':
                    if (tokens[*amount_tokens - 1] > -1)
                        tokens[*amount_tokens] = -3;
                    else
                        tokens[*amount_tokens] = -2;
                    break;
                case '*':
                    tokens[*amount_tokens] = -4;
                    break;
                case '/':
                    tokens[*amount_tokens] = -5;
                    break;
                case '(':
                    tokens[*amount_tokens] = -6;
                    break;
                case ')':
                    tokens[*amount_tokens] = -7;
                    break;
            }

            (*amount_tokens)++;
            i += 1;
        } else if ('0' <= input[i] && input[i] <= '9') {
            int digit = 0;

            while ('0' <= input[i] && input[i] <= '9' && i < len) {
                digit *= 10;
                digit += input[i] - '0';
                i++;
            }

            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = digit;
            (*amount_tokens)++;
        } else if ((len - i >= 4) && strncmp(input + i, "sqrt", 4) == 0) {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = -12;
            (*amount_tokens)++;
            i += 4;
        } else if ((len - i >= 2) && (strncmp(input + i, "ln", 2) == 0)) {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = -13;
            (*amount_tokens)++;
            i += 2;
        } else if ((strncmp(input + i, "sin", 3) == 0) && (len - i >= 3)) {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = -8;
            (*amount_tokens)++;
            i += 3;
        } else if ((strncmp(input + i, "cos", 3) == 0) && (len - i >= 3)) {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = -9;
            (*amount_tokens)++;
            i += 3;
        } else if ((strncmp(input + i, "tan", 3) == 0) && (len - i >= 3)) {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = -10;
            (*amount_tokens)++;
            i += 3;
        } else if ((strncmp(input + i, "ctg", 3) == 0) && (len - i >= 3)) {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = -11;
            (*amount_tokens)++;
            i += 3;
        } else if (input[i] == 'x') {
            tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
            tokens[*amount_tokens] = -14;
            (*amount_tokens)++;
            i++;
        } else if (input[i] == ' ' || input[i] == '\t') {
            i++;
        } else {
            flag = 1;
            i++;
        }
    }

    if (flag) {
        *amount_tokens = 0;
        free(tokens);
        tokens = NULL;
    }

    return tokens;
}

struct queue *shunting_yard(char *input, int *flag) {
    struct queue * result = NULL;
    int amount_tokens = 0;
    int *tokens = read_tokens(input, &amount_tokens);
    struct stack *temp_stack = NULL;

    *flag = 0;

    if (!tokens) {
        *flag = 1;
    } else {
        int i = 0;
        while (i < amount_tokens) {
            if (tokens[i] > -1 || tokens[i] == -14) {
                result= push_queue(result, tokens[i]);
            } else if (is_function(tokens[i])) {
                temp_stack = push(temp_stack, tokens[i]);

            } else if (is_operator(tokens[i])) {
                while (temp_stack && is_operator(temp_stack->data) &&
                (priority(tokens[i]) < priority((int) temp_stack->data) ||
                (priority(tokens[i]) == priority((int) temp_stack->data) && associativity(tokens[i]) == 0))) {
                    result = push_queue(result, (int) temp_stack->data);
                    temp_stack = pop(temp_stack);
                }

                temp_stack = push(temp_stack, (double) tokens[i]);
            } else if (tokens[i] == -6) {
                temp_stack = push(temp_stack, tokens[i]);
            } else if (tokens[i] == -7) {
                int brace_flag = 1;

                while (temp_stack) {
                    if (temp_stack->data == -6) {
                        brace_flag = 0;
                        break;
                    } else {
                        result = push_queue(result, (int) temp_stack->data);
                        temp_stack = pop(temp_stack);
                    }
                }

                if (brace_flag) {
                    *flag = 1;
                    break;
                }

                temp_stack = pop(temp_stack);

                if (temp_stack && is_function(temp_stack->data)) {
                    result = push_queue(result, (int) temp_stack->data);
                    temp_stack = pop(temp_stack);
                }
            }

            i++;
        }

        if (!*flag) {
            while (temp_stack) {
                if (temp_stack->data == -6 || temp_stack->data == -7) {
                    *flag = 1;
                    break;
                }
                result = push_queue(result, (int) temp_stack->data);
                temp_stack = pop(temp_stack);
            }
        }

        free(tokens);
    }

    free_stack(temp_stack);
    return result;
}

int **function2matrix(struct queue *result) {
    int **matrix = calloc(HEIGHT, sizeof(int *));

    for (int i = 0; i < HEIGHT; i++)
        matrix[i] = calloc(WIDHT, sizeof(int));

    for (int i = 0; i < WIDHT; i++) {
        int flag = 0;
        struct stack *temp = NULL;
        struct queue *current = result;

        while (current) {
            if (current->data > 0) {
                temp = push(temp, current->data);
            } else {
                switch ((int) current->data) {
                    double x2;
                    double x1;
                    double x;
                    case -1:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        temp = pop(temp);
                        temp = push(temp, x1 + x2);
                        break;
                    case -2:
                        x = temp->data;
                        temp = pop(temp);
                        temp = push(temp, -x);
                        break;
                    case -3:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        temp = pop(temp);
                        temp = push(temp, x1 - x2);
                        break;
                    case -4:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        temp = pop(temp);
                        temp = push(temp, x1 * x2);
                        break;
                    case -5:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        temp = pop(temp);
                        if (x2)
                            temp = push(temp, x1 / x2);
                        else
                            flag = 1;
                        break;
                    case -8:
                        x = temp->data;
                        temp = pop(temp);
                        temp = push(temp, sin(x));
                        break;
                    case -9:
                        x = temp->data;
                        temp = pop(temp);
                        temp = push(temp, cos(x));
                        break;
                    case -10:
                        x = temp->data;
                        temp = pop(temp);
                        if (cos(x))
                            temp = push(temp, tan(x));
                        else
                            flag = 1;
                        break;
                    case -11:
                        x = temp->data;
                        temp = pop(temp);
                        if (sin(x))
                            temp = push(temp, cos(x) / sin(x));
                        else
                            flag = 1;
                        break;
                    case -12:
                        x = temp->data;
                        temp = pop(temp);
                        if (x)
                            temp = push(temp, sqrt(x));
                        else
                            flag = 1;
                        break;
                    case -13:
                        x = temp->data;
                        temp = pop(temp);
                        if (x)
                            temp = push(temp, log(x));
                        else
                            flag = 1;
                        break;
                    case -14:
                        temp = push(temp, i * 4.0 * M_PI / 79.0);
                        break;
                }
            }
            if (flag)
                break;
            current = current->next;
        }

        if (!flag) {
            if (0 <= (int) round(temp->data * 12.0) + 12 && (int) round(temp->data * 12.0) + 12 <= 24)
                matrix[(int) round(temp->data * 12.0) + 12][i] = 1;
        }

        free_stack(temp);
    }

    return matrix;
}

void free_matrix(int **matrix) {
    for (int i = 0; i < HEIGHT; i++)
        free(matrix[i]);

    free(matrix);
}
