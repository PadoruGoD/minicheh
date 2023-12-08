/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:48:36 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 16:48:38 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_tmp_file(char *tmp_file_name)
{
	int	tmp_fd;

	tmp_fd = open(tmp_file_name, O_RDWR | O_CREAT, 0600);
	if (tmp_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return (tmp_fd);
}

static int	process_line(int tmp_fd, char **line, t_list *list)
{
	if (!(*line) && g_data_heredoc == 1)
		return (0);
	if ((*line)[0] == '\0')
	{
		free(*line);
		return (0);
	}
	if (*line && ft_strncmp(*line, list->value, ft_strlen(*line)) == 0)
	{
		free(*line);
		return (1);
	}
	if (g_data_heredoc == 0)
	{
		free(*line);
		return (1);
	}
	ft_write(tmp_fd, *line, ft_strlen(*line));
	ft_write(tmp_fd, "\n", 1);
	free(*line);
	return (0);
}

static void	write_heredoc(int tmp_fd, t_list *list, char *prompt, t_data *shell)
{
	char	*line;

	signal(SIGINT, sigint_hd);
	signal(SIGQUIT, SIG_IGN);
	g_data_heredoc = 1;
	while (g_data_heredoc == 1)
	{
		line = readline(prompt);
		if (process_line(tmp_fd, &line, list))
			break ;
	}
	if (g_data_heredoc == 0)
	{
		shell->exit_heredoc = 1;
		shell->lastret = 130;
	}
	g_data_heredoc = 0;
}

void	set_heredoc_fd(t_list *list, int *current_fd_in, t_data *shell)
{
	int		tmp_fd;
	char	*tmp_file_name;

	if (list->id != HEREDOC_TOKEN || !list->value)
		return ;
	tmp_file_name = "./heredoc";
	tmp_fd = create_tmp_file(tmp_file_name);
	write_heredoc(tmp_fd, list, "heredoc> ", shell);
	ft_close(tmp_fd);
	tmp_fd = open(tmp_file_name, O_RDONLY);
	if (tmp_fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	*current_fd_in = tmp_fd;
	if (list->next)
		list->next->fd_in = tmp_fd;
	ft_unlink(tmp_file_name);
	shell->heredoc = 1;
}

int	heredoc_fd_2(t_list *list, t_data *shell)
{
	int		tmp_fd;
	char	*tmp_file_name;

	tmp_file_name = "./heredoc";
	tmp_fd = create_tmp_file(tmp_file_name);
	write_heredoc(tmp_fd, list, "pipe heredoc> ", shell);
	close(tmp_fd);
	shell->heredoc = 1;
	shell->tmp_filename = tmp_file_name;
	return (open(tmp_file_name, O_RDONLY, 0600));
}
