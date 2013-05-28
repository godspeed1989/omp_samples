#include <omp.h>
#include <cstdio>


int main()
{
	int ncores = omp_get_num_procs();
	printf("Total %d cores.\n", ncores);
	omp_set_num_threads(ncores * 2);
	printf("Max %d threads in omp.\n", omp_get_max_threads());
	
	printf("+++++Parallel\n");
	#pragma omp parallel
	{
		if(omp_in_parallel())
			printf("Hello, World\n");
	}
	
	printf("+++++Nested Parallel\n");
	omp_set_nested(true);
	#pragma omp parallel num_threads(2)
	{
		printf("Hello, TID=%d, level=%d\n", omp_get_thread_num(), omp_get_level());
		#pragma omp parallel num_threads(2)
		{
			printf("World! TID=%d, level=%d\n", omp_get_thread_num(), omp_get_level());
		}
	}
	
	printf("+++++Parallel for\n");
	int sum = 0;
	#pragma omp parallel for
	for(int i=0; i<4; i++)
	{
		sum += i;
		printf("i=%d, TID=%d\n", i, omp_get_thread_num());
	}
	printf("sum is %d\n", sum);
	
	printf("+++++Parallel if\n");
	int n = 11;
	#pragma omp parallel if (n>10) num_threads(2)
	{
		printf("if clause. TID=%d\n", omp_get_thread_num());
	}
	
	printf("+++++Parallel sections\n");
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
				printf("section 1, TID=%d\n", omp_get_thread_num());
			#pragma omp section
				printf("section 2, TID=%d\n", omp_get_thread_num());
		}
		#pragma omp sections
		{
			#pragma omp section
				printf("section 3, TID=%d\n", omp_get_thread_num());
			#pragma omp section
				printf("section 4, TID=%d\n", omp_get_thread_num());
		}
	}
	
	printf("+++++Single sections\n");
	#pragma omp parallel num_threads(2)
	{
		printf("parallel region BEFORE single.\n");
		#pragma omp single
		{
			printf("I am SINGLE!\n");
		}
		printf("parallel region AFTER single.\n");
	}
	return 0;
}
