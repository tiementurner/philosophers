/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 14:16:11 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/02 15:38:00 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_error(char *error)
{
	ft_putstr_fd("Error:\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	printf("usage: ./philo [number] [number] [number] [number] \
(optional)[number]\n");
}

int		validate_input(t_table *table, int ac, char **av)
{
	if (ac < 5)
	{
		put_error("Not enough arguments(4 needed).");
		return (0);
	}
	if (ac > 6)
	{
		return (0);
		put_error("Too many arguments(max 5).");
	}
	if (ac == 6)
	 	table->number_of_meals = ft_atoi(av[5]);
	else
		table->number_of_meals = -1;
	table->n_philosophers = ft_atoi(av[1]);
	table->time_until_starve = ft_atoi(av[2]);
	table->eating_time = ft_atoi(av[3]);
	table->sleeping_time  = ft_atoi(av[4]);
	if (table->n_philosophers < 0 || table->eating_time < 0 ||
		table->sleeping_time < 0 || table->time_until_starve < 0 ||
		(table->number_of_meals < 0 && ac == 6))
	{
		put_error("Only positive numbers allowed as arguments.");
		return (0);
	}
	return (1);
}

