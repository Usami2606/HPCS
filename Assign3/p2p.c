#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>
#include "Timer.c"
#define BUFSIZE (10 * 1024 * 1024)

double second();

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
		MPI_Send(sendbuf, BUFSIZE, MPI_BYTE, 1, tag, MPI_COMM_WORLD);
	} 
	else if (rank == 1) {
		float start = second();
		MPI_Recv(recvbuf, BUFSIZE, MPI_BYTE, 0, tag, MPI_COMM_WORLD, &status);
		printf("recv string = %s\n", recvbuf);
		float end = second();
		printf("Rank 1: Recv time = %f seconds\n", end - start);
	}
	MPI_Finalize();
	return 0;
}
