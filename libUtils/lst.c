/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:14 by abosc             #+#    #+#             */
/*   Updated: 2025/05/27 00:19:28 by abosc            ###   ########.fr       */
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

void	free_lst(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
}

char	*remove_quotes(char *str, int quote_type)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	if (!str || quote_type == NO_Q)
		return (ft_strdup(str));
	len = ft_strlen(str);
	if (len < 2)
		return (ft_strdup(str));
	if ((quote_type == S_Q && str[0] == '\'' && str[len - 1] == '\'') ||
		(quote_type == D_Q && str[0] == '\"' && str[len - 1] == '\"'))
	{
		result = malloc(sizeof(char) * (len - 1));
		if (!result)
			return (NULL);
		i = 1;
		j = 0;
		while (i < len - 1)
			result[j++] = str[i++];
		result[j] = '\0';
		return (result);
	}
	return (ft_strdup(str));
}

void	converter(t_exec *dat_tmp, t_args *tmp, t_mnours *mini, int i)
{
	while (dat_tmp)
	{
		i = 0;
		tmp = dat_tmp->args;
		while (tmp)
		{
			if (tmp->tok == CMD)
				i++;
			tmp = tmp->next;
		}
		dat_tmp->lst = malloc(sizeof(char *) * (i + 1));
		if (!dat_tmp->lst)
			ft_error("malloc error", mini);
		i = 0;
		tmp = dat_tmp->args;
		while (tmp)
		{
			if (tmp->tok == CMD)
			{
				char *quoted_removed = remove_quotes(tmp->name, tmp->quote);
				dat_tmp->lst[i++] = quoted_removed;
			}
			tmp = tmp->next;
		}
		dat_tmp->lst[i] = NULL;
		dat_tmp = dat_tmp->next;
	}
}

void	ft_lstconvert(t_mnours *mini, t_exec *data)
{
	t_exec	*dat_tmp;
	t_args	*tmp;
	int		i;

	dat_tmp = data;
	i = 0;
	tmp = dat_tmp->args;
	converter(dat_tmp, tmp, mini, i);
}
