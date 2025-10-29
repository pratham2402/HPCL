#include <stdio.h>
#include <cuda_runtime.h>

__global__ void addMatrices(const float *A, const float *B, float *R, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < N) R[idx] = A[idx] + B[idx];
}

void fill(float *x, int N, float val) {
    for (int i = 0; i < N; i++) x[i] = val + i;
}

int main() {
    int N = 16;
    size_t bytes = N * sizeof(float);

    float *h_A = (float*)malloc(bytes);
    float *h_B = (float*)malloc(bytes);
    float *h_C = (float*)malloc(bytes);
    float *h_D = (float*)malloc(bytes);
    float *h_R1 = (float*)malloc(bytes);
    float *h_R2 = (float*)malloc(bytes);

    fill(h_A, N, 1.0f);
    fill(h_B, N, 10.0f);
    fill(h_C, N, 100.0f);
    fill(h_D, N, 1000.0f);

    float *d_A, *d_B, *d_C, *d_D, *d_R1, *d_R2;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);
    cudaMalloc(&d_D, bytes);
    cudaMalloc(&d_R1, bytes);
    cudaMalloc(&d_R2, bytes);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, h_C, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_D, h_D, bytes, cudaMemcpyHostToDevice);

    int blockSize = 128;
    int gridSize = (N + blockSize - 1) / blockSize;

    addMatrices<<<gridSize, blockSize>>>(d_A, d_B, d_R1, N);
    addMatrices<<<gridSize, blockSize>>>(d_C, d_D, d_R2, N);
    cudaDeviceSynchronize();

    cudaMemcpy(h_R1, d_R1, bytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_R2, d_R2, bytes, cudaMemcpyDeviceToHost);

    printf("A + B:\n");
    for (int i = 0; i < N; i++) printf("%.1f ", h_R1[i]);
    printf("\nC + D:\n");
    for (int i = 0; i < N; i++) printf("%.1f ", h_R2[i]);
    printf("\n");

    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
    cudaFree(d_D); cudaFree(d_R1); cudaFree(d_R2);
    free(h_A); free(h_B); free(h_C); free(h_D); free(h_R1); free(h_R2);
    return 0;
}