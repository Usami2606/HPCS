#include <stdio.h>
#include <mpi.h>
#include "Timer.c"

int main(int argc, char **argv)
{
	int rank, tag = 0;
	MPI_Status status;
	char sendbuf[1024];
	char recvbuf[1024];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("rank = %d\n", rank);
	
	if (rank == 0) {
		sprintf(sendbuf, "send data from rank0 to rank1");
		MPI_Send(sendbuf, 1024, MPI_BYTE, 1, tag, MPI_COMM_WORLD);
	} 
	else if (rank == 1) {
		start = second();
		MPI_Recv(recvbuf, 1024, MPI_BYTE, 0, tag, MPI_COMM_WORLD, &status);
		printf("recv string = %s\n", recvbuf);
		end = second();
		printf("Rank 1: Recv time = %f seconds\n", end - start);
	}
	MPI_Finalize();
	return 0;
}
