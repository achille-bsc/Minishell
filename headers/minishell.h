/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/05/29 02:33:40 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./structures.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

t_env	*ft_envnew(char *line);
void	ft_env(t_env *env);

// ---- Parsing | Tokening ----
void	parser(char *prompt, t_mnours *data);
void	parsing(t_args *tokens);
void	tokener(t_mnours *mnours, t_exec *exec, t_args *tokens);
// void	set_tok_in_mnours(t_args *tokens, t_mnours *mnours);

// ----- Parsing | Utils -----
int		set_squote(char c, int in_squote);
int		handle_redir(char *prompt, int i, t_lst **word);
void	check_args(t_exec *exec);
int		complete(int i, char *prompt, t_lst **word, int *in_quote);
t_lst	*create_word(void);
int		verif(t_mnours *mnours);
int		is_buildtin(t_exec *exe, char *cmd);

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
void	exec_build(t_mnours *data, char **l);

void	ft_exit(t_mnours *data, char **line);
void	ft_echo(char **line);
void	ft_env(t_env *env);
void	ft_export(t_env *env, char **line);
t_env	*ft_unset(t_env *env, char **line);

// -------- Tests | Print tokener --------
void	write_args(t_exec *exec);

// -------- Executing | Utils ---------
void	dup_close(int fd, int fileno);
void	free_array(char **array);

// -------- Executing | Utils ---------
void	resetfd(int fd, int fout);

// ------- Tokener | Utils ------
int		set_dquote(char c, int in_dquote);
int		capipe(char *prompt, int i, t_lst **word);
void	tok_pipe(t_mnours *data, t_exec *exec, t_args *pre_tok);
void	set_token(t_mnours *data);
void	signals(void);
void	sigint_handler(int sig);


// t_env	*set_env(char **env);

#endif
