/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:48:09 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:50:13 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	comp_word_len(char *input, int *i)
{
	int	in_quotes;
	int	i_save;

	in_quotes = 0;
	i_save = *i;
	while (input[*i] && (in_quotes || (!ft_is_separator(input[*i])
				&& !ft_is_blank(input[*i]))))
	{
		if (input[*i] == '"' && in_quotes == 0)
			in_quotes = 1;
		else if (input[*i] == '"' && in_quotes == 1)
			in_quotes = 0;
		(*i)++;
	}
	return (*i - i_save);
}

char	*allocate_word(int length, t_data *shell)
{
	char	*word;

	word = malloc(sizeof(char) * (length + 1));
	if (!word)
		clean_exit("Malloc error", shell);
	return (word);
}

int	fill_word(char *input, int i_save,
	int only_count, t_data *shell)

{
	int	in_quotes;
	int	j;

	j = 0;
	in_quotes = 0;
	while (input[i_save] && (in_quotes || (!ft_is_separator(input[i_save])
				&& !ft_is_blank(input[i_save]))))
	{
		if (ft_is_quote(input[i_save]) == 2 && only_count == 0
			&& input[i_save] != '"')
			shell->is_quote[shell->lexer_current] = 1;
		if (ft_is_quote(input[i_save]) > 0 && in_quotes == 0)
			in_quotes = 1;
		else if (ft_is_quote(input[i_save]) > 0 && in_quotes == 1)
			in_quotes = 0;
		else
			shell->word[j++] = input[i_save];
		i_save++;
	}
	shell->word[j] = '\0';
	stock_in_struct(shell, shell->word, j, only_count);
	return (i_save);
}

int	ft_is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
