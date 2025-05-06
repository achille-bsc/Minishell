/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:41:14 by abosc             #+#    #+#             */
/*   Updated: 2025/05/06 18:44:41 by alegrix          ###   ########.fr       */
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

void	ft_lstconvert(t_mnours *mini, t_exec *data)
{
	t_args	*tmp;
	int		i;

	i = 0;
	tmp = data->args;
	while (tmp)
	{
		if (tmp->tok == CMD)
			i++;
		tmp = tmp->next;
	}
	data->lst = malloc(sizeof(char *) * (i + 1));
	if (!data)
		ft_error("malloc error", mini);
	i = 0;
	tmp = data->args;
	while (tmp)
	{
		if (tmp->tok == CMD)
			data->lst[i++] = tmp->name;
		tmp = tmp->next;
	}
	data->lst[i] = NULL;
}
