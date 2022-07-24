#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "stack.h"

#define WIGHT 80
#define HEIGHT 25

// Операторы
// Приоритет Оператор Ассоциативность
// 4 ! правая
// 3 * / % левая
// 2 + - левая
// 1 = левая

/*
 + -1
 - -2 (унарный) -3 (бинарный)
 * -4
 / -5
 ( -6
 ) -7
 sin -8
 cos -9
 tan -10
 ctg -11
 sqrt -12
 ln -13
 x -14
*/

int priorites(int token) {
    switch (token) {
        case
    }
}

#define is_operator(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')

int *read_tokens(char *input, int *amount_tokens) {
    int len = (int) strlen(input), flag = 0;
    int *tokens = NULL;
    
    *amount_tokens = 0;
    
    for (int i = 0; i < len; ) {
            if (len - i > 2 && is_operator(input[i])) {
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
                
                while('0' <= input[i] && input[i] <= '9' && i < len) {
                    digit *= 10;
                    digit += input[i] - '0';
                    i++;
                }

                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = digit;
                (*amount_tokens)++;
            } else if ((len - i > 5) && strncmp(input + i, "sqrt", 4) == 0) {
                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = -12;
                (*amount_tokens)++;
                i += 4;
            } else if ((len - i > 3) && (strncmp(input + i, "ln", 2) == 0)) {
                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = -13;
                (*amount_tokens)++;
                i += 2;
            } else if ((strncmp(input + i, "sin", 3) == 0) && (len - i > 4)) {
                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = -8;
                (*amount_tokens)++;
                i += 3;
            } else if ((strncmp(input + i, "cos", 3) == 0) && (len - i > 4)) {
                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = -9;
                (*amount_tokens)++;
                i += 3;
            } else if ((strncmp(input + i, "tan", 3) == 0) && (len - i > 4)) {
                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = -10;
                (*amount_tokens)++;
                i += 3;
            } else if ((strncmp(input + i, "ctg", 3) == 0) && (len - i > 4)) {
                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = -11;
                (*amount_tokens)++;
                i += 3;
            } else if (input[i] == 'x') {
                tokens = realloc(tokens, (*amount_tokens + 1) * sizeof(int));
                tokens[*amount_tokens] = -14;
                (*amount_tokens)++;
                i++;
            } else if (input[i] == ' ' || input[i] == '\t'){
                i++;
            } else {
                flag = 1;
            }
    }

    if (flag) {
        *amount_tokens = 0;
        free(tokens);
        tokens = NULL;
    }
    
    return tokens;
}

int shunting_yard(char *input, struct stack *result) {
    int amount_tokens = 0, i = 0, amount_output = 0, flag = 0;
    int *tokens = read_tokens(input, &amount_tokens);
    struct stack *temp_stack = NULL;

    if (!tokens) {
        flag = 1;
    } else {
        while (i < amount_tokens) {
            if (tokens[i] >= -1) {
                output = realloc(output, (amount_output + 1) * sizeof(int));
                output[amount_output] = tokens[i];
                amount_output++;
            } else if (-14 < tokens[i] && tokens[i] < -7) {
                push(result, tokens[i]);
            }
        }
    }

    return flag;
}

int **function2matrix(struct stack *result) {
    struct stack *temp = NULL, *current = result;
    int **matrix = calloc(HEIGHT, sizeof(int *));

    for (int i = 0; i < HEIGHT; i++)
        matrix[i] = calloc(WIGHT, sizeof(int));

    for (int i = 0; i < WIGHT; i++) {
        int flag = 0;
        
        while (current) {
            if (current->data) {
                push(temp, current->data);
            } else {
                switch ((int) current->data) {
                    double x2;
                    double x1;
                    double x;
                    case -1:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        push(temp, x1 - x2);
                        break;
                    case -2:
                        x = temp->data;
                        temp = pop(temp);
                        push(temp, -x);
                        break;
                    case -3:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        push(temp, x1 + x2);
                        break;
                    case -4:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        push(temp, x1 * x2);
                        break;
                    case -5:
                        x2 = temp->data;
                        temp = pop(temp);
                        x1 = temp->data;
                        if (x2)
                            push(temp, x1 / x2);
                        else
                            flag = 1;
                        break;
                    case -8:
                        x = temp->data;
                        temp = pop(temp);
                        push(temp, sin(x));
                        break;
                    case -9:
                        x = temp->data;
                        temp = pop(temp);
                        push(temp, cos(x));
                        break;
                    case -10:
                        x = temp->data;
                        temp = pop(temp);
                        if (cos(x))
                            push(temp, tan(x));
                        else
                            flag = 1;
                        break;
                    case -11:
                        x = temp->data;
                        temp = pop(temp);
                        if (sin(x))
                            push(temp, cos(x) / sin(x));
                        else
                            flag = 1;
                        break;
                    case -12:
                        x = temp->data;
                        temp = pop(temp);
                        if (x)
                            push(temp, sqrt(x));
                        else
                            flag = 1;
                        break;
                    case -13:
                        x = temp->data;
                        temp = pop(temp);
                        if (x)
                            push(temp, log(x));
                        else
                            flag = 1;
                        break;
                    case -14:
                        push(temp, i * 4.0 * M_PI / 79.0);
                        break;
                }
            }
            if (flag)
                break;
            current = current->next;
        }
        
        if (!flag) {
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
