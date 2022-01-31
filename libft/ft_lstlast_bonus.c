/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 12:13:09 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:39 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *res;

	if (!(lst))
		return (0);
	res = lst;
	while (res->next)
	{
		res = res->next;
	}
	return (res);
}
