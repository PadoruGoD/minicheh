/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:25 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/21 16:15:59 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end_setenv(char *c, char *name, char *value, int *offset)
{
	char	*tmp;

	tmp = name;
	c = (char *)name;
	while (*c && *c != '=')
		++c;
	free((g_data->env)[*offset]);
	(g_data->env)[*offset] = malloc((size_t)((int)(c - name) \
		+ ft_strlen(value) + 2));
	if (!((g_data->env)[*offset]))
		ft_exit(-1);
	c = (g_data->env)[*offset];
	*c = *name++;
	while ((*c) && *c != '=')
	{
		c++;
		*c = *name++;
	}
	*c++ = '=';
	ft_strlcpy(c, value, ft_strlen(value) + 1);
	g_data->offset = *offset;
	free(tmp);
}

void	dont_exist(int *offset)
{
	static int	alloced;
	int			cnt;
	char		**p;

	p = g_data->env;
	cnt = splitlen(p);
	if (alloced)
	{
		g_data->env = (char **)ft_realloc((char *)g_data->env, \
			(size_t)(sizeof(char *) * (cnt + 2)));
		if (!g_data->env)
			ft_exit(-1);
	}
	else
	{
		alloced = 1;
		p = malloc((size_t)(sizeof(char *) * (cnt + 2)));
		if (!p)
			ft_exit(-1);
		ft_memmove(p, g_data->env, cnt * sizeof(char *));
		g_data->env = p;
	}
	(g_data->env)[cnt + 1] = NULL;
	*offset = cnt;
}

int	exist(char *var, char *value, char *name, char *c)
{
	char		*tmp;
	int			i;

	i = -1;
	if (var[egal_len(var)] != '=')
	{
		free(value);
		free(name);
		return (0);
	}
	tmp = value;
	if ((ft_strlen(c) >= ft_strlen(value)))
	{
		while (value[++i])
			(c[i] = value[i]);
		c[i] = '\0';
		free(tmp);
		free(name);
		return (0);
	}
	return (1);
}

int	my_setenv(char *var)
{
	char		*c;
	int			offset;
	char		*value;
	char		*name;

	name = ft_substr(var, 0, egal_len(var));
	if (!name)
		ft_error(2);
	if (var[egal_len(var)] == '=')
		value = ft_substr(var, egal_len(var) + 1, ft_strlen(var));
	else
		value = ft_strdup("");
	c = my_getenv(name, &offset);
	if (c)
	{
		if (exist(var, value, name, c) == 0)
			return (0);
	}
	else
		dont_exist(&offset);
	end_setenv(c, name, value, &offset);
	free(value);
	return (0);
}

char	*my_getenv(char *name, int *index)
{
	int		i;
	int		j;
	char	*sub;

	i = -1;
	while (g_data->env[++i])
	{
		j = 0;
		while (g_data->env[i][j] && g_data->env[i][j] != '=')
			j++;
		sub = ft_substr(g_data->env[i], 0, j);
		if (!sub)
			ft_error(2);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			if (index != NULL)
				*index = i;
			return (g_data->env[i] + j + 1);
		}
		free(sub);
	}
	return (NULL);
}
