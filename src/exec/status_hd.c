/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:48:57 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 14:52:34 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hd_child_error(int pid)
{
	if (pid < 0)
		perror("fork");
}

void	close_fd(t_list *list)
{
	if (list->fd_in > 2)
		ft_close(list->fd_in);
	if (list->fd_out > 2)
		ft_close(list->fd_out);
}

void	reset_fd(void)
{
	ft_dup2(STDIN_FILENO, 0);
	ft_dup2(STDOUT_FILENO, 1);
	ft_dup2(STDERR_FILENO, 2);
}

void	hd_status(t_list *list, t_data *shell, int pid)
{
	int	status;

	(void) list;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		shell->lastret = 128 + shell->lastret;
		kill(pid, SIGKILL);
	}
	else if (WIFEXITED(status))
		shell->lastret = WEXITSTATUS(status);
}
