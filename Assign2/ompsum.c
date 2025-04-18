#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

double second();

int A[100000000];

long long sum(int *a, int n) {
    int i;
    long long s = 0;
#pragma omp parallel
{
#pragma omp for reduction(+:s)
    for (i = 0; i < n; i++) s += a[i];
}
    return s;
}

int main() {
    double start, end;
    double times[20];  // 計測時間を格納する配列
    int i, j;

    // 計測を20回行う
    for (j = 0; j < 20; j++) {
        start = second();
        for (i = 0; i < 100000000; i++) A[i] = i;
        sum(A, 100000000);  // 計算の実行
        end = second();
        times[j] = end - start;  // 計測時間を配列に保存
    }

    // 平均、最大値、最小値を計算
    double total_time = 0.0;
    double max_time = times[0];
    double min_time = times[0];

    for (i = 0; i < 20; i++) {
        total_time += times[i];
        if (times[i] > max_time) max_time = times[i];
        if (times[i] < min_time) min_time = times[i];
    }

    double average_time = total_time / 20.0;

    // 結果を出力
    printf("Average time = %f seconds\n", average_time);
    printf("Maximum time = %f seconds\n", max_time);
    printf("Minimum time = %f seconds\n", min_time);

    return 0;
}

double second() {
    struct timeval tm;
    double t;

    gettimeofday(&tm, NULL);
    t = (double)(tm.tv_sec) + ((double)(tm.tv_usec)) / 1.0e6;
    return t;
}
