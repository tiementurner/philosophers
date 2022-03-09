/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 17:50:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/09 17:07:22 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_if_done(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->check_lock);
	if (philo->state == DEAD || table->funeral)
	{
		pthread_mutex_unlock(&table->check_lock);
		return (1);
	}
	if (philo->meals == table->number_of_meals)
	{
		table->finished_eating++;
		pthread_mutex_unlock(&table->check_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->check_lock);
	return (0);
}

void	check_stomach(t_table *table, t_philosopher *philo)
{
	int	timestamp;

	timestamp = get_timestamp(table);
	if (timestamp - philo->time_since_meal > table->time_until_starve)
	{
		if (check_if_done(table, philo))
			return ;
		pthread_mutex_lock(&philo->state_lock);
		table->funeral = 1;
		pthread_mutex_unlock(&philo->state_lock);
		pthread_mutex_lock(&table->print_lock);
		usleep(1000);
		printf("%-10d %d died.\n", timestamp, philo->id + 1);
		pthread_mutex_unlock(&table->print_lock);
	}
}
