// Copyright of Faisal Almashouq 444105697 - Parallel VIA CUDA
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#define N 256


__global__ void bitonic_sort_device(int *d_data, int size) {
    int index = threadIdx.x;

    for(int group_size = 2; group_size <= size; group_size *=2){
        for(int swap_distance = group_size/2; swap_distance > 0; swap_distance /=2){
            
            if (index < size){
                int swap_index = index ^ swap_distance;

                if (swap_index > index){
                    int direction = (index / group_size) % 2 == 0;

                    if (((d_data[index] > d_data[swap_index]) && direction ==1) || ((d_data[index] < d_data[swap_index]) && direction ==0)){    
                        int temp = d_data[index];
                        d_data[index] = d_data[swap_index];
                        d_data[swap_index] = temp;
                    }
                }
            }    
        __syncthreads();
        }
    }
}

int load_data(int *unsorted) {
    FILE *file = fopen("data/data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int i = 0, num;
    printf("Unsored Array:\n");

    while((fscanf(file, "%d", &num) == 1) && (i < 100)) {
        unsorted[i++] = num;
        printf("%d ", num);
    }

    fclose(file);
    return i;
}

void bitonic_sort_host(int* unsorted, int* d_data, int* sorted, int size) {

    cudaMemcpy(d_data, unsorted, size * sizeof(int), cudaMemcpyHostToDevice);
    

    bitonic_sort_device<<<1, N>>>(d_data, size);

    cudaDeviceSynchronize();

    cudaMemcpy(sorted, d_data, size * sizeof(int), cudaMemcpyDeviceToHost);
}



int is_power_of_two(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int main() {
    int *unsorted = (int*)malloc(256 * sizeof(int)), *sorted = (int*)malloc(256 * sizeof(int));
    int *d_data;

    int size = load_data(unsorted);

    if (is_power_of_two(size) == 0) {
        printf("Array size must be a power of 2.\n");
        free(unsorted);
        free(sorted);
        return -1;
    }

    cudaMalloc((void**)&d_data, size * sizeof(int));

    bitonic_sort_host(unsorted, d_data, sorted, size);

    cudaFree(d_data);

    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", sorted[i]);
    }

    free(unsorted);
    free(sorted);
    return 0;
}