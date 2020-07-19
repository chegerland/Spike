#!/bin/bash

#Submit this script with: sbatch thefilename

#SBATCH --time=15:00:00   # walltime
#SBATCH --ntasks=60   # number of processor cores (i.e. tasks)
#SBATCH -p defq   # partition(s)
#SBATCH -J "White Noise Check"   # job name
#SBATCH --mail-user=egerlanc@physik.hu-berlin.de   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e6_alpha_3e-3_T_5e2.json &&
mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e6_alpha_3e-3_T_1e3.json &&
mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e6_alpha_3e-3_T_5e3.json
