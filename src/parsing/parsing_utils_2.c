/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:30 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:46:07 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	count_quote(char *input, t_data *shell)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_is_quote(input[i]) == 1)
			shell->dquote_count++;
		if (ft_is_quote(input[i]) == 2)
			shell->quote_count++;
		i++;
	}
}

int	ft_is_quote(char c)
{
	if (c == '"')
		return (1);
	if (c == '\'')
		return (2);
	return (0);
}

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

int	ft_skip_blank(char *line, int i)
{
	while (ft_is_blank(line[i]) && line[i])
		i++;
	return (i);
}

void	set_last_of_list(t_data *shell)
{
	t_list	*list;

	list = shell->first;
	while (list)
		list = list->next;
	shell->last = list;
}
