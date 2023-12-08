/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:20 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:44:21 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hd_child_exec(t_list *list, t_data *shell, char *cmd, char **args)
{
	child_process(list, shell, cmd, args);
	exit(EXIT_SUCCESS);
}

void	hd_parent_exec(t_list *list, t_data *shell, pid_t pid)
{
	pid_t	*new_pid;

	new_pid = (pid_t *)malloc(sizeof(pid_t) * (shell->n_pid + 1));
	if (!new_pid)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (shell->pid)
	{
		ft_memcpy(new_pid, shell->pid, sizeof(pid_t) * shell->n_pid);
		free(shell->pid);
	}
	new_pid[shell->n_pid] = pid;
	shell->pid = new_pid;
	shell->n_pid++;
	g_data_heredoc = 2;
	hd_child_error(pid);
	(void) list;
	g_data_heredoc = 0;
}

void	exec_cmd(t_list *list, t_data *shell)
{
	char	**args;
	char	*cmd;
	pid_t	pid;

	prepare_cmd(shell, list, &cmd, &args);
	if (!ft_strncmp(list->value, "cd", 2))
		ft_cd(shell, list);
	else if (!ft_strncmp(list->value, "exit", 4))
		ft_exit(shell, list);
	else if (!ft_strncmp(list->value, "export", 6) && list->arg[0])
		hd_export(shell, list->arg);
	else if (!ft_strncmp(list->value, "unset", 5) && list->arg[0])
		hd_unset(shell, list->arg);
	else
	{
		pid = fork();
		if (pid == 0)
			hd_child_exec(list, shell, cmd, args);
		else
			hd_parent_exec(list, shell, pid);
	}
	free(args);
	free(cmd);
	reset_fd();
}

void	exec_builtins(t_list *list, t_data *shell)
{
	if (!ft_strncmp(list->value, "pwd", 3))
		ft_pwd();
	if (!ft_strncmp(list->value, "echo", 4))
		ft_echo(list);
	if (!ft_strncmp(list->value, "env", 3))
		ft_env(shell, list);
	if (!ft_strncmp(list->value, "export", 6))
		ft_export(shell, list);
	if (!ft_strncmp(list->value, "unset", 5))
		ft_unset(list);
}

void	exec(t_data *shell)
{
	t_list	*list;
	int		i;

	setup_signal();
	list = shell->first;
	shell->pid = NULL;
	shell->n_pid = 0;
	set_fd(shell);
	while (list)
	{
		if ((list->id == CMD_OK || list->id == BUILTIN_OK)
			&& shell->exit_heredoc == 0)
			exec_cmd(list, shell);
		list = list->next;
	}
	i = -1;
	close_all_fd(shell);
	while (++i < shell->n_pid)
		hd_status(NULL, shell, shell->pid[i]);
	free(shell->pid);
	shell->pid = NULL;
	shell->n_pid = 0;
}
