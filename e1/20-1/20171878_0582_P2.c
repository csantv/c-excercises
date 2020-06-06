/*
 * Estrategia:
 *
 * Para encontrar la mejor posicion:
 * avanzar desde el ultimo elemento de la ultima columna
 * del tablero hasta la posicion (0,0), y cuando se encuentre
 * el primer casillero con suficiente espacio termina la funcion e
 * imprime lo pedido. Se debe saber que esta funcion modifica valores
 * pasados por referencia los cuales indican la posicion 'x' e 'y' en
 * el tablero. De esta manera podemos obtener la pila necesitada para poder
 * combinarla con la pila del robot
 *
 * Para combinar las pilas:
 * Combinar el nodo incial de la pila 'p'
 * con el nodo final de la pila 'u', luego
 * aplicar bubble sort a la pila 'u' para que este
 * ordenada
 */
#include <stdio.h>
#include <stdlib.h>

// estructuras necesarias
typedef struct QueueNode TQueueNode;
typedef TQueueNode * TQueue;

struct QueueNode {
    int elem;
    int max;
    TQueueNode * next;
};

// prototype de funciones
void create_queue(TQueue*);
void enqueue(TQueue*, int, int);
void join_queue(TQueue*, TQueue*);
void swap_nodes(TQueue*, int, int);
void sort_queue(TQueue*);
void show_queue_elements(TQueue);
void mejor_posicion(int n, TQueue[n][n], int, int, int, int*, int*);
void free_queue(TQueue* list);

int main()
{
    // ingreso de datos para el tablero
    // cada casillero tiene un TAD queue
    int n, t;
    printf("n = ");
    scanf("%d", &n);
    printf("t = ");
    scanf("%d", &t);
    printf("Ingrese tablero:\n");
    TQueue tablero[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            TQueue * queue = &tablero[i][j];
            create_queue(queue);
            int max;
            scanf("%d", &max);
            enqueue(queue, max, 0);
        }
    }
    // ingreso de la pila del robot
    printf("Ingrese la pila del robot\n");
    TQueue robot;
    create_queue(&robot);
    for (int i = 0; i < t; ++i) {
        int valor;
        scanf("%d", &valor);
        enqueue(&robot, t, valor);
    }
    int x = -1, y = -1;
    // obtener la mejor posicion
    mejor_posicion(n, tablero, t, n - 1, n - 1, &x, &y);
    // obtener la pila del tablero
    TQueue * pilaU = &tablero[x][y];
    // combinar ambas pilas
    join_queue(pilaU, &robot);
    // mostrar el resultado de la combinacion
    show_queue_elements(*pilaU);
    // finalmente liberar las pilas
    // como todo esta conectado a pilaU es suficiente
    // liberar esta misma
    free_queue(pilaU);
    return 0;
}

// liberar datos del queue
void free_queue(TQueue* list)
{
    TQueueNode * runner = NULL;
    while ((*list) != NULL) {
        runner = *list;
        (*list) = (*list)->next;
        free(runner);
    }
}

void mejor_posicion(int n, TQueue tablero[n][n], int t, int row, int col, int* x, int* y)
{
    // caso base, se encontro un x e y
    if ((*x) != -1 && (*y) != -1) {
        return;
    }

    // obtener el queue del casillero
    TQueue queue = tablero[col][row];

    // verificar si terminas o continuamos recursion
    if (queue->max >= t) {
        *x = col;
        *y = row;
        printf("El mejor espacio esta a %d pasos de distancia y acepta pilas de tamaño %d.\n", row + col, queue->max);
        return;
    } else {
        // si estamos en el y no encontramos nada
        // terminar el programa
        if (col == 0 && row == 0) {
            printf("No se encontro un lugar apropiado.\n");
            exit(1);
        }

        if (row == 0) {
            mejor_posicion(n, tablero, t, row - 1, n - 1, x, y);
        } else {
            mejor_posicion(n, tablero, t, row, col - 1, x, y);
        }
    }
}

// combina 2 queues en 1 sola y luego
// ordenar la queue resultado
void join_queue(TQueue* q1, TQueue* q2)
{
    // avanzar hasta el final de q1
    TQueueNode * runner = *q1;
    while (runner->next) {
        runner = runner->next;
    }
    // conectar el ultimo de q1 a q2
    runner->next = (*q2);
    (*q2) = NULL;
    sort_queue(q1);
}

// mostrar los datos que posee la cola
void show_queue_elements(TQueue queue)
{
    while (queue != NULL) {
        printf("Elemento: %d\n", queue->elem);
        queue = queue->next;
    }
}

// aplicar bubble sort a la cola
// intercambiando nodos mas no intercambiando datos
void sort_queue(TQueue* queue)
{
    int sorted, i;
    TQueueNode * runner = NULL;
    do {
        sorted = 1; i = 0;
        runner = *queue;
        while (runner != NULL) {
            if (!runner->next) break;
            if (runner->elem > runner->next->elem) {
                sorted = 0;
                swap_nodes(queue, i, i + 1);
            }
            runner = runner->next;
            i++;
        }
    } while (!sorted);
}

// funcion auxiliar para intercambiar nodos
// usada en la funcion sort_queue
void swap_nodes(TQueue* queue, int x, int y)
{
    if (x == y) return;

    int i;

    i = 0;
    TQueueNode * prevX = NULL, *currX = *queue;
    while (currX && i != x) {
        prevX = currX;
        currX = currX->next;
        i++;
    }

    i = 0;
    TQueueNode * prevY = NULL, *currY = *queue;
    while (currY && i != y) {
        prevY = currY;
        currY = currY->next;
        i++;
    }

    if (prevX != NULL)
        prevX->next = currY;
    else
        *queue = currY;

    if (prevY != NULL)
        prevY->next = currX;
    else
        *queue = currX;

    if (!currX || !currY) return;

    TQueueNode * temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

// crear una cola nueva
void create_queue(TQueue* queue)
{
    *queue = NULL;
}

// ingresar un nuevo dato a la cola
void enqueue(TQueue* queue, int max, int val)
{
    TQueueNode * ptrNewNode = malloc(sizeof(TQueueNode));
    ptrNewNode->max = max;
    ptrNewNode->elem = val;
    ptrNewNode->next = *queue;
    *queue = ptrNewNode;
}