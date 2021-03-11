#!/bin/bash

#Submit this script with: sbatch thefilename

#SBATCH --time=70:00:00   # walltime
#SBATCH --ntasks=80   # number of processor cores (i.e. tasks)
#SBATCH -p defq   # partition(s)
#SBATCH -J "LIFAC scan"   # job name
#SBATCH --mail-user=egerlanc@physik.hu-berlin.de   # email address
#SBATCH --mail-type=BEGIN
#SBATCH --mail-type=END
#SBATCH --mail-type=FAIL

mpirun ./../bin/spike_suscept_nonlin -f lif.ini
