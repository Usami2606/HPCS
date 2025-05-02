#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double second() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	char *procName = malloc(sizeof(char) * 300);
	int len=0;
	MPI_Get_processor_name(procName, &len);
	//printf("%s:%d/%d\n",procName,rank,size);


	int DataNum = 0;
	if (argc == 2)
	{
		DataNum = atoi(argv[1]);
	}
	else
	{
		fprintf(stderr, "引数が1つではありません\n");
	}

	int localDataNum = (DataNum + size - 1) / size;

	int *sentbuf = malloc(sizeof(int) * DataNum);
	int *recvbuf = malloc(sizeof(int) * DataNum);

	// 計測開始--------------------------------------
	MPI_Barrier(MPI_COMM_WORLD);
	double start = second();

	MPI_Status status;
	if (rank == 0)
	{
		MPI_Send(sentbuf, DataNum, MPI_INT, 1, 2024, MPI_COMM_WORLD);
	}
	else if (rank == 1)
	{
		MPI_Recv(recvbuf, DataNum, MPI_INT, 0, 2024, MPI_COMM_WORLD, &status);
	}

	// 計測終了--------------------------------------
	MPI_Barrier(MPI_COMM_WORLD);
	double end = second();

	double commTime = end - start;
	if (rank == 1)
	{
		MPI_Send(&commTime, 1, MPI_INT, 0, 2025, MPI_COMM_WORLD);
	}
	else if (rank == 0)
	{
		double otherCommTime;
		MPI_Recv(&otherCommTime, 1, MPI_INT, 1, 2025, MPI_COMM_WORLD, &status);
		double maxTime = otherCommTime > commTime ? otherCommTime : commTime;
		printf("%lf", maxTime);
	}

	MPI_Finalize();
}