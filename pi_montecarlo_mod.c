#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


/* Serial function */
void Get_args(char* argv[], int* thread_count_p, 
      long long int* number_of_tosses_p);
void Usage(char* prog_name);

long double fRand(long double fMin, long double fMax)
{
	long double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


int player(int playersDarts)
{
	srand(time(NULL));
	long double pi, x, y;
	int score = 0;

	for (int i = 0; i < playersDarts; i++)
	{
		x = fRand(-1.0, 1.0);
		y = fRand(-1.0, 1.0);

		if (x*x + y*y < 1.0)
			score++;
	}
	return score;
}

int main(int argc, char* argv[])
{
	int thread_count;
	long long int number_of_tosses;

	long double pi;
	long const double REAL_PI = 3.141592653589;
	int score = 0, playersDarts;

	if (argc != 3) Usage(argv[0]);
    Get_args(argv, &thread_count, &number_of_tosses);

	// devide the total number of DARTS between players
	playersDarts = number_of_tosses / thread_count;
	double beginParallel = omp_get_wtime();

#pragma omp parallel for
	for (int i = 1; i <= thread_count; i++)
		score += player(playersDarts);

	double endParallel = omp_get_wtime();
	pi = 4.0 * ((long double)score / (long double)number_of_tosses);

	double time_spent_parallel = endParallel - beginParallel;
	printf("\n\t Calculated pi : %.12Lf\n", pi);
	printf(	 "\t       Real pi : %.12Lf\n", REAL_PI);
	printf("\n\t Execution Time: %f\n", time_spent_parallel);

	return(0);	

}

/*---------------------------------------------------------------------
 * Function:  Usage 
 * Purpose:   Print a message showing how to run program and quit
 * In arg:    prog_name:  the name of the program from the command line
 */

void Usage(char prog_name[] /* in */) {
   fprintf(stderr, "usage: %s ", prog_name); 
   fprintf(stderr, "<number of threads> <total number of tosses>\n");
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argv
 * Out args:    thread_count_p, number_of_tosses_p
 */

void Get_args(
           char*           argv[]              /* in  */,
           int*            thread_count_p      /* out */,
           long long int*  number_of_tosses_p  /* out */) {
   
   *thread_count_p = strtol(argv[1], NULL, 10);  
   *number_of_tosses_p = strtoll(argv[2], NULL, 10);
}  /* Get_args */