/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 18:16:04 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/10 18:19:33 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static	int	destroy_state_mutexes(t_philosopher *list, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&list[i].state_lock);
		i++;
	}
	return (0);
}

static	int	create_philo_list(t_table *table)
{
	int	i;

	i = 0;
	table->philo_list = malloc(sizeof(t_philosopher) * table->n_philosophers);
	if (!table->philo->list)
		return (0);
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
		if (pthread_mutex_init(&table->philo_list[i].state_lock, NULL))
			return (destroy_state_mutexes(table->philo_list, i));
		i++;
	}
	return (1);
}

int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->sync_lock))
		return (0);
	if (pthread_mutex_init(&table->check_lock))
	{
		pthread_mutex_destroy(&table->sync_lock);
		return (0);
	}
	if (pthread_mutex_init(&table->print_lock))
		return (0);
	return (1);
}

void	initialize(t_table *table)
{
	int	i;

	table->funeral = 0;
	table->timestamp = 0;
	table->finished_eating = 0;
	i = 0;
	table->lock = malloc(sizeof(pthread_mutex_t) * table->n_philosophers);
	if (!table->lock)
		return (0);
	table->thread_list = malloc(sizeof(pthread_t) * table->n_philosophers);
	if (!table->thread_list)
	{
		free(table->lock);
		return (0);
	}
	while (i < table->n_philosophers)
	{
		pthread_mutex_init(&table->lock[i], NULL);
		i++;
	}
	if (!init_mutexes(table))
		return (0);
	if (!create_philo_list(table))
		return (0);
	return (1);
}
