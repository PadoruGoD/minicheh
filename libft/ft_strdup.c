/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:28:42 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/20 17:15:14 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*scpy;
	int		i;

	i = 0;
	scpy = (char *) malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!scpy)
		return (scpy);
	while (s[i])
	{
		scpy[i] = s[i];
		i++;
	}
	scpy[i] = 0;
	return (scpy);
}
