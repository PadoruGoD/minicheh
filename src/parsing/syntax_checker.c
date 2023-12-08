/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:36 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:46:32 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax(t_data *shell)
{	
	if (unclosed_quote_error(shell))
		return (0);
	if (shell->lexer_size <= 0)
		return (0);
	if (pipe_syntax_error(shell))
		return (0);
	if (pipe_syntax_error_2(shell))
		return (0);
	if (wrong_cmd_error(shell))
		return (0);
	return (1);
}

int	unclosed_quote_error(t_data *shell)
{
	if (shell->dquote_count % 2 == 1 && shell->dquote_count != 0)
	{
		printf("Unclosed double quote detected\n");
		return (1);
	}
	if (shell->quote_count % 2 == 1 && shell->quote_count != 0)
	{
		printf("Unclosed quote detected\n");
		return (1);
	}
	return (0);
}

static int	check_cmd_error(t_list *list, t_data *shell)
{
	while (list)
	{
		if (list->id == CMD_OK)
		{
			if (list->value[0] == '/' || (list->value[0] == '.'
					&& (list->value[1] == '/' || (list->value[1] == '.'
							&& list->value[2] == '/'))))
			{
				if (access(list->value, F_OK | X_OK) != 0)
					return (1);
			}
			else if (ft_check_cmd(list->value, shell))
			{
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	wrong_cmd_error(t_data *shell)
{
	t_list	*list;

	list = shell->first;
	shell->lastret = 127;
	if (check_cmd_error(list, shell))
	{
		printf("Unrecognized command : %s\n", list->value);
		return (1);
	}
	return (0);
}
