#include <stdio.h>
#include <gc/gc.h>

#include "p1.h"

int main()
{
    // ingreso de datos
    int x, y, monticulos = 0;
    printf("Ingrese las dimensiones de la matriz (x e y): ");
    scanf("%d %d", &x, &y);
    TList codigos[x];
    printf("Ingrese los codigos de los monticulos:\n");
    for (int i = 0; i < x; ++i) {
        TList* list = &codigos[i];
        create_list(list);
        for (int j = 0; j < y; ++j) {
            int value;
            printf("y=%d , x=%d: ", i + 1, j + 1);
            scanf("%d", &value);
            append_node(list, value);
        }
    }
    // ejecutar funcion
    recorrido(x, codigos, 0, x - 1, &monticulos);
    printf("\nNumero de monticulos: %d\n", monticulos);
    return 0;
}

void recorrido(int x, TList list_arr[x], int begin, int end, int* monticulos)
{
    // 2 casos base
    if (begin == end) {
        show_list(list_arr[begin]);
        (*monticulos) += list_size(list_arr[begin]);
        return;
    } else if (begin + 1 == end) {
        show_list(list_arr[begin]);
        (*monticulos) += list_size(list_arr[begin]);
        reverse(&list_arr[end]);
        show_list(list_arr[end]);
        (*monticulos) += list_size(list_arr[end]);
        return;
    }
    // primero mostrar la primera lista regularmente
    show_list(list_arr[begin]);
    (*monticulos) += list_size(list_arr[begin]);
    // mostrar el ultimo elemento de cada lista, luego eliminarlo
    for (int i = begin + 1; i <= end - 1; ++i) {
        print_and_remove_last(&list_arr[i]);
        (*monticulos)++;
    }
    // mostrar la ultima lista en reverso
    reverse(&list_arr[end]);
    show_list(list_arr[end]);
    (*monticulos) += list_size(list_arr[end]);
    // mostrar el primer elemento de cada lista
    for (int i = end - 1; i >= begin + 1; --i) {
        print_and_remove_first(&list_arr[i]);
        (*monticulos)++;
    }
    recorrido(x, list_arr, begin + 1, end - 1, monticulos);
}

// remueve el primer y ultimo elemento de la lista
void print_and_remove_first(TList* ptr_list)
{
    int first = (*ptr_list)->data;
    (*ptr_list) = (*ptr_list)->next;
    printf("%d ", first);
}

int list_size(TList ptr_list)
{
    TNode * ptr_runner = ptr_list;
    int count = 0;
    while (ptr_runner) {
        count++;
        ptr_runner = ptr_runner->next;
    }
    return count;
}

void print_and_remove_last(TList* ptr_list)
{
    TNode * runner = *ptr_list;
    TNode * prev;
    while (runner ->next) {
        prev = runner;
        runner = runner->next;
    }
    int last = runner->data;
    prev->next = NULL;
    printf("%d ", last);
}

void create_list(TList* ptr_list)
{
    *ptr_list = NULL;
}

void show_list(TList list)
{
    TNode* ptr_runner = list;
    while (ptr_runner) {
        printf("%d ", ptr_runner->data);
        ptr_runner = ptr_runner->next;
    }
}

void append_node(TList* ptr_list, int data)
{
    TNode * new_node = GC_malloc(sizeof(TNode));
    new_node->data = data;
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

void reverse(TList* ptr_list)
{
    TNode* prev = NULL;
    TNode* curr = *ptr_list;
    TNode* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *ptr_list = prev;
}