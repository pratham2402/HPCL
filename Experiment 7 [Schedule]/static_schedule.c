#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int n = 16;              // Total iterations
    int chunk = 4;           // Each thread executes 4 iterations at a time

    // Set 4 threads
    omp_set_num_threads(4);

    printf("Static Scheduling with chunk size = %d\n", chunk);

    #pragma omp parallel for schedule(static,4)
    for (i = 0; i < n; i++) {
        int tid = omp_get_thread_num();
        printf("Thread %d is executing iteration %d\n", tid, i);
    }

    return 0;
}
