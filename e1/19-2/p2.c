#include <stdio.h>
#include <math.h>
#include <gc/gc.h>

#include "p2.h"

#define MAX 20

int main(int argc, char** argv)
{
    int num_cajas;
    printf("Numero de cajas: ");
    scanf("%d", &num_cajas);
    if (num_cajas > MAX) {
        printf("Las cajas no pueden ser mas que %d.\n", MAX);
        return 1;
    }
    printf("Ingrese peso de cajas:\n");
    TList pesos; create_list(&pesos);
    // cargar los valores a la lista enlazada
    cargar_lista(&pesos, num_cajas);
    // maximizar los pesos en el camion
    int camion [4][3] = {
            {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}
    };
    maximizar_pesos(&pesos, camion, num_cajas);
    // mostrar distribucion del camion
    printf("Distribucion en el camion:\n");
    show_matrix(camion);
    return 0;
}

void show_matrix(int matrix[4][3])
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            int peso = matrix[j][i];
            if (!peso) {
                printf("%3c ", ' ');
            } else {
                printf("%-03d ", peso);
            }
        }
        printf("\n");
    }
}

void maximizar_pesos(TList* pesos, int camion[4][3], int num_cajas)
{
    int max_cajas = (num_cajas > 12) ? 12 : num_cajas;
    int buff[max_cajas];

    int selected = -1, max_prod = 0;
    // maximizar el peso en el camion usando el metodo de la mochila
    for (int i = 0; i < pow(2, max_cajas); ++i) {
        int_to_bin(i, max_cajas, buff);
        int partial_prod = 0, partial_weight = 0;
        for (int j = 0; j < max_cajas; ++j) {
            if (buff[j]) {
                TNode* node = get_node(pesos, j);
                partial_prod++;
                partial_weight += node->peso;
            }
        }
        if (partial_weight <= 2000 && partial_prod > max_prod) {
            selected = i;
            max_prod = partial_prod;
        }
    }
    // Asignar el peso de 0 a todos los nodos no seleccionados
    int_to_bin(selected, max_cajas, buff);
    for (int i = 0; i < max_cajas; ++i) {
        if (!buff[i]) {
            TNode* node = get_node(pesos, i);
            node->peso = 0;
        }
    }
    // ordenar lista
    order_list(pesos);
    // insertar datos en el camion
    TNode* runner = *pesos;
    for (int i = 0; i < 4; ++i) {
        for (int j = 2; j >= 0; --j) {
            camion[i][j] = runner->peso;
            runner = runner->next;
            if (!runner) {
                return;
            }
        }
    }
}

TNode* get_node(TList* ptr_list, int index)
{
    int i = 0;
    TNode* runner = *ptr_list;
    while (i < index && runner != NULL) {
        i++;
        runner = runner->next;
    }
    return runner;
}

void order_list(TList* ptr_list)
{
    int swapped;
    TNode *ptrRunner;
    TNode *ptrLast = NULL;

    do {
        swapped = 0;
        ptrRunner = *ptr_list;
        while (ptrRunner->next != ptrLast) {
            if (ptrRunner->peso < ptrRunner->next->peso) {
                swap_nodes(ptrRunner, ptrRunner->next);
                swapped = 1;
            }
            ptrRunner = ptrRunner->next;
        }
        ptrLast = ptrRunner;
    } while (swapped);
}

void swap_nodes(TNode* cur1, TNode* cur2)
{
    int tmp = cur1->peso;
    cur1->peso = cur2->peso;
    cur2->peso = tmp;
}

void cargar_lista(TList* ptr_list, int num_cajas)
{
    for (int i = 0; i < num_cajas; ++i) {
        int peso;
        scanf("%d", &peso);
        append_node(ptr_list, peso);
    }
}

void int_to_bin(unsigned int num, int size, int* out)
{
    unsigned int mask = 1U;
    for (int i = 0; i < size; ++i) {
        out[i] = (num & mask) ? 1 : 0;
        num >>= 1U;
    }
}

void create_list(TList* ptr_list)
{
    *ptr_list = NULL;
}

void append_node(TList* ptr_list, int data)
{
    TNode * new_node = GC_malloc(sizeof(TNode));
    new_node->peso = data;
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
