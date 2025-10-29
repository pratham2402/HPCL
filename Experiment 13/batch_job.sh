#!/bin/bash
#SBATCH --job-name=add_two_mat
#SBATCH --output=add_two_mat.%j.out
#SBATCH --error=add_two_mat.%j.err
#SBATCH --partition=gpu
#SBATCH --gres=gpu:1
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:10:00
#SBATCH --mem=4G

module load cuda/12.3
module load compiler/gcc/12.3

cd $HOME/cuda_matrix_add
echo "Running on node: $(hostname)"
echo "CUDA version:"
nvcc --version

echo "Starting program..."
./matrix_add
echo "Program finished."