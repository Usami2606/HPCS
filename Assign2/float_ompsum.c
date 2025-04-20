#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

double second();

#define N 100000000

float A[N];

float sum(float *a, int n) {
    int i;
    float s = 0;
#pragma omp parallel
{
#pragma omp for reduction(+:s)
    for (i = 0; i < n; i++) s += a[i];
}
    return s;
}

int main() {
    double start, end;
    double times[20];  // Array to store measurement time
    int i, j;

    // Take 20 measurements
    for (j = 0; j < 20; j++) {
        start = second();
        for (i = 0; i < N; i++) A[i] = i;
        sum(A, N);  // Performing calculations
        end = second();
        times[j] = end - start;  // Save the measured time in an array
    }

    // Calculate the average, maximum, and minimum
    double total_time = 0.0;
    double max_time = times[0];
    double min_time = times[0];

    for (i = 0; i < 20; i++) {
        total_time += times[i];
        if (times[i] > max_time) max_time = times[i];
        if (times[i] < min_time) min_time = times[i];
    }

    double average_time = total_time / 20.0;

    // Output results
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
