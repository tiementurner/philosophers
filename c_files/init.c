/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 18:16:04 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/16 17:16:10 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	create_philo_list(t_table *table)
{
	int	i;
	int	max;

	max = table->n_philosophers;
	i = 0;
	table->philo_list = malloc(sizeof(t_philosopher) * max);
	while (i < max)
	{
		table->philo_list[i].left = i;
		table->philo_list[i].right = i - 1;
		if (i == 0)
			table->philo_list[i].right = max - 1;
		table->philo_list[i].id = i;
		table->philo_list[i].state = NOTHING;
		table->philo_list[i].threaded = 0;
		table->philo_list[i].time_since_meal = 0;
		table->philo_list[i].forks_in_hand = 0;
		i++;
	}
}

void	initialize(t_table *table, char **av, int ac)
{
	int i;
	pthread_mutex_t mutex_list[ft_atoi(av[1])];

	if (ac == 6)
	 	table->number_of_meals = ft_atoi(av[5]);
	table->n_philosophers = ft_atoi(av[1]);
	table->time_until_starve = ft_atoi(av[2]);
	table->eating_time = ft_atoi(av[3]);
	table->sleeping_time  = ft_atoi(av[4]);
	table->funeral = 0;
	i = 0;
	table->fork_list = malloc(sizeof(int) * table->n_philosophers);
	table->lock = mutex_list;
	while (i < table->n_philosophers)
	{
		table->fork_list[i] = 1;
		pthread_mutex_init(&table->lock[i], NULL);
		i++;
	}
	create_philo_list(table);
}
