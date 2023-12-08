/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:48:51 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:46:47 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	hd_heredoc_token(t_list *list, t_data *shell, int temp_fd)
{
	ssize_t	byte_read;
	char	buffer[1024];
	char	*line;

	if (list->fd_in > 2)
	{
		byte_read = read(list->fd_in, buffer, sizeof(buffer));
		while (byte_read > 0)
		{
			write(temp_fd, buffer, byte_read);
			byte_read = read(list->fd_in, buffer, sizeof(buffer));
		}
	}
	line = copy_fd_to_str(shell->tmp_fd);
	ft_close(shell->tmp_fd);
	ft_unlink(shell->tmp_filename);
	ft_putstr_fd(line, temp_fd);
	ft_close(temp_fd);
	temp_fd = open("tempfile", O_RDWR | O_CREAT, 0666);
	ft_dup2(temp_fd, STDIN_FILENO);
	ft_close(list->fd_in);
	list->fd_in = temp_fd;
}

static void	redirect_fd(t_list *list)
{
	if (list->fd_in != -1 && list->fd_in != STDIN_FILENO)
		ft_dup2(list->fd_in, STDIN_FILENO);
	if (list->fd_out != STDOUT_FILENO && list->fd_out > 1)
		ft_dup2(list->fd_out, STDOUT_FILENO);
}

void	pipe_and_exec(t_list *list, t_data *shell, char *cmd, char **args)
{
	int		temp_fd;

	if (list->next && list->next->id == HEREDOC_TOKEN)
	{
		temp_fd = open("tempfile", O_RDWR | O_CREAT, 0666);
		hd_heredoc_token(list, shell, temp_fd);
	}
	redirect_fd(list);
	close_all_fd(shell);
	if (list->next && list->next->id == HEREDOC_TOKEN)
		unlink("tempfile");
	if (list->id == CMD_OK)
	{
		execve(cmd, args, shell->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		exec_builtins(list, shell);
	}
}

void	child_process(t_list *list, t_data *shell, char *cmd, char **args)
{
	g_data_heredoc = 2;
	signal(SIGINT, child_sigint_hd);
	signal(SIGQUIT, SIG_DFL);
	setup_signal();
	pipe_and_exec(list, shell, cmd, args);
	g_data_heredoc = 0;
}
