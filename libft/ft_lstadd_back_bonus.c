/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 12:15:23 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:15 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *temp;

	if (!(new) || !(lst))
		return ;
	temp = *lst;
	if (temp)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		ft_lstadd_front(lst, new);
}
