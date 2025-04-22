/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:46:53 by alegrix           #+#    #+#             */
/*   Updated: 2025/04/22 18:26:15 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export2(t_env *env, char *line)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	if (ft_isalpha(line[0]) == 1 || line[0] == '_')
	{
		ft_printf("%s isn't a valid identifier\n", line);
		return ;
	}
	while (line[i] && line[i] != ' ' && line[i] != '=')
		i++;
	while (tmp)
	{
		if (ft_strncmp(line, tmp->name, i) == 0)
		{
			free(tmp->value);
			tmp->value = line;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = ft_envnew(line);
}

void	ft_export(t_env *env, char **line)
{
	int	i;

	i = 1;
	if (line[i] == NULL)
		ft_env(env);
	while (line[i])
		ft_export2(env, line[i++]);
}
