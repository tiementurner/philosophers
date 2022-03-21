/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 17:50:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/21 14:01:03 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	check_if_die(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->n_philosophers)
		{
			check_stomach(table, &table->philo_list[i]);
			i++;
			pthread_mutex_lock(&table->check_lock);
			if (table->funeral == 1 || table->finished_eating
				== table->n_philosophers)
			{
				pthread_mutex_unlock(&table->check_lock);
				return ;
			}
			pthread_mutex_unlock(&table->check_lock);
			usleep(50);
		}
		usleep(50);
	}
}

int	check_if_done(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->check_lock);
	if (table->funeral)
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
		pthread_mutex_lock(&table->check_lock);
		table->funeral = 1;
		pthread_mutex_unlock(&table->check_lock);
		pthread_mutex_lock(&table->print_lock);
		printf("%-10d %d died.\n", timestamp, philo->id + 1);
		pthread_mutex_unlock(&table->print_lock);
	}
}
