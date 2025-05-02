/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegrix <alegrix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/04/22 19:06:37 by alegrix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include "./structures.h"
# include "../libft/libft.h"

t_env	*ft_envnew(char *line);
char	**parser(char *prompt);
void	ft_env(t_env *env);

// --------- Parsing ---------
t_args	*tokener(char *prompt);
// ----- Parsing | Utils -----

int	set_dquote(char c, int in_dquote);
int	set_squote(char c, int in_squote);
int	handle_redir(char *prompt, int i, char *word);

#endif
