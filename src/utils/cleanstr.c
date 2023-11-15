/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:09:12 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:09:14 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	tokenize_2(char *line, int i)
{
	if (line[i] && line[i] == '|')
	{
		if (i)
			line[i - 1] = 1;
		if (line[i + 1])
			line[i + 1] = 1;
		i++;
	}
	else
		i++;
	return (i);
}

char	*tokenize(char *line)
{
	size_t	i;

	if (!line)
		return (line);
	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '(')
			ft_skip_p(line, &i);
		else if (line[i] && ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] && line[i + 1] && (ft_strnstr(line + i, "&&", 2)
				|| ft_strnstr(line + i, "||", 2)))
		{
			if (i)
				line[i - 1] = 1;
			if (line[i + 2])
				line[i + 2] = 1;
			i += 2;
		}
		else
			i = tokenize_2(line, i);
	}
	return (line);
}
