#include <omp.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main()
{
	int val;
	omp_lock_t lock_val;
	val = 0;
	omp_init_lock(&lock_val);
	#pragma omp parallel num_threads(6)
	while(val < 6)
	{
		omp_set_lock(&lock_val);
		if(val == omp_get_thread_num())
		{
			val++;
			printf("%d ", omp_get_thread_num());
		}
		omp_unset_lock(&lock_val);
	}
	printf("\n");
	
	int food;
	omp_lock_t lock_food;
	food = 0;
	omp_init_lock(&lock_food);
	omp_set_num_threads(6);
	#pragma omp parallel shared(food, lock_food)
	{
		if(omp_get_thread_num() & 1)
		{
			for(int i = 0; i < 10; i++)
			{
				omp_set_lock(&lock_food);
				food++;
				printf("%d Feeding... %d+\n", i, food);
				omp_unset_lock(&lock_food);
				sleep(rand()%2 + 2);
			}
		}
		else
		{
			for(int j = 0; j < 10; j++)
			{
				omp_set_lock(&lock_food);
				if(food > 0)
				{
					--food;
					printf("%d Eating... %d-\n", j, food);
				}
				else
					printf("%d Waiting...\n", j);
				omp_unset_lock(&lock_food);
				sleep(rand()%2 + 1);
			}
		}
	}
	#pragma omp barrier
	return 0;
}


