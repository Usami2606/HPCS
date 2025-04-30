#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

double second() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

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
        int size = m * 10000;  // 配列のサイズを変更
        buf = malloc(sizeof(double) * size);  // 動的にサイズを変更

        // mallocの成功をチェック
        if (buf == NULL) {
            fprintf(stderr, "Memory allocation failed for size %d\n", size);
            MPI_Abort(MPI_COMM_WORLD, 1);  // メモリ割り当てに失敗した場合、MPIプログラムを終了
        }

        if (myrank == 0) {
            // 送信するデータを設定
            for (i = 0; i < size; i++) {
                buf[i] = (double)i * 1.1;  // 例として、iを1.1倍した値を設定
            }
        }

		MPI_Barrier(MPI_COMM_WORLD);  // 同期を取る

        start = second();
        // データを送信・受信
        if (myrank == 0) {
            MPI_Send(buf, size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        } else if (myrank == 1) {
            MPI_Recv(buf, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        }
        end = second();

        // 時間を記録
        times[m] = end - start;

        // bufのメモリ解放
        free(buf);
    }

    for (n = 0; n < 20; n++) {
        printf("time%d = %f seconds\n", n, times[n]);
    }
    MPI_Finalize();
    return 0;
}
