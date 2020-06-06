#include <stdio.h>
#include <gc/gc.h>

#include "p1.h"

int main()
{
    TList list;
    create_list(&list);
    append_node(&list, 2);
    append_node(&list, 5);
    append_node(&list, 7);
    append_node(&list, 12);
    append_node(&list, 10);
    append_node(&list, 6);
    append_node(&list, 4);
    append_node(&list, 1);
    show_list(list);
    biotonic_sort(&list);
    show_list(list);
    return 0;
}

void biotonic_sort(TList* ptr_list)
{
    TNode * runner = *ptr_list;
    // si la lista esta vacia o contiene un solo elemento no hacer nada
    if (runner == NULL || runner->next == NULL) return;
    // verificar si el orden es descendente desde el principio
    // si lo es, solo hacemos reverse a la lista
    if (runner->data > runner->next->data) {
        reverse(ptr_list);
        return;
    }
    while (runner->next != NULL) {
        // si llegamos a un nodo que el cual su data es menor
        // que el nodo anterior, salimos del bucle
        if (runner->prev != NULL) {
            if (runner->data < runner->prev->data) {
                break;
            }
        }
        runner = runner->next;
    }
    // si llegamos al final de la lista, no hay nada que hacer
    // puesto que ya esta ordenada
    if (runner->next == NULL) {
        return;
    }
    // dividir la lista en 2
    runner->prev->next = NULL;
    runner->prev = NULL;
    // combinar las nuevas 2 listas
    *ptr_list = merge_list(*ptr_list, runner);
}

TList merge_list(TNode* a, TNode* b)
{
    TNode * result = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (a->data <= b->data) {
        result = a;
        result->next = merge_list(a->next, b);
    } else {
        result = b;
        result->next = merge_list(a, b->next);
    }

    return result;
}

void reverse(TList* ptr_list)
{
    TNode * tmp = NULL;
    TNode * curr = *ptr_list;

    while (curr != NULL) {
        tmp = curr->prev;
        curr->prev = curr->next;
        curr->next = tmp;
        curr = curr->prev;
    }

    if (tmp != NULL)
        *ptr_list = tmp->prev;
}

void create_list(TList* ptr_list)
{
    *ptr_list = NULL;
}

void append_node(TList* ptr_list, int data)
{
    TNode * new_node = GC_malloc(sizeof(TNode));
    TNode * runner = *ptr_list;
    new_node->data = data;
    new_node->next = NULL;

    if (*ptr_list == NULL) {
        new_node->prev = NULL;
        *ptr_list = new_node;
        return;
    }

    while (runner->next != NULL)
        runner = runner->next;

    runner->next = new_node;

    new_node->prev = runner;
}

void show_list(TList list)
{
    TNode* ptr_runner = list;
    while (ptr_runner) {
        printf("%d -> ", ptr_runner->data);
        ptr_runner = ptr_runner->next;
    }
    printf("NULL\n");
}

void insert_begin(TList *ptr_list, int data)
{
    TNode* new_node = GC_malloc(sizeof(TNode));
    new_node->data = data;
    new_node->next = (*ptr_list);
    new_node->prev = NULL;
    if ((*ptr_list) != NULL)
        (*ptr_list)->prev = new_node;
    (*ptr_list) = new_node;
}