#include <stdio.h>
#include <omp.h>

int A[100];

int main() {
    double starttime = second();

    int i;
    for (i = 0; i < 100; i++)
        A[i] = i;

    printf("sum = %d\n", sum(A, 100));

    double endtime = second();
    printf("%f\n", endtime - starttime);
    return 0;
}



