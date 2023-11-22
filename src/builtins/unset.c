/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:55 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/21 19:23:40 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkvalid_unset(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[0] == '-')
			return (2);
		if ((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\''
				&& cmd[i] != '"' && cmd[i] != '_' && cmd)
			|| ft_isdigit(cmd[0]) == 1)
		{
			puterror(cmd, "not a valid identifier");
			return (1);
		}
		i++;
		if (cmd[i] == '=')
			break ;
	}
	return (0);
}

int	del_element(char *name)
{
	char	**p_env;
	int		i;

	p_env = g_data->env;
	i = -1;
	while (p_env[++i])
	{
		if (ft_strncmp(p_env[i], name, ft_strlen(name) - 1) == 0)
		{
			free(p_env[i]);
			break ;
		}
	}
	while (p_env[++i])
		p_env[i - 1] = p_env[i];
	p_env[i - 1] = NULL;
	free(name);
	return (0);
}

int	unset(char **cmd)
{
	int		i;
	int		err;
	char	*tmp;

	i = 1;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		err = checkvalid_unset(cmd[i]);
		if (err != 0)
			return (err);
		tmp = ft_ecrase_q(cmd[i]);
		del_element(tmp);
		i++;
	}
	return (0);
}
