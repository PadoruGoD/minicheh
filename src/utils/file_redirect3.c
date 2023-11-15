/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:10:59 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/15 16:27:55 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*ft_chrredirect(char *line, t_hd **open, t_hd **open2, size_t *v);

void	ft_file_2(size_t *v, char *line, size_t *i)
{
	*v = 1;
	while (line[*i] && *v != 0)
	{
		if (line[*i] == '(')
			(*v)++;
		else if (line[*i] == ')')
			(*v)--;
		(*i)++;
	}
}

t_list	*ft_file(char *line, char c, t_hd **open, t_hd **open2)
{
	t_list	*lst;
	size_t	i;
	char	*str;
	size_t	v;

	v = 0;
	lst = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] && ft_strchr("(", line[i]) && ++i)
			ft_file_2(&v, line, &i);
		else if (line[i] && line[i] == c && line[i + 1])
		{
			v = 0;
			str = ft_chrredirect(line + i, open, open2, &v);
			ft_lstadd_back(&lst, ft_lstnew(str));
			i += v;
		}
		else if (line[i])
			i++;
	}
	return (lst);
}

t_redirect	ft_init_redirect(void)
{
	t_redirect	file;

	file.infile = 0;
	file.outfile = 0;
	file.infd = 0;
	file.outfd = 1;
	file.open = 0;
	file.open2 = 0;
	return (file);
}
