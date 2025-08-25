#include <stdio.h>
#include <omp.h>

int main() {
    int val = 1234;   // Shared variable before parallel region

    // Set OpenMP threads to 4
    omp_set_num_threads(4);

    // Print value before entering parallel region
    printf("Initial value of val outside parallel region: %d\n", val);

    // Parallel region with private clause
    #pragma omp parallel private(val)
    {
        int tid = omp_get_thread_num();

        // val is undefined here (each thread has its own private copy)
        printf("Thread %d: Initial val (private, uninitialized) = %d\n", tid, val);

        val = tid + 100;   // Assign a value unique to each thread
        printf("Thread %d: Updated val = %d\n", tid, val);
    }

    // Print value after exiting parallel region
    printf("Final value of val outside parallel region: %d\n", val);

    return 0;
}
