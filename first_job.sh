# load MPI enviroment
module avail
module load gcc/4.8.5
module load openmpi/3.1.0

# run MPIprogram
<< COMMENTOUT
PART=comq
NODE=ppx00
NP=4
salloc -p ${PART} -N 1\
            -w ${NODE}\
            -- mpirun -np ${NP} ./filename
COMMENTOUT

