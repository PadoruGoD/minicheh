/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:31:03 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/20 17:15:05 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (ft_strlen(s) < start)
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		*new = 0;
		return (new);
	}
	else if (len > ft_strlen(&s[start]))
		new = malloc(sizeof(*new) * (ft_strlen(&s[start]) + 1));
	else
		new = malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (NULL);
	while (i < len && s[start])
		new[i++] = s[start++];
	new[i] = 0;
	return (new);
}
