/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:26:43 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 16:31:21 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str != c && *str)
			count++;
		while (*str != c && *str)
			str++;
	}
	return (c);
}

static size_t	ft_len_of_word(char const *str, char c)
{
	size_t	len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static char	*ft_word_up(char const *str, size_t len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * len + 1);
	if (!word)
		return (NULL);
	while (i < (int)len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_len_of_word(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != c && *s)
				tab[i++] = ft_word_up(s, ft_count_words(s, c));
		while (*s && *s != c)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
