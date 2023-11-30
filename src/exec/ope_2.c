/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:40 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:04:41 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_3(int *is_and, t_token *tmp)
{
	t_data	**envglo;

	*is_and = 0;
	if (envglo->is_pipe == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
		redirect_exec(tmp, 1);
	else
		redirect_exec(tmp, 0);
}

void	execute_4(int *is_or, t_token *tmp)
{
	t_data	**envglo;

	*is_or = 0;
	if (envglo->is_pipe == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
		redirect_exec(tmp, 1);
	else
		redirect_exec(tmp, 0);
}

void	execute_5(int *is_and, int *is_or, int start, t_token *tmp)
{
	if (start == 0 && what_im(tmp->cmd) == 1)
		*is_and = 1;
	else if (start == 0 && what_im(tmp->cmd) == 2)
		*is_or = 1;
}

void	execute_2(int *is_or, int *is_and, t_token *tmp, int start)
{
	t_data	**envglo;

	if (*is_and == 1 && envglo->lastret == 0)
		execute_3(is_and, tmp);
	else if (*is_or == 1 && envglo->lastret != 0)
		execute_4(is_or, tmp);
	else if (start == 1 && envglo->is_pipe == 0 && tmp->next
		&& what_im(tmp->next->cmd) == 3 && tmp->redirect.outfd == 1)
		redirect_exec(tmp, 1);
	else if (start == 1)
		redirect_exec(tmp, 0);
}

void	execute(t_token *token)
{
	int		start;
	t_token	*tmp;
	int		is_and;
	int		is_or;
	int		is_ope;
	t_data	**envglo;

	tmp = token;
	init(&start, &is_and, &is_or, &is_ope);
	while (tmp && envglo->hd_stop == 0)
	{
		init_2(tmp);
		if (ft_strlen(tmp->cmd) == 0)
			return ;
		if (what_im(tmp->cmd) == 0)
			execute_2(&is_or, &is_and, tmp, start);
		else
			execute_5(&is_and, &is_or, start, tmp);
		ft_clean_hd(tmp->redirect.open);
		ft_clean_hd(tmp->redirect.open2);
		tmp = tmp->next;
		start = 0;
	}
}
