/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 18:16:04 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/12 01:46:56 by tblanker      ########   odam.nl         */
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
		table->philo_list[i].id = i;
		table->philo_list[i].state = NOTHING;
		table->philo_list[i].threaded = 0;
		i++;
	}
}

void	initialize(t_table *table, char **av, int ac)
{
	int i;

	if (ac == 6)
	 	table->number_of_meals = ft_atoi(av[5]);
	table->n_philosophers = ft_atoi(av[1]);
	table->time_until_starve = ft_atoi(av[2]);
	table->eating_time = ft_atoi(av[3]) * 1000;
	table->sleeping_time  = ft_atoi(av[4]);
	i = 0;
	table->fork_list = malloc(sizeof(int) * table->n_philosophers);
	while (i < table->n_philosophers)
	{
		table->fork_list[i] = 1;
		i++;
	}
	create_philo_list(table);
}
