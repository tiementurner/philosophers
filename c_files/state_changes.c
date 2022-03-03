/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_changes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 13:17:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/03 18:21:21 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static	void	use_forks(t_table *table, t_philosopher *philo)
{
	int	dinner_time;

	printf("%d %d is eating.\n", table->timestamp, philo->id + 1);
	philo->time_since_meal = table->timestamp;
	dinner_time = table->timestamp;
	while (table->timestamp - dinner_time < table->eating_time)
		usleep(50);
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
//	static int start;

	//if (start == 0)
	printf("id: %d    %d --- %p\n", philo->id + 1, fork + 1, &table->lock[fork]);
	// start = 1;
	//usleep(100);
	pthread_mutex_lock(&table->lock[fork]);
	if (table->fork_list[fork])
	{
		printf("%d is in mutex from fork; %d, adress: %p\n", philo->id + 1, fork + 1, &table->lock[fork]);
		printf("%d %d has taken a fork.\n", table->timestamp, philo->id + 1);
		table->fork_list[fork] = TAKEN;
		usleep(100);
		philo->forks_in_hand++;
	}
	pthread_mutex_unlock(&table->lock[fork]);
}

void			try_to_eat(t_table *table, t_philosopher *philo)
{
	if (table->n_philosophers == 1)
		return ;
	// if (philo->start == 0)
	// 	usleep(10000 * (philo->id % 2));
	philo->start = 1;
	check_fork(table, philo, philo->left);
	check_fork(table, philo, philo->right);
	while(1);
	if (philo->forks_in_hand == 2)
	{
		use_forks(table, philo);
		philo->meals++;
	}
}

void		sleep_and_think(t_table *table, t_philosopher *philo)
{
	int sleeping_time;

	if (philo->state == SLEEPING)
	{
		sleeping_time = table->timestamp;
		printf("%d %d is sleeping.\n", table->timestamp, philo->id + 1);
		while(table->timestamp - sleeping_time < table->sleeping_time)
			usleep(50);
		philo->state = THINKING;
		printf("%d %d is thinking.\n", table->timestamp, philo->id + 1);
	}
}
