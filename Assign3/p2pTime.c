#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_SIZE (1024 * 1024) // 最大1MB
#define NUM_REPEATS 1000       // 繰り返し回数

int main(int argc, char **argv)
{
    int rank;
    MPI_Status status;
    char *buffer;
    double start_time, end_time, total_time;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 送信サイズ（バイト単位）
    int sizes[] = {1, 10, 100, 1000, 10000, 100000, MAX_SIZE};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    if (rank == 0) {
        printf("# Size (bytes), Time per transfer (us), Throughput (MB/s)\n");
    }

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        buffer = (char*)malloc(size);

        if (rank == 0) {
            memset(buffer, 'A', size);
            MPI_Barrier(MPI_COMM_WORLD);  // 同期
            start_time = MPI_Wtime();

            for (int i = 0; i < NUM_REPEATS; i++) {
                MPI_Send(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(buffer, size, MPI_BYTE, 1, 0, MPI_COMM_WORLD, &status);
            }

            end_time = MPI_Wtime();
            total_time = end_time - start_time;
            double avg_time = total_time / (2 * NUM_REPEATS); // 片道の平均時間
            double throughput = (size / (1024.0 * 1024.0)) / avg_time; // MB/s

            printf("%10d, %20.2f, %18.2f\n", size, avg_time * 1e6, throughput);

        } else if (rank == 1) {
            for (int i = 0; i < NUM_REPEATS; i++) {
                MPI_Recv(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &status);
                MPI_Send(buffer, size, MPI_BYTE, 0, 0, MPI_COMM_WORLD);
            }
        }

        free(buffer);
    }

    MPI_Finalize();
    return 0;
}
