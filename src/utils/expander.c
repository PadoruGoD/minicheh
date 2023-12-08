/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:45:46 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 16:47:03 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_substring(char **str, t_cur *cur, t_data *shell)
{
	char	*new_str;

	new_str = create_new_string(str, cur, shell);
	free(*str);
	*str = new_str;
	cur->k = ft_strlen(*str) - 1;
}

void	expand_lastret(t_data *shell, t_cur *cur)
{
	char	*tmp;

	tmp = ft_itoa(shell->lastret);
	if (!tmp)
		clean_exit("Malloc error", shell);
	cur->tmp = tmp;
	replace_substring(&shell->lexer[cur->i], cur, shell);
}

static void	expand_variable(t_data *shell, t_cur *cur)
{
	if (shell->lexer[cur->i][cur->k] == '$' && shell->is_quote[cur->i] == 0)
	{
		if (shell->lexer[cur->i][cur->k + 1] == '?')
		{
			cur->l = cur->k + 2;
			expand_lastret(shell, cur);
			return ;
		}
		cur->l = cur->k;
		while (!ft_is_blank(shell->lexer[cur->i][cur->l])
			&& shell->lexer[cur->i][cur->l])
			cur->l++;
		expander_2(shell, cur);
	}
}

void	expander(t_data *shell, char **env)
{
	int		j;
	t_cur	*cur;

	(void) env;
	cur = malloc(sizeof(t_cur));
	if (!cur)
		clean_exit("Malloc error", shell);
	cur->i = -1;
	j = -1;
	shell->lexer[shell->lexer_size] = 0;
	while (shell->lexer[++cur->i])
	{
		cur->m = -1;
		cur->k = -1;
		while (shell->lexer[cur->i][++cur->m])
		{
			cur->k = cur->m;
			expand_variable(shell, cur);
		}
	}
	if (cur)
		free(cur);
}

int	get_substr_length(char *str, int start_idx)
{
	int	len;

	len = 0;
	while (str[start_idx + len] && str[start_idx + len] != '\''
		&& str[start_idx + len] != ' ')
		len++;
	return (len);
}
