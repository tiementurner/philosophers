/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 13:17:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/23 16:58:23 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static	void	use_forks(t_table *table, t_philosopher *philo)
{
	int	dinner_time;

	printf("%d %d is eating.\n", table->timestamp, philo->id + 1);
	philo->time_since_meal = table->timestamp;
	dinner_time = table->timestamp;
//	usleep(table->eating_time * 1000);
	while (table->timestamp - dinner_time < 200)
		usleep(1);
//	printf("%d %d is waiting for mutex of left fork\n", table->timestamp, philo->id + 1);
//	pthread_mutex_lock(&table->lock[philo->left]);
	table->fork_list[philo->left] = ON_TABLE;
//	pthread_mutex_unlock(&table->lock[philo->left]);
//	philo->left_taken = 0;
//	printf("%d %d is waiting for mutex of right fork\n", table->timestamp, philo->id + 1);
//	pthread_mutex_lock(&table->lock[philo->right]);
	table->fork_list[philo->right] = ON_TABLE;
//	pthread_mutex_unlock(&table->lock[philo->right]);
//	philo->right_taken = 0;
	philo->state = SLEEPING;
	philo->forks_in_hand = 0;
}

static	void	check_fork(t_table *table, t_philosopher *philo, int fork, int left_right)
{
	pthread_mutex_lock(&table->lock[fork]);
	if (table->fork_list[fork])
	{
		table->fork_list[fork] = TAKEN;
		if (left_right == 0)
			philo->left_taken = 1;
		if (left_right == 1)
			philo->right_taken = 1;
		printf("%d %d has taken a fork. fork num: %d\n", table->timestamp, philo->id + 1, fork + 1);
		philo->forks_in_hand++;
	}
	pthread_mutex_unlock(&table->lock[fork]);	
}

void			put_fork_back(t_table *table, t_philosopher *philo)
{
	if (philo->left_taken == 1)
	{
		pthread_mutex_lock(&table->lock[philo->left]);
		table->fork_list[philo->left] = ON_TABLE;
		pthread_mutex_unlock(&table->lock[philo->left]);
//		printf("%d %d has put fork back fork num :%d\n", table->timestamp, philo->id + 1, philo->left);
		philo->forks_in_hand = 0;
		philo->left_taken = 0;
	}
	if (philo->right_taken == 1)
	{
		pthread_mutex_lock(&table->lock[philo->right]);
		table->fork_list[philo->right] = ON_TABLE;
		pthread_mutex_unlock(&table->lock[philo->right]);
//		printf("%d %d has put fork back\n", table->timestamp, philo->id + 1);
		philo->forks_in_hand = 0;
		philo->right_taken = 0;
	}
	usleep(philo->id % 2 * 100);
}

void			try_to_eat(t_table *table, t_philosopher *philo)
{
	if (table->n_philosophers == 1)
		return ;
	if (philo->start == 0)
		usleep(10000 * (philo->id % 2));
	philo->start = 1;
	check_fork(table, philo, philo->left, 0);
	check_fork(table, philo, philo->right, 1);
//	printf("forks in hand: %d---%d----%d\n", philo->forks_in_hand, philo->left_taken, philo->right_taken);
	if (philo->forks_in_hand == 1)
		put_fork_back(table, philo);
	if (philo->forks_in_hand == 2)
		use_forks(table, philo);
}
