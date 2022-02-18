/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 13:17:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/18 17:03:38 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static	void	use_forks(t_table *table, t_philosopher *philo)
{
	printf("%d %d is eating.\n", table->timestamp, philo->id + 1);
	philo->time_since_meal = table->timestamp;
	usleep(table->eating_time * 1000);
	pthread_mutex_lock(&table->lock[philo->left]);
	table->fork_list[philo->left] = ON_TABLE;
	pthread_mutex_unlock(&table->lock[philo->left]);
	pthread_mutex_lock(&table->lock[philo->right]);
	table->fork_list[philo->right] = ON_TABLE;
	pthread_mutex_unlock(&table->lock[philo->right]);
	philo->state = SLEEPING;
	philo->forks_in_hand = 0;
}

static	void	check_fork(t_table *table, t_philosopher *philo, int fork)
{
	pthread_mutex_lock(&table->lock[fork]);
	if (table->fork_list[fork])
	{
		table->fork_list[fork] = TAKEN;
		printf("%d %d has taken a fork. fork number: %d\n", table->timestamp, philo->id + 1, fork);
		philo->forks_in_hand++;
	}
	pthread_mutex_unlock(&table->lock[fork]);	
}

void			put_fork_back(t_table *table, t_philosopher *philo)
{
	if (table->fork_list[philo->left] == TAKEN)
	{
		pthread_mutex_lock(&table->lock[philo->left]);
		table->fork_list[philo->left] = ON_TABLE;
		pthread_mutex_unlock(&table->lock[philo->right]);
		philo->forks_in_hand = 0;
	}
	if (table->fork_list[philo->right] == TAKEN)
	{
		pthread_mutex_lock(&table->lock[philo->right]);
		table->fork_list[philo->right] = ON_TABLE;
		pthread_mutex_unlock(&table->lock[philo->right]);
		philo->forks_in_hand = 0;
	}
}

void			try_to_eat(t_table *table, t_philosopher *philo)
{
	if (table->n_philosophers == 1)
		return ;
	if (philo->start == 0)
		usleep(10000 * (philo->id % 2));
	philo->start = 1;
	check_fork(table, philo, philo->left);
	check_fork(table, philo, philo->right);
	if (philo->forks_in_hand == 1)
		put_fork_back(table, philo);
	if (philo->forks_in_hand == 2)
		use_forks(table, philo);
}
