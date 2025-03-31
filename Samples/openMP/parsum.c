#include <stdio.h>

int A[1000];

int sum(int *a, int n) {
    int s, i;
    s = 0;
#pragma omp parallel
{
#pragma omp for reduction(+:s)
    for (i = 0; i < n; i++)
        s += a[i];
}
    return s;
}

int main() {
    int i;
    for (i = 0; i < 1000; i++)
        A[i] = i;

    printf("sum = %d\n", sum(A, 1000));

    return 0;
}

// -bash-4.2$ gcc -fopenmp -o parsum parsum.c
// -bash-4.2$ ./parsum
// sum = 1009247