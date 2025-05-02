#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

double second() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char* argv[])
{
    double start, send_time, recv_time, sync_time;
    int myrank, nprocs, i;
    double *sendbuf, *recvbuf;  // 配列の型をdoubleに変更
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    printf("my rank is %d and size is %d\n", myrank, nprocs);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    printf("Rank %d running on %s\n", myrank, hostname);

    // ここでプロセス数が1でないことを確認
    if (nprocs < 2) {
        if (myrank == 0) {
            fprintf(stderr, "This program requires at least 2 processes.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int size = 100000;  // 配列のサイズを変更
    sendbuf = malloc(sizeof(double) * size);  // 動的にサイズを変更
    recvbuf = malloc(sizeof(double) * size);

    memset(sendbuf, 0, sizeof(double) * size);
    memset(recvbuf, 0, sizeof(double) * size);

    // mallocの成功をチェック
    if (sendbuf == NULL) {
        fprintf(stderr, "Memory allocation failed for size %d\n", size);
        MPI_Abort(MPI_COMM_WORLD, 1);  // メモリ割り当てに失敗した場合、MPIプログラムを終了
    }

    if (myrank == 0) {
        // 送信するデータを設定
        for (i = 0; i < size; i++) {
            sendbuf[i] = (double)rand() / (double)RAND_MAX;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);  // 同期を取る

    // 送信時間の計測
    start = MPI_Wtime();
    if (myrank == 0) {
        MPI_Send(sendbuf, size, MPI_DOUBLE, 1, 2025, MPI_COMM_WORLD);
    }
    send_time = MPI_Wtime() - start;  // 送信の時間を計測

    // 受信時間の計測
    start = MPI_Wtime();
    if (myrank == 1) {
        MPI_Recv(recvbuf, size, MPI_DOUBLE, 0, 2025, MPI_COMM_WORLD, &status);
    }
    recv_time = MPI_Wtime() - start;  // 受信の時間を計測

    // 同期時間の計測
    start = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    sync_time = MPI_Wtime() - start;  // バリア同期の時間を計測

    // 結果の表示
    if (myrank == 0) {
        printf("rank0 send time: %f\n", send_time);
    } else if (myrank == 1) {
        printf("rank1 recv time: %f\n", recv_time);
    }

    // バリア同期時間を表示
    printf("Synchronization time: %f\n", sync_time);

    // bufのメモリ解放
    free(sendbuf);
    free(recvbuf);
    
    printf("freebuffer\n");

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
