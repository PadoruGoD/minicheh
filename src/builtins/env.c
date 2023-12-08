/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:25 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 14:49:20 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *shell, t_list *list)
{
	int	i;

	if (list->arg[0])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return ;
	}
	i = -1;
	while (shell->env[++i])
		printf("%s\n", shell->env[i]);
}
