/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 11:07:57 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:59 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*q;

	p = (unsigned char *)s1;
	q = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] < q[i])
			return ((unsigned char)p[i] - (unsigned char)q[i]);
		if (p[i] > q[i])
			return ((unsigned char)p[i] - (unsigned char)q[i]);
		i++;
	}
	return (0);
}
