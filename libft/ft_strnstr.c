/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:30:14 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:30:15 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		i2 = 0;
		while (haystack[i + i2] == needle[i2] && i + i2 < len)
		{
			i2++;
			if (!needle[i2])
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (0);
}
