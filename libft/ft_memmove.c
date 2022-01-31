/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:59:17 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:04 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*q;

	if (!dst && !src)
		return (dst);
	p = (unsigned char *)src;
	q = (unsigned char *)dst;
	i = 0;
	if (dst < src)
		while (i < len)
		{
			q[i] = p[i];
			i++;
		}
	else
	{
		while (len)
		{
			q[len - 1] = p[len - 1];
			len--;
		}
	}
	return (dst);
}
