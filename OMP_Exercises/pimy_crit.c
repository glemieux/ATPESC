#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 4
static long num_steps = 100000000;
double step;
int main ()
{
	  int i;
	  double pi, sum = 0.0;
	  double start_time, run_time;

	  /* We need a global array to hold the partial sums */
	  double sumarr[NUM_THREADS];

	  /* Set the number of threads */
	  omp_set_num_threads(NUM_THREADS);

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
             int i;
	     double x, sum;
	     /* get the thread id for this task */
	     int threadid = omp_get_thread_num();
	     int nthrds = omp_get_num_threads();

	     /* Initialize the summarr */

	     /* Distribute the work in a simple round robin.
	      * This makes it easy to determine the starting
	      * thread as it is equivalent to the thread id.
	      * Since here we are subtracting to get the mid point
	      * we need to start at 1 */
	     for (i=threadid;i<=num_steps; i+=nthrds){
	             x = (i+0.5)*step;
	             sum += 4.0/(1.0+x*x);
	     }
             #pragma omp critical
	     pi += sum*step;
	  }
	  /* stop the parallel timer */
	  run_time = omp_get_wtime() - start_time;

	  /* Multiply the sum by the step size to get the estimate of pi */
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}





