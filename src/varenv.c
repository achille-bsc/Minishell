/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:12:27 by alegrix           #+#    #+#             */
/*   Updated: 2025/06/23 03:19:55 by abosc            ###   ########.fr       */
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

char	*rep2(char *var_val, int var_end, char *temp_str, int i)
{
	char	*result;
	char	*tmp[2];

	tmp[0] = ft_substr(temp_str, 0, i);
	tmp[1] = ft_strdup(temp_str + var_end);
	if (var_val)
	{
		result = ft_calloc(ft_strlen(tmp[0]) + ft_strlen(var_val)
				+ ft_strlen(tmp[1]) + 1, 1);
		ft_strlcpy(result, tmp[0], ft_strlen(tmp[0]) + 1);
		ft_strlcat(result, var_val, ft_strlen(tmp[0]) + ft_strlen(var_val) + 1);
		ft_strlcat(result, tmp[1], ft_strlen(tmp[0]) + ft_strlen(var_val)
			+ ft_strlen(tmp[1]) + 1);
	}
	else
	{
		result = ft_calloc(ft_strlen(tmp[0]) + ft_strlen(tmp[1]) + 1, 1);
		ft_strlcpy(result, tmp[0], ft_strlen(tmp[0]) + 1);
		ft_strlcat(result, tmp[1], ft_strlen(tmp[0]) + ft_strlen(tmp[1]) + 1);
	}
	return (free(tmp[0]), free(tmp[1]), free(temp_str), result);
}

char	*replace_var(char *str, t_env *env, int k)
{
	char	*var[3];
	int		nb[2];
	int		in_squote;
	int		in_dquote;

	if (!str)
		return (NULL);
	if (!env)
		return (ft_strdup(str));
	var[2] = ft_strdup(str);
	if (k == 1)
		free(str);
	nb[0] = 0;
	in_squote = 0;
	in_dquote = 0;
	while (var[2][nb[0]])
	{
		if (var[2][nb[0]] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (var[2][nb[0]] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (var[2][nb[0]++] == '$' && !in_squote)
		{
			var[0] = extract_var_name(var[2], nb[0], &nb[1]);
			if (var[0])
			{
				var[1] = get_var_value(var[0], env);
				return (free(var[0]), replace_var(rep2(var[1], nb[1], var[2],
							nb[0] - 1), env, 1));
			}
		}
	}
	return (var[2]);
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
		new_str = replace_var(tab[i], env, 0);
		if (new_str)
		{
			free(old_str);
			tab[i] = new_str;
		}
		i++;
	}
	return (tab);
}
