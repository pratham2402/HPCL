#include <stdio.h>
#include <omp.h>

int main() {
    // Parallel region starts here
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();   // Thread ID
        int nthreads = omp_get_num_threads(); // Total threads
        printf("Hello World from thread %d out of %d threads\n", tid, nthreads);
    }
    return 0;
}
