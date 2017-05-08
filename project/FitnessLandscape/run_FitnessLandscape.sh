#!/bin/bash 

#PBS -N FitnessLandscape
#PBS -A 3ANTAL-2016
#PBS -q parallel

# skript žiada o 2 výpočtové uzly, 6 procesorových jadier na uzol, pre každé jadro/proces 200MB fyzickej pamäte na 2 minúty
#PBS -l nodes=4:ppn=12
#PBS -l walltime=2:00:00

. /etc/profile.d/modules.sh
module purge
module load gcc/5.4 mvapich2/2.2

application="./FitnessLandscape input/bigrams.csv input/trigrams.csv input/ct/ input/pt/"

CMD="mpirun $application"

# prechod do priečinka odkiaľ bola spustená úloha
cd $PBS_O_WORKDIR

if [ -r "$PBS_NODEFILE" ]; then
	cat $PBS_NODEFILE | uniq > machfile
fi

eval $CMD
