#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

// Structure to pass data to threads
typedef struct {
    int *array;
    int start;
    int end;
    long long sum;
} ThreadData;

// Function that each thread will run
void *compute_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->sum = 0;
    for (int i = data->start; i < data->end; i++) {
        data->sum += data->array[i];
    }
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the number of elements (greater than 1000): ");
    scanf("%d", &n);

    if (n <= 1000) {
        printf("The number of elements should be greater than 1000.\n");
        return 1;
    }

    int *array = (int *)malloc(n * sizeof(int));
    if (array == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize the array with sample values
    for (int i = 0; i < n; i++) {
        array[i] = i + 1; 
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int elements_per_thread = n / NUM_THREADS;

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * elements_per_thread;
        thread_data[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * elements_per_thread;
        int ret = pthread_create(&threads[i], NULL, compute_sum, &thread_data[i]);
        if (ret) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    long long total_sum = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        int ret = pthread_join(threads[i], NULL);
        if (ret) {
            fprintf(stderr, "Error joining thread %d\n", i);
            return 1;
        }
        total_sum += thread_data[i].sum;
    }

    printf("Total sum: %lld\n", total_sum);

    free(array);
    return 0;
}
