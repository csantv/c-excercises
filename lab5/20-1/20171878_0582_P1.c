/*
 * Estrategia: Problema de la mochila con backtracking
 * utilizando una funcion utilitaria para ambos casos, mandando
 * los flags respectivos.
 */

#include <stdio.h>

int is_valid(int P, int N, int tmp_p, int i, int sol[N], int proyectos[N][2])
{
    // verificar que no se paso del presupuesto
    if (tmp_p > P) return 0;

    // verificar indice del resultado
    if (i > N) return 0;

    // verificar que todos los proyectos tengan sus predecesores
    for (int j = 0; j < i; ++j) {
        int pred = proyectos[sol[j]][1];
        if (pred == -1) continue;
        int found = 0;
        for (int k = 0; k < i; ++k) {
            if (sol[k] == pred) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }

    return 1;
}

// cont es una variable flag para decidir que hacer durante cada iteracion
int selecciona_util(int P, int N, int tmp_p, int i, int sol[N], int prev_sol[N], int k, int proyectos[N][2], int* cont)
{
    if (k > N) return 0;

    if (is_valid(P, N, tmp_p, i, sol, proyectos)) {
        if (tmp_p == P) {
            // imprimir una vez nomas
            if (*cont <= 2) {
                printf("Hay soluciones:\n");
            }
            int same_ans = 0;
            if (prev_sol) {
                // verificar que la solucion anterior sea distinta
                int same = 1;
                for (int j = 0; j < i; ++j) {
                    if (sol[j] != prev_sol[j]) {
                        same = 0;
                        break;
                    }
                }
                same_ans = same;
            }

            // evitar repetir soluciones
            if (!same_ans) {
                for (int j = 0; j < i; ++j) {
                    printf("P%d ", sol[j]);
                }
                printf("\n");

                // copiar solucion anterior
                if (prev_sol) {
                    for (int j = 0; j < i; ++j) {
                        prev_sol[j] = sol[j];
                    }
                }
            }

            // si es 1, solo mostrar la primera solucion
            if (*cont == 1) return 1;

            // modificar la flag para todos
            *cont = 3;
        }

        // guardar valores
        sol[i] = k;
        tmp_p += proyectos[k][0];

        // probar la siguiente solucion posible
        if (selecciona_util(P, N, tmp_p, i + 1, sol, prev_sol, k + 1, proyectos, cont)) {
            return 1;
        } else {
            // backtrack
            sol[i] = -1;
            tmp_p -= proyectos[k][0];
            return selecciona_util(P, N, tmp_p, i, sol, prev_sol, k + 1, proyectos, cont);
        }
    }

    return 0;
}

void seleccion_una(int P, int N, int proyectos[N][2])
{
    int sol[N];
    for (int i = 0; i < N; ++i) {
        sol[i] = -1;
    }

    int cont = 1;
    if (!selecciona_util(P, N, 0, 0, sol, NULL, 0, proyectos, &cont)) {
        printf("No hay soluciones.\n");
    }
}

void seleccion_multiple(int P, int N, int proyectos[N][2])
{
    int sol[N];
    int prev_sol[N];
    for (int i = 0; i < N; ++i) {
        sol[i] = -1;
        prev_sol[i] = -1;
    }

    int cont = 2;
    if (selecciona_util(P, N, 0, 0, sol, prev_sol, 0, proyectos, &cont)) {
        printf("No hay soluciones.\n");
    }
}

int main()
{
    // Ingreso de datos
    /*
    int N, P;
    printf("Numero de proyectos: ");
    scanf("%d", &N);
    printf("Presupuesto: ");
    scanf("%d", &P);
    int proyectos[N][2];
    printf("Ingrese informacion de proyectos:\n");
    int i = 0;
    while (i < N) {
        printf("==> Proyecto %d\n", i);
        printf("Costo (c): ");
        scanf("%d", &proyectos[i][0]);
        int pred;
        printf("Predecesores: (-1 para ninguno)");
        scanf("%d", &pred);
        if (!(-1 < pred && pred <= 7)) {
            printf("Error en el ingreso de datos\n");
            continue;
        }
        proyectos[i][1] = pred;
        i++;
    }*/
    int N = 8, P = 10;
    int i;
    int proyectos[][2] = {
            {7,-1}, {1,-1}, {3, 1}, {2,-1}, {4,2}, {5,4},{1, -1},{5,6}
    };

    // funciones que solucionan
    seleccion_una(P, N, proyectos);

    seleccion_multiple(P, N, proyectos);
    return 0;
}