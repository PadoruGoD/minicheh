/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:55 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 19:26:13 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env(t_data *shell, int id)
{
	char	**new_env;
	int		size;
	int		i;
	int		j;

	size = 0;
	while (shell->env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * size);
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (i != id)
		{
			new_env[j] = shell->env[i];
			j++;
		}
		else
		{
			free(shell->env[i]);
		}
	}
	new_env[j] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	unset_cmd(t_data*shell, char *arg)
{
	int		id;

	id = find_token(shell, arg);
	if (id >= 0)
	{
		remove_env(shell, id);
	}
}

void	hd_unset(t_data *shell, char **args)
{
	int		i;

	i = 0;
	if (!args[0])
	{
		shell->lastret = 0;
		return ;
	}
	while (args[i])
	{
		unset_cmd(shell, args[i]);
		i++;
	}
	shell->lastret = 0;
}

void	ft_unset(t_list *list)
{
	if (!list->arg[0])
	{
		ft_putstr_fd("unset: not enought arguments\n", 2);
		return ;
	}
}
