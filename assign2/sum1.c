#include <stdio.h>
#include <omp.h>

int A[1000];

int sum(int *a, int n) {
    int s, i;
    s = 0;
#pragma omp parallel
{
    // printf("Hello World from %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
#pragma omp for reduction(+:s)
    
    for (i = 0; i < n; i++)
        s += a[i];
}
    return s;
}



