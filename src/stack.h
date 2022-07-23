#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdlib.h>

struct stack {
    int data;
    struct stack *next;
};

struct stack *init(int data);
struct stack *push(struct stack *root, int data);
struct stack *pop(struct stack *root);
void free_stack(struct stack *root);

#endif  // SRC_STACK_H_

