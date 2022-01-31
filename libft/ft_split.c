/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 16:15:16 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:17:27 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_strings(char **str, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int	skip_splitchars(char const *s, char c, int i)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

static char	**malloc_substrings(char const *s, char c, char **str)
{
	int		i;
	int		j;
	int		letter_count;

	i = 0;
	j = 0;
	i = skip_splitchars(s, c, i);
	while (s[i])
	{
		letter_count = 0;
		i = skip_splitchars(s, c, i);
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			letter_count++;
			i++;
		}
		str[j] = (char *)malloc(sizeof(char) * letter_count + 1);
		if (!(str[j]))
			return (free_strings(str, j));
		j++;
	}
	return (str);
}

static char	**fill_string(char const *s, char c, char **str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	i = skip_splitchars(s, c, i);
	while (s[i])
	{
		k = 0;
		i = skip_splitchars(s, c, i);
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			str[j][k] = s[i];
			k++;
			i++;
		}
		str[j][k] = '\0';
		j++;
	}
	return (str);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		word_count;
	char	**str;

	if (!s)
		return (NULL);
	word_count = 0;
	i = 0;
	i = skip_splitchars(s, c, i);
	while (s[i])
	{
		if (s[i] != c)
			word_count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	str = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!str)
		return (NULL);
	str[word_count] = NULL;
	str = malloc_substrings(s, c, str);
	str = fill_string(s, c, str);
	return (str);
}
