/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:56:43 by abosc             #+#    #+#             */
/*   Updated: 2025/03/09 23:48:36 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	count_words(char *s, char c)
{
	int	in_words;
	int	count;
	int	in_dquote;

	count = 0;
	in_words = 0;
	in_dquote = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && in_words == 0 && in_dquote == 0)
		{
			in_words = 1;
			count++;
		}
		else if (*s == c)
			in_words = 0;
		if (*s == '"' && !in_dquote)
			in_dquote = 1;
		if (*s == '"' && in_dquote)
			in_dquote = 0;
		s++;
	}
	return (count);
}

static char	*splitting(char *splitter, char *s, int *i, char c)
{
	int	start;
	int	len;
	int	in_dquote;

	len = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && (s[*i] != c || in_dquote))
	{
		if (c == '"' && !in_dquote)
			in_dquote = 1;
		if (c == '"' && in_dquote)
			in_dquote = 0;
		len++;
		(*i)++;
	}
	splitter = ft_substr((char *)s, start, len);
	return (splitter);
}

static char	**ft_split_with_dquotes(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (j < count_words ((char *)s, c))
	{
		result[j] = splitting(result[j], (char *)s, &i, c);
		if (!result[j])
		{
			while (j--)
				free(result[j]);
			free(result);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**parser(char *prompt)
{
	char	*prompt_cpy;
	char	**spaces_splited_prompt;

	prompt_cpy = ft_strdup(prompt);
	spaces_splited_prompt = ft_split_with_dquotes(prompt_cpy, ' ');
	return (spaces_splited_prompt);
}

int	main(int argc, char *argv[])
{
	printf("%s", parser("\"coucou cava\" et toi")[0]);
	printf("ksjd %s", parser("\"coucou cava\" et toi")[1]);
	printf("zx,cm %s", parser("\"coucouc cava\" et toi")[2]);
	return (EXIT_SUCCESS);
}
