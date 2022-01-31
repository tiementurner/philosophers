/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 15:12:05 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:42 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	void	*content;
	t_list	*newlist;

	if (!(lst))
		return (NULL);
	newlist = 0;
	while (lst)
	{
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (!(temp))
			ft_lstclear(&lst, del);
		ft_lstadd_back(&newlist, temp);
		lst = lst->next;
	}
	return (newlist);
}
