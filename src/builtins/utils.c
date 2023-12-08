/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:06 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 19:39:46 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_token(t_data *shell, char *token)
{
	int		index;
	int		token_len;

	index = 0;
	token_len = ft_strlen(token);
	while (shell->env[index])
	{
		if (ft_strncmp(shell->env[index], token, token_len)
			&& (shell->env[index][token_len] == '='))
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

char	*get_token(char *arg)
{
	int		i;
	char	*token;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	token = (char *)malloc(i + 2);
	ft_strlcpy(token, arg, i + 1);
	token[i + 1] = '\0';
	return (token);
}

void	add_env(t_data *shell, char *arg)
{
	int		size;
	char	**new_env;
	int		i;

	size = 0;
	i = -1;
	while (shell->env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	while (++i < size)
		new_env[i] = shell->env[i];
	new_env[size] = ft_strdup(arg);
	new_env[size + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}

void	export_cmd(t_data *shell, char *arg)
{
	char	*token;
	int		id;

	token = get_token(arg);
	if (!token)
		return ;
	id = find_token(shell, token);
	if (id >= 0)
		unset_cmd(shell, token);
	if (arg)
		add_env(shell, arg);
	free(token);
}

void	hd_export(t_data *shell, char **args)
{
	int		i;

	i = 0;
	if (!args[0])
	{
		shell->lastret = 127;
		return ;
	}
	while (args[i])
	{
		export_cmd(shell, args[i]);
		i++;
	}
	shell->lastret = 127;
}
