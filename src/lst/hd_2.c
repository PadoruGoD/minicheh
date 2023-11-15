/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:07:27 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:07:28 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*ft_hd_to_tab(t_hd *hd)
{
	size_t	i;
	size_t	size;
	int		*tab;
	t_hd	*tmp;

	i = 0;
	size = ft_hdsize(hd);
	tab = malloc(sizeof(tab) * size);
	if (!tab)
		ft_error(2);
	while (i < size)
	{
		tab[i++] = hd->fd;
		tmp = hd;
		hd = hd->next;
		free(tmp);
	}
	return (tab);
}
