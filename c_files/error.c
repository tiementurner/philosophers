/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 14:16:11 by tblanker      #+#    #+#                 */
/*   Updated: 2022/01/26 15:07:15 by tblanker      ########   odam.nl         */
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
