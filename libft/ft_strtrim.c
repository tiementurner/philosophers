/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 14:51:43 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:18:00 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_check_char(char c, const char *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	char	*begin_pos;
	char	*end_pos;

	if (s1 == 0)
		return (NULL);
	begin_pos = (char*)s1;
	end_pos = (char*)s1 + ft_strlen(s1) - 1;
	while (ft_check_char(*begin_pos, set))
		begin_pos++;
	if (begin_pos > end_pos)
		return (ft_strdup(""));
	while (ft_check_char(*end_pos, set))
		end_pos--;
	end_pos++;
	p = (char*)malloc(end_pos - begin_pos + 1);
	if (!p)
		return (NULL);
	else
		ft_strlcpy(p, begin_pos, end_pos - begin_pos + 1);
	return (p);
}
