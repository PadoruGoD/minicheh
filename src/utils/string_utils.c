/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:45:30 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 17:58:30 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_quote_to_string(char **str, int number_end_quote)
{
	char	*quote;
	char	*new_str;
	int		i;

	quote = (char *)malloc(number_end_quote + 1);
	i = 0;
	while (i < number_end_quote)
	{
		quote[i] = '\'';
		i++;
	}
	quote[i] = '\0';
	new_str = ft_strjoin(*str, quote);
	free(*str);
	free(quote);
	*str = new_str;
}

static int	process_env(t_data *shell, t_cur *cur, int len_to_end)
{
	int		j;
	int		tmp_size;

	j = -1;
	while (shell->env[++j])
	{
		if (!ft_strncmp(cur->tmp, shell->env[j], len_to_end)
			&& shell->env[j][len_to_end] == '=')
		{
			tmp_size = len_to_end;
			free(cur->tmp);
			cur->tmp = ft_substr(shell->env[j], tmp_size + 1,
					ft_strlen(shell->env[j]));
			if (!cur->tmp)
				clean_exit("Malloc error", shell);
			replace_substring(&shell->lexer[cur->i], cur, shell);
			return (1);
		}
	}
	return (0);
}

void	expander_2(t_data *shell, t_cur *cur)
{
	int		len_to_end;
	int		len_to_real_end;
	int		n_quote;
	int		ret;

	if (shell->lexer[cur->i][cur->k + 1] == '\0')
	{
		cur->tmp = ft_strdup("$");
		if (!cur->tmp)
			clean_exit("Malloc error", shell);
		return ;
	}
	cur->tmp = ft_substr(shell->lexer[cur->i],
			cur->k + 1, ft_strlen(shell->lexer[cur->i]));
	len_to_end = get_substr_length(shell->lexer[cur->i], cur->k + 1);
	len_to_real_end = get_substr_real_length(shell->lexer[cur->i], cur->k + 1);
	n_quote = ft_strlen(cur->tmp) - len_to_real_end;
	if (!cur->tmp)
		clean_exit("Malloc error", shell);
	ret = process_env(shell, cur, len_to_end);
	if (!ret)
		replace_with_empty(shell, cur);
	if (n_quote && ret == 1)
		append_quote_to_string(&shell->lexer[cur->i], n_quote);
}

char	*create_new_string2(char *prefix, t_cur *cur, char *temp_str)
{
	char	*tmp;

	if (cur->tmp)
	{
		tmp = ft_strdup(cur->tmp);
		free(cur->tmp);
		temp_str = ft_strjoin(prefix, tmp);
		free(tmp);
	}
	else
		temp_str = ft_strdup(prefix);
	return (temp_str);
}

char	*create_new_string(char **str, t_cur *cur, t_data *shell)
{
	char	*new_str;
	char	*prefix;
	char	*suffix;
	char	*temp_str;

	temp_str = NULL;
	prefix = ft_substr(*str, 0, cur->k);
	if (!prefix)
		clean_exit("Malloc error", shell);
	suffix = ft_substr(*str, cur->l, ft_strlen(*str) - cur->l);
	if (!suffix)
		clean_exit("Malloc error", shell);
	temp_str = create_new_string2(prefix, cur, temp_str);
	if (!temp_str)
		clean_exit("Malloc error", shell);
	new_str = ft_strjoin(temp_str, suffix);
	free(prefix);
	free(suffix);
	free(temp_str);
	if (!new_str)
		clean_exit("Malloc error", shell);
	return (new_str);
}
