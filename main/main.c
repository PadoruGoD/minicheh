/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <ndiamant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:01:54 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/23 16:31:21 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ls && (echo 1 && echo 2 )

#include "../includes/minishell.h"

void	shlvlhandler(char *lvl, char *join2)
{
	char	*var;
	int		shlvl;
	char	*join;

	var = my_getenv("SHLVL", NULL);
	shlvl = ft_atoi(var) + 1;
	join = ft_strdup("_=/usr/bin/env");
	my_setenv(join);
	my_setenv("OLDPWD");
	if (shlvl > 1000)
		shlvl = 1;
	if (shlvl == 1000)
		my_setenv("SHLV");
	else
	{
		lvl = ft_itoa(shlvl);
		join2 = ft_strjoin("SHLVL=", lvl);
		my_setenv(join2);
	}
	free(lvl);
	free(join);
	free(join2);
}

void	initiate_values(t_data *envglo, char **env)
{
	envglo->lastret = 0;
	envglo->env = env;
	envglo->env = array_dup();
	envglo->hd = 0;
	shlvlhandler(NULL, NULL);
	tcgetattr(0, &envglo->old);
	tcgetattr(0, &envglo->new);
	envglo->new.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &envglo->new);
	signal(SIGINT, c_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main_3(char **line, char *pt)
{
	t_data	*envglo;

	envglo->hd_stop = 0;
	pt = prompt();
	*line = readline(pt);
	free(pt);
	if (!*line)
	{
		ft_putstr_fd("\b\bexit\n", 2);
		ft_exit(0);
	}
	if (**line)
		add_history(*line);
	if (!**line || ft_isprohibited(*line) == 1)
	{
		free(*line);
		return (1);
	}
	return (0);
}

void	main_2(void)
{
	char	*line;
	t_token	*token;

	line = NULL;
	while (1)
	{
		if (main_3(&line, NULL))
			continue ;
		line = ft_epur_str(ft_chdir(ft_pgross_str((line))));
		if (!*line)
			continue ;
		if (ft_isprohibited(line) == 1)
		{
			free(line);
			continue ;
		}
		token = ft_parsing(line);
		if (ft_token_error(token))
			continue ;
		free(line);
		execute(token);
		ft_tokenclean_all(&token);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*envglo;
	(void) av;
	//sleep(10);
	if (ac != 1)
	{
		puterror("\e[0;37mUse", "./minishell without arguments");
		return (0);
	}
	envglo = malloc(sizeof(t_data));
	if (!(envglo))
		return (0);
	initiate_values(envglo, env);
	main_2();
	ft_exit(envglo->lastret);
}
