/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_changes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 13:17:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/23 20:47:44 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	grab_forks(t_table *table, t_philosopher *philo)
{
	int	timestamp;

	pthread_mutex_lock(&table->lock[philo->left]);
	philo_print("has taken a fork.\n", table, philo);
	if (philo->right == philo->left)
	{
		timestamp = get_timestamp(table);
		pthread_mutex_unlock(&table->lock[philo->left]);
		while (get_timestamp(table) - timestamp < table->time_until_starve + 1)
			usleep(500);
		return ;
	}
	pthread_mutex_lock(&table->lock[philo->right]);
	philo_print("has taken a fork.\n", table, philo);
	philo_print("is eating\n", table, philo);
	pthread_mutex_lock(&table->check_lock);
	philo->time_since_meal = get_timestamp(table);
	pthread_mutex_unlock(&table->check_lock);
	while (get_timestamp(table) - philo->time_since_meal < table->eating_time)
		usleep(500);
	pthread_mutex_unlock(&table->lock[philo->left]);
	pthread_mutex_unlock(&table->lock[philo->right]);
}

void	eat(t_table *table, t_philosopher *philo)
{
	if (philo->start == 0)
		usleep((1000 * table->n_philosophers) * (philo->id % 2));
	philo->start = 1;
	grab_forks(table, philo);
	philo->meals++;
}

void	sleep_and_think(t_table *table, t_philosopher *philo)
{
	int	sleeping_time;

	sleeping_time = get_timestamp(table);
	philo_print("is sleeping\n", table, philo);
	while (get_timestamp(table) - sleeping_time < table->sleeping_time)
	{
		if (get_timestamp(table) - philo->time_since_meal
			> table->time_until_starve)
			return ;
		usleep(500);
	}
	philo_print("is thinking\n", table, philo);
}
