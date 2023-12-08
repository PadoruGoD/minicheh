/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:47:26 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 14:52:46 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*prompt_data(t_data *shell)
{
	int		i;
	char	*pwd;

	i = -1;
	pwd = NULL;
	while (shell->env[++i])
	{
		if (!ft_strncmp("PWD", shell->env[i], 3)
			&& shell->env[i][3] == '=')
		{
			pwd = ft_substr(shell->env[i],
					ft_strlen("pwd") + 1, ft_strlen(shell->env[i]));
			if (!pwd)
				clean_exit("Malloc error", shell);
			break ;
		}
	}
	if (pwd == NULL)
		return ("minishell> ");
	return (pwd);
}
