#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>


#define N 1000

int A[N][N];
int B[N][N];
int C[N][N];

int main() 
{
    int i,j,k;
    double start_time, end_time;
    double elapsed; 
    srand(time(NULL));
    int num_threads = 1; // set the number of threads to be used

    for (i= 0; i< N; i++)
        for (j= 0; j< N; j++)
        {
            A[i][j] = 2;
            B[i][j] = 2;
        }

    start_time = omp_get_wtime();
    omp_set_num_threads(num_threads); // set the number of threads
    #pragma omp parallel for private(i,j,k) shared(A,B,C) num_threads(num_threads)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            for (k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    end_time = omp_get_wtime();

    // print execution time
    printf("Execution time: %f seconds using %d threads\n", end_time - start_time, num_threads);
   
}
