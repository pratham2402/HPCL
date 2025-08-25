#include <stdio.h>
#include <omp.h>

int main() {
    // Run with exactly 2 threads
    omp_set_num_threads(2);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        if (tid == 0) {
            printf("Thread %d printing multiples of 2:\n", tid);
            for (int i = 1; i <= 5; i++) {
                printf("Thread %d: %d\n", tid, 2 * i);
            }
        }
        else if (tid == 1) {
            printf("Thread %d printing multiples of 4:\n", tid);
            for (int i = 1; i <= 5; i++) {
                printf("Thread %d: %d\n", tid, 4 * i);
            }
        }
    }
    return 0;
}
