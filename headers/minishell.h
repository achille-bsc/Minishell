/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/05/10 00:39:35 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "./structures.h"
# include "../libft/libft.h"

t_env	*ft_envnew(char *line);
char	**parser(char *prompt);
void	ft_env(t_env *env);

// ---- Parsing | Tokening ----
t_args	*tokener(char *prompt);

// ----- Parsing | Utils -----
int		set_dquote(char c, int in_dquote);
int		set_squote(char c, int in_squote);
int		handle_redir(char *prompt, int i, char *word);

// ------- Free | Error -------
void	ft_error(char *msg, t_mnours *data);

// -------- Util | lst --------
int	ft_args_lstsize(t_args *lst);
#endif
