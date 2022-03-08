/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 15:14:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/08 17:34:05 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		get_philo_id(t_table *table)
{
	int	id;

	id = 0;
	pthread_mutex_lock(&table->sync_lock);
	while (table->philo_list[id].threaded)
		id++;
	table->philo_list[id].threaded = 1;
	pthread_mutex_unlock(&table->sync_lock);
	return (id);
}

int		get_timestamp(t_table *table)
{
	int timestamp;

	gettimeofday(&table->time, NULL);
	timestamp = (table->time.tv_sec - table->start_sec) * 1000 +
				(table->time.tv_usec / 1000 - table->start_usec / 1000);
	return(timestamp);
}

void	philo_print(char *message, t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->print_lock);
	if (check_if_done(table, philo))
	{
		pthread_mutex_unlock(&table->print_lock);
		return ;
	}
	printf("%d %d %s", get_timestamp(table), philo->id + 1, message);
	pthread_mutex_unlock(&table->print_lock);
}
