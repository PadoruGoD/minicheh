/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:31:03 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:38:56 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (!s)
		return (0);
	if (start + i < ft_strlen(s))
		while (s[start + i] && i < len)
			i++;
	dst = malloc(sizeof(*dst) * i + 1);
	if (!dst)
		ft_error(2);
	dst[i] = '\0';
	while (i--)
		dst[i] = s[start + i];
	return (dst);
}
