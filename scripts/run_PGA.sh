#!/bin/bash

app=PGA_Mpi
workdir=/work/$USER/PGA

mkdir -p $workdir
cp bin/$app $workdir

for i in 3 5 11; do
    for j in b d e f; do

	# skip 3 f
	if [ "$i" = "3" ] && [ "$j" = "f" ]; then
	    continue
	fi

	file=$workdir/run_${i}_${j}
	jobname=${app}_${i}_${j}

	cat<<EOF > $file
#!/bin/bash

#PBS -N $jobname
#PBS -A 3ANTAL-2016
#PBS -q parallel
#PBS -M xelias@stuba.sk
#PBS -l nodes=1:ppn=$((i + 1)),walltime=120:00:00
#PBS -m ea

application="./$app $j input/"

. /etc/profile.d/modules.sh
module purge
module load gcc/5.4 mvapich2/2.2

CMD="mpirun $application 1>${jobname}.stdout 2>${jobname}.stderr"

# prechod do priečinka odkiaľ bola spustená úloha
cd $workdir
# echo -e "Changed directory to \$(pwd)"

# spustenie ulohy
eval $CMD
EOF
	qsub $file
	rm $file
    done
done
