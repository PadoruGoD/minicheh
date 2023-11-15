/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:14:15 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:14:16 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace(char *str, char *search, char *replace)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*ret;

	end = 0;
	ret = 0;
	while (str[end])
	{
		start = end;
		len = ft_strlen(search);
		if (!ft_strrcmp(str + end, search, len - 1))
		{
			while (str[end] && !ft_strrcmp(str + end, search, len - 1))
				end++;
			ret = ft_strjoin3(ret, ft_substr(str, start, end - start - 1));
		}
		if (str[end] && ft_strrcmp(str + end, search, len - 1))
			ret = ft_strjoin3(ret, replace);
	}
	return (ret);
}
