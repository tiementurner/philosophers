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

int main(int ac, char **av)
{
	t_table		table;

	if (!validate_input(&table, ac, av))
		return (0);
	initialize(&table);
	start_threading(&table);
	while (1);
	return (1);
}
