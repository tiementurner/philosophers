/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:38:02 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:52 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*p;
	unsigned char		*q;

	p = (unsigned char *)src;
	q = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		q[i] = p[i];
		if (q[i] == (unsigned char)c)
			return ((void *)(q + 1 + i));
		i++;
	}
	return (NULL);
}
