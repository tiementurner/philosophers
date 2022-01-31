/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 11:53:15 by tblanker      #+#    #+#                 */
/*   Updated: 2021/12/16 20:47:24 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;

	i = 0;
	if (NULL == s1)
		return (NULL);
	p = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (p)
	{
		while (i < ft_strlen(s1))
		{
			p[i] = s1[i];
			i++;
		}
		p[ft_strlen(s1)] = '\0';
	}
	return (p);
}
