/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   death_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 17:50:28 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/04 16:02:13 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_if_done(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->check_lock);
	if (philo->state == DEAD || table->funeral)
		return (1);
	if (philo->meals == table->number_of_meals)
	{
		table->finished_eating++;
		pthread_mutex_unlock(&table->check_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->check_lock);
	return(0);
}

int			twenty_five_line_rule(t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	pthread_mutex_lock(&table->check_lock);
	if (philo->state == DEAD || table->finished_eating == table->n_philosophers)
	{
		pthread_mutex_lock(&table->print_lock);
		printf("ending millisecond: %d\n", get_timestamp(table));
		pthread_mutex_unlock(&table->print_lock);
		table->funeral = 1;
		pthread_mutex_unlock(&philo->state_lock);
		pthread_mutex_unlock(&table->check_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->state_lock);
	pthread_mutex_unlock(&table->check_lock);
	return (1);
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
			if (!twenty_five_line_rule(table, &table->philo_list[i]))
				return (0);
			i++;
		}
		usleep(50);
	}
	return (0);
}

void		check_stomach(t_table *table, t_philosopher *philo)
{
	if (get_timestamp(table) - philo->time_since_meal > table->time_until_starve)
	{
		pthread_mutex_lock(&table->print_lock);
		printf("%d %d died.\n", get_timestamp(table), philo->id + 1);
		pthread_mutex_unlock(&table->print_lock);
		pthread_mutex_lock(&philo->state_lock);
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->state_lock);
	}
}
