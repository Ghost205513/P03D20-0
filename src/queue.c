#include "queue.h"
#include <stdlib.h>

struct queue *init(int data) {
    struct queue *elements = NULL;

    elements = malloc(sizeof(struct queue));
    elements->data = data;
    elements->next = NULL;

    return elements;
}

struct queue *push_queue(struct queue *root, int data) {
    struct queue *new = init(data);
    struct queue *current = root;

    if (root) {
        while (current->next != NULL)
            current = current->next;

        current->next = new;
    } else {
        root = new;
    }

    return root;
}

struct queue *pop_queue(struct queue *root) {
    if (root) {
        struct queue *next = root->next;
        free(root);
        root = next;
    }

    return root;
}

void free_queue(struct queue *root) {
    struct queue *current = root, *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
