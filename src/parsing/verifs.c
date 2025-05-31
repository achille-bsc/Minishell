/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:48:01 by abosc             #+#    #+#             */
/*   Updated: 2025/05/31 04:55:19 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_quotes(int type, char *line)
{
	int		counter;
	int		i;
	char	c;

	i = 0;
	counter = 0;
	if (type == 1)
		c = '"';
	if (type == 2)
		c = '\'';
	while (line[i])
	{
		if (line[i] == c)
			counter++;
		i++;
	}
	if (counter % 2 == 1)
		return (1);
	return (0);
}

// char	*replace_word(const char *str, const char *old, const char *new_word)
// {
// 	char	*pos;
// 	size_t	len_before;
// 	size_t	len_old;
// 	size_t	len_new;
// 	char	*result;

// 	if (!str || !old || !new_word)
// 		return (NULL);
// 	pos = ft_strstr(str, old);
// 	ft_printf("test2\n");
// 	if (!pos)
// 		return (ft_strdup(str));
// 	ft_printf("test3\n");
// 	len_before = pos - str;
// 	len_old = strlen(old);
// 	ft_printf("test4\n");
// 	len_new = strlen(new_word);
// 	ft_printf("test5\n");
// 	result = malloc(len_before + len_new + strlen(pos + len_old) + 1);
// 	ft_printf("test6\n");
// 	if (!result)
// 		return (NULL);
// 	ft_printf("test7\n");
// 	strncpy(result, str, len_before);
// 	ft_printf("test8\n");
// 	strcpy(result + len_before, new_word);
// 	ft_printf("test9\n");
// 	strcpy(result + len_before + len_new, pos + len_old);
// 	ft_printf("test1000000\n");
// 	return (result);
// }

// void	replace_vars(t_mnours *mnours, char *line)
// {
// 	int		i[2];
// 	char	**splited_line;
// 	char	*word;

// 	i[0] = 0;
// 	i[1] = 0;
// 	splited_line = ft_split(line, ' ');
// 	word = NULL;
// 	while (splited_line[i[0]])
// 	{
// 		word = splited_line[i[0]];
// 		if (ft_strchr(splited_line[i[0]], '$') != NULL)
// 		{
// 			while (splited_line[i[0]][i[1]])
// 			{
// 				if (splited_line[i[0]][i[1]] == '$')
// 				{
// 					ft_printf("coucououuuuoriginal\n");
// 					replace_word(splited_line[i[0]], word, get_env(mnours,
// 							word)->value);
// 				}
// 				i[1]++;
// 				(*word)++;
// 			}
// 		}
// 		i[0] += 1;
// 	}
// }

// PROMPT EXEMPLES
// > echo $USER
// > echo "$USER"
// > echo '$USER'
// > echo "'$USER'"
// > echo '"$USER"'
// > echo $test
// > echo "$test"
// > echo '$test'
// > echo "'$test'"
// > echo '"$test"'
int	verif(t_mnours *mnours)
{
	if (check_quotes(1, mnours->line) == 1)
	{
		ft_error("Syntax Error: incorrect quotes (single)", mnours);
		return (1);
	}
	if (check_quotes(2, mnours->line) == 1)
	{
		ft_error("Syntax Error: incorrect quotes (double)", mnours);
		return (1);
	}
	// mnours->line = replacer(mnours, mnours->line);
	// ft_printf("%s", mnours->line);
	return (0);
}
