/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 19:21:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/09 14:14:17 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	void	*philo_thread(void *arg)
{
	t_table			*table;
	t_philosopher	*philo;

	table = (t_table *) arg;
	philo = &table->philo_list[get_philo_id(table)];
	while (1)
	{
		if (check_if_done(table, philo))
			break ;
		eat(table, philo);
		if (check_if_done(table, philo))
			break ;
		sleep_and_think(table, philo);
		if (check_if_done(table, philo))
			break ;
		check_stomach(table, philo);
	}
	return (0);
}

static	void	join_threads(pthread_t *thread_list, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

void	start_threading(t_table *table)
{
	int				i;

	i = 0;
	gettimeofday(&table->time, NULL);
	table->start_sec = table->time.tv_sec;
	table->start_usec = table->time.tv_usec;
	while (i < table->n_philosophers)
	{
		pthread_create(&table->thread_list[i], NULL, philo_thread, table);
		i++;
	}
	join_threads(table->thread_list, table->n_philosophers);
}
