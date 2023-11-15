/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:16:56 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:16:57 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	ft_strrcmp2(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = n;
	while (*(unsigned char *)s1)
		s1++;
	while (i && (*(unsigned char *)s1 == ((unsigned char *)s2)[i]))
	{
		s1--;
		i--;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	ft_lstdel(t_list **lst, t_list *elem)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp && (tmp)->next && (tmp)->next != elem && (tmp) != elem)
		tmp = (tmp)->next;
	if ((tmp)->next)
	{
		tmp2 = tmp->next;
		tmp->next = tmp2->next;
		free(tmp2->content);
		free(tmp2);
	}
}
