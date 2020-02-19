/* File:     piSeriesNaive.c
 * Purpose:  Estimate pi using OpenMP and the formula
 *
 *              pi = 4*[1 - 1/3 + 1/5 - 1/7 + 1/9 - . . . ]
 *
 * Compile:  gcc -g -Wall -fopenmp -o piSeriesNaive piSeriesNaive.c -lm              
 * Run:      piSeriesNaive <thread_count> <n>
 *           thread_count is the number of threads
 *           n is the number of terms of the series to use
 *
 * Input:    none            
 * Output:   The estimate of pi and the value of pi computed by the
 *           arctan function in the math library
 *
 * Notes:
 *    1.  The radius of convergence is only 1.  So the series converges
 *        *very* slowly.
 */        

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> 

void Usage(char* prog_name);

int main(int argc, char* argv[]) {
   long long n, k;
   int thread_count;
   double factor = 1.0;
   double sum = 0.0;

   thread_count = strtol(argv[1], NULL, 10);
   n = strtoll(argv[2], NULL, 10);

#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: sum)
   for (k = 0; k < n; k++) { 
      sum += factor/(2*k+1);
	  factor = -factor;
   }

   sum = 4.0*sum;
   printf("With n = %lld terms and %d threads,\n", n, thread_count);
   printf("   Our estimate of pi = %.14f\n", sum);
   printf("                   PI = %.14f\n", 4.0*atan(1.0));

   return 0;
}  /* main */

