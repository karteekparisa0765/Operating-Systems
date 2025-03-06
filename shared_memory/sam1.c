#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 2

int arr[] = {4, 5, 7, 8, 9, 1};
int size = sizeof(arr) / sizeof(arr[0]);

typedef struct {
    int start;
    int end;
} threadargs;

void merge(int start, int mid, int end) {
    int left_size = mid - start + 1;
    int right_size = end - mid;
    int left[left_size], right[right_size];

    // Copying data into temporary arrays
    for (int i = 0; i < left_size; i++) {
        left[i] = arr[start + i];
    }
    for (int i = 0; i < right_size; i++) {
        right[i] = arr[mid + 1 + i];
    }

    // Merge two sorted halves
    int i = 0, j = 0, k = start;
    while (i < left_size && j < right_size) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }
    while (i < left_size) {
        arr[k++] = left[i++];
    }
    while (j < right_size) {
        arr[k++] = right[j++];
    }
}

void *sort_part(void *args) {
    threadargs *arg = (threadargs *)args;
    int start = arg->start;
    int end = arg->end;

    // Insertion sort for small sections
    for (int i = start + 1; i <= end; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    threadargs args[NUM_THREADS];

    int mid = size / 2 - 1;

    // Assign range for the first thread
    args[0].start = 0;
    args[0].end = mid;
    pthread_create(&threads[0], NULL, sort_part, &args[0]);

    // Assign range for the second thread
    args[1].start = mid + 1;
    args[1].end = size - 1;
    pthread_create(&threads[1], NULL, sort_part, &args[1]);

    // Wait for sorting threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    // Merge the two sorted halves
    merge(0, mid, size - 1);

    // Print sorted array
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

