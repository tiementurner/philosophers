/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/06 22:13:13 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void	philo_thread(t_table *table)
// {
// 	int id;
// 	int fork_left;
// 	int	fork_right;

// 	id = 0;
// 	while (table->philo_list[id].threaded)
// 		id++;
// 	if (id == 0)
// 		fork_left = table->n_philosophers;
// 	else
// 		fork_left = id - 1;
// 	if(id == table->n_philosophers - 1)
// 		fork_right = 0;
// 	else
// 		fork_right = id + 1;
// 	if (table->fork_list[fork_left] && table->fork_list[fork_right])
// 		table->philo_list[id].state = EATING;
// }

static	int	synchronize_threads(t_table *table)
{
	int	id;


	id = 0;
	while (table->philo_list[id].threaded)
		id++;
	table->philo_list[id].threaded = 1;
	while (table->philo_list[0].threaded == 0);//
	return (id);
}
void *test_thread(void *arg)
{
	t_table *table;
	int		id;
	//int		count;
	// int 	fork_left;
	// int		fork_right;
	table = (t_table *) arg;
	id = synchronize_threads(table);
	while (*table->milliseconds_counted < 1)
	{
//		if(*table->milliseconds_counted > 1000)
		//	printf("%d\n", *table->milliseconds_counted);
	}
	printf("%d\n", *table->milliseconds_counted);
	return (0);
}

void	*timer_thread(void *arg)
{
	int volatile ms;
	t_table *table;

	table = (t_table *) arg;
	table->milliseconds_counted = &ms;
	gettimeofday(&table->time, NULL);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
	while (1)
	{
		gettimeofday(&table->time, NULL);
		if (table->time.tv_sec > table->previous_sec)
			ms += (1000000 - table->previous_usec + table->time.tv_usec) / 1000;
		else
			ms += (table->time.tv_usec - table->previous_usec) / 1000;
		table->previous_sec = table->time.tv_sec;
		table->previous_usec = table->time.tv_usec;
	//	printf("%d\n", ms);
	}
}

void	start_threading(t_table *table)
{
	pthread_t		thread_list[table->n_philosophers];
	pthread_t		timer;
	int				i;

//	pthread_mutex_init(&table->lock, NULL);

	pthread_create(&timer, NULL, timer_thread, table);
	i = 0;
	while (i < 1)
	{
		pthread_create(&thread_list[i], NULL, test_thread, table);
		i++;
	}
	while (table->philo_list[0].threaded == 0)

	i = 0;
	sleep(1);
	while (i < table->n_philosophers)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}
