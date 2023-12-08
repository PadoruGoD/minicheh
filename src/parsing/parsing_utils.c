/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:22 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:45:57 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**process_path(char **path, t_data *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			clean_exit("Malloc error", shell);
		free(path[i]);
		path[i] = tmp;
		i++;
	}
	return (path);
}

char	**ft_parsing_execve(char **env, t_data *shell)
{
	int		i;
	char	*full_path;
	char	**path;

	i = 0;
	full_path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5))
		{
			full_path = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!full_path)
	{
		return (NULL);
	}
	path = ft_split(full_path, ':');
	if (!path)
	{
		clean_exit("Malloc error", shell);
	}
	return (process_path(path, shell));
}

int	is_builtin(char *tmp)
{
	if (!ft_strncmp(tmp, "echo", 4))
		return (1);
	if (!ft_strncmp(tmp, "cd", 2))
		return (1);
	if (!ft_strncmp(tmp, "pwd", 3))
		return (1);
	if (!ft_strncmp(tmp, "export", 6))
		return (1);
	if (!ft_strncmp(tmp, "unset", 5))
		return (1);
	if (!ft_strncmp(tmp, "env", 3))
		return (1);
	if (!ft_strncmp(tmp, "exit", 4))
		return (1);
	return (0);
}

int	ft_check_cmd(char *ok, t_data *shell)
{
	int		i;
	char	*cmd;

	i = -1;
	if (!shell->path)
	{
		return (1);
	}
	while (shell->path[++i])
	{
		cmd = ft_strjoin(shell->path[i], ok);
		if (access(cmd, F_OK) == 0)
		{
			free(cmd);
			return (0);
		}
		free(cmd);
	}
	return (1);
}
