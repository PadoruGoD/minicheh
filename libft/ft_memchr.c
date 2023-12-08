/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:25:22 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:25:22 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	while (n - i)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			tmp = (unsigned char *)(s + i);
			return (tmp);
		}
		i++;
	}
	return (0);
}
