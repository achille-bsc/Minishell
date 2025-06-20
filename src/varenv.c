/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:12:27 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/20 17:48:08 by alegrix          ###   ########.fr       */
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
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*end = i;
	if (i == start)
		return (NULL);
	var_name = ft_substr(str, start, i - start);
	return (var_name);
}

char	*replace_variable(char *str, t_env *env, int k)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*before;
	char	*after;
	char	*temp_str;
	int		i;
	int		var_end;
	int		found_var;

	if (!str)
		return (NULL);
	if (!env)
		return (ft_strdup(str));
	temp_str = ft_strdup(str);
	if (k == 1)
		free(str);
	i = 0;
	found_var = 0;
	while (temp_str[i])
	{
		if (temp_str[i] == '$')
		{
			var_name = extract_var_name(temp_str, i + 1, &var_end);
			if (var_name)
			{
				found_var = 1;
				var_value = get_var_value(var_name, env);
				before = ft_substr(temp_str, 0, i);
				after = ft_strdup(temp_str + var_end);
				if (var_value)
				{
					result = ft_calloc(ft_strlen(before) + ft_strlen(var_value) + ft_strlen(after) + 1, 1);
					ft_strlcpy(result, before, ft_strlen(before) + 1);
					ft_strlcat(result, var_value, ft_strlen(before) + ft_strlen(var_value) + 1);
					ft_strlcat(result, after, ft_strlen(before) + ft_strlen(var_value) + ft_strlen(after) + 1);
				}
				else
				{
					result = ft_calloc(ft_strlen(before) + ft_strlen(after) + 1, 1);
					ft_strlcpy(result, before, ft_strlen(before) + 1);
					ft_strlcat(result, after, ft_strlen(before) + ft_strlen(after) + 1);
				}
				free(before);
				free(after);
				free(var_name);
				free(temp_str);
				return (replace_variable(result, env, 1));
			}
		}
		i++;
	}
	return (temp_str);
}

char	**var_search(char **tab, t_env *env)
{
	int		i;
	char	*old_str;
	char	*new_str;

	if (!tab || !env)
		return (tab);
	i = 0;
	while (tab[i])
	{
		old_str = tab[i];
		new_str = replace_variable(tab[i], env, 0);
		if (new_str)
		{
			free(old_str);
			tab[i] = new_str;
		}
		i++;
	}
	return (tab);
}
