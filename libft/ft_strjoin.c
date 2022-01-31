/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:42:48 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:36 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_merge(char *p, char const *s1, char const *s2)
{
	int i;
	int j;

	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		p[j] = s2[i];
		i++;
		j++;
	}
	p[j] = '\0';
	return (p);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p)
		p = ft_merge(p, s1, s2);
	return (p);
}
