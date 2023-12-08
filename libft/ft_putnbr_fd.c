/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:26:25 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/13 16:26:26 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd != -1)
	{
		if (n == -2147483648)
		{
			ft_putstr_fd("-2147483648", fd);
			return ;
		}
		else if (n < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(-n, fd);
		}
		else
		{
			if (n > 9)
			{
				ft_putnbr_fd(n / 10, fd);
			}
			ft_putchar_fd(48 + n % 10, fd);
		}
	}
}
