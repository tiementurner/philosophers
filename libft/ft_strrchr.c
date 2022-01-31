/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 08:50:53 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:56 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *p;

	p = NULL;
	while (*s)
	{
		if ((char)s[0] == (char)c)
		{
			p = (char *)s;
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (p);
}
