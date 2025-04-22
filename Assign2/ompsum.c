#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

double second();

#define N 100000000

int A[N];

// 配列の合計を計算する関数
long long sum(int *a, int n) {
    int i;
    long long s = 0;
    
    // OpenMPで並列計算
    #pragma omp parallel
    {
        #pragma omp for reduction(+:s) // reductionを正しく使用
        for (i = 0; i < n; i++) {
            s += a[i];
        }
    }
    return s;
}

int main() {
    double start, end;
    double times[20];  // 計測時間を格納する配列
    int i, j;

    // 20回の計測を実行
    for (j = 0; j < 20; j++) {
        start = second();  // 計測開始時間
        for (i = 0; i < N; i++) A[i] = i;  // 配列Aを初期化
        sum(A, N);  // 計算を実行
        end = second();  // 計測終了時間
        times[j] = end - start;  // 時間を配列に保存
    }

    // 計測時間の平均、最大、最小を計算
    double total_time = 0.0;
    double max_time = times[0];
    double min_time = times[0];

    for (i = 0; i < 20; i++) {
        total_time += times[i];
        if (times[i] > max_time) max_time = times[i];
        if (times[i] < min_time) min_time = times[i];
    }

    double average_time = total_time / 20.0;

    // 結果を表示
    printf("平均時間 = %f 秒\n", average_time);
    printf("最大時間 = %f 秒\n", max_time);
    printf("最小時間 = %f 秒\n", min_time);

    return 0;
}

// 現在時刻を秒で返す関数
double second() {
    struct timeval tm;
    double t;

    gettimeofday(&tm, NULL);
    t = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6;
    return t;
}
