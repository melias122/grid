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
