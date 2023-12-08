/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:47:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 16:47:50 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_lexer_malloc(t_data *shell)
{
	shell->lexer = malloc(sizeof(char *) * (shell->lexer_size + 1));
	if (!shell->lexer)
		clean_exit("Malloc error", shell);
	shell->is_quote = malloc(sizeof(int) * (shell->lexer_size));
	if (shell->lexer_size == 0)
		shell->is_quote = malloc(sizeof(int) * (1));
	if (!shell->is_quote)
		clean_exit("Malloc error", shell);
}

void	free_lexer(t_data *shell)
{
	int	i;

	i = -1;
	while (shell->lexer[++i])
		free (shell->lexer[i]);
	free (shell->lexer);
}

void	clean_exit(char *msg, t_data *shell)
{
	perror(msg);
	destroy_token(shell);
	ft_free_tab(shell);
	exit (1);
}

void	ft_free_tab(t_data *shell)
{
	int	i;

	i = -1;
	if (shell->env)
	{
		while (shell->env[++i])
		{
			free (shell->env[i]);
		}
		free (shell->env);
	}
}

void	init_struct(t_data *shell, char **env)
{
	shell->lexer = 0;
	shell->lexer_size = 0;
	shell->lexer_current = 0;
	shell->dquote_count = 0;
	shell->quote_count = 0;
	shell->path = ft_parsing_execve(env, shell);
	shell->input = 0;
	shell->heredoc = 0;
	shell->exit_heredoc = 0;
}
