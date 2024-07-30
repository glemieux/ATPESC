/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
#define num_threads 4
static long num_steps = 100000000;
double step;
int main ()
{
	  int i;
	  double x, pi, sum = 0.0;
	  double start_time, run_time;

	  /* We need a global array to hold the partial sums */
	  double sumarr[num_threads];

	  /* Set the number of threads */
	  int omp_set_num_thread(num_threads);

          /* The step size the same for each thread.
	   * This could be done set larger to allow 
	   * for the threads to loop back around 
	   * back to the beginning */
	  step = 1.0/(double) num_steps;

	  /* start the timer */
	  start_time = omp_get_wtime();

  	  /* Enter the parallel region */
          #pragma omp parallel
          {	 
	  /* get the thread id for this task */
	  int threadid = omp_get_thread_num();

	  /* Initialize the summarr */
	  sumarr[threadid] = 0.0

	  /* Distribute the work in a simple round robin.
	   * This makes it easy to determine the starting
	   * thread as it is equivalent to the thread id.
	   * Since here we are subtracting to get the mid point
	   * we need to start at 1 */
	  for (i=threadid+1;i<= num_steps; i++){
		  x = (i-0.5)*step;
		  sumarr[threadid] += 4.0/(1.0+x*x);
	  }
	  }
	  /* stop the parallel timer */
	  run_time = omp_get_wtime() - start_time;

	  /* sum the array */
	  for (i=0;i<=num_threads;i++){
	      sum += sumarr[i]
	  }

	  /* Multiply the sum by the step size to get the estimate of pi */
	  pi = step * sum;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}





