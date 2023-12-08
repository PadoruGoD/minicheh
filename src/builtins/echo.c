/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:05 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 16:49:23 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_list *list)
{
	int	i;

	i = -1;
	if (!list->arg[0])
	{
		printf("\n");
		return ;
	}
	while (list->arg[++i])
	{
		if (i > 1)
			printf(" ");
		if (ft_strncmp(list->arg[0], "-n", 2) && i == 1)
			printf(" ");
		if (ft_strncmp(list->arg[i], "-n", 2) || i != 0)
			printf("%s", list->arg[i]);
	}
	if (list->arg)
		if (ft_strncmp(list->arg[0], "-n", 2))
			printf("\n");
}
