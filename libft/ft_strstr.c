/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:30:41 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:30:41 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char	*str, char	*to_find)
{
	int	i;

	if (to_find[0] == '\0')
		return (str);
	while (*str)
	{
		if (*str == *to_find)
		{
			i = 1;
			while (to_find[i] && str[i] == to_find[i])
				i++;
			if (!to_find[i])
				return (str);
		}
		str++;
	}
	return (0);
}
