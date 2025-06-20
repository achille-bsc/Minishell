/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:14 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 18:07:02 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_lstargssize(t_args *lst)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = lst;
	if (!lst)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	**ft_tabdup(char **tab)
{
	char	**res;
	int		i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	res = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tab != NULL && tab[i] != NULL)
	{
		i[res] = ft_strdup(tab[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*remove_quotes(char *str, int quote_type)
{
	char	*result;
	int		i;
	int		j;

	if (!str || quote_type == NO_Q)
		return (ft_strdup(str));
	if (ft_strlen(str) < 2)
		return (ft_strdup(str));
	j = 0;
	i = 1;
	if (quote_type == S_Q && str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
	{
		result = malloc(sizeof(char) * (ft_strlen(str) - 1));
		while (i < (int)ft_strlen(str) - 1)
			result[j++] = str[i++];
		return (result[j] = '\0', result);
	}
	if (quote_type == D_Q && str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
	{
		result = malloc(sizeof(char) * (ft_strlen(str) - 1));
		while (i < (int)ft_strlen(str) - 1)
			result[j++] = str[i++];
		return (result[j] = '\0', result);
	}
	return (process_complex_quotes(str));
}

char	*process_complex_quotes(char *str)
{
	char	*result;
	int		i[2];
	int		len;
	int		in_dquote;
	int		in_squote;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(sizeof(char) * (len + 1));
	i[0] = 0;
	i[1] = 0;
	in_dquote = 0;
	in_squote = 0;
	while (i[0] < len)
	{
		if (str[i[0]] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i[0]] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else
			result[i[1]++] = str[i[0]];
		i[0]++;
	}
	return (result[i[1]] = '\0', result);
}

void	converter(t_exec *dat_tmp, t_args *tmp, t_mnours *mini, int i)
{
	char	*expanded_name;
	char	*quoted_removed;

	i = 0;
	tmp = dat_tmp->args;
	while (tmp)
	{
		if (tmp->tok == CMD)
			i++;
		tmp = tmp->next;
	}
	dat_tmp->lst = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = dat_tmp->args;
	while (tmp)
	{
		if (tmp->tok == CMD)
		{
			if (tmp->quote != S_Q)
			{
				expanded_name = replace_variable(tmp->name, mini->env, 0);
				if (!expanded_name || !ft_strncmp(expanded_name, "", ft_strlen(expanded_name)))
				{
					if (expanded_name)
						free(expanded_name);
					expanded_name = ft_strdup("\0");
				}
			}
			else
				expanded_name = ft_strdup(tmp->name);
			if (tmp->quote == NO_Q && (ft_strchr(expanded_name, '\'') || ft_strchr(expanded_name, '\"')))
				quoted_removed = process_complex_quotes(expanded_name);
			else
				quoted_removed = remove_quotes(expanded_name, tmp->quote);
			if (!quoted_removed)
				quoted_removed = ft_strdup(expanded_name);
			dat_tmp->lst[i++] = quoted_removed;
			free(expanded_name);
		}
		tmp = tmp->next;
	}
	dat_tmp->lst[i] = NULL;
}

