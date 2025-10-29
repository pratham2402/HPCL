#!/bin/bash
#SBATCH --job-name=mpi_numbers
#SBATCH --output=mpi_numbers.out
#SBATCH --error=mpi_numbers.err
#SBATCH --ntasks=4
#SBATCH --time=00:05:00
#SBATCH --partition=standard

module load compiler/openmpi/4.1.5

mpirun ./mpi_send_numbers