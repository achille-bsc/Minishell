/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:56:43 by abosc             #+#    #+#             */
/*   Updated: 2025/03/20 00:05:31 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static int	get_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

char	**ft_split_with_dquotes(char const *s, char c)
{
	char	**split;
	size_t	len;
	int		i;
	int		in_dquotes;
	char	*str;

	in_dquotes = 0;
	split = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!s || !split)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (*s == '\"')
			{
				in_dquotes = !in_dquotes;
				s++;
			}
			if (in_dquotes)
			{
				if (!ft_strchr(s, '\"'))
					len = ft_strlen(s);
				else
					len = ft_strchr(s, '\"') - s;
				str = ft_strjoin("\"", ft_substr(s, 0, len + (get_len((s + len
						+ 1), c) + 1)));
				if (s[len + 1] == c)
					split[i++] = str;
				else
				{
					split[i++] = str;
					len += get_len((s + len + 1), c) + 1;
				}
				s += len;
				if (*s == '\"')
				{
					in_dquotes = !in_dquotes;
					s++;
				}
			}
			else
			{
				if (!ft_strchr(s, c))
					len = ft_strlen(s);
				else
					len = ft_strchr(s, c) - s;
				split[i++] = ft_substr(s, 0, len);
				s += len;
			}
		}
	}
	split[i] = NULL;
	return (split);
}

int check_dquotes(char *prompt)
{
	int i;
	int dquotes;

	i = 0;
	dquotes = 0;
	while (prompt[i])
	{
		if (prompt[i] == '"')
			dquotes++;
		i++;
	}
	if (dquotes % 2 != 0)
		return (1);
	return (0);
}

int check_squotes(char *prompt)
{
	int i;
	int squotes;

	i = 0;
	squotes = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'')
			squotes++;
		i++;
	}
	if (squotes % 2 != 0)
		return (1);
	return (0);
}

int check_txt_afer_pipe(char *prompt)
{
	int i;
	
	i = 0;
	while(prompt[i])
	{
		if (prompt[i] == '|')
		{
			while(prompt[i] == ' ' || prompt[i] == '\t')
				i++;
			if (prompt[i++] != '\0')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (1);
}
void	parser(char *prompt)
{
	char	*prompt_cpy;
	char	**spaces_splited_prompt;
	prompt_cpy = ft_strdup(prompt);
	if (check_txt_afer_pipe(prompt_cpy) == 0)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		exit(0);
	}
	if (check_dquotes(prompt_cpy) == 1)
	{
		printf("Error: dquotes not closed\n");
		exit(0);
	}
	if (check_squotes(prompt_cpy) == 1)
	{
		printf("Error: squotes not closed\n");
		exit(0);
	}
	spaces_splited_prompt = ft_split_with_dquotes(prompt_cpy, ' ');
	tokener(spaces_splited_prompt);
}

// int	main(void)
// {
// 	printf("%s\n", parser("c\"a\"t \"Make'f'ile 3\" | -e")[0]);
// 	printf("test: %s\n", parser("c\"a\"t \"Mak'efile 3\"|\0")[1]);
// 	printf("test 2: %s\n", parser("c\"a\"t \"Makefile 3\" -e")[2]);
// 	return (EXIT_SUCCESS);
// }
