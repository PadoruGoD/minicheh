/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:12 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:45:39 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_redirection_token(t_data *shell, t_list *to_add, int i)
{
	to_add = NULL;
	to_add = ft_init_token(shell);
	to_add->value = ft_strdup(shell->lexer[i]);
	if (!to_add->value)
		clean_exit("Malloc error", shell);
	to_add->fd_in = 0;
	to_add->fd_out = 0;
	to_add->arg = 0;
	if (shell->lexer[i][0] == '<')
	{
		if (shell->lexer[i][1] == '<')
			to_add->id = HEREDOC_TOKEN;
		else
			to_add->id = ENTRY_TOKEN;
	}
	else
	{
		if (shell->lexer[i][1] == '>')
			to_add->id = APPEND_TOKEN;
		else
			to_add->id = EXIT_TOKEN;
	}
	ft_add_token(shell, to_add);
	i++;
	return (i);
}

static int	create_pipe_token(t_data *shell, t_list *to_add, int i)
{
	to_add = ft_init_token(shell);
	to_add->value = ft_strdup(shell->lexer[i]);
	if (!to_add->value)
		clean_exit("Malloc error", shell);
	to_add->fd_in = 0;
	to_add->fd_out = 0;
	to_add->arg = 0;
	to_add->id = PIPE_OK;
	ft_add_token(shell, to_add);
	i++;
	return (i);
}

static int	create_cmd_token_2(t_data *shell, int i, t_list *to_add)
{
	int	j;

	j = 0;
	while (i < shell->lexer_size && shell->lexer[i][0] != '<'
		&& shell->lexer[i][0] != '>' && shell->lexer[i][0] != '|'
			&& shell->lexer[i] && ft_strncmp(shell->lexer[i], "$?", 2))
	{
		to_add->arg[j] = ft_strdup(shell->lexer[i]);
		if (!to_add->arg[j])
			clean_exit("Malloc error", shell);
		i++;
		j++;
	}
	to_add->arg[j] = 0;
	return (i);
}

static int	create_cmd_token(t_data *shell, t_list *to_add, int i)
{
	int	j;

	j = i + 1;
	to_add = ft_init_token(shell);
	to_add->value = ft_strdup(shell->lexer[i]);
	if (!to_add->value)
		clean_exit("Malloc error", shell);
	to_add->fd_in = 0;
	to_add->fd_out = 0;
	while (j < shell->lexer_size && shell->lexer[j][0] != '<'
		&& shell->lexer[j][0] != '>' && shell->lexer[j][0] != '|'
			&& ft_strncmp(shell->lexer[j], "$?", 2))
		j++;
	i++;
	to_add->arg = malloc (sizeof(char *) * (j + 1));
	if (!to_add->arg)
		clean_exit("Malloc error", shell);
	i = create_cmd_token_2(shell, i, to_add);
	to_add->id = CMD_OK;
	if (is_builtin(to_add->value))
		to_add->id = BUILTIN_OK;
	ft_add_token(shell, to_add);
	return (i);
}

void	parsing(t_data *shell)
{
	int		i;
	t_list	*to_add;

	i = 0;
	to_add = NULL;
	shell->first = 0;
	while (shell->lexer[i])
	{
		if (shell->lexer[i][0] == '<' || shell->lexer[i][0] == '>')
			i = create_redirection_token(shell, to_add, i);
		else if (shell->lexer[i][0] == '|')
			i = create_pipe_token(shell, to_add, i);
		else
			i = create_cmd_token(shell, to_add, i);
	}
	correct_redir(shell);
}
