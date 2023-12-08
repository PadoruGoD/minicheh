/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:47:18 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/08 16:29:20 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_data_heredoc = 0;

void	ft_shlvl(t_data *shell)
{
	int		i;
	int		shlvl;
	char	*new_value;
	char	*temp;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(shell->env[i] + 6);
			shlvl++;
			new_value = ft_itoa(shlvl);
			temp = ft_strjoin("SHLVL=", new_value);
			free(shell->env[i]);
			shell->env[i] = temp;
			free(new_value);
			break ;
		}
		i++;
	}
}

static void	sigint_main_hd(int sig)
{
	(void) sig;
	if (g_data_heredoc == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	hd_input(t_data *shell)
{
	if (shell->input[0] == '\0')
		return ;
	add_history(shell->input);
	count_quote(shell->input, shell);
	lexer_size(shell->input, shell);
	ft_memset(shell->is_quote, 0, sizeof(int) * shell->lexer_size);
	lexer(shell->input, shell);
	expander(shell, shell->env);
	parsing(shell);
	set_last_of_list(shell);
	if (check_syntax(shell) && shell->lexer_size > 0)
		exec(shell);
	destroy_token(shell);
}

static void	prompt(t_data *shell)
{
	char	*pwd;

	shell->lastret = -1;
	while (1)
	{
		signal(SIGINT, sigint_main_hd);
		signal(SIGQUIT, SIG_IGN);
		init_struct(shell, shell->env);
		pwd = prompt_data(shell);
		shell->input = readline(pwd);
		if (ft_strncmp(pwd, "minishell> ", 13))
			free(pwd);
		if (shell->input == NULL)
		{
			if (g_data_heredoc)
				write(1, "\n", 1);
			else
				break ;
		}
		hd_input(shell);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	shell;
	int		i;

	(void) av;
	i = 0;
	while (env[i])
		i++;
	shell.env = malloc (sizeof(char *) * (i + 1));
	if (!shell.env)
		return (1);
	shell.env[i] = 0;
	i = -1;
	while (env[++i])
	{
		shell.env[i] = ft_strdup(env[i]);
	}
	ft_shlvl(&shell);
	disable_ctrl_c();
	using_history();
	write(1, "\n", 1);
	if (ac == 1)
		prompt(&shell);
	else
		printf("No args accepted in minishell.\n");
	ft_free_tab(&shell);
	return (0);
}
