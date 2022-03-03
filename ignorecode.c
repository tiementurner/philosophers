#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct structje{
	int 			count;
	pthread_mutex_t	*lock;
	int				*fork_list;
	int				threaded;
}				t_struct;

void	*func(void *arg)
{
	t_struct *test;

	test = (t_struct *) arg;
	while(1)
	{
		pthread_mutex_lock(&test->lock[0]);
		if (test->fork_list[0] == 0)
			test->fork_list[0] = 1;
		pthread_mutex_unlock(&test->lock[0]);
		pthread_mutex_lock(&test->lock[0]);
		test->fork_list[0] = 0;
		pthread_mutex_unlock(&test->lock[0]);
		usleep(100);
		//while(1);
	}
}

int main()
{
	pthread_t		thread_1, thread_2;
	t_struct		test;
	pthread_mutex_t	mutex[2];

	test.fork_list = malloc(sizeof(int) * 2);
	test.fork_list[0] = 1;
	test.fork_list[1] = 1;
	test.lock = mutex;
	test.threaded = 0;
	test.count = 0;
	pthread_mutex_init(&test.lock[0], NULL);
	pthread_mutex_init(&test.lock[1], NULL);
	pthread_create(&thread_1, NULL, func, &test);
	pthread_create(&thread_2, NULL, func, &test);
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}