/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gipaul <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:49:54 by gipaul            #+#    #+#             */
/*   Updated: 2023/12/07 18:42:51 by gipaul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	ft_pwd(t_data *shell, t_list *list)
{
	int		i;
	char	*pwd;

	i = -1;
	pwd = NULL;
	if (list->arg[0])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return ;
	}
	while (shell->env[++i])
	{
		if (!ft_strncmp("PWD", shell->env[i], 3)
			&& shell->env[i][3] == '=')
		{
			pwd = ft_substr(shell->env[i],
					ft_strlen("pwd") + 1, ft_strlen(shell->env[i]));
			if (!pwd)
				clean_exit("Malloc error", shell);
			break ;
		}
	}
	printf("%s\n", pwd);
	free (pwd);
}
*/

int	ft_pwd(void)
{
	char	buffer[1024];

	if (!getcwd(buffer, sizeof(buffer)))
		return (-1);
	printf("%s\n", buffer);
	return (0);
}
