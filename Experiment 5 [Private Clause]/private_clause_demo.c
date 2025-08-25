#include <stdio.h>
#include <omp.h>

int main() {
    int val = 1234;   // Initialize variable

    // Set OpenMP threads to 4
    omp_set_num_threads(4);

    // Print value before entering parallel region
    printf("Initial value of val outside parallel region: %d\n", val);

    // Parallel region with firstprivate
    #pragma omp parallel firstprivate(val)
    {
        int tid = omp_get_thread_num();
        printf("Thread %d: Initial val = %d\n", tid, val);

        val = val + 1;   // Increment local copy
        printf("Thread %d: Updated val = %d\n", tid, val);
    }

    // Print value after exiting parallel region
    printf("Final value of val outside parallel region: %d\n", val);

    return 0;
}
