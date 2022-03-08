/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_changes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 13:17:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/08 16:13:59 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static	void	grab_forks(t_table *table, t_philosopher *philo, int left, int right)
{
	int timestamp;
	int dinner_time;

	pthread_mutex_lock(&table->lock[left]);
	philo_print("has taken a fork.\n", table, philo);
	pthread_mutex_lock(&table->lock[right]);
	philo_print("has taken a fork.\n", table, philo);
	timestamp = get_timestamp(table);
	philo_print("is eating\n", table, philo);
	philo->time_since_meal = timestamp;
	dinner_time = timestamp;
	while (get_timestamp(table) - dinner_time < table->eating_time)
		usleep(50);
	pthread_mutex_unlock(&table->lock[left]);
	pthread_mutex_unlock(&table->lock[right]);
}

void			eat(t_table *table, t_philosopher *philo)
{
	if (philo->start == 0)
		usleep(100 * (philo->id % 2));
	philo->start = 1;
	grab_forks(table, philo, philo->left, philo->right);
	philo->meals++;
}

void		sleep_and_think(t_table *table, t_philosopher *philo)
{
	int sleeping_time;

	sleeping_time = get_timestamp(table);
	philo_print("is sleeping\n", table, philo);
	while(get_timestamp(table) - sleeping_time < table->sleeping_time)
		usleep(50);
	philo_print("is thinking\n", table, philo);
}
