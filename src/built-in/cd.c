/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:57:57 by abosc             #+#    #+#             */
/*   Updated: 2025/06/21 00:14:30 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	move_directory(char *path, t_mnours *mnours)
{
	if (chdir(path) == -1)
	{
		mnours->exit_code = 1;
		ft_printf("cd %s: No such file or directory\n", path);
	}
	else
	{
		update_env(mnours, "OLDPWD", mnours->pwd);
		if (getcwd(mnours->pwd, 1024) == NULL)
		{
			mnours->exit_code = 1;
			ft_printf("cd %s: No such file or directory\n", path);
		}
		update_env(mnours, "PWD", mnours->pwd);
	}
	free(path);
}

int	ft_cd2(char **path, t_mnours *mnours)
{
	if (!*path || (*path)[0] == '~')
	{
		*path = ft_getenv("HOME", mnours->env);
		if (!*path)
			return (mnours->exit_code = 1, ft_printf("cd: HOME not set\n"), 1);
		if (*path && (*path)[0] == '~')
		{
			(*path)++;
			if (**path)
				*path = ft_getenv("HOME", mnours->env);
			else
				*path = ft_strjoin(ft_getenv("HOME", mnours->env), *path);
		}
	}
	else if ((*path)[0] == '-' && !((*path)[1]))
		*path = get_env(mnours, "OLDPWD")->value;
	else if (!*path || !(**path))
	{
		*path = ft_getenv("HOME", mnours->env);
		if (!*path)
			return (mnours->exit_code = 1, ft_printf("cd: HOME not set\n"), 1);
	}
	return (0);
}

int	ft_cd(char **line, t_mnours *mnours)
{
	char	*path;

	path = line[1];
	if (ft_cd2(&path, mnours) == 1)
		return (1);
	if (get_array_size(line) > 2)
	{
		mnours->exit_code = 1;
		return (ft_printf("minishell: too many arguments\n"), 1);
	}
	mnours->exit_code = 0;
	move_directory(ft_strdup(path), mnours);
	mnours->lst_env = convert_env(mnours);
	return (mnours->exit_code);
}
