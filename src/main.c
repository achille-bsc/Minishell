/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:30 by abosc             #+#    #+#             */
/*   Updated: 2025/03/10 00:07:12 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_exec	*creat_exec_type(void)
{
	t_exec	*result;

	result = (ft_calloc(sizeof(t_exec *), 1));
	if (!result)
		exit(1);
	result->args = ft_calloc(sizeof(t_args *), 1);
	if (!result->args)
		exit(1);
	return (result);
}

void	count_pipe(t_mnours *d)
{
	int		i;
	t_exec	*cmd;

	cmd = creat_exec_type();
	d->ex = cmd;
	i = 0;
	while (d->line[i])
	{
		if (d->line[i++] == '|')
		{
			cmd->next = creat_exec_type();
			cmd = cmd->next;
			d->nb_pipe++;
		}
	}
}

void	token_dir(char *l, int i, t_exec *cmd)
{
	t_args	*tmp;
	int		j;

	tmp = cmd->args;
	while (tmp)
		tmp = tmp->next;
	if (l[i] == '<' && l[i + 1] == '<')
		tmp->tok = HD;
	else if (l[i] == '>' && l[i + 1] == '>')
		tmp->tok = AP;
	else if (l[i] == '<')
		tmp->tok = OP;
	else if (l[i] == '>')
		tmp->tok = TR;
	j = i;
	while (l[i] == '>' || l[i] == '<')
		if (i++ == j + 2)
			exit(1);
	j = i;
	while (ft_isalnum(l[i]) || l[i] == '/' || l[i])
		i++;
	ft_strlcpy(tmp->args[0], l + j, i);
}

void	tokenning(char *line, t_exec *cmd)
{
	int	i;

	i = 0;
	while (line[i] != '|' || line[i])
		i++;
	if (line[i] == '|')
	{
		i = 0;
		while (line[i] != '|')
		{
			if (line[i] == '>' | line[i] == '<')
				token_dir(line, i, cmd);
		}
	}
}

void	parsing(t_mnours *d)
{
	int	i;

	i = 0;
	count_tok(d);
	tokenning(d);
	if (line[i] == '>')

}

int	main(int argc, char **argv, char **env)
{
	parsing();
	return (0);
}

