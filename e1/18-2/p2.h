#ifndef EXCERCISES_P2_H
#define EXCERCISES_P2_H

enum usuario {no_cliente = 0, cliente = 1, vip = 2};

typedef struct QueueNode TQueueNode;
typedef TQueueNode * TQueue;

struct QueueNode {
    int elem;
    TQueueNode * next;
};

void create_queue(TQueue*);
void enqueue(TQueue*, int);
void show_queue_elements(TQueue);
int is_empty(TQueue);
void dequeue(TQueue*);
int max_queue_elem(TQueue);

#endif
