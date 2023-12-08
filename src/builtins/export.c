/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 19:36:06 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sort_env(char **env)
{
	char	**i;
	char	**j;
	char	*tmp;

	i = env;
	while (*i)
	{
		j = i + 1;
		while (*j)
		{
			if (ft_strncmp(*i, *j, 1) > 0)
			{
				tmp = *i;
				*i = *j;
				*j = tmp;
			}
			j++;
		}
	i++;
	}
}

char	**array_dup(t_data *shell)
{
	char	**export;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (shell->env[j])
		j++;
	export = malloc(sizeof(char *) * (j + 1));
	if (!export)
		clean_exit("Malloc error", shell);
	while (shell->env[++i])
	{
		export[i] = ft_strdup(shell->env[i]);
		if (!export[i])
			clean_exit("Malloc error", shell);
	}
	export[i] = 0;
	return (export);
}

void	ft_export(t_data *shell, t_list *list)
{
	char	**export;
	int		i;

	i = -1;
	export = array_dup(shell);
	sort_env(export);
	if (!list->arg[0])
	{
		while (export[++i])
		{
			printf("%s\n", export[i]);
			free(export[i]);
		}
		free(export);
	}
}
