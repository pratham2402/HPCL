#!/bin/bash
#SBATCH --job-name=ring_sum
#SBATCH --output=ring_sum.out
#SBATCH --error=ring_sum.err
#SBATCH --ntasks=4
#SBATCH --time=00:05:00
#SBATCH --partition=standard

module load compiler/openmpi/4.1.5

mpirun ./ring_sum 10000

