/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/15 16:47:02 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	get_timestamp(t_table *table)
{
	gettimeofday(&table->time, NULL);
	table->timestamp += (table->time.tv_sec - table->previous_sec) * 1000 +
						(table->time.tv_usec / 1000 - table->previous_usec / 1000);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
}

void	try_to_eat(t_table *table, t_philosopher *philo)
{
	int left_fork;
	int	right_fork;

	if (table->n_philosophers == 1)
		return ;
	left_fork = philo->id;
	right_fork = philo->id - 1;
	if (philo->id == 0)
		right_fork = table->n_philosophers - 1;
	if (philo->id == table->n_philosophers - 1)
		left_fork = 0;
//	printf("ms: %d id: %d----left: %d, right:%d\n", table->time.tv_usec, philo->id + 1, table->fork_list[left_fork], table->fork_list[right_fork]);
	pthread_mutex_lock(&table->lock[left_fork]);
	if (table->fork_list[left_fork])
	{
		table->fork_list[left_fork] = TAKEN;
		printf("%d %d has taken a fork.\n", table->timestamp, philo->id + 1);
		philo->forks_in_hand++;
	}
	pthread_mutex_unlock(&table->lock[left_fork]);
	pthread_mutex_lock(&table->lock[right_fork]);
	if (table->fork_list[right_fork])
	{
		table->fork_list[right_fork] = TAKEN;
		printf("%d %d has taken a fork.\n", table->timestamp, philo->id + 1);
		philo->forks_in_hand++;
	}
	pthread_mutex_unlock(&table->lock[right_fork]);
	if (philo->forks_in_hand == 2)
	{
		printf("%d %d is eating.\n", table->timestamp, philo->id + 1);
		philo->time_since_meal = table->timestamp;
		usleep(table->eating_time * 1000);
		pthread_mutex_lock(&table->lock[left_fork]);
		table->fork_list[left_fork] = ON_TABLE;
		pthread_mutex_unlock(&table->lock[right_fork]);
		pthread_mutex_lock(&table->lock[right_fork]);
		table->fork_list[right_fork] = ON_TABLE;
		pthread_mutex_unlock(&table->lock[right_fork]);
		philo->state = SLEEPING;
	}
}

void *test_thread(void *arg)
{
	t_table 		*table;
	t_philosopher 	*philo;
	int				id;
	int				i;

	i = 0;
	table = (t_table *) arg;
	id = synchronize_threads(table);
	philo = &table->philo_list[id];
	while(1)
	{
		try_to_eat(table, philo);
		if (table->timestamp - philo->time_since_meal > table->time_until_starve)
		{
			printf("%d %d died.\n", table->timestamp, philo->id + 1);
			break ;
		}
		if (philo->state == SLEEPING)
		{
			printf("%d %d is sleeping.\n", table->timestamp, philo->id + 1);
			usleep(table->sleeping_time * 1000);
			philo->state = THINKING;
			printf("%d %d is thinking.\n", table->timestamp, philo->id + 1);
		}
		i++;
	}
	return (0);
}



void	start_threading(t_table *table)
{
	pthread_t		thread_list[table->n_philosophers];
	int				i;

	i = 0;

	while (i < table->n_philosophers)
	{
		pthread_create(&thread_list[i], NULL, test_thread, table);
		i++;
	}
	while (table->philo_list[0].threaded == 0)
	table->timestamp = 0;
	gettimeofday(&table->time, NULL);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
	while (1)
	{
		get_timestamp(table);
	}
	i = 0;
	while (i < table->n_philosophers)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}
