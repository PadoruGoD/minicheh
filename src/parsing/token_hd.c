/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:46:54 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 16:46:56 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_init_token(t_data *shell)
{
	t_list	*token;

	token = (t_list *)malloc(sizeof(t_list));
	if (!token)
		clean_exit("Malloc error", shell);
	token->prev = 0;
	token->next = 0;
	token->id = 0;
	token->fd_in = 0;
	token->fd_out = 0;
	return (token);
}

void	ft_add_token(t_data *shell, t_list *to_add)
{
	t_list	*tmp;

	if (!shell->first)
		shell->first = to_add;
	else
	{
		tmp = shell->first;
		while (tmp->next)
			tmp = tmp->next;
		ft_connect_token(tmp, to_add);
	}
}

void	ft_connect_token(t_list *list, t_list *to_add)
{
	list->next = to_add;
	to_add->prev = list;
}

static void	destroy_token_2(t_data *shell)
{
	t_list	*list;
	t_list	*temp;
	char	**args;

	list = shell->first;
	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->value != 0)
			free(temp->value);
		if (temp->arg != 0)
		{
			args = temp->arg;
			while (*args != 0)
			{
				free(*args);
				args++;
			}
			free(temp->arg);
		}
		free(temp);
	}
}

void	destroy_token(t_data *shell)
{
	int		i;

	destroy_token_2(shell);
	free_lexer(shell);
	i = -1;
	if (shell->path)
	{
		while (shell->path[++i])
			free(shell->path[i]);
		free(shell->path);
	}
	if (shell->is_quote)
		free(shell->is_quote);
	if (shell->input)
		free(shell->input);
}
