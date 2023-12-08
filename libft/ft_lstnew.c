/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:25:08 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:58:59 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listo	*ft_lstnew(void *content)
{
	t_listo	*list;

	list = malloc(sizeof(t_listo));
	if (!list)
		return (0);
	list->content = content;
	list->next = NULL;
	return (list);
}
