/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:18 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/24 14:51:58 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(int ac, char **av)
{
	t_table		table;

	if (!validate_input(&table, ac, av))
		return (0);
	table.n_philosophers = ft_atoi(av[1]);
	if (!initialize(&table))
	{
		put_error("Oops! something went wrong during initialisation.", 0);
		return (0);
	}
	start_threading(&table);
	free_machine(&table);
	return (1);
}
