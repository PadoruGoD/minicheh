/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:02:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 15:50:37 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	path_in_env(t_data *shell, char *new_pwd)
{
	int		i;
	char	*path;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			path = ft_strjoin("PWD=", new_pwd);
			if (!path)
				return ;
			shell->env[i] = ft_strdup(path);
			free (path);
			break ;
		}
		i++;
	}
	shell->lastret = 0;
}

int	ft_cd(t_data *shell, t_list *cmd)
{
	char	old_pwd[4096];
	char	new_pwd[4096];

	if (!cmd->arg || !cmd->arg[0])
	{
		ft_putstr_fd("cd: No path provided.\n", 2);
		return (-1);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		perror("getcwd error");
		return (-1);
	}
	if (chdir(cmd->arg[0]) == -1)
	{
		perror("chdir error");
		return (-1);
	}
	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		perror("getcwd error");
		return (-1);
	}
	path_in_env(shell, new_pwd);
	return (0);
}
