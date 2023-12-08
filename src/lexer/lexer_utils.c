/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:48:02 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:49:54 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_to_char(char *input, int i, t_data *shell, int only_count)
{
	int		j;
	char	*word;

	j = calculate_redir_to_char(input, i, shell);
	word = malloc (sizeof(char) * (j + 1));
	if (!word)
		clean_exit("Malloc error", shell);
	j = 0;
	while ((input[i] == '<' || input[i] == '>') && input[i])
		word[j++] = input[i++];
	i = ft_skip_blank(input, i);
	while (!ft_is_blank(input[i]) && input[i] != '|'
		&& input[i] != '<' && input[i] != '>' && input[i] != '"'
		&& input[i] != '\'' && input[i])
		word[j++] = input[i++];
	word[j] = '\0';
	stock_in_struct(shell, word, j, only_count);
	return (i);
}

int	pipe_to_char(char *input, int i, t_data *shell, int only_count)
{
	char	*word;

	(void) input;
	word = "|\0";
	i++;
	if (only_count == 1)
		shell->lexer_size++;
	else
	{
		shell->lexer[shell->lexer_current] = ft_strdup(word);
		if (!shell->lexer[shell->lexer_current])
			clean_exit("Malloc error", shell);
		shell->lexer_current++;
	}
	return (i);
}

int	word_to_char(char *input, int i, t_data *shell, int only_count)
{
	char	*word;
	int		i_save;

	i_save = i;
	word = allocate_word(comp_word_len(input, &i), shell);
	shell->word = word;
	return (fill_word(input, i_save, only_count, shell));
}

int	quote_to_char(char *input, int i, t_data *shell, int only_count)
{
	char	*word;
	int		j;
	int		i_save;
	char	start_quote;

	j = 0;
	start_quote = input[i];
	if (ft_is_quote(input[i]) == 2 && only_count == 0 && start_quote != '"')
		shell->is_quote[shell->lexer_current] = 1;
	i++;
	i_save = i;
	while (input[i] && input[i] != start_quote)
		i++;
	if (!input[i])
		return (i);
	word = malloc(sizeof(char) * ((i - i_save) + 1));
	if (!word)
		clean_exit("Malloc error", shell);
	i = i_save;
	while (input[i] && input[i] != start_quote)
		word[j++] = input[i++];
	word[j] = 0;
	stock_in_struct(shell, word, j, only_count);
	i++;
	return (i);
}

void	replace_with_empty(t_data *shell, t_cur *cur)
{
	free(cur->tmp);
	cur->tmp = NULL;
	replace_substring(&shell->lexer[cur->i], cur, shell);
}
