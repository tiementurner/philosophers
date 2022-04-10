/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/28 17:22:18 by tblanker      #+#    #+#                 */
/*   Updated: 2022/04/10 15:06:21 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	main(int ac, char **av)
{
	t_table		table;

	if (!validate_input(&table, ac, av))
		return (0);
	if (!initialize(&table))
	{
		put_error("Oops! something went wrong during initialisation.", 0);
		return (0);
	}
	start_threading(&table);
	return (1);
}
