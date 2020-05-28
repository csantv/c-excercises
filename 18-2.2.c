#include <stdio.h>

void print_arr(int* arr, int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void inversion_negativa_arr(int* arr, int begin, int end, int* valor)
{
    if (begin == end) {
        if (arr[begin] < 0) {
            (*valor) += arr[begin] * -1;
        } else {
            (*valor) += arr[begin];
        }
        return;
    }
    int mid = (begin + end) / 2;

    inversion_negativa_arr(arr, begin, mid, valor);
    inversion_negativa_arr(arr, mid + 1, end, valor);
}

void inversion_negativa(int k, int n, int arr[n][k], int* valores)
{
    for (int i = 0; i < n; ++i) {
        int count = 0;
        inversion_negativa_arr(arr[i], 0, k - 1, &count);
        valores[i] = count;
    }
}

void max_inversion_negativa(int k, int n, int arr[n][k])
{
    int valores[n];
    inversion_negativa(k, n, arr, valores);
    int max = 0, max_index = -1;
    for (int i = 0; i < n; ++i) {
        int val = valores[i];
        if (val > max) {
            max = val;
            max_index = i;
        }
    }
    printf("El cromosoma con mayor valor: ");
    print_arr(arr[max_index], k);
    printf("Valor: %d\n", max);
}

int main(int argc, char** argv)
{
    int k, n;
    scanf("%d %d", &n, &k);
    int arr[n][k];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }
    max_inversion_negativa(k, n, arr);
    return 0;
}