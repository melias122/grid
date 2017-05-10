#!/bin/bash

for i in 3 5 11; do
    for j in b d e f; do

	# skip 3 f
	if [ "$i" = "3" ] && [ "$j" = "f" ]; then
	    continue
	fi

	file=pga_${i}_${j}.qsub
	jobname=pga_${i}_${j}

	cat << EOF > $file
#!/bin/bash

#PBS -N $jobname
#PBS -A 3ANTAL-2016
#PBS -q parallel
#PBS -l nodes=1:ppn=$((i + 1))
#PBS -l walltime=200:00:00

#PBS -M xelias@stuba.sk
#PBS -m ea

. /etc/profile.d/modules.sh
module purge
module load gcc/5.4 mvapich2/2.2

CMD="mpirun ./pga $j 1>${jobname}.stdout"

# prechod do pracovneho priečinka
cd \$PBS_O_WORKDIR

# spustenie ulohy
eval \$CMD
EOF
	qsub -d $(pwd) $file
	rm $file
    done
done
