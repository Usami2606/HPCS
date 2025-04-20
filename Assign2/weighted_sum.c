#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

double second();

#define N 100000000

double A[N];  // 配列を double に

double sum(double *a, int n) {
    int i;
    double s = 0.0;
#pragma omp parallel for reduction(+:s)
    for (i = 0; i < n; i++) s += a[i];
    return s;
}

int main() {
    double start, end;
    double time[20];
    int i, j;
    
    start = second();

#pragma omp parallel for
    for (i = 0; i < N; i++) {
        double m = (double)(i + 1);  // m = 1〜N
        A[i] = (1.0 / m) * sin(1.0 / m);
    }

    printf("sum = %.12f\n", sum(A, N));

    end = second();
    printf("time = %f seconds\n", end - start);

    return 0;
}

double second() {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    return (double)(tm.tv_sec) + (double)(tm.tv_usec) / 1.0e6;
}
