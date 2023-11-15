/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdollar3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:11:35 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:11:36 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_chdollar_ok(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '\"' && ++i)
		{
			while (line[i] && line[i] != '\"')
			{
				if (line[i] && line[i] == '$')
					return (0);
				i++;
			}
			if (line[i])
				i++;
		}
		else if (line[i] && line[i] == '\'')
			ft_skip_q(line, &i);
		else if (line[i] && line[i] == '$')
			return (0);
		else if (line[i])
			i++;
	}
	return (1);
}
