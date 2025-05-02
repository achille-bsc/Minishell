/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:20:29 by abosc             #+#    #+#             */
/*   Updated: 2025/05/02 16:01:04 by abosc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H 

enum e_token
{
	OP,
	HD,
	CMD,
	TR,
	AP
};

enum e_quote
{
	NO_Q,
	S_Q,
	D_Q
};

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_args
{
	enum e_quote	quote;
	enum e_token	tok;
	char			*name;
	struct s_args	*next;
}				t_args;

typedef struct s_exec
{
	int				l_hd;
	int				fin;
	int				fout;
	struct s_exec	*next;
	t_args			*args;
}				t_exec;

typedef struct s_mnours
{
	int		argc;
	char	*line;
	int		nb_pipe;
	t_exec	*ex;
	int		act_exec;
	char	*pwd;
	t_env	*env;
	int		exit;
}				t_mnours;

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}					t_lst;

#endif
