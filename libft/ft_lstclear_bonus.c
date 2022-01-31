/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 16:32:19 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:25 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *elem;
	t_list *next_elem;

	if (!(lst))
		return ;
	elem = *lst;
	while (elem)
	{
		next_elem = elem->next;
		del(elem->content);
		free(elem);
		elem = next_elem;
	}
	*lst = NULL;
}
