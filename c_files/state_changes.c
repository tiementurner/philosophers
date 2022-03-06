/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state_changes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 13:17:39 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/04 16:00:33 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	philo_print(char *message, t_table *table, t_philosopher *philo)
{
	pthread_mutex_lock(&table->print_lock);
	if (check_if_done(table, philo))
	{
		pthread_mutex_unlock(&table->print_lock);
		return ;
	}
	printf("%d %d %s", get_timestamp(table), philo->id +1, message);
	pthread_mutex_unlock(&table->print_lock);
}

static	void	use_forks(t_table *table, t_philosopher *philo)
{
	int	dinner_time;
	int	timestamp;

	timestamp = get_timestamp(table);
	philo_print("is eating\n", table, philo);
	philo->time_since_meal = timestamp;
	dinner_time = timestamp;
	while (get_timestamp(table) - dinner_time < table->eating_time)
		usleep(50);
	pthread_mutex_lock(&table->lock[philo->left]);
	table->fork_list[philo->left] = ON_TABLE;
	pthread_mutex_unlock(&table->lock[philo->left]);
	pthread_mutex_lock(&table->lock[philo->right]);
	table->fork_list[philo->right] = ON_TABLE;
	pthread_mutex_unlock(&table->lock[philo->right]);
	pthread_mutex_lock(&philo->state_lock);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->state_lock);
	philo->forks_in_hand = 0;
}

static	void	check_fork(t_table *table, t_philosopher *philo, int fork)
{
	pthread_mutex_lock(&table->lock[fork]);
	if (table->fork_list[fork])
	{
		if (check_if_done(table, philo))
		{
			pthread_mutex_unlock(&table->lock[fork]);
			return ;
		}
		philo_print("has taken a fork.\n", table, philo);
		table->fork_list[fork] = TAKEN;
		philo->forks_in_hand++;
	}
	pthread_mutex_unlock(&table->lock[fork]);
}

void			try_to_eat(t_table *table, t_philosopher *philo)
{
	if (philo->start == 0)
		usleep(100 * (philo->id % 2));
	philo->start = 1;
	check_fork(table, philo, philo->left);
	check_fork(table, philo, philo->right);
	if (philo->forks_in_hand == 2)
	{
		use_forks(table, philo);
		philo->meals++;
	}
}

void		sleep_and_think(t_table *table, t_philosopher *philo)
{
	int sleeping_time;
	int timestamp;

	if (philo->state == SLEEPING)
	{
		timestamp = get_timestamp(table);
		sleeping_time = timestamp;
		philo_print("is sleeping\n", table, philo);
		while(get_timestamp(table) - sleeping_time < table->sleeping_time)
			usleep(50);
		pthread_mutex_lock(&philo->state_lock);
		philo->state = THINKING;
		pthread_mutex_unlock(&philo->state_lock);
		philo_print("is thinking\n", table, philo);
	}
}
