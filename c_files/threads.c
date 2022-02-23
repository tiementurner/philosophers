/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/23 16:34:45 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	int		synchronize_threads(t_table *table)
{
	int	id;

	id = 0;
	while (table->philo_list[id].threaded)
		id++;
	table->philo_list[id].threaded = 1;
	while (table->philo_list[0].threaded == 0);//
	return (id);
}

static	void	get_timestamp(t_table *table)
{
	gettimeofday(&table->time, NULL);
	table->timestamp += (table->time.tv_sec - table->previous_sec) * 1000 +
						(table->time.tv_usec / 1000 - table->previous_usec / 1000);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
}

void		check_stomach(t_table *table, t_philosopher *philo)
{
	if (table->timestamp - philo->time_since_meal > table->time_until_starve)
	{
		printf("%d %d died.\n", table->timestamp, philo->id + 1);
		philo->state = DEAD;
	}
}

void		sleep_and_think(t_table *table, t_philosopher *philo)
{
	int sleeping_time;

	if (philo->state == SLEEPING)
	{
		sleeping_time = table->timestamp;
		printf("%d %d is sleeping.\n", table->timestamp, philo->id + 1);
		while(table->timestamp - sleeping_time < 200)
			usleep(1);
		//printf("%d %d is done sleeping.\n", table->timestamp, philo->id + 1);
		philo->state = THINKING;
		printf("%d %d is thinking.\n", table->timestamp, philo->id + 1);
	}
}

static	void	*philo_thread(void *arg)
{
	t_table 		*table;
	t_philosopher 	*philo;
	int				id;

	table = (t_table *) arg;
	id = synchronize_threads(table);
	philo = &table->philo_list[id];
	while(1)
	{
		try_to_eat(table, philo);
		sleep_and_think(table, philo);
		check_stomach(table, philo);
		if (philo->state == DEAD || table->funeral)
			break ;
	}
	return (0);
}

void		*check_pulse_rates(void *arg)
{
	int i;
	t_table	*table;

	table = (t_table *) arg;
	i = 0;
	while (!table->funeral)
	{
		i = 0;
		while (i < table->n_philosophers)
		{
			if (table->philo_list[i].state == DEAD)
			{
				get_timestamp(table);
				printf("ending millisecond: %d\n", table->timestamp);
				table->funeral = 1;
				// i = 0;
				// while (i < table->n_philosophers)
				// {
				// 	pthread_join(thread_list[i], NULL);
				// 	i++;
				// }
				exit(1);
			}
			i++;
		}
	}
	return (0);
}

void	start_threading(t_table *table)
{	
	pthread_t		thread_list[table->n_philosophers];
	int				i;
	pthread_t		pulse_checker = NULL;

	i = 0;
	while (i < table->n_philosophers)
	{
		pthread_create(&thread_list[i], NULL, philo_thread, table);
		i++;
	}
	while (table->philo_list[0].threaded == 0)
	table->timestamp = 0;
	pthread_create(&pulse_checker, NULL, check_pulse_rates, table);
	gettimeofday(&table->time, NULL);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
	while (1)
	{
		get_timestamp(table);
	//	check_pulse_rates(table, thread_list);
	}
}
