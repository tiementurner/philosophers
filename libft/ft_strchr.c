/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 11:54:04 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:30 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *p;

	while (*s)
	{
		if (s[0] == (char)c)
		{
			p = (char*)s;
			return (p);
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char*)s);
	return (NULL);
}
