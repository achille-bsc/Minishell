/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:46:53 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 01:06:37 by abosc            ###   ########.fr       */
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


int	ft_export2(t_mnours *data, t_env *env, char *line)
{
	t_env	*tmp;
	t_env	*new_env;
	char	**split_result;
	int		i;

	tmp = env;
	i = 0;
	if (ft_isalpha(line[0]) == 0 && line[0] != '_')
	{
		ft_printf("%s isn't a valid identifier\n", line);
		return (1);
	}
	// Diviser la ligne en nom=valeur
	split_result = ft_split(line, '=');
	if (get_array_size(split_result) == 3 && split_result[2])
		split_result = join_split(split_result);
	// Chercher si la variable existe déjà
	if (ft_getenv(split_result[0], data->env))
	{
		if (get_array_size(split_result) == 2 && split_result[1])
		{
			update_env(data, split_result[0], split_result[1]);
			return (0);
		}
		else
		{
			update_env(data, split_result[0], "");
			return (0);
		}
	}
	// while (tmp)
	// {
	// 	if (ft_strncmp(split_result[0], tmp->name,
	// ft_strlen(split_result[0])) == 0
	// 		&& ft_strlen(tmp->name) == ft_strlen(split_result[0]))
	// 	{
	// 		// Mettre à jour la valeur existante
	// 		free(tmp->value);
	// 		tmp->value = ft_strdup(split_result[1]);
	// 		return (free_array(split_result));
	// 	}
	// 	tmp = tmp->next;
	// }
	// Si la variable n'existe pas, la créer et l'ajouter à la fin
	new_env = ft_envnew(line);
	ft_printf("new_env: %s\n", new_env->name);
	if (!data->env)
		data->env = new_env;
	if (new_env)
	{
		// Trouver la fin de la liste et ajouter
		tmp = env;
		if (!env)
			env = new_env;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
			ft_printf("tmp->next: %s\n", tmp->next->name);
		}
	}
	free_array(split_result);
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
