/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:46 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:04:48 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_ope(t_token *tmp)
{
	int	ret;
	t_data	*envglo;

	ret = 1;
	while (envglo->is_pipe && tmp->cmd)
	{
		init_2(tmp);
		if (envglo->is_pipe && tmp->next && what_im(tmp->next->cmd) == 3)
			ret = pipex(tmp->cmd);
		else if (envglo->is_pipe == 1 && what_im(tmp->cmd) == 0)
		{
			envglo->is_pipe = 0;
			if (tmp->redirect.outfd == -1 || tmp->redirect.infd == -1)
				return (1);
			dup2(tmp->redirect.infd, 0);
			dup2(tmp->redirect.outfd, 1);
			ret = exec(tmp->cmd);
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	exec_pipe(t_token *tmp)
{
	int	ret;

	ret = 0;
	if (tmp && what_im(tmp->cmd) == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && !tmp->next->next)
		printf("prohibited character or input not close\n");
	else
		ret = pipe_ope(tmp);
	return (ret);
}
