/*
 * Estrategia:
 *
 * Las estructuras son las mismas a las vistas en clase, con modificacion
 * para adaptar a la cantidad de datos que se tiene
 *
 * Para poder encontrar si hay cruce se crea una
 * variable runner el cual va a navegar el arbol y si encuentra
 * un nodo con el mismo dia y hora devolver true y si no hay colision
 * devolver false. Finalmente insertar un nodo de manera iterativa
 * en el arbol utilizando las funciones dadas en clase.
 *
 * Para modificar los estados, se crea un bucle infinito, se obtiene
 * una referencia al nodo que se desea modificar usando una funcion
 * auxiliar y finalmente se modifica el estado.
 *
 * Para mostrar el reporte se crea una funcion simple recursiva
 * la cual vimos en clase.
 */

#include <stdlib.h>
#include <stdio.h>

#include "p1.h"

int main()
{
    // inicializacion del arbol de citas
    TBinaryTree * citas;
    create_binary_tree(&citas);

    // Ingreso de datos
    int num = 1;
    int cod, dia, hora;
    while (true) {
        printf("Ingrese informacion para la cita %d (Ingrese -1 para terminar):\n", num);
        printf("Codigo del paciente: ");
        scanf("%d", &cod);
        if (cod == -1) break;
        if (cod < 0) {
            printf("Solo se permiten codigos positivos!\n");
            continue;
        }
        printf("Dia de la cita (0 = Lunes, 1 = Martes, 2 = Miercoles, 3 = Jueves, 4 = Viernes): ");
        scanf("%d", &dia);
        if (!(0 <= dia && dia <= 4)) {
            printf("Error en el ingreso del dia!\n");
            continue;
        }
        printf("Hora de la cita (08:00 -> 18:00): ");
        scanf("%d", &hora);
        if (!(8 <= hora && hora <= 18)) {
            printf("Error en el ingreso de la hora!\n");
            continue;
        }
        if (!insert(&citas, cod, dia, hora)) {
            continue;
        }
        num++;
    }

    // Registrar estados
    registro_estado(&citas);

    // Mostrar el reporte de citas
    printf("\nReporte de citas:\n");
    print_reporte(citas->root);

    // Liberar la memoria del arbol de citas
    if (citas)
        free_tree(&citas->root);

    return 0;
}

// funcion para modificar el estado de una funcion
void registro_estado(TBinaryTree** tree)
{
    int cod, dia, hora;
    while (true) {
        // ingreso de datos
        printf("\nIngrese informacion de la cita a modificar (Ingrese -1 para terminar):\n");
        printf("Codigo del paciente: ");
        scanf("%d", &cod);
        if (cod == -1) break;
        printf("Dia de la cita (0 = Lunes, 1 = Martes, 2 = Miercoles, 3 = Jueves, 4 = Viernes): ");
        scanf("%d", &dia);
        printf("Hora de la cita (08:00 -> 18:00): ");
        scanf("%d", &hora);
        // obtenemos el nodo con la informacion brindad
        TNode * found = NULL;
        get_node(*tree, &found, cod, dia, hora);
        // si no la encontramos, reiniciar el bucle
        if (!found) {
            printf("Cita no encontrada!\n");
            continue;
        }
        // modificar el estado del nodo
        printf("Ingrese el nuevo estado (0 = A tiempo, 1 = Retraso, 2 = No llego): ");
        scanf("%d", &found->est);
    }
}

// funcion para liberar memoria, usando postorden
void free_tree(TNode** root)
{
    TNode * node = *root;

    if (!node) return;

    free_tree(&node->left);
    free_tree(&node->right);

    free(*root);
    *root = NULL;
}

// funcion auxiliar para obtener el nodo con la informacion requerida
void get_node(TBinaryTree* tree, TNode** node, int cod, int dia, int hora)
{
    TNode * runner = tree->root;

    while (runner) {
        // si llegamos aca, es posible que se encontro, todo depende del
        // codigo ahora
        if (runner->dia == dia && runner->hora == hora) {
            if (runner->cod != cod) {
                runner = NULL;
            }
            break;
        }

        if (dia < runner->dia ||
            (dia == runner->dia) && hora <= runner->hora) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    *node = runner;
}

// funcion para verificar si hay cruce
bool hay_cruce(TBinaryTree* tree, int dia, int hora)
{
    TNode * runner = tree->root;

    while (runner) {
        if (runner->dia == dia && runner->hora == hora) return true;

        if (dia < runner->dia ||
                (dia == runner->dia) && hora <= runner->hora) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    return false;
}

// funcion para insertar en el arbol
// version del prof baldeon modificada para poder verificar
// una condicion de cruce
bool insert(TBinaryTree** tree, int cod, int dia, int hora)
{
    if (hay_cruce(*tree, dia, hora)) {
        printf("Ya hay una cita en el dia y hora pedidos.\n");
        return false;
    }

    TNode * father = NULL;
    TNode * runner = (*tree)->root;

    while (runner) {
        father = runner;
        if (dia < runner->dia ||
            (dia == runner->dia && hora <= runner->hora)) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    TNode * node = malloc(sizeof(TNode));
    node->cod = cod;
    node->dia = dia;
    node->hora = hora;
    node->est = 2;

    if (!father) {
        (*tree)->root = node;
    } else {
        if (dia < father->dia ||
            (dia == father->dia && hora <= father->hora)) {
            father->left = node;
        } else {
            father->right = node;
        }
    }

    return true;
}

// imprimir reporte en orden
void print_reporte(TNode* node)
{
    if (!node) return;
    print_reporte(node->left);
    printf("Paciente: %d\n", node->cod);
    printf("Dia: %s\n", dias[node->dia]);
    printf("Hora: %d\n", node->hora);
    printf("Estado: %s\n\n", estados[node->est]);
    print_reporte(node->right);
}

// inicializar un arbol asignando memoria suficiente
void create_binary_tree(TBinaryTree** tree)
{
    *tree = malloc(sizeof(TBinaryTree));
    (*tree)->root = NULL;
}