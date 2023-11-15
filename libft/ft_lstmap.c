/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:25:02 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:25:03 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmps;

	if (!lst || !f)
		return (0);
	tmp = ft_lstnew(f(lst->content));
	if (!tmp)
		return (0);
	tmps = tmp;
	while (lst->next)
	{
		tmps->next = ft_lstnew(f(lst->next->content));
		if (!tmps)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		tmps = tmps->next;
		lst = lst->next;
	}
	tmps->next = NULL;
	return (tmp);
}
