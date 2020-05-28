#include <stdio.h>

int dv_binary_search(int* arr, int begin, int end, int elem)
{
    if (begin > end) return -1;

    int mid = (begin + end) / 2;

    if (arr[mid] == elem) {
        return mid;
    } else if (arr[mid] < elem){
        return dv_binary_search(arr, mid + 1, end, elem);
    } else {
        return dv_binary_search(arr, begin, mid - 1, elem);
    }
}

void matrix_search(int N, int arr[N][N], int K)
{
    for (int i = 0; i < N; ++i) {
        int index = dv_binary_search(arr[i], 0, N - 1, K);
        if (index != -1) {
            printf("%d %d\n", i, index);
            return;
        }
    }
    // Si llegamos a aca, no se encontro el elemento
    printf("El elemento no se encuentra.\n");
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int arr[N][N];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &arr[i][j]);
        }
    }
    matrix_search(N, arr, K);
    return 0;
}
