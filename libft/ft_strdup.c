/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:28:42 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:28:43 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	if (!s1)
		return (0);
	size = ft_strlen(s1);
	s2 = malloc(sizeof(*s2) * size + 1);
	if (!s2)
		ft_error(2);
	ft_strlcpy(s2, s1, size + 1);
	return (s2);
}	
