/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_changes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 13:17:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/10 19:50:37 by tblanker      ########   odam.nl         */
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
			usleep(50);
		return ;
	}
	pthread_mutex_lock(&table->lock[philo->right]);
	philo_print("has taken a fork.\n", table, philo);
	philo_print("is eating\n", table, philo);
	philo->time_since_meal = get_timestamp(table);
	while (get_timestamp(table) - philo->time_since_meal < table->eating_time)
		usleep(50);
	pthread_mutex_unlock(&table->lock[philo->left]);
	pthread_mutex_unlock(&table->lock[philo->right]);
}

void	eat(t_table *table, t_philosopher *philo)
{
	if (philo->start == 0)
		usleep(100 * (philo->id % 2));
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
		usleep(50);
	philo_print("is thinking\n", table, philo);
}
