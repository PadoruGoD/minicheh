/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:15:50 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/23 15:58:56 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_parsing2(t_token *sup_token)
{
	char	**tab;
	t_token	*token;
	t_token	*tmp;
	char	*line;

	line = tokenize(ft_ecrase_p(sup_token->cmd));
	tab = ft_split(line, "=");
	free(line);
	token = ft_tab_to_token2(tab, sup_token);
	tmp = token;
	while (tmp)
	{
		ft_hdadd_back(&g_data->hd, ft_hd_finder(tmp->cmd));
		tmp->redirect = ft_init_redirect();
		if (tmp->cmd[0] == '(')
			tmp->sub_token = ft_parsing2(tmp);
		tmp = tmp->next;
	}
	return (token);
}

t_token	*ft_parsing(char *line)
{
	char	**tab;
	t_token	*token;
	t_token	*tmp;

	line = tokenize(line);
	tab = ft_split(line, "=");
	token = ft_tab_to_token(tab);
	tmp = token;
	while (tmp)
	{
		ft_hdadd_back(&g_data->hd, ft_hd_finder(tmp->cmd));
		tmp->redirect = ft_init_redirect();
		if (tmp->cmd[0] == '(')
			tmp->sub_token = ft_parsing2(tmp);
		tmp = tmp->next;
	}
	return (token);
}
