/*
 * Estrategia:
 * Hacer el ingreso de datos
 * Combinar todas las listas enlazadas en
 * la del lunes, para luego realizar bubble sort para
 * ordenar de acuerdo a lo pedido
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

// arreglo global para facilitar impresion
const char* dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes"
};

// definicion de las estructuras
typedef struct Tnode TNode;
typedef TNode* TList;

struct Tnode {
    int hora;
    int dia;
    TNode* next;
};

// prototype de funciones
void create_list(TList*);
void append_node(TList*, int, int);
void show_list(TList);
void combine_lists(TList[MAX]);
void sort_list(TList*);
void swap_nodes(TList*,int,int);
void free_list(TList*);

int main()
{
    // definir arreglo de listas
    TList entregas[MAX];
    // ingreso de datos
    for (int i = 0; i < MAX; ++i) {
        TList* list = &entregas[i];
        create_list(list);
        char ch = '\0';
        printf("%s: ", dias[i]);
        while (1) {
            if (ch == '\n') break;
            int input = -1;
            scanf("%d%c", &input, &ch);
            append_node(list, input, i);
        }
        sort_list(list);
    }
    // fusionar las listas
    combine_lists(entregas);
    // imprimir la lista resultante
    show_list(entregas[0]);
    // liberar las listas enlazadas
    // como la lista del lunes contiene todas las referencias
    // es suficiente liberar solo esa
    free_list(&entregas[0]);
    return 0;
}

void free_list(TList* list)
{
    TNode * runner = NULL;
    while ((*list) != NULL) {
        runner = *list;
        (*list) = (*list)->next;
        free(runner);
    }
}

// todas las listas se van a fusionar sobre la lista
// que corresponde al dia lunes
void combine_lists(TList entregas[MAX])
{
    TNode * runner = NULL;
    // primero combinar todas las listas en la del lunes
    // todas las listas se combinan con complejidad O(n)
    // se combinan las listas con horarios disjuntos tambien
    for (int i = 0; i < 5; ++i) {
        runner = entregas[i];
        while (runner->next) {
            runner = runner->next;
        }
        if (i + 1 < 5) {
            if (entregas[i + 1])
                runner->next = entregas[i + 1];
        }
    }
    // una vez combinados todos las listas
    // realizar un bubble sort de acuerdo a
    // lo requerido
    int sorted, i;
    TList* lun = &entregas[0];
    do {
        sorted = 1; i = 0;
        runner = entregas[0];
        while (runner != NULL) {
            if (!runner->next) break;
            if (runner->hora > runner->next->hora ||
                    (runner->hora == runner->next->hora && runner->dia > runner->next->dia)) {
                sorted = 0;
                swap_nodes(lun, i, i + 1);
            }
            runner = runner->next;
            i++;
        }
    } while (!sorted);
}

// usar bubble sort para ordenar las listas
void sort_list(TList* list)
{
    int sorted, i;
    TNode * runner = NULL;
    do {
        sorted = 1; i = 0;
        runner = *list;
        while (runner != NULL) {
            if (!runner->next) break;
            if (runner->hora > runner->next->hora) {
                sorted = 0;
                swap_nodes(list, i, i + 1);
            }
            runner = runner->next;
            i++;
        }
    } while (!sorted);
}

// intercambiar 2 nodos
// se intercambia la memoria, no los datos
void swap_nodes(TList * list, int x, int y)
{
    if (x == y) return;

    int i;

    i = 0;
    TNode * prevX = NULL, *currX = *list;
    while (currX && i != x) {
        prevX = currX;
        currX = currX->next;
        i++;
    }

    i = 0;
    TNode * prevY = NULL, *currY = *list;
    while (currY && i != y) {
        prevY = currY;
        currY = currY->next;
        i++;
    }

    if (prevX != NULL)
        prevX->next = currY;
    else
        *list = currY;

    if (prevY != NULL)
        prevY->next = currX;
    else
        *list = currX;

    if (!currX || !currY) return;

    TNode * temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

// crear una lista nula
void create_list(TList* ptr_list)
{
    *ptr_list = NULL;
}

// agregar un nuevo nodo a la lista
// seteando el valor de hora y dia
void append_node(TList* ptr_list, int hora, int dia)
{
    TNode * new_node = malloc(sizeof(TNode));
    new_node->hora = hora;
    new_node->dia = dia;
    new_node->next = NULL;
    TNode * ptrRunner = *ptr_list;
    TNode * ptr_last = NULL;

    while (ptrRunner) {
        ptr_last = ptrRunner;
        ptrRunner = ptrRunner->next;
    }

    if (ptr_last) {
        ptr_last->next = new_node;
    } else {
        *ptr_list = new_node;
    }
}

// funcion que muestra la lista resultado
// utiliza el array de char global
void show_list(TList list)
{
    TNode* runner = list;
    while (runner) {
        printf("%d (%s) ", runner->hora, dias[runner->dia]);
        runner = runner->next;
        if (runner)
            printf("-> ");
    }
    printf("\n");
}