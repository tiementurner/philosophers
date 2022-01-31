/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tblanker <tblanker@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:52:57 by tblanker      #+#    #+#                 */
/*   Updated: 2020/10/11 16:16:21 by tblanker      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!(lst) || (!(new)))
		return ;
	new->next = *lst;
	*lst = new;
}
