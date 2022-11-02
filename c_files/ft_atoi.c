/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 10:15:29 by tblanker      #+#    #+#                 */
/*   Updated: 2022/03/09 15:00:14 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

static int	ft_skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		result;
	int		i;
	long	sign;

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
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((i == 9 && str[i] > '7' ) || i > 9)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
