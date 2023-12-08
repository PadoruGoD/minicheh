/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systeme_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:49:06 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/06 16:49:07 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_dup2(int to_change, int new)
{
	if (dup2(to_change, new) == -1)
	{
		perror("Error duplicating file descriptor");
		exit(EXIT_FAILURE);
	}
}

void	ft_close(int to_close)
{
	if (close(to_close))
	{
		perror("Error closing file descriptor");
		exit(EXIT_FAILURE);
	}
}

void	ft_write(int fd, char *value, size_t size)
{
	if (write(fd, value, size) == -1)
	{
		perror("Error during write");
		exit(EXIT_FAILURE);
	}
}

void	ft_unlink(char *name)
{
	if (unlink(name) == -1)
	{
		perror("Error during unlink");
		exit(EXIT_FAILURE);
	}
}
