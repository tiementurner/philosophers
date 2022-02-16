/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/16 17:17:53 by tblanker      ########   odam.nl         */
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

void	use_forks(t_table *table, t_philosopher *philo)
{
	printf("%d %d is eating.\n", table->timestamp, philo->id + 1);
	philo->time_since_meal = table->timestamp;
	usleep(table->eating_time * 1000);
	pthread_mutex_lock(&table->lock[philo->left]);
	table->fork_list[philo->left] = ON_TABLE;
	pthread_mutex_unlock(&table->lock[philo->left]);
	pthread_mutex_lock(&table->lock[philo->right]);
	table->fork_list[philo->right] = ON_TABLE;
	pthread_mutex_unlock(&table->lock[philo->right]);
	philo->state = SLEEPING;
	philo->forks_in_hand = 0;
}

void	check_fork(t_table *table, t_philosopher *philo, int fork)
{
	pthread_mutex_lock(&table->lock[fork]);
	if (table->fork_list[fork])
	{
		table->fork_list[fork] = TAKEN;
		printf("%d %d has taken a fork.\n", table->timestamp, philo->id + 1);
		philo->forks_in_hand++;
	}
	pthread_mutex_unlock(&table->lock[fork]);	
}

void	try_to_eat(t_table *table, t_philosopher *philo)
{
	static int	start;

	start = 0;
	if (table->n_philosophers == 1)
		return ;
	if (start == 0)
		usleep(100000 * (philo->id % 2));
	start = 1;
	check_fork(table, philo, philo->left);
	check_fork(table, philo, philo->right);
	if (philo->forks_in_hand == 2)
		use_forks(table, philo);
}

void *test_thread(void *arg)
{
	t_table 		*table;
	t_philosopher 	*philo;
	int				id;

	table = (t_table *) arg;
	id = synchronize_threads(table);
	philo = &table->philo_list[id];
	while(1)
	{
		if (table->funeral)
			break;
		try_to_eat(table, philo);
		if (table->timestamp - philo->time_since_meal > table->time_until_starve)
		{
			printf("%d %d died.\n", table->timestamp, philo->id + 1);
			philo->state = DEAD;
			break ;
		}
		if (philo->state == SLEEPING)
		{
			printf("%d %d is sleeping.\n", table->timestamp, philo->id + 1);
			usleep(table->sleeping_time * 1000);
			philo->state = THINKING;
			printf("%d %d is thinking.\n", table->timestamp, philo->id + 1);
		}
	}
	return (0);
}

void	check_pulse_rates(t_table *table, pthread_t *thread_list)
{
	int i;

	i = 0;
	while (i < table->n_philosophers)
	{
		if (table->philo_list[i].state == DEAD)
		{
			get_timestamp(table);
			printf("ending millisecond: %d\n", table->timestamp);
			table->funeral = 1;
			i = 0;
			while (i < table->n_philosophers)
			{
				pthread_join(thread_list[i], NULL);
				i++;
			}
			exit(1);
		}
		i++;
	}
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
		check_pulse_rates(table, thread_list);
	}
}
