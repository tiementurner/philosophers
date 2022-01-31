/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 15:49:55 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:48 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		length;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	length = ft_strlen((char *)s);
	str = (char *)malloc(sizeof(char) * length + 1);
	if (!str)
		return (NULL);
	while (i < length)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[length] = '\0';
	return (str);
}
