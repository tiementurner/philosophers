/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 10:38:27 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:01 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*p;
	unsigned char		*q;

	if (!dst && !src)
		return (dst);
	p = src;
	q = dst;
	i = 0;
	while (i < n)
	{
		q[i] = p[i];
		i++;
	}
	return (dst);
}
