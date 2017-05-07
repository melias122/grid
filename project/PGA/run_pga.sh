#!/bin/bash

app=PGA
workdir=/work/$USER/PGA

mkdir -p $workdir
ln -s $workdir out
ls -s input $workdir/input
cp -v bin/$app $workdir

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
#PBS -l nodes=1:ppn=$((i + 1))
#PBS -l walltime=120:00:00
#PBS -m ea

. /etc/profile.d/modules.sh
module purge
module load gcc/5.4 mvapich2/2.2

CMD="mpirun ./$app $j 1>${jobname}.stdout 2>${jobname}.stderr"

# prechod do pracovneho priečinka
cd $workdir

# spustenie ulohy
eval \$CMD
rm ./$app
EOF
	qsub $file
	rm $file
    done
done
