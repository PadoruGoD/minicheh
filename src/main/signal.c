/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:47:33 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 14:52:57 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	disable_ctrl_c(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	child_sigint_hd(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

void	sigint_hd(int sig)
{
	(void) sig;
	if (g_data_heredoc == 1)
		g_data_heredoc = 0;
	if (g_data_heredoc == 2)
	{
		g_data_heredoc = 0;
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	sigquit_hd(int sig)
{
	(void) sig;
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	setup_signal(void)
{
	signal(SIGINT, sigint_hd);
	signal(SIGQUIT, SIG_IGN);
}
