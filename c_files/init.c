/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 18:16:04 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/08 16:07:33 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	create_philo_list(t_table *table)
{
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philosopher) * table->n_philosophers);
	while (i < table->n_philosophers)
	{
		table->philo_list[i].left = i;
		table->philo_list[i].right = i - 1;
		if (i == 0)
			table->philo_list[i].right = table->n_philosophers - 1;
		table->philo_list[i].id = i;
		table->philo_list[i].state = ALIVE;
		table->philo_list[i].threaded = 0;
		table->philo_list[i].time_since_meal = 0;
		table->philo_list[i].forks_in_hand = 0;
		table->philo_list[i].start = 0;
		table->philo_list[i].meals = 0;
		pthread_mutex_init(&table->philo_list[i].state_lock, NULL);
		i++;
	}
}

void	initialize(t_table *table)
{
	int i;

	table->funeral = 0;
	table->timestamp = 0;
	table->finished_eating = 0;
	i = 0;
	table->lock = malloc(sizeof(pthread_mutex_t) * table->n_philosophers);
	table->fork_list = malloc(sizeof(int) * table->n_philosophers);
	while (i < table->n_philosophers)
	{
		table->fork_list[i] = 1;
		pthread_mutex_init(&table->lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->sync_lock, NULL);
	pthread_mutex_init(&table->check_lock, NULL);
	create_philo_list(table);
}
