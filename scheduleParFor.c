/* File:   scheduleParFor.c
 * Purpose:   Output the default scheduling used in a parallel for loop
 *
 * Compile:   gcc -g -Wall -fopenmp -o scheduleParFor 
 *                 scheduleParFor.c
 * Run:      ./scheduleParFor <thread_count> <n>
 *              n is the number of iterations in the for loop
 *
 * Input:    None
 * Output:   Which iterations are executed of the loop are
 *           executed by each thread
 *
 * Note:     The program assumes that each thread will execute
 *           a sequence of consecutive iterations.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Usage(char prog_name[]);
void Get_args(char* argv[], int* thread_count, int* n);
void Schedule(int thread_count, int n);

int main(int argc, char* argv[]) {
   int thread_count, n;
 
   if (argc != 3) Usage(argv[0]);
   Get_args(argv, &thread_count, &n);
   
   Schedule(thread_count, n);
   

   return 0;
}  /* main */


/*---------------------------------------------------------------------
 * Function:  Usage 
 * Purpose:   Print a message showing how to run the program and quit
 * In arg:    prog_name:  the name of the program from the command line
 */

void Usage(char prog_name[]) {
   fprintf(stderr, "usage: %s <thread_count> <n>\n", prog_name);
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argv
 * Out args:    thread_count, n
 */

void Get_args(
           char* argv[]          /* in  */,
           int*  thread_count    /* out */,
           int*  n               /* out */) {
   *thread_count = strtol(argv[1], NULL, 10);  
   *n = strtol(argv[2], NULL, 10);
}  /* Get_args */


/*------------------------------------------------------------------
 * Function:    Schedule
 * Purpose:     Print out default scheduling of parallel for loop
 * In args:     thread_count, n
 */

void Schedule(int thread_count, int n) {
   int  i;
   int* min = malloc(thread_count*sizeof(int));
   int* max = malloc(thread_count*sizeof(int));
  

   /*aqui*/
   #pragma omp parallel for num_threads(thread_count)

   for (i = 0; i < n; i++) {
      max[omp_get_thread_num()] = i;
   }
   
   /* imprimir en donde empieza y donde termina la asignacion de manera paralela 
   /* End of omp parallel */
   
   for (i = 0; i < thread_count; i++) {
      if (max[i] == 0)
         printf("Th %d > No iterations\n", i);
      else
         printf("Th %d > Iteration  %d\n", i, max[i]);
   }
   
   free(min);
   free(max);


}  /* Schedule */

