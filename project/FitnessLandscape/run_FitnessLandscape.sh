#!/bin/bash 

#PBS -N LHSNG
#PBS -A 3ANTAL-2016
#PBS -q parallel
#PBS -M xelias@stuba.sk

# skript žiada o 2 výpočtové uzly, 6 procesorových jadier na uzol, pre každé jadro/proces 200MB fyzickej pamäte na 2 minúty
#PBS -l nodes=4:ppn=12,pmem=100mb,walltime=2:00:00
#PBS -m ea

home="/home/3xelias/FitnessLandscape"

application="$home/FitnessLandscape $home/input/bigrams.csv $home/input/trigrams.csv $home/input/ct/ $home/input/pt/"

# štandardný výstup z aplikácie sa bude priebežne zapisovať do súboru "OUT"
options="> job.stdout"

. /etc/profile.d/modules.sh
module purge
module load gcc/5.4 mvapich2/2.2

CMD="mpirun $application $options"

###############################################################

# prechod do priečinka odkiaľ bola spustená úloha
cd $PBS_O_WORKDIR
echo -e "Changed directory to $(pwd)"
JOBID=$(echo $PBS_JOBID | sed -e "s/..*$//")

echo -e "JobID: $JOBIDn======"
echo "Time: `date`"
echo "Running on master node: $(hostname)"
echo "Current directory: $(pwd)"

if [ -r "$PBS_NODEFILE" ]; then
	cat $PBS_NODEFILE | uniq > machfile
	echo -e "Nodes allocated:================"
	echo $(cat machfile | sed -e "s/..*$//g")
fi

echo -e "numprocs=$PBS_NP, numnodes=$PBS_NUM_NODES, ppn=$PBS_NUM_PPN"
echo -e "Executing command:==================$CMD"

eval $CMD
