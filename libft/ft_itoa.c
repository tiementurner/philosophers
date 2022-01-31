/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 15:16:07 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:09 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_arraylength(int nbr)
{
	int arraylength;

	arraylength = 1;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		arraylength++;
	}
	while (nbr >= 10)
	{
		arraylength++;
		nbr = nbr / 10;
	}
	return (arraylength);
}

static char		*ft_makestring(int arraylength, int nbr, char *string)
{
	while (arraylength > -1)
	{
		string[arraylength] = nbr % 10 + '0';
		arraylength--;
		nbr = nbr / 10;
	}
	return (string);
}

char			*ft_itoa(int nbr)
{
	char	*string;
	int		negative;
	int		arraylength;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	arraylength = ft_arraylength(nbr);
	negative = 0;
	if (nbr < 0)
	{
		negative = 1;
		nbr = nbr * -1;
	}
	string = (char *)malloc(sizeof(char) * arraylength + 1);
	if (!string)
		return (NULL);
	string[arraylength] = '\0';
	arraylength--;
	string = ft_makestring(arraylength, nbr, string);
	if (negative == 1)
		string[0] = '-';
	return (string);
}
