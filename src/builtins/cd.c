/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:02:47 by gipaul            #+#    #+#             */
/*   Updated: 2023/11/20 17:25:31 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	char	buffer[1024];

	if (!getcwd(buffer, sizeof(buffer)))
		return (-1);
	printf("%s\n", buffer);
	return (0);
}

int	cd_2(void)
{
	char	*home;

	home = my_getenv("HOME", NULL);
	if (home == NULL)
	{
		puterror("cd", "HOME not set");
		return (1);
	}
	chdir(home);
	return (0);
}

int	goto_dir(void)
{
	char	pwd_buff[1024];
	char	*pwd_var;
	char	*tmp;

	if (!getcwd(pwd_buff, sizeof(pwd_buff)))
		return (-1);
	pwd_var = my_getenv("PWD", NULL);
	if (pwd_var)
	{
		tmp = my_getenv("PWD", NULL);
		tmp = ft_strjoin("OLDPWD=", tmp);
		my_setenv(tmp);
		free(tmp);
		tmp = ft_strjoin("PWD=", pwd_buff);
		my_setenv(tmp);
		free(tmp);
	}
	return (0);
}

int	cd(char *cmd)
{
	char	**s_cmd;
	int		ret;

	ret = 0;
	s_cmd = ft_split2(cmd, " ");
	if (!s_cmd[1])
		return (cd_2());
	if (chdir(ft_ecrase_q(s_cmd[1])) == -1)
	{
		perror("cd");
		return (1);
	}
	else
		ret = goto_dir();
	ft_free_tab(s_cmd);
	return (ret);
}
