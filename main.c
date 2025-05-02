#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10
#define ORIGINAL_ARRAY original_array1

int original_array1[ARRAY_SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
int original_array2[ARRAY_SIZE] = {5, 11, 14, 1, 17, 9, 10, 13, 16, 20};

int sorted_array[ARRAY_SIZE];

typedef struct ThreadArguments {
    int start_i;
    int end_i;
} ThreadArguments;

void insertion_sort(int array[], int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = array[i];
        int j = i - 1;

        while (j >= start && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void* merge_arrays(void* args) {
    int middle = ARRAY_SIZE / 2;
    int i = 0;
    int j = middle;
    int k = 0;

    while (i < middle && j < ARRAY_SIZE) {
        if (ORIGINAL_ARRAY[i] <= ORIGINAL_ARRAY[j]) {
            sorted_array[k++] = ORIGINAL_ARRAY[i++];
        } else {
            sorted_array[k++] = ORIGINAL_ARRAY[j++];
        }
    }

    while (i < middle) {
        sorted_array[k++] = ORIGINAL_ARRAY[i++];
    }

    while (j < ARRAY_SIZE) {
        sorted_array[k++] = ORIGINAL_ARRAY[j++];
    }

    pthread_exit(NULL);
}

void* sort_subarray(void* args) {
    ThreadArguments* thread_args = (ThreadArguments*)args;
    insertion_sort(ORIGINAL_ARRAY, thread_args->start_i, thread_args->end_i);
    pthread_exit(NULL);
}

int main() {

    printf("Original array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", ORIGINAL_ARRAY[i]);
    }
    printf("\n");

    ThreadArguments args1 = {0, (ARRAY_SIZE / 2) - 1}; // first half
    ThreadArguments args2 = {ARRAY_SIZE / 2, ARRAY_SIZE - 1}; // second half

    pthread_t thread1, thread2, merge_thread;

    // sorting halves
    pthread_create(&thread1, NULL, sort_subarray, (void*)&args1);
    pthread_create(&thread2, NULL, sort_subarray, (void*)&args2);

    // wait for the sorting threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // merging
    pthread_create(&merge_thread, NULL, merge_arrays, NULL);

    // wait for the merge thread to finish
    pthread_join(merge_thread, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", sorted_array[i]);
    }

    return 0;
}