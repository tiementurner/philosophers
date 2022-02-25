/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/25 17:53:17 by tblanker      ########   odam.nl         */
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

void	get_timestamp(t_table *table)
{
	gettimeofday(&table->time, NULL);
	table->timestamp += (table->time.tv_sec - table->previous_sec) * 1000 +
						(table->time.tv_usec / 1000 - table->previous_usec / 1000);
	table->previous_sec = table->time.tv_sec;
	table->previous_usec = table->time.tv_usec;
}

static	void	*philo_thread(void *arg)
{
	t_table 		*table;
	t_philosopher 	*philo;
	int				id;

	table = (t_table *) arg;
	id = synchronize_threads(table);
	philo = &table->philo_list[id];
	while(!table->funeral)
	{
		try_to_eat(table, philo);
		if (philo->state == DEAD || table->funeral)
			break ;
		sleep_and_think(table, philo);
		if (philo->state == DEAD || table->funeral)
			break ;
		check_stomach(table, philo);
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
	while (!table->funeral)
	{
		get_timestamp(table);
		usleep(50);
	}
}
