// Copyright of Faisal Almashouq 444105697
#include <stdio.h>
#include <stdlib.h>

void load_data(int** data) {
    printf("Loading data");
}

int** bitonic_sort(int** data) {
    printf("Sorting data using Bitonic Merge Sort Algorithm");
    return data;
}
int main() {
    int **unsorted;
    load_data(unsorted);
    if ((sizeof(unsorted)/sizeof(unsorted[0])) % 2 != 0) {
        printf("Array length must be even");
        return -1;
    }
    

    int** sorted = bitonic_sort(unsorted);
    for (int i = 0; sorted[i] != NULL; i++) {
        printf("The new sorted data: %d ", *sorted[i]);
    }
    
    
    return 0;
}