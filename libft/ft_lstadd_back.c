/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:24:19 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:12:02 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_listo **alst, t_listo *new)
{
	t_listo	*last_elem;

	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			last_elem = ft_lstlast(*alst);
			last_elem->next = new;
		}
	}
}
