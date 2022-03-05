/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/04 00:42:56 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	int		synchronize_threads(t_table *table)
{
	int	id;

	id = 0;
	pthread_mutex_lock(&table->sync_lock);
	while (table->philo_list[id].threaded)
		id++;
	table->philo_list[id].threaded = 1;
	pthread_mutex_unlock(&table->sync_lock);
	// while (table->philo_list[table->n_philosophers - 1].threaded == 0)
	// 	usleep(50);//
	return (id);
}

int	get_timestamp(t_table *table)
{
	int timestamp;

	gettimeofday(&table->time, NULL);
	timestamp = (table->time.tv_sec - table->start_sec) * 1000 +
				(table->time.tv_usec / 1000 - table->start_usec / 1000);
	return(timestamp);
}

int		check_if_done(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->check_lock);
	if (philo->state == DEAD || table->funeral)
		return (1) ;
	if (philo->meals == table->number_of_meals)
	{
		table->finished_eating++;
		return (1);
	}
	pthread_mutex_unlock(&table->check_lock);
	return(0);
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
		if (check_if_done(table, philo))
			break ;
		try_to_eat(table, philo);
		if (check_if_done(table, philo))
			break ;
		sleep_and_think(table, philo);
		if (check_if_done(table, philo))
			break ;
		check_stomach(table, philo);
	}
	return (0);
}

static	void	join_threads(pthread_t *thread_list, int n, pthread_t pulse_check)
{
	int i;

	i = 0;
	while (i < n)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
	pthread_join(pulse_check, NULL);
}

void	start_threading(t_table *table)
{	
	pthread_t		thread_list[table->n_philosophers];
	int				i;
	pthread_t		pulse_checker;

	i = 0;
	gettimeofday(&table->time, NULL);
	table->start_sec = table->time.tv_sec;
	table->start_usec = table->time.tv_usec;
	while (i < table->n_philosophers)
	{
		pthread_create(&thread_list[i], NULL, philo_thread, table);
		i++;
	}
//	while (table->philo_list[table->n_philosophers - 1].threaded == 0)
	pthread_create(&pulse_checker, NULL, check_pulse_rates, table);
	join_threads(thread_list, table->n_philosophers, pulse_checker);
}
