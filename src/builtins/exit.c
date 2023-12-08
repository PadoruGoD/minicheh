/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:03:37 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:50:23 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_all_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_data *shell, t_list *list)
{
	int	error;

	error = 0;
	if (list->arg && list->arg[0])
	{
		if (list->arg[1])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			return ;
		}
		if (!is_all_digit(list->arg[0]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			return ;
		}
		error = ft_atoi(list->arg[0]);
		destroy_token(shell);
		exit(error);
	}
	destroy_token(shell);
	ft_free_tab(shell);
	exit(0);
}
