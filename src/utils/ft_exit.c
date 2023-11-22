/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:13:19 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/21 17:46:18 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(int numerror)
{
	ft_free_tab(g_data->env);
	free(g_data);
	tcsetattr(0, TCSANOW, &g_data->new);
	rl_clear_history();
	exit(numerror);
}
