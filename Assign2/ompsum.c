#include <stdio.h>
#include <sys/time.h>

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

    start = second();
    int i;
    for (i = 0; i < 100000000; i++) A[i] = i;
    // printf("sum = %lld\n", sum(A, 100000000));
    printf("Thread is  %d\n",omp_get_num_threads());
    end = second();
    printf("time = %f seconds\n", end - start);
}

double second()
{
    struct timeval tm;
    double t ;

    gettimeofday(&tm,NULL);
    t = (double) (tm.tv_sec) + ((double) (tm.tv_usec))/1.0e6;
    return t;
}