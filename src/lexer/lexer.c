/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:47:55 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:49:34 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_size(char *input, t_data *shell)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			i = pipe_to_char(input, i, shell, 1);
		else if (ft_is_quote(input[i]))
			i = quote_to_char(input, i, shell, 1);
		else if ((input[i] == '<' || input[i] == '>'))
			i = redir_to_char(input, i, shell, 1);
		else if (ft_is_blank(input[i]))
			i = ft_skip_blank(input, i);
		else
			i = word_to_char(input, i, shell, 1);
	}
	init_lexer_malloc(shell);
}

char	**lexer(char *input, t_data *shell)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			i = pipe_to_char(input, i, shell, 0);
		else if (ft_is_quote(input[i]))
			i = quote_to_char(input, i, shell, 0);
		else if ((input[i] == '<' || input[i] == '>'))
			i = redir_to_char(input, i, shell, 0);
		else if (ft_is_blank(input[i]))
			i = ft_skip_blank(input, i);
		else
			i = word_to_char(input, i, shell, 0);
	}
	return (0);
}

int	calculate_redir_to_char(char *input, int i, t_data *shell)
{
	int	j;

	j = 0;
	(void) shell;
	while ((input[i] == '<' || input[i] == '>') && input[i])
	{
		i++;
		j++;
	}
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i])
	{
		j++;
		i++;
	}
	return (j);
}

void	stock_in_struct(t_data *shell, char *word, int j, int only_count)
{
	if (only_count == 1)
	{
		free (word);
		shell->lexer_size++;
	}
	else
	{
		shell->lexer[shell->lexer_current] = ft_strdup(word);
		if (!shell->lexer[shell->lexer_current])
			clean_exit("Malloc error", shell);
		free (word);
		shell->lexer[shell->lexer_current][j] = '\0';
		shell->lexer_current++;
	}
}

int	get_substr_real_length(char *str, int start_idx)
{
	int	len;

	len = 0;
	while (str[start_idx + len] && str[start_idx + len] != '\'')
		len++;
	return (len);
}
