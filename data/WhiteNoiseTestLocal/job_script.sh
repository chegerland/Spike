#!/bin/bash

#Submit this script with: sbatch thefilename

#SBATCH --time=15:00:00   # walltime
#SBATCH --ntasks=40   # number of processor cores (i.e. tasks)
#SBATCH -p defq   # partition(s)
#SBATCH -J "White Noise Check"   # job name
#SBATCH --mail-user=egerlanc@physik.hu-berlin.de   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e5_alpha_3e-4.json &&
mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e5_alpha_3e-5.json &&
mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e5_alpha_3e-6.json &&
mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e5_alpha_3e-7.json
