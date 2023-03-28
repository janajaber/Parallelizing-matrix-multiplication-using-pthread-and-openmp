#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define N 1000
#define NUM_THREADS 60

int A[N][N];
int B[N][N];
int C[N][N];

// Define a struct to hold the data that will be passed to each thread
typedef struct {
    int thread_id;
    int num_threads;
} thread_data;

// Define the function that each thread will run
void* multiply_matrices(void* arg) {
    thread_data* data = (thread_data*) arg;
    int start = data->thread_id * (N / data->num_threads);
    int end = start + (N / data->num_threads);
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the matrices with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Start the timer
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    // Multiply the matrices using pthreads
    pthread_t threads[NUM_THREADS];
    thread_data thread_args[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].thread_id = i;
        thread_args[i].num_threads = NUM_THREADS;
        pthread_create(&threads[i], NULL, multiply_matrices, &thread_args[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Stop the timer and print the elapsed time
    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Elapsed time using %d threads: %f seconds\n", NUM_THREADS, elapsed_time);
   
    return 0;
}
