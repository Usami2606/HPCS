#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

double second();

int main(int argc, char* argv[])
{
	double start, end;
	int m, n;
	double times[20];
    int myrank, nprocs, i;
    double *buf;  // 配列の型をdoubleに変更
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
    for (m = 0; m < 20; m++) {
        buf = malloc(sizeof(double) * m * 1000);  // 動的にサイズを変更

        if (myrank == 0) {
            // 送信するデータを設定
            for (i = 0; i < m * 1000; i++) {
                buf[i] = (double)i * 1.1;  // 例として、iを1.1倍した値を設定
            }
        }

		start = second();
        // データを送信・受信
        if (myrank == 0) {
            MPI_Send(buf, m * 1000, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        } else if (myrank == 1) {
            MPI_Recv(buf, m * 1000, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        }

		end = second();
		times[m] = end - start;

		free(buf);

        // // 送信したデータを表示（rank 0）
        // if (myrank == 0) {
        //     printf("[%d/%d] send data for size %d = {", myrank, nprocs, size);
        //     for (i = 0; i < size; i++) {
        //         printf("%f,", buf[i]);  // double型の値を表示
        //     }
        //     printf("}\n");
        // }
	}

	double total_time = 0.0;
    double max_time = times[0];
    double min_time = times[0];

	for (n = 0; n < 20; n++) {
        total_time += times[n];
        if (times[i] > max_time) max_time = times[n];
        if (times[i] < min_time) min_time = times[n];
    }

	double average_time = total_time / 20.0;

    // Output results
    printf("Average time = %f seconds\n", average_time);
    printf("Maximum time = %f seconds\n", max_time);
    printf("Minimum time = %f seconds\n", min_time);


    MPI_Barrier(MPI_COMM_WORLD);

    // // 受信したデータを表示（rank 1）
    // if (myrank == 1) {
    //     printf("[%d/%d] recv data = {", myrank, nprocs);
    //     for (i = 0; i < 20; i++) {
    //         printf("%f,", buf[i]);  // double型の値を表示
    //     }
    //     printf("}\n");
    // }
    MPI_Finalize();
    return 0;
}
