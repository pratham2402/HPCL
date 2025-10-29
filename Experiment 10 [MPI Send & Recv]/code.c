#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    int numbers[2];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    numbers[0] = rank * 2 + 1;  // first number
    numbers[1] = rank * 2 + 2;  // second number

    if (rank != 0) {
        MPI_Send(numbers, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
	printf("Root process %d received its own numbers: [%d, %d]\n", rank, numbers[0], numbers[1]);
        int recv_data[2];
        for (int i = 1; i < size; i++) {
            MPI_Recv(recv_data, 2, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            printf("Received from process %d: [%d, %d]\n", i, recv_data[0], recv_data[1]);
        }
    }

    MPI_Finalize();
    return 0;
}