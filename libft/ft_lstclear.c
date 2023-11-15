/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:24:35 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:24:35 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem_to_del;
	t_list	*tmp;

	if (lst && del)
	{
		elem_to_del = *lst;
		while (elem_to_del)
		{
			tmp = elem_to_del->next;
			del(elem_to_del->content);
			free(elem_to_del);
			elem_to_del = tmp;
		}
		*lst = NULL;
	}
}
