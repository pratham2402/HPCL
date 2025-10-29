#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

long long sum_range(long long a, long long b) {
    if (b < a) return 0;
    long long n = b - a + 1;
    return n * (a + b) / 2;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 2) {
        if (rank == 0) {
            fprintf(stderr, "Usage: mpirun -np <P> ./ring_sum <N>\n");
        }
	MPI_Finalize();
        return 1;
    }

    long long N = atoll(argv[1]);
    long long base = N / size;
    long long rem = N % size;
    long long my_count = base + (rank < rem ? 1 : 0);
    long long start = rank * base + (rank < rem ? rank : rem) + 1;
    long long end = start + my_count - 1;

    long long local_sum = sum_range(start, end);
    int next = (rank + 1) % size;
    int prev = (rank - 1 + size) % size;

    if (size == 1) {
        printf("Sum of 1..%lld = %lld\n", N, local_sum);
        MPI_Finalize();
        return 0;
    }

    long long token;
    if (rank == 0) {
        token = local_sum;
        MPI_Send(&token, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Sum of 1..%lld = %lld\n", N, token);
    } else {
	MPI_Recv(&token, 1, MPI_LONG_LONG, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        token += local_sum;
        MPI_Send(&token, 1, MPI_LONG_LONG, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
