#include <stdio.h>
#include <omp.h>
#include "timer.c"
#include "sum1.c"

int main() {
    double starttime = second();

    int i;
    for (i = 0; i < 1000; i++)
        A[i] = i;

    printf("sum = %d\n", sum(A, 1000));

    double endtime = second();
    printf("%f\n", endtime - starttime);
    return 0;
}