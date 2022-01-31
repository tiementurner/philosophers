/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 10:15:29 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:14:56 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_checklongs(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

static	int		ft_skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int				ft_atoi(const char *str)
{
	long	result;
	int		i;
	long	sign;
	long	temp;

	sign = 1;
	if (!*str || ft_strlen(str) == 0)
		return (0);
	result = 0;
	i = ft_skip_spaces(str);
	if (str[i] == '+' || str[i] == '-')
	{
		sign = 1 - 2 * (str[i] == '-');
		i++;
	}
	temp = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = result;
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (temp > result)
		return (ft_checklongs(sign));
	return (result * sign);
}
