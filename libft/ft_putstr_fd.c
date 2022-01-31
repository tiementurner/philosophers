/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 20:23:48 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:24 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	if (!s)
		return ;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		write(fd, &s[i], 1);
		i++;
	}
}
