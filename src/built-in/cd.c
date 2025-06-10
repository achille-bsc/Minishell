/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:57:57 by abosc             #+#    #+#             */
/*   Updated: 2025/06/11 00:29:59 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	move_directory(char *path, t_mnours *mnours)
{
	if (chdir(path) == -1)
		ft_printf("cd %s: No such file or directory\n", path);
	else
	{
		update_env(mnours, "OLDPWD", mnours->pwd);
		if (getcwd(mnours->pwd, 1024) == NULL)
			ft_printf("cd %s: No such file or directory\n", path);
		update_env(mnours, "PWD", mnours->pwd);
	}
}

int	ft_cd(char **line, t_mnours *mnours)
{
	char	*path;

	path = line[1];
	if (!path || path[0] == '~')
	{
		path = getenv("HOME");
		if (path && path[0] == '~')
		{
			path++;
			if (*path)
				path = getenv("HOME");
			else
				path = ft_strjoin(getenv("HOME"), path);
		}
	}
	else if (path[0] == '-' && !path[1])
		path = mnours->oldpwd;
	else if (!path || !*path)
	{
		path = ft_getenv("HOME", mnours->env);
		if (!path)
			return (ft_printf("cd: HOME not set\n"), 1);
	}
	if (get_array_size(line) > 2)
		return (ft_printf("minishell: too many arguments\n"), 1);
	move_directory(path, mnours);
	mnours->lst_env = convert_env(mnours);
	return (0);
}
