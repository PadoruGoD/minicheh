/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:29:26 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:29:27 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <printf.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i2;

	if (!src)
		return (ft_strlen(dst));
	i = -1;
	while (++i < dstsize && *dst)
		dst++;
	if (i == dstsize)
		return (i + ft_strlen(src));
	i2 = 0;
	while (src[i2] != '\0')
	{
		if (i2 <= dstsize - 1 - i)
			*dst++ = src[i2++];
		else
			i2++;
	}
	*dst = '\0';
	return (i + i2);
}
