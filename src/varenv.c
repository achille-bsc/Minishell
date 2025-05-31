/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:12:27 by alegrix           #+#    #+#             */
/*   Updated: 2025/05/31 02:48:59 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*get_var_value(char *var_name, t_env *env)
{
	t_env	*current;

	if (!var_name || !env)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strncmp(current->name, var_name, ft_strlen(var_name)) == 0
			&& ft_strlen(current->name) == ft_strlen(var_name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*extract_var_name(char *str, int start, int *end)
{
	int		i;
	char	*var_name;

	i = start;
	// Rechercher la fin du nom de variable (lettres, chiffres, underscore)
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*end = i;
	if (i == start)
		return (NULL);
	var_name = ft_substr(str, start, i - start);
	return (var_name);
}

char	*replace_variable(char *str, t_env *env)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*before;
	char	*after;
	int		i;
	int		var_end;

	if (!str || !env)
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = extract_var_name(str, i + 1, &var_end);
			if (var_name)
			{
				var_value = get_var_value(var_name, env);
				if (var_value)
				{
					before = ft_substr(str, 0, i);
					after = ft_strdup(str + var_end);
					result = ft_calloc(ft_strlen(before) + ft_strlen(var_value) + ft_strlen(after) + 1, 1);
					ft_strlcpy(result, before, ft_strlen(before) + 1);
					ft_strlcat(result, var_value, ft_strlen(before) + ft_strlen(var_value) + 1);
					ft_strlcat(result, after, ft_strlen(before) + ft_strlen(var_value) + ft_strlen(after) + 1);
					free(before);
					free(after);
					free(var_name);
					free(str);
					return (replace_variable(result, env)); // Récursion pour autres variables
				}
				free(var_name);
			}
		}
		i++;
	}
	return (str);
}

char	**var_search(char **tab, t_env *env)
{
	int	i;

	if (!tab || !env)
		return (tab);
	i = 0;
	while (tab[i])
	{
		tab[i] = replace_variable(tab[i], env);
		i++;
	}
	return (tab);
}
