/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 15:08:07 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_pipe_error(void)
{
	printf("No command before pipe\n");
}

static int	check_before_pipe(t_list *list)
{
	while (list)
	{
		if (list->id != CMD_OK && list->id != BUILTIN_OK
			&& list->id != HEREDOC_TOKEN)
		{
			if (list->next && list->next->id == PIPE_OK)
			{
				print_pipe_error();
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	pipe_syntax_error(t_data *shell)
{
	t_list	*list;

	list = shell->first;
	if (list->id == PIPE_OK)
	{
		print_pipe_error();
		return (1);
	}
	return (check_before_pipe(list));
}

static int	check_after_pipe(t_list *list)
{
	while (list)
	{
		if (list->id == PIPE_OK && list->next)
		{
			list = list->next;
			if (list->id != CMD_OK && list->id != BUILTIN_OK
				&& list->id != PIPE_ERROR && list->id != HEREDOC_TOKEN)
			{
				printf("No command after pipe\n");
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	pipe_syntax_error_2(t_data *shell)
{
	t_list	*list;

	list = shell->first;
	if (check_after_pipe(list))
		return (1);
	while (list->next)
		list = list->next;
	if (list->id == PIPE_OK)
	{
		printf("No command after pipe\n");
		return (1);
	}
	return (0);
}
