#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

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
*/

//#define is_start_of_function(c) (c == 's' || c == 'c' || c == 't' || c == 'l')
#define is_operator(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
#define is_start_of_number(c) (c >= '0' && c <= '9')

int *read_tokens(char *input) {
    int len = (int) strlen(input);
    int flag = 0, amount_tokens = 0;
    int *tokens = NULL;
    char *token;

    for (int i = 0; i < len; ) {
            if ((len - i > 5) && strncmp(input + i, "sqrt", 4) == 0) {
                tokens = realloc(tokens, (amount_tokens + 1) * sizeof(int));
                tokens[amount_tokens] = -12;
                amount_tokens++;
                i += 4;
            }

            if (len - i > 4) {
                if (strncmp(input + i, "sin", 3) == 0) {
                    tokens = realloc(tokens, (amount_tokens + 1) * sizeof(int));
                    tokens[amount_tokens] = -8;
                    amount_tokens++;
                }else if (strncmp(input + i, "cos", 3) == 0) {
                    tokens = realloc(tokens, (amount_tokens + 1) * sizeof(int));
                    tokens[amount_tokens] = -9;
                    amount_tokens++;
                }else if (strncmp(input + i, "tan", 3) == 0) {
                    tokens = realloc(tokens, (amount_tokens + 1) * sizeof(int));
                    tokens[amount_tokens] = -10;
                    amount_tokens++;
                }else if (strncmp(input + i, "ctg", 3) == 0) {
                    tokens = realloc(tokens, (amount_tokens + 1) * sizeof(int));
                    tokens[amount_tokens] = -11;
                    amount_tokens++;
                }

                i += 3;
            }

            if ((len - i > 3) && (strncmp(input + i, "ln", 2) == 0)) {
                tokens = realloc(tokens, (amount_tokens + 1) * sizeof(int));
                tokens[amount_tokens] = -13;
                amount_tokens++;
                i += 2;
            }

            if (len - i > 2 && is_operator(input[i])) {
                tokens = realloc(tokens, (amount_tokens + 1) * sizeof(int));

                switch (input[i]) {
                    case '+':
                        tokens[amount_tokens] = -1;
                        break;
                    case '-':
                        if (tokens[amount_tokens - 1] > -1)
                            tokens[amount_tokens] = -3;
                        else
                            tokens[amount_tokens] = -2;
                        break;
                    case '*':
                        tokens[amount_tokens] = -4;
                        break;
                    case '/':
                        tokens[amount_tokens] = -5;
                        break;
                    case '(':
                        tokens[amount_tokens] = -6;
                        break;
                    case ')':
                        tokens[amount_tokens] = -7;
                        break;
                }

                amount_tokens++;
                i += 1;
            }

            if (47 < input[i] && input[i] < 58)
    }
}

int shunting_yard(char *input, struct stack *result) {

}














int op_preced(const char c)
{
    switch(c)
    {
        case '!':
            return 4;

        case '*':
        case '/':
        case '%':
            return 3;

        case '+':
        case '-':
            return 2;

        case '=':
            return 1;
    }
    return 0;
}

bool op_left_assoc(const char c)
{
    switch(c)
    {
        // лево-ассоциативные операторы
        case '*':
        case '/':
        case '%':
        case '+':
        case '-':
        case '=':
            return true;
            // право-ассоциативные операторы
        case '!':
            return false;
    }
    return false;
}

unsigned int op_arg_count(const char c)
{
    switch(c)
    {
        case '*':
        case '/':
        case '%':
        case '+':
        case '-':
        case '=':
            return 2;
        case '!':
            return 1;

        default:
            return c - 'A';
    }
    return 0;
}
#define is_function(c) (c >= 'A' && c <= 'Z')


bool shunting_yard(const char *input, char *output)
{
    const char *strpos = input, *strend = input + strlen(input);
    char c, stack[32], sc, *outpos = output;
    unsigned int sl = 0;
    while(strpos < strend)
    {
        c = *strpos;
        if(c != ' ')
        {
            // Если токен является числом (идентификатором), то добавить его в очередь вывода.
            if(is_ident(c))
            {
                *outpos = c; ++outpos;
            }
                // Если токен - функция, то положить его в стек.
            else if(is_function(c))
            {
                stack[sl] = c;
                ++sl;
            }
                //Если токен - разделитель аргументов функции (запятая):
            else if(c == ',')
            {
                bool pe = false;
                while(sl > 0)
                {
                    sc = stack[sl - 1];
                    if(sc == '(')
                    {
                        pe = true;
                        break;
                    }
                    else
                    {
                        // Пока на вершине не левая круглая скобка,
                        // перекладывать операторы из стека в очередь вывода.
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                }
                // Если не была достигнута левая круглая скобка, либо разделитель не в том месте
                // либо была пропущена скобка
                if(!pe)
                {
                    printf("Error: separator or parentheses mismatched\n");
                    return false;
                }
            }
                // Если токен оператор op1, то:
            else if(is_operator(c))
            {
                while(sl > 0)
                {
                    sc = stack[sl - 1];
                    // Пока на вершине стека присутствует токен оператор op2,
                    // а также оператор op1 лево-ассоциативный и его приоритет меньше или такой же чем у оператора op2,
                    // или оператор op1 право-ассоциативный и его приоритет меньше чем у оператора op2
                    if(is_operator(sc) &&
                       ((op_left_assoc(c) && (op_preced(c) <= op_preced(sc))) ||
                        (!op_left_assoc(c) && (op_preced(c) < op_preced(sc)))))
                    {
                        // Переложить оператор op2 из стека в очередь вывода.
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                    else
                    {
                        break;
                    }
                }
                // положить в стек оператор op1
                stack[sl] = c;
                ++sl;
            }
                // Если токен - левая круглая скобка, то положить его в стек.
            else if(c == '(')
            {
                stack[sl] = c;
                ++sl;
            }
                // Если токен - правая круглая скобка:
            else if(c == ')')
            {
                bool pe = false;
                // До появления на вершине стека токена "левая круглая скобка"
                // перекладывать операторы из стека в очередь вывода.
                while(sl > 0)
                {
                    sc = stack[sl - 1];
                    if(sc == '(')
                    {
                        pe = true;
                        break;
                    }
                    else
                    {
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                }
                // Если стек кончится до нахождения токена левая круглая скобка, то была пропущена скобка.
                if(!pe)
                {
                    printf("Error: parentheses mismatched\n");
                    return false;
                }
                // выкидываем токен "левая круглая скобка" из стека (не добавляем в очередь вывода).
                sl--;
                // Если на вершине стека токен - функция, положить его в очередь вывода.
                if(sl > 0)
                {
                    sc = stack[sl - 1];
                    if(is_function(sc))
                    {
                        *outpos = sc; ++outpos;
                        sl--;
                    }
                }
            }
            else
            {
                printf("Unknown token %c\n", c);
                return false; // Unknown token
            }
        }
        ++strpos;
    }
    // Когда не осталось токенов на входе:
    // Если в стеке остались токены:
    while(sl > 0)
    {
        sc = stack[sl - 1];
        if(sc == '(' || sc == ')')
        {
            printf("Error: parentheses mismatched\n");
            return false;
        }
        *outpos = sc; ++outpos;
        --sl;
    }

    *outpos = 0; // Добавляем завершающий ноль к строке
    return true;
}

bool execution_order(const char *input)
{
    printf("order: (arguments in reverse order)\n");
    const char *strpos = input, *strend = input + strlen(input);
    char c, res[4];
    unsigned int sl = 0, sc, stack[32], rn = 0;
    // Пока на входе остались токены
    while(strpos < strend)
    {
        // Прочитать следующий токен
        c = *strpos;
        // Если токен - значение или идентификатор
        if(is_ident(c))
        {
            // Поместить его в стек
            stack[sl] = c;
            ++sl;
        }
            // В противном случае, токен - оператор (здесь под оператором понимается как оператор, так и название функции)
        else if(is_operator(c) || is_function(c))
        {
            sprintf(res, "_%02d", rn);
            printf("%s = ", res);
            ++rn;
            // Априори известно, что оператор принимает n аргументов
            unsigned int nargs = op_arg_count(c);
            unsigned int Tnargs = nargs;
            // Если в стеке значений меньше, чем n
            if(sl < nargs)
            {
                // (ошибка) Недостаточное количество аргументов в выражении.
                return false;
            }
            // В противном случае, взять последние n аргументов из стека
            // Вычислить оператор, взяв эти значения в качестве аргументов
            if(is_function(c))
            {
                printf("%c(", c);
                while(nargs > 0)
                {
                    sc = stack[sl - nargs];
                    if(nargs > 1)
                    {
                        printf("%s, ", &sc);
                    }
                    else
                    {
                        printf("%s)\n", &sc);
                    }
                    --nargs;
                }
                sl -= Tnargs;
            }
            else
            {
                if(nargs == 1)
                {
                    sc = stack[sl - 1];
                    sl--;
                    printf("%c %s;\n", c, &sc);
                }
                else
                {
                    sc = stack[sl - 2];
                    printf("%s %c ", &sc, c);
                    sc = stack[sl - 1];
                    printf("%s;\n",&sc);
                    sl -= 2;

                }
            }
            // Если получены результирующие значения, поместить таковые в стек.
            stack[sl] = *(unsigned int*)res;
            ++sl;
        }
        ++strpos;
    }
    // Если в стеке осталось лишь одно значение,
    // оно будет являться результатом вычислений.
    if(sl == 1)
    {
        sc = stack[sl - 1];
        sl--;
        printf("%s is a result\n", &sc);
        return true;
    }
    // Если в стеке большее количество значений,
    // (ошибка) Пользователь ввёл слишком много значений.
    return false;
}

int main()
{
    // Имена функций: A() B(a) C(a, b), D(a, b, c) ...
    // идентификаторы: 0 1 2 3 ... and a b c d e ...
    // операторы: = - + / * % !
    const char *input = "(2 - 3 * 5) * 2 - 3";
    char output[128];
    printf("input: %s\n", input);
    if(shunting_yard(input, output))
    {
        printf("output: %s\n", output);
        execution_order(output);
    }
    return 0;
}
