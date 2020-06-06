#include <stdio.h>
#include <gc/gc.h>

#include "p1.h"

int main()
{
    // Ingreso de datos
    int num_dias;
    printf("Ingrese el numero de dias: ");
    scanf("%d", &num_dias);
    TStack precios;
    create_stack(&precios);
    for (int i = 0; i < num_dias; ++i) {
        int precio;
        scanf("%d", &precio);
        push(&precios, precio);
    }
    // mostrar datos
    show_stack_elems(precios);
    return 0;
}

void push(TStack* ptr_stack, int precio)
{
    TStackNode * ptrNewNode;
    ptrNewNode = GC_malloc(sizeof(TStackNode));
    int base = 1;
    // setear los valores de intervalos
    TStackNode* cur = *ptr_stack;
    while (cur != NULL) {
        if (cur->data.precio < precio) {
            base++;
        }
        cur = cur->next;
    }
    dia_t data = {.precio = precio,.intervalos = base};
    ptrNewNode->data = data;
    ptrNewNode->next = *ptr_stack;
    *ptr_stack = ptrNewNode;
}

void create_stack(TStack* ptr_stack)
{
    *ptr_stack = NULL;
}

void show_stack_elems(TStack stack)
{
    if (stack == NULL) {
        return;
    }
    show_stack_elems(stack->next);
    printf("Precio: %d\nIntervalos: %d\n", stack->data.precio, stack->data.intervalos);
}