#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        printf("Hello World from %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }
}


// -bash-4.2$ ./hello
// Hello World from 36 of 56
// Hello World from 55 of 56
// Hello World from 1 of 56
// Hello World from 49 of 56
// Hello World from 17 of 56
// Hello World from 8 of 56
// Hello World from 15 of 56
// Hello World from 13 of 56
// Hello World from 20 of 56
// Hello World from 39 of 56
// Hello World from 7 of 56
// Hello World from 50 of 56
// Hello World from 34 of 56
// Hello World from 12 of 56
// Hello World from 5 of 56
// Hello World from 31 of 56
// Hello World from 6 of 56
// Hello World from 37 of 56
// Hello World from 21 of 56
// Hello World from 46 of 56
// Hello World from 52 of 56
// Hello World from 16 of 56
// Hello World from 29 of 56
// Hello World from 19 of 56
// Hello World from 44 of 56
// Hello World from 26 of 56
// Hello World from 2 of 56
// Hello World from 14 of 56
// Hello World from 9 of 56
// Hello World from 40 of 56
// Hello World from 41 of 56
// Hello World from 22 of 56
// Hello World from 32 of 56
// Hello World from 35 of 56
// Hello World from 51 of 56
// Hello World from 18 of 56
// Hello World from 23 of 56
// Hello World from 48 of 56
// Hello World from 3 of 56
// Hello World from 4 of 56
// Hello World from 45 of 56
// Hello World from 10 of 56
// Hello World from 33 of 56
// Hello World from 24 of 56
// Hello World from 42 of 56
// Hello World from 53 of 56
// Hello World from 11 of 56
// Hello World from 43 of 56
// Hello World from 0 of 56
// Hello World from 38 of 56
// Hello World from 25 of 56
// Hello World from 54 of 56
// Hello World from 30 of 56
// Hello World from 28 of 56
// Hello World from 27 of 56
// Hello World from 47 of 56