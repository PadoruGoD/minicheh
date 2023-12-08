/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:48:44 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 16:48:46 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exit_fd(t_list *list, int *current_fd_out)
{
	if (list->id == EXIT_TOKEN && list->value)
	{
		*current_fd_out = open(list->value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (*current_fd_out == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		if (list->prev)
			list->prev->fd_out = *current_fd_out;
	}
}

void	set_append_fd(t_list *list, int *current_fd_out)
{
	if (list->id == APPEND_TOKEN && list->value)
	{
		*current_fd_out = open(list->value, O_WRONLY
				| O_CREAT | O_APPEND, 0666);
		if (*current_fd_out == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		if (list->prev)
			list->prev->fd_out = *current_fd_out;
	}
}

void	set_entry_fd(t_list *list, int *current_fd_in)
{
	if (list->id == ENTRY_TOKEN && list->value)
	{
		*current_fd_in = open(list->value, O_RDONLY);
		if (*current_fd_in == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
		if (list->next)
			list->next->fd_in = *current_fd_in;
	}
}

void	set_pipe_fd(t_list *list, int *current_fd_in, int *current_fd_out)
{
	int	pipe_fd[2];

	(void) current_fd_out;
	if (list->id == PIPE_OK && list->prev)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (list->prev->id == HEREDOC_TOKEN)
			list->prev->prev->fd_out = pipe_fd[1];
		else
			list->prev->fd_out = pipe_fd[1];
		if (list->next)
		{
			list->next->fd_in = pipe_fd[0];
			*current_fd_in = pipe_fd[0];
		}
	}
}

void	set_fd(t_data *shell)
{
	int		current_fd_in;
	int		current_fd_out;
	t_list	*list;

	list = shell->first;
	current_fd_in = 0;
	current_fd_out = 1;
	while (list)
	{
		if (list->id == CMD_OK || list->id == BUILTIN_OK)
		{
			list->fd_in = current_fd_in;
			list->fd_out = current_fd_out;
		}
		if (!list->prev || (list->prev->id != CMD_OK
				&& list->prev->id != BUILTIN_OK))
			set_heredoc_fd(list, &current_fd_in, shell);
		else if (list && list->id == HEREDOC_TOKEN)
			shell->tmp_fd = heredoc_fd_2(list, shell);
		set_exit_fd(list, &current_fd_out);
		set_append_fd(list, &current_fd_out);
		set_entry_fd(list, &current_fd_in);
		set_pipe_fd(list, &current_fd_in, &current_fd_out);
		list = list->next;
	}
}
