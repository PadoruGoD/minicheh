/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:54 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:04:55 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ecraseq_tab(char *cmd)
{
	int		i;
	char	**tab;
	char	*tmp;

	tab = ft_split2(cmd, " ");
	i = -1;
	while (tab[++i])
	{
		tmp = tab[i];
		tab[i] = ft_ecrase_q(tab[i]);
		free(tmp);
	}
	return (tab);
}
