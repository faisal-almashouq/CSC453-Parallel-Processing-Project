// Copyright of Faisal Almashouq 444105697
#include <stdio.h>
#include <stdlib.h>

int load_data(int *data) {
    printf("\nLoading data\n");

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("\nError opening file");
        exit(1);
    }

    int i = 0, num;
    while((fscanf(file, "%d", &num) == 1) && (i < 100)) {
        data[i++] = num;
        printf("%d ", num);
    }

    fclose(file);
    return i;
}

void compare_and_swap(int* data, int i, int j, int direction) {
    if((data[i] > data[j] && direction == 1) || (data[i] < data[j] && direction == -1)) {
        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}
void merge(int* data, int min, int size, int direction) {
    if (size > 1) {
        int k = size / 2;
        for (int i = 0; i < k; i++) {
            compare_and_swap(data, min + i, min + i + k, direction);
        }
        merge(data, min, k, direction);
        merge(data, min + k, k, direction);
    }
}
void bitonic_sort_recursive(int* data, int min, int size, int direction) {
    if (size > 1) {
        int k = size / 2;
        bitonic_sort_recursive(data, min, k, 1);
        bitonic_sort_recursive(data, min + k, k, -1);
        merge(data, min, size, direction);
    }
}

int* bitonic_sort(int* data, int size) {
    printf("\nSorting data using Bitonic Merge Sort Algorithm");
    bitonic_sort_recursive(data, 0, size, 1);

    return data;
}
int main() {
    int* unsorted = malloc(100 * sizeof(int));
    int size = load_data(unsorted);

    if (size % 2 != 0) {
        printf("\nArray length must be powers of 2");
        free(unsorted);
        return -1;
    }
    

    int* sorted = bitonic_sort(unsorted, size);

    printf("The new sorted data:\n");
    for (int i = 0; i < size; i++) {
         printf("%d " ,sorted[i]);
    }

    free(unsorted);
    free(sorted);
    return 0;
}