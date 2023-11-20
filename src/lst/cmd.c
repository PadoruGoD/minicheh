/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:07:11 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/20 18:05:12 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_cmdnew(char *newline, t_cmd *sup_cmd, t_redirect redirect)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_error(2);
	cmd->line = newline;
	cmd->redirect = redirect;
	cmd->sup_cmd = sup_cmd;
	cmd->sub_cmd = 0;
	cmd->back = 0;
	cmd->and = 0;
	cmd->or = 0;
	return (cmd);
}

t_cmd	*ft_cmdfist(t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return (cmd);
	tmp = cmd;
	while (tmp->back)
		tmp = tmp->back;
	return (tmp);
}

void	ft_cmdadd_and(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last_elem;

	last_elem = NULL;
	if (cmd && new)
	{
		if (!*cmd)
			*cmd = new;
		else
			last_elem->and = new;
	}
}

void	ft_cmdadd_or(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last_elem;

	last_elem = NULL;
	if (cmd && new)
	{
		if (!*cmd)
			*cmd = new;
		else
			last_elem->or = new;
	}
}
