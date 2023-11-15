/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chwc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:12:34 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:12:35 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_wc_in_fw(char *line)
{
	size_t	i;
	char	c;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i] && !ft_isspace(line[i]))
	{
		if (ft_strchr("\"\'", line[i]))
		{
			c = line[i++];
			while (line[i] && !ft_isspace(line[i]) && line[i] != c)
				i++;
			if (line[i] && !ft_isspace(line[i]))
				i++;
		}
		else if (line[i] == '*')
			return (0);
		else
			i++;
	}
	return (1);
}

void	ft_wcsearch_2(char *line, t_tmp *tmp)
{
	if (line[tmp->end] && ft_strchr("\"\'", line[tmp->end]))
		ft_skip_q(line, &tmp->end);
	else if (line[tmp->end] && line[tmp->end] == '*' && ++tmp->end)
		tmp->c = 1;
	else if (line[tmp->end])
		tmp->end++;
}

// lst == wc

t_list	*ft_wcsearch(char *line)
{
	t_tmp	tmp;

	tmp.end = 0;
	tmp.lst = 0;
	while (line[tmp.end])
	{
		tmp.c = 0;
		tmp.start = tmp.end;
		if (line[tmp.end] && ft_strchr("<>", line[tmp.end]))
			tmp.end = ft_next_word(line, ft_next_word(line, tmp.end));
		else if (line[tmp.end] && !ft_isspace(line[tmp.end])
			&& !ft_strchr("&|", line[tmp.end]))
		{
			while (line[tmp.end] && !ft_isspace(line[tmp.end]))
				ft_wcsearch_2(line, &tmp);
			if (tmp.c == 1)
				ft_lstadd_back(&tmp.lst, ft_lstnew
					(ft_substr(line, tmp.start, tmp.end - tmp.start)));
		}
		else if (line[tmp.end])
			tmp.end++;
	}
	return (tmp.lst);
}
