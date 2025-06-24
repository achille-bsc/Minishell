/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:11:54 by abosc             #+#    #+#             */
/*   Updated: 2025/06/24 03:57:14 by alegrix          ###   ########.fr       */
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

void		get_words2(t_lst *words);
int			checker(t_exec *exec);
int			got_ended(char *line, int i, char c);
int			check_quotes_2(char c[2], int counter);
void		prompter(t_mnours *mnours);
void		free_env(t_env *env);
void		here_doc(t_args *n, t_exec *c, t_mnours *mnours);
void		converter(t_exec *dat_tmp, t_args *tmp, t_mnours *mini, int i);
t_env		*ft_envnew(char *line);

// ---- Variables d'environnement ----
char		**var_search(char **tab, t_env *env);
char		*replace_var(char *str, t_env *env, int k);
char		*get_var_value(char *var_name, t_env *env);

// ---- Parsing | Tokening ----
void		parser(char *prompt, t_mnours *data);
void		parsing(t_args *tokens);
int			tokener(t_mnours *mnours, t_exec *exec, t_args *tokens);
int			analyze_quote_type(char *str);

// ----- Parsing | Utils -----
int			handle_redir(char *prompt, int i, t_lst **word);
void		check_args(t_exec *exec);
int			complete(int i, char *line, t_lst **word, t_quotes *q);
t_lst		*create_word(void);
int			verif(t_mnours *mnours);
int			is_buildtin(t_exec *exe, char *cmd);
void		iffree(char *str, int *k);
void		replace_mid(t_quotes *q, char *v, int i);

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
char		**ft_tabdup(char **tab);

int			set_heredoc(t_exec *c, t_mnours *data);
int			redir(t_exec *c, t_mnours *data);
void		execute(t_mnours *d);
void		exec_build(t_mnours *data, char **l, t_exec *c);
char		*get_clean_delimiter(t_args *delimiter);

int			ft_exit(t_mnours *data, char **line);
int			ft_echo(char **line);
int			ft_env(char **tab);
int			ft_export(t_mnours *data, t_env *env, char **line);
t_env		*ft_unset(t_env *env, char **line, t_mnours *mnours);

// -------- Executing | Utils ---------
void		close_next_hd(t_exec *c);
void		exec_close_fd(t_exec *cmd);
void		dup_close(int fd, int fileno);
void		free_array(char **array);
char		*process_complex_quotes(char *str);
char		*find_name(char *line, int *i);
char		*find_value(char *line, int *i);
void		access_path(char **cmd, char **env, t_mnours *d);
char		*find_path(char *cmop, char **paths);
void		exec_cmd(char **envp, t_exec *c, t_mnours *mnours);
pid_t		child_factory(t_mnours *data, t_exec *c);
void		piping(t_exec *cmd);

// -------- Executing | Utils ---------
void		resetfd(int fd, int fout);

// ------- Tokener | Utils ------
t_lst		*get_words(char *prompt);
void		set_quotes(char prompt, t_quotes *q);
int			capipe(char *prompt, int i, t_lst **word);
int			casemicolon(char *prompt, int i, t_lst **word);
void		tok_pipe(t_mnours *data, t_exec *exec, t_args *pre_tok);
void		tok_semicolon(t_mnours *data, t_exec *exec, t_args *pre_tok);
int			set_token(t_mnours *data);
void		expends_exit_status(t_mnours *mnours);

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
void		signals_wait(void);
void		free_prompt(t_mnours *mnours);
void		close_fds(int fd);

#endif
