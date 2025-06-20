/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:46:53 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 05:26:13 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**join_split(char **split)
{
	char	*tmp;
	char	**result;
	int		i;

	result = ft_calloc(sizeof(char *), 3);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(split[0]);
	result[1] = ft_strjoin(split[1], "=");
	tmp = result[1];
	result[1] = ft_strjoin(result[1], split[2]);
	free(tmp);
	i = 3;
	while (split[i])
	{
		tmp = result[1];
		result[1] = ft_strjoin(result[1], "=");
		free(tmp);
		tmp = result[1];
		result[1] = ft_strjoin(result[1], split[i++]);
		free(tmp);
	}
	free_array(split);
	return (result);
}

char	*find_name(char *line, int *i)
{
	char	*name;
	int		j;

	j = 0;
	while (line[*i] != '=')
		(*i)++;
	name = ft_calloc(sizeof(char), *i + 1);
	while (line[j] != '=')
	{
		name[j] = line[j];
		j++;
	}
	return (name);
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
	value[count] = '\0';
	return (value);
}

int	ft_export2(t_mnours *data, t_env *env, char *line)
{
	t_env	*tmp;
	t_env	*new_env;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	tmp = env;
	if (ft_isalpha(line[0]) == 0 && line[0] != '_')
	{
		ft_printf("%s isn't a valid identifier\n", line);
		return (1);
	}
	name = find_name(line, &i);
	value = find_value(line, &i);
	if (ft_getenv(name, data->env))
	{
		if (value[0] != '\0')
		{
			update_env(data, name, value);
			free(name);
			free(value);
			return (0);
		}
		else
		{
			update_env(data, name, "");
			free(name);
			return (0);
		}
	}
	new_env = ft_envnew(line);
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
	free(name);
	free(value);
	return (0); 
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
			i++;
		if (!line[i])
			break ;
		ft_export2(data, env, line[i++]);
	}
	data->lst_env = convert_env(data);
	return (0);
}
