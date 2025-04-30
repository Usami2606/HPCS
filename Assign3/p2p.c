#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int myrank, nprocs, i;
    double *buf;  // 配列の型をdoubleに変更
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    for (int size = 10000; size <= 20000; size += 10000) {
        buf = malloc(sizeof(double) * size);  // 動的にサイズを変更

        if (myrank == 0) {
            // 送信するデータを設定
            for (i = 0; i < size; i++) {
                buf[i] = (double)i * 1.1;  // 例として、iを1.1倍した値を設定
            }
        }

        // データを送信・受信
        if (myrank == 0) {
            MPI_Send(buf, size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        } else if (myrank == 1) {
            MPI_Recv(buf, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        }

        // // 送信したデータを表示（rank 0）
        // if (myrank == 0) {
        //     printf("[%d/%d] send data for size %d = {", myrank, nprocs, size);
        //     for (i = 0; i < size; i++) {
        //         printf("%f,", buf[i]);  // double型の値を表示
        //     }
        //     printf("}\n");
        // }
	}


    MPI_Barrier(MPI_COMM_WORLD);

    // // 受信したデータを表示（rank 1）
    // if (myrank == 1) {
    //     printf("[%d/%d] recv data = {", myrank, nprocs);
    //     for (i = 0; i < 20; i++) {
    //         printf("%f,", buf[i]);  // double型の値を表示
    //     }
    //     printf("}\n");
    // }

    free(buf);  // メモリ解放
    MPI_Finalize();
    return 0;
}
