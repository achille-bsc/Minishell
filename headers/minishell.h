/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/05/10 02:54:06 by abosc            ###   ########.fr       */
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
void	ft_env(t_env *env);

// ---- Parsing | Tokening ----
void	parser(char *prompt);
void	parsing(t_args *tokens);
t_args	*tokener(t_mnours *mnours);
void	set_tok_in_mnours(t_args *tokens, t_mnours *mnours);

// ----- Parsing | Utils -----
int		set_dquote(char c, int in_dquote);
int		set_squote(char c, int in_squote);
int		handle_redir(char *prompt, int i, char *word);

// ------- Free | Error -------
void	ft_error(char *msg, t_mnours *data);

// -------- Util | lst --------
int	ft_args_lstsize(t_args *lst);
#endif
