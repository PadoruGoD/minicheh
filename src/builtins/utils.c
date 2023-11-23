/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:04:06 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/23 15:49:02 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	return (new_ptr);
}

int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][egal_len(env[i]) + 1])
		{
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}

void	format_env(char *var)
{
	char	*sub;
	char	*sub2;

	sub = ft_substr(var, 0, egal_len(var));
	if (!ft_strcmp(sub, "_"))
	{
		free(sub);
		return ;
	}
	printf(" %s", sub);
	if (var[egal_len(var)] == '=')
	{
		sub2 = ft_substr(var, egal_len(var) + 1, ft_strlen(var));
		if (ft_strlen(sub2) != 0)
			printf("=\"%s\"", sub2);
		free(sub2);
	}
	printf("\n");
	free(sub);
}

int	egal_len(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	return (i);
}

char	**array_dup(void)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (splitlen(g_data->env) + 1));
	if (!res)
		return (NULL);
	while (i < splitlen(g_data->env))
	{
		res[i] = ft_strdup(g_data->env[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
