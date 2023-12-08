/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:48:27 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:43:11 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_fd(t_data *shell)
{
	t_list	*list;

	list = shell->first;
	while (list)
	{
		if (list->id == CMD_OK || list->id == BUILTIN_OK)
			close_fd(list);
		list = list->next;
	}
}

char	*add_path(t_data *shell, t_list *list)
{
	char	*cmd;
	int		i;

	if (list->value[0] == '/' || (list->value[0] == '.'
			&& (list->value[1] == '/' || (list->value[1] == '.'
					&& list->value[2] == '/'))))
	{
		if (access(list->value, F_OK) == 0)
			return (ft_strdup(list->value));
		else
			return (NULL);
	}
	i = -1;
	if (!shell->path)
		return (NULL);
	while (shell->path[++i])
	{
		cmd = ft_strjoin(shell->path[i], list->value);
		if (access(cmd, F_OK) == 0)
			break ;
		free(cmd);
		cmd = 0;
	}
	return (cmd);
}

void	prepare_cmd(t_data *shell, t_list *list, char **cmd, char ***args)
{
	int	i;

	*cmd = add_path(shell, list);
	i = 0;
	while (list->arg && list->arg[i])
		i++;
	*args = (char **)malloc((i + 2) * sizeof(char *));
	if (!*args)
		return ;
	(*args)[0] = list->value;
	i = -1;
	while (list->arg && list->arg[++i])
		(*args)[i + 1] = list->arg[i];
	(*args)[i + 1] = 0;
}

char	*append_buffer(char *result, char *buffer, size_t byte_read,
		size_t *total_byte)
{
	char	*new_result;

	new_result = (char *)malloc(*total_byte + byte_read + 1);
	if (!new_result)
		return (NULL);
	if (result)
	{
		ft_memcpy(new_result, result, *total_byte);
		free(result);
	}
	ft_memcpy(new_result + *total_byte, buffer, byte_read);
	*total_byte += byte_read;
	return (new_result);
}

char	*copy_fd_to_str(int fd)
{
	char	buffer[4096];
	char	*result;
	ssize_t	byte_read;
	size_t	total_byte;

	total_byte = 0;
	result = NULL;
	byte_read = read(fd, buffer, sizeof(buffer));
	while (byte_read > 0)
	{
		result = append_buffer(result, buffer, byte_read, &total_byte);
		if (!result)
			return (NULL);
		byte_read = read(fd, buffer, sizeof(buffer));
	}
	if (byte_read == -1 || !result)
	{
		free(result);
		return (NULL);
	}
	result[total_byte] = '\0';
	return (result);
}
