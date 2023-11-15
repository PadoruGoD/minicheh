/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:05 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:03:07 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_2(char **cmd, int *i, int *option)
{
	int	j;

	while (cmd[*i] && cmd[*i][0] == '-')
	{
		j = 1;
		while (cmd[*i][j] && cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j] == '\0')
		{
			*i += 1;
			*option = 1;
		}
		else
			break ;
	}
}

int	echo(char **cmd)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	echo_2(cmd, &i, &option);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
