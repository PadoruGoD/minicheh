/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:15:59 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:16:00 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*prompt(void)
{
	char	*path;
	char	*line;
	char	*sub;
	int		i;

	path = NULL;
	path = getcwd(path, 1024);
	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	sub = ft_substr(path, i + 1, ft_strlen(path));
	line = ft_strjoin(sub, " ❯ ");
	free(path);
	free(sub);
	return (line);
}
