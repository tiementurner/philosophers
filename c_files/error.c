/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 14:16:11 by tblanker      #+#    #+#                 */
/*   Updated: 2022/02/05 17:29:31 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_error(char *error)
{
	ft_putstr_fd("Error:\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	exit(1);
}

void	argument_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 4 && ac != 5)
		put_error("Invalid amount of arguments(4 or 5 needed)");
	i = 0;
	while (av[i])
	{
		j = 0;
		while (i != 0 && av[i][j])
		{
			if (av[i][j] > '9' && av[i][j] < '0')
			{
				printf("hier :%c\n", av[i][j]);
				put_error("please enter only digits");
			
			}j++;
		}
		i++;
	}
}

