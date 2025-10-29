#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    char message[50];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank != 0) {
        sprintf(message, "Hello World from process %d of %d", rank, size);
        MPI_Send(message, 50, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
	printf("Hello World from process %d of %d\n", rank, size);
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
            printf("%s\n", message);
        }
    }

    MPI_Finalize();
    return 0;
}