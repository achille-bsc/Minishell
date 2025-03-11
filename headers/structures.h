/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abosc <abosc@student.42lehavre.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:20:29 by abosc             #+#    #+#             */
/*   Updated: 2025/03/11 20:27:57 by alegrix          ###   ########.fr       */
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
	AP,
	PIP
};

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
	char	**env;
	int		nb_pipe;
	t_exec	*ex;
	int		act_exec;
}				t_mnours;

#endif
