/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:03 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:45:46 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	correct_here_doc(t_list *list)
{
	char	*tmp;

	if (list->id == HEREDOC_TOKEN)
	{
		tmp = ft_substr(list->value, 2, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

static void	correct_entry(t_list *list)
{
	char	*tmp;

	if (list->id == ENTRY_TOKEN)
	{
		tmp = ft_substr(list->value, 1, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

static void	correct_exit(t_list *list)
{
	char	*tmp;

	if (list->id == EXIT_TOKEN)
	{
		tmp = ft_substr(list->value, 1, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

static void	correct_append(t_list *list)
{
	char	*tmp;

	if (list->id == APPEND_TOKEN)
	{
		tmp = ft_substr(list->value, 2, ft_strlen(list->value));
		free(list->value);
		list->value = tmp;
	}
}

void	correct_redir(t_data *shell)
{
	t_list	*list;

	list = shell->first;
	while (list)
	{
		correct_here_doc(list);
		correct_entry(list);
		correct_exit(list);
		correct_append(list);
		list = list->next;
	}
}
