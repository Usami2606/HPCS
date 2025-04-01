#include <stdio.h>
#include <omp.h>

int A[1000000];

int main() {
    double starttime = second();

    int i;
    for (i = 0; i < 1000000; i++)
        A[i] = i;

    printf("sum = %d\n", sum(A, 1000000));

    double endtime = second();
    printf("%f\n", endtime - starttime);
    return 0;
}


