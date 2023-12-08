/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:24:54 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:10:15 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listo	*ft_lstlast(t_listo *lst)
{
	t_listo	*last_elem;

	if (!lst)
		return (0);
	last_elem = lst;
	while (last_elem->next != NULL)
		last_elem = last_elem->next;
	return (last_elem);
}
