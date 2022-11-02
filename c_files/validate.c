/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 14:16:11 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/10 18:49:30 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	put_error(char *error, int usage)
{
	printf("Error:\n%s\n", error);
	if (usage == 1)
		printf("usage: ./philo [number] [number] [number] [number] \
(optional)[number]\n");
}

static	int	digit_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	convert_to_int(t_table *table, char **av)
{
	table->n_philosophers = ft_atoi(av[1]);
	table->time_until_starve = ft_atoi(av[2]);
	table->eating_time = ft_atoi(av[3]);
	table->sleeping_time = ft_atoi(av[4]);
	return (1);
}

int	validate_input(t_table *table, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		put_error("Invalid amount of arguments(4 needed).", 1);
		return (0);
	}
	if (ac == 6)
		table->number_of_meals = ft_atoi(av[5]);
	else
		table->number_of_meals = -1;
	if (!digit_check(av))
	{
		put_error("Only digits allowed.(no minus sign)", 0);
		return (0);
	}
	if (!convert_to_int(table, av))
		return (0);
	if (ft_atoi(av[1]) < 0 || table->eating_time < 0
		|| table->sleeping_time < 0 || table->time_until_starve < 0
		|| (table->number_of_meals < 0 && ac == 6))
	{
		put_error("Only positive numbers allowed as arguments.", 0);
		return (0);
	}
	return (1);
}
