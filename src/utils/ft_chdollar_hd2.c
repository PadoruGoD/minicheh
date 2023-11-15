/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdollar_hd2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:11:51 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:11:52 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_chdollar_ok_hd(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '$')
			return (0);
		else if (line[i])
			i++;
	}
	return (1);
}

char	*ft_changedollar_hd(char *line, t_list **dollar)
{
	char	*str;

	if (ft_isdigit(line[0]))
		str = 0;
	else if (ft_strncmp(line, "$?", 1))
		str = ft_strdup(my_getenv(line + 1, 0));
	else if (!ft_strncmp(line, "$?", 1))
		str = ft_itoa(g_data->lastret);
	else
		str = 0;
	ft_lstadd_back(dollar, ft_lstnew(str));
	free(line);
	return (str);
}
