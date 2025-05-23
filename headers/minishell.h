/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/05/23 21:06:00 by alegrix          ###   ########.fr       */
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
void	parser(char *prompt, t_mnours *data);
void	parsing(t_args *tokens);
void	tokener(t_mnours *mnours, t_exec *exec, t_args *tokens);
void	set_token(t_mnours *data);
// void	set_tok_in_mnours(t_args *tokens, t_mnours *mnours);

// ----- Parsing | Utils -----
int		set_dquote(char c, int in_dquote);
int		set_squote(char c, int in_squote);
int		handle_redir(char *prompt, int i, t_lst **word);
void	check_args(t_exec *exec);
int		complete(int i, char *prompt, t_lst **word, int *in_quote);
t_lst	*create_word(void);

// ------- Free | Error -------
void	ft_error(char *msg, t_mnours *data);
void	free_exec(t_exec *exe);
void	free_args(t_args *args);
void	ft_free_word(t_lst *word);
void	free_mnours(t_mnours *data);

// -------- Util | lst --------
int		ft_args_lstsize(t_args *lst);
void	ft_lstconvert(t_mnours *mini, t_exec *data);

void	redir(t_exec *c);
void	execute(t_mnours *d, char **env);

void	ft_echo(char **line);
void	ft_env(t_env *env);
void	ft_export(t_env *env, char **line);
t_env	*ft_unset(t_env *env, char **line);

// -------- Tests | Print tokener --------
void	write_args(t_exec *exec);

#endif
