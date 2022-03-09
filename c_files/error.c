/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 14:16:11 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/09 15:12:53 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	put_error(char *error)
{
	ft_putstr_fd("Error:\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	printf("usage: ./philo [number] [number] [number] [number] \
(optional)[number]\n");
}

int	validate_input(t_table *table, int ac, char **av)
{
	if (ac < 5)
	{
		put_error("Not enough arguments(4 needed).");
		return (0);
	}
	if (ac > 6)
	{
		put_error("Too many arguments(max 5).");
		return (0);
	}
	if (ac == 6)
		table->number_of_meals = ft_atoi(av[5]);
	else
		table->number_of_meals = -1;
	table->time_until_starve = ft_atoi(av[2]);
	table->eating_time = ft_atoi(av[3]);
	table->sleeping_time = ft_atoi(av[4]);
	if (ft_atoi(av[1]) < 0 || table->eating_time < 0
		|| table->sleeping_time < 0 || table->time_until_starve < 0
		|| (table->number_of_meals < 0 && ac == 6))
	{
		put_error("Only positive numbers allowed as arguments.");
		return (0);
	}
	return (1);
}
