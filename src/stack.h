#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdlib.h>

struct stack {
    double data;
    struct stack *next;
};

struct stack *push(struct stack *root, double data);
struct stack *pop(struct stack *root);
void free_stack(struct stack *root);

#endif  // SRC_STACK_H_

