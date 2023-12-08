/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:24:48 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 18:02:09 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_listo *lst, void (*f)(void *))
{
	t_listo	*elem;

	if (lst && f)
	{
		elem = lst;
		while (elem)
		{
			f(elem->content);
			elem = elem->next;
		}
	}
}
