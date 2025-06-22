/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:46:53 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/22 23:24:12 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_export_name(char *line)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(line[0]) && line[0] != '_'))
		return (ft_printf("%s isn't a valid identifier\n", line), 0);
	while (line[i] && line[i] != '=')
	{
		if ((!ft_isalnum(line[i]) && line[i] != '_'))
			return (ft_printf("%s isn't a valid identifier\n", line), 0);
		i++;
	}
	return (1);
}

char	*find_value(char *line, int *i)
{
	char	*value;
	int		count;

	count = 0;
	(*i)++;
	count = ft_strlen(line) - *i;
	value = ft_calloc(sizeof(char), count + 1);
	count = 0;
	while (line[*i])
		value[count++] = line[(*i)++];
	return (value);
}

void	ft_export3(t_mnours *data, t_env *new_env, t_env *env)
{
	t_env	*tmp;

	if (!data->env)
		data->env = new_env;
	if (new_env)
	{
		tmp = env;
		if (!env)
			env = new_env;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
		}
	}
}

int	ft_export2(t_mnours *data, t_env *env, char *line)
{
	t_env	*tmp;
	t_env	*new_env;
	char	*name;
	char	*value;
	int		i;

	tmp = env;
	if (is_export_name(line) == 0)
		return (data->exit_code = 1, 1);
	i = 0;
	name = find_name(line, &i);
	value = find_value(line, &i);
	if (ft_getenv(name, data->env))
	{
		if (value[0] != '\0')
			return (update_env(data, name, value), free(name), free(value), 0);
		else
			return (update_env(data, name, ""), free(name), 0);
	}
	new_env = ft_envnew(line);
	return (ft_export3(data, new_env, env), free(name), free(value), 0);
}

int	ft_export(t_mnours *data, t_env *env, char **line)
{
	int	i;

	i = 1;
	if (line[i] == NULL)
		ft_env(data->lst_env);
	while (line[i])
	{
		while (line[i] && ft_strchr(line[i], '=') == NULL)
		{
			if (is_export_name(line[i]) == 0)
				return (data->exit_code = 1, 1);
			i++;
		}
		if (!line[i])
			break ;
		ft_export2(data, env, line[i++]);
	}
	return (data->lst_env = convert_env(data), 0);
}
