/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:16:08 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:16:08 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_purge_q_2(char *line, size_t *start, size_t *end, char *str)
{
	*start = *end;
	if (ft_strchr("\'\"", line[*end]) && line[*end + 1]
		&& line[*end + 1] == line[*end])
	{
		*end += 2;
		*start = *end;
	}
	else if (ft_strchr("\'\"", line[*end]))
	{
		ft_skip_q(line, end);
	}
	else
	{
		while (line[*end] && !ft_strchr("\'\"", line[*end]))
			*end += 1;
	}
	if (*start != *end)
		str = ft_strjoin2(str, ft_substr(line, *start, *end - *start));
}

char	*ft_purge_q(char *line)
{
	size_t	end;
	size_t	start;
	char	*str;

	end = 0;
	str = 0;
	while (line[end])
		ft_purge_q_2(line, &start, &end, str);
	printf("str == %s\n", str);
	return (str);
}
