#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <stdlib.h>

struct queue {
    int data;
    struct queue *next;
};

struct queue *push_queue(struct queue *root, int data);
void free_queue(struct queue* root);

#endif  // SRC_QUEUE_H_
