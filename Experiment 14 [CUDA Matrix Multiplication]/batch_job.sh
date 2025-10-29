#!/bin/bash
#SBATCH --job-name=mat_mul
#SBATCH --partition=gpu
#SBATCH --gres=gpu:1
#SBATCH --output=mat_mul.%j.out
#SBATCH --error=mat_mul.%j.err
#SBATCH --time=00:02:00

module load cuda/12.3
module load compiler/gcc/12.3

echo "Running on node: $(hostname)"
echo "CUDA version:"
nvcc --version
echo "Starting program..."
./matrix_mul
echo "Program finished."

