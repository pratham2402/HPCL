#include <stdio.h>
#include <omp.h>

int main() {
    // Set the number of threads to 4
    omp_set_num_threads(4);

    #pragma omp parallel
    {
        // Each thread prints its ID and the name
        int thread_id = omp_get_thread_num();
        printf("Thread %d: PRATHAM\n", thread_id);
    }

    return 0;
}

