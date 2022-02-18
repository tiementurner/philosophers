#include <sys/time.h>

typedef struct structje{
	char *array;
}				t_struct;

void	func(t_struct *pointer)
{
	int i = 0;

	while (pointer->array[i])
	{
		printf("%c,", pointer->array[i]);
		i++;
	}
}

int main()
{
	struct 	timeval time;
	int 	timestamp;
	int prev_sec, prev_usec;
	gettimeofday(&time);
	prev_sec = time.tv_sec;
	prev_usec = time.tv_usec;
	timestamp += (time.tv_sec - prev_sec) * 1000 + (time.tv_usec / 1000 - prev_usec / 1000);
	prev_sec 
}