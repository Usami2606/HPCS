#include <stdio.h>
#include <omp.h>

int A[100000];

int main() {
    double starttime = second();

    int i;
    for (i = 0; i < 100000; i++)
        A[i] = i;

    printf("sum = %d\n", sum(A, 100000));

    double endtime = second();
    printf("%f\n", endtime - starttime);
    return 0;
}


