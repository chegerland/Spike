#!/bin/bash

#Submit this script with: sbatch thefilename

#SBATCH --time=15:00:00   # walltime
#SBATCH --ntasks=40   # number of processor cores (i.e. tasks)
#SBATCH -p defq   # partition(s)
#SBATCH --mem-per-cpu=1G   # memory per CPU core
#SBATCH -J "LIF Suscept Scan"   # job name
#SBATCH --mail-user=egerlanc@physik.hu-berlin.de   # email address
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

mpirun ./../../bin/suscept_mpi --file lif_scan_N_1e6_alpha_1e-4.json
