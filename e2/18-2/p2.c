#include <stdio.h>
#include <stdlib.h>
#include <gc/gc.h>

#include "p2.h"

int count_vip = 0;

int main()
{
    TQueue queue;

    create_queue(&queue);
    enqueue(&queue, vip);
    enqueue(&queue, vip);
    enqueue(&queue, vip);
    enqueue(&queue, vip);
    enqueue(&queue, cliente);
    enqueue(&queue, no_cliente);
    enqueue(&queue, cliente);
    enqueue(&queue, vip);

    show_queue_elements(queue);
    for (int i = 0; i < 7; ++i) {
        dequeue(&queue);
        show_queue_elements(queue);
    }

    return 0;
}

void create_queue(TQueue* queue)
{
    *queue = NULL;
}

void dequeue(TQueue* queue)
{
    // no hacer nada si la cola esta vacia
    if (*queue == NULL) return;
    // obtener el mayor elemento de la cola
    // en esta cola el valor del nodo es la prioridad
    int max = max_queue_elem(*queue);
    // si pasaron 3 vips pasa 1 regular
    if (max != 0) {
        if (count_vip == 3) {
            max = 1;
            count_vip = 0;
        }
    }
    // desencolar la ultima aparicion del mayor elemento
    TQueueNode * runner = *queue, *prev = NULL, *tmp = NULL;
    while (runner != NULL) {
        if (runner->next != NULL) {
            if (runner->next->elem == max) {
                prev = runner;
                tmp = runner->next;
            }
        }
        runner = runner->next;
    }
    // asegurarnos de no asignar weas a NULL
    if (prev == NULL) {
        (*queue) = (*queue)->next;
    } else {
        prev->next = tmp->next;
    }
    // aumentar la cuenta de vips
    count_vip++;
}

// devolver el indice del ultimo mayor de la cola
int max_queue_elem(TQueue queue)
{
    int max = INT_MIN;
    while (queue != NULL) {
        if (queue->elem > max) {
            max = queue->elem;
        }
        queue = queue->next;
    }
    return max;
}

void enqueue(TQueue* queue, int val)
{
    TQueueNode * ptrNewNode = GC_malloc(sizeof(TQueueNode));
    ptrNewNode->elem = val;
    ptrNewNode->next = *queue;
    *queue = ptrNewNode;
}

void show_queue_elements(TQueue queue)
{
    while (queue != NULL) {
        printf(" %d ->", queue->elem);
        queue = queue->next;
    }
    printf(" NULL\n");
}