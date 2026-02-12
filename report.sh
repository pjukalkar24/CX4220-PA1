#!/bin/bash

#SBATCH --job-name=report
#SBATCH --output=report.out
#SBATCH --error=report.err
#SBATCH --nodes=1
#SBATCH --constraint=gold6226
#SBATCH --ntasks-per-node=24
#SBATCH --time=00:05:00
#SBATCH --exclusive

lscpu

echo "-------------------------------------"
module load openmpi
make clean
make

echo "-------------------------------------"
echo "# of processors: 1"
echo "n = 10^9"
output1=$(mpirun -np 1 ./pi -n 1000000000)
echo "$output1"

echo "-------------------------------------"
echo "# of processors: 6"
echo "n = 10^9"
output2=$(mpirun -np 6 ./pi -n 1000000000)
echo "$output2"

echo "-------------------------------------"
echo "# of processors: 12"
echo "n = 10^9"
output3=$(mpirun -np 12 ./pi -n 1000000000)
echo "$output3"

echo "-------------------------------------"
echo "# of processors: 24"
echo "n = 10^9"
output4=$(mpirun -np 24 ./pi -n 1000000000)
echo "$output4"
