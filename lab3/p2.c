#include <stdio.h>
#include <limits.h>

// copiar valores de un array de ints a otro
void copy_values(int num, int src[num], int dest[num])
{
    for (int i = 0; i < num; ++i) {
        dest[i] = src[i];
    }
}

// merge sort para matrices de acuerdo a un indice
// en este caso, ordenar de acuerdo al nivel
void merge(int num_con, int consult[num_con][4], int begin, int mid, int end)
{
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    int arr1[n1 + 1][4];
    int arr2[n2 + 1][4];

    // copy arrays
    for (int i = begin, j = 0; i <= mid; i++) {
        copy_values(4, consult[i], arr1[j]);
        j++;
    }

    for (int i = mid + 1, j = 0; i <= end; i++) {
        copy_values(4, consult[i], arr2[j]);
        j++;
    }

    arr1[n1][2] = INT_MAX;
    arr2[n2][2] = INT_MAX;

    int i = begin, k = 0, m = 0;
    while (i <= end) {
        // indice 2 es el nivel
        if (arr1[k][2] < arr2[m][2]) {
            copy_values(4, arr1[k], consult[i]);
            k++;
        } else {
            copy_values(4, arr2[m], consult[i]);
            m++;
        }
        i++;
    }
}

// merge sort basico
void merge_sort(int num_con, int consult[num_con][4], int begin, int end)
{
    if (begin == end) return;

    int mid = (begin + end) / 2;
    merge_sort(num_con, consult, begin, mid);
    merge_sort(num_con, consult, mid + 1, end);
    merge(num_con, consult, begin, mid, end);
}

// cuenta_ceros modificado para funcionar con matrices
int numero_consultores(int num_con, int consult[num_con][4], int k, int ini, int fin, int contador){
    if(ini>fin)return contador;
    int mid = (ini + fin) / 2;
    if(consult[mid][2] >= k)
        return numero_consultores(num_con, consult, k, ini, mid - 1, contador);
    else
        return numero_consultores(num_con, consult, k, mid + 1, fin, mid - ini + 1 + contador);
}

int main()
{
    // Ingreso de datos
    int N;
    printf("N = ");
    scanf("%d", &N);
    int consultores[N][4];
    printf("Ingrese la informacion de los consultores:\n");
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d %d", &consultores[i][0], &consultores[i][1], &consultores[i][2],
              &consultores[i][3]);
    }
    int exp, nivel, dinero;
    printf("\nRequerimientos \n");
    printf("Años de experiencia = ");
    scanf("%d", &exp);
    printf("Nivel = ");
    scanf("%d", &nivel);
    printf("Presupuesto = ");
    scanf("%d", &dinero);
    // ordenar de acuerdo al nivel
    merge_sort(N, consultores, 0, N - 1);
    // obtener la cantidad de consultores que cumplen
    // con la cantidad de años de experiencia
    int total_con = 0;
    int tmp_con = 0;
    for (int i = nivel; i <= 3; ++i) {
        tmp_con = numero_consultores(N, consultores, i, tmp_con, N - 1, 0);
        total_con += tmp_con;
    }
    // Retorno de resultados
    printf("Hay %d consultores para lo requerido.\n", total_con);
    return 0;
}
