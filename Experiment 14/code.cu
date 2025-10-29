
#include <iostream>
#include <cuda_runtime.h>
using namespace std;

__global__ void matMul(float *A, float *B, float *C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < N && col < N) {
        float sum = 0;
        for (int k = 0; k < N; ++k)
            sum += A[row * N + k] * B[k * N + col];
        C[row * N + col] = sum;
    }
}

void fillMatrix(float *m, int N, float start) {
    for (int i = 0; i < N * N; i++) m[i] = start + i;
}

void printMatrix(float *m, int N) {
    for (int i = 0; i < N * N; i++) {
        cout << m[i] << " ";
        if ((i + 1) % N == 0) cout << "\n";
    }
}

int main() {
    int N = 4;
    int size = N * N * sizeof(float);

    float *A, *B, *C, *D, *E, *F;
    cudaMallocHost(&A, size);
    cudaMallocHost(&B, size);
    cudaMallocHost(&C, size);
    cudaMallocHost(&D, size);
    cudaMallocHost(&E, size);
    cudaMallocHost(&F, size);

    fillMatrix(A, N, 1);
    fillMatrix(B, N, 2);
    fillMatrix(C, N, 10);
    fillMatrix(D, N, 20);

    float *dA, *dB, *dC, *dD, *dE, *dF;
    cudaMalloc(&dA, size);
    cudaMalloc(&dB, size);
    cudaMalloc(&dC, size);
    cudaMalloc(&dD, size);
    cudaMalloc(&dE, size);
    cudaMalloc(&dF, size);

    cudaMemcpy(dA, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dB, B, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dC, C, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dD, D, size, cudaMemcpyHostToDevice);

    dim3 threads(16, 16);
    dim3 blocks((N + 15) / 16, (N + 15) / 16);

    matMul<<<blocks, threads>>>(dA, dB, dE, N);
    matMul<<<blocks, threads>>>(dC, dD, dF, N);
    cudaDeviceSynchronize();

    cudaMemcpy(E, dE, size, cudaMemcpyDeviceToHost);
    cudaMemcpy(F, dF, size, cudaMemcpyDeviceToHost);

    cout << "A x B:\n";
    printMatrix(E, N);
    cout << "\nC x D:\n";
    printMatrix(F, N);

    cudaFree(dA); cudaFree(dB); cudaFree(dC); cudaFree(dD);
    cudaFree(dE); cudaFree(dF);
    cudaFreeHost(A); cudaFreeHost(B); cudaFreeHost(C); cudaFreeHost(D);
    cudaFreeHost(E); cudaFreeHost(F);

    return 0;
}

