/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:58:58 by abosc             #+#    #+#             */
/*   Updated: 2025/06/20 17:59:32 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	analyze_quote_type(char *str)
{
	int	len;
	int	i;
	int	in_squote;
	int	in_dquote;
	int	has_quotes;

	if (!str || !*str)
		return (NO_Q);
	len = ft_strlen(str);
	i = 0;
	in_squote = 0;
	in_dquote = 0;
	has_quotes = 0;
	// Analyser le string entier pour comprendre le contexte des quotes
	while (i < len)
	{
		if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			has_quotes = 1;
		}
		else if (str[i] == '\"' && !in_squote)
		{
			in_dquote = !in_dquote;
			has_quotes = 1;
		}
		i++;
	}

	// Si on a des quotes, c'est un token avec quotes (même complexe)
	if (has_quotes)
	{
		// Si le string commence et se termine par des guillemets doubles simples
		if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"')
		{
			// Vérifier s'il n'y a que des guillemets doubles extérieurs
			int j = 1;
			int internal_quotes = 0;
			while (j < len - 1)
			{
				if (str[j] == '\"')
					internal_quotes = 1;
				j++;
			}
			if (!internal_quotes)
				return (D_Q);
		}

		// Si le string commence et se termine par des quotes simples
		if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		{
			// Vérifier qu'il n'y a pas de quotes simples à l'intérieur
			int j = 1;
			while (j < len - 1)
			{
				if (str[j] == '\'')
					return (NO_Q);  // Il y a des quotes simples à l'intérieur
				j++;
			}
			return (S_Q);
		}

		// Cas complexe : retourner NO_Q mais on traitera quand même les quotes
		return (NO_Q);
	}

	return (NO_Q);
}
