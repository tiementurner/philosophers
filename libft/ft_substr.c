/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:26:00 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:18:02 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*p;
	size_t		i;

	if (!(s))
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		p = (char *)malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		p = (char *)malloc(sizeof(char) * (len + 1));
	if (p)
	{
		while (i < len && s[start] != '\0')
		{
			p[i] = s[start];
			start++;
			i++;
		}
		p[i] = '\0';
		return (p);
	}
	else
		return (NULL);
}
