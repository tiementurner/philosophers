/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 11:44:16 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:38 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t dst)
{
	int	i;

	i = 0;
	while (i < (int)dst && *s)
	{
		i++;
		s++;
	}
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t src_len;
	size_t j;

	i = ft_strnlen(dst, dstsize);
	j = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (dstsize > i)
	{
		while ((i + j) < (dstsize - 1) && src[j])
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	if (dstsize < i)
		return (src_len + dstsize);
	return (i + src_len);
}
