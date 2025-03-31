#include <stdio.h>
#include <omp.h>

float A[1000];

float sum(float *a, int n) {
    int i;
    float s = 0.0f;
#pragma omp parallel
{
    printf("Hello World from %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
#pragma omp for reduction(+:s)
    
    for (i = 0; i < n; i++)
        s += a[i];
}
    return s;
}

int main() {
    int i;
    for (i = 0; i < 1000; i++)
        A[i] = (float)i + 0.5f;

    printf("sum = %d\n", sum(A, 1000));

    return 0;
}

