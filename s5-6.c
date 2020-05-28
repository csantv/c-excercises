#include <stdio.h>

void num_inversiones(int* arr, int begin, int end, int total, int* count)
{
    if (begin == end) {
        int next = begin + 1;
        if (next < total) {
            if (next > begin && arr[next] < arr[begin]) {
                (*count)++;
            }
        }
        return;
    }

    int mid = (begin + end) / 2;

    num_inversiones(arr, begin, mid, total, count);
    num_inversiones(arr, mid + 1, end, total, count);
}

int main()
{

}