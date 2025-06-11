/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/06/12 00:00:20 by abosc            ###   ########.fr       */
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
# define SIGNAL_EXECUTE 1
# define SIGNAL_IGN 2
# define SIGNAL_DEFAULT 3
# define SIGNAL_HERE_DOC 4

extern int	g_signal;

t_env		*ft_envnew(char *line);

// ---- Variables d'environnement ----
char		**var_search(char **tab, t_env *env);
char		*replace_variable(char *str, t_env *env);
char		*get_var_value(char *var_name, t_env *env);

// ---- Parsing | Tokening ----
void		parser(char *prompt, t_mnours *data);
void		parsing(t_args *tokens);
void		tokener(t_mnours *mnours, t_exec *exec, t_args *tokens);
int			analyze_quote_type(char *str);
// void	set_tok_in_mnours(t_args *tokens, t_mnours *mnours);

// ----- Parsing | Utils -----
int			handle_redir(char *prompt, int i, t_lst **word);
void		check_args(t_exec *exec);
int			complete(int i, char *line, t_lst **word, int *in_squote,
				int *in_dquote);
t_lst		*create_word(void);
int			verif(t_mnours *mnours);
int			is_buildtin(t_exec *exe, char *cmd);

// ------- Free | Error -------
void		ft_error(char *msg, t_mnours *data);
void		free_exec(t_exec *exe);
void		free_args(t_args *args);
void		ft_free_word(t_lst *word);
void		free_mnours(t_mnours *data);

// -------- Util | lst --------
int			ft_args_lstsize(t_args *lst);
void		ft_lstconvert(t_mnours *mini, t_exec *data);
char		*remove_quotes(char *str, int quote_type);

int			redir(t_exec *c, t_mnours *mnours);
void		execute(t_mnours *d, char **env);
void		exec_build(t_mnours *data, char **l, t_exec *c);
int			should_expand_heredoc(t_args *delimiter);
char		*get_clean_delimiter(t_args *delimiter);

void		ft_exit(t_mnours *data, char **line);
void		ft_echo(char **line);
void		ft_env(char **env);
void		ft_export(t_mnours *data, t_env *env, char **line);
t_env		*ft_unset(t_env *env, char **line, t_mnours *mnours);

// -------- Tests | Print tokener --------
void		write_args(t_exec *exec);

// -------- Executing | Utils ---------
void		dup_close(int fd, int fileno);
void		free_array(char **array);
char		*process_complex_quotes(char *str);

// -------- Executing | Utils ---------
void		resetfd(int fd, int fout);

// ------- Tokener | Utils ------
void		set_quotes(char prompt, int *in_squote, int *in_dquote);
int			capipe(char *prompt, int i, t_lst **word);
int			casemicolon(char *prompt, int i, t_lst **word);
void		tok_pipe(t_mnours *data, t_exec *exec, t_args *pre_tok);
void		tok_semicolon(t_mnours *data, t_exec *exec, t_args *pre_tok);
void		set_token(t_mnours *data);
// void	clear_rl_line(void);

int			ft_cd(char **line, t_mnours *mnours);
int			get_array_size(char **array);

void		set_env(t_mnours *g, char **env);
char		*ft_getenv(char *name, t_env *env);
t_env		*get_env(t_mnours *mnours, char *var);
char		*replacer(t_mnours *mnours, char *line);
int			ft_pwd(t_mnours *mnours);
char		**convert_env(t_mnours *mnours);

void		update_env(t_mnours *mnours, char *var_name, char *new_value);

void		signals(int sig);

void		close_fds(int fd);
// static int	g_signal = 0;

#endif
