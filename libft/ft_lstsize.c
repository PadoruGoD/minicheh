/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:25:15 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 18:01:06 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_listo *lst)
{
	int		i;
	t_listo	*current;

	if (!lst)
		return (0);
	i = 1;
	current = lst;
	while (current->next != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
