/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:18 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/03 12:49:27 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	validate_input(t_table *table, int ac, char **av)
{
	if (ac < 5)
		put_error("Not enough arguments(4 needed).");
	if (ac > 6)
		put_error("Too many arguments(max 5).");
	if (ac == 6)
	 	table->number_of_meals = ft_atoi(av[5]);
	table->n_philosophers = ft_atoi(av[1]);
	table->time_until_starve = ft_atoi(av[2]);
	table->eating_time = ft_atoi(av[3]);
	table->sleeping_time  = ft_atoi(av[4]);
	if (table->n_philosophers < 0 || table->eating_time < 0 ||
		table->sleeping_time < 0 || table->time_until_starve < 0 ||
		(table->number_of_meals < 0 && ac == 6))
		put_error("Only positive numbers allowed as arguments.");
}

int main(int ac, char **av)
{
	t_table		table;

	validate_input(&table, ac, av);
	initialize(&table, av, ac);
	//while (1);
	start_threading(&table);
	return (0);
}
