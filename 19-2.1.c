#include <stdio.h>
#include <limits.h>

void print_arr(int* arr, int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int binary_search();

int buscar_productos(int N, int M, int almacen[N][M][2], int valor)
{
    // usar binary search
    int cantidad = 0;
    for (int i = 0; i < N; ++i) {
        if (binary_search() != -1) {
            printf("Coordenada")
        }
    }
}

void merge(int P, int palets[P][2], int begin, int mid, int end)
{
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    int arr1[n1 + 1][2];
    int arr2[n2 + 1][2];

    // copy arrays
    for (int i = begin, j = 0; i <= mid; i++) {
        arr1[j][0] = palets[i][0];
        arr1[j][1] = palets[i][1];
        j++;
    }

    for (int i = mid + 1, j = 0; i <= end; i++) {
        arr2[j][0] = palets[i][0];
        arr2[j][1] = palets[i][1];
        j++;
    }

    arr1[n1][0] = INT_MAX;
    arr2[n2][0] = INT_MAX;

    int i = begin, k = 0, m = 0;
    while (i <= end) {
        if (arr1[k][0] < arr2[m][0]) {
            palets[i][0] = arr1[k][0];
            palets[i][1] = arr1[k][1];
            k++;
        } else {
            palets[i][0] = arr2[m][0];
            palets[i][1] = arr2[m][1];
            m++;
        }
        i++;
    }
}

void merge_sort(int P, int palets[P][2], int begin, int end)
{
    if (begin == end) return;

    int mid = (begin + end) / 2;
    merge_sort(P, palets, begin, mid);
    merge_sort(P, palets, mid + 1, end);
    merge(P, palets, begin, mid, end);
}

void ordenar_almacen(int P, int palets[P][2], int M, int N, int almacen[N][M][2])
{
    // primero ordenar los palets y luego pasarlos al almacen
    merge_sort(P, palets, 0, P - 1);
    int row = 0, col = 0;
    for (int i = 0; i < P; ++i) {
        almacen[row][col][0] = palets[i][0];
        almacen[row][col][1] = palets[i][1];
        col++;
        if (col == M) {
            col = 0;
            row++;
        }
    }
}

int main()
{
    int P, N, M;
    printf("Numero de palets: ");
    scanf("%d", &P);
    printf("Informacion de palets: (codigo, cantidad)\n");
    int palets[P][2];
    for (int i = 0; i < P; ++i) {
        scanf("%d %d", &palets[i][0], &palets[i][1]);
    }
    printf("N = ");
    scanf("%d", &N);
    printf("M = ");
    scanf("%d", &M);
    int almacen[N][M][2];
    // inicializar todos los elementos de la matriz
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            almacen[i][j][0] = INT_MAX;
            almacen[i][j][1] = INT_MAX;
        }
    }
    ordenar_almacen(P, palets, M, N, almacen);
}
