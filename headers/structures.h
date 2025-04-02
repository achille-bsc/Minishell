/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:20:29 by abosc             #+#    #+#             */
/*   Updated: 2025/04/02 22:47:28 by alegrix          ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_args
{
	int				in_dquote;
	int				in_quote;
	char			**args;
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
}				t_mnours;

typedef struct s_gnours
{
	t_env		*env;
	t_mnours	*mini;
}				t_gnours;

#endif
