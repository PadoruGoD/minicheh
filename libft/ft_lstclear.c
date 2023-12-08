/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:24:35 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 18:01:52 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_listo **lst, void (*del)(void *))
{
	t_listo	*elem_to_del;
	t_listo	*tmp;

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
