/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:26:00 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:08:46 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listo	*ft_next(t_listo *lst)
{
	t_listo	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	lst = lst->next;
	free(tmp->content);
	free(tmp);
	return (lst);
}
