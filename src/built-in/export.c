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
	t_env	*new_env;
	char	**split_result;
	int		i;

	tmp = env;
	i = 0;
	if (ft_isalpha(line[0]) == 0 && line[0] != '_')
	{
		ft_printf("%s isn't a valid identifier\n", line);
		return ;
	}
	
	// Diviser la ligne en nom=valeur
	split_result = ft_split(line, '=');
	if (!split_result || !split_result[0])
	{
		if (split_result)
			free_array(split_result);
		return ;
	}
	
	// Chercher si la variable existe déjà
	while (tmp)
	{
		if (ft_strncmp(split_result[0], tmp->name, ft_strlen(split_result[0])) == 0
			&& ft_strlen(tmp->name) == ft_strlen(split_result[0]))
		{
			// Mettre à jour la valeur existante
			free(tmp->value);
			tmp->value = split_result[1] ? ft_strdup(split_result[1]) : ft_strdup("");
			free_array(split_result);
			return ;
		}
		tmp = tmp->next;
	}
	
	// Si la variable n'existe pas, la créer et l'ajouter à la fin
	new_env = ft_envnew(line);
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
		}
	}
	free_array(split_result);
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
