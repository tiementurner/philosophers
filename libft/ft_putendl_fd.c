/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 20:28:52 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:17 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
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
	ft_putchar_fd('\n', fd);
}
