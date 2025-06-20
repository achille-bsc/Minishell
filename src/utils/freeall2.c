/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:57:20 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 17:57:30 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_free_word(t_lst *word)
{
	t_lst	*tmp;

	tmp = word;
	while (word)
	{
		tmp = word;
		word = word->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env *temp;

	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
}