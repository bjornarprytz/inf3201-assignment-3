#include <stdio.h> 
#include <sys/time.h>
#include <unistd.h>

#ifdef _OPENMP
#include <omp.h>
#endif

void do_sleep(int, int);
double get_time();

// Timing function
double get_time() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return 1.0*time.tv_sec + time.tv_usec/1000000.0;
}

int main(int argc, char*argv[])
{
	double start_time, end_time;
	float result;

	start_time = get_time();

	// Simple parallel section
	// Causes all threads to run this code
	#pragma omp parallel
	#ifdef _OPENMP
		printf("OpenMP hello world from thread %i of %i!\n", omp_get_thread_num() + 1, omp_get_num_threads());
	#else
		printf("This isn't OpenMP! Did you compile without -fopenmp?\n");
	#endif

	// Parallel for directive
	// Automatically distributed iterations of the loop to threads

	#pragma omp parallel for
    for(int i = 0; i < 5; i++) {
		sleep(1);
	}

	// Parallel section directive
	// Manually define which parts are run in parallel
	#pragma omp parallel sections
	{
		#pragma omp section
		sleep(1);
		#pragma omp section
		sleep(1);
	}

	// Task example
	#pragma omp parallel
	#pragma omp single nowait
	{
		do_sleep(3,3);
	}

	end_time = get_time();
	printf("Time taken: %f\n", end_time-start_time);
}

void do_sleep(int width, int depth){
	if(depth == 0) return;

	for(int i = 0; i < width; i++) {
		#pragma omp task
		do_sleep(width, depth-1);
	}
	sleep(1);
	return;
}
