#!/bin/sh 

#PBS -N LHSNG
#PBS -l nodes=4:ppn=8,pmem=100mb,walltime=00:01:00
#PBS -A 3ANTAL-2016
#PBS -q parallel
#PBS -e job.stderr
#PBS -o job.stdout
# #PBS -m ae
# #PBS -M xelias@stuba.sk

mpirun /home/3xelias/grid/example/helloworld/helloworld


# #PBS -N HelloWorld
# #PBS -q parallel
# #PBS -e SimpleMPI.stderr
# #PBS -o SimpleMPI.stdout
# #PBS -A MPI-projekt

# # skript žiada o 2 výpočtové uzly, 6 procesorových jadier na uzol, pre každé jadro/proces 200MB fyzickej pamäte na 2 minúty
# #PBS -l nodes=2:ppn=6,pmem=200mb,walltime=00:02:00
# #PBS -m ea

#application="/apps/examples/hello-world"

# štandardný výstup z aplikácie sa bude priebežne zapisovať do súboru "OUT"
#options="> OUT"

#. /etc/profile.d/modules.sh
#module purge
#module load openmpi/1.6.5
# Príklad využitia premenných (PBS/Torque)
#np=$PBS_NP
#ppn=$PBS_NUM_PPN
#numnodes=$PBS_NUM_NODES

#CMD="mpirun --report-bindings $application $options"

###############################################################

# prechod do priečinka odkiaľ bola spustená úloha
#cd $PBS_O_WORKDIR
#echo -e "Changed directory to `pwd`.n"
#JOBID=`echo $PBS_JOBID | sed -e "s/..*$//"`

#echo -e "JobID: $JOBIDn======"
#echo "Time: `date`"
#echo "Running on master node: `hostname`"
#echo "Current directory: `pwd`"

#if [ -r "$PBS_NODEFILE" ]; then
#	cat $PBS_NODEFILE | uniq > machfile
#	echo -e "nNodes allocated:n================"
#	echo `cat machfile | sed -e "s/..*$//g"`
#fi

# echo -e "nnumprocs=$np, numnodes=$numnodes, ppn=$ppn"

# echo -e "nExecuting command:n==================n$CMDn"

# eval $CMD
