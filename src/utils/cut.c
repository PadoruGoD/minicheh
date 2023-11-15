/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:09:19 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:09:21 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_cutoff(char *str, size_t start, size_t len)
{
	char	*newstr;
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!newstr)
		ft_error(2);
	while (str[i])
	{
		if (i < start || i >= start + len)
			newstr[i2++] = str[i++];
		else
			i++;
	}
	newstr[i2] = 0;
	return (newstr);
}
