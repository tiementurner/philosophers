/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 20:34:20 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:21 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	result;

	result = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		result = (unsigned int)(n * -1);
	}
	else
		result = (unsigned int)n;
	if (result >= 10)
		ft_putnbr_fd(result / 10, fd);
	ft_putchar_fd((char)(result % 10 + '0'), fd);
}
