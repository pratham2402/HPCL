#!/bin/bash
#SBATCH --job-name=mpi_sum_n
#SBATCH --output=mpi_sum_n.out
#SBATCH --error=mpi_sum_n.err
#SBATCH --ntasks=2
#SBATCH --time=00:02:00
#SBATCH --partition=standard

module load compiler/openmpi/4.1.5

mpirun ./mpi_sum_n