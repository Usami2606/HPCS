#include <stdio.h>

int A[1000];

int sum(int *a, int n) {
    int s, i;
    for (i = 0; i < n; i++)
        s += a[i];
    return s;
}

int main() {
    int i;
    for (i = 0; i < 1000; i++)
        A[i] = i;

    printf("sum = %d\n", sum(A, 100));

    return 0;
}

// -bash-4.2$ gcc -fopenmp -o mpisum mpisum.c
// -bash-4.2$ ./mpisum
// sum = 499500
// -bash-4.2$ 