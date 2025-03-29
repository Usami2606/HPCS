#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{

        int myrank, nprocs, i;
        int *buf;
        MPI_Status status;

        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

        buf = malloc(sizeof(int)*20);

        if(myrank == 0){
                for(i=0;i<20;i++){
                        buf[i] = i;
                }
        }

        if(myrank == 0){
                MPI_Send(buf, 20, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }else if(myrank == 1){
                MPI_Recv(buf, 20, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        }

        if(myrank == 0){
                printf("[%d/%d] send data = {", myrank, nprocs);
                for(i=0;i<20;i++){
                        printf("%d,", buf[i]);
                }
                printf("}\n");
        }

        MPI_Barrier(MPI_COMM_WORLD);

        if(myrank == 1){
                printf("[%d/%d] recv data = {", myrank, nprocs);
                for(i=0;i<20;i++){
                        printf("%d,", buf[i]);
                }
                printf("}\n");
        }

        MPI_Finalize();
        return 0;
}

// salloc -p ${PART} -N 1\
//             -w ${NODE}\
//             -- mpirun -np ${NP} ./sample3


// -bash-4.2$ mpicc -o sample3 sample3.c
// -bash-4.2$ PART=comq
// -bash-4.2$ NODE=ppx00
// -bash-4.2$ salloc -p ${PART} -N 1\
// >             -w ${NODE}\
// >             -- mpirun -np ${NP} ./sample3
// salloc: Granted job allocation 305197
// [ppx00][[546,1],2][btl_openib_component.c:1670:init_one_device] error obtaining device attributes for mlx5_0 errno says No space left on device
// [ppx00][[546,1],6][btl_openib_component.c:1670:init_one_device] error obtaining device attributes for mlx5_0 errno says No space left on device
// [ppx00][[546,1],3][btl_openib_component.c:1670:init_one_device] error obtaining device attributes for mlx5_0 errno says No space left on device
// [ppx00][[546,1],5][btl_openib_component.c:1670:init_one_device] error obtaining device attributes for mlx5_0 errno says No space left on device
// [ppx00][[546,1],1][btl_openib_component.c:1670:init_one_device] error obtaining device attributes for mlx5_0 errno says No space left on device
// [ppx00][[546,1],0][btl_openib_component.c:1670:init_one_device] error obtaining device attributes for mlx5_0 errno says No space left on device
// --------------------------------------------------------------------------
// WARNING: There was an error initializing an OpenFabrics device.

//   Local host:   ppx00
//   Local device: mlx5_0
// --------------------------------------------------------------------------
// [ppx00][[546,1],4][btl_openib_component.c:1670:init_one_device] error obtaining device attributes for mlx5_0 errno says No space left on device
// [0/7] send data = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,}
// [1/7] recv data = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,}
// [ppxsvc.ccs.tsukuba.ac.jp:52601] 6 more processes have sent help message help-mpi-btl-openib.txt / error in device init
// [ppxsvc.ccs.tsukuba.ac.jp:52601] Set MCA parameter "orte_base_help_aggregate" to 0 to see all help / error messages
// salloc: Relinquishing job allocation 305197
